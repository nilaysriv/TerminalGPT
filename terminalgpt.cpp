#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <unistd.h>

using json = nlohmann::json;

// UTILITY FUNCTIONS
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string clean_command(std::string cmd) {
    cmd.erase(std::remove(cmd.begin(), cmd.end(), '`'), cmd.end());
    if (cmd.find("bash") == 0) cmd.erase(0, 4);
    cmd.erase(0, cmd.find_first_not_of(" \n\r\t"));
    size_t last = cmd.find_last_not_of(" \n\r\t");
    return (last == std::string::npos) ? "" : cmd.substr(0, last + 1);
}

//  COLOR CODES 
const std::string RESET = "\x1b[0m";
const std::string GREEN = "\x1b[1;32m";
const std::string BLUE  = "\x1b[1;34m";
const std::string RED   = "\x1b[1;31m";
const std::string CYAN  = "\x1b[1;36m";
const std::string BOLD  = "\x1b[1m";

int main() {
    std::string server_url = "http://100.118.161.53:11434/api/generate"; //replace with ip address of your own server ollama instance
    std::cout << CYAN << "===========================================" << RESET << std::endl;
    std::cout << BOLD << " TERMINAL-GPT " << RESET << std::endl;
    std::cout << CYAN << "===========================================" << RESET << std::endl;
    std::cout << "Connected to: " << BLUE << server_url << RESET << "\n" << std::endl;

    while (true) {
        std::string user_input;
        std::cout << BOLD << "[Nilay@Fedora]" << RESET << " > ";
        std::getline(std::cin, user_input);
        
        if (user_input == "exit" || user_input == "quit") break;

        // API LOGIC START
        CURL* curl = curl_easy_init();
        if (curl) {
            std::string readBuffer;
            json payload = {
                {"model", "qwen2.5-coder:7b"},
                {"prompt", user_input},
                {"system", "Provide ONLY the raw Linux bash command. No markdown."},
                {"stream", false}
            };
            std::string json_str = payload.dump();

            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, server_url.c_str()); // Using IP here
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            if (curl_easy_perform(curl) == CURLE_OK) {
                auto res_json = json::parse(readBuffer);
                std::string cmd = clean_command(res_json["response"]);

                std::cout << "\n" << BOLD << "🤖 AI Suggestion: " << RESET << GREEN << cmd << RESET << std::endl;
                std::cout << "Confirm execution? (y/n): ";
                
                std::string confirm;
                std::getline(std::cin, confirm);

                if (confirm == "y" || confirm == "Y") {
                    std::cout << BLUE << "--- OUTPUT ---" << RESET << std::endl;
                    system(cmd.c_str()); 
                    std::cout << BLUE << "--------------" << RESET << std::endl;
                }
            } else {
                std::cerr << RED << "✖ Network Error: Check server connection." << RESET << std::endl;
            }
            curl_easy_cleanup(curl);
        }
    }
    return 0;
}
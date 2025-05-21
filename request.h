#ifndef REQUEST_H
#define REQUEST_H
#include <iostream>
#include <curl/curl.h>
#include "output_config.h"

struct Config {
    std::string url;
    std::string wordlist;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

void request(Config cfg, std::string line) {
    Out_color getColors = colors();
    CURL* curl = curl_easy_init();
    if(curl) {
        std::string response;
        std::string url_mod = cfg.url+"/"+line;
        curl_easy_setopt(curl, CURLOPT_URL, url_mod.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);          

        CURLcode res = curl_easy_perform(curl);                        
        if(res == CURLE_OK){
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            std::cout << getColors.b_white 
                      << "[ + ] URL: " 
                      << getColors.green 
                      << url_mod 
                      << getColors.reset 
                      << " - "
                      << getColors.b_white
                      << "Status Code: " 
                      << (response_code == 200 ? getColors.green : getColors.yellow) 
                      << response_code
                      << getColors.reset
                      << std::endl;
        } else {
            std::cerr << getColors.red 
                      << "[ - ] Erro CURL: " 
                      << curl_easy_strerror(res) 
                      << " na URL: " 
                      << url_mod 
                      << getColors.reset
                      << std::endl;
        }
        curl_easy_cleanup(curl);                                       
    }
}
#endif
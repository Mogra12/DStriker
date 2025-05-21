#ifndef REQUEST_H
#define REQUEST_H
#include <iostream>
#include <curl/curl.h>

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
            std::cout << "URL: " << url_mod << " - Status Code: " << response_code << std::endl;
        } else {
            std::cerr << "Erro CURL: " << curl_easy_strerror(res) << " na URL: " << url_mod << std::endl;
        }
        curl_easy_cleanup(curl);                                       
    }
}
#endif
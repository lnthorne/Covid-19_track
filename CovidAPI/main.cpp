//
//  main.cpp
//  CovidAPI
//
//  Created by Liam Thorne on 2022-01-06.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <json.h>
#include <curl/curl.h>
#include "MemoryChunk.hpp"
#include "View.hpp"

static size_t init_mem(char* content, size_t size, size_t nmemb, void* chunkdata);
void api_call(chunk*);
Json::Value read(chunk*, std::string, std::string);

int main() {
    Json::Value result;
    chunk* theChunk = new chunk;
    view* View = new view;
    std::string userIN;
    
    api_call(theChunk);
    
    userIN = View->countryQuery();
    result = read(theChunk, userIN, "PLACEHOLDER");
    View->displayInfo(result);
    
    delete View;
    delete theChunk;
    return 0;
}


//  creates cURL handle
//  calls API
//  calls init_mem to store data
void api_call(chunk* myChunk) {
    CURL* curlHandle = curl_easy_init();
    
//    check if init worked properly
    if (curlHandle) {
//        call to API
        curl_easy_setopt(curlHandle, CURLOPT_URL, "https://api.covid19api.com/summary");
//        callback function to store data
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, init_mem);
//        pass mem chunk into function
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, myChunk);
        
//        send the request
        CURLcode result = curl_easy_perform(curlHandle);
//        check if handle performed properly
        if (result != CURLE_OK)
            std::cout << curl_easy_strerror(result);
    }
    
    curl_easy_cleanup(curlHandle);
}


//  stores the data in the chunk of mem allocated
//  returns number of bytes taken if success
//      else returns CURLE_WRITE_ERR

static size_t init_mem(char* content, size_t size, size_t nmemb, void* chunkdata) {
//    number of bytes
    size_t realSize = size * nmemb;
    
    chunk* tempChunk = ((chunk*)chunkdata);
    char* address = (char*)realloc(tempChunk->Mem(), tempChunk->Size() + realSize + 1);
//    Check if space was allocated
    if (address == NULL)
        return CURLE_WRITE_ERROR;
    
    tempChunk->setNem(address);
    memcpy(&tempChunk->Mem()[tempChunk->Size()], content, realSize);
    tempChunk->setSIze(realSize);
//    base 0
    tempChunk->Mem()[tempChunk->Size()] = 0;
    
    return realSize;
}


//  parses through raw Json
//  returns a Json::Value of all the country data
//      else returns PARSE_ERR
Json::Value read(chunk* data, std::string country, std::string value) {
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;
    std::string errMess;
    
//    parse through data in chunk
//    return true if success
//      else false
    bool success = reader->parse(data->Mem(), data->Mem() + data->Size(), &root, &errMess);
    if (success) {
        const Json::Value resultArr = root["Countries"];
        for (auto& it : resultArr) {
//            set possible match tolower case
            std::string possible_match = it["Country"].asString();
            std::transform(possible_match.begin(), possible_match.end(), possible_match.begin(), ::tolower);
//            removes spaces from possible_match
            possible_match.erase(std::remove(possible_match.begin(), possible_match.end(), ' '), possible_match.end());
            if (possible_match == country)
                return it;
        }
    }
    std::cout << errMess;
    std::cout << "Sorry that country is not available\n";
    return 0;
}

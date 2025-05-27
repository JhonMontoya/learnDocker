#include <iostream>
#include <string>
#include <chrono>
#include <openssl/hmac.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

string pass = "Cl4v3Secreta";

string getToken (long timestamp){
    unsigned char* result;
    unsigned int len = 32;
    string msg = to_string(timestamp);

    result= HMAC(EVP_sha256(), pass.c_str(), pass.length(), (unsigned char*)msg.c_str(), msg.length(), NULL, &len);

    char hex[65];
    for (unsigned int i = 0; i < len; i++) {
        sprintf(&hex[i * 2], "%02x", result[i]);
    }
    return string(hex);

}

int main(){
    long timestamp = time(0)/30;
    string token = getToken(timestamp);

    json payload = {
        {"timestamp", timestamp},
        {"token", token},
        {"monto", 2500}
    };


    CURL *curl = curl_easy_init();

    if(curl){
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "http://servidor:3000/transferencia");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.dump().c_str());

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
    }

    return 0;
}
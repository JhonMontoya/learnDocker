#include <iostream>
#include <string>
#include <openssl/hmac.h>
#include <nlohmann/json.hpp>
#include "crow_all.h"

using json = nlohmann::json;
using namespace std;

string SECRET = "Cl4v3Secreta";

string generar_token(long timestamp) {
    unsigned char* result;
    unsigned int len = 32;
    string msg = to_string(timestamp);

    result = HMAC(EVP_sha256(), SECRET.c_str(), SECRET.length(),
                  (unsigned char*)msg.c_str(), msg.length(), NULL, &len);

    char hex[65];
    for (int i = 0; i < len; i++)
        sprintf(&hex[i * 2], "%02x", result[i]);

    return string(hex);
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/transaccion").methods("POST"_method)([](const crow::request& req) {
        auto data = json::parse(req.body);
        string token = data["token"];
        long timestamp = data["timestamp"];
        int monto = data["monto"];

        string token_valido = generar_token(timestamp);
        if (token == token_valido) {
            return crow::response(200, json{{"status", "aprobado"}, {"monto", monto}}.dump());
        } else {
            return crow::response(401, json{{"status", "rechazado"}, {"razon", "token inválido"}}.dump());
        }
    });

    app.port(3000).multithreaded().run();
}

#pragma once
#include "../crow_all.h"
#include <fstream>

void registerFileRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/upload").methods("POST"_method)([](const crow::request& req) {
        std::ofstream out("uploaded.txt");
        out << req.body;
        out.close();
        return crow::response(200, "Файл загружен");
    });

    CROW_ROUTE(app, "/api/download").methods("GET"_method)([]() {
        std::ifstream in("uploaded.txt");
        if (!in.is_open()) {
            return crow::response(404, "Файл не найден");
        }
        std::ostringstream ss;
        ss << in.rdbuf();
        return crow::response(200, ss.str());
    });
}
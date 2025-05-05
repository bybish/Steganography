#pragma once
#include "../crow_all.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <chrono>

namespace fs = std::filesystem;

// Генерация простого хеша из содержимого и времени (можно заменить на SHA256 при необходимости)
inline std::string generate_hash(const std::string& content) {
    auto now = std::chrono::system_clock::now().time_since_epoch().count();
    std::hash<std::string> hasher;
    size_t hash = hasher(content + std::to_string(now));
    std::ostringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

void registerFileRoutes(crow::App<CORS>& app) {
    CROW_ROUTE(app, "/api/upload").methods("POST"_method)([](const crow::request& req) {
        auto multipart_req = crow::multipart::message(req);

        if (multipart_req.parts.empty()) {
            return crow::response(400, "Пустой multipart-запрос");
        }

        const auto& file_part = multipart_req.get_part_by_name("file");
        if (file_part.body.empty()) {
            return crow::response(400, "Файл не получен");
        }

        std::string filename = generate_hash(file_part.body) + ".txt";

        std::ofstream out("input_files/" + filename);
        if (!out) {
            return crow::response(500, "Ошибка при сохранении файла");
        }
        out << file_part.body;
        out.close();

        crow::json::wvalue response;
        response["filename"] = filename;
        return crow::response{response};
    });
}
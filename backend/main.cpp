#include "crow_all.h"

// Простое middleware для CORS
struct CORS {
    struct context {};

    void before_handle(crow::request& req, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
    }

    void after_handle(crow::request&, crow::response& res, context&) {
        // можно добавлять логи или доп. заголовки
    }
};

int main() {
    crow::App<CORS> app;

    // Обработка POST запроса
    CROW_ROUTE(app, "/api/encode").methods("POST"_method)
    ([](const crow::request& req){
        // Пример обработки
        return crow::response("Encoded result");
    });

    // Обработка preflight OPTIONS-запроса
    CROW_ROUTE(app, "/api/encode").methods("OPTIONS"_method)
    ([](const crow::request& /*req*/, crow::response& res){
        res.code = 204; // No Content
        res.end();
    });

    app.port(8080).multithreaded().run();
}

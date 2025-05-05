#pragma once

#include "../crow_all.h"
#include "../cors.h"

void registerEncodeRoutes(crow::App<CORS>& app) {
    CROW_ROUTE(app, "/api/encode").methods("POST"_method)
    ([](const crow::request& req){
        // Пример обработки
        return crow::response("Encoded result");
    });
}

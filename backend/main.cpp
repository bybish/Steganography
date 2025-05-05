#include "crow_all.h"
#include "routes/encode.h"
#include "cors.h"

int main() {
    crow::App<CORS> app; // <-- Указываем middleware CORS

    // Регистрируем маршруты
    registerEncodeRoutes(app);

    app.port(8080).multithreaded().run();
}
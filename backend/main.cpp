#include "crow_all.h"
#include "routes/encode.h"
#include "routes/file.h"
#include "cors.h"

int main() {
    crow::App<CORS> app; // <-- Указываем middleware CORS

    // Создание директорий
    std::filesystem::create_directories("input_files");
    std::filesystem::create_directories("output_files");

    // Регистрируем маршруты
    registerEncodeRoutes(app);
    registerFileRoutes(app);

    app.port(8080).multithreaded().run();
}
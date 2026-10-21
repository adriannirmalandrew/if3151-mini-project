/*
 * Main Executable of IF3151 ADSA Mini Project
 * Support Ticket Priority Queue using Max Heap
 * Implementation: SQLite, Single Page Web Interface with controls and queue display
 * Boost.Beast for REST, SQLite for storage and almost-vanilla JS for UI
 */

#include <crow.h>
#include <crow/http_response.h>

int main() {
    crow::SimpleApp app;

    // Show index page
    CROW_ROUTE(app, "/")([](const crow::request& req, crow::response& res){
        res.set_static_file_info("html/index.html");
        res.end();
    });

    // Add entry
    CROW_ROUTE(app, "/add_entry")([](const crow::request& req, crow::response& res){
        res = crow::response(501, "WIP");
        res.end();
    });

    // Delete entry
    CROW_ROUTE(app, "/delete_entry")([](const crow::request& req, crow::response& res){
        res = crow::response(501, "WIP");
        res.end();
    });

    // Get all entries, sorted, in JSON
    CROW_ROUTE(app, "/get_all_entries")([](const crow::request& req, crow::response& res){
        res = crow::response(501, "WIP");
        res.end();
    });

    app.port(18080).multithreaded().run();
}

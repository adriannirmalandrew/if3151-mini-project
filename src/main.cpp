/*
 * Main Executable of IF3151 ADSA Mini Project
 * Support Ticket Priority Queue using Max Heap
 * Implementation: SQLite, Single Page Web Interface with controls and queue display
 * Crow.cpp for REST, SQLite for storage and almost-vanilla JS for UI
 * SQLite columns: uuid (String), description (String), creation_time (Integer), deadline_time (Integer), priority (Integer)
 */

#include <string>

#include <crow.h>
#include <crow/json.h>
#include <crow/http_response.h>

#include "ticket.h"
#include "utils.h"

using std::string, std::stoi, std::stoll;

int main() {
    crow::SimpleApp app;

    // Show index page
    CROW_ROUTE(app, "/")([](const crow::request& req, crow::response& res){
        res.set_static_file_info("html/index.html");
        res.end();
    });

    // Add entry
    CROW_ROUTE(app, "/add_entry").methods("POST"_method)([](const crow::request& req, crow::response& res){
        // Write entry to SQLite
        crow::query_string body_params = req.get_body_params();
        string req_uuid(body_params.get("uuid"));
        string req_description(body_params.get("description"));
        long long req_creation_time = static_cast<long long>(std::time(nullptr));
        long long req_deadline_time = stoll(body_params.get("deadline_time"));
        int req_priority = stoi(body_params.get("priority"));

        bool add_success = add_record_to_db(req_uuid, req_description, req_creation_time, req_deadline_time, req_priority);
        int response_code = add_success ? 200 : 500;
        res = crow::response(response_code);
        res.end();
    });

    // Delete entry
    CROW_ROUTE(app, "/delete_entry").methods("POST"_method)([](const crow::request& req, crow::response& res){
        // Drop entry from SQLite
        crow::query_string body_params = req.get_body_params();
        string req_uuid(body_params.get("uuid"));

        bool del_success = delete_record_from_db(req_uuid);
        int response_code = del_success ? 200 : 500;
        res = crow::response(response_code);
        res.end();
    });

    // Get all entries, sorted, in JSON
    CROW_ROUTE(app, "/get_all_entries")([](const crow::request& req, crow::response& res){
        // Select all entries from SQLite
        vector<Ticket> tickets_list = get_all_entries_from_db_sorted();
        vector<crow::json::wvalue> tickets_list_json;
        for(Ticket ticket: tickets_list) {
            tickets_list_json.push_back(ticket.get_as_json());
        }
        crow::json::wvalue tickets_list_output = tickets_list_json;

        res = crow::response(200, tickets_list_output);
        res.end();
    });

    app.port(18080).multithreaded().run();
}

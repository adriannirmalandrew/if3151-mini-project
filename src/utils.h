/*
 * Header file that defines database functionality
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <sqlite3.h>

#include "maxheap.h"
#include "ticket.h"

using std::cout, std::string, std::to_string, std::vector;

// Write data to SQLite
bool add_record_to_db(string uuid, string description, long long creation_time, long long deadline_time, int priority) {
    // Open SQLite, create file if does not exist
    sqlite3 *db_pointer = nullptr;
    int status = sqlite3_open("tickets.db", &db_pointer);
    if(db_pointer == nullptr) {
        return false;
    }
    // Create table if it doesn't exist
    string create_table_query = "create table if not exists tickets(\
        uuid string primary key, description string, creation_time integer, deadline_time integer, priority integer\
    );";
    sqlite3_exec(db_pointer, create_table_query.c_str(), 0, 0, nullptr);

    // Add record using prepared statement
    string add_record_query = "insert into tickets(uuid, description, creation_time, deadline_time, priority)\
        values(?, ?, ?, ?, ?);";
    sqlite3_stmt *add_record_query_stmt = nullptr;
    sqlite3_prepare_v2(db_pointer, add_record_query.c_str(), -1, &add_record_query_stmt, 0);
    // Add parameters
    sqlite3_bind_text(add_record_query_stmt, 1, uuid.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(add_record_query_stmt, 2, description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(add_record_query_stmt, 3, creation_time);
    sqlite3_bind_int64(add_record_query_stmt, 4, deadline_time);
    sqlite3_bind_int(add_record_query_stmt, 5, priority);
    // Finalize and execute
    sqlite3_step(add_record_query_stmt);
    sqlite3_finalize(add_record_query_stmt);

    // Close DB
    sqlite3_close(db_pointer);
    return true;
}

// Delete record with the given UUID from SQLite
bool delete_record_from_db(string uuid) {
    sqlite3 *db_pointer = nullptr;
    int status = sqlite3_open("tickets.db", &db_pointer);
    if(db_pointer == nullptr) {
        return false;
    }

    string delete_record_query = "delete from tickets where uuid = ?;";
    sqlite3_stmt *delete_record_query_stmt = nullptr;
    sqlite3_prepare_v2(db_pointer, delete_record_query.c_str(), -1, &delete_record_query_stmt, 0);
    sqlite3_bind_text(delete_record_query_stmt, 1, uuid.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(delete_record_query_stmt);
    sqlite3_finalize(delete_record_query_stmt);

    sqlite3_close(db_pointer);
    return true;
}

// Read all data entries from SQLite
vector<Ticket> get_all_entries_from_db() {
    // List of results
    vector<Ticket> results;

    sqlite3 *db_pointer = nullptr;
    int status = sqlite3_open("tickets.db", &db_pointer);
    if(db_pointer == nullptr) {
        return results; // Returns empty vector
    }

    string get_all_entries_query = "select * from tickets;";
    sqlite3_stmt *get_all_entries_query_stmt = nullptr;
    sqlite3_prepare_v2(db_pointer, get_all_entries_query.c_str(), -1, &get_all_entries_query_stmt, 0);

    while(sqlite3_step(get_all_entries_query_stmt) == SQLITE_ROW) {
        const unsigned char * res_uuid_raw = sqlite3_column_text(get_all_entries_query_stmt, 0);
        const unsigned char * res_description_raw = sqlite3_column_text(get_all_entries_query_stmt, 1);

        string res_uuid(reinterpret_cast<const char*>(res_uuid_raw));
        string res_description(reinterpret_cast<const char*>(res_description_raw));

        long long res_creation_time = sqlite3_column_int64(get_all_entries_query_stmt, 2);
        long long res_deadline_time = sqlite3_column_int64(get_all_entries_query_stmt, 3);
        int res_priority = sqlite3_column_int(get_all_entries_query_stmt, 4);

        results.push_back(
            Ticket(res_uuid, res_description, res_creation_time, res_deadline_time, res_priority)
        );
    }
    sqlite3_finalize(get_all_entries_query_stmt);

    sqlite3_close(db_pointer);
    return results;
}

// Return list of all Tickets, sorted using a maxheap
vector<Ticket> get_all_entries_from_db_sorted() {
    MaxHeap tickets_maxheap;

    vector<Ticket> all_db_entries = get_all_entries_from_db();
    for(Ticket ticket: all_db_entries) {
        tickets_maxheap.insert(ticket);
    }
    all_db_entries.clear();

    while(!tickets_maxheap.is_empty()) {
        all_db_entries.push_back(tickets_maxheap.get_top());
        tickets_maxheap.delete_max();
    }

    return all_db_entries;
}

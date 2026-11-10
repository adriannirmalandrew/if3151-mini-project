/*
 * Defines the Ticket class, which contains all its required helper functions
 */
#pragma once

#include "crow_all.h"
#include <string>
#include <ctime>
#include <cmath>

// #include <crow/json.h>
// #include <crow.h>

using std::string, std::exp;

class Ticket {
private:
    // Fields from DB
    string uuid; string description; long long creation_time; long long deadline_time; int priority;
    // Calculated fields
    int days_left; int score;

    void calculate_values() {
        // Compute days
        long long current_timestamp = static_cast<long long>(std::time(nullptr));
        this->days_left = (this->deadline_time - current_timestamp) / 86400;
        // Compute score with P + (10000 * e-D)
        this->score = this->priority + (100000 * exp(-1 * this->days_left));
    }

public:
    Ticket(string uuid, string description, long long creation_time, long long deadline_time, int priority) {
        this->uuid = uuid;
        this->description = description;
        this->creation_time = creation_time;
        this->deadline_time = deadline_time;
        this->priority = priority;

        // Populate all fields
        this->calculate_values();
    }

    // Convert to JSON using Crow
    crow::json::wvalue get_as_json() {
        crow::json::wvalue ticket_json;
        ticket_json["uuid"] = this->uuid;
        ticket_json["description"] = this->description;
        ticket_json["creation_time"] = this->creation_time;
        ticket_json["deadline_time"] = this->deadline_time;
        ticket_json["priority"] = this->priority;
        ticket_json["days_left"] = this->days_left;
        ticket_json["score"] = this->score;

        return ticket_json;
    }

    // Operators for MaxHeap
    bool operator==(const Ticket& other) const {
        return this->uuid == other.uuid;
    }

    // Getters
    string get_uuid() {
        return this->uuid;
    }

    string get_description() {
        return this->description;
    }

    long long get_creation_time() {
        return this->creation_time;
    }

    long long get_deadline_time() {
        return this->deadline_time;
    }

    int get_priority() {
        return this->priority;
    }

    int get_days_left() {
        return this->days_left;
    }

    int get_score() {
        return this->score;
    }
};

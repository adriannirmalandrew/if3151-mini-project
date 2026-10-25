/*
 * Defines the Ticket class, which contains all its required helper functions
 */
#pragma once

#include <string>
#include <ctime>
#include <cmath>

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
        this->score = this->priority + (10000 * exp(-1 * this->days_left));
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

/*
 * Defines the Ticket class, which contains all its required helper functions
 */
#pragma once

#include <string>

using std::string;

class Ticket {
private:
    // Fields from DB
    string uuid; string description; int creation_time; int deadline_time; int priority;
    // Calculated fields
    // TODO

    int calculate_values() {
        // TODO
        return -1;
    }

public:
    Ticket(string uuid, string description, int creation_time, int deadline_time, int priority) {
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

    int get_creation_time() {
        return this->creation_time;
    }

    int get_deadline_time() {
        return this->deadline_time;
    }

    int get_priority() {
        return this->priority;
    }
};

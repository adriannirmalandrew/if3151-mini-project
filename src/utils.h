/*
 * Header file that defines application functionality and required datatypes
 */

#include <string>

class Ticket {
private:
    std::string uuid;
    int priority_addend;
    int days_left;
    int final_score;

    int calculate_final_score() {
        // Calculate score using formula
        return -1;
    }

public:
    Ticket(std::string uuid, int priority_addend, int days_left) {
        this->uuid = uuid;
        this->priority_addend = priority_addend;
        this->days_left = days_left;
        this->final_score = calculate_final_score();
    }
};

void add_record_to_db() {
    // TODO
}

void delete_record_from_db() {
    // TODO
}

void get_all_entries_from_db() {
    // TODO
}

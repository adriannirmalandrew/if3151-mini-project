#include "ticket.h"
#include "utils.h"

#include <iostream>
#include <vector>

using std::cout, std::vector, std::endl;

int main() {
    // Create record
    long long current_timestamp = static_cast<long long>(std::time(nullptr));
    long long test_days = current_timestamp - (86400);

    add_record_to_db("test74", "test_desc", current_timestamp, test_days, 300);

    // Delete record
    delete_record_from_db("test");
    cout << "deleted" << endl;

    // Get all records
    vector<Ticket> records = get_all_entries_from_db();
    cout << "got records" << endl;
    for(Ticket ticket: records) {
        cout << ticket.get_uuid() << " " << ticket.get_description() << " " << ticket.get_days_left() << " " << ticket.get_score() << endl;
    }
}

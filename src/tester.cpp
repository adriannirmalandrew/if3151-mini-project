#include "ticket.h"
#include "utils.h"

#include <iostream>
#include <vector>

using std::cout, std::vector, std::endl;

int main() {
    // Create record
    add_record_to_db("test", "test_desc", 1001, 1002, 300);
    add_record_to_db("test67", "test_desc", 1067, 1069, 300);

    // Delete record
    delete_record_from_db("test");
    cout << "deleted" << endl;

    // Get all records
    vector<Ticket> records = get_all_entries_from_db();
    cout << "got records" << endl;
    for(Ticket ticket: records) {
        cout << ticket.get_uuid() << ticket.get_description() << endl;
    }
}

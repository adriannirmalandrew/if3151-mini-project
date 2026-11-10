# README for the IF3151 ADSA Mini Project

This project implements a priority queue for support tickets using a max heap.

## Description

This system is used to keep track of support tickets, scored on the basis of both their deadline date and assigned priority, then ordered in descending order, with the highest scores indicating the highest urgency.

## Implementation

This project is implemented entirely in C++, and relies on the following external libraries:
- Crow.cpp: C++ REST Library, included here in /src/crow_all.h
- SQLite: Used for data storage. Used system copy of sqlite3 libraries while building.

Other functionality is implemented and included as follows:
- /src/main.cpp: Main executable. Defines the crow.cpp web server and endpoints.
- /src/maxheap.h: Implements the MaxHeap class.
- /src/ticket.h: Implements the Ticket class.
- /src/utils.h: Implements database operations and related functionality for adding, deleting and retrieving an ordered list of records.

## Build Instructions (Linux)

1) Ensure that SQLite and SQLite libraries are installed on the system ("`sudo apt install sqlite3 libsqlite3-dev`" on Ubuntu)
2) Clone this repository.
3) Navigate to the cloned folder's root and run `make`.

Optionally, run "`make clean`" before step 3 to ensure a full rebuild.

## Execution Instructions (Linux)

The compiled executable exists as /bin/main, it should run as-is provided all dependencies are installed.

Please execute it using `./run.sh` in the project's root folder.

## Usage Instructions

Running the main executable launches a web server accessible at port 18080. Please ensure no other program is using the same port before running.

Navigating to http://localhost:18080/ should display the application's main page. This project only has a single webpage, at /html/index.html.

## Links

- Crow.cpp: [https://github.com/crowcpp/crow](https://github.com/crowcpp/crow)

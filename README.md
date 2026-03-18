# Restaurant Waitlist Management System

## Overview

This project is a Data Structures-based application that simulates a restaurant waitlist system. It efficiently manages customer queues and table allocation using appropriate data structures.

The system allows adding parties to a waitlist, seating them based on table availability, prioritizing VIP customers, and managing table status dynamically.



## Problem Statement

In restaurants, managing waiting customers and assigning tables efficiently is crucial. This project aims to:

* Maintain a waitlist of customers
* Assign tables based on availability and capacity
* Handle priority customers (VIPs)
* Provide operations like cancellation, wait time estimation, and table management



## Data Structures Used

### 1. Queue (Linked List)

* Used to maintain the waitlist of parties
* Follows FIFO (First In First Out)
* Each node represents a party with:

  * Name
  * Size

Implementation:
Defined using `struct Party` and managed through `Waitlist` 



### 2. Binary Search Tree (BST)

* Used to store and manage restaurant tables
* Tables are organized based on capacity
* Helps in efficiently finding a suitable table

Implementation:
Defined using `struct Table` 



## Features

* Add a party to waitlist
* Seat next party based on table availability
* View current waitlist
* Estimate total wait time
* Cancel reservation
* Prioritize VIP customers
* View all tables (in-order traversal of BST)
* Free a table by ID

Menu-driven interface implemented in main program 



## Working

1. Tables are inserted into a BST based on capacity
2. Parties are added to a queue (waitlist)
3. When seating:

   * The system finds a suitable table using BST traversal
   * The first party in queue is assigned
4. VIP prioritization moves selected party forward in queue
5. Wait time is estimated based on party sizes

Core logic implemented in 



## Algorithms

### Queue Operations

* Enqueue: Add party to rear
* Dequeue: Remove party from front
* Traversal: Display waitlist

### BST Operations

* Insertion: Based on table capacity
* Search: Find suitable table for a party
* Traversal: In-order to display tables



## Time Complexity

| Operation                     | Complexity       |
| ----------------------------- | ---------------- |
| Add Party (Enqueue)           | O(1)             |
| Seat Party (Search + Dequeue) | O(n)             |
| View Waitlist                 | O(n)             |
| Cancel Reservation            | O(n)             |
| VIP Prioritization            | O(n)             |
| Insert Table (BST)            | O(log n) average |
| Find Suitable Table           | O(n)             |

---

## Project Structure

```id="dsa1"
DSA Mini Project/
│
├── main.c
├── restaurant.c
├── restaurant.h
└── README.md
```



## Compilation and Execution

### Compile:

```id="dsa2"
gcc main.c restaurant.c -o restaurant
```

### Run:

```id="dsa3"
./restaurant
```

(On Windows: `restaurant.exe`)

---

## Sample Operations

* Add Party → Inserts into queue
* Seat Next Party → Assigns table if available
* Estimate Wait Time → Based on total party sizes
* VIP Priority → Moves selected party ahead

---

## Future Enhancements

* Use Priority Queue instead of manual VIP handling
* Graph-based table allocation for better optimization
* GUI-based interface
* Database integration for persistence

---

## Author

Yash Raghavendra
GitHub: https://github.com/YASH-RAGHAVENDRA-A

---

## Conclusion

This project demonstrates practical use of fundamental data structures like Queue and Binary Search Tree in solving a real-world problem efficiently.

# general Notes

---

# Notes on choosing the DS

# DS Complexity

- Stack:
  - Insertion (push): O(1)
  - Removal (pop): O(1)
  - Accessing top element (peek): O(1)
  - Searching for an element: O(n)
- Queue:
  - Insertion (enqueue): O(1)
  - Removal (dequeue): O(1)
  - Accessing front element: O(1)
  - Searching for an element: O(n)
- Priority Queue:
  - Insertion: O(log n)
  - Removal: O(log n)
  - Accessing highest priority element: O(1)
  - Searching for an element: O(n)
- Tree:
  - Insertion: O(log n) - O(n) (depending on the tree structure and balancing)
  - Removal: O(log n) - O(n) (depending on the tree structure and balancing)
  - Searching for an element: O(log n) - O(n) (depending on the tree structure and balancing)
- Binary Search Tree (BST):
  - Insertion: O(log n) - O(n) (depending on the balance of the tree)
  - Removal: O(log n) - O(n) (depending on the balance of the tree)
  - Searching for an element: O(log n) - O(n) (depending on the balance of the tree)
- List:

  - Insertion (at end): O(1)
  - Removal (at end): O(1)
  - Insertion (at beginning): O(1)
  - Removal (at beginning): O(1)
  - Accessing an element (by index): O(n)
  - Searching for an element: O(n)

- _stacks and queues have fast insertion and removal times, but slower search times compared to other data structures_
- _priority queues offer fast access to the highest priority element, but insertion and removal times are slower compared to stacks and queues_
- _Trees and BSTs provide fast searching times, but their insertion and removal times depend on the structure of the tree and its balancing._
- _Lists offer fast insertion and removal times at both the beginning and the end, but searching for an element is slower compared to other data structures_

## process holding ds

- New => ( Note that processes arrive sorted by arrival time)
  => queue
- RUN => should be only one Item per processor
- I/O => must be only one item
- TRM => (output is sorted ascending by trm time)
  => queue
- BLK => (FIFO Behavior)
  => Queue
- FCFS RDY => (FIFO behavior)
  => List (when IO and come back to rdy que with different wt) 
- SJF RDY => (shortest remaining time first)
  => pQueue (minHeap)
- RR RDY => Circular loop Behavior
  => Queue || circular queue

### processor holding ds

- Processors => list ADT

---

# phase 1 Specific Notes

## bullet lists

- all data members of classes:
  - Entities:
    - Process Class
    - Processor (Abstract) Class
      - FCFS
      - SJF
      - RR
  - Controllers
    - Schedular ( Maestro / Singleton )
      - has these lists:
        - NEW
        - BLK
        - TRM
        - Processors
    - UI Class
    ***
    - will probably need:
      - Clock Class
      - Simulation Class
- All Data Structures for lists implementation
- File Loading Function
- Simple Simulator Function
- when many processes ask for IO in the same time take the shortest IO time first
- _No Actual Scheduling is required at phase 1_


* Ask about FCFS behavior
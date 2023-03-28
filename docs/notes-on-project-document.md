# general Notes


---
# Notes on choosing the DS

### process holding ds
* New         => ( Note that processes arrive sorted by arrival time) 
  => queue
* RUN         => should be only one Item per processor
* I/O         => must be only one item 
* TRM         => (output is sorted ascending by trm time)
* BLK         => (FIFO Behavior)
  => Queue 
* FCFS RDY    => (FIFO behavior)
  => Queue 
* SJF RDY     => (shortest remaining time first)
  => pQueue 
* RR RDY      => Circular loop Behavior

### processor holding ds
* Processors  =>

---
# phase 1 Specific Notes

## bullet lists
* all data members of classes:
  * Entities:
    * Process Class
    * Processor (Abstract) Class
      * FCFS
      * SJF
      * RR
  * Controllers
    * Schedular ( Maestro / Singleton )
      * has these lists:
        * NEW
        * BLK
        * TRM
        * Processors
    * UI Class
    ------------
    * will probably need:
      * Clock Class
      * Simulation Class
* All Data Structures for lists implementation
* File Loading Function
* Simple Simulator Function

* *No Actual Scheduling is required at phase 1*
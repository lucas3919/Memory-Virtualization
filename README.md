# Virtual Memory Simulation
<br>

# Description:
This program simulates a Virtual Memory of an Operating System using the FIFO (First In First Out) method or LRU (Least Recently Used) method. We have one main file and 5 headers on this application.
<br>

## main.c
This is the main file where every function is being called and the code is executing the given commands, for better organization it was decided to make the files this way.
<br>

## structs.h
This is where all the structs used throughout the code reside.
<br>

## functions.h
This is where all the functions signatures are located for better organization. Besides that on this file we have the functions used to load & organize the page table and the functions used to create the physical addresses.
<br>

## fifo.h
This is where all the functions regarding the FIFO (First In First Out) method are situated.
<br>

## lru.h
This is where all the functions regarding the LRU (Least Recently Used) method are situated.
<br>

## save_file
This header is where all the functions used to save the physical addresses, the amount of page faults and translated addresses are situated. this is where we create a file called "correct.txt" and print the information on it.

# How it works:
firtly compile the program using your terminal on the main.c application folder using the command "make", after that the program will create a binary file called "vm", for the application to work you need to pass 4 arguments on your terminal in this respective order: 
<br>
<br>
1st argument is the binary file;
<br>
2nd argument is the ".txt" file used for the logic addresses;
<br>
3rd argument is the method you  wish to use when loading the page table;
<br>
4th argument is the method you wish to use to load the TLB;
<br>
<br>
Ex:
```
./vm addresses.txt fifo lru
```
<br>
<br>

# Usage:

### 1.Compile
``` bash
$ make
```

### 2.Cleaning
``` bash
$ make clean
```
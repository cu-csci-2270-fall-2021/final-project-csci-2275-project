# CSCI 2275 – Data Structures - Final Project
### By Kieran Stone and Elijah Smith


## Initialization

    Used to set up the reposotory when first running the program. Allows a choice of hash table size. 
    Creates the hash table and the .minigit folder when run.
  
  \***Must be run first**\*

## Destructor
    Used to destroy all the data structures and free up memory.
    Iterates through the doubly linked list and singly linked lists destroying each node without leaving any unreachable data in memory.
    Also deletes the hash table.
  
## Add

    Adds a file to the singly linked list to be commited. Files must be added one at a time.
    Files are not saved to the .minigit directory in add.
    The version number is checked to make sure a file is not added to the singly linked list twice.
  
## Remove

    Removes the specified file singly linked list so it is not commited.
    Deletes node to free memory.
  
## Commit

    Finalized the commit, saving the current version of all added files to the .minigit directory. 
    A unique commit message must be specified, that may be up to 3 words long, and can be used to find the commit later.
    Also checks whether added files have been modified since the last commit, and only copies them and increments their version number if they have been modified.
  
## Checkout

    Returns files to the version of the specified commit number. 
    Copies files of the correct version number for whichever commit is selected over the main working files.
  
  \***Cannot be Reversed**\*
  
## Search

    Finds all commit numbers from commits who's message contains the specified word. Only 1 word may be used to search.
    Searches the hash table and returns a list of commit numbers.

## Hash Function

    Takes a string as input and adds all ASCII values of the characters together, then runs a modulo operation with the table size to return an index in the table.

## Hash Table Insert

    Inserts the specified string into the hash table at the index specified by the hash function.
    If another values exists at that index, it creates a new node in the SLL of entries.
    Also records what commit number the string is associated with, and if a string has already been added, it adds the new commit number to that strings data.

## Hash Table Search

    Searches the hash table at the index given by the hash function for the string inputted.
    If the string is found in the table, all commit numbers associated with it are returned.
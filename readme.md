# CSCI 2275 – Data Structures - Final Project
### By Kieran Stone and Elijah Smith


## Initialization

  Used to set up the reposotory when first running the program. Allows a choice of hash table size. 
Creates the hash table and the .minigit folder when run.
  
  \***Must be run first**\*
  
## Add

  Adds a file to the current commit. Files must be added one at a time.
When added, files are put in the SLL of files to be committed, but no files are copied or saved.
  
## Remove

 Removes the specified file from the current commit. Deletes the files entry in the SLL.
  
## Commit

  Finalized the commit, saving the current version of all added files. A unique commit message must be specified, that may be up to 3 words long, and can be used to find the commit later.
Also checks whether added files have been modified since the last commit, and only copies them and increments their version number if they have been modified.
  
## Checkout

  Returns files to the version of the specified commit number. 
Copies files of the correct version number for whichever commit is selected over the main working files.
  
  \***Cannot be Reversed**\*
  
## Search

   Finds all commit numbers from commits who's message contains the specified word. Only 1 word may be used to search.
Searches the hash table and returns a list of commit numbers
  

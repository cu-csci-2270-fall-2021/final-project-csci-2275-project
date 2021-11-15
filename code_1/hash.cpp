// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

HashNode* HashTable::createNode(string key, HashNode* next)
{
    HashNode* nw = NULL;
    return nw;
}

//KIERAN
HashTable::HashTable(int bsize)
{
   HashNode* arr [bsize];
   table = arr;
}

//KIERAN
//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    int sum = 0;
    int index = 0;
    for(int i=0; i < s.length(); i++)
    {
        sum += s[i];
    }
    return sum % tableSize;
}

//KIERAN
// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
   HashNode* temp = table[hashFunction(key)];
   while(temp->key != key && temp != NULL){
       temp = temp->next;
   }
   return temp;
}

//ELIJAH
//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    
    //TODO
    return false;
}


// function to display hash table //
/* assume the table size is 5. For each bucket it will show the 
** the string key and the commit number (separated by comma) within parenthesis
** e.g. the key is science and commit numbers are 1 and 4. The key science
** is hashed to position 0. So the print format will be-

0|| science(1,4,)
1|| 
2|| 
3|| 
4|| difficult(3,)-->fun(2,)-->computer(0,)

*/
//ELIJAH
void HashTable::printTable()
{

 }

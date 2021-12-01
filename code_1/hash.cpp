// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

HashNode* HashTable::createNode(string key, HashNode* next)
{
    HashNode* nw = NULL;
    return nw;
}

HashTable::HashTable(int bsize)
{
    tableSize = bsize;
    table = new HashNode* [bsize];
    for(int i = 0; i<bsize; i++){
        table[i] = NULL;
    }
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    int sum = 0;
    int index = 0;
    for(int i=0; i < (int)(s.length()); i++)
    {
        sum += s[i];
    }
    index = (int)(sum % tableSize);
    return index;
}

// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
   HashNode* temp = table[hashFunction(key)];
   if(temp == NULL){
       return temp;
   }
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
    // int index = hashFunction(key);
    // if(table[index] != NULL && table[index]->key == key){
    //     table[index]->commitNums.push_back(cNum);
    //     return true;
    // }
    // HashNode *newNode = new HashNode;
    // newNode->next = NULL;
    // newNode->key = key;
    // newNode->commitNums.push_back(cNum);
    // if(table[index] == NULL){
    //     table[index] = newNode;
    //     return true;
    // } else {
    //     newNode->next = table[index];
    //     table[index] = newNode;
    //     return true;
    // }
    // return false;
    int index = hashFunction(key);
    HashNode* temp = table[index];
    if(temp == NULL){
        temp = new HashNode;
        temp->key = key;
        temp->next = NULL;
        temp->commitNums.push_back(cNum);
        table[index] = temp;
        return true;
    }
    else{
        while(temp != NULL){
            if(temp->key == key){
                temp->commitNums.push_back(cNum);
                return true;
            }
            temp = temp->next;
        }
        temp = new HashNode;
        temp->key = key;
        temp->next = table[index];
        temp->commitNums.push_back(cNum);
        table[index] = temp;
        return true;
    }
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
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";
        HashNode* temp = table[i];
        while(temp){
            cout << temp->key;
            if(temp->commitNums.size()>0){
                cout << "(";
                for(int i = 0; i<(int)(temp->commitNums.size()); i++){
                    cout << temp->commitNums[i] << ",";
                }
                cout << ")";
            }
            if(temp->next != NULL){
                cout << "-->";
            }
            temp = temp->next;
        }
        cout << endl;
    }
 }


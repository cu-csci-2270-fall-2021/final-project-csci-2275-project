#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

MiniGit::MiniGit() {
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
}

//ELIJAH
MiniGit::~MiniGit() {   
    // Any postprocessing that may be required

}

//ELIJAH
void MiniGit::init(int hashtablesize) {
   
}

//ELIJAH
void MiniGit::add(string fileName) {
   
}

//KIERAN
void MiniGit::rm(string fileName) {
    BranchNode* temp = commitHead;
    while(temp->next != NULL){
        temp = temp->next;
    }
    FileNode* sll = temp->fileHead;
    FileNode* prev = sll;
    while(sll->name != fileName && sll->next != NULL){
        prev = sll;
        sll = sll->next;
    }
    if(sll->next != NULL){
        prev->next = sll->next;
        delete sll;
    }
}


void MiniGit::printSearchTable()
{
    ht->printTable();
}

//KIERAN
void MiniGit::search(string key)
{
    HashNode* arr = ht[ht->hashFunction(key)]->*table;
    while(arr->next != NULL){
        cout << arr->commitId << endl;
        arr = arr->next;
    }
}

//KIERAN
string MiniGit::commit(string msg) {
    return " "; //should return the commitID of the commited DLL node
}

//ELIJAH
void MiniGit::checkout(string commitID) {
   
}
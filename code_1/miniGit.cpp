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
   ht = new HashTable(hashtablesize);
   commitHead = new BranchNode;
}

//ELIJAH
void MiniGit::add(string fileName) {
    BranchNode* crawler = commitHead;
    while(crawler->next != NULL){
        crawler = crawler->next;
    }
    FileNode* lastFile = crawler->fileHead;
    FileNode* newNode = new FileNode;
    newNode->name = fileName;
    if(lastFile == NULL){
        crawler->fileHead = newNode;
    }
    while(lastFile->next != NULL){
        lastFile = lastFile->next;
    }
    lastFile->next = newNode;
    
    string newFileName = fileName;
    newFileName += crawler->commitID;
    fs::copy_file(fileName,  ".minigit/" + newFileName);
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
    vector<int> arr = ht->searchItem(key)->commitNums;
    BranchNode* temp = commitHead;
    for(int i = 0; i<arr.size(); i++){
        cout << "Commit ID: " << temp->commitID << endl;
    }
}

//KIERAN
string MiniGit::commit(string msg) {
    FileNode* temp = commitHead->fileHead;
        while(temp->next != NULL){
            for(int i = 0; i<.minigit.size(); i++){
                if(temp->version = .minigit[i]){
                    
                }
            }
        }
    return " "; //should return the commitID of the commited DLL node
}

//ELIJAH
void MiniGit::checkout(string commitID) {
   
}
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
    newFileName += ".txt";
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
    cout << "Commit numbers for " << key << ": ";
    for(int i = 0; i<(int)(arr.size()); i++){
        cout << temp->commitID << ",";
    }
}

//KIERAN
string MiniGit::commit(string msg) {
    BranchNode* curr = commitHead;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->commitMessage = msg;
    FileNode* file = curr->fileHead;
    while(file->next != NULL){
        string path = ".minigit";
        vector<string> file_arr;
        int i = 0;
        for (const auto & entry : fs::directory_iterator(path)){
            file_arr[i] = entry.path();
            i++;
        }
        for(int i = 0; i<(int)(file_arr.size()); i++){
            if(file->version == stoi(file_arr[i].substr(3,2))){
                string gitFile = ".minigit/" + file->name;
                if(file->name.compare(gitFile) != 0){
                    string newFileName = file->name.substr(0,2) + "_" + to_string(file->version+1) + ".txt";
                    ofstream outfile(newFileName);
                    fs::copy_file(file->name, newFileName);
                    file->version = file->version+1;
                }
            }
            else{
                string newFileName = file->name.substr(0,2) + "_" + to_string(file->version+1) + ".txt";
                ofstream outfile(newFileName);
                fs::copy_file(file->name, newFileName);
                file->version = file->version+1;
            }
        }
    }
    for(int i = 0; i<(int)(msg.size()); i++){
        if(msg.at(i) == ' ' && i != 0){
            ht->insertItem(msg.substr(0,i-1), curr->commitID);
        }
    }
    BranchNode * newN = new BranchNode();
    newN->commitID = curr->commitID+1;
    newN->commitMessage = "";
    newN->next = NULL;
    newN->previous = curr;
    curr->next = newN;
    newN->fileHead = Duplicate(curr->fileHead);
    commits++;
    return curr->commitID + " "; //should return the commitID of the commited DLL node
}

FileNode* MiniGit::Duplicate(FileNode* list){
    if(list == NULL){
        return list;
    }
    FileNode* temp = new FileNode();
    temp->name = list->name;
    temp->version = list->version;
    temp->next = Duplicate(list->next);
    return temp;
}

//ELIJAH
void MiniGit::checkout(string commitID) {
   
}
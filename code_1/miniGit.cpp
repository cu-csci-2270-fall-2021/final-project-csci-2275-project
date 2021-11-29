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
   commitHead->commitID = 0;
   commitHead->commitMessage = "";
   commitHead->fileHead = NULL;
   commitHead->previous = NULL;
   commitHead->next = NULL;
}

//ELIJAH
void MiniGit::add(string fileName) {
    BranchNode* crawler = commitHead;
    while(crawler->next != NULL){
        crawler = crawler->next;
    }
    FileNode* lastFile = crawler->fileHead;
    FileNode* newNode = new FileNode;
    int pos = fileName.find(".");
    newNode->name = fileName.substr(0, pos) + "_00" + ".txt";
    newNode->version = 0;
    newNode->next = NULL;
    if(lastFile == NULL){
        crawler->fileHead = newNode;
    } else {
        while(lastFile->next != NULL){
            pos = lastFile->name.find("_");
            string lFileName = lastFile->name.substr(0,pos) + ".txt";
            if(lFileName == fileName){
                lastFile->version++;
                cout << "File has already been added. Version number updated" << endl;
                goto label;
            }
            lastFile = lastFile->next;
        }
        pos = lastFile->name.find("_");
        string lFileName = lastFile->name.substr(0,pos) + ".txt";
        if(lFileName == fileName){
            lastFile->version++;
            cout << "File has already been added. Version number updated" << endl;
        } else lastFile->next = newNode;
    }
    label:
    return;
}

//KIERAN
void MiniGit::rm(string fileName) {
    BranchNode* dll = commitHead;
    while(dll->next != NULL){
        dll = dll->next;
    }
    FileNode* temp = dll->fileHead;
    FileNode* prev = NULL;
    int pos = temp->name.find("_");
    string tName = temp->name.substr(0,pos) + ".txt";
    if (temp != NULL && tName == fileName){
        dll->fileHead = temp->next; 
        delete temp;            
        return;
    }
    else{
        while (temp != NULL && tName != fileName){
            prev = temp;
            temp = temp->next;
            pos = temp->name.find("_");
            tName = temp->name.substr(0,pos) + ".txt";
        }
        if (temp == NULL){
            return;
        }
        prev->next = temp->next;
        delete temp;
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

//JUST FOR TESTING
//REMOVE BEFORE FINAL COMMIT
void MiniGit::printLastSLL(){
    BranchNode* temp = commitHead;
    while(temp->next != NULL){
        temp = temp->next;
    }
    FileNode* SLL = temp->fileHead;
    if(SLL == NULL){
        cout << "NULL" << endl;
    }
    while(SLL != NULL){
        cout << SLL->name << endl;
        SLL = SLL->next;
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
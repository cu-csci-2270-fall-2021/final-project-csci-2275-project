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
    BranchNode* crawler = commitHead;
    while(crawler != NULL){
        FileNode* node = crawler->fileHead;
        while(node != NULL){
            FileNode* temp = node;
            node = node->next;
            delete temp;
        }
        BranchNode* tempCrawl = crawler;
        crawler = crawler->next;
        delete tempCrawl;
    }
    delete ht;
    fs::remove_all(".minigit");
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
    newNode->name = fileName.substr(0, pos) + ".txt";
    newNode->version = 0;
    newNode->next = NULL;
    if(lastFile == NULL){
        crawler->fileHead = newNode;
    } else {
        while(lastFile->next != NULL){
            pos = lastFile->name.find(".");
            string lFileName = lastFile->name.substr(0,pos) + ".txt";
            if(lFileName == fileName){
                lastFile->version++;
                cout << "File has already been added. Version number updated" << endl;
                goto label;
            }
            lastFile = lastFile->next;
        }
        pos = lastFile->name.find(".");
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
    int pos = temp->name.find(".");
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
            pos = temp->name.find(".");
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
    HashNode* searchNode = ht->searchItem(key);
    if(searchNode == NULL){
        cout << "key not found" << endl;
        return;
    }
    vector<int> arr = searchNode->commitNums;
    cout << "Commit numbers for " << key << ": ";
    for(int i = 0; i<(int)(arr.size()); i++){
        cout << arr[i] << ",";
    }
    cout << endl;
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

//JUST FOR TESTING
//REMOVE BEFORE FINAL COMMIT
void MiniGit::printDLL(){
    BranchNode* temp = commitHead;
    while(temp != NULL){
        cout << "CommitID: " << temp->commitID << " Commit msg: " << temp->commitMessage << " SLL: ";
        FileNode* curr = temp->fileHead;
        while(curr != NULL){
            cout << curr->name << "-->";
            curr = curr->next;
        }
        cout << endl;
        temp = temp->next;
    }
}

bool MiniGit::searchForCommitMSG(string msg){
    BranchNode* temp = commitHead;
    while(temp != NULL){
        if(temp->commitMessage == msg){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//KIERAN
string MiniGit::commit(string msg) {
    bool modified = false;
    BranchNode* curr = commitHead;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->commitMessage = msg;
    FileNode* file = curr->fileHead;
    while(file != NULL){
        bool found = false;
        fs::current_path(fs::path(".minigit"));
        int pos = file->name.find(".");
        string fileName = "";
        if(file->version>10){
            fileName = file->name.substr(0,pos) + "_" + to_string(file->version-1) + ".txt";
        }
        else{
            fileName =file->name.substr(0,pos) + "_0" + to_string(file->version-1) + ".txt";
        }
        if(fs::exists(fileName)){
            found = true;
        }
        fs::current_path(fs::path("../"));
        if(found){
            int pos = file->name.find(".");
            string gitFile = "";
            if(file->version>10){
                gitFile = ".minigit/" + file->name.substr(0,pos) + "_" + to_string(file->version-1) + ".txt";
            }
            else{
                gitFile = ".minigit/" + file->name.substr(0,pos) + "_0" + to_string(file->version-1) + ".txt";
            }
            bool same = true;
            ifstream f1 (file->name);
            ifstream f2 (gitFile);
            string line1;
            string line2;
            int count1 = 0;
            int count2 = 0;
            while(getline(f1,line1)){
                count1++;
            }
            while(getline(f2,line2)){
                count2++;
            }
            if(count1 != count2){
                same = false;
            }
            f1.close();
            f2.close();
            ifstream f3 (file->name);
            ifstream f4 (gitFile);
            if(same){
                while(getline(f4,line2)){
                    getline(f3, line1);
                    if(line2 != line1){
                        same = false;
                        break;
                    }
                }
            }
            if(!same){
                int pos = file->name.find(".");
                string title = file->name.substr(0,pos);
                string newFileName = "";
                if(file->version<10){
                    newFileName = title + "_0" + to_string(file->version) + ".txt";
                }
                else{
                    newFileName = title + "_" + to_string(file->version) + ".txt";
                }
                modified = true;
                ifstream src (file->name);
                ofstream dest(".minigit/" + newFileName);
                string line;
                int lineCount = 0;
                int curr = 0;
                while(getline(src, line)){
                    lineCount++;
                }
                src.close();
                ifstream src1 (file->name);
                while(getline(src1, line)){
                    if(curr<lineCount-1){
                        dest << line << endl;
                    }
                    else{
                        dest << line;
                    }
                    curr++;
                }
                src.close();
                dest.close();
            } else file->version--;
        }
        else{
            int pos = file->name.find(".");
            modified = true;
            string newFileName = file->name.substr(0,pos) + "_00.txt";
            ifstream src (file->name);
            ofstream dest(".minigit/" + newFileName);
            int lineCount = 0;
            int curr = 0;
            string line;
            while(getline(src, line)){
                lineCount++;
            }
            src.close();
            ifstream src1 (file->name);
            while(getline(src1, line)){
                if(curr<lineCount-1){
                    dest << line << endl;
                }
                else{
                    dest << line;
                }
                curr++;
            }
            src1.close();
            dest.close();
            
        }
        file = file->next;
    }
    string word = "";
    for (auto x : msg) {
        if (x == ' ') {
            ht->insertItem(word, curr->commitID);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    ht->insertItem(word, curr->commitID);
    BranchNode * newN = new BranchNode();
    newN->commitID = curr->commitID+1;
    newN->commitMessage = "";
    newN->next = NULL;
    newN->previous = curr;
    curr->next = newN;
    newN->fileHead = Duplicate(curr->fileHead);
    commits++;
    if(modified){
        cout << "Commit successful: ";
        cout << curr->commitID;
    }
    else{
        cout << "Commit successful. No file has been modified. Commit ID: " << curr->commitID;
    }
    return curr->commitID + ""; //should return the commitID of the commited DLL node
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
   BranchNode* crawler = commitHead;
   while(crawler != NULL){
       if(crawler->commitID == stoi(commitID)){
           FileNode* node = crawler->fileHead;
           while(node != NULL){
                string fileVersionName;
                int pos = node->name.find(".");
                string title = node->name.substr(0,pos);
                if(node->version+1<10){
                    fileVersionName = title + "_0" + to_string(node->version) + ".txt";
                }
                else{
                    fileVersionName = title + "_" + to_string(node->version) + ".txt";
                }
                // string fileLoc = ".minigit/" + fileVersionName;
                // string fileDest =  node->name;
                // fs::copy(fileLoc, fileDest, fs::copy_options::overwrite_existing);
                ifstream src (".minigit/" + fileVersionName);
                ofstream dest(node->name);
                int lineCount = 0;
                int curr = 0;
                string line;
                while(getline(src, line)){
                    lineCount++;
                }
                src.close();
                ifstream src1 (".minigit/" + fileVersionName);
                while(getline(src1, line)){
                    if(curr<lineCount-1){
                        dest << line << endl;
                    }
                    else{
                        dest << line;
                    }
                    curr++;
                }
                src1.close();
                dest.close();
                node = node->next;
           }
           return;
       }
       crawler = crawler->next;
   }
   cout << "version not found" << endl;
}
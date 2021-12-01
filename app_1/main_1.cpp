#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. init " << endl;
    cout << " 2. add " << endl;
    cout << " 3. rm " << endl;
    cout << " 4. commit " << endl;
    cout << " 5. checkout" << endl;
    cout << " 6. search" << endl;
    cout << " 7. quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
int main(int argc, char* argv[]) {
    MiniGit* repo = new MiniGit();
    // repo->init(5);
    // cout << "adding f0" << endl;
    // repo->add("f0.txt");
    // repo->printDLL();
    // cout << "adding f1" << endl;
    // repo->add("f1.txt");
    // repo->printDLL();
    // cout << "Commiting" << endl;
    // repo->commit("one");
    // repo->printDLL();
    // cout << "adding f0" << endl;
    // repo->add("f0.txt");
    // repo->printDLL();
    // cout << "adding f1" << endl;
    // repo->add("f1.txt");
    // repo->printDLL();
    // cout << "Commiting" << endl;
    // repo->commit("two");
    string input = "";
    while(input != "7"){
        displayMenu();
        getline(cin, input);
        if(input == "1"){
            repo->init(5);
        }
        if(input == "2"){
            int count = 0;
            cout << "Enter the filename to be added: ";
            string filename = "";
            getline(cin, filename);
            bool found = false;
            while(!found){
                if(count != 0){
                    cout << "File not in current directory, try again: ";
                    getline(cin, filename);
                }
                count++;
                string path = fs::current_path();
                for(const auto & entry : fs::directory_iterator(path)){
                    string filePath = entry.path();
                    filePath = filePath.substr(path.length()+1);
                    if(filename == filePath){
                        found = true;
                    }
                }
            }
            repo->add(filename);
            //repo->printLastSLL();
        }
        if(input == "3"){
            int count = 0;
            cout << "Enter the filename to be removed: ";
            string filename = "";
            getline(cin, filename);
            bool found = false;
            while(!found){
                if(count != 0){
                    cout << "File not in current directory, try again: ";
                    getline(cin, filename);
                }
                count++;
                string path = fs::current_path();
                for(const auto & entry : fs::directory_iterator(path)){
                    string filePath = entry.path();
                    filePath = filePath.substr(path.length()+1);
                     if(filename == filePath){
                        found = true;
                    }
                }
            }
            repo->rm(filename);
            //repo->printLastSLL();
        }
        if(input == "4"){
            cout << "Enter unique commit message (at most 3 space separated words): ";
            string commitMsg = "";
            getline(cin, commitMsg);
            int space = 0;
            for(int i = 0; i<(int)(commitMsg.length()); i++){
                if(commitMsg.at(i) == ' '){
                    space++;
                }
            }
            while(space>2){
                cout << "commit message should be at most 3 words long" << endl;
                cout << "Enter unique commit message (at most 3 space separated words): ";
                commitMsg = "";
                getline(cin, commitMsg);
                space = 0;
                for(int i = 0; i<(int)(commitMsg.length()); i++){
                    if(commitMsg.at(i) == ' '){
                        space++;
                    }
                }
            }
            while(repo->searchForCommitMSG(commitMsg)){
                cout << "That is a duplicate commit message. Try again: ";
                commitMsg = "";
                getline(cin, commitMsg);
            }
            cout << repo->commit(commitMsg) << endl;
            //repo->printDLL();
            repo->printSearchTable();
        }
        if(input == "5"){
            cout << "Enter the commit number: ";
            string commitNum = "";
            getline(cin, commitNum);
            cout << "Are you sure you want to do this? Warning, you will lose all local changes. Y or N?";
            string confirm = "";
            getline(cin, confirm);
            if(confirm == "Y" || confirm == "y"){
                repo->checkout(commitNum);
            }
        }
        if(input == "6"){
            cout << "Enter the search key: ";
            string key = "";
            getline(cin, key);
            repo->search(key);
            cout << endl;
        }

    }
    delete repo;
    return 0;
}
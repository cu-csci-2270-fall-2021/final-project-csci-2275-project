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
    string s = "error";
    int sum = 0;
    for(int i = 0; i<(int)(s.length()); i++){
        sum += s[i];
    }
    cout << sum%7 << endl;
    string input = "";
    MiniGit* repo = new MiniGit();
    while(input != "7"){
        displayMenu();
        cin >> input;
        if(input == "1"){
            repo->init(5);
        }
        if(input == "2"){
            int count = 0;
            cout << "Enter the filename to be added: ";
            string filename = "";
            cin >> filename;
            bool filePres = false;
            while(!filePres){
                if(count != 0){
                    cout << "File not in current directory, try again: ";
                    cin >> filename;
                }
                count++;
                filePres = true;
                string path = "../test";
                for(const auto & entry : fs::directory_iterator(path)){
                    string filePath = entry.path();
                    filePath = filePath.substr(path.length()+1);
                    for(int i = 0; i<int(filename.length()); i++){
                        if(int(filePath[i]) != int(filename[i])){
                            filePres = false;
                        }
                    }
                }
            }
            repo->add(filename);
            repo->printLastSLL();
        }
        if(input == "3"){
            
        }
        if(input == "4"){
            cout << "Enter unique commit message (at most 3 space separated words): ";
            string commitMsg = "";
            cin >> commitMsg;
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
                cin >> commitMsg;
                space = 0;
                for(int i = 0; i<(int)(commitMsg.length()); i++){
                    if(commitMsg.at(i) == ' '){
                        space++;
                    }
                }
            }
            cout << commitMsg << endl << "commit successful: " << repo->commit(commitMsg);
            repo->printSearchTable();
        }
        if(input == "5"){
            cout << "Enter the commit number: ";
            string commitNum = "";
            cin >> commitNum;
            repo->checkout(commitNum);
        }
        if(input == "6"){
            cout << "Enter the search key: ";
            string key = "";
            cin >> key;
            repo->search(key);
        }

    }
    return 0;
}
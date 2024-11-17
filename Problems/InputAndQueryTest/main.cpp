#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>

#define DEBUG 1;
using namespace std;
namespace fs = std::filesystem;

const int MAX_LOOP = 1e4;
const char* DIRECTORY_PATH = "./InputQuerys";
int LOOP_CNT = 0;

void InitLoop() { LOOP_CNT = 0; }

/*
leaks Report Version: 3.0
Process 5114: 187 nodes malloced for 15 KB
Process 5114: 0 leaks for 0 total leaked bytes.
*/
shared_ptr<vector<string>> RetrieveDirectoryFiles() {
    shared_ptr<vector<string>> querys(new vector<string>());
    const fs::path PATH(DIRECTORY_PATH);

    cout << boolalpha << "InputQuery exists : "<< fs::exists(PATH) <<'\n';
    cout << boolalpha << "InputQuery is_regular_file : "<< fs::is_regular_file(PATH) <<'\n';
    cout << boolalpha << "InputQuery is_directory : "<< fs::is_directory(PATH) <<'\n';

    if(fs::exists(PATH) && fs::is_directory(PATH)) {
        fs::directory_iterator diter(PATH);
        InitLoop();
        for(LOOP_CNT = 0; (diter != fs::end(diter) && LOOP_CNT < MAX_LOOP); ++LOOP_CNT) {
            const fs::directory_entry& entry = *diter;
            querys.get()->push_back(entry.path().c_str());
            diter++;
        }
    }
    return move(querys);
}

void HandleInput(istream& ins) {
    int num;
    InitLoop();
    for(LOOP_CNT = 0; (!ins.eof() && LOOP_CNT < MAX_LOOP); ++LOOP_CNT){
        ins >> num;
        if(ins.fail()) {
            ins.clear();
            ins.ignore('\n');
            continue;
        }
        cout << num << '\n';
    }
    if(LOOP_CNT >= MAX_LOOP) abort();
}

void HandleQuery(string& file) {
    fstream fs;
    fs.open(file);
    HandleInput(fs);
}

int main() {
    shared_ptr<vector<string>> files = RetrieveDirectoryFiles();
    for(auto& str : *files.get()) {
        HandleQuery(str);
    }
    return 0;
}
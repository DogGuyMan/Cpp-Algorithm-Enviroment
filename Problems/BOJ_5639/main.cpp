#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)
#define DEBUG 0
#define X first
#define Y second
using namespace std;

class Node {
public :
    int     curVal = 0;
    Node*   left = nullptr;
    Node*   right = nullptr;
    Node(int val) : curVal(val), left(nullptr), right(nullptr) {}
    Node() : Node(0) {}
};

class BST {
public: 
    vector<Node*> nodes;
    Node* rootNode = nullptr;
    const int RootIdx = 1;
    BST() {}
    ~BST() {
        for(auto& node : nodes) {
            node->left = nullptr;
            node->right = nullptr;
            delete node;
        }
        nodes.clear();
    }
    void Push(int val) {
        if(nodes.size() <= 0) {
            rootNode = new Node(val);
            nodes.push_back(rootNode);
            return;
        }
        int curIdx = RootIdx;
        Node* curNode = rootNode;
        Node* prevNode = nullptr;
        while(!(curNode == NULL)) {
            if(curNode->curVal == val) return;
            else if(val < curNode->curVal ){prevNode = curNode; curNode = curNode->left;}
            else if(curNode->curVal < val) {prevNode = curNode; curNode = curNode->right;}
#if DEBUG
            // cout << " curval : " << val << '\n';
            // cout << nxtIdx << '\n';
#endif
        }
        curNode = new Node(val);
        if(val < prevNode->curVal )     {prevNode->left = curNode;}
        else if(prevNode->curVal < val) {prevNode->right = curNode;}
        nodes.push_back(curNode);
    }
    int LeftIndex(int curIdx) {return curIdx * 2;}
    int RightIndex(int curIdx) {return (curIdx * 2) + 1;}
    void PostOrderPrint(Node* curNode) {
        if(curNode->left != NULL) PostOrderPrint(curNode->left);
        if(curNode->right != NULL) PostOrderPrint(curNode->right);
        cout << curNode->curVal << '\n';
    }
};

void HandleInput(istream& ins) {
    BST bst;
    while(!ins.eof()) {
        int val; ins >> val;
        if(ins.fail()) {ins.clear(); ins.ignore(); continue;}
        bst.Push(val);
    }
    if(bst.nodes.size() > 0)
        bst.PostOrderPrint(bst.rootNode);
}
void HandleQuery(const char* FILE_PATH) {
    fstream fs(FILE_PATH);
    if(fs.is_open()) { HandleInput(fs); }
}

int main(int argc, char* args[]){
    if(argc <= 1) {
	    FASTIO;
        HandleInput(cin);
    }
    else {
        const char* FILE_PATH = args[1];
        HandleQuery(FILE_PATH);
    }
}

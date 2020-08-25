#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class BinaryNode {
public:
    int nodeNumber;
    int x;
    int y;
    BinaryNode *leftChild = nullptr;
    BinaryNode *rightChild = nullptr;

    BinaryNode(int nodeNumber, int x, int y) {
        this->nodeNumber = nodeNumber;
        this->x = x;
        this->y = y;
    }
};

class BinaryTree {
public:
    BinaryNode *head;

    BinaryTree() {}

    BinaryTree(int nodeNumber, int x, int y) {
        this->head = new BinaryNode(nodeNumber, x, y);
    }

    ~BinaryTree() {
        delete this->head;
    }

    void insertNode(BinaryNode *node) {
        BinaryNode *now = this->head;

        while(now != nullptr) {
            if(node->x < now->x && node->y < now->y) {
                if(now->leftChild == nullptr) {
                    now->leftChild = node;
                    return;
                } else {
                    now = now->leftChild;
                }
            } else if(node->x > now->x && node->y < now->y) {
                if(now->rightChild == nullptr) {
                    now->rightChild = node;
                    return;
                } else {
                    now = now->rightChild;
                }
            }
        }
    }

    vector<int> preorder(BinaryNode *node) {
        vector<int> visit;
        visit.push_back(node->nodeNumber);

        if(node->leftChild != nullptr) {
            vector<int> leftVisit = preorder(node->leftChild);
            for(int i = 0; i < leftVisit.size(); i++) {
                visit.push_back(leftVisit[i]);
            }
        }

        if(node->rightChild != nullptr) {
            vector<int> rightVisit = preorder(node->rightChild);
            for(int i = 0; i < rightVisit.size(); i++) {
                visit.push_back(rightVisit[i]);
            }
        }

        return visit;
    }

    vector<int> postorder(BinaryNode *node) {
        vector<int> visit;

        if(node->leftChild != nullptr) {
            vector<int> leftVisit = postorder(node->leftChild);
            for(int i = 0; i < leftVisit.size(); i++) {
                visit.push_back(leftVisit[i]);
            }
        }

        if(node->rightChild != nullptr) {
            vector<int> rightVisit = postorder(node->rightChild);
            for(int i = 0; i < rightVisit.size(); i++) {
                visit.push_back(rightVisit[i]);
            }
        }

        visit.push_back(node->nodeNumber);

        return visit;
    }
};

bool compareNodes(const BinaryNode& a, const BinaryNode& b) {
    if(a.y == b.y) {
        return a.x < b.x;
    }
    return a.y > b.y;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<BinaryNode> nodes;
    for(int i = 0; i < nodeinfo.size(); i++) {
        nodes.push_back(BinaryNode(i + 1, nodeinfo[i][0], nodeinfo[i][1]));
    }

    sort(nodes.begin(), nodes.end(), compareNodes);

    BinaryTree binaryTree(nodes.front().nodeNumber, nodes.front().x, nodes.front().y);

    for(int i = 1; i < nodes.size(); i++) {
        binaryTree.insertNode(&nodes[i]);
    }

    vector<vector<int>> answer;
    answer.push_back(binaryTree.preorder(binaryTree.head));
    answer.push_back(binaryTree.postorder(binaryTree.head));
    return answer;
}
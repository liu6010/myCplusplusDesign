/*** 
 * @Descripttion: 
 * @version: 
 * @Author: lhw
 * @Date: 2023-04-23 20:40:10
 * @FilePath: /C++/algorithm/lru/lru.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-05-29 10:58:48
 */
#include<iostream>
#include <unordered_map>
using namespace std;

struct Node
{
    int key, value;
    Node* prev;
    Node* next;
    Node(): key(0), value(0), prev(nullptr), next(nullptr){};
    Node(int key, int value): key(key), value(value), prev(nullptr), next(nullptr){};
};


class LRUCache{
private:
    int capacity;
    int size;
    Node* head;
    Node* tail;
    unordered_map<int, Node*> umap;
public:
    LRUCache(int capacity): capacity(capacity), size(0){
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    ~LRUCache(){
        while(head){
            auto temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void addToHead(Node* node){
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node* node){
        removeNode(node);
        addToHead(node);
    }
    Node* removeTail(){
        auto node = tail->prev;
        removeNode(node);
        return node;
    }
    int get(int key){
        if(!umap.count(key)) return -1;
        else{
            auto node = umap[key];
            moveToHead(node);
            return node->value; 
        }
    }

    void put(int key, int value){
        if(umap.count(key)){
            auto node = umap[key];
            node->value = value;
            moveToHead(node);
        }
        else{
            auto node = new Node(key, value);
            addToHead(node);
            ++size;
            umap[key] = node;
            if(size > capacity){
                auto node = removeTail();
                umap.erase(node->key);
                --size;
                delete node;
            }
        }
    }

    void printlru(ostream& iost = std::cout){
        auto cur = head->next;
        while(cur != tail->prev){
            iost << "[key:"<<cur->key<<", value:"<<cur->value<<"] -> ";
            cur = cur->next;
        }
        iost<< "[key:"<<cur->key<<", value:"<<cur->value <<"]"<<std::endl;
    }
};

// g++ lru.cpp -o lru
int main(){
    auto plru = new LRUCache(2);
    plru->put(1,1);
    plru->put(2,2);
    int get1 = plru->get(1);

    plru->put(3,3); 
    int get2 = plru->get(2);

    plru->put(4,4);

    int get11 = plru->get(1);
    int get3 = plru->get(3);
    int get4 = plru->get(4);

    std::cout << "get(1):"<<get1<<" get(2):"<<get2<<" get(1):"<<get11<<" get(2):"<<get3<<" get(4):"<<get4<<std::endl;
    plru->printlru();
    delete plru;
    getchar();

}
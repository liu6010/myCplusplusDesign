/*** 
 * @Descripttion: 
 * 实现双向链表+翻转链表
 * @version: 
 * @Author: lhw
 * @Date: 2023-08-09 16:36:46
 * @FilePath: /C++/myCplusplusDesign/algorithm/InterviewQuestion/3_ReverseList.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-08-09 16:36:53
 */
#include<iostream>
#include<vector>
using namespace std;
struct Node
{
    int date;
    struct Node* pre;
    struct Node* next;
    Node() : date(0), pre(nullptr), next(nullptr){}
    Node(int val) : date(val), pre(nullptr), next(nullptr){}
    Node(int val, struct Node* pre_, struct Node* next_) : date(val), pre(pre_), next(next_){}
};


class list{
public:

    list():head(new Node()), tail(new Node()){
        head->next = tail;
        tail->pre = head;
    }
    ~list(){
        while(head){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void add(int val){
        Node* pre = tail->pre;
        Node* newNode = new Node(val, pre, tail);
        pre->next = newNode;
        tail->pre = newNode;
    }
    void reverse()
    {
        Node* pre = tail;   // 最后一个节点为tail，将tail->pre = head->next;
        pre->pre = head->next;

        Node* cur = head->next;
        while (cur != tail)
        {
            Node* temp = cur->next;
            cur->next = pre;    // cur->next指向pre
            cur->pre = temp;    // cur->pre指向temp
            
            pre = cur;          // pre = cur
            cur = temp;         // cur = temp
        }
        pre->pre = head;
        head->next = pre;
    }
    void printList() const{
        Node* cur = head->next;
        while(cur != tail){
            std::cout << cur->date << " " ;
            cur = cur->next;
        }
        std::cout << std::endl;
    }
private:
    Node* head;
    Node* tail;

};
int main()
{
    list* pNode = new list();
    pNode->add(1);
    pNode->add(2);
    pNode->add(3);
    pNode->add(4);
    pNode->add(5);
    pNode->add(6);
    pNode->printList();
    pNode->reverse();
    pNode->printList();
    return 0;

}
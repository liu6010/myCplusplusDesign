#include <iostream>
#include <vector>
using namespace std;


class Trie {
private:
    vector<Trie*> datas;
    bool isEnd;
public:
    Trie():isEnd(false), datas(26, nullptr) {
    }
    
    void insert(string word) {
        Trie* node = this;
        for(int i=0;i<word.size();i++){
            int index = word[i]-'a';
            if(!node->datas[index]){
                node->datas[index] = new Trie();
            }
            node = node->datas[index];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        Trie* node = this;
        for(int i=0;i<word.size();i++){
            int index = word[i]-'a';
            if(!node->datas[index]){
                return false;
            }
            node = node->datas[index];
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        Trie* node = this;
        for(int i=0;i<prefix.size();i++){
            int index = prefix[i]-'a';
            if(!node->datas[index]){
                return false;
            }
            node = node->datas[index];
        }
        return node != nullptr;
    }
};


int main(){
    Trie t;
    t.insert("apple");
    std::cout << R"(insert "apple")" << std::endl;

    std::cout << R"(search "apple")" << t.search("apple") << std::endl;
    std::cout << R"(search "app")" << t.search("app") << std::endl;
    std::cout << R"(startsWith "app")" << t.startsWith("app") << std::endl;
    t.insert("app");
    std::cout << R"(insert "app")" <<std::endl;
    std::cout << R"(search "app")" << t.search("app") << std::endl;


}


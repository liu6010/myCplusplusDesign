#include <iostream>
#include <vector>
using namespace std;
/*
原理：当前位置选择后面所有元素最小的
*/


// 时间复杂度:O(n^2)
// 不稳定排序

void SelectSort(vector<int>& nums){
    int minIdx = 0;
    for(size_t i=0;i<nums.size();i++){
        minIdx = i;
        for(size_t j=i+1;j<nums.size();++j){
            if(nums[j] < nums[minIdx]) minIdx = j;
        }
        swap(nums[i], nums[minIdx]);
    }
}

int main(){
    srand(time(nullptr));
    vector<int> nums;
    for(size_t i=0;i<10;i++){
        nums.emplace_back(rand()%100);
    }
    for(auto& n:nums){
        cout<<n<<" ";
    }
    cout <<endl;
    SelectSort(nums);

    for(auto& n:nums){
        cout<<n<<" ";
    }
    cout <<endl;

}
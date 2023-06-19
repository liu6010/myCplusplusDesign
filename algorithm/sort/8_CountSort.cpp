#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
思路：
    新建一个数组，统计每个元素出现的次数
    求比当前元素小的个数为i
    在新数组中i位置就是该元素
*/

// 稳定
// 时间复杂度O(max(nums))
// 空间复杂度O(max(nums))

void CountSort(vector<int>& nums){
    vector<int> obj(nums.size(),0);
    int maxVal = *max_element(nums.begin(), nums.end());
    vector<int> vecCount(maxVal+1, 0);
    for(auto& n:nums){
        vecCount[n]++;
    }
    for(int i=1;i<vecCount.size();i++){
        vecCount[i] += vecCount[i-1];
    }
    // 将当前元素从计数数组中取出来
    for(int i=nums.size(); i>0;i--){
        obj[--vecCount[nums[i-1]]] = nums[i-1];
    }

    nums.swap(obj);
}


int main(){
    srand(time(nullptr));
    vector<int> nums;
    for(int i=0;i<10;i++){
        nums.emplace_back(rand()%100);
    }
    for(auto& n:nums){
        cout<<n<<" ";
    }
    cout <<endl;
    CountSort(nums);

    for(auto& n:nums){
        cout<<n<<" ";
    }
    cout <<endl;
}
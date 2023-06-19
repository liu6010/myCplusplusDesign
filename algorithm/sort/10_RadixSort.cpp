#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*
基数排序：
    获取最大元素的位数，决定迭代的次数
    分为10个桶，因为个位数是0——9，统计个位、十位、百位....在桶的个数
        然后使用计数排序的方式，统计当前元素有多少个元素k，元素的新位置就是k

*/

int getMaxBit(vector<int>& nums){
    int maxVal = *max_element(nums.begin(), nums.end());
    int cnt(1);
    while(maxVal>10){
        cnt++;
        maxVal /=10;
    }
    return cnt;
}

void RadixSort(vector<int>& nums){
    int maxBit = getMaxBit(nums);
    int n = nums.size();
    vector<int> count(10, 0);       // 用来计数
    vector<int> temp(nums.size());  // 暂存排序结果
    int radix = 1;
    int index;
    for(int i=1; i<= maxBit; i++){  
        std::fill(count.begin(), count.end(), 0);
        // 统计在桶中的数量
        for(int j=0; j<n;j++){
            index = (nums[j]/radix) % 10;
            count[index]++;
        }
        // 统计元素j前有多少个元素
        for(int j=1;j<10;j++){
            count[j] += count[j-1];
        }
        // 将当前元素从桶中取出来放到temp数组中
        for(int j=n-1;j>=0;j--){                // 必须逆序，因为在当前桶中其实隐含了之前迭代位数的有序行，从小到大，取出时也应保持有序
            index = (nums[j]/radix) % 10;
            temp[--count[index]] = nums[j];
        }
        swap(temp, nums); // 将临时数组的内容交换到nums中

        radix *= 10;
    }
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
    RadixSort(nums);

    for(auto& n:nums){
        cout<<n<<" ";
    }
    cout <<endl;
}
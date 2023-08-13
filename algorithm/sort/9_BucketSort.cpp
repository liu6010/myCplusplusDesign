#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
/*
桶排序

计数排序的优化：将整个数组按最小值和最大值的整个区间进行均分，均分的数量的桶的数量
            遍历整个数组，将对应的数字放到对应的桶中；
            对每个桶进行排序，排序的方式可以是插入排序也可以是其他排序
            然后再把桶里面的元素取出来
*/

const int BUCKET_NUM = 10;

void InsertSort(vector<int>& nums){
    for(size_t i=1;i<nums.size();i++){
        int temp = nums[i];
        int j=i-1;
        while(j>=0 && temp < nums[j]){
            nums[j+1] = nums[j];
            --j;
        }
        nums[j+1] = temp;
    }
}


void BucketSort(vector<int>& nums){
    int minVal = *min_element(nums.begin(), nums.end());
    int maxVal = *max_element(nums.begin(), nums.end());

    int buket_size = (maxVal-minVal) / BUCKET_NUM + 1;      // 每个桶的容量
    vector<vector<int>> buckets(BUCKET_NUM);

    for(size_t i=0; i< nums.size();i++){
        int index = (nums[i] - minVal) / buket_size; 
        buckets[index].emplace_back(nums[i]);
    }
    for(size_t i=0, k=0; i< buckets.size();i++){
        InsertSort(buckets[i]);
        for(size_t j=0; j< buckets[i].size();j++){
            nums[k++] = buckets[i][j];
        }
    }
}

bool valid(vector<int>& nums){
    for(size_t i=1; i< nums.size();i++){
        if(nums[i] < nums[i-1]) return false;
    }
    return true;
}

void test(){

    int count(0);
    int testCnt=1000;
    while(testCnt--){
        srand(time(nullptr));
        vector<int> nums(rand()%1000);
        for(size_t i=0;i<nums.size();i++){
            nums[i] = rand()%200 - 100;
        }
        BucketSort(nums);
        bool flag = valid(nums);
        if(flag==false){
            cout << "error"<<endl;
            break;
        }
        count++;
    }
    cout << "sucess "<< count<<endl;
}
// g++ ../9.BucketSort.cpp BucketSort
int main(){
    test();
    // srand(time(nullptr));
    // vector<int> nums;
    // for(int i=0;i<10;i++){
    //     nums.emplace_back(rand()%100);
    // }
    // for(auto& n:nums){
    //     cout<<n<<" ";
    // }
    // cout <<endl;
    // BucketSort(nums);

    // for(auto& n:nums){
    //     cout<<n<<" ";
    // }
    // cout <<endl;
}
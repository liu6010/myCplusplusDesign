// 归并排序 https://leetcode.cn/problems/sort-an-array/
#include <iostream>
#include <vector>
using namespace std;

vector<int> temp;
// 自顶向下
void mergeSort(vector<int>& nums, int l, int r){
    if(l>=r) return ;
    int mid = l + (r-l) /2;
    mergeSort(nums, l, mid);                    // 递归到最左端
    mergeSort(nums, mid+1, r);                  // 递归到最右端，子区间只有一个元素
    int i=l, j = mid+1;
    int cnt =0;
    while(i<=mid && j<= r)temp[cnt++] = nums[i] < nums[j] ? nums[i++] : nums[j++];                      // 将两个右序数组合并到一个temp数组
    while(i<= mid) temp[cnt++] = nums[i++];
    while(j<= r) temp[cnt++] = nums[j++];
    for(int i=0; i< r-l+1; i++) nums[i+l] = temp[i];
}

void merge(vector<int>&nums, int start, int mid, int end){
    vector<int> temp(end-start+1, 0);
    int i=start, j = mid+1;
    int cnt=0;
    while(i<= mid && j <= end) temp[cnt++] = nums[i]<nums[j] ? nums[i++] : nums[j++];
    while(i<=mid) temp[cnt++] = nums[i++];
    while(j<=end) temp[cnt++] = nums[j++];
    for(int i=0; i< cnt; ++i){
        nums[start+i] = temp[i]; 
    }
}

// 自底向上
vector<int> sortArray(vector<int>& nums) {
    if(nums.size()==1) return nums;
    int n = nums.size();

    for(int size=1; size< n; size *= 2){
        for(int start =0; start < n-size; start += 2*size){
            int mid = start + size -1;
            int end = min(start + size * 2 -1,  n-1);
            merge(nums, start, mid, end);
        }
    }
    return nums;
}




int main(){
    vector<int> nums = {5,1,1,2,0,0};
    temp.resize((int)nums.size(), 0);
    mergeSort(nums, 0, nums.size()-1);

    for(auto& num:nums){
        cout <<num <<" ";
    }
    cout<<endl;
}
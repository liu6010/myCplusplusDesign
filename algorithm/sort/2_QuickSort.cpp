/*** 
 * @Descripttion: 快速排序
 * 随机选取一个数（x = rand() % len + startIndex）作为基准；
 * 把比基准小的数交换到前面，比基准大的数交换到后面；
 * 对左右区间递归重复。
 * @version: 
 * @Author: lhw
 * @Date: 2023-04-13 09:36:37
 * @FilePath: /myCplusplusDesign/algorithm/sort/2_QuickSort.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-08-13 13:36:15
 */

#include <iostream>
#include <vector>
using namespace std;

void QuickSortSimple(vector<int>& nums, int start, int end){
    if(start >= end) return;

    swap(nums[start], nums[rand() % (end - start + 1) + start]); // 基于随机的原则
    int tmp = nums[start];
    int l = start, r = end;
    while(l<r){
        // 往左走
        while (l<r && nums[r] >= tmp) --r;          // 结束时，右边遇到第一个小于tmp的数字就交换
        // 往右走
        while (l<r && nums[l] <= tmp) ++l;          // 结束时，左边遇到第一个大于tmp的数字；加等号的意义：如果在前进的过程中出现了相等的元素，加上等号，就代表跳过，继续向右移动，不进行填坑
        // if(l<r) nums[r] = nums[l];                  // 右边填坑
        if(l<r) swap(nums[r], nums[l]);                  // 右边填坑
    }
    // 两边相等了
    // nums[l] = tmp;      // 将tmp数填在l和r共同指向的位置
    swap(nums[start], nums[l]);
    QuickSortSimple(nums, start, l-1);     // 左边区间
    QuickSortSimple(nums, l+1, end);      // 右边区间
}

int choosePivot(vector<int>& nums, int start, int end){
        int mid = start+(end-start)/2;
        if(nums[start] > nums[mid]) swap(nums[start], nums[mid]);
        if(nums[start] > nums[end]) swap(nums[start], nums[end]);
        if(nums[mid] > nums[end]) swap(nums[mid], nums[end]);
        return nums[mid];
    }
void QuickSortThreeOfMedian(vector<int>& nums, int start, int end){
    if(start >= end) return;
    // 三数取中
    int pivot = choosePivot(nums, start, end);
    int l = start, r = end;
    while(l <= r) {
        while(nums[l] < pivot) ++l;
        while(nums[r] > pivot) --r;
        if(l <= r) {
            swap(nums[l++], nums[r--]);
        }
    }
    QuickSortThreeOfMedian(nums, start, r);
    QuickSortThreeOfMedian(nums, l, end);
}


int main(){
    srand((int)time(0));
    vector<int> nums;
    for(int i=0; i<10;i++){
        nums.push_back(rand()%100);
    }
    QuickSortThreeOfMedian(nums, 0, nums.size()-1);

    for(size_t i=0; i< nums.size();i++){
        cout << nums[i] <<" ";
    }
    cout <<endl;

}




/*** 
 * @Descripttion: 堆排序
 * https://leetcode.cn/problems/sort-an-array/solution/pai-xu-shu-zu-by-leetcode-solution/
 * 
 * @version: 
 * @Author: lhw
 * @Date: 2023-04-14 11:37:47
 * @FilePath: /CodeDemo/C++/algorithm/sort/HeapSort.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-06-02 19:35:29
 */
#include<iostream>
#include <vector>
using namespace std;


// len显示调整的区间长度
// holeIndex为开始节点，len为结束节点 
void AdjustHeap(vector<int>& nums, int holeIndex, int len){
    while(holeIndex*2+1 < len){     // 左孩子节点要小于总节点数量，只要没有超出范围就一直向下调整大小关系
        int lchild = holeIndex * 2+1;
        int rchild = lchild + 1;
        int large = holeIndex;
        if((lchild < len) && nums[lchild] > nums[holeIndex])  large = lchild;       // 左节点大于父节点

        if((rchild < len) && nums[rchild] > nums[large])  large = rchild;           // 右节点大于父节点大于左节点
        
        if(large != holeIndex){
            swap(nums[holeIndex], nums[large]);
            holeIndex = large; // 将替换的孩子作为新洞
        }
        else break;   // 父节点都大于子节点，退出
    }
}


void MakeHeap(vector<int>& nums){
    int len = nums.size();
    // 找出第一个需要重排的子树头部，任何叶子节点不需要执行下溯：将子节点和其较大子节点“对调”，并持续下放，直到叶子节点
    // // 数组array中如果当前节点为i，则左节点为2i，右节点为2i+1，父节点位于i/2处：#0元素不使用
    // 数组array中如果当前节点为i，则左节点为2i+1，右节点为2i+2，父节点位于i/2处：#0元素使用
    int holeIndex = (len-1) / 2;        // 最右端叶子节点的父节点下标
    for(int i = holeIndex; i>=0; i--){
        AdjustHeap(nums, i, len);
        // getchar();
    }
}


int main(){
    vector<int> nums = {-2, 45, 0, 11, -9, 7};
    MakeHeap(nums);                     // 创建一个大顶堆
    int len = nums.size()-1;
    for(int i=len; i>=0;i--){
        swap(nums[i], nums[0]);          // 将堆顶元素放到数组最后面，此时堆已经不是大顶堆了，需要重新调整堆的结构
        --len;                              // 调整范围[0, --len)
        AdjustHeap(nums, 0, len);           // 只调整堆顶元素就可以

    }

    for(auto& c:nums){
        cout << c <<" " ;
    }
    cout <<endl;
}
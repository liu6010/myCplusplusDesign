/*** 
 * @Descripttion: https://blog.csdn.net/Sueko/article/details/124563226
 *      冒泡排序
 *          比较相邻元素，如果第一个比第二个大则交换
 *          时间复杂度n^2，空间复杂度1
 * @version: 
 * @Author: lhw
 * @Date: 2023-04-13 10:16:38
 * @FilePath: /myCplusplusDesign/algorithm/sort/1_bubbleSort.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-08-13 13:33:14
 */
#include<iostream>
#include <vector>
#include <functional>
using namespace std;


/*
时间复杂度：
最优	O(n)
最坏	O(n^2)
平均	O(n^2)

空间复杂度	O(1)
稳定性	Yes

平均复杂度计算：(n-1) + (n-2) + (n-3) +.....+ 1 = n(n-1)/2

*/

// n个长度数组长度要排n-1次
void bubblesort(vector<int>& nums){
    int n = nums.size();
    for(int i=0;i<n-1;i++){ // 当前元素
        bool flag = false;
        for(int j=0; j<n-1-i;j++){      // n-1-i后面的元素表示已经排序完成
            if(nums[j]>nums[j+1]) {
                swap(nums[j], nums[j+1]);   // 将大的元素交换到最后面
                flag = true;
            }
        }
        if(flag == false) break;
    }
}

// print array
void printArray(vector<int>& nums ) {
  for (size_t i = 0; i < nums.size(); ++i) {
    cout << "  " << nums[i];
  }
  cout << "\n";
}

int main(){

    vector<int> nums = {-2, 45, 0, 11, -9};
    bubblesort(nums);
    printArray(nums);
    


}
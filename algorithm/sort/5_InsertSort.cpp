#include <iostream>
#include <vector>
using namespace std;

// 时间复杂度:O(n^2)
// 稳定排序

void InsertSort(vector<int>& nums){
    for(size_t i=1; i< nums.size(); ++i){
        if(nums[i] < nums[i-1]){
            int temp = nums[i];
            int j=i-1;
            while(j>=0 && temp < nums[j]){
                nums[j+1] = nums[j];
                j--;
            }
            nums[j+1] = temp;
        }
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
    InsertSort(nums);

    for(auto& n:nums){
        cout<<n<<" ";
    }
    cout <<endl;

}
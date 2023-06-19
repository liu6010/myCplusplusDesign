#include <iostream>
#include <vector>
using namespace std;

void InsertSort(vector<int>& nums, int gap){
    for(int i=gap;i<nums.size();i++){
        int temp = nums[i];
        int j = i-gap;
        while(j>=0 && temp < nums[j]){
            nums[j+gap] = nums[j];
            j -= gap;
        }
        nums[j+gap] = temp;
    }
}

void ShellSort(vector<int>& nums){
    for(int gap = nums.size() / 2; gap>0; gap>>=1){
        InsertSort(nums, gap);
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
    ShellSort(nums);

    for(auto& n:nums){
        cout<<n<<" ";
    }
    cout <<endl;
}
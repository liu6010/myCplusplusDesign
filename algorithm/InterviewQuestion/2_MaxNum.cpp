// https://leetcode.cn/problems/maximum-lcci/description/

/*
编写一个方法，找出两个数字a和b中最大的那一个。不得使用if-else或其他比较运算符。

示例：

输入： a = 1, b = 2
输出： 2
*/

#include <iostream>

using namespace std;

int maximum_simple(int a, int b)
{
    int val = a - b;
    int flag = (val >> 31) &1;  // 负数右移高位会补1，直接取最低位
    return b * flag + a * (flag ^ 1); // // 如果是0则a大，如果是1则b大
}

int maximum(int a, int b) {
    // 计算 int 类型的位数，避免不同系统下长度不同
    int bitlen = sizeof(a) * 8;

    // 计算 a 的符号位，b 的符号位
    // C/C++ 中负数右移最高位会补 1，因此需要转成无符号类型后再右移
    int asign = (a >> (bitlen - 1)) & 1;
    int bsign = (b >> (bitlen - 1)) & 1;
    // 假设 a 与 b 异号，计算 k 的值
    int k = asign ^ 1;  // a为正数时k=1,为负数时k=0

    // 当 a 和 b 异号时，asign ^ bsign ^ 1 为 0，由于 逻辑与运算 的短路性，将不再计算后半行代码，避免溢出
    // 当 a 和 b 同号时，asign ^ bsign ^ 1 为 1，此时会执行后半行代码，重新对 k 赋值
    int temp_cond = (asign ^ bsign ^ 1) && (k = static_cast<unsigned>(a - b) >> (bitlen - 1) ^ 1);
    return a * k + b * (k ^ 1);
}

int main()
{

    int a = 2147483647, b = -2147483648;
    int res = maximum(a, b);

    std::cout << res << std::endl;
}
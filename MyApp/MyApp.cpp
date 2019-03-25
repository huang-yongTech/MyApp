// MyApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <numeric>
//#include "AlgorithmTest.h"
//#include "MapTest.h"
//#include "MemoryTest.h"
#include "CopyControlTest.h"

using namespace std;

//函数声明
int fact(int value);

int main() {
	//cout << "Hello World!\n";

	//int b = 3;
	//int *const p1 = &b;
	//const int c = 4;
	//*p1 = c;
	//cout << "*p1的值为 " << *p1 << endl;

	//int aa = 11;
	//const int *p2 = &aa;
	//int bb = 22;
	//cout << "*p2的值为 " << *p2 << endl;

	//string s1 = "213a";
	//if (!s1.empty())
	//{
	//	string s2 = s1.substr(0, 2);
	//	cout << "s2的值为： " << s2 << endl;
	//}


	//vector<string> v;
	////这是范围for语句
	//for (char s : s1) {
	//	//cout << s << endl;
	//	v.push_back(string(1, s));
	//}

	//for (auto b = v.cbegin(); b != v.cend(); b++)
	//{
	//	cout << "输出的值为：" << *b << endl;
	//}

	//for (vector<string>::value_type &a : v) {
	//	cout << "另一种形式的打印：" << a << endl;
	//}


	//这里要注意一个问题：字符串字面值不能和int类型的值相加，否则会出现难以预料的效果，
	//编译器会运行通过，但是结果难以预料，总之不是想要的结果，
	//这个时候应该在字符串字面值和int类型的值之间添加一个重载输出运算符 "<<"
	//cout << "函数的返回值为：" << fact(5) << endl;

	//AlgorithmTest al;
	//al.removeIfTest();

	//MapTest mapTest;
	//mapTest.wordTransform();

	/*MemoryTest memoryTest;
	memoryTest.runQuries();*/

	string s("常规字符串");
	string s1("指针类型字符串");
	string *p1 = &s1;

	CopyControlTest controlTest(s, p1);
	CopyControlTest controlTest1 = copyControl(controlTest);
	controlTest1.print();

	return 0;
}

//函数定义
int fact(int value) {

	int total = 1;
	while (value > 1) {
		total *= value--;
	}
	return total;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目

// MyApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
//#include "CopyControlTest.h"
//#include "CopyControlPtrTest.h"
//#include "Message.h"
#include "MyString.h"
#include "StrVec.h"

using namespace std;

int main() {
	//string s("常规字符串");
	//string s1("指针类型字符串");
	//string *p1 = &s1;
	//CopyControlTest controlTest(s, p1);
	////这里虽然使用了等号赋值的形式，但是由于在等号左侧生了一个新的对象，因此这里调用的是拷贝构造函数
	////CopyControlTest controlTest1 = copyControl(controlTest);
	//CopyControlTest controlTest1;
	//controlTest1 = copyControl(controlTest);
	//controlTest1.print();

	/*CopyControlPtrTest copyControlPtr("测试行为像指针的类");
	CopyControlPtrTest copyControlPtr2;
	copyControlPtr2 = copyControlPtr;
	copyControlPtr.print();
	copyControlPtr2.print();*/

	//CopyControlPtrTest test1("111");
	//CopyControlPtrTest test2("1234");
	//CopyControlPtrTest test3("1112");
	//CopyControlPtrTest test4("11");
	//vector<CopyControlPtrTest> vec;
	//vec.push_back(test1);
	//vec.push_back(test2);
	//vec.push_back(test3);
	//vec.push_back(test4);
	//sort(vec.begin(), vec.end());

	//for (vector<CopyControlPtrTest>::value_type &value : vec) {
	//	value.print();
	//}

	//由于构造函数是显示的，因此需要使用string对象来构造一个string对象，再将该对象传到message的构造函数中
	//这里有问题，读取访问权限冲突
	//string s1("第一条消息");
	//string s2("第二条消息");
	//Message message1(s1);
	//Message message2(s2);
	//Message message3(message2);
	//message1 = message2;

	//message1.print();
	//message2.print();
	//message3.print();

	MyString s1("这是s1数据");
	MyString s2 = s1;
	vector<MyString> vec;
	vec.push_back(s1);
	vec.push_back(s1);
	vec.push_back(s1);
	vec.push_back(s1);

	return 0;
}


// MyApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include <vector>
//#include "CopyControlTest.h"
//#include "CopyControlPtrTest.h"
//#include "Message.h"
//#include "MyString.h"
#include "StrVec.h"
#include <iostream>

using namespace std;

int main() {
	//string s("常规字符串");
	//string s1("指针类型字符串");
	//string *p1 = &s1;
	//CopyControlTest controlTest1(s, p1);
	////这里虽然使用了等号赋值的形式，但是由于在等号左侧生了一个新的对象，因此这里调用的是拷贝构造函数
	////CopyControlTest controlTest1 = copyControl(controlTest);
	//CopyControlTest controlTest2;
	//controlTest2 = copyControl(controlTest1);
	//cout << (controlTest1 >= controlTest2) << endl;

	//CopyControlPtrTest copyControlPtr1("测试行为像指针的类");
	//CopyControlPtrTest copyControlPtr2;
	//copyControlPtr2 = copyControlPtr1;
	//cout << (copyControlPtr1 == copyControlPtr2) << endl;

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

	//Message message1("第一条消息");
	//Message message2("第二条消息");
	////需要初始化一个folder
	//Folder* folder = new Folder;
	//message1.save(*folder);
	//message2.save(*folder);
	//Message message3(message2);
	//message1 = message2;
	//delete folder;

	//message1.print();
	//message2.print();
	//message3.print();

	/*MyString s1("这是s1数据");
	MyString s2("这是s数据");
	cout << (s1 <= s2) << endl;*/

	string s1 = "拷贝进去的字符串1";
	string s2 = "拷贝进去的字符串2";
	StrVec vec1,vec2;
	vec1 = { s1,s2 };
	cout << vec1 << endl;

	return 0;
}


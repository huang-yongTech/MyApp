// MyApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "SalesData.h"
#include "Token.h"

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

	SalesData s1("book1", 4, 15);
	SalesData s2("book1", 5, 17);
	SalesData s3 = s1 + s2;

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;

	return EXIT_SUCCESS;
}

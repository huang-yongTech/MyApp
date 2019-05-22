// MyApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "pch.h"
//#include <vector>
//#include "CopyControlTest.h"
//#include "Message.h"
//#include "StrVec.h"
#include <iostream>
#include "Query.h"
#include "NotQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"
#include "TextQuery.h"
#include <fstream>
#include "QueryHistory.h"
//#include "Quote.h"
//#include "BulkQuote.h"
//#include "Basket.h"

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

	ifstream fileStream("D:\\AndroidDev\\CppSource\\MyApp\\outerfile\\MemoryExample.txt");
	TextQuery textQuery(fileStream);
	Query q1 = Query("the");
	Query q2 = Query("project");
	Query q3 = Query("AndroidX");
	QueryHistory queryHistory;
	queryHistory.add(q1);
	queryHistory.add(q2);
	//cout << ((queryHistory[0] & q3).eval(textQuery)) << endl;
	print(cout, (queryHistory[0] & q3).eval(textQuery), 1, 7);

	return 0;
}

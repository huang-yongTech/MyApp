// MyApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include <vector>
//#include "CopyControlTest.h"
//#include "Message.h"
//#include "StrVec.h"
#include <iostream>
#include "Quote.h"
#include "BulkQuote.h"

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

	double printTotal(ostream & os, const Quote & quote, size_t n);

	Quote quote1("1号书", 12.2);
	BulkQuote bulkQuote1("1号书", 12.2, 4, 0.2);
	printTotal(cout, bulkQuote1, 5);

	return 0;
}

double printTotal(ostream& os, const Quote& quote, size_t n) {
	double total = quote.net_price(n);
	os << "ISBN： " << quote.isbn() << " 卖出了： " << n << " 总价格是： " << total << endl;
	return total;
}


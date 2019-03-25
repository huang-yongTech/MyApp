#ifndef _COPY_CONTROL_TEST_H_
#define _COPY_CONTROL_TEST_H_

#include <string>

using namespace std;

class CopyControlTest {

	friend CopyControlTest copyControl(CopyControlTest copyControl);

public:
	//默认构造函数
	CopyControlTest();

	//构造函数
	CopyControlTest(string s, string *ptr);

	//拷贝构造函数
	CopyControlTest(const CopyControlTest &copyControl);

	//拷贝赋值运算符
	CopyControlTest& operator=(const CopyControlTest &copyControl);

	//打印
	void print();

	//析构函数
	~CopyControlTest();

private:
	//普通成员变量
	string s = "";
	//指针成员变量
	string *ptr = nullptr;
};

//拷贝
CopyControlTest copyControl(CopyControlTest copyControl);

#endif

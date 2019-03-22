#pragma once

using namespace std;

class CopyControlTest {
public:
	//默认构造函数
	CopyControlTest() = default;

	//拷贝构造函数
	CopyControlTest(CopyControlTest &);

	//拷贝赋值运算符
	CopyControlTest & operator=(const CopyControlTest &);

	//析构函数
	~CopyControlTest();
};


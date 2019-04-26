#ifndef _COPY_CONTROL_TEST_H_
#define _COPY_CONTROL_TEST_H_

#include <string>
#include <iostream>

using namespace std;

/*行为像值的类*/
class CopyControlTest {

	friend CopyControlTest copyControl(CopyControlTest copyControl);

	friend inline void swap(CopyControlTest &lControl, CopyControlTest &rControl);

	friend bool operator==(const CopyControlTest& lhs, const CopyControlTest& rhs);

	friend bool operator!=(const CopyControlTest& lhs, const CopyControlTest& rhs);

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

//如果内联函数在头文件中声明，则其定义最好也在头文件中，避免其他类调用时出现“LNK2019: 无法解析的外部符号”错误
inline void swap(CopyControlTest &lControl, CopyControlTest &rControl) {
	cout << "调用自定义的swap函数" << endl;

	using std::swap;
	swap(lControl.s, rControl.s);
	swap(lControl.ptr, rControl.ptr);
}

bool operator==(const CopyControlTest& lhs, const CopyControlTest& rhs);

bool operator!=(const CopyControlTest& lhs, const CopyControlTest& rhs);

#endif

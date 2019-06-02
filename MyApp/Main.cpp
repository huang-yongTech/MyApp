// MyApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Blob.h"
#include "BlobPtr.h"
#include "Vec.h"
#include "SharedPointer.h"

using namespace std;

//比较函数模板最好使用同一种比较操作符，这样可以节省调用者的工作量
template<typename T> int compare(const T& lhs, const T& rhs) {
	if (lhs < rhs) {
		return -1;
	}

	if (rhs < lhs) {
		return 1;
	}

	return 0;
}

template<typename IteratorT, typename ValueT> bool findX(const IteratorT& firstT, const IteratorT& lastT,
	const ValueT& valueT) {

	IteratorT begins = firstT;
	while (begins != lastT) {
		if (*begins == valueT) {
			return true;
		}
		++begins;
	}
	return false;
}

//打印任意长度任意大小的数组（在实际匹配时会优先匹配该函数）
template<typename T, unsigned N> void print(const T(&p1)[N]) {
	for (auto s = p1; s != p1 + N; ++s) {
		cout << *s << " ";
	}
	cout << endl;
}

//重载版本
template<typename T> void print(const T& arr) {
	for (auto& elem : arr) {
		cout << elem << " ";
	}
	cout << endl;
}

template<typename Arr> auto begin(const Arr& arr) -> decltype(arr.begin()) {
	return arr.begin();
}

template<typename Arr> auto end(const Arr& arr)->decltype(arr.end()) {
	return arr.end();
}

template<typename T, unsigned N> unsigned getArrLength(const T(&arr)[N]) {
	return N;
}

//第16章第19题
template<typename C> std::ostream& displayContainerItem(std::ostream& os, const C& c) {
	//使用容器的size_type和size()成员来循环打印容器
	/*for (typename C::size_type i = 0; i != c.size(); ++i) {
		os << c[i] << " ";
	}*/

	//使用容器的迭代器成员来打印容器
	for (auto first = c.begin(); first != c.end(); ++first) {
		os << *first << " ";
	}
	os << endl;

	return os;
}

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

	

	return 0;
}

#include "pch.h"
#include "MyString.h"
#include <algorithm>
#include <iostream>

using namespace std;

MyString::MyString() :elements(nullptr), firstFree(nullptr) {
}

MyString::MyString(const char *c) {
	//这里为什么要去掉底层const？
	char *ss = const_cast<char*>(c);

	//这里c是一个指针，指向一个字符数组的首元素，因此我们对其进行递增，得到字符数组的尾后指针
	while (*ss) {
		++ss;
	}

	//分配内存空间及数据
	auto newData = alloc_n_copy(c, ss);
	elements = newData.first;
	firstFree = newData.second;
}

MyString::MyString(const MyString &myString) {
	cout << "调用MyString拷贝构造函数" << endl;

	auto newData = alloc_n_copy(myString.elements, myString.firstFree);
	elements = newData.first;
	firstFree = newData.second;
}

MyString::MyString(MyString&& myString) noexcept :
	elements(myString.elements), firstFree(myString.firstFree) {
	cout << "调用MyString移动构造函数" << endl;

	myString.elements = myString.firstFree = nullptr;
}

MyString& MyString::operator=(const MyString &myString) {
	cout << "调用MyString拷贝赋值运算符" << endl;

	auto newData = alloc_n_copy(myString.elements, myString.firstFree);
	//在拷贝赋值运算符这里，需要销毁原来的内存数据
	free();

	//重新赋值
	elements = newData.first;
	firstFree = newData.second;

	return *this;
}

MyString& MyString::operator=(MyString&& myString) noexcept {
	cout << "调用MyString移动赋值运算符" << endl;

	if (this != &myString) {
		free();

		elements = myString.elements;
		firstFree = myString.firstFree;

		myString.elements = myString.firstFree = nullptr;
	}

	return *this;
}

MyString::~MyString() {
	free();
}

allocator<char> MyString::alloc;

pair<char*, char*> MyString::alloc_n_copy(const char *first, const char *last) {
	char* dstFirst = alloc.allocate(last - first);
	char* dstSecond = uninitialized_copy(first, last, dstFirst);
	//另一种返回pair数据结构的形式
	return make_pair(dstFirst, dstSecond);
}

void MyString::free() {
	if (elements) {
		for_each(elements, firstFree, [this](char &c)->void {alloc.destroy(&c); });
		alloc.deallocate(elements, firstFree - elements);
	}
}

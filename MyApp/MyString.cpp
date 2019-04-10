#include "pch.h"
#include "MyString.h"
#include <algorithm>

using namespace std;

MyString::MyString() {
}

MyString::MyString(const char *c) {
	//这里为什么要去掉底层const？
	auto ss = const_cast<char*>(c);

	//这里c是一个指针，指向一个字符数组的首元素，因此我们对其进行递增，得到字符数组的尾后指针
	while (ss) {
		++ss;
	}

	//分配内存空间及数据
	auto newData = alloc_n_copy(c, ss);
	elements = newData.first;
	end = newData.second;
}

MyString::MyString(const MyString &myString) {
	auto newData = alloc_n_copy(myString.elements, myString.end);
	elements = newData.first;
	end = newData.second;
}

MyString& MyString::operator=(const MyString &myString) {
	auto newData = alloc_n_copy(myString.elements, myString.end);
	//在拷贝赋值运算符这里，需要销毁原来的内存数据
	free();

	//重新赋值
	elements = newData.first;
	end = newData.second;

	return *this;
}

MyString::~MyString() {
}

pair<char*, char*> MyString::alloc_n_copy(const char *first, const char *last) {
	char* dstFirst = alloc.allocate(last - first);
	char* dstSecond = uninitialized_copy(first, last, dstFirst);
	//另一种返回pair数据结构的形式
	return make_pair(dstFirst, dstSecond);
}

void MyString::free() {
	if (elements) {
		for_each(elements, end, [this](char &c)->void {alloc.destroy(&c); });
		alloc.deallocate(elements, end - elements);
	}
}

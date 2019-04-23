#include "pch.h"
#include "StrVec.h"
#include <algorithm>
#include <iostream>

using namespace std;

//默认构造函数执行默认初始化
StrVec::StrVec() :elements(nullptr), firstFree(nullptr), cap(nullptr) {
}

//接受可变参数的构造函数
StrVec::StrVec(initializer_list<string> strList) {
	//为什么要把参数再次拷贝一遍？
	//答：这是构造函数，在构造的时候需要分配内存才能使用，因此需要使用alloc_n_copy函数分配一个内存。
	pair<string*, string*> newData = alloc_n_copy(strList.begin(), strList.end());
	elements = newData.first;
	firstFree = cap = newData.second;
}

StrVec::StrVec(const StrVec& strVec) {
	auto newData = alloc_n_copy(strVec.begin(), strVec.end());
	//初始化首迭代器
	elements = newData.first;
	//初始化尾后迭代器和表示容量的迭代器
	firstFree = cap = newData.second;
}

StrVec::StrVec(StrVec&& strVec) noexcept
	:elements(strVec.elements), firstFree(strVec.firstFree), cap(strVec.cap) {
	strVec.elements = strVec.firstFree = strVec.cap = nullptr;
}

StrVec& StrVec::operator=(const StrVec& strVec) {
	auto data = alloc_n_copy(strVec.begin(), strVec.end());
	free();
	//初始化首迭代器
	elements = data.first;
	//初始化尾后迭代器和表示容量的迭代器
	firstFree = cap = data.second;

	return *this;
}

StrVec& StrVec::operator=(StrVec&& strVec) noexcept {
	if (this != &strVec) {
		free();

		elements = strVec.elements;
		firstFree = strVec.firstFree;
		cap = strVec.cap;

		strVec.elements = strVec.firstFree = strVec.cap = nullptr;
	}

	return *this;
}

StrVec::~StrVec() {
	free();
}

//添加一个元素
void StrVec::push_back(const string& str) {
	cout << "调用拷贝版本的push_back" << endl;

	check_n_alloc();
	alloc.construct(firstFree++, str);
}

void StrVec::push_back(std::string&& str) {
	cout << "调用移动版本的push_back" << endl;

	check_n_alloc();
	alloc.construct(firstFree++, std::move(str));
}

//返回容器当前包含元素的大小
size_t StrVec::size() const {
	return firstFree - elements;
}

//容器当前能包含元素的最大大小
size_t StrVec::capacity() const {
	return cap - elements;
}

//返回首迭代器
string* StrVec::begin() const {
	return elements;
}

//返回尾后迭代器
string* StrVec::end() const {
	return firstFree;
}

//分配至少能容纳n个元素的空间
void StrVec::reserve(size_t n) {
	if (n < capacity()) {
		return;
	}

	alloc_n_move(n);
}

//调整容器的大小为n个元素，若n<size(),则多出的元素被丢弃。若必须添加新元素，对新元素进行值初始化。
void StrVec::resize(size_t n) {
	resize(n, string());
}

//调整容器的大小为n个元素。任何新添加的元素都初始化为值str
void StrVec::resize(size_t n, const string& str) {
	if (n > size()) {
		if (n > capacity()) {
			//扩容
			reserve(n);
			for (size_t pos = size(); pos < n; ++pos) {
				//这里要使用后缀递增运算符
				alloc.construct(firstFree++, str);
			}
		}
	}
	else if (n < size()) {
		while (firstFree != elements + n) {
			//这里要使用前缀递减运算符
			alloc.destroy(--firstFree);
		}
	}
}

allocator<string> StrVec::alloc;

//分配内存，并拷贝一个给定范围中的元素
pair<string*, string*> StrVec::alloc_n_copy(const string* first, const string* last) {
	string* data = alloc.allocate(last - first);
	return { data,uninitialized_copy(first,last,data) };
}

//销毁元素，并释放内存
void StrVec::free() {
	if (elements) {
		/*for (string* p = firstFree; p != elements;) {
			alloc.destroy(--p);
		}*/

		//为什么要捕获this参数？
		for_each(elements, firstFree, [this](string & str) {alloc.destroy(&str); });

		alloc.deallocate(elements, cap - elements);
	}
}

//检查StrVec的容量，若容量不够，则扩容
void StrVec::check_n_alloc() {
	if (size() == capacity()) {
		reallocate();
	}
}

//当StrVec当前空间用完时，为其重新分配内存
void StrVec::reallocate() {
	//分配大小为两倍内存的空间
	size_t newCapacity = size() ? 2 * size() : 1;

	alloc_n_move(newCapacity);
}

void StrVec::alloc_n_move(size_t newCapacity) {
	//分配新内存
	string* newStr = alloc.allocate(newCapacity);

	//将数据从旧内存移动到新内存
	string* dest = newStr;
	string* src = elements;

	for (size_t i = 0; i < size(); ++i) {
		//这里调用的是移动方法，避免在重新分配内存由于拷贝元素和销毁元素带来的性能消耗
		alloc.construct(dest++, std::move(*src++));
	}

	//移动完元素后就释放原来的内存空间
	free();

	elements = newStr;
	firstFree = dest;
	cap = elements + newCapacity;
}

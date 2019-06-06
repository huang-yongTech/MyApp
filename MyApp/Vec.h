#ifndef _VEC_H_
#define _VEC_H_

#include <ostream>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>
#include <map>

//第16章16题

template<typename T>
class Vec {

	friend std::ostream& operator<<(std::ostream& os, const Vec<T>& strVec) {
		for (T* first = strVec.begin(); first != strVec.end(); first++) {
			os << *first << " ";
		}
		os << std::endl;

		return os;
	}

	friend bool operator==(const Vec<T>& lhs, const Vec<T>& rhs) {
		return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	friend bool operator!=(const Vec<T>& lhs, const Vec<T>& rhs) {
		return !(lhs == rhs);
	}

	friend bool operator<(const Vec<T>& lhs, const Vec<T>& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	friend bool operator>(const Vec<T>& lhs, const Vec<T>& rhs) {
		return (lhs != rhs) && !(lhs < rhs);
	}

	friend bool operator<=(const Vec<T>& lhs, const Vec<T>& rhs) {
		return !(lhs > rhs);
	}

	friend bool operator>=(const Vec<T>& lhs, const Vec<T>& rhs) {
		return !(lhs < rhs);
	}

public:
	Vec();

	//接受可变参数的构造函数
	Vec(std::initializer_list<T> strList);

	//拷贝构造函数
	Vec(const Vec& strVec);

	//移动构造函数
	Vec(Vec&& strVec) noexcept;

	//拷贝赋值运算符
	Vec& operator=(const Vec& strVec);

	Vec& operator=(std::initializer_list<T> strList);

	//移动赋值运算符
	Vec& operator=(Vec&& strVec) noexcept;

	T& operator[](std::size_t n);

	const T& operator[](std::size_t n) const;

	~Vec();

	//像容器中添加一个元素
	void push_back(const T& t);

	void push_back(T&& t);

	//使用构造的方式向容器中添加元素
	//重点备注：这里虽然说是可变模板参数，但是一次只能接收一个参数，如果一次传入多个参数，
	//会导致未知错误（不知道这是不是设计上的bug？）
	template<typename...Args>
	void emplace_back(Args&& ...args);

	//返回容器当前包含元素的大小
	std::size_t size() const;

	//返回容器当前的容量
	std::size_t capacity() const;

	//返回指向容器第一个元素位置的迭代器
	T* begin() const;

	//返回指向容器最后一个元素位置之后的迭代器
	T* end() const;

	//分配至少能容纳n个元素的空间
	void reserve(std::size_t n);

	//调整容器的大小为n个元素，若n<size(),则多出的元素被丢弃。若必须添加新元素，对新元素进行值初始化。
	void resize(std::size_t n);

	//调整容器的大小为n个元素。任何新添加的元素都初始化为值str
	void resize(std::size_t n, const T& t);

private:

	//内存中的首元素
	T* elements;
	//最后一个实际元素之后的位置
	T* firstFree;
	//分配的内存末尾之后的位置
	T* cap;

	//静态变量声明后还需要在cpp源文件中定义才能运行
	static std::allocator<T> alloc;

	//分配内存，并拷贝一个给定范围中的元素
	std::pair<T*, T*> alloc_n_copy(const T* first, const T* last);

	//销毁构造的元素并释放内存
	void free();

	//检查StrVec的容量，若容量不够，则扩容
	void check_n_alloc();

	//当StrVec当前空间用完时，为其重新分配内存
	void reallocate();

	//当StrVec当前空间用完时，为其重新分配内存，新内存的容量大小为n，并将原容器中的元素移动到新内存中
	void alloc_n_move(std::size_t newCapacity);
};

//默认构造函数执行默认初始化
template<typename T>
Vec<T>::Vec() : elements(nullptr), firstFree(nullptr), cap(nullptr) {
}

//接受可变参数的构造函数
template<typename T>
Vec<T>::Vec(std::initializer_list<T> strList) {
	//为什么要把参数再次拷贝一遍？
	//答：这是构造函数，在构造的时候需要分配内存才能使用，因此需要使用alloc_n_copy函数分配一个内存。
	std::pair<T*, T*> newData = alloc_n_copy(strList.begin(), strList.end());
	elements = newData.first;
	firstFree = cap = newData.second;
}

template<typename T>
Vec<T>::Vec(const Vec<T>& strVec) {
	auto newData = alloc_n_copy(strVec.begin(), strVec.end());
	//初始化首迭代器
	elements = newData.first;
	//初始化尾后迭代器和表示容量的迭代器
	firstFree = cap = newData.second;
}

template<typename T>
Vec<T>::Vec(Vec<T>&& strVec) noexcept
	:elements(strVec.elements), firstFree(strVec.firstFree), cap(strVec.cap) {
	strVec.elements = strVec.firstFree = strVec.cap = nullptr;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& strVec) {
	std::pair<T*, T*> data = alloc_n_copy(strVec.begin(), strVec.end());
	free();
	//初始化首迭代器
	elements = data.first;
	//初始化尾后迭代器和表示容量的迭代器
	firstFree = cap = data.second;

	return *this;
}

template<typename T>
Vec<T>& Vec<T>::operator=(std::initializer_list<T> strList) {
	std::pair<T*, T*> newData = alloc_n_copy(strList.begin(), strList.end());
	free();
	elements = newData.first;
	firstFree = cap = newData.second;

	return *this;
}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec<T>&& strVec) noexcept {
	if (this != &strVec) {
		free();

		elements = strVec.elements;
		firstFree = strVec.firstFree;
		cap = strVec.cap;

		strVec.elements = strVec.firstFree = strVec.cap = nullptr;
	}

	return *this;
}

template<typename T>
T& Vec<T>::operator[](std::size_t n) {
	return elements[n];
}

template<typename T>
const T& Vec<T>::operator[](std::size_t n) const {
	return elements[n];
}

template<typename T>
Vec<T>::~Vec() {
	free();
}

//添加一个元素
template<typename T>
void Vec<T>::push_back(const T& t) {
	std::cout << "调用拷贝版本的push_back" << std::endl;

	check_n_alloc();
	alloc.construct(firstFree++, t);
}

template<typename T>
void Vec<T>::push_back(T&& t) {
	std::cout << "调用移动版本的push_back" << std::endl;

	check_n_alloc();
	alloc.construct(firstFree++, std::move(t));
}

template<typename T>
template<typename...Args>
inline void Vec<T>::emplace_back(Args&& ...args) {
	check_n_alloc();
	std::cout << size() << std::endl;
	std::cout << sizeof...(args) << std::endl;
	alloc.construct(firstFree++, std::forward<Args>(args)...);
}

//返回容器当前包含元素的大小
template<typename T>
std::size_t Vec<T>::size() const {
	return firstFree - elements;
}

//容器当前能包含元素的最大大小
template<typename T>
std::size_t Vec<T>::capacity() const {
	return cap - elements;
}

//返回首迭代器
template<typename T>
T* Vec<T>::begin() const {
	return elements;
}

//返回尾后迭代器
template<typename T>
T* Vec<T>::end() const {
	return firstFree;
}

//分配至少能容纳n个元素的空间
template<typename T>
void Vec<T>::reserve(std::size_t n) {
	if (n < capacity()) {
		return;
	}

	alloc_n_move(n);
}

//调整容器的大小为n个元素，若n<size(),则多出的元素被丢弃。若必须添加新元素，对新元素进行值初始化。
template<typename T>
void Vec<T>::resize(std::size_t n) {
	resize(n, T());
}

//调整容器的大小为n个元素。任何新添加的元素都初始化为值str
template<typename T>
void Vec<T>::resize(std::size_t n, const T& str) {
	if (n > size()) {
		if (n > capacity()) {
			//扩容
			reserve(n);
			for (std::size_t pos = size(); pos < n; ++pos) {
				//这里要使用后缀递增运算符
				alloc.construct(firstFree++, str);
			}
		}
	} else if (n < size()) {
		while (firstFree != elements + n) {
			//这里要使用前缀递减运算符
			alloc.destroy(--firstFree);
		}
	}
}

template<typename T>
std::allocator<T> Vec<T>::alloc;

//分配内存，并拷贝一个给定范围中的元素
template<typename T>
std::pair<T*, T*> Vec<T>::alloc_n_copy(const T* first, const T* last) {
	T* data = alloc.allocate(last - first);
	return { data,std::uninitialized_copy(first,last,data) };
}

//销毁元素，并释放内存
template<typename T>
void Vec<T>::free() {
	if (elements) {
		/*for (string* p = firstFree; p != elements;) {
			alloc.destroy(--p);
		}*/

		//为什么要捕获this参数？
		std::for_each(elements, firstFree, [this](T& t) {alloc.destroy(&t); });

		alloc.deallocate(elements, cap - elements);
	}
}

//检查StrVec的容量，若容量不够，则扩容
template<typename T>
void Vec<T>::check_n_alloc() {
	if (size() == capacity()) {
		reallocate();
	}
}

//当StrVec当前空间用完时，为其重新分配内存
template<typename T>
void Vec<T>::reallocate() {
	//分配大小为两倍内存的空间
	std::size_t newCapacity = size() ? 2 * size() : 1;

	alloc_n_move(newCapacity);
}

template<typename T>
void Vec<T>::alloc_n_move(size_t newCapacity) {
	//分配新内存
	T* newT = alloc.allocate(newCapacity);

	//将数据从旧内存移动到新内存
	T* dest = newT;
	T* src = elements;

	for (std::size_t i = 0; i < size(); ++i) {
		//这里调用的是移动方法，避免在重新分配内存由于拷贝元素和销毁元素带来的性能消耗
		alloc.construct(dest++, std::move(*src++));
	}

	//移动完元素后就释放原来的内存空间
	free();

	elements = newT;
	firstFree = dest;
	cap = elements + newCapacity;
}

#endif

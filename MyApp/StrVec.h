#ifndef _STR_VEC_H_
#define _STR_VEC_H_

#include <string>
#include <memory>

class StrVec {

	friend std::ostream& operator<<(std::ostream& os, const StrVec& strVec);

	friend bool operator==(const StrVec& lhs, const StrVec& rhs);

	friend bool operator!=(const StrVec& lhs, const StrVec& rhs);

	friend bool operator<(const StrVec& lhs, const StrVec& rhs);

	friend bool operator>(const StrVec& lhs, const StrVec& rhs);

	friend bool operator<=(const StrVec& lhs, const StrVec& rhs);

	friend bool operator>=(const StrVec& lhs, const StrVec& rhs);

public:
	StrVec();

	//接受可变参数的构造函数
	StrVec(std::initializer_list<std::string> strList);

	//拷贝构造函数
	StrVec(const StrVec& strVec);

	//移动构造函数
	StrVec(StrVec&& strVec) noexcept;

	//拷贝赋值运算符
	StrVec& operator=(const StrVec& strVec);

	StrVec& operator=(std::initializer_list<std::string> strList);

	//移动赋值运算符
	StrVec& operator=(StrVec&& strVec) noexcept;

	std::string& operator[](std::size_t n);

	const std::string& operator[](std::size_t n) const;

	~StrVec();

	//像容器中添加一个元素
	void push_back(const std::string& str);

	void push_back(std::string&& str);

	//同样一次只能接收一个参数，虽然这是可变模板参数，参考Vec.h中的同名函数
	template<typename...Args>
	void emplace_back(Args&& ...args);

	//返回容器当前包含元素的大小
	std::size_t size() const;

	//返回容器当前的容量
	std::size_t capacity() const;

	//返回指向容器第一个元素位置的迭代器
	std::string* begin() const;

	//返回指向容器最后一个元素位置之后的迭代器
	std::string* end() const;

	//分配至少能容纳n个元素的空间
	void reserve(std::size_t n);

	//调整容器的大小为n个元素，若n<size(),则多出的元素被丢弃。若必须添加新元素，对新元素进行值初始化。
	void resize(std::size_t n);

	//调整容器的大小为n个元素。任何新添加的元素都初始化为值str
	void resize(std::size_t n, const std::string& str);

private:

	//内存中的首元素
	std::string* elements;
	//最后一个实际元素之后的位置
	std::string* firstFree;
	//分配的内存末尾之后的位置
	std::string* cap;

	//静态变量声明后还需要在cpp源文件中定义才能运行
	static std::allocator<std::string> alloc;

	//分配内存，并拷贝一个给定范围中的元素
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string* first, const std::string* last);

	//销毁构造的元素并释放内存
	void free();

	//检查StrVec的容量，若容量不够，则扩容
	void check_n_alloc();

	//当StrVec当前空间用完时，为其重新分配内存
	void reallocate();

	//当StrVec当前空间用完时，为其重新分配内存，新内存的容量大小为n，并将原容器中的元素移动到新内存中
	void alloc_n_move(std::size_t newCapacity);
};

template<typename...Args>
void StrVec::emplace_back(Args&& ...args) {
	check_n_alloc();
	alloc.construct(firstFree++, std::forward<Args>(args)...);
}

std::ostream& operator<<(std::ostream& os, const StrVec& strVec);

bool operator==(const StrVec& lhs, const StrVec& rhs);

bool operator!=(const StrVec& lhs, const StrVec& rhs);

bool operator<(const StrVec& lhs, const StrVec& rhs);

bool operator>(const StrVec& lhs, const StrVec& rhs);

bool operator<=(const StrVec& lhs, const StrVec& rhs);

bool operator>=(const StrVec& lhs, const StrVec& rhs);

//第19章1节（自定义的operator new(或operator delete)最好放在类头文件中类定义的外面）
//void* operator new(size_t t);

//第19章1节
//void operator delete(void* ptr) noexcept;

#endif

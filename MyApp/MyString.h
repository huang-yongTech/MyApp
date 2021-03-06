#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <memory>

class MyString {

	friend std::ostream& operator<<(std::ostream& os, const MyString& myStream);

	friend bool operator==(const MyString& lsh, const MyString& rhs);

	friend bool operator!=(const MyString& lhs, const MyString& rhs);

	friend bool operator<(const MyString& lhs, const MyString& rhs);

	friend bool operator>(const MyString& lhs, const MyString& rhs);

	friend bool operator<=(const MyString& lhs, const MyString& rhs);

	friend bool operator>=(const MyString& lhs, const MyString& rhs);

public:

	MyString();

	//接受C风格字符串指针参数的构造函数
	MyString(const char* c);

	MyString(const MyString& myString);

	MyString(MyString&& myString) noexcept;

	MyString& operator=(const MyString& myString);

	MyString& operator=(MyString&& myString) noexcept;

	char& operator[](std::size_t n);

	const char& operator[](std::size_t n) const;

	~MyString();

	char* first() const;

	char* last() const;

	std::size_t size() const;

private:

	static std::allocator<char> alloc;

	//表示元素的首尾指针
	char* elements;
	char* firstFree;

	//分配内存，并拷贝一个给定范围中的元素
	std::pair<char*, char*> alloc_n_copy(const char* first, const char* last);

	//释放内存
	void free();
};

std::ostream& operator<<(std::ostream& os, const MyString& myStream);

bool operator==(const MyString& lhs, const MyString& rhs);

bool operator!=(const MyString& lhs, const MyString& rhs);

bool operator<(const MyString& lhs, const MyString& rhs);

bool operator>(const MyString& lhs, const MyString& rhs);

bool operator<=(const MyString& lhs, const MyString& rhs);

bool operator>=(const MyString& lhs, const MyString& rhs);

#endif

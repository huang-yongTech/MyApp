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

	//����C����ַ���ָ������Ĺ��캯��
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

	//��ʾԪ�ص���βָ��
	char* elements;
	char* firstFree;

	//�����ڴ棬������һ��������Χ�е�Ԫ��
	std::pair<char*, char*> alloc_n_copy(const char* first, const char* last);

	//�ͷ��ڴ�
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

#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <string>

class MyString {

public:

	MyString();

	//����C����ַ���ָ������Ĺ��캯��
	MyString(const char *c);

	MyString(const MyString& myString);

	MyString& operator=(const MyString& myString);

	~MyString();

private:

	static std::allocator<char> alloc;

	//��ʾԪ�ص���βָ��
	char *elements;
	char *end;

	//�����ڴ棬������һ��������Χ�е�Ԫ��
	std::pair<char*, char*> alloc_n_copy(const char *first, const char *last);

	//�ͷ��ڴ�
	void free();
};


#endif

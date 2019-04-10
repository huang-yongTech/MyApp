#ifndef _STR_VEC_H_
#define _STR_VEC_H_

#include <string>

class StrVec {

public:
	StrVec();

	//���ܿɱ�����Ĺ��캯��
	StrVec(initializer_list<string> strList);

	//�������캯��
	StrVec(const StrVec& strVec);

	//������ֵ�����
	StrVec& operator=(const StrVec& strVec);

	~StrVec();

	//�����������һ��Ԫ��
	void push_back(const std::string &str);

	//����������ǰ����Ԫ�صĴ�С
	size_t size() const;

	//����������ǰ������
	size_t capacity() const;

	//����ָ��������һ��Ԫ��λ�õĵ�����
	std::string* begin() const;

	//����ָ���������һ��Ԫ��λ��֮��ĵ�����
	std::string* end() const;

	//��������������n��Ԫ�صĿռ�
	void reserve(size_t n);

	//���������Ĵ�СΪn��Ԫ�أ���n<size(),������Ԫ�ر������������������Ԫ�أ�����Ԫ�ؽ���ֵ��ʼ����
	void resize(size_t n);

	//���������Ĵ�СΪn��Ԫ�ء��κ�����ӵ�Ԫ�ض���ʼ��Ϊֵstr
	void resize(size_t n, const string &str);

private:

	//�ڴ��е���Ԫ��
	std::string *elements;
	//���һ��ʵ��Ԫ��֮���λ��
	std::string *firstFree;
	//������ڴ�ĩβ֮���λ��
	std::string *cap;

	static std::allocator<std::string> alloc;

	//�����ڴ棬������һ��������Χ�е�Ԫ��
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string *first, const std::string *last);

	//���ٹ����Ԫ�ز��ͷ��ڴ�
	void free();

	//���StrVec��������������������������
	void check_n_alloc();

	//��StrVec��ǰ�ռ�����ʱ��Ϊ�����·����ڴ�
	void reallocate();

	//��StrVec��ǰ�ռ�����ʱ��Ϊ�����·����ڴ棬���ڴ��������СΪn������ԭ�����е�Ԫ���ƶ������ڴ���
	void alloc_n_move(size_t newCapacity);
};

#endif

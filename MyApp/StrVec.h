#ifndef _STR_VEC_H_
#define _STR_VEC_H_

#include <string>
#include <memory>

class StrVec {

public:
	StrVec();

	//���ܿɱ�����Ĺ��캯��
	StrVec(std::initializer_list<std::string> strList);

	//�������캯��
	StrVec(const StrVec& strVec);

	//�ƶ����캯��
	StrVec(StrVec&& strVec) noexcept;

	//������ֵ�����
	StrVec& operator=(const StrVec& strVec);

	//�ƶ���ֵ�����
	StrVec& operator=(StrVec&& strVec) noexcept;

	~StrVec();

	//�����������һ��Ԫ��
	void push_back(const std::string &str);

	void push_back(std::string&& str);

	//����������ǰ����Ԫ�صĴ�С
	std::size_t size() const;

	//����������ǰ������
	std::size_t capacity() const;

	//����ָ��������һ��Ԫ��λ�õĵ�����
	std::string* begin() const;

	//����ָ���������һ��Ԫ��λ��֮��ĵ�����
	std::string* end() const;
	
	//��������������n��Ԫ�صĿռ�
	void reserve(std::size_t n);

	//���������Ĵ�СΪn��Ԫ�أ���n<size(),������Ԫ�ر������������������Ԫ�أ�����Ԫ�ؽ���ֵ��ʼ����
	void resize(std::size_t n);

	//���������Ĵ�СΪn��Ԫ�ء��κ�����ӵ�Ԫ�ض���ʼ��Ϊֵstr
	void resize(std::size_t n, const std::string &str);

private:

	//�ڴ��е���Ԫ��
	std::string *elements;
	//���һ��ʵ��Ԫ��֮���λ��
	std::string *firstFree;
	//������ڴ�ĩβ֮���λ��
	std::string *cap;

	//��̬������������Ҫ��cppԴ�ļ��ж����������
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
	void alloc_n_move(std::size_t newCapacity);
};

#endif

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

	//���ܿɱ�����Ĺ��캯��
	StrVec(std::initializer_list<std::string> strList);

	//�������캯��
	StrVec(const StrVec& strVec);

	//�ƶ����캯��
	StrVec(StrVec&& strVec) noexcept;

	//������ֵ�����
	StrVec& operator=(const StrVec& strVec);

	StrVec& operator=(std::initializer_list<std::string> strList);

	//�ƶ���ֵ�����
	StrVec& operator=(StrVec&& strVec) noexcept;

	std::string& operator[](std::size_t n);

	const std::string& operator[](std::size_t n) const;

	~StrVec();

	//�����������һ��Ԫ��
	void push_back(const std::string& str);

	void push_back(std::string&& str);

	//ͬ��һ��ֻ�ܽ���һ����������Ȼ���ǿɱ�ģ��������ο�Vec.h�е�ͬ������
	template<typename...Args>
	void emplace_back(Args&& ...args);

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
	void resize(std::size_t n, const std::string& str);

private:

	//�ڴ��е���Ԫ��
	std::string* elements;
	//���һ��ʵ��Ԫ��֮���λ��
	std::string* firstFree;
	//������ڴ�ĩβ֮���λ��
	std::string* cap;

	//��̬������������Ҫ��cppԴ�ļ��ж����������
	static std::allocator<std::string> alloc;

	//�����ڴ棬������һ��������Χ�е�Ԫ��
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string* first, const std::string* last);

	//���ٹ����Ԫ�ز��ͷ��ڴ�
	void free();

	//���StrVec��������������������������
	void check_n_alloc();

	//��StrVec��ǰ�ռ�����ʱ��Ϊ�����·����ڴ�
	void reallocate();

	//��StrVec��ǰ�ռ�����ʱ��Ϊ�����·����ڴ棬���ڴ��������СΪn������ԭ�����е�Ԫ���ƶ������ڴ���
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

#endif

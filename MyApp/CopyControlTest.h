#ifndef _COPY_CONTROL_TEST_H_
#define _COPY_CONTROL_TEST_H_

#include <string>
#include <iostream>

using namespace std;

/*��Ϊ��ֵ����*/
class CopyControlTest {

	friend CopyControlTest copyControl(CopyControlTest copyControl);

	friend inline void swap(CopyControlTest &lControl, CopyControlTest &rControl);

	friend bool operator==(const CopyControlTest& lhs, const CopyControlTest& rhs);

	friend bool operator!=(const CopyControlTest& lhs, const CopyControlTest& rhs);

public:
	//Ĭ�Ϲ��캯��
	CopyControlTest();

	//���캯��
	CopyControlTest(string s, string *ptr);

	//�������캯��
	CopyControlTest(const CopyControlTest &copyControl);

	//������ֵ�����
	CopyControlTest& operator=(const CopyControlTest &copyControl);

	//��ӡ
	void print();

	//��������
	~CopyControlTest();

private:
	//��ͨ��Ա����
	string s = "";
	//ָ���Ա����
	string *ptr = nullptr;
};

//����
CopyControlTest copyControl(CopyControlTest copyControl);

//�������������ͷ�ļ������������䶨�����Ҳ��ͷ�ļ��У��������������ʱ���֡�LNK2019: �޷��������ⲿ���š�����
inline void swap(CopyControlTest &lControl, CopyControlTest &rControl) {
	cout << "�����Զ����swap����" << endl;

	using std::swap;
	swap(lControl.s, rControl.s);
	swap(lControl.ptr, rControl.ptr);
}

bool operator==(const CopyControlTest& lhs, const CopyControlTest& rhs);

bool operator!=(const CopyControlTest& lhs, const CopyControlTest& rhs);

#endif

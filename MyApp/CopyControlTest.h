#ifndef _COPY_CONTROL_TEST_H_
#define _COPY_CONTROL_TEST_H_

#include <string>

using namespace std;

class CopyControlTest {

	friend CopyControlTest copyControl(CopyControlTest copyControl);

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

#endif

#pragma once

using namespace std;

class CopyControlTest {
public:
	//Ĭ�Ϲ��캯��
	CopyControlTest() = default;

	//�������캯��
	CopyControlTest(CopyControlTest &);

	//������ֵ�����
	CopyControlTest & operator=(const CopyControlTest &);

	//��������
	~CopyControlTest();
};


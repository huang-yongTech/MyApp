#include "pch.h"
#include "CopyControlTest.h"

CopyControlTest::CopyControlTest() {
	cout << "�����޲������캯��" << endl;
}

//���������������н�����ɾ������ָ��Ĳ��������������ָ�븳ֵ�����ptr(new string(*ptr))����ֵ
//�����ڵ�����ͨ���캯����������غ����Լ���ǰ�����˳��������µ�����ָ�뱻ɾ�����ζ����ֵ�δ֪����
CopyControlTest::CopyControlTest(string s, string* ptr) :s(s), ptr(new string(*ptr)) {
	cout << "���ô������Ĺ��캯��" << endl;
}

CopyControlTest::CopyControlTest(const CopyControlTest& copyControl) {
	cout << "���ÿ������캯��" << endl;

	//ǳ����
	/*s = copyControl.s;
	ptr = copyControl.ptr;*/

	//���
	s = copyControl.s;

	//�漰��ָ�������ֵ������ڸ�ֵ֮ǰ���ָ���Ƿ�Ϊ��
	auto newPtr = (copyControl.ptr == nullptr) ? nullptr : new string(*copyControl.ptr);
	delete ptr;
	ptr = newPtr;
}

CopyControlTest & CopyControlTest::operator=(const CopyControlTest & copyControl) {
	cout << "���ÿ�����ֵ�����" << endl;

	//ǳ����
	//s = copyControl.s;
	//ptr = copyControl.ptr;

	//���
	s = copyControl.s;

	auto newPtr = (copyControl.ptr == nullptr) ? nullptr : new string(*copyControl.ptr);
	delete ptr;
	ptr = newPtr;

	return *this;
}

void CopyControlTest::print() {
	cout << "��ӡ��һ����Ա��" << s << endl;
	cout << "��ӡ�ڶ�����Ա��" << *ptr << endl;
}

CopyControlTest::~CopyControlTest() {
	if (ptr != nullptr) {
		cout << "ɾ��ָ��" << endl;
		delete this->ptr;
	}
}

CopyControlTest copyControl(CopyControlTest copyControl) {

	CopyControlTest controlTest(copyControl);

	return controlTest;
}

bool operator==(const CopyControlTest & lhs, const CopyControlTest & rhs) {
	if (lhs.ptr == nullptr && rhs.ptr != nullptr) {
		return false;
	}

	if (lhs.ptr != nullptr && rhs.ptr == nullptr) {
		return false;
	}

	if (lhs.ptr == nullptr && rhs.ptr == nullptr) {
		return lhs.s == rhs.s;
	}

	return (*lhs.ptr == *rhs.ptr) && (lhs.s == rhs.s);
}

bool operator!=(const CopyControlTest & lhs, const CopyControlTest & rhs) {
	return !(lhs == rhs);
}

bool operator<(const CopyControlTest & lhs, const CopyControlTest & rhs) {
	//��ָ����ǿ�ָ���С����жϣ�
	if (lhs.ptr == nullptr && rhs.ptr != nullptr) {
		return true;
	}

	if (lhs.ptr != nullptr && rhs.ptr == nullptr) {
		return false;
	}

	if (lhs.ptr == nullptr && rhs.ptr == nullptr) {
		return lhs.s < rhs.s;
	}

	return (*lhs.ptr < *rhs.ptr) && (lhs.s < rhs.s);
}

bool operator>(const CopyControlTest & lhs, const CopyControlTest & rhs) {
	return (lhs != rhs) && !(lhs < rhs);
}

bool operator<=(const CopyControlTest & lhs, const CopyControlTest & rhs) {
	return !(lhs > rhs);
}

bool operator>=(const CopyControlTest & lhs, const CopyControlTest & rhs) {
	return !(lhs < rhs);
}

#include "pch.h"
#include "CopyControlPtrTest.h"
#include <iostream>

/*��Ϊ��ָ�����*/

//���캯�������캯������һ���µĶ����Ķ���
CopyControlPtrTest::CopyControlPtrTest(const string& s = string()) : ps(new string(s)), i(0), use(new size_t(1)) {
	cout << "���ù��캯��" << endl;
}

//�������캯�����������캯����������ļ�������
CopyControlPtrTest::CopyControlPtrTest(const CopyControlPtrTest& copyControlPtr) :
	ps(copyControlPtr.ps), i(copyControlPtr.i), use(copyControlPtr.use) {
	cout << "���ÿ������캯��" << endl;

	++* use;
}

//������ֵ�������������ֵ����������Ҳ����õļ��������ݼ�������õļ�������
CopyControlPtrTest& CopyControlPtrTest::operator=(const CopyControlPtrTest& copyControlPtr) {
	cout << "���ÿ�����ֵ�����" << endl;

	//������ֵ������Ҳ��������ü���
	++* copyControlPtr.use;
	//�ݼ���ֵ���������������ü����������useָ����Ҫ��һ���пմ���
	if (use != nullptr && -- * use == 0) {
		delete ps;
		delete use;
	}

	ps = copyControlPtr.ps;
	i = copyControlPtr.i;
	use = copyControlPtr.use;

	return *this;
}

CopyControlPtrTest::CopyControlPtrTest(CopyControlPtrTest&& copyControlPtr) noexcept :
	ps(copyControlPtr.ps), i(copyControlPtr.i), use(copyControlPtr.use) {
	copyControlPtr.ps = nullptr;
	copyControlPtr.use = nullptr;
}

CopyControlPtrTest& CopyControlPtrTest::operator=(CopyControlPtrTest&& copyContronPtr) noexcept {
	if (this != &copyContronPtr) {
		delete ps;
		delete use;

		ps = copyContronPtr.ps;
		i = copyContronPtr.i;
		use = copyContronPtr.use;
	}

	return *this;
}

void CopyControlPtrTest::print() {
	cout << "��ӡ��Ϊ��ָ����ࣺ" << endl;
	cout << "ps: " << *ps << endl;
	cout << "i: " << i << endl;
	cout << "use: " << *use << endl;
}

CopyControlPtrTest::~CopyControlPtrTest() {
	if (use != nullptr && -- * use == 0) {
		delete use;
		//����ps����Ҫ�����ü���use����һ��ɾ����
		//ֻ�е�useΪ0����û������ʱ�����ɾ�������ܵ���ɾ�����������ֶ��delete ps���³���δ֪����
		delete ps;
	}
}

bool operator<(const CopyControlPtrTest& leftControl, const CopyControlPtrTest& rightControl) {
	cout << "����С�ڱȽ������" << endl;

	return *leftControl.ps < *rightControl.ps;
}

//�Զ���Ľ�������
void swap(CopyControlPtrTest& lControl, CopyControlPtrTest& rControl) {
	cout << "����CopyControlPtrTest�Զ����swap����" << endl;

	using std::swap;
	swap(lControl.ps, rControl.ps);
	swap(lControl.i, rControl.i);
	swap(lControl.use, rControl.use);
}

bool operator==(const CopyControlPtrTest& lhs, const CopyControlPtrTest& rhs) {
	return (lhs.ps == rhs.ps) && (lhs.i == rhs.i) && (lhs.use == rhs.use);
}

bool operator!=(const CopyControlPtrTest & lhs, const CopyControlPtrTest & rhs) {
	return !(lhs == rhs);
}

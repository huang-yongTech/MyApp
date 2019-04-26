#ifndef _COPY_CONTROL_PTR_TEST_H_
#define _COPY_CONTROL_PTR_TEST_H_

#include <string>

using namespace std;

/*行为像指针的类*/
class CopyControlPtrTest {

	friend bool operator<(const CopyControlPtrTest &leftControl, const CopyControlPtrTest &rightControl);

	friend void swap(CopyControlPtrTest &lControl, CopyControlPtrTest &rControl);

	friend bool operator==(const CopyControlPtrTest& lhs, const CopyControlPtrTest& rhs);

	friend bool operator!=(const CopyControlPtrTest& lhs, const CopyControlPtrTest& rhs);

public:
	CopyControlPtrTest() = default;

	CopyControlPtrTest(const string &s);

	CopyControlPtrTest(const CopyControlPtrTest &copyControlPtr);

	CopyControlPtrTest& operator=(const CopyControlPtrTest &copyControlPtr);

	CopyControlPtrTest(CopyControlPtrTest&& copyControlPtr) noexcept;

	CopyControlPtrTest& operator=(CopyControlPtrTest&& copyControlPtr) noexcept;

	void print();

	~CopyControlPtrTest();

private:
	string *ps;
	int i;
	size_t *use;
};

bool operator<(const CopyControlPtrTest &leftControl, const CopyControlPtrTest &rightControl);

void swap(CopyControlPtrTest &lControl, CopyControlPtrTest &rControl);

bool operator==(const CopyControlPtrTest& lhs, const CopyControlPtrTest& rhs);

bool operator!=(const CopyControlPtrTest& lhs, const CopyControlPtrTest& rhs);

#endif


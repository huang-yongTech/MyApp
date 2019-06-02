#ifndef _DEBUG_DELETE_H_
#define _DEBUG_DELETE_H_

#include <ostream>
#include <iostream>

using namespace std;

//��16��21��

class DebugDelete {
public:

	DebugDelete(std::ostream& os = std::cerr);

	~DebugDelete();

	template<typename T> void operator()(T* t) const;

private:

	std::ostream& os;
};

template<typename T>
void DebugDelete::operator()(T* p) const {
	cout << "deleting ptr" << endl;
	delete p;
}

#endif

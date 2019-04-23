#ifndef _FOO_H_
#define _FOO_H_

#include <vector>

class Foo {
public:
	
	Foo();
	
	~Foo();

	Foo sorted() &&;

	Foo sorted() const &;

private:

	std::vector<int> vec;
};

#endif

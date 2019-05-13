#ifndef _QUOTE_H_
#define _QUOTE_H_

#include <string>

class Quote {

	friend bool operator!=(const Quote& lhs, const Quote& rhs);

public:

	Quote();

	Quote(const std::string& bookNo, double salesPrice);

	Quote(const Quote& quote);

	Quote& operator=(const Quote& quote);

	Quote(Quote&& quote) noexcept;

	Quote& operator=(Quote&& quote) noexcept;

	virtual ~Quote();

	std::string isbn() const;

	virtual double net_price(std::size_t n) const;

	virtual void debug();

	//使用左值和右值限定符时，使用左值限定符的成员函数必须同时使用const限定符修饰，否则在调用的时候会出现二义性错误。
	virtual Quote* clone() const & {
		return new Quote(*this);
	}

	virtual Quote* clone() && {
		return new Quote(std::move(*this));
	}

private:

	std::string bookNo;

protected:

	double price = 0.0;
};

bool operator!=(const Quote& lhs, const Quote& rhs);

double printTotal(std::ostream& os, const Quote& quote, std::size_t n);

#endif

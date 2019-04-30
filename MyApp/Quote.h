#ifndef _QUOTE_H_
#define _QUOTE_H_

#include <string>

class Quote {

public:

	Quote();

	Quote(const std::string& bookNo, double salesPrice);

	virtual ~Quote();

	std::string isbn() const;

	virtual double net_price(std::size_t n) const;

	virtual void debug();

private:

	std::string bookNo;

protected:

	double price = 0.0;
};

#endif

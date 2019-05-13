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

	//ʹ����ֵ����ֵ�޶���ʱ��ʹ����ֵ�޶����ĳ�Ա��������ͬʱʹ��const�޶������Σ������ڵ��õ�ʱ�����ֶ����Դ���
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

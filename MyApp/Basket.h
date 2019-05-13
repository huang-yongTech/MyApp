#ifndef _BASKET_H_
#define _BASKET_H_

#include "Quote.h"
#include <memory>
#include <set>

class Basket {

public:

	Basket();

	~Basket();

	void addItem(const std::shared_ptr<Quote>& quoteSale);

	void addItem(const Quote& quoteSale);

	void addItem(Quote&& quoteSale);

	double totalReceipt(std::ostream& os) const;

private:

	//为什么这里必须要声明为static，否则下面的成员就会报错？
	static bool compare(const std::shared_ptr<Quote>& lhs, const std::shared_ptr<Quote>& rhs);

	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> quoteItems{ compare };
};

#endif

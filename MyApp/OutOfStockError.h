#ifndef _OUT_OF_STOCK_ERROT_H_
#define _OUT_OF_STOCK_ERROT_H_

#include <string>
#include <stdexcept>

class OutOfStockError : public std::runtime_error {
public:
	explicit OutOfStockError(const std::string& s);
};

#endif



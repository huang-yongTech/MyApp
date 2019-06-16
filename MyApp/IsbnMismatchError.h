#ifndef _ISBN_MISMATCH_ERROR_
#define _ISBN_MISMATCH_ERROR_

#include <exception>
#include <string>
#include <stdexcept>

class IsbnMismatchError : public std::logic_error {

public:

	explicit IsbnMismatchError(const std::string& s);

	explicit IsbnMismatchError(const std::string& s, const std::string& left, const std::string& right);
	

	const std::string left;
	const std::string right;
};

#endif

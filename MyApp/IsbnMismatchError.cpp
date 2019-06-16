#include "pch.h"
#include "IsbnMismatchError.h"

IsbnMismatchError::IsbnMismatchError(const std::string& s) : std::logic_error(s) {
}

IsbnMismatchError::IsbnMismatchError(const std::string& s, const std::string& left, const std::string& right)
	: std::logic_error(s), left(left), right(right) {
}

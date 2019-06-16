#include "pch.h"
#include "OutOfStockError.h"

OutOfStockError::OutOfStockError(const std::string& s) : std::runtime_error(s) {
}

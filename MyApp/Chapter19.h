#ifndef _CHAPTER_H_
#define _CHAPTER_H_

#include "SalesData.h"
#include <vector>
#include <functional>
#include <algorithm>

class Chapter19 {

public:

	//ตฺ19ีย19ฬโ
	std::vector<SalesData>::iterator findFirstSalesData(std::vector<SalesData>& vec, double d) {
		double (SalesData:: * pf)() const = &SalesData::avgPrices;
		auto fcn = bind(pf, std::placeholders::_1);
		return find_if(vec.begin(), vec.end(), [&](const SalesData& salesData) -> bool { return d < fcn(salesData); });
	}
};

#endif

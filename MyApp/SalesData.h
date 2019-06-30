#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <string>
#include <istream>
#include <ostream>

template<typename T> struct std::hash;

class SalesData {

	friend bool operator==(const SalesData& lhs, const SalesData& rhs);

	friend bool operator!=(const SalesData& lhs, const SalesData& rhs);

	friend std::ostream& operator<<(std::ostream& os, const SalesData& salesData);

	friend bool compareIsbn(const SalesData& lhs, const SalesData& rhs);

	friend struct std::hash<SalesData>;

public:

	SalesData();

	SalesData(const std::string& s);

	SalesData(const std::string& s, unsigned unitsSold, double renvenue);

	SalesData(const SalesData& salesData);

	SalesData& operator=(const SalesData& salesData);

	SalesData(SalesData&& salesData) noexcept;

	SalesData& operator=(SalesData&& salesData) noexcept;

	~SalesData();

	std::string isbn() const;

	SalesData& combine(const SalesData& saledData);

	double avgPrices() const;

	std::istream& read(std::istream& is, SalesData& salesData);

	std::ostream& print(std::ostream& os, SalesData& salesData);

	//备注：当把重载运算符作为类的成员时，如果在重载运算符函数体内调用了别的重载运算符，
	//则需要将该运算符也声明为类的成员，否则会报错。
	SalesData& operator+(const SalesData& lhs);

	SalesData& operator+=(const SalesData& lhs);

private:

	std::string bookNo;

	unsigned unitsSold = 0;

	double renvenue = 0.0;
};

bool operator==(const SalesData& lhs, const SalesData& rhs);

bool operator!=(const SalesData& lhs, const SalesData& rhs);

std::ostream& operator<<(std::ostream& os, const SalesData& salesData);

bool compareIsbn(const SalesData& lhs, const SalesData& rhs);

//第16章62题
namespace std {
	//声明并定义一个SalesData的hash特例化版本
	template<>
	struct hash<SalesData> {
		//这两个类型别名是使用散列所必须的
		typedef size_t result_type;
		typedef SalesData argument_type;

		size_t operator()(const SalesData& salesData) const;
	};

	inline size_t hash<SalesData>::operator()(const SalesData& salesData) const {
		return hash<string>()(salesData.bookNo) ^
			hash<unsigned>()(salesData.unitsSold) ^
			hash<double>()(salesData.renvenue);
	}
}

#endif

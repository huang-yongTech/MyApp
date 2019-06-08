#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <string>
#include <istream>
#include <ostream>

template<typename T> struct std::hash;

class SalesData {

	friend bool operator==(const SalesData& lhs, const SalesData& rhs);

	friend SalesData& operator+=(const SalesData& lhs, const SalesData& rhs);

	friend SalesData& operator+(const SalesData& lhs, const SalesData& rhs);

	friend std::ostream& operator<<(std::ostream& os, const SalesData& salesData);

	friend bool compareIsbn(const SalesData& lhs, const SalesData& rhs);

	friend struct std::hash<SalesData>;

public:

	SalesData();

	SalesData(const std::string& s);

	SalesData(const std::string& s, unsigned unitsSold, double renvenue);

	~SalesData();

	std::string isbn() const;

	SalesData& combine(const SalesData& saledData);

	double avgPrices() const;

	std::istream& read(std::istream& is, SalesData& salesData);

	std::ostream& print(std::ostream& os, SalesData& salesData);

private:

	std::string bookNo;

	unsigned unitsSold = 0;

	double renvenue = 0.0;
};

bool operator==(const SalesData& lhs, const SalesData& rhs);

SalesData& operator+=(const SalesData& lhs,const SalesData& rhs);

//重载的加法运算符必须使用const修饰，否则会报错
SalesData& operator+(const SalesData& lhs,const SalesData& rhs);

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

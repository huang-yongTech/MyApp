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

	//��ע�����������������Ϊ��ĳ�Աʱ�����������������������ڵ����˱�������������
	//����Ҫ���������Ҳ����Ϊ��ĳ�Ա������ᱨ��
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

//��16��62��
namespace std {
	//����������һ��SalesData��hash�������汾
	template<>
	struct hash<SalesData> {
		//���������ͱ�����ʹ��ɢ���������
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

#ifndef _CHAPTER_SEVENTEEN_H_
#define _CHAPTER_SEVENTEEN_H_

#include <tuple>
#include <vector>
#include "SalesData.h"
#include <algorithm>
#include <istream>
#include <ostream>
#include <iostream>
#include <numeric>
#include <bitset>
#include <regex>

//第17章习题
class Chapter17 {

public:
	typedef std::tuple<std::vector<SalesData>::size_type,
		std::vector<SalesData>::const_iterator,
		std::vector<SalesData>::const_iterator> matches;

	typedef std::pair<std::vector<SalesData>::size_type,
		std::pair<std::vector<SalesData>::const_iterator,
		std::vector<SalesData>::const_iterator>> matches_pair;

	struct matches_struct {
		std::vector<SalesData>::size_type storePos;
		std::vector<SalesData>::const_iterator salesPosFirst;
		std::vector<SalesData>::const_iterator salesPosLast;

		matches_struct(std::vector<SalesData>::size_type storePos,
			std::vector<SalesData>::const_iterator salesPosFirst,
			std::vector<SalesData>::const_iterator salesPosLast)
			: storePos(storePos), salesPosFirst(salesPosFirst), salesPosLast(salesPosLast) {
		}
	};

	Chapter17() = default;

	~Chapter17() = default;

	//17.4
	std::vector<matches> findBook(const std::vector<std::vector<SalesData>>& filesVec, const std::string& book) {
		std::vector<matches> retVec;

		for (std::vector<std::vector<SalesData>>::const_iterator it = filesVec.cbegin(); it != filesVec.cend(); ++it) {
			std::pair<std::vector<SalesData>::const_iterator,
				std::vector<SalesData>::const_iterator> founds =
				equal_range(it->cbegin(), it->cend(), book, compareIsbn);

			if (founds.first != founds.second) {
				retVec.push_back(make_tuple(it - filesVec.cbegin(), founds.first, founds.second));
			}
		}
	}

	//17.5
	std::vector<matches_pair> findBookPair(const std::vector<std::vector<SalesData>>& filesVec, const std::string& book) {
		std::vector<matches_pair> retVec;

		for (std::vector<std::vector<SalesData>>::const_iterator it = filesVec.cbegin(); it != filesVec.cend(); ++it) {
			std::pair<std::vector<SalesData>::const_iterator,
				std::vector<SalesData>::const_iterator> founds =
				equal_range(it->cbegin(), it->cend(), book, compareIsbn);

			if (founds.first != founds.second) {
				retVec.push_back(make_pair(it - filesVec.cbegin(), make_pair(founds.first, founds.second)));
			}
		}
	}

	//17.6
	std::vector<matches_struct> findBookStruct(const std::vector<std::vector<SalesData>>& filesVec, const std::string& book) {
		std::vector<matches_struct> retVec;

		for (std::vector<std::vector<SalesData>>::const_iterator it = filesVec.cbegin(); it != filesVec.cend(); ++it) {
			std::pair<std::vector<SalesData>::const_iterator,
				std::vector<SalesData>::const_iterator> founds =
				equal_range(it->cbegin(), it->cend(), book, compareIsbn);

			if (founds.first != founds.second) {
				retVec.push_back(matches_struct(it - filesVec.cbegin(), founds.first, founds.second));
			}
		}
	}

	//17.4
	void reportResult(std::istream& is, std::ostream& os, const std::vector<std::vector<SalesData>>& filesVec) {
		std::string s;//要查找的书

		while (is >> s) {
			std::vector<matches> matchVec = findBook(filesVec, s);

			if (matchVec.empty()) {
				os << s << " 在书店中没有找到该书籍" << std::endl;
				continue;
			}

			for (const matches& match : matchVec) {
				os << "商店 " << std::get<0>(match) << " 销售了：" <<
					std::accumulate(std::get<1>(match), std::get<2>(match), SalesData(s)) << std::endl;
			}
		}
	}

	//17.12
	template<unsigned N>
	void questionTest(std::bitset<N>& bitvec, std::pair<std::size_t, bool> pair) {
		bitvec.set(pair.first, pair.second);
	}

	//17.13
	template<unsigned N>
	void questionMark(std::bitset<N>& stuAnswers, std::bitset<N>& correctAnswers) {
		std::bitset<N> resultBit = stuAnswers ^ correctAnswers;
		resultBit.flip();
		std::cout << resultBit.count() << std::endl;
	}

	//17.15
	void regexWord() {
		std::string patten("[^c]ei");
		patten = "[[:alpha:]]*" + patten + "[[:alpha:]]*";
		try {
			std::regex r(patten, std::regex::icase);
			std::smatch results;

			std::string word;
			std::cout << "请输入待匹配的单词：" << std::endl;
			while (std::cin >> word && word != "q") {

				if (std::regex_search(word, results, r)) {
					std::cout << "符合匹配： " << results.str() << std::endl;
				} else {
					std::cout << "不符合匹配： " << word << std::endl;
				}

				std::cout << "请输入带匹配的单词，输入q退出！" << std::endl;
			}
		} catch (std::regex_error e) {
			std::cout << e.what() << " 出错了 " << e.code() << std::endl;
		}
	}

	//17.17
	void regexWord1() {
		std::string patten("[^c]ei");
		patten = "[[:alpha:]]*" + patten + "[[:alpha:]]*";
		try {
			std::regex r(patten, std::regex::icase);
			std::smatch results;

			std::string word;
			std::cout << "请输入待匹配的单词：" << std::endl;
			getline(std::cin, word);
			for (std::sregex_iterator it(word.begin(), word.end(), r), it_end; it != it_end; ++it) {
				std::cout << it->str() << std::endl;;
			}
		} catch (std::regex_error e) {
			std::cout << e.what() << " 出错了 " << e.code() << std::endl;
		}
	}

	//17.20 17.22
	void regexPhone();

	bool validPhone(const std::smatch& m);

	//17.23
	void regexPostCode();

	bool validPostCode(const std::smatch& m);

	//17.24
	void regexReplaceNum();

	//17.28
	void randomNumber();

	//17.29
	void randomNumber(unsigned long seed);

	//17.30
	void randomNumber(unsigned long seed, unsigned long min, unsigned long max);
};

#endif

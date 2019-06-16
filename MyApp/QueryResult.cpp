#include "pch.h"
#include "QueryResult.h"
#include <string>
#include <iostream>

using namespace std;

namespace chapter12 {

	using lineNo = vector<string>::size_type;

	QueryResult::QueryResult(string word, shared_ptr<set<lineNo>> linesSetP, shared_ptr<vector<string>> fileVectorP) :
		word(word), linesSetP(linesSetP), fileVectorP(fileVectorP) {
	}

	QueryResult::~QueryResult() {}

	set<lineNo>::iterator QueryResult::begin() const {
		return linesSetP->begin();
	}

	set<lineNo>::iterator QueryResult::end() const {
		return linesSetP->end();
	}

	shared_ptr<vector<string>> QueryResult::getFile() {
		return fileVectorP;
	}

	ostream& operator<<(ostream& os, const QueryResult& result) {
		os << result.word << " ������ " << result.linesSetP->size() << endl;

		for (set<lineNo>::size_type num : *result.linesSetP) {
			//result.fileVectorP->begin() + num�����ʾ��ӡword�������ڵ���
			os << "\t (line" << num + 1 << ")" << *(result.fileVectorP->begin() + num) << endl;
		}
		return os;
	}

	ostream& print(ostream& os, const QueryResult& result, const std::size_t& start, const std::size_t& end) {
		if (result.linesSetP->size() == 0) {
			return os;
		}

		if (start < 0) {
			cout << "start����С��0" << endl;
			return os;
		}

		if (end > result.linesSetP->size()) {
			cout << "end���ܳ�����ѯ����������Χ" << endl;
			return os;
		}

		size_t total = 0;

		for (set<lineNo>::size_type num : *result.linesSetP) {
			if ((num + 1) >= start && (num + 1) <= end) {
				os << "\t (line" << num + 1 << ")" << *(result.fileVectorP->begin() + num) << endl;
				++total;
			}
		}
		os << result.word << " ������ " << total << " �� " << endl;

		return os;
	}
}

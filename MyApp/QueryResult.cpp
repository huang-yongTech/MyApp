#include "pch.h"
#include "QueryResult.h"
#include <string>
#include <iostream>

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
	os << result.word << " 出现了 " << result.linesSetP->size() << endl;

	for (auto num : *result.linesSetP) {
		//result.fileVectorP->begin() + num这里表示打印word单词所在的行
		os << "\t (line" << num + 1 << ")" << *(result.fileVectorP->begin() + num) << endl;
	}
	return os;
}
#include "pch.h"
#include "QueryResult.h"
#include <string>
#include <iostream>

QueryResult::QueryResult(string word, shared_ptr<set<lineNo>> linesSetP, shared_ptr<vector<string>> fileVectorP) :
	word(word), linesSetP(linesSetP), fileVectorP(fileVectorP) {
}

QueryResult::~QueryResult() {}

//打印查找结果
ostream& print(ostream& os, const QueryResult& result) {
	os << result.word << " 出现了 " << result.linesSetP->size() << endl;

	for (auto num : *result.linesSetP) {
		//result.fileVectorP->begin() + num这里表示打印word单词所在的行
		os << "\t (line" << num + 1 << ")" << *(result.fileVectorP->begin() + num) << endl;
	}
	return os;
}
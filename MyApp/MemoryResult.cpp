#include "pch.h"
#include "MemoryResult.h"
#include <string>
#include <iostream>

MemoryResult::MemoryResult(string word, shared_ptr<set<lineNo>> linesSetP, shared_ptr<vector<string>> fileVectorP) :
	word(word), linesSetP(linesSetP), fileVectorP(fileVectorP) {
}

MemoryResult::~MemoryResult() {}

//打印查找结果
ostream & print(ostream &os, const MemoryResult &result) {
	os << result.word << " 出现了 " << result.linesSetP->size() << endl;

	for (auto num : *result.linesSetP) {
		//result.fileVectorP->begin() + num这里表示打印word单词所在的行
		os << "\t (line" << num + 1 << ")" << *(result.fileVectorP->begin() + num) << endl;
	}
	return os;
}
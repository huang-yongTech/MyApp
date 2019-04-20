#include "pch.h"
#include "MemoryResult.h"
#include <string>
#include <iostream>

MemoryResult::MemoryResult(string word, shared_ptr<set<lineNo>> linesSetP, shared_ptr<vector<string>> fileVectorP) :
	word(word), linesSetP(linesSetP), fileVectorP(fileVectorP) {
}

MemoryResult::~MemoryResult() {}

//��ӡ���ҽ��
ostream & print(ostream &os, const MemoryResult &result) {
	os << result.word << " ������ " << result.linesSetP->size() << endl;

	for (auto num : *result.linesSetP) {
		//result.fileVectorP->begin() + num�����ʾ��ӡword�������ڵ���
		os << "\t (line" << num + 1 << ")" << *(result.fileVectorP->begin() + num) << endl;
	}
	return os;
}
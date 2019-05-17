#include "pch.h"
#include "QueryResult.h"
#include <string>
#include <iostream>

QueryResult::QueryResult(string word, shared_ptr<set<lineNo>> linesSetP, shared_ptr<vector<string>> fileVectorP) :
	word(word), linesSetP(linesSetP), fileVectorP(fileVectorP) {
}

QueryResult::~QueryResult() {}

//��ӡ���ҽ��
ostream& print(ostream& os, const QueryResult& result) {
	os << result.word << " ������ " << result.linesSetP->size() << endl;

	for (auto num : *result.linesSetP) {
		//result.fileVectorP->begin() + num�����ʾ��ӡword�������ڵ���
		os << "\t (line" << num + 1 << ")" << *(result.fileVectorP->begin() + num) << endl;
	}
	return os;
}
#include "pch.h"
#include "TextQuery.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

//���캯������ȡ�����ļ������������ʵ��кŵ�mapӳ��
//����ΪfilesVectorP������һ���µ��ڴ�
TextQuery::TextQuery(ifstream &fileStream) :filesVectorP(new vector<string>) {
	//���ڱ���һ������
	string lineText;
	while (getline(fileStream, lineText)) {
		filesVectorP->push_back(lineText);
		//��ǰ�к�
		lineNo n = filesVectorP->size() - 1;
		//��һ���ı��ֽ�Ϊ����
		istringstream linestream(lineText);
		string word;
		while (linestream >> word) {
			//������ʲ���linesMap�У�ʹ���±���ӣ����±귵�ص���һ��ָ��map��value�Ķ���
			auto &lines = linesMap[word];
			if (!lines) {
				lines.reset(new set<lineNo>);
			}
			//�����к�
			lines->insert(n);
		}
	}
}

//��ʼ��ѯ
void TextQuery::runQuries() const {
	ifstream fileStream("D:\\AndroidDev\\CppSource\\MyApp\\outerfile\\MemoryExample.txt");
	runQuries(fileStream);
}

//��ʼ��ѯ
void TextQuery::runQuries(ifstream &fileStream) const {
	TextQuery memoryTest(fileStream);

	while (true) {
		cout << "������Ҫ��ѯ�ĵ��ʣ���������quit���˳���";
		string word;
		if (!(cin >> word) || word == "quit") {
			break;
		}

		//��ʼ��ѯ
		print(cout, memoryTest.query(word));
	}
}

QueryResult TextQuery::query(const string &word) const {
	//���û���ҵ�������һ���յĶ���
	shared_ptr<set<lineNo>> noData(new set<lineNo>);
	auto location = linesMap.find(word);
	if (location == linesMap.end()) {
		return QueryResult(word, noData, filesVectorP);
	}
	return QueryResult(word, location->second, filesVectorP);
}

TextQuery::~TextQuery() {
}

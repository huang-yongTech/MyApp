#include "pch.h"
#include "MemoryTest.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

//���캯������ȡ�����ļ������������ʵ��кŵ�mapӳ��
//����ΪfilesVectorP������һ���µ��ڴ�
MemoryTest::MemoryTest(ifstream &fileStream) :filesVectorP(new vector<string>) {
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
void MemoryTest::runQuries() const {
	ifstream fileStream("D:\\AndroidDev\\CppSource\\MyApp\\outerfile\\MemoryExample.txt");
	runQuries(fileStream);
}

//��ʼ��ѯ
void MemoryTest::runQuries(ifstream &fileStream) const {
	MemoryTest memoryTest(fileStream);

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

MemoryResult MemoryTest::query(const string &word) const {
	//���û���ҵ�������һ���յĶ���
	shared_ptr<set<lineNo>> noData(new set<lineNo>);
	auto location = linesMap.find(word);
	if (location == linesMap.end()) {
		return MemoryResult(word, noData, filesVectorP);
	}
	return MemoryResult(word, location->second, filesVectorP);
}

MemoryTest::~MemoryTest() {
}

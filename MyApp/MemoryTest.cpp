#include "pch.h"
#include "MemoryTest.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

//构造函数，读取输入文件，并建立单词到行号的map映射
//这里为filesVectorP分配了一个新的内存
MemoryTest::MemoryTest(ifstream &fileStream) :filesVectorP(new vector<string>) {
	//用于保存一行数据
	string lineText;
	while (getline(fileStream, lineText)) {
		filesVectorP->push_back(lineText);
		//当前行号
		lineNo n = filesVectorP->size() - 1;
		//将一行文本分解为单词
		istringstream linestream(lineText);
		string word;
		while (linestream >> word) {
			//如果单词不在linesMap中，使用下标添加，该下标返回的是一个指向map中value的对象
			auto &lines = linesMap[word];
			if (!lines) {
				lines.reset(new set<lineNo>);
			}
			//插入行号
			lines->insert(n);
		}
	}
}

//开始查询
void MemoryTest::runQuries() const {
	ifstream fileStream("D:\\AndroidDev\\CppSource\\MyApp\\outerfile\\MemoryExample.txt");
	runQuries(fileStream);
}

//开始查询
void MemoryTest::runQuries(ifstream &fileStream) const {
	MemoryTest memoryTest(fileStream);

	while (true) {
		cout << "请输入要查询的单词，或者输入quit来退出：";
		string word;
		if (!(cin >> word) || word == "quit") {
			break;
		}

		//开始查询
		print(cout, memoryTest.query(word));
	}
}

MemoryResult MemoryTest::query(const string &word) const {
	//如果没有找到，返回一个空的对象
	shared_ptr<set<lineNo>> noData(new set<lineNo>);
	auto location = linesMap.find(word);
	if (location == linesMap.end()) {
		return MemoryResult(word, noData, filesVectorP);
	}
	return MemoryResult(word, location->second, filesVectorP);
}

MemoryTest::~MemoryTest() {
}

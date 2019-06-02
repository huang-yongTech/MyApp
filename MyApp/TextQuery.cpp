#include "pch.h"
#include "TextQuery.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "DebugDelete.h"

//构造函数，读取输入文件，并建立单词到行号的map映射
//这里为filesVectorP分配了一个新的内存（并使用了我们自己定义的删除指针方法）
TextQuery::TextQuery(ifstream& fileStream) : filesVectorP(new vector<string>, DebugDelete()) {
	using resultType = map<string, shared_ptr<set<lineNo>>>::mapped_type;

	string lineText;
	while (getline(fileStream, lineText)) {
		//将文本一行一行的保存到集合中
		filesVectorP->push_back(lineText);
		//当前行号
		lineNo n = filesVectorP->size() - 1;
		//将一行文本分解为单词
		istringstream linestream(lineText);
		string word;
		while (linestream >> word) {
			//如果单词不在linesMap中，使用下标添加，该下标返回的是一个指向map中value的对象
			resultType& lines = linesMap[word];
			if (!lines) {
				lines.reset(new set<lineNo>);
			}
			//插入行号
			lines->insert(n);
		}
	}
}

//开始查询
void TextQuery::runQuries() const {
	ifstream fileStream("D:\\AndroidDev\\CppSource\\MyApp\\outerfile\\MemoryExample.txt");
	runQuries(fileStream);
}

//开始查询
void TextQuery::runQuries(ifstream& fileStream) const {
	TextQuery memoryTest(fileStream);

	while (true) {
		cout << "请输入要查询的单词，或者输入quit来退出：";
		string word;
		if (!(cin >> word) || word == "quit") {
			break;
		}

		//开始查询
		cout << memoryTest.query(word) << endl;
	}
}

//在运行这个方法之前，首先要建立文件单词与行号的map映射
QueryResult TextQuery::query(const string& word) const {
	//如果没有找到，返回一个空的对象
	shared_ptr<set<lineNo>> noData(new set<lineNo>);

	map<string, shared_ptr<set<lineNo>>>::const_iterator location = linesMap.find(word);
	if (location == linesMap.end()) {
		return QueryResult(word, noData, filesVectorP);
	}
	return QueryResult(word, location->second, filesVectorP);
}

TextQuery::~TextQuery() {
}

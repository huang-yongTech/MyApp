#include "pch.h"
#include "MapTest.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

MapTest::~MapTest() {
}

void MapTest::wordTransform() const {
	ifstream fileStream("D:\\AndroidDev\\CppSource\\convert.txt");
	ifstream inputStream("D:\\AndroidDev\\CppSource\\source.txt");

	if (fileStream && inputStream) {
		cout << "开始单词转换" << endl;
		wordTransform(fileStream, inputStream);
	}
}

//将需要转换的单词按转换规则转换，并打印
void MapTest::wordTransform(ifstream &fileStream, ifstream &inputStream) const {
	//获取转换规则map
	auto transMap = buildMap(fileStream);

	//保存输入流读取的一行文本
	string text;

	while (getline(inputStream, text)) {
		istringstream stream(text);
		string word;

		bool firstWord = true;
		while (stream >> word) {
			if (firstWord) {
				firstWord = false;
			} else {
				cout << " ";
			}

			//打印单词
			cout << transform(word, transMap);
		}
		//处理完一行后换行
		cout << endl;
	}
}

//构建转换规则map
map<string, string> MapTest::buildMap(ifstream &fileStream) const {
	map<string, string> transMap;
	string key;
	string value;

	while (fileStream >> key && getline(fileStream, value)) {
		if (value.size() > 1) {
			transMap.insert(make_pair(key, value.substr(1)));
		} else {
			throw runtime_error("单词" + key + "没有匹配的转换规则");
		}
	}

	return transMap;
}

//开始转换单词
const string & MapTest::transform(const string &s, map<string, string> &convertMap) const {
	auto ptr = convertMap.find(s);

	if (ptr != convertMap.cend()) {
		return ptr->second;
	} else {
		return s;
	}
}


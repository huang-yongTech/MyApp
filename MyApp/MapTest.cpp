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
		cout << "��ʼ����ת��" << endl;
		wordTransform(fileStream, inputStream);
	}
}

//����Ҫת���ĵ��ʰ�ת������ת��������ӡ
void MapTest::wordTransform(ifstream &fileStream, ifstream &inputStream) const {
	//��ȡת������map
	auto transMap = buildMap(fileStream);

	//������������ȡ��һ���ı�
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

			//��ӡ����
			cout << transform(word, transMap);
		}
		//������һ�к���
		cout << endl;
	}
}

//����ת������map
map<string, string> MapTest::buildMap(ifstream &fileStream) const {
	map<string, string> transMap;
	string key;
	string value;

	while (fileStream >> key && getline(fileStream, value)) {
		if (value.size() > 1) {
			transMap.insert(make_pair(key, value.substr(1)));
		} else {
			throw runtime_error("����" + key + "û��ƥ���ת������");
		}
	}

	return transMap;
}

//��ʼת������
const string & MapTest::transform(const string &s, map<string, string> &convertMap) const {
	auto ptr = convertMap.find(s);

	if (ptr != convertMap.cend()) {
		return ptr->second;
	} else {
		return s;
	}
}


#pragma once
#include <map>
#include "MemoryResult.h"

using namespace std;

class MemoryTest {
public:
	using lineNo = vector<string>::size_type;

	MemoryTest() = default;
	MemoryTest(ifstream &fileStream);

	//查询单词
	MemoryResult query(const string &word) const;

	void runQuries() const;

	void runQuries(ifstream &fileStream) const;

	~MemoryTest();

private:
	//这里使用指针是为了避免拷贝，以免文件内容过大导致内存溢出
	map<string, shared_ptr<set<lineNo>>> linesMap;//单词与其所在行号的映射
	shared_ptr<vector<string>> filesVectorP;//输入文件
};


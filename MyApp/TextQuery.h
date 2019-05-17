#ifndef _MEMORY_TEST_H_
#define _MEMORY_TEST_H_

#include <map>
#include "QueryResult.h"

class TextQuery {

public:
	using lineNo = vector<string>::size_type;

	TextQuery() = default;

	TextQuery(ifstream &fileStream);

	//查询单词
	QueryResult query(const string &word) const;

	void runQuries() const;

	void runQuries(ifstream &fileStream) const;

	~TextQuery();

private:
	//这里使用指针是为了避免拷贝，以免文件内容过大导致内存溢出
	map<string, shared_ptr<set<lineNo>>> linesMap;//单词与其所在行号的映射

	shared_ptr<vector<string>> filesVectorP;//输入文件
};

#endif


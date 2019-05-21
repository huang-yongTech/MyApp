#ifndef _MEMORY_TEST_H_
#define _MEMORY_TEST_H_

#include <map>
#include "QueryResult.h"

class TextQuery {

public:
	using lineNo = std::vector<std::string>::size_type;

	TextQuery() = default;

	TextQuery(std::ifstream& fileStream);

	//查询单词
	QueryResult query(const std::string& word) const;

	void runQuries() const;

	void runQuries(std::ifstream& fileStream) const;

	~TextQuery();

private:
	//这里使用指针是为了避免拷贝，以免文件内容过大导致内存溢出
	//单词与其所在行号的映射,一个单词可能会出现在多行，同一行的单词只显示一次
	std::map<std::string, std::shared_ptr<std::set<lineNo>>> linesMap;

	std::shared_ptr<std::vector<std::string>> filesVectorP;//输入文件
};

#endif


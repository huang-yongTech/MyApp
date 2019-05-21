#ifndef _MEMORY_TEST_H_
#define _MEMORY_TEST_H_

#include <map>
#include "QueryResult.h"

class TextQuery {

public:
	using lineNo = std::vector<std::string>::size_type;

	TextQuery() = default;

	TextQuery(std::ifstream& fileStream);

	//��ѯ����
	QueryResult query(const std::string& word) const;

	void runQuries() const;

	void runQuries(std::ifstream& fileStream) const;

	~TextQuery();

private:
	//����ʹ��ָ����Ϊ�˱��⿽���������ļ����ݹ������ڴ����
	//�������������кŵ�ӳ��,һ�����ʿ��ܻ�����ڶ��У�ͬһ�еĵ���ֻ��ʾһ��
	std::map<std::string, std::shared_ptr<std::set<lineNo>>> linesMap;

	std::shared_ptr<std::vector<std::string>> filesVectorP;//�����ļ�
};

#endif


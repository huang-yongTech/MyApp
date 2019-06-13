#ifndef _MAP_TEST_H_
#define _MAP_TEST_H_

#include <map>
#include <fstream>

using namespace std;

//11.3.6С��
class MapTest {
public:
	MapTest() = default;
	~MapTest();

	void wordTransform() const;

	/*
	����Ҫת���ĵ���ת�����򻻣������ת����ĵ���
	*/
	void wordTransform(ifstream &fileStream, ifstream &inputStream) const;

	/*
	��������ת������map
	*/
	map<string, string> buildMap(ifstream &fileStream) const;

	/*
	��ʼת��
	*/
	const string & transform(const string &s, map<string, string> &convertMap) const;
};

#endif


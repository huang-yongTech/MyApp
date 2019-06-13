#ifndef _MAP_TEST_H_
#define _MAP_TEST_H_

#include <map>
#include <fstream>

using namespace std;

//11.3.6小节
class MapTest {
public:
	MapTest() = default;
	~MapTest();

	void wordTransform() const;

	/*
	将需要转换的单词转按规则换，并输出转换后的单词
	*/
	void wordTransform(ifstream &fileStream, ifstream &inputStream) const;

	/*
	建立单词转换规则map
	*/
	map<string, string> buildMap(ifstream &fileStream) const;

	/*
	开始转换
	*/
	const string & transform(const string &s, map<string, string> &convertMap) const;
};

#endif


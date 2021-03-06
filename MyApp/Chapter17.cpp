#include "pch.h"
#include "Chapter17.h"
#include <fstream>
#include <random>

using namespace std;

void Chapter17::regexPhone() {
	//匹配规则
	//string patten = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	string patten = "(\\()?(\\d{3})(\\))?([ ]*)?(\\d{3})([ ]*)?(\\d{4})";
	regex r(patten);
	string s;

	bool validRecord = false;

	cout << "please enter phone number,enter 'q' to exit:" << endl;
	while (getline(cin, s)) {
		if (s == "q") {
			break;
		}

		for (sregex_iterator it(s.begin(), s.end(), r), it_end; it != it_end; ++it) {
			validRecord = true;

			if (validPhone(*it)) {
				cout << "valid: " << it->str() << endl;
			} else {
				cout << "not valid: " << it->str() << endl;
			}
		}

		if (!validRecord) {
			cout << "not a valid record!please enter new phone number,or enter 'q' to exit:" << endl;
		}
	}
}

bool Chapter17::validPhone(const smatch& m) {
	if (m[1].matched) {
		//return m[3].matched &&
		//	(m[4].matched == 0 || m[4].str() == " ");
		return m[3].matched;
	} else {
		//return !m[3].matched &&
		//	(m[4].str() == m[6].str());
		return !m[3].matched;
	}
}

void Chapter17::regexPostCode() {
	string postCode = "(\\d{5})([-])?(\\d{4})?";
	regex r(postCode);

	string s;
	bool validRecord = false;

	cout << "please enter post code,enter 'q' to exit:" << endl;
	while (getline(cin, s)) {
		if (s == "q") {
			break;
		}

		for (sregex_iterator it(s.begin(), s.end(), r), it_end; it != it_end; ++it) {
			validRecord = true;

			if (validPostCode(*it)) {
				cout << "valid post code" << endl;
			} else {
				cout << "not a valid post code" << endl;
			}
		}

		if (!validRecord) {
			cout << "not a valid record!please enter new phone number,or enter 'q' to exit:" << endl;
		}
	}
}

bool Chapter17::validPostCode(const smatch& m) {
	if (m[2].matched) {
		return m[3].matched;
	} else {
		return !m[3].matched;
	}
}

void Chapter17::regexReplaceNum() {
	string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	regex r(phone);

	string fmt = "$2.$5.$7";
	string s;
	ifstream fileStream("D:\\AndroidDev\\CppSource\\MyApp\\outerfile\\record.txt");

	while (getline(fileStream, s)) {
		cout << regex_replace(s, r, fmt) << endl;
	}
}

void Chapter17::randomNumber() {
	//在实际开发中，需要将随机数引擎和随机数发生器声明为static，
	//只有这样程序每次运行时，均会生成不同的随机数
	default_random_engine e;
	uniform_int_distribution<unsigned> u(0, 9);
	cout << u(e) << endl;
}

void Chapter17::randomNumber(unsigned long seed) {
	default_random_engine e(seed);
	uniform_int_distribution<unsigned> u(0, 9);
	cout << u(e) << endl;
}

void Chapter17::randomNumber(unsigned long seed, unsigned long min, unsigned long max) {
	//好像声明为static每次也会生成相同的随机序列
	static default_random_engine e(seed);
	static uniform_int_distribution<unsigned> u(min, max);

	for (int i = 0; i < 3; ++i) {
		cout << u(e) << ",";
	}
	cout << endl;
}

void Chapter17::seekStream() {
	fstream inOutStream("..\\outerfile\\copyOut.txt", fstream::in | fstream::out | fstream::ate);
	if (!inOutStream) {
		cerr << "打开文件出错！" << endl;
		return;
	}

	inOutStream << "\n";

	fstream::pos_type endMark = inOutStream.tellg();
	inOutStream.seekg(0, fstream::beg);

	string line;
	//记录当前读取的一行大小
	size_t currSize = 0;
	while (inOutStream.tellg() != endMark && getline(inOutStream, line)) {
		currSize += line.size() + 1;
		fstream::pos_type currMark = inOutStream.tellg();

		inOutStream.seekp(0, fstream::end);
		inOutStream << currSize;
		
		//如果没有读取到最后一行，则输入空格
		if (currMark != endMark) {
			inOutStream << " ";
		}

		inOutStream.seekg(currMark);
	}

	inOutStream.seekp(0, fstream::end);
}



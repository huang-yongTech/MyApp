#include "pch.h"
#include "Chapter17.h"
#include <fstream>

using namespace std;

void Chapter17::regexPhone() {
	//∆•≈‰πÊ‘Ú
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



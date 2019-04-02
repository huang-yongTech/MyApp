#include "pch.h"
#include "Folder.h"
#include <iostream>

using namespace std;

Folder::Folder() {
}

Folder::Folder(const Folder& folder) :messageSet(folder.messageSet) {
}

Folder& Folder::operator=(const Folder& folder) {
	messageSet = folder.messageSet;

	return *this;
}

Folder::~Folder() {
}

//Message��ʹ����addMessage(this)���������Ĳ�����Ҫʹ��ָ��
void Folder::addMessage(Message *message) {
	cout << "ִ��folder��addMessage����" << endl;
	//���ﱨ����ȡ����Ȩ�޳�ͻ
	messageSet.insert(message);
}

void Folder::removeMessage(Message *message) {
	messageSet.erase(message);
}

void Folder::print() {
	cout << "Folder�д洢����Ϣ��С��" << endl;
	cout << "��Ϣ���ݣ� " << endl;
	for (auto message : messageSet) {
		cout << message->content;
	}
}
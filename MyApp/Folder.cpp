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

//Message中使用了addMessage(this)，因此这里的参数需要使用指针
void Folder::addMessage(Message *message) {
	cout << "执行folder类addMessage函数" << endl;
	//这里报错：读取访问权限冲突
	messageSet.insert(message);
}

void Folder::removeMessage(Message *message) {
	messageSet.erase(message);
}

void Folder::print() {
	cout << "Folder中存储的消息大小：" << endl;
	cout << "消息内容： " << endl;
	for (auto message : messageSet) {
		cout << message->content;
	}
}
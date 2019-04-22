#include "pch.h"
#include "Message.h"
#include <iostream>

using namespace std;

Message::Message(const string& content) : content(content) {
}

//�������캯��������һ���µĶ���
Message::Message(const Message& message) : content(message.content), folderSet(message.folderSet) {
	cout << "���ÿ������캯��" << endl;

	addToFolders(message);
}

//������ֵ��������ڽ��Ҳ���󿽱���������֮ǰ����Ҫ������message��folderSet��ɾ����
//������ɺ��ٽ�����ӵ�folderSet��
Message& Message::operator=(const Message& message) {
	cout << "���ÿ�����ֵ�����" << endl;

	removeFromFolders();
	content = message.content;
	folderSet = message.folderSet;
	addToFolders(message);

	return *this;
}

Message::~Message() {
	//removeFromFolders();
}

//����message��ӵ�ָ��folder�У�����folder��ӵ�folder������
void Message::save(Folder& folder) {
	folderSet.insert(&folder);
	folder.addMessage(this);
}

//��folder������ɾ����message
void Message::remove(Folder& folder) {
	folderSet.erase(&folder);
	folder.removeMessage(this);
}

void Message::print() {
	cout << "��ӡMessage----" << endl;

	cout << "���ڵ��ļ��д�С:" << folderSet.size() << endl;
	for (auto folder : folderSet) {
		folder->print();
	}
}

//������Ϣ��ӵ�ָ��������ļ�����
void Message::addToFolders(const Message& message) {
	cout << "message����folderSet��С��" << message.folderSet.size() << endl;
	for (Folder* folder : message.folderSet) {
		folder->addMessage(this);
	}
}

//������Ϣ���ļ������Ƴ�
void Message::removeFromFolders() {
	for (Folder* folder : folderSet) {
		folder->removeMessage(this);
	}
}

//�Զ����swap����
void swap(Message& leftMsg, Message& rightMsg) {
	using std::swap;

	//����֮ǰҪ�Ƚ�����message��֮ǰ��folderSet��ɾ��
	for (Folder* folder : leftMsg.folderSet) {
		folder->removeMessage(&leftMsg);
	}

	for (Folder* folder : rightMsg.folderSet) {
		folder->removeMessage(&rightMsg);
	}

	swap(leftMsg.content, rightMsg.content);
	swap(leftMsg.folderSet, rightMsg.folderSet);

	//������Ϻ��ٽ�������ӵ����ڵ�folderSet��
	for (Folder* folder : leftMsg.folderSet) {
		folder->addMessage(&leftMsg);
	}

	for (Folder* folder : rightMsg.folderSet) {
		folder->addMessage(&rightMsg);
	}
}
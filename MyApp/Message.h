#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>
#include <set>
#include "Folder.h"

class Message {

	friend class Folder;

	friend void swap(Message& leftMsg, Message& rightMsg);

public:
	//����Ϊexplicit�Ĺ��캯������Ҫ��ͷ�ļ���ɶ��壬������Դ�ļ�����ȥ���壬��������
	Message(const std::string& content);

	Message(const Message& message);

	Message& operator=(const Message& message);

	~Message();

	void save(Folder &folder);

	void remove(Folder& folder);

	void print();

private:

	std::string content;
	std::set<Folder*> folderSet;

	void addToFolders(const Message& message);

	void removeFromFolders();
};

void swap(Message& leftMsg, Message& rightMsg);

#endif
#pragma once

#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "include/ISubscribe.h"

class TestClass :public ISubscribe
{
public:
	TestClass(std::string name)
		: instanceName(name)
	{
	}

	/*
	  メッセージ受信
	*/
	void ReceiveMessage(std::string message)
	{
		// メッセージを表示
		std::cout << "name:" << instanceName << " message:" << message << "\n";
	}

private:
	std::string instanceName;

};

#endif //TESTCLASS_H
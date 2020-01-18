#pragma once

#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "ISubscribe.h"

class TestClass :public ISubscribe
{
public:
	TestClass(std::string name)
		: instanceName(name)
	{
	}

	/*
	  ���b�Z�[�W��M
	*/
	void ReceiveMessage(std::string message)
	{
		// ���b�Z�[�W��\��
		std::cout << "name:" << instanceName << " message:" << message << "\n";
	}

private:
	std::string instanceName;

};

#endif //TESTCLASS_H
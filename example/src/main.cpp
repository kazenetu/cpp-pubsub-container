#include <memory>
#include "../include/TestClass.h"
#include "PubSubContainer.h"

int main()
{
	// TestClassインスタンスを生成
	auto test1 = std::make_unique<TestClass>("TEST1");
	auto test2 = std::make_unique<TestClass>("TEST2");

	// 購読登録
	PubSubContainer::Add(test1.get());
	PubSubContainer::Add(test2.get());


	// 発行
	PubSubContainer::Publish("Publish");
}


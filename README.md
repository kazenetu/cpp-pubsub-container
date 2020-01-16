# C++用簡易pub/subコンテナ
簡易的なPublish/Subscribeメッセージ機能

# 主な特徴
* ISubscribeを継承したクラスのみSubscribe(購読:受信)として登録可能。
* Publish(出版:送信)はどの処理からでも実行可能。

# 利用方法
* Visual Studioでの利用方法
   * 「追加のインクルードディレクトリ」に「include」ディレクトリを追加
   * 「include/PubSubContainer.cpp」をプロジェクトに追加

# 実装例
## Subscribe(購読:受信)用クラス
```cpp
#pragma once

#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "include/ISubscribe.h"

class TestClass :public ISubscribe
{
public:
	TestClass(std::string name)
		: instanceName(name) {
	}

	/*
	  メッセージ受信
	*/
	void ReceiveMessage(std::string message) {
		// メッセージを表示
		std::cout << "name:" << instanceName << " message:" << message << "\n";
	}

private:
	std::string instanceName;

};
#endif //TESTCLASS_H
```


## 利用例
```cpp
#include "TestClass.h"
#include "include/PubSubContainer.h"

int main() {
	// TestClassインスタンスを生成
	auto test1 = std::make_unique<TestClass>("TEST1");
	auto test2 = std::make_unique<TestClass>("TEST2");

	// 購読登録
	PubSubContainer::Add(test1.get());
	PubSubContainer::Add(test2.get());


	// 発行
	PubSubContainer::Publish("Publish");

}
```
```sh
# 実行結果
name:TEST2 message:Publish
name:TEST1 message:Publish
```
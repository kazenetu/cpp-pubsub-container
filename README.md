# C++用簡易pub/subコンテナ
簡易的なPublish/Subscribeメッセージ機能

# 主な特徴
* ISubscribeを継承したクラスのみSubscribe(購読:受信)として登録可能。
* Publish(出版:送信)はどの処理からでも実行可能。
* スタティックライブラリとして実装。

# 機能詳細
|クラス・メソッド|概要|備考|
|---------------|-----------|-----------|
|ISubscribe|Subscribe(購読:受信)クラス継承用<br>スーパークラス|・public継承<br>・void ReceiveMessage(std::string message)の実装が必要|
|PubSubContainer::Add(ISubscribe* instance)|Subscribe(購読:受信)インスタンス追加|追加したインスタンスに対してpublishしたメッセージが送信される|
|PubSubContainer::Publish(std::string message)|追加したSubscribeインスタンスに対してメッセージを一斉送信する|SubscribeインスタンスのReceiveMessageメソッドが呼び出される|
|PubSubContainer::Remove(ISubscribe* instance)|追加済みSubscribeインスタンスを送信対象から除外する|第一パラメータに除外対象のSubscribeインスタンスを指定する|
|PubSubContainer::RemoveAll()|追加済みSubscribeインスタンス全てを送信対象から除外する||


# 実装例
## Subscribe(購読:受信)用クラス:**example/class/TestClass.h**
```cpp
#pragma once

#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "ISubscribe.h"

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


## 利用例:**example/main.cpp**
```cpp
#include "class/TestClass.h"
#include "PubSubContainer.h"

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

# ビルド(コンパイル)方法
* Visual Studioでのビルド方法  
  **本ライブラリを使用するプロジェクトは下記を設定する。**  
  ※詳細は[example](example/)を参照
   * 対象ソリューションにpubsub-container」プロジェクトを追加 (同時にライブラリのビルドを行う場合)

   * 「プロジェクトの依存関係」で「pubsub-container」プロジェクトにチェック (同時にライブラリのビルドを行う場合)

   * 「C/C++」の「追加のインクルードディレクトリ」に  
     「pubsub-container/include」ディレクトリを追加

   * 「リンカー」－「入力」の「追加の依存ファイル」に  
     「$(SolutionDir)$(Platform)\$(Configuration)\pubsub-container.lib」を追加

* makeでのコンパイル・リンク方法  
 1. 事前手順：簡易pub/subコンテナのコンパイル
    * pubsub-containerをスタティックライブラリとしてコンパイルする  
	  ※```./lib/libpubsub.a```が作成される  
	  ```sh
	  cd pubsub-container
	  make clean
      make
	  ```
 1. ライブラリ使用側のコンパイル・リンク  
  **本ライブラリを使用する場合は下記を設定する。**  
  [example/makefile](example/makefile)を参照  
    ```makefile
	#!/bin/make

	# build directory
	SRCPATH := ./src

	BUILDPATH := ./build
	BINPATH := ./bin
	BINNAME := example.out

	CXX := g++
	INCLUDE := -I /usr/local/include -I /usr/include -I./include -I../pubsub-container/include #追加1
	CXXFLAGS := -Wall -O2 
	LDFLAGS := -L /usr/lib -L /usr/local/lib -L ../pubsub-container/lib #追加2
	LIBS := -lpubsub #追加3
	SRCS := $(shell find $(SRCPATH) -name '*.cpp')
	OBJS :=  $(patsubst $(SRCPATH)/%,$(BUILDPATH)/%,$(SRCS:.cpp=.o))

	$(BINPATH)/$(BINNAME):$(OBJS)
		mkdir -p $(BINPATH)
		$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

	$(BUILDPATH)/%.o : $(SRCPATH)/%.cpp
		mkdir -p  $(BUILDPATH)
		$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ -c $^

	.PHONY: clean
	
	clean:
		rm -rf $(BUILDPATH)
		rm -rf $(BINPATH)  
    ```  
   **追加内容**  
   1. cppファイルコンパイル時のincludeディレクトリに```pubsub-container/include```を追加

   1. cppファイルコンパイル時とリンク時のライブラリディレクトリに```pubsub-container/lib```を追加
   
   1. リンク時のスタティックライブラリに```libpubsub.a```を追加  
   ※```-lpubsub```と省略

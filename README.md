# C++用簡易pub/subコンテナ
簡易的なPublish/Subscribeメッセージ機能

# 主な特徴
* ISubscribeを継承したクラスのみSubscribe(購読:受信)として登録可能。
* Publish(出版:送信)はどの処理からでも実行可能。
* スタティックライブラリとして実装。

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

# 利用方法
* Visual Studioでの利用方法  
  **本ライブラリを利用するプロジェクトは下記を設定する。**  
  ※詳細は[example](example/)を参照
   * 対象ソリューションにpubsub-container」プロジェクトを追加 (同時にライブラリのビルドを行う場合)

   * 「プロジェクトの依存関係」で「pubsub-container」プロジェクトにチェック (同時にライブラリのビルドを行う場合)

   * 「C/C++」の「追加のインクルードディレクトリ」に  
     「pubsub-container/include」ディレクトリを追加

   * 「リンカー」－「入力」の「追加の依存ファイル」に  
     「$(SolutionDir)$(Platform)\$(Configuration)\pubsub-container.lib」を追加

* makeコマンドでの利用方法  
  1. 事前手順：簡易pub/subコンテナのコンパイル
    * pubsub-containerをスタティックライブラリとしてコンパイルする  
	  ※```./lib/libpubsub.a```が作成される  
	  ```sh
	  cd pubsub-container
	  make clean
      make
	  ```
  1. 利用側のコンパイル  
  **本ライブラリを利用する場合は下記を設定する。**  
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
		rm -r $(BUILDPATH)
		rm -r $(BINPATH)  
    ```  
	**追加内容**  
   1. cppファイルコンパイル時のincludeディレクトリに```pubsub-container/include```を追加

   1. cppファイルコンパイル時とリンク時のライブラリディレクトリに```pubsub-container/lib```を追加
   
   1. リンク時のスタティックライブラリに```libpubsub.a```を追加  
   ※```-lpubsub```と省略

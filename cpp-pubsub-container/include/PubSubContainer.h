#pragma once

#ifndef PUBSUBCONTAINER_H
#define PUBSUBCONTAINER_H

#include <map>
#include <functional>
#include <iostream>
#include "ISubscribe.h"

/*
  pub/sub簡易コンテナ(ヘッダーオンリー)
*/
class PubSubContainer
{
public:
    /*
      購読の追加
    */
    static void Add(ISubscribe* instance)
    {
        // 追加済み確認
        if (container.find(instance) != container.end()) {
            // すでにメソッド登録済みで有効の場合
            if (container[instance]) {
                // HACK 例外エラー：すでに存在
                return;
            }
        }

        // 追加
        container[instance] = true;
    }

    /*
      購読の削除
    */
    static void Remove(ISubscribe* instance)
    {
        // 存在確認
        if (container.find(instance) == container.end()) {
            // HACK 例外エラー：削除対象なし
            return;
        }

        // 論理削除
        container[instance] = false;
    }

    /*
      購読の全削除
    */
    static void RemoveAll()
    {
        // 物理削除
        container.clear();
    }

    /*
      発行
    */
    static void Publish(std::string message)
    {
        for (auto item = container.cbegin(); item != container.cend(); ++item) {
            // 有効なメソッドのみ実行
            if (item->second) {
                item->first->ReceiveMessage(message);
            }
        }
    }

private:
    /*
      コンテナ本体
    */
    static std::map<ISubscribe*, bool> container;
};

#ifndef PUBSUB_INIT
// 実体化
std::map<ISubscribe*, bool> PubSubContainer::container{};
#define PUBSUB_INIT
#endif

#endif //PUBSUBCONTAINER_H
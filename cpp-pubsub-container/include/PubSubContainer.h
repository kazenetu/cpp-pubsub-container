#pragma once

#ifndef PUBSUBCONTAINER_H
#define PUBSUBCONTAINER_H

#include <map>
#include <functional>
#include <iostream>

/*
  pub/sub簡易コンテナ(ヘッダーオンリー)
*/
class PubSubContainer
{
public:
    /*
      購読の追加
    */
    void Add(std::function<void(std::string)> method)
    {
        // 追加済み確認
        if (container.find(method) != container.end()) {
            // すでにメソッド登録済みで有効の場合
            if (container[method]) {
                // HACK 例外エラー：すでに存在
                return;
            }
        }

        // 追加
        container[method] = true;
    }

    /*
      購読の削除
    */
    void Remove(std::function<void(std::string)> method)
    {
        // 存在確認
        if (container.find(method) == container.end()) {
            // HACK 例外エラー：削除対象なし
            return;
        }

        // 論理削除
        container[method] = false;
    }

    /*
      購読の全削除
    */
    void RemoveAll()
    {
        // 物理削除
        container.clear();
    }

    /*
      発行
    */
    void Publish(std::string message)
    {
        for (auto item = container.cbegin(); item != container.cend(); ++item) {
            // 有効なメソッドのみ実行
            if (item->second) {
                item->first(message);
            }
        }
    }

private:
    /*
      コンテナ本体
    */
    static std::map<std::function<void(std::string)>,bool> container;
};

#ifdef PUBSUB_INIT
// 実体化
std::map<std::function<void(std::string)>, bool> PubSubContainer::container{};
#endif

#endif //PUBSUBCONTAINER_H
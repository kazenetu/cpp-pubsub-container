#pragma once

#ifndef ISUBSCRIBE_H
#define ISUBSCRIBE_H

#include <iostream>

/*
  購読用インターフェースクラス
*/
class ISubscribe
{
public:

    /*
      メッセージ受信
    */
    virtual void ReceiveMessage(std::string message) {};
};

#endif //ISUBSCRIBE_H
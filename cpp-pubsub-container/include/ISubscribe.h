#pragma once

#ifndef ISUBSCRIBE_H
#define ISUBSCRIBE_H

#include <iostream>

/*
  �w�Ǘp�C���^�[�t�F�[�X�N���X
*/
class ISubscribe
{
public:

    /*
      ���b�Z�[�W��M
    */
    virtual void ReceiveMessage(std::string message) {};
};

#endif //ISUBSCRIBE_H
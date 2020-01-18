#pragma once

#ifndef PUBSUBCONTAINER_H
#define PUBSUBCONTAINER_H

#include <map>
#include "ISubscribe.h"

/*
  pub/sub�ȈՃR���e�i
*/
class PubSubContainer
{
public:
    /*
      �w�ǂ̒ǉ�
    */
    static void Add(ISubscribe* instance)
    {
        // �ǉ��ς݊m�F
        if (container.find(instance) != container.end()) {
            // ���łɃ��\�b�h�o�^�ς݂ŗL���̏ꍇ
            if (container[instance]) {
                // HACK ��O�G���[�F���łɑ���
                return;
            }
        }

        // �ǉ�
        container[instance] = true;
    }

    /*
      �w�ǂ̍폜
    */
    static void Remove(ISubscribe* instance)
    {
        // ���݊m�F
        if (container.find(instance) == container.end()) {
            // HACK ��O�G���[�F�폜�ΏۂȂ�
            return;
        }

        // �_���폜
        container[instance] = false;
    }

    /*
      �w�ǂ̑S�폜
    */
    static void RemoveAll()
    {
        // �����폜
        container.clear();
    }

    /*
      ���s
    */
    static void Publish(std::string message)
    {
        for (auto item = container.cbegin(); item != container.cend(); ++item) {
            // �L���ȃ��\�b�h�̂ݎ��s
            if (item->second) {
                item->first->ReceiveMessage(message);
            }
        }
    }

private:
    /*
      �R���e�i�{��
    */
    static std::map<ISubscribe*, bool> container;
};

#endif //PUBSUBCONTAINER_H
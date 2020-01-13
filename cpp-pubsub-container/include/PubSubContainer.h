#pragma once

#ifndef PUBSUBCONTAINER_H
#define PUBSUBCONTAINER_H

#include <map>
#include <functional>
#include <iostream>

/*
  pub/sub�ȈՃR���e�i(�w�b�_�[�I�����[)
*/
class PubSubContainer
{
public:
    /*
      �w�ǂ̒ǉ�
    */
    static void Add(std::function<void(std::string)> method)
    {
        // �ǉ��ς݊m�F
        if (container.find(method) != container.end()) {
            // ���łɃ��\�b�h�o�^�ς݂ŗL���̏ꍇ
            if (container[method]) {
                // HACK ��O�G���[�F���łɑ���
                return;
            }
        }

        // �ǉ�
        container[method] = true;
    }

    /*
      �w�ǂ̍폜
    */
    static void Remove(std::function<void(std::string)> method)
    {
        // ���݊m�F
        if (container.find(method) == container.end()) {
            // HACK ��O�G���[�F�폜�ΏۂȂ�
            return;
        }

        // �_���폜
        container[method] = false;
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
                item->first(message);
            }
        }
    }

private:
    /*
      �R���e�i�{��
    */
    static std::map<std::function<void(std::string)>,bool> container;
};

#ifdef PUBSUB_INIT
// ���̉�
std::map<std::function<void(std::string)>, bool> PubSubContainer::container{};
#endif

#endif //PUBSUBCONTAINER_H
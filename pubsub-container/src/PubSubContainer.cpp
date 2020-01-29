#include "../include/PubSubContainer.h"

// 実体化
std::map<ISubscribe*, bool> PubSubContainer::container{};

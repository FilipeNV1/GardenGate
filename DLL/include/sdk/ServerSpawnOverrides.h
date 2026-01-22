#pragma once

#include "LevelSetup.h"
#include "ISocketManager.h"

namespace fb
{
    struct ServerSpawnOverrides
    {
        LevelSetup *levelSetup;
        ISocketManager *socketManager;
        intptr_t connectionCreator;
        intptr_t peerCreator;
    };
}
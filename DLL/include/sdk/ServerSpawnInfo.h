#pragma once

#include "sdk/LevelSetup.h"

namespace fb
{
    struct ServerSpawnInfo
    {
        ServerSpawnInfo(LevelSetup &setup)
            : levelSetup(setup)
        {
        }

        void *fileSystem = nullptr;
        void *damageArbitrator = nullptr;
        void *playerManager = nullptr;
        LevelSetup &levelSetup;
        unsigned int tickFrequency = 0;
        bool isSinglePlayer = false;
        bool isLocalHost = false;
        bool isDedicated = false;
        bool isEncrypted = false;
        bool isCoop = false;
        bool isMenu = false;
        bool keepResources = false;
        void *saveData;
        void *serverCallbacks = nullptr;
        void *runtimeModules = nullptr;
    };
}

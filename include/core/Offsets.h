#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "core/Util.h"

#define DEFINE_INSTANCE(name, addr) inline constexpr std::uintptr_t g_##name  = (addr)
#define DEFINE_FUNCTION(name, addr) inline constexpr std::uintptr_t fn_##name = (addr)
#define DEFINE_PATCH(name, addr, data) inline constexpr auto patch_##name = Patch<std::tuple_size_v<decltype(data)>>{ (addr), (data) }

namespace offsets
{
    namespace gw1 {
        //--- PvZ: GW1
        DEFINE_INSTANCE(AppId, 0x141578300);

        DEFINE_FUNCTION(GetOptionParameter, 0x1403A97D0);
        DEFINE_FUNCTION(ServerStart, 0x1406f8f80);
        DEFINE_FUNCTION(ClientInitNetwork, 0x140541740);
        DEFINE_FUNCTION(ClientConnectToAddress, 0x140559CD0);
        DEFINE_FUNCTION(NetworkEnginePeerInit, 0x1408038F0);
        DEFINE_FUNCTION(PeerHasJoined, 0x14075B800);
        DEFINE_FUNCTION(ClientDisconnect, 0x1405BF3D0);
        DEFINE_FUNCTION(ClientInactivityTimer, 0x140C00470);
        DEFINE_FUNCTION(GetPlayerName, 0x1403A9170);

        DEFINE_PATCH(AllowCommandArgumentsAsOptions, 0x14000D3FA, (std::array<std::uint8_t, 1>{ 0xDE }));
        DEFINE_PATCH(FixLevelReportInstanceIndex, 0x140AE8B99, (std::array<std::uint8_t, 3>{ 0x6A, 0x03, 0x5B }));
        DEFINE_PATCH(FixAvailableConsumables, 0x140B3F69D, (std::array<std::uint8_t, 1>{ 0xC9 }));
        DEFINE_PATCH(FixHolidayConsumables, 0x140B3F615, (std::array<std::uint8_t, 6>{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90}));
    }

    namespace gw2 {
        //--- PvZ: GW2
        DEFINE_INSTANCE(AppId, 0x1421A0A28);

        DEFINE_FUNCTION(GetOptionParameter, 0x1401C51E0);
        DEFINE_FUNCTION(ServerStart, 0x1405D5FE0);
        DEFINE_FUNCTION(ClientInitNetwork, 0x140444B50);
        DEFINE_FUNCTION(ClientConnectToAddress, 0x14054ABE0);
        DEFINE_FUNCTION(NetworkEnginePeerInit, 0x14070CF70);
        DEFINE_FUNCTION(ClientDisconnected, 0x14054B6E0);
        DEFINE_FUNCTION(PeerHasJoined, 0x140616DC0);
        DEFINE_FUNCTION(GetPlayerName, 0x1401F7C00);

        DEFINE_PATCH(AllowCommandArgumentsAsOptions, 0x1401328DA, (std::array<std::uint8_t, 1>{ 0xE6 }));
        DEFINE_PATCH(PlayerNameFormatting, 0x1422DC782, (std::array<std::uint8_t, 3>{ 0x00, 0x00, 0x00}));
    }

    template <class T>
    [[nodiscard]] inline T ptr(std::uintptr_t a) noexcept { return reinterpret_cast<T>(a); }

    template <class T>
    [[nodiscard]] inline T ptr(void* p) noexcept { return reinterpret_cast<T>(p); }
}

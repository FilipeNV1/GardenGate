# GardenGate Softlock Fix

## Issue Overview
- When a client closes their game via console, the server's socket remains open but becomes unresponsive
- This leads to a "softlock" during level loads, as the server waits indefinitely for the unresponsive socket to respond
- Affects all supported games (GW1, GW2, Battle for Neighborville)

## Changes Made

### 1. **Socket-Level Timeout Detection**
- Each socket now tracks when it last received data
- After 30 seconds of silence, the socket is marked as invalid
- Updated in: [DLL/include/sdk/UDPSocket.h](DLL/include/sdk/UDPSocket.h)

### 2. **Manager-Level Cleanup**
- SocketManager now has a method to remove all invalid sockets
- Prevents phantom clients from staying in the peer list
- Updated in: [DLL/include/sdk/SocketManager.h](DLL/include/sdk/SocketManager.h)

### 3. **Pre-Level-Load Integration**
- All ServerStart hooks now clean up invalid peers BEFORE loading a level
- This happens automatically before server-peer communication starts
- Updated in: [DLL/include/core/Hooks.h](DLL/include/core/Hooks.h) + [DLL/include/core/Game.h](DLL/include/core/Game.h)

## Testing Instructions

### Building
```bash
cd DLL
cmake -B build
cmake --build build --config Release
```

### Testing
1. **Test Console Close**: Close a client via console while server is active
2. **Try Level Load**: Immediately load next level on server
3. **Check Logs**: Look for "Removing invalid socket" message
4. **Verify**: No softlock occurs

## Files Modified
- `DLL/include/sdk/UDPSocket.h` - Added timeout tracking and detection
- `DLL/include/sdk/SocketManager.h` - Added cleanup method
- `DLL/include/core/Game.h` - Added cleanup orchestration
- `DLL/include/core/Hooks.h` - Integrated cleanup into ServerStart hooks
#include <cassert>
#include <iostream>
#include <cstring>

// Mock implementation of timeout logic matching UDPSocket.h
class MockUDPSocket {
private:
    static constexpr float PEER_TIMEOUT_SECONDS = 30.0f;
    float m_lastActivityTime{0.0f};
    float m_totalElapsedTime{0.0f};
    bool m_peerValid{false};

public:
    void setPeerActive() {
        m_peerValid = true;
        m_lastActivityTime = m_totalElapsedTime;
    }

    void pulse(float deltaSeconds) {
        m_totalElapsedTime += deltaSeconds;
        if (m_peerValid) {
            float inactivityTime = m_totalElapsedTime - m_lastActivityTime;
            if (inactivityTime > PEER_TIMEOUT_SECONDS) {
                m_peerValid = false;
            }
        }
    }

    bool isPeerValid() const {
        return m_peerValid;
    }

    void receiveData() {
        m_lastActivityTime = m_totalElapsedTime;
    }

    float getTotalElapsedTime() const {
        return m_totalElapsedTime;
    }
};

int main() {
    int passed = 0;
    int failed = 0;

    // Test 1: Socket starts invalid
    {
        std::cout << "Test 1: Socket starts invalid... ";
        MockUDPSocket socket;
        assert(!socket.isPeerValid());
        std::cout << "Passed\n";
        passed++;
    }

    // Test 2: Socket becomes valid on peer activation
    {
        std::cout << "Test 2: Socket becomes valid on activation... ";
        MockUDPSocket socket;
        socket.setPeerActive();
        assert(socket.isPeerValid());
        std::cout << "Passed\n";
        passed++;
    }

    // Test 3: Peer stays valid with activity
    {
        std::cout << "Test 3: Peer stays valid with regular activity... ";
        MockUDPSocket socket;
        socket.setPeerActive();
        
        for (int i = 0; i < 10; i++) {
            socket.pulse(2.0f);  // 2 seconds per pulse
            if (i % 3 == 0) {
                socket.receiveData();  // activity every 6 seconds
            }
            assert(socket.isPeerValid());
        }
        std::cout << "Passed\n";
        passed++;
    }

    // Test 4: Peer times out after 30 seconds of inactivity
    {
        std::cout << "Test 4: Peer times out after 30 seconds... ";
        MockUDPSocket socket;
        socket.setPeerActive();
        assert(socket.isPeerValid());

        socket.pulse(15.0f); // 15 seconds
        assert(socket.isPeerValid());
        
        socket.pulse(10.0f); // 25 seconds total
        assert(socket.isPeerValid());
        
        socket.pulse(6.0f); // 31 seconds total - TIMEOUT!
        assert(!socket.isPeerValid());
        std::cout << "Passed\n";
        passed++;
    }

    // Test 5: Activity resets timeout timer
    {
        std::cout << "Test 5: Activity resets timeout timer... ";
        MockUDPSocket socket;
        socket.setPeerActive();
        
        socket.pulse(25.0f); // 25 seconds
        assert(socket.isPeerValid());
        
        socket.receiveData(); // reset timer
        socket.pulse(25.0f); // 25 more seconds (timer reset, so still valid)
        assert(socket.isPeerValid());
        
        socket.pulse(6.0f); // 31 seconds from reset - TIMEOUT
        assert(!socket.isPeerValid());
        std::cout << "Passed\n";
        passed++;
    }

    // Test 6: Exact timeout boundary
    {
        std::cout << "Test 6: Timeout at exactly 30 seconds... ";
        MockUDPSocket socket;
        socket.setPeerActive();
        socket.pulse(29.9f);  // 29.9 seconds
        assert(socket.isPeerValid());
        socket.pulse(0.2f);   // 30.1 seconds total - TIMEOUT
        assert(!socket.isPeerValid());
        std::cout << "Passed\n";
        passed++;
    }

    // Test 7: Multiple activity resets
    {
        std::cout << "Test 7: Multiple activity cycles... ";
        MockUDPSocket socket;
        socket.setPeerActive();
        for (int cycle = 0; cycle < 5; cycle++) {
            socket.pulse(20.0f);  // 20 seconds per cycle
            assert(socket.isPeerValid());
            socket.receiveData(); // reset timer
        }
        std::cout << "Passed\n";
        passed++;
    }

    // Test 8: Immediate timeout without activity
    {
        std::cout << "Test 8: No timeout if peer stays active... ";
        MockUDPSocket socket;
        socket.setPeerActive();
        for (int i = 0; i < 100; i++) {
            socket.pulse(0.5f);
            socket.receiveData();  // continuous activity
            assert(socket.isPeerValid());
        }
        std::cout << "Passed\n";
        passed++;
    }

    std::cout << "Results: " << passed << " passed | " << failed << " failed\n";
}

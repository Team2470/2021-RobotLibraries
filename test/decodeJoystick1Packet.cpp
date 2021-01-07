#include "gtest/gtest.h"
#include "DSProtocol.h"

TEST(DSProtocol, decodeJoystick1Packet) {
    char buffer[] = "!j00000000000000008B\r\n";
    int length = 22;

    unsigned char cs = 0;
    for (int i = 0; i < 18; i++) {
        cs += buffer[i];
    }
    printf("%02x\n", cs);

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    // EXPECT_FALSE(estopped);
    // EXPECT_TRUE(enabled);
    // EXPECT_EQ(mode, 0);
    // EXPECT_EQ(switchState, 0);
}

#include "gtest/gtest.h"
#include "DSProtocol.h"

TEST(DSProtocol, decodeJoystick2Packet_zeros) {
    char buffer[] = "!J00000000000000006B\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick2Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], 0);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_buttonword) {
    char buffer[] = "!JC0DE000000000000A7\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick2Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 0, 0, 0, 0};

    EXPECT_EQ(buttonWord, 0xC0DE);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_axis_0) {
    char buffer[] = "!J00003F000000000084\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick2Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {63, 0, 0, 0, 0, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_axis_1) {
    char buffer[] = "!J0000003F0000000084\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick2Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 63, 0, 0, 0, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_axis_2) {
    char buffer[] = "!J000000003F00000084\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick2Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 63, 0, 0, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_axis_3) {
    char buffer[] = "!J00000000003F000084\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick2Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 0, 63, 0, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_axis_4) {
    char buffer[] = "!J0000000000003F0084\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick2Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 0, 0, 63, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_axis_5) {
    char buffer[] = "!J000000000000003F84\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick2Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 0, 0, 0, 63};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_bufferTooSmall) {
    char buffer[] = "!J000000000000006B\r\n";
    int length = 20;

    uint16_t buttonWord = 128;
    int8_t axis[6] = {1, 2, 3, 4, 5, 6};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 0);

    uint16_t expectedButtonWord = 128;
    int8_t expectedAxis[6] = {1, 2, 3, 4, 5, 6};

    EXPECT_EQ(buttonWord, expectedButtonWord);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_invalidStartChar) {
    char buffer[] = "#J000000000000006B\r\n";
    int length = 22;

    uint16_t buttonWord = 128;
    int8_t axis[6] = {1, 2, 3, 4, 5, 6};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 0);

    uint16_t expectedButtonWord = 128;
    int8_t expectedAxis[6] = {1, 2, 3, 4, 5, 6};

    EXPECT_EQ(buttonWord, expectedButtonWord);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick2Packet_invalidMSGId) {
    char buffer[] = "!J000000000000006B\r\n";
    int length = 22;

    uint16_t buttonWord = 128;
    int8_t axis[6] = {1, 2, 3, 4, 5, 6};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 0);

    uint16_t expectedButtonWord = 128;
    int8_t expectedAxis[6] = {1, 2, 3, 4, 5, 6};

    EXPECT_EQ(buttonWord, expectedButtonWord);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

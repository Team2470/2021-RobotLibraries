#include "gtest/gtest.h"
#include "DSProtocol.h"

TEST(DSProtocol, decodeJoystick1Packet_zeros) {
    char buffer[] = "!j00000000000000008B\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);


    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], 0);
    }
}

TEST(DSProtocol, decodeJoystick1Packet_neg_axis) {
    char buffer[] = "!j0000F60000000000A7\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0, 0, 0, 0, 0, 0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {-10, 0, 0, 0, 0, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick1Packet_buttonword) {
    char buffer[] = "!jC0DE000000000000C7\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 0, 0, 0, 0};

    EXPECT_EQ(buttonWord, 0xC0DE);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick1Packet_axis_0) {
    char buffer[] = "!j00003F0000000000A4\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {63, 0, 0, 0, 0, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick1Packet_axis_1) {
    char buffer[] = "!j0000003F00000000A4\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 63, 0, 0, 0, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick1Packet_axis_2) {
    char buffer[] = "!j000000003F000000A4\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 63, 0, 0, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick1Packet_axis_3) {
    char buffer[] = "!j00000000003F0000A4\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 0, 63, 0, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick1Packet_axis_4) {
    char buffer[] = "!j0000000000003F00A4\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 0, 0, 63, 0};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick1Packet_axis_5) {
    char buffer[] = "!j000000000000003FA4\r\n";
    int length = 22;

    uint16_t buttonWord = 0;
    int8_t axis[6] = {0};

    int pl = DSProtocol::decodeJoystick1Packet(buffer, length, buttonWord, axis);   
    EXPECT_EQ(pl, 22);

    int8_t expectedAxis[6] = {0, 0, 0, 0, 0, 63};

    EXPECT_EQ(buttonWord, 0);
    for(int i = 0; i < 6; i++) {
        EXPECT_EQ(axis[i], expectedAxis[i]);
    }
}

TEST(DSProtocol, decodeJoystick1Packet_bufferTooSmall) {
    char buffer[] = "!j000000000000003F\r\n";
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

TEST(DSProtocol, decodeJoystick1Packet_invalidStartChar) {
    char buffer[] = "#j000000000000003F\r\n";
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

TEST(DSProtocol, decodeJoystick1Packet_invalidMSGId) {
    char buffer[] = "!w000000000000003F\r\n";
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

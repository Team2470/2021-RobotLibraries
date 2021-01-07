#include "gtest/gtest.h"
#include "DSProtocol.h"

TEST(DSProtocol, decodeDSControlPacket_Enabled) {
    char buffer[] = "!c100045\r\n";
    int length = 12;

    bool estopped = false;
    bool enabled = false;
    uint8_t mode = 0;
    uint8_t switchState = 0;

    int pl = DSProtocol::decodeDSControlPacket(buffer, length, estopped, enabled, mode, switchState);   
    EXPECT_EQ(pl, 10);

    EXPECT_FALSE(estopped);
    EXPECT_TRUE(enabled);
    EXPECT_EQ(mode, 0);
    EXPECT_EQ(switchState, 0);
}

TEST(DSProtocol, decodeDSControlPacket_Estopped) {
    char buffer[] = "!c200046\r\n";
    int length = 12;

    bool estopped = false;
    bool enabled = false;
    uint8_t mode = 0;
    uint8_t switchState = 0;

    int pl = DSProtocol::decodeDSControlPacket(buffer, length, estopped, enabled, mode, switchState);   
    EXPECT_EQ(pl, 10);

    EXPECT_TRUE(estopped);
    EXPECT_FALSE(enabled);
    EXPECT_EQ(mode, 0);
    EXPECT_EQ(switchState, 0);
}

TEST(DSProtocol, decodeDSControlPacket_Mode) {
    char buffer[] = "!c0f007A\r\n";
    int length = 12;

    bool estopped = false;
    bool enabled = false;
    uint8_t mode = 0;
    uint8_t switchState = 0;

    int pl = DSProtocol::decodeDSControlPacket(buffer, length, estopped, enabled, mode, switchState);   
    EXPECT_EQ(pl, 10);

    EXPECT_TRUE(estopped);
    EXPECT_FALSE(enabled);
    EXPECT_EQ(mode, 15);
    EXPECT_EQ(switchState, 0);
}

TEST(DSProtocol, decodeDSControlPacket_Switches) {
    char buffer[] = "!c004A59\r\n";
    int length = 12;

    bool estopped = false;
    bool enabled = false;
    uint8_t mode = 0;
    uint8_t switchState = 0;

    int pl = DSProtocol::decodeDSControlPacket(buffer, length, estopped, enabled, mode, switchState);   
    EXPECT_EQ(pl, 10);

    EXPECT_FALSE(estopped);
    EXPECT_FALSE(enabled);
    EXPECT_EQ(mode, 0);
    EXPECT_EQ(switchState, 74);
}


TEST(DSProtocol, decodeDSControlPacket_bufferTooSmall) {
    char buffer[] = "!c004A\r\n";
    int length = 10;

    bool estopped = true;
    bool enabled = true;
    uint8_t mode = 3;
    uint8_t switchState = 14;

    int pl = DSProtocol::decodeDSControlPacket(buffer, length, estopped, enabled, mode, switchState);   
    EXPECT_EQ(pl, 0);

    EXPECT_TRUE(estopped);
    EXPECT_TRUE(enabled);
    EXPECT_EQ(mode, 3);
    EXPECT_EQ(switchState, 14);
}

TEST(DSProtocol, decodeDSControlPacket_invalidStartChar) {
    char buffer[] = "#c004A59\r\n";
    int length = 12;

    bool estopped = true;
    bool enabled = true;
    uint8_t mode = 3;
    uint8_t switchState = 14;

    int pl = DSProtocol::decodeDSControlPacket(buffer, length, estopped, enabled, mode, switchState);   
    EXPECT_EQ(pl, 0);

    EXPECT_TRUE(estopped);
    EXPECT_TRUE(enabled);
    EXPECT_EQ(mode, 3);
    EXPECT_EQ(switchState, 14);
}

TEST(DSProtocol, decodeDSControlPacket_invalidMSGId) {
    char buffer[] = "!x004A59\r\n";
    int length = 12;

    bool estopped = true;
    bool enabled = true;
    uint8_t mode = 3;
    uint8_t switchState = 14;

    int pl = DSProtocol::decodeDSControlPacket(buffer, length, estopped, enabled, mode, switchState);   
    EXPECT_EQ(pl, 0);

    EXPECT_TRUE(estopped);
    EXPECT_TRUE(enabled);
    EXPECT_EQ(mode, 3);
    EXPECT_EQ(switchState, 14);
}

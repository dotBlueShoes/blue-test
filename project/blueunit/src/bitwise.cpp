// Created 2026.03.26 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#define BLUELIB_IMPLEMENTATION
#include <blue/instructions/bswap.hpp> // ! comment this out to test without bswap !
#include <blue/bitwise.hpp>
#include <gtest/gtest.h>

TEST (bitwise_reverse, u8) {
    u8  a = 2; BITWISE::Reverse8 (a);
    EXPECT_EQ (a, 64);
}

TEST (bitwise_reverse, u16) {
    u16 b = 265; BITWISE::Reverse16 (b);
    EXPECT_EQ (b, 36992);
}

TEST (bitwise_reverse, u32) {
    u32 c = 871225; BITWISE::Reverse32 (c);
    EXPECT_EQ (c, 2631053312);
}

TEST (bitwise_reverse, u64) {
    u64 d = 880078481234; BITWISE::Reverse64 (d);
    EXPECT_EQ (d, 5397497182834130944);
}

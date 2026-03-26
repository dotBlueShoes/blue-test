// Created 2026.03.26 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#define BLUELIB_IMPLEMENTATION
// TODO. REDO WAVE
#define BLUE_WAVE_NO_OPT // this is the fastest on debug build
//#define BLUE_WAVE_LUT_OPT
//#define BLUE_WAVE_BITWISE_SCALING_OPT
//
#include <blue/wave.hpp>
#include <gtest/gtest.h>

TEST (wave_datatype, size_w8 ) { EXPECT_EQ (sizeof  (w8), 1); }
TEST (wave_datatype, size_w16) { EXPECT_EQ (sizeof (w16), 2); }

TEST (normal_datatype, size_n8 ) { EXPECT_EQ (sizeof  (n8), 1); }
TEST (normal_datatype, size_n16) { EXPECT_EQ (sizeof (n16), 2); }

//TEST (type_size, u32r32) { EXPECT_EQ (sizeof (u32r32), 4); }

TEST (normal_datatype, casting_u8) {
    const u8 i = 16; // 0.25f
    r32 r; n8r32 (i, r);
    EXPECT_NEAR (r, 0.25f, 0); // Tolerance of ±0.00000
}


TEST (normal_datatype, addition) {
    const u8 a = 16; // 0.25f
    const u8 b = 16; // 0.25f

    r32 normalA, normalB, normalC;
    n8r32 (a, normalA);
    n8r32 (b, normalB);
    n8r32 (a + b, normalC);

    EXPECT_NEAR (normalA + normalB, normalC, 0); // Tolerance of ±0.00000
}


TEST (wave_datatype, casting_u8) {
    const u8 i = 32; // 0.25f
    r32 r; w8r32 (i, r);
    EXPECT_NEAR (r, 0.25f, 0.10000); // Tolerance of ±0.10000
}

TEST (wave_datatype, addition) {
    const u8 a = 32; // 0.25f
    const u8 b = 32; // 0.25f
    
    r32 normalA, normalB, normalC;
    w8r32 (a, normalA);
    w8r32 (b, normalB);
    w8r32 (a + b, normalC);  

    EXPECT_NEAR (normalA + normalB, normalC, 0.10000); // Tolerance of ±0.10000
}

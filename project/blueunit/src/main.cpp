// Created 2025.05.07 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#define BLUELIB_IMPLEMENTATION
#define WAVE_NO_OPT // this is the fastest on debug build
//#define WAVE_LUT_OPT
//#define WAVE_BITWISE_SCALING_OPT
//
#include <blue/wave.hpp>
#include <blue/error.hpp>
#include <blue/struct.hpp>
#include <blue/types.hpp>
//
#include <blue/cmpxchg16b.hpp>
//
#include <gtest/gtest.h>

interface

TEST (TypeSize, u8)  { EXPECT_EQ (sizeof  (u8), 1); }
TEST (TypeSize, u16) { EXPECT_EQ (sizeof (u16), 2); }
TEST (TypeSize, u32) { EXPECT_EQ (sizeof (u32), 4); }
TEST (TypeSize, u64) { EXPECT_EQ (sizeof (u64), 8); }

TEST (TypeSize, s8)  { EXPECT_EQ (sizeof  (s8), 1); }
TEST (TypeSize, s16) { EXPECT_EQ (sizeof (s16), 2); }
TEST (TypeSize, s32) { EXPECT_EQ (sizeof (s32), 4); }
TEST (TypeSize, s64) { EXPECT_EQ (sizeof (s64), 8); }

TEST (TypeSize, c8)  { EXPECT_EQ (sizeof  (c8), 1); }
TEST (TypeSize, c16) { EXPECT_EQ (sizeof (c16), 2); }
TEST (TypeSize, r32) { EXPECT_EQ (sizeof (r32), 4); }
TEST (TypeSize, r64) { EXPECT_EQ (sizeof (r64), 8); }

TEST (TypeSize, w8)     { EXPECT_EQ (sizeof     (w8), 1); }
TEST (TypeSize, w16)    { EXPECT_EQ (sizeof    (w16), 2); }
TEST (TypeSize, u32r32) { EXPECT_EQ (sizeof (u32r32), 4); }


TEST (MathNormal, u8Casting) {
    const u8 i = 16; // 0.25f
    
    r32 r;
    n8r32 (i, r);

    // Tolerance of ±0.00000
    EXPECT_NEAR (r, 0.25f, 0);
}


TEST (MathNormal, Addition) {
    const u8 a = 16; // 0.25f
    const u8 b = 16; // 0.25f

    r32 normalA, normalB, normalC;
    n8r32 (a, normalA);
    n8r32 (b, normalB);
    n8r32 (a + b, normalC);

    // Tolerance of ±0.00000
    EXPECT_NEAR (normalA + normalB, normalC, 0);  
}


TEST (MathWave, u8Casting) {
    const u8 i = 32; // 0.25f
    
    r32 r;
    w8r32 (i, r);

    //// Tolerance of ±0.00000
    //EXPECT_NEAR (r, 0.25f, 0); 

    // Tolerance of ±0.10000
    EXPECT_NEAR (r, 0.25f, 0.10000); 
}

TEST (cmpxchg16b, EqualityTrue) {

    alignas (16) u64 out[2] { 10, 1 };
    register u64 exp[2] { 10, 1 };
    register u64 des[2] { 22, 22 };

    bool isEqual = cmpxchg16b (out, exp[0], exp[1], des[0], des[1]);

    EXPECT_EQ (out[0], des[0]);
    EXPECT_EQ (out[1], des[1]);
    EXPECT_EQ (isEqual, true);
}

TEST (cmpxchg16b, EqualityFalse) {

    alignas (16) u64 out[2] { 22, 21 };
    register u64 exp[2] { 1, 2 };
    register u64 des[2] { 10, 9 };

    bool isEqual = cmpxchg16b (out, exp[0], exp[1], des[0], des[1]);

    EXPECT_EQ (out[0], exp[0]);
    EXPECT_EQ (out[1], exp[1]);
    EXPECT_EQ (isEqual, false);
}

TEST (atomic_cmpxchg16b, EqualityTrue) {

    alignas (16) u64 out[2] { 10, 1 };
    register u64 exp[2] { 10, 1 };
    register u64 des[2] { 22, 22 };

    bool isEqual = atomic_cmpxchg16b (out, exp[0], exp[1], des[0], des[1]);

    EXPECT_EQ (out[0], des[0]);
    EXPECT_EQ (out[1], des[1]);
    EXPECT_EQ (isEqual, true);
}

TEST (atomic_cmpxchg16b, EqualityFalse) {

    alignas (16) u64 out[2] { 22, 21 };
    register u64 exp[2] { 1, 2 };
    register u64 des[2] { 10, 9 };

    bool isEqual = atomic_cmpxchg16b (out, exp[0], exp[1], des[0], des[1]);

    EXPECT_EQ (out[0], exp[0]);
    EXPECT_EQ (out[1], exp[1]);
    EXPECT_EQ (isEqual, false);
}

TEST (MathWave, Addition) {
    const u8 a = 32; // 0.25f
    const u8 b = 32; // 0.25f
    
    r32 normalA, normalB, normalC;
    w8r32 (a, normalA);
    w8r32 (b, normalB);
    w8r32 (a + b, normalC);

    //// Tolerance of ±0.00000
    //EXPECT_NEAR (normalA + normalB, normalC, 0);   

    // Tolerance of ±0.10000
    EXPECT_NEAR (normalA + normalB, normalC, 0.10000); 
}


TEST (Environment, Initialization) {

    { // BLUE START
        TIMESTAMP_BEGIN = TIMESTAMP::GetCurrent ();
        DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align fututre debug-logs
        LOGINFO ("Application Statred!\n");
    }

    { // BLUE EXIT
        LOGMEMORY ();
        LOGINFO ("Finalized Execution\n");
        DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align debug-logs
    }

}

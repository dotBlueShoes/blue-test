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
#include <blue/instructions/cmpxchg16b.hpp>
//
#include <gtest/gtest.h>
//
#include <blue/windows/controls.hpp>

TEST (type_size, u8)  { EXPECT_EQ (sizeof  (u8), 1); }
TEST (type_size, u16) { EXPECT_EQ (sizeof (u16), 2); }
TEST (type_size, u32) { EXPECT_EQ (sizeof (u32), 4); }
TEST (type_size, u64) { EXPECT_EQ (sizeof (u64), 8); }

TEST (type_size, s8)  { EXPECT_EQ (sizeof  (s8), 1); }
TEST (type_size, s16) { EXPECT_EQ (sizeof (s16), 2); }
TEST (type_size, s32) { EXPECT_EQ (sizeof (s32), 4); }
TEST (type_size, s64) { EXPECT_EQ (sizeof (s64), 8); }

TEST (type_size, c8)  { EXPECT_EQ (sizeof  (c8), 1); }
TEST (type_size, c16) { EXPECT_EQ (sizeof (c16), 2); }
TEST (type_size, r32) { EXPECT_EQ (sizeof (r32), 4); }
TEST (type_size, r64) { EXPECT_EQ (sizeof (r64), 8); }

TEST (type_size, w8)     { EXPECT_EQ (sizeof     (w8), 1); }
TEST (type_size, w16)    { EXPECT_EQ (sizeof    (w16), 2); }
TEST (type_size, u32r32) { EXPECT_EQ (sizeof (u32r32), 4); }


TEST (math_norm, u8Casting) {
    const u8 i = 16; // 0.25f
    
    r32 r;
    n8r32 (i, r);

    // Tolerance of ±0.00000
    EXPECT_NEAR (r, 0.25f, 0);
}


TEST (math_norm, Addition) {
    const u8 a = 16; // 0.25f
    const u8 b = 16; // 0.25f

    r32 normalA, normalB, normalC;
    n8r32 (a, normalA);
    n8r32 (b, normalB);
    n8r32 (a + b, normalC);

    // Tolerance of ±0.00000
    EXPECT_NEAR (normalA + normalB, normalC, 0);  
}


TEST (math_wave, u8Casting) {
    const u8 i = 32; // 0.25f
    
    r32 r;
    w8r32 (i, r);

    //// Tolerance of ±0.00000
    //EXPECT_NEAR (r, 0.25f, 0); 

    // Tolerance of ±0.10000
    EXPECT_NEAR (r, 0.25f, 0.10000); 
}

TEST (math_wave, Addition) {
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



TEST (cmpxchg16b, equality_true) {
    alignas (16) u64 out[2] { 10, 1 };
    alignas (16) u64 a[2] { 10, 1 };
    register const u64 b[2] { 22, 22 };

    x_cmpxchg16b (b, a, out);

    EXPECT_EQ (out[0], b[0]);
    EXPECT_EQ (out[1], b[1]);
}

TEST (cmpxchg16b, equality_false) {
    alignas (16) u64 out[2] { 10, 1 };
    alignas (16) u64 a[2] { 9, 2 };
    register const u64 b[2] { 22, 22 };

    x_cmpxchg16b (b, a, out);

    EXPECT_EQ (out[0], a[0]);
    EXPECT_EQ (out[1], a[1]);
}

TEST (cmpxchg16b, atomic_equality_true) {
    alignas (16) u64 out[2] { 10, 1 };
    register u64 a[2] { 10, 1 };
    register const u64 b[2] { 22, 22 };

    atomic_cmpxchg16b (b, a, out);

    EXPECT_EQ (out[0], b[0]);
    EXPECT_EQ (out[1], b[1]);
}

TEST (cmpxchg16b, atomic_equality_false) {
    alignas (16) u64 out[2] { 10, 1 };
    register u64 a[2] { 9, 2 };
    register const u64 b[2] { 22, 22 };

    atomic_cmpxchg16b (b, a, out);

    EXPECT_EQ (out[0], a[0]);
    EXPECT_EQ (out[1], a[1]);
}

TEST (cmpxchg16b, equality_flag_true) {

    alignas (16) u64 out[2] { 10, 1 };
    alignas (16) u64 a[2] { 10, 1 };
    register const u64 b[2] { 22, 22 };

    bool isEqual = x_cmpxchg16b_zf (b, a, out);

    EXPECT_EQ (out[0], b[0]);
    EXPECT_EQ (out[1], b[1]);
    EXPECT_EQ (isEqual, true);
}

TEST (cmpxchg16b, equality_flag_false) {

    alignas (16) u64 out[2] { 22, 21 };
    alignas (16) u64 a[2] { 1, 2 };
    register const u64 b[2] { 10, 9 };

    bool isEqual = x_cmpxchg16b_zf (b, a, out);

    EXPECT_EQ (out[0], a[0]);
    EXPECT_EQ (out[1], a[1]);
    EXPECT_EQ (isEqual, false);
}

TEST (cmpxchg16b, atomic_equality_flag_true) {

    alignas (16) u64 out[2] { 10, 1 };
    register u64 a[2] { 10, 1 };
    register const u64 b[2] { 22, 22 };

    bool isEqual = atomic_cmpxchg16b_zf (b, a, out);

    EXPECT_EQ (out[0], b[0]);
    EXPECT_EQ (out[1], b[1]);
    EXPECT_EQ (isEqual, true);
}

TEST (cmpxchg16b, atomic_equality_flag_false) {

    alignas (16) u64 out[2] { 22, 21 };
    register u64 a[2] { 1, 2 };
    register const u64 b[2] { 10, 9 };

    bool isEqual = atomic_cmpxchg16b_zf (b, a, out);

    EXPECT_EQ (out[0], a[0]);
    EXPECT_EQ (out[1], a[1]);
    EXPECT_EQ (isEqual, false);
}



TEST (environment, initialization) {

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

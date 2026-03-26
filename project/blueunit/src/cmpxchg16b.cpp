// Created 2026.03.26 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#define BLUELIB_IMPLEMENTATION
#include <blue/instructions/cmpxchg16b.hpp>
#include <gtest/gtest.h>

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

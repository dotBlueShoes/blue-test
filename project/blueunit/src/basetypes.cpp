// Created 2026.03.26 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#define BLUELIB_IMPLEMENTATION
#include <blue/basetypes.hpp>
#include <gtest/gtest.h>

TEST (basetypes_size, u8 ) { EXPECT_EQ (sizeof  (u8), 1); }
TEST (basetypes_size, u16) { EXPECT_EQ (sizeof (u16), 2); }
TEST (basetypes_size, u32) { EXPECT_EQ (sizeof (u32), 4); }
TEST (basetypes_size, u64) { EXPECT_EQ (sizeof (u64), 8); }

TEST (basetypes_size, s8 ) { EXPECT_EQ (sizeof  (s8), 1); }
TEST (basetypes_size, s16) { EXPECT_EQ (sizeof (s16), 2); }
TEST (basetypes_size, s32) { EXPECT_EQ (sizeof (s32), 4); }
TEST (basetypes_size, s64) { EXPECT_EQ (sizeof (s64), 8); }

TEST (basetypes_size, c8 ) { EXPECT_EQ (sizeof  (c8), 1); }
TEST (basetypes_size, c16) { EXPECT_EQ (sizeof (c16), 2); }
TEST (basetypes_size, r32) { EXPECT_EQ (sizeof (r32), 4); }
TEST (basetypes_size, r64) { EXPECT_EQ (sizeof (r64), 8); }

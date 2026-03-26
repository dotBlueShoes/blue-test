// Created 2025.05.07 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#define BLUELIB_IMPLEMENTATION
#include <blue/error.hpp>
#include <gtest/gtest.h>

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

#pragma once

#include "../../common/seal_kats.h"
#include "kreyvium_13_seal.h"

using namespace KREYVIUM_13;

// build an array of KnownAnswerTests for KREYVIUM13
SEALKnownAnswerTest<KREYVIUM13_SEAL> KNOWN_ANSWER_TESTS[] = {
    {
        {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
         0x55, 0x55, 0x55, 0x55},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00},
        {0x89, 0xa3, 0xb7, 0x00, 0xd9, 0x46, 0x2f, 0xdf, 0x01, 0xad, 0xbf, 0x06,
         0xcb, 0xc7, 0x58, 0x88},
        2,
        16384,
        128,
        SEALKnownAnswerTest<KREYVIUM13_SEAL>::Testcase::DEC,
    },
    {
        {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
         0x55, 0x55, 0x55, 0x55},
        {0x00},
        {0x00},
        2,
        32768,
        128,
        SEALKnownAnswerTest<KREYVIUM13_SEAL>::Testcase::USE_CASE,
        5,
        16,
    }};

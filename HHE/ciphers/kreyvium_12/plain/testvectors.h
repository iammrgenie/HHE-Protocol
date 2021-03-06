#pragma once

#include "../../common/kats.h"
#include "kreyvium_12_plain.h"

using namespace KREYVIUM_12;

// build an array of KnownAnswerTests for KREYVIUM_12
KnownAnswerTest<Kreyvium12> KNOWN_ANSWER_TESTS[] = {
    {
        {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
         0x55, 0x55, 0x55, 0x55},
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {0x89, 0xA3, 0xB7, 0x00, 0xD9, 0x44},
        KnownAnswerTest<Kreyvium12>::Testcase::DEC,
    },
    {
        {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
         0x55, 0x55, 0x55, 0x55},
        {0x00},
        {0x00},
        KnownAnswerTest<Kreyvium12>::Testcase::USE_CASE,
        5,
        16,
    }};

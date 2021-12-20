//
//  Created by Maximilian Reif on 05.07.14.
//  Copyright (c) 2014 Maximilian Reif. All rights reserved.
//

#pragma once

#include <stdint.h>

const uint8_t generatorTable[] = {0, 225, 210, 51, 180, 85, 102, 135, 120, 153, 170, 75, 204, 45, 30, 255};
const uint8_t parityCheckTable[] = {0, 14, 13, 3, 11, 5, 6, 8, 7, 9, 10, 4, 12, 2, 1, 15};
const uint8_t errorMaskTable[] = {0, 16, 32, 255, 64, 255, 255, 8, 128, 255, 255, 4, 255, 2, 1, 255};

uint8_t encode(uint8_t x) {
    return generatorTable[x & 0xf];
}

uint8_t decode(uint8_t x) {
    uint8_t syndrome  = (x >> 4) ^ parityCheckTable[x & 0xf];
    uint8_t mask = errorMaskTable[syndrome];
    return (mask == 0xff) ? 0xff : (x ^ mask) & 0xf;
}

void encodeBuffer(uint8_t *inputData, uint8_t *encodedData, uint32_t inputLength) {
    while (inputLength--) {
        *encodedData++ = encode(*inputData >> 4);
        *encodedData++ = encode(*inputData++);
    }
}

bool decodeBuffer(uint8_t *encodedData, uint8_t *outputData, uint32_t outputLength) {
    while (outputLength--) {
        uint8_t high = decode(*encodedData++);
        uint8_t low = decode(*encodedData++);
        if (high == 0xff || low == 0xff) return false;
        *outputData++ = (high << 4) | low;
    }
    return true;
}

//
//  Created by Maximilian Reif on 20.12.2021.
//  Copyright (c) 2021 Maximilian Reif. All rights reserved.
//

#include <iostream>
#include "ExtHamming.h"

using namespace std;

int main(int argc, const char * argv[]) {

    uint8_t helloWorld[] = "Hello World!", encoded[sizeof(helloWorld) * 2], decoded[sizeof(helloWorld)];

    encodeBuffer(helloWorld, encoded, sizeof(helloWorld));
    bool success = decodeBuffer(encoded, decoded, sizeof(decoded));

    cout << "Decoded message: " << (success ? reinterpret_cast<char*>(decoded) : "decoding failed") << endl;

    return 0;
}
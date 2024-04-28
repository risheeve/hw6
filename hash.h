#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T w[5] = {0};
        int segLen = 6;
        int n = k.length();
        int segs = (n + segLen - 1) / segLen;
        for (int i = 0; i < segs; ++i) {
                        HASH_INDEX_T pow_36 = 1;
                        int segEnd = n - i * segLen;
                        int segStart = std::max(0, segEnd - segLen);

                        for (int pos = segEnd - 1; pos >= segStart; --pos) {
                            char c = std::tolower(k[pos]);
                            HASH_INDEX_T val = letterDigitToNumber(c);
                            int indx = 4 - i; 
                            w[indx] += val * pow_36;
                            pow_36 *= 36;
                        }
                    }
                    HASH_INDEX_T hash_val = 0;
                    for (int i = 0; i < 5; ++i) {
                        hash_val += rValues[i] * w[i];
                    }

                    return hash_val;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = std::tolower(letter);
        if(std::isalpha(letter)) {
            return letter - 'a';
        } else if(std::isdigit(letter)) {
            return letter - '0' + 26;
        } else {
            return 0;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

#include "EncryptData.h"
void encryptDecrypt(char*& toEncrypt, uint32_t dataSize) {
    for (uint32_t i = 0; i < dataSize; i++) {
        toEncrypt[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
    }
}
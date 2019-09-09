#include "judge.h"

#include <vector>
#include <string>
#include <iostream>
using namespace std;

unsigned char charToCompressed(char c) {
    if (c < 64)
        return c - '0';
    else if (c < 96)
        return c - 'A' + 10;
    else
        return  c - 'a' + 36;
}

char compressedToChar(char compressed) {
    if (compressed < 10) {
        return '0' + compressed;
    } else if (compressed < 36) {
        return 'A' + compressed - 10;
    } else {
        return 'a' + compressed - 36;
    }
}

struct User {

    User() {value_int_ptr = (const int*)value;}

    void compress(const char* _value);
    void decompress(char* _value);

    unsigned char value[48];
    const int* value_int_ptr;
    int idx1;
    int idx2;

    bool operator==(const char* data) const;
};

const int USER_SIZE = 56;
const int BUCKETS_CNT = 149795;

int getBucketId(char* data) {
    int* int_ptr = (int*)data;

    int rval = *int_ptr % BUCKETS_CNT;
    return rval;
}

bool User::operator==(const  char* data) const {

    const int* data_int_ptr = (const int*)data;

    for (int i = 0; i < 48/4; ++i) {
        if (value_int_ptr[i] != data_int_ptr[i]){
            return false;
        }
    }
    return true;
}


void User::compress(const char* _value) {
    for (int i = 0; i < 48; ++i) {
        value[i] = 0;
    }

    int offset = 0;
    for (int i = 0; i < 64; ++i) {
        if (_value[i] == 0) {
            break;
        }
        auto cc = charToCompressed(_value[i]);

        int pos = i*6/8;

        value[pos] |= (cc << offset) & 0xFF;
        value[pos+1] |= (cc >> (8 - offset)) & 0xFF;

        offset -=2;
        if (offset < 0) {
            offset = 6;
        }
    }
}

void User::decompress(char* _value) {
    int offset = 0;
    for (int i = 0; i < 64; ++i) {
        int pos = i*6/8;
        unsigned char cc1 = ((value[pos] >> offset) & 0x3F);
        unsigned char cc2 = (value[pos+1] << (8 - offset) & 0x3F);

        auto cc = ((value[pos] >> offset) & 0x3F) | (value[pos+1] << (8 - offset) & 0x3F);

        _value[i] = compressedToChar(cc);

        if(_value[i] == 0) {
            break;
        }

        offset -=2;
        if (offset < 0) {
            offset = 6;
        }
    }
}

class NAZ : public INaz {
public:
    void init(int maxSize);
    void addCitizen(char *name, char *surname, char *pesel) {  }
    void delCitizen(char *pesel) {  }
    void getNameByPesel(char *pesel, /*OUT*/ char *name) {  }
    void getSurnameByPesel(char *pesel, /*OUT*/ char *surname) {  }
    void getPeselByName(char *name, /*OUT*/ char *pesel) {  }
    void getPeselBySurname(char *surname, /*OUT*/ char *pesel) {  }
};

void NAZ::init(int maxSize) {
    int buff[1024*128];

    for (int i = 0; i < 1024*128; i++) {
        buff[i] = 0;
    }

    for (int i = 0; i < 8*1024*1024; i += 1024*128*4)
        Judge::memoryWrite(i,1024*128*4,(char*)buff);
}


NAZ solution;

int main() {
    Judge::run(&solution);

    string testChars = "0987654321qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

    vector<char> compressed;
    vector<char> decompressed;

    for (auto cc : testChars) {
        auto compr = charToCompressed(cc);
        auto decompr = compressedToChar(compr);
        compressed.push_back(compr);
        compressed.push_back(decompr);

        if (decompr != cc){
            cout << cc << endl;
        }

    }

    cout << sizeof(User) << endl;

    User user;
    string name = "AlaMaKota6";

    user.compress(name.c_str());

    char name_decempressed[64];

    user.decompress(name_decempressed);

    for (int i = 0; i < name.length(); i++ ) {
        if (name[i] != name_decempressed[i]) {
            cout << i << endl;
        }
    }

    return 0;
}


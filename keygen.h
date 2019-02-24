#ifndef KEYGEN_H
#define KEYGEN_H

#include <string>

#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/files.h>

using namespace std;

using namespace CryptoPP;

class keygen
{
    string pubKeypath;
    string priKeypath;
    unsigned int keySize;
public:
    keygen();
    void setPubKeypath(string s);
    void setPriKeypath(string s);
    void setKeySize(unsigned int size);
    void saveKey();

};

#endif // KEYGEN_H

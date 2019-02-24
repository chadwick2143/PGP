#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <string>

#include <crypto++/idea.h>
#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/modes.h>
#include <crypto++/files.h>
#include <crypto++/filters.h>

using namespace std;

using namespace CryptoPP;

class encrypt
{
    byte key[IDEA::DEFAULT_KEYLENGTH];
    byte iv[IDEA::BLOCKSIZE];
    //const char *inFilePath;
    //const char *outFilePath;
    RSA::PrivateKey privatekey;
    RSA::PublicKey publickey;
    string dir;
    void genkeyiv();
    void savekeyiv();
public:
    encrypt();
    void setkeyiv(string keyPath);
    //void setFilePath(string in, string out);
    void setdir(string d);
    void setpubkey(string pubkeyPath);
    void setprikey(string prikeyPath);
    void enc(string in, string out);
    void dec(string in, string out);
};

#endif // ENCRYPT_H

#include "keygen.h"

keygen::keygen()
{
    pubKeypath = "/home/jack/public.key";
    priKeypath = "/home/jack/private.key";
    keySize = 3072;
}
void keygen::setPubKeypath(string s)
{
    pubKeypath = s;
}
void keygen::setPriKeypath(string s)
{
    priKeypath = s;
}
void keygen::setKeySize(unsigned int size)
{
    keySize = size;
}

void Save(const string& filename, const BufferedTransformation& bt)
{
    FileSink file(filename.c_str());

    bt.CopyTo(file);
    file.MessageEnd();
}
void SavePublicKey(const string& filename, const PublicKey& key)
{
    ByteQueue queue;
    key.Save(queue);

    Save(filename, queue);
}
void SavePrivateKey(const string& filename, const PrivateKey& key)
{
    ByteQueue queue;
    key.Save(queue);

    Save(filename, queue);
}

void keygen::saveKey()
{
    AutoSeededRandomPool rng;
    RSA::PrivateKey privatekey;
    privatekey.GenerateRandomWithKeySize(rng, keySize);
    RSA::PublicKey publickey(privatekey);

    SavePublicKey(pubKeypath, publickey);
    SavePrivateKey(priKeypath, privatekey);
}

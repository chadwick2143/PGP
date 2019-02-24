#include "encrypt.h"

encrypt::encrypt()
{

}

void encrypt::genkeyiv()
{
    AutoSeededRandomPool rng;
    rng.GenerateBlock(key, sizeof(key));
    rng.GenerateBlock(iv, sizeof(iv));

}
void encrypt::savekeyiv()
{
    string strkey(reinterpret_cast<const char*>(&key[0]), sizeof(key));
    string striv(reinterpret_cast<const char*>(&iv[0]), sizeof(iv));

    string cipherkey;

    AutoSeededRandomPool rng;

    RSAES_OAEP_SHA_Encryptor e(publickey);

    StringSource(strkey, true,
        new PK_EncryptorFilter(rng, e,
            new StringSink(cipherkey)
       )
    );

    cipherkey = striv + cipherkey;

    string k = dir + "/idea.key";

    const char *keyPath = k.c_str();

    StringSource(cipherkey, true, new FileSink(keyPath));
}
/*
void encrypt::setFilePath(string in, string out)
{
    inFilePath = in.c_str();
    outFilePath = out.c_str();
}
*/
void encrypt::setdir(string d)
{
    dir = d;
}
void encrypt::setkeyiv(string k)
{
    const char *keyPath = k.c_str();

    string recoveredkey, cipherkey,striv;

    FileSource(keyPath, true, new StringSink(cipherkey));
    striv = cipherkey.substr(0, 8);
    cipherkey = cipherkey.substr(8);

    AutoSeededRandomPool rng;
    RSAES_OAEP_SHA_Decryptor d(privatekey);

    StringSource(cipherkey, true,
        new PK_DecryptorFilter(rng, d,
            new StringSink(recoveredkey)
       )
    );

    StringSource(recoveredkey, true, new ArraySink(key, IDEA::DEFAULT_KEYLENGTH));
    StringSource(striv, true, new ArraySink(iv, IDEA::BLOCKSIZE));
}
void encrypt::enc(string in, string out)
{
    const char *inFilePath = in.c_str();
    const char *outFilePath = out.c_str();

    genkeyiv();
    savekeyiv();

    try
    {
        CBC_Mode<IDEA>::Encryption e;
        e.SetKeyWithIV(key, sizeof(key), iv);

        FileSource(inFilePath, true,
            new StreamTransformationFilter(e,
                new FileSink(outFilePath)
            )
        );
    }
    catch(const CryptoPP::Exception& exc)
    {
        cerr << exc.what() << endl;
        exit(1);
    }
}
void encrypt::dec(string in, string out)
{
    const char *inFilePath = in.c_str();
    const char *outFilePath = out.c_str();

    try
    {
        CBC_Mode< IDEA >::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv);

        FileSource(inFilePath, true,
            new StreamTransformationFilter(d,
                new FileSink(outFilePath)
            )
        );
    }
    catch(const CryptoPP::Exception& exc)
    {
        cerr << exc.what() << endl;
        exit(1);
    }
}

void Load(const string& filename, BufferedTransformation& bt)
{
    FileSource file(filename.c_str(), true /*pumpAll*/);

    file.TransferTo(bt);
    bt.MessageEnd();
}
void LoadPublicKey(const string& filename, PublicKey& key)
{
    ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);
}
void LoadPrivateKey(const string& filename, PrivateKey& key)
{
    ByteQueue queue;
    Load(filename, queue);

    key.Load(queue);
}
void encrypt::setpubkey(string pubkeyPath)
{
    LoadPublicKey(pubkeyPath, publickey);
}
void encrypt::setprikey(string prikeyPath)
{
    LoadPrivateKey(prikeyPath, privatekey);
}

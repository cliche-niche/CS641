#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string encrypt(string plain, const vector<int> (&key)){
    int i_p = 0, i_k = 0, l = key.size();
    for(i_p = 0; i_p < plain.length(); i_p++){
        if('a' <= plain[i_p] && plain[i_p] <= 'z'){
            plain[i_p] = 'a' + ((plain[i_p] - 'a' + key[i_k % l]) % 26 + 26) % 26;      // Add the key (mod 26) to the plaintext's character to encrypt
            i_k++;                                                                      // Iterator to keep track of index in the key
        }
    }
    return plain;
}

string decrypt(string cipher, const vector<int> (&key)){
    int i_c = 0, i_k = 0, l = key.size();
    for(i_c = 0; i_c < cipher.length(); i_c++){
        if('a' <= cipher[i_c] && cipher[i_c] <= 'z'){
            cipher[i_c] = 'a' + ((cipher[i_c] -'a' -  key[i_k % l]) % 26 + 26) % 26;      // Subtract the key (mod 26) to the plaintext's character to decrypt
            i_k++;                                                                      // Iterator to keep track of index in the key
        }
    }
    return cipher;
}

int main(){
    
    string s = \
                "Kg fcwd qh vin pnzy hjcocnt, cjjwg ku wnth nnyvng kxa cjjwg. "
                "Urfjm xwy yjg rbbufqwi \"vjg_djxn_ofs_dg_rmncbgi\" yq iq uqtxwlm. "  
                "Oca zxw qcaj vjg tctnplyj hqs cjn pjcv ejbvdnt. Yt hkpe cjn gcnv, "
                "aqv okauy bknn ongm vt zvvgs vcpkh bqtft cjntj.";


    transform(s.begin(), s.end(), s.begin(), ::tolower);
    cout<<s<<'\n';

    vector<int> k = {9, 2, 9, 2, 5, 5, 2, 2, 2, 1};     // Found using the human face drawn on the boulder

    cout<<decrypt(s, k);

    return 0;
}

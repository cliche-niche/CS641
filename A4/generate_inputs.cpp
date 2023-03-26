#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <string.h>

using namespace std;




int main(){
    FILE *fr;
    fr = fopen("input.txt","w+");
    string diff = bitset<64> (5940).to_string();
    // string input [100000];
    for (int i = 0; i < 100000; i++){
        string s = bitset<64> (i).to_string();
        for (int j = 0; j < 64; j++){
            if (diff[j]==s[j])
                // input[i].append("0");
                fprintf(fr, "0" );
            else
                // input [i].append("1");
                fprintf(fr, "1" );
        }
        // cout<< input [i] << endl;
        fprintf(fr, "\n" );
    }
}


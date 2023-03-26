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
        for (int j = 0; j < 16; j++){
            string t = "";
            for(int k = 0; k < 4; k++){
                if (diff[j*4+k]==s[j*4+k])
                    t.append("0");
                    // fprintf(fr, "0");

                else
                    t.append("1");
                    // fprintf(fr, "1");
            }
            
            if(t == "0000")
                fprintf(fr,"f");
            
            else if(t == "0001")
                fprintf(fr,"g");

            else if(t == "0010")
                fprintf(fr,"h");

            else if(t == "0011")
                fprintf(fr,"i");

            else if(t == "0100")
                fprintf(fr,"j");

            else if(t == "0101")
                fprintf(fr,"k");

            else if(t == "0110")
                fprintf(fr,"l");

            else if(t == "0111")
                fprintf(fr,"m");

            else if(t == "1000")
                fprintf(fr,"n");

            else if(t == "1001")
                fprintf(fr,"o");

            else if(t == "1010")
                fprintf(fr,"p");

            else if(t == "1011")
                fprintf(fr,"q");

            else if(t == "1100")
                fprintf(fr,"r");

            else if(t == "1101")
                fprintf(fr,"s");

            else if(t == "1110")
                fprintf(fr,"t");

            else if(t == "1111")
                fprintf(fr,"u");
            
           
        }
        // cout<< input [i] << endl;
        fprintf(fr, "\n" );
    }
    fclose(fr);
}


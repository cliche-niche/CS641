#include <bits/stdc++.h>

using namespace std;

void shift(string s, int k){
    cout<<"Key = "<<k<<'\n';
    for(auto &i : s){
        if('a' <= i && i <= 'z'){
            i = (i - 'a' + k) % 26 + 'a';
        }
    }
    cout<<"Shifted text : "<<s<<"\n\n";
}

int main(){
    string s = \
                "Mewa wa mey twsam iepjoys gt mey ipbya. "
                "Pa xgn iph ayy, meysy wa hgmewhr gt whmysyam wh mey iepjoys. "
                "Agjy gt mey kpmys iepjoysa vwkk oy jgsy whmysyamwhr meph mewa ghy! "
                "Mey iguy nayu tgs mewa jyaapry wa p awjfky anoamwmnmwgh iwfeys wh vewie uwrwma epby oyyh aewtmyu ox 8 fkpiya. "
                "Mey fpaavgsu wa \"mxSrN03uwdd\" vwmegnm mey dngmya.";
    
    transform(s.begin(), s.end(), s.begin(), ::tolower);

    for(int k = 0; k < 26; k++){
        shift(s, k);
    }    

    return 0;
}
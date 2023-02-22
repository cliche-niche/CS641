#include <bits/stdc++.h>

using namespace std;

void give_frequency(string (&s)){
    map<char, int> m;

    for(auto &i : s){
        if(i<='z' && i>='a'){
            m[i]++;
        }else if(i<='Z' && i>='A'){
            m[i]++;
        }
    }

    cout<<'\n';
    for(auto &i : m){
        cout<<i.first<<':'<<i.second<<", ";
    }
    cout<<'\n';
}

void fill(map<char, set<int> > (&m), const string (&t)){
    for(int i=0; i<t.length(); i++){
        if(t[i]<='z' && t[i]>='a'){
            m[t[i]].insert(i);
        }
    }
}

void substitute(string (&t), char x, char y, map<char, set<int> > (&m), map<char, char> (&c), map<char, char> (&a)){
    x = tolower(x); y = toupper(y);
    c[x] = y;
    a[y] = x;
    for(auto &i : m[x]){
        t[i] = y;
    }
}

void un_substitute(string (&t), char y, map<char, set<int> > (&m), map<char, char> (&c), map<char, char> (&a)){
    y = toupper(y);
    c[a[y]] = a[y];
    for(auto &i : m[a[y]]){
        t[i] = a[y];
    }
    a[y] = y;
}

int main(){

    // * Original Cipher text on which substitution cipher was applied directly but did not work.
    // string s = \
    //             "qmnjvsa nv wewc flct vprj tj tvvplvl fv xja vqildhc "
    //             "xmlnvc nacyclpa fc gyt vfvw. fv wgqyp, pqq pqcs y wsq "
    //             "rx qmnjvafy cgv tlvhf cw tyl aeuq fv xja tkbv cqnsqs. "
    //             "lhf avawnc cv eas fuqb qvq tc yllrqr xxwa cfy. psdc uqf "
    //             "avrqc gefq pyat trac xwv taa wwd dv eas flcbq. vd trawm "
    //             "vupq quw x decgqcwt, yq yafl vlqs yqklhq! snafq vml "
    //             "lhvqpawr nqg_vfusr_ec_wawy qp fn wgawdgf.";


    // * Truncated text provided by the `.ipynb` file after applying inverse permutation.
    // (The spaces and punctations have been retained manually by corresponding between the original cipher text and the output text)
    string s = \
                "jnvqmvn ws afcl ewpv rctt jv jtvllvp jx afv lidvqmx "
                "lhcnca nvlcpcyg cy afv fwtv. gw qfvqp, qyp scyp q rqx "
                "ws jnvqmcyg afv lhvtt wy fcu eqla jx afv vbct kqssqn. "
                "afv lhcnca ws afv eqbv uqy cl qtrqxl rcaf xwd. scyp afv "
                "uqgce rqyp afqa rctt tva xwd wda ws afv eqbvl. ca rwdtp "
                "uqmv xwd q uqgcecqy, yw tvll afqy kqssqn! lhvqm afv "
                "hqllrwnp afv_uqgce_ws_rqyp aw gw afn";
    

    string t = s;
    transform(t.begin(), t.end(), t.begin(), ::tolower);

    map<char, char> mapping, inv_mapping;
    map<char, set<int> > index;
    fill(index, t);


    int x = 1;
    char a, b;
    while(x){
        cout<<endl;
        cout<<"Original message:\n"<<s<<"\n\nCurrent Message:\n"<<t;
        cout<<"\n"; give_frequency(t);
        cout<<"\n\nPress:\n";
        cout<<"1 - To substitute a letter for a letter\n";
        cout<<"2 - To undo the substitution of a letter\n";
        cout<<"3 - To stop substituting characters\n\n";

        cin>>x;

        switch (x)
        {
        case 1:
            cout<<"\nEnter the first letter: "; cin>>a;
            cout<<"Enter the second letter: "; cin>>b;
            substitute(t, a, b, index, mapping, inv_mapping);
            break;

        case 2:
            cout<<"Enter the letter: "; cin>>a;
            un_substitute(t, a, index, mapping, inv_mapping);
            break;

        case 3:
            x = 0;
            break;

        default:
            break;
        }
    }

    cout<<endl;
    cout<<"Here is the final mapping:\n";
    for(auto &i : mapping){
        cout<<i.first<<":"<<i.second<<", ";
    }
    cout<<"\nAnd the final deciphered message: \n"<<t;

    return 0;
}

/*
Here is the final mapping:
a:T, b:V, c:I, d:U, e:C, f:H, g:G, h:P, i:Q, j:B, l:S, m:K, n:R, p:D, q:A, r:W, s:F, t:L, u:M, v:E, w:O, x:Y, y:N, 
And the final deciphered message:
BREAKER OF THIS CODE WILL BE BLESSED BY THE SQUEAKY SPIRIT RESIDING IN THE HOLE. GO AHEAD, AND FIND A WAY OF 
BREAKING THE SPELL ON HIM CAST BY THE EVIL kAFFAR. THE SPIRIT OF THE CAVE MAN IS ALWAYS WITH YOU. FIND THE MAGIC
WAND THAT WILL LET YOU OUT OF THE CAVES. IT WOULD MAKE YOU A MAGICIAN, NO LESS THAN kAFFAR! SPEAK THE PASSWORD 
THE_MAGIC_OF_WAND TO GO THR
*/
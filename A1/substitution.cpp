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
    string s = \
                "Mewa wa mey twsam iepjoys gt mey ipbya. "
                "Pa xgn iph ayy, meysy wa hgmewhr gt whmysyam wh mey iepjoys. "
                "Agjy gt mey kpmys iepjoysa vwkk oy jgsy whmysyamwhr meph mewa ghy! "
                "Mey iguy nayu tgs mewa jyaapry wa p awjfky anoamwmnmwgh iwfeys wh vewie uwrwma epby oyyh aewtmyu ox 8 fkpiya. "
                "Mey fpaavgsu wa \"mxSrN03uwdd\" vwmegnm mey dngmya.";
    

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
a:S, b:V, d:Q, e:H, f:P, g:O, h:N, i:C, j:M, k:L, m:T, n:U, o:B, p:A, r:G, s:R, t:F, u:D, v:W, w:I, x:Y, y:E, 
And the final deciphered message: 
THIS IS THE FIRST CHAMBER OF THE CAVES. AS YOU CAN SEE, THERE IS NOTHING OF INTEREST IN THE CHAMBER. SOME OF THE LATER CHAMBERS WILL BE MORE 
INTERESTING THAN THIS ONE! THE CODE USED FOR THIS MESSAGE IS A SIMPLE SUBSTITUTION CIPHER IN WHICH DIGITS HAVE BEEN SHIFTED BY 8 PLACES. THE 
PASSWORD IS "TYRGU03DIQQ" WITHOUT THE QUOTES.
*/
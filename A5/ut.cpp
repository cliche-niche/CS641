#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <bits/stdc++.h>

using namespace std;

const int POLY = 131;   // x^7 + x^1 + 1
vector< vector<int> > pows(128, vector<int>(127, 0));

int to_int(char, char);
int to_int(string);
string conv_to_string(int);
string conv_to_string(vector<int>);
int add(int, int);
int mul(int, int);
int exp(int, int);
void fill_pows();

int eval_diag(int, int, int);
set< vector<int> > solve_diag(vector<int>);
vector<int> solve_tria(vector<int>);


int to_int(char a, char b){
    if(a < 'f' || a > 'm'){
        cout << "First letter should be between [f, m]." << endl;
        exit(1);
    }

    if(b < 'f' || b > 'u'){
        cout << "Second letter should be between [f, u]." << endl;
        exit(1);
    }

    return (a - 'f') * 16 + (b - 'f');
}

int to_int(string t){
    if(t.size() != 2){
        cout << "Cannot convert a string of size (" << t.size() << ") to required int." << endl;
        exit(1);
    }

    if(t[0] < 'f' || t[0] > 'm'){
        cout << "First letter should be between [f, m]." << endl;
        exit(1);
    }

    if(t[1] < 'f' || t[1] > 'u'){
        cout << "Second letter should be between [f, u]." << endl;
        exit(1);
    }

    return (t[0] - 'f') * 16 + (t[1] - 'f');
}

string conv_to_string(const int t){
    if(t > 127 || t < 0){
        cout << "Given integer (" << t << ") is out of expected range." << endl;
        exit(1); 
    }

    string s = "";
    s += (char) (t / 16 + 'f');
    s += (char) (t % 16 + 'f');
    return s;
}

string conv_to_string(vector<int> v){
    if(v.size() != 8){
        cout << "The number of integers must be 8." << endl;
        exit(1); 
    }

    string s = "";
    for(const auto (&x) : v){
        s += conv_to_string(x);
    }
    return s;
}

int find_i(vector<int> out){
    for(int k=0; k<out.size(); k+=1){
        if(out[k]!=0){
            return k+1;
        }
    }   
}



vector <int> string_to_vector(string line){
    int vector_element;
    vector <int> line_vector;
    if (line.size() != 16){
        cout << "Invalid output line." << endl;
        exit(1);
    } 
    else{
        for(int j=0; j<16; j+=2){
            vector_element = to_int(line[j],line[j+1]);
            line_vector.push_back(vector_element);
        }
        return line_vector;
    }
}

vector <vector <int>> get_vectors_i (int i, string filename){
    // string filename = "fout.txt"
    vector <vector <int>> vectors_i;
    vector <int> line_vector;
    
    int n = 128*(i-1)+1; 
    int m = 128*(i); 
    string line;
    int current_line = 1;

    ifstream infile(filename);
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (current_line >= n && current_line <= m) {
                line_vector = string_to_vector(line);
                vectors_i.push_back(line_vector);
            }
            if (current_line > m) {
                break;
            }
            current_line++;
        }
        infile.close();
    }
    return vectors_i;
}

int exp(int a, int e){
    int r = 1;

    while(e){
        if(e & 1){
            r = mul(r, a);
        }
        a = mul(a, a);
        e >>= 1;
    }

    return r;
}

void fill_pows(){
    for(int v = 0; v < pows.size(); v++){
        pows[v][0] = 1;
        for(int e = 1; e < pows[v].size(); e++){
            pows[v][e] = mul(pows[v][e-1], v);
        }
    }

}

int add(int a, int b){
    int r = (a ^ b);
    if(r & (1 << 7)){
        r = r ^ POLY;
    }
    return r;
}

int mul(int a, int b){
    int r = 0;
    while(b){
        if(b & 1){
            r = (r ^ a);
            if(r & (1 << 7)){
                r = r ^ POLY;
            }
        }
        a <<= 1;
        if(a & (1 << 7)){
            a = a ^ POLY;
        }
        b >>= 1;
    }
    return r;
}

int eval_diag(int v, int a, int e){     // v EAEAE = (((v_i)^e_i a_ii)^e_i a_ii)^e_i
    return exp(mul(exp(mul(exp(v, e), a), e), a), e); // v = x
}


vector<int> solve_tria(vector<int> v){      // @TODO
    vector<int> sol(2);     // sol[0] = a_{ii}, sol[1] = e_i
    return sol;
}

set< vector<int> > solve_diag(vector<int> v){
    vector<int> sol(2);                 // sol[0] = a_{ii}, sol[1] = e_i

    set< vector<int> > candidates, new_cands; // candidates are all a_{ii} and e_i. new_cands are the 

    for(int a = 0; a < 128; a++){
        for(int e = 0; e < 127; e++){
            sol[0] = a;
            sol[1] = e;
            candidates.insert(sol);
        }
    }

    for(int i = 0; i < v.size(); i++){ // for all 8 i's? why are we doing this?
        new_cands.clear();

        for(auto c : candidates){
            if(eval_diag(i+1, c[0], c[1]) == v[i]){ // makes sense
                new_cands.insert(c); // yep
            }
        }

        candidates = new_cands; 
    }

    return candidates;
}



int main(){
    vector <vector <int>> vectors_i;
    set < vector<int> > new_new_cands;
    set < vector<int> > new_cands;
    vectors_i = get_vectors_i(7, "fout.txt");
    for (int k = 0; k < vectors_i.size(); k++){
        new_cands = solve_diag(vectors_i[k]);
        for (const auto& vec : new_cands) {
            for (const auto& elem : vec) {
                cout << elem << " ";
            }
        cout << std::endl;
    }
    }
    // for(int i = 0; i < 128; i++){
    //     for(int j = 0; j < 8; j++){
    //         cout << vectors_i[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
}

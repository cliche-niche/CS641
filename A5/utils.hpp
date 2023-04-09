#ifndef UTILS_HPP
#define UTILS_HPP

#include <bits/stdc++.h>

using namespace std;

const int POLY = 131;   // x^7 + x^1 + 1
vector< vector<int> > pows(128, vector<int>(127, 0));

int to_int(char, char);
int to_int(string);
string conv_to_string(int);
string conv_to_string(vector<int>);
string mul_string(string, int);
int add(int, int);
int mul(int, int);
int exp(int, int);

int find_i(vector<int>);
vector< vector<int> > get_vectors_i(int, string);

set< vector<int> > solve_diag(vector<int>);
bool check_sol(int, int, vector< vector<int> >, vector< vector<int> >, vector<int>);
int eval_diag(int, int, int);
vector<int> vector_exponent(vector<int>, const vector<int>&);
vector<int> vector_matrix(vector<int>, const vector< vector<int> > );
vector<int> simulate_aes(vector<int>, const vector<int>, const vector< vector<int> >);

void inc_vector(vector<int>&);
string to_ascii_string(string);
string decrypt_password(string, const vector<int>, const vector< vector<int> >);



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

vector <int> string_to_vector(string line){
    int vector_element;
    vector <int> line_vector;
    if (line.size() != 16){
        cout << "Invalid output line." << endl;
        exit(1);
    } 
    
    for(int j = 0; j < 16; j += 2){
        line_vector.push_back(to_int(line[j], line[j + 1]));
    }
    return line_vector;
}

int find_i(vector<int> out){
    for(int i = 0; i < out.size(); i++){
        if(out[i] != 0){
            return i + 1;
        }
    }
    return 0;
}

vector <vector <int> > get_vectors_i (int i, string filename = "fout.txt"){
    // 1-based indexing on i
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
    }
    infile.close();
    return vectors_i;
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

set< vector<int> > solve_diag(vector<int> v){
    vector<int> sol(2);                 // sol[0] = a_{ii}, sol[1] = e_i

    set< vector<int> > candidates, new_cands;

    for(int a = 0; a < 128; a++){
        for(int e = 0; e < 127; e++){
            sol[0] = a;
            sol[1] = e;
            candidates.insert(sol);
        }
    }

    for(int i = 0; i < v.size(); i++){
        new_cands.clear();

        for(auto c : candidates){
            if(eval_diag(i, c[0], c[1]) == v[i]){
                new_cands.insert(c);
            }
        }

        candidates = new_cands;
    }

    return candidates;
}

bool check_sol(int i, int k, vector< vector<int> > outputs, vector< vector<int> > a, vector<int> e){
    // Solves for a_{i, i+k}
    vector<int> v(8, 0), res;

    for(int c = 0; c < 128; c++){
        v[i] = c;
        res = simulate_aes(v, e, a);

        // for(int j = i; j <= i + k; j++){
            if(res[i + k] != outputs[c][i + k]){
                return false;
            }
        // }
    }

    return true;
}

int eval_diag(int v, int a, int e){     // v EAEAE = (((v_i)^e_i a_ii)^e_i a_ii)^e_i
    return exp(mul(exp(mul(exp(v, e), a), e), a), e); 
}

vector<int> vector_exponent(vector<int> v, const vector<int> (&e)){
    for(int i = 0; i < 8; i++){
        v[i] = exp(v[i], e[i]);
    }
    return v;
}

vector<int> vector_matrix(vector<int> v, const vector< vector<int> > a){
    vector<int> p(8, 0);

    for(int j = 0; j < 8; j++){
        for(int i = 0; i < 8; i++){
            p[j] = add(p[j], mul(v[i], a[i][j]));
        }
    }

    return p;
}

string mul_string(string operand_string, int n){
    string multiplied_string = "";
    for(int i = 0; i < n; i++){
        multiplied_string += operand_string;
    }
    return multiplied_string;
}

vector<int> simulate_aes(vector<int> v, const vector<int> e, const vector< vector<int> > a){
    v = vector_exponent(v, e);
    v = vector_matrix(v, a);
    v = vector_exponent(v, e);
    v = vector_matrix(v, a);
    v = vector_exponent(v, e);
    
    return v;
}

void inc_vector(vector<int> (&v)){
    for(auto &c : v){
        if(c == 15){
            c = 0;
        }else{
            c++;
        }
    }
}

string to_ascii_string(string decrypted_password){
    if(decrypted_password.size() != 32){
        cout << "Decrypted password is incorrect." << endl;
        exit(1);
    }
    else{
        string required_password = "";
        for (int i = 0; i < 32; i+=2){
            string s = decrypted_password.substr(i,2);
            char c = 16 * (s[0] - 'f') + (s[1] - 'f');
            required_password += c;
        }
        return required_password;
    }
}

string decrypt_password(string half_encrypted_password, const vector<int> e, const vector< vector<int> > a){
    vector <int> half_encrypted_password_vector = string_to_vector(half_encrypted_password);
    string half_decrypted_password = "";
    for(int p = 0; p < 8; p++){
        for(int q = 0; q < 128; q++){
            string input = half_decrypted_password + conv_to_string(q) + mul_string("f", 14-half_decrypted_password.size());
            if (half_encrypted_password_vector[p] == simulate_aes(string_to_vector(input), e, a)[p]){
                half_decrypted_password += conv_to_string(q);
                break;
            }

        }
    }
    return half_decrypted_password;
}

#endif

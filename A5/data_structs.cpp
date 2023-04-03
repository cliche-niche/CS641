#include "data_structs.hpp"

const int POLY = 131;   // x^7 + x^1 + 1
vector< vector<int> > pows(128, vector<int>(127, 0));

letter::letter() {;}

letter::letter(int v){
    this->val = (v + POLY) % POLY;
}

letter::letter(char a, char b){
    if(a < 'f' && a > 'm'){
        cout << "First letter out of range (" << a << ")" << endl;
        exit(1); 
    }

    if(b < 'f' && b > 'u'){
        cout << "Second letter out of range (" << b << ")" << endl;
        exit(1); 
    }

    this->val = ((a - 'f') << 4) + (b - 'f');
}

letter::letter(string t){
    if(t.size() != 2){
        cout << "Cannot make letter from string of size (" << t.size() << ")" << endl;
        exit(1);
    }

    if(t[0] < 'f' && t[0] > 'm'){
        cout << "First letter out of range (" << t[0] << ")" << endl;
        exit(1); 
    }

    if(t[1] < 'f' && t[1] > 'u'){
        cout << "Second letter out of range (" << t[1] << ")" << endl;
        exit(1); 
    }

    this->val = ((t[0] - 'f') << 4) + (t[1] - 'f');
}

void letter::upd_val(int v){
    if(v > 127 || v < 0){
        cout << "Value (" << v << ") is out of bounds, expecting [0, 127]" << endl;
        exit(1); 
    }

    val = v;
}

void letter::upd_val(string t){
    if(t.size() != 2){
        cout << "Cannot make letter from string of size (" << t.size() << ")" << endl;
        exit(1);
    }

    if(t[0] < 'f' && t[0] > 'm'){
        cout << "First letter out of range (" << t[0] << ")" << endl;
        exit(1); 
    }

    if(t[1] < 'f' && t[1] > 'u'){
        cout << "Second letter out of range (" << t[1] << ")" << endl;
        exit(1); 
    }

    this->val = ((t[0] - 'f') << 4) + (t[1] - 'f');
}

string letter::conv_to_string(){
    string s = "";
    s += ((char) ('f' + (val >> 4)));   // Upper four bits
    s += ((char) ('f' + (val % 16)));   // Lower four bits
    return s;
}

letter letter::operator +(letter const& other){
    letter l;
    l.val = (this->val ^ other.val);
    l.val %= POLY;
    return l;
}

letter letter::operator *(letter const& other){ 
    int a = this->val, b = other.val;
    letter r(mul(a, b));
    return r;
}

letter letter::exponent(int e){
    letter result(1);
    letter l(this->val);

    while(e--){
        result = result * l;
    }

    return result;
}

vector<int> letter::diag(vector<int> v){
    return solve_diag(v);
}

vector<int> letter::tria(vector<int> v){
    return solve_tria(v);
}

int to_int(string t){
    return (t[0] - 'f') * 16 + (t[1] - 'f');
}

int add(int a, int b){
    return (a ^ b) % POLY;
}

int mul(int a, int b){
    int r = 0;
    while(b){
        if(b & 1){
            r = (r ^ a);
        }
        a <<= 1;
        b >>= 1;
    }
    return r % POLY;
}

int exp(int a, int e){
    int r = 1;
    
    while(e--){
        r = mul(r, a);
    }

    return r;
}

void fill_pows(){
    letter l;

    for(int v = 0; v < pows.size(); v++){
        pows[v][0] = 1;
        for(int e = 1; e < pows[v].size(); e++){
            pows[v][e] = mul(pows[v][e-1], v);
        }
    }
}

int eval_diag(int v, int a, int e){
    return exp(mul(exp(mul(exp(v, e), a), e), a), e); // v EAEAE
}

vector<int> solve_diag(vector<int> v){
    vector<int> sol(2); // sol[0] = a_{ii}, sol[1] = e_i

    set< vector<int> > candidates;

    for(int a = 0; a < 128; a++){
        for(int e = 0; e < 127; e++){
            if((e * (e + 1) < 127 && pows[a][e*(e+1)] == v[0]) || (exp(exp(a, e + 1), e) == v[0])){
                sol[0] = a;
                sol[1] = e;
                candidates.insert(sol);
            }
        }
    }

    for(int i = 1; i < v.size(); i++){
        cout << candidates.size() << ' ';

        set< vector<int> > to_remove;
        for(auto c : candidates){
            if(eval_diag(i+1, c[0], c[1]) != v[i]){
                to_remove.insert(c);
            }
        }

        for(auto tr : to_remove){
            candidates.erase(tr);
        }

        cout << candidates.size() << endl;
    }

    for(auto c : candidates){
        cout << c[0] << ' ' << c[1] << endl;
    }

    return sol;
}

vector<int> solve_tria(vector<int> v){
    vector<int> sol(2); // sol[0] = a_{ii}, sol[1] = e_i
    return sol;
}
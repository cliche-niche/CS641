#ifndef DATA_STRUCTS_HPP
#define DATA_STRUCTS_HPP

#include <bits/stdc++.h>

using namespace std;

struct letter{
    int val = 0;        // ff to mu, i.e., 0 to 127

    letter();
    letter(int);
    letter(char, char);
    letter(string);
    void upd_val(int);
    void upd_val(string);
    string conv_to_string();
    letter operator +(letter const& other);
    letter operator *(letter const& other);
    letter exponent(int e);

    vector<int> diag(vector<int>);
    vector<int> tria(vector<int>);
};

int to_int(string);
int add(int, int);
int mul(int, int);
int exp(int, int);
void fill_pows();

int eval_diag(int, int, int);
vector<int> solve_diag(vector<int>);
vector<int> solve_tria(vector<int>);

#endif
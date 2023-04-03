#include "data_structs.hpp"

extern const int POLY;
extern vector< vector<int> > pows;

int main(){

    fill_pows();

    vector<int> v = {to_int("fm"), to_int("jf"), to_int("ig"), to_int("mp")};
    solve_diag(v);

    return 0;
}
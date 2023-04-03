#include "utils.hpp"

extern const int POLY;
extern vector< vector<int> > pows;

int main(){

    fill_pows();

    vector<int> v = {to_int("fm"), to_int("jf"), to_int("ig"), to_int("mp"), to_int("kt"), to_int("ju"), to_int("mq"), to_int("hr"), to_int("ku"), to_int("hl"), to_int("jj"), to_int("kj"), to_int("fh"), to_int("fg"), to_int("gt"), to_int("lj"), to_int("kg"), to_int("fq"), to_int("fl"), to_int("kf")};
    solve_diag(v);

    return 0;
}
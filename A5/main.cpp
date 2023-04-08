#include "utils.hpp"

vector < vector<int> > a(8, vector<int> (8, 0));
vector <int> e(8, 0);

int main(){
    vector< set< vector<int> > > candidates(8); // Candidates for (a_ii, e_i) pairs
    vector< vector <vector <int> > > outputs_i(8);

    for(int i = 0; i < 8; i++){
        outputs_i[i] = get_vectors_i(i + 1, "fout.txt");
        {
            vector<int> temp;
            for(auto v : outputs_i[i]){
                temp.push_back(v[i]);
            }
            candidates[i] = solve_diag(temp);
        }
    }
    // * At this point we have all the candidate pairs (a_ii, e_i), but no exact solutions
    // * And the outputs corresponding to each 1-hot vector

    // * We now solve for a_{i, i+1}
    for(int i = 6; i >= 0; i--){
        int cands = 0;
        for(auto c_i : candidates[i]){
            a[i][i] = c_i[0];
            e[i] = c_i[1];
            for(auto c_i1 : candidates[i + 1]){
                a[i + 1][i + 1] = c_i1[0];
                e[i + 1] = c_i1[1];

                for(int c = 0; c < 128; c++){
                    a[i][i + 1] = c;
                    cands += check_sol(i, 1, outputs_i[i], a, e);
                }
            }
        }

        if(cands == 1){
            cands = 0;
            for(auto c_i : candidates[i]){
                a[i][i] = c_i[0];
                e[i] = c_i[1];
                for(auto c_i1 : candidates[i + 1]){
                    a[i + 1][i + 1] = c_i1[0];
                    e[i + 1] = c_i1[1];

                    for(int c = 0; c < 128; c++){
                        a[i][i + 1] = c;
                        if(check_sol(i, 1, outputs_i[i], a, e)){
                            cands = 1;

                            vector<int> v;
                            candidates[i].clear();
                            v = {c_i[0], c_i[1]};
                            candidates[i].insert(v);
                            
                            candidates[i + 1].clear();
                            v = {c_i1[0], c_i1[1]};
                            candidates[i + 1].insert(v);

                            break;
                        }
                    }

                    if(cands){
                        break;
                    }
                }

                if(cands){
                    break;
                }
            }
        }else{
            break;
        }
    }
    // * At this point, we know a_{ii}, e_i, a_{i, i+1} of the matrix exactly

    // * We now just solve for a_{ij} one-by-one from lower-right to upper-left 
    for(int l = 2; l <= 7; l++){
        for(int i = 7-l; i >= 0; i--){
            int cands = 0, candidate;

            for(int c = 0; c < 128; c++){
                a[i][i + l] = c;
                if(check_sol(i, l, outputs_i[i], a, e)){
                    cands++;
                    candidate = c;
                }
            }

            if(cands == 1){
                a[i][i + l] = candidate;
            }
        }
    }
    // * At this point, we have the complete matrix A, and the exponent vector E

    cout << "The solution till now has been found to be:" << endl;
    cout << "(Note: 0's might represent garbage value)\n" << endl;

    cout << "E = [";
    for(auto ei : e){
        cout << ei << '\t';
    }
    cout << "]\n" << endl;
    
    cout << "A = [\n";
    for(auto i : a){
        cout << "[";
        for(auto j : i){
            cout << j << '\t';
        }
        cout << "]" << endl;
    }
    cout << "]\n" << endl;

    return 0;
}

#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <string.h>

using namespace std;

int main(){

    // Create a binary 2D array of outputs
    FILE *fr;
    fr = fopen("output.txt","r+");
    int bin_output_list [200000][64];
    for(int i = 0; i < 200000; i++){
        for(int j = 0; j < 64; j++){
            char a;
            fscanf(fr,"%c", &a);
            if(a=='0')bin_output_list[i][j]=0;
            else bin_output_list[i][j]=1;
        }
    }

    //Apply reverse final permutation
    int rev_final_permutation[8][8] = {{57, 49, 41, 33, 25, 17, 9, 1},
                       {59, 51, 43, 35, 27, 19, 11, 3},
                       {61, 53, 45, 37, 29, 21, 13, 5},
                       {63, 55, 47, 39, 31, 23, 15, 7},
                       {58, 50, 42, 34, 26, 18, 10, 2},
                       {60, 52, 44, 36, 28, 20, 12, 4},
                       {62, 54, 46, 38, 30, 22, 14, 6},
                       {64, 56, 48, 40, 32, 24, 16, 8}};

    int inv_fper[200000][64];
    for(int i = 0; i < 200000; i++){
        for(int j = 0; j < 64; j++){
            inv_fper[i][j] = bin_output_list[i][rev_final_permutation[j/8][j%8]-1];
        }
    }

    // Apply Expansion on R5=L6
    int expansion [48] ={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,
             18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1}

    int ex_out [200000][48];
    for(int i = 0; i < 200000; i++){
        for(int j = 0; j < 48; j++){
            ex_out[i][j] = inv_fper[i][expansion[j]-1];
        }
    }

    // Calculate XORed input at S-Boxes

    int s_in_xor[100000][48];
    for(int i = 0; i < 200000; i+=2){
        for(int j = 0; j < 48; j++){
            if(ex_out[i][j]==ex_out[i+1][j]) s_in_xor[i/2][j]=0;
            else s_in_xor[i/2][j]=1; 
        }
    }

    // XORed Fiestal output
    int in_xor[100000][64];
    for(int i = 0; i < 200000; i+=2){
        for(int j = 0; j < 64; j++){
            if(inv_fper[i][j]==inv_fper[i+1][j]) in_xor[i/2][j]=0;
            else in_xor[i/2][j]=1; 
        }
    }

    int f_out [120][32];
    for(int i = 0; i < 120; i++){
        for(int j = 32; j < 64; j++){
            f_out[i][j-32] = in_xor[i][j];
        }
    }

    // Apply inverse permutation on Fiestal output
    int inv_perm [120][32];
    for(int i = 0; i < 120; i++){
        for(int j = 0; j < 32; j++){
            inv_perm[i][j] = f_out[i][inv_permutation[i]-1];
        }
    }

    // Find key of sboxes
    int k6;
    int freq_k6;
    int keys[8][64];
    int t_s_in_xor[6];
    int t_s_out_xor[4];
    int t_ex_out1[6];
    for (int i = 0; i < 120; i++){
        for(int j = 0; j < 8, j++){
            for(int k = 0; k < 6; k++)
                t_s_in_xor[k] = s_in_xor[i][j*6+k];
            for(int k = 0; k < 4; k++)
                t_s_out_xor[k] = inv_perm[i][j*6+k];
            for(int k = 0; k < 6; k++)
                t_s_ex_out1[k] = ex_out[i][j*6+k];
            int a1[6];
            int a2[6];
            for(int l = 0; l < 64; l++){
                string a = bitset<6> (l).to_string();
                for(int m = 0; m < 6; m++){
                    if(a[m]=="0") a1[m]=0;
                    else a1[m]=1;
                    if(a1[m]==t_s_in_xor[m]) a2[m]=0;
                    else a2[m]=1;
                }
                int s_a1_xor_a2[6];
                string s_a1 = bitset<6> (s_blocks[j][2*a1[0]+a1[5]][a1[4]+2*a1[3]+4*a1[2]+8*a1[1]]).to_string();
                string s_a2 = bitset<6> (s_blocks[j][2*a2[0]+a2[5]][a2[4]+2*a2[3]+4*a2[2]+8*a2[1]]).to_string();
                for(int m = 0; m < 6; m++){
                    if(s_a1[m]==s_a2[m]) s_a1_xor_a2[m]=0;
                    else s_a1_xor_a2[m]=1;
                }

            }
        }
    }
    



}
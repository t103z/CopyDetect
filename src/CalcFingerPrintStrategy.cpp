//
// Created by zhang on 16-6-23.
//

#include <iostream>
#include <limits.h>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "CalcFingerPrintStrategy.h"
void WinnowingStrategy::Set_K_gram(int _k_gram_len) {
    k_gram_len = _k_gram_len;
}
int WinnowingStrategy::Get_K_gram() {
    return k_gram_len;
}
void WinnowingStrategy::Set_Window_len(int _window_len) {
    window_len = _window_len;
}
int WinnowingStrategy::Get_Window_len() {
    return window_len;
}
FingerPrint::hash_t WinnowingStrategy::ComputeNextHash(int hash_num, std::string &str) {
    static const int p = 6999997; //hash mod
    static const int k = 257;     //hash seed
    if(hash_num == 1) {
        for(int i = 0; i < k_gram_len; i++) {
            HashBase = (HashBase * k) % p;
            //compute the k^k_gram_ken-1 so that time can be saved
        }
        for(int i = 0; i < k_gram_len; i++) {
            HashValue = (HashValue * k + str[i]) % p;
            //compute the first Hash value in order to do rolling hash later
        }
    }
    else {
        HashValue = (HashValue * k + str[hash_num + k_gram_len - 2] - str[hash_num - 2] * HashBase) % p;
        if(HashValue < 0) {
            HashValue += p;
        }
    }
    return HashValue;
}
std::vector<FingerPrint> &&WinnowingStrategy::GetFingerPrint(std::istream &input, const std::string &name, size_t id)
{
    using namespace std;
    vector<FingerPrint> fp;
    //TODO

    //better need to input the k-gram number and window-len number by the user
    //when calling this function
    Set_K_gram(5);
    Set_Window_len(4);

    FingerPrint::hash_t * h = new FingerPrint::hash_t (window_len);
    fp.clear();
    for(int i = 0; i < window_len; i++) {
        h[i] = INT_MAX;
    }
    int right_end = 0;
    int min_index = 0;
    int count = 0;
    size_t line_count = 1;
    string str;
    char nowchar;
    while(input.get(nowchar)) {
        str[count] = nowchar;
        count ++;

        right_end = (right_end + 1) % window_len;
        if(str[count] == '\n') {
            line_count ++;
        }

        h[right_end] = ComputeNextHash(count,str);

        if(min_index == right_end) {
            for(int i = (right_end - 1) % window_len; i != right_end; i = (i - 1 + window_len) % window_len) {
                if(h[i] < h[min_index]) {
                    min_index = i;
                }
            }
            FingerPrint *newfp = new FingerPrint();
            newfp->key = h[min_index];
            newfp->info.line_number = line_count;
            newfp->info.file_name = name;
            newfp->info.id = id;
            fp.push_back(*newfp);
        }
        else {
            if(h[right_end] <= h[min_index]) {
                min_index = right_end;
                FingerPrint* newfp = new FingerPrint();
                newfp->key = h[min_index];
                newfp->info.line_number = line_count;
                newfp->info.file_name = name;
                newfp->info.id = id;
                fp.push_back(*newfp);
            }
        }
    }

    return std::move(fp);
}


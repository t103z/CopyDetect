//
// Created by zhang on 16-6-26.
//

#ifndef COPYDETECT_TEST_HELPER_H_H
#define COPYDETECT_TEST_HELPER_H_H

#include <vector>
#include <climits>
#include <string>


struct Info
{
    std::string file_name;
    size_t      line_number;
    size_t      id;
};

struct FingerPrint
{
    typedef int hash_t;

    hash_t key;
    Info info;
};


class CalcFingerPrintStrategy
{
public:
    virtual std::vector<FingerPrint> GetFingerPrint(std::istream &input, const std::string &name, size_t id) = 0;
};

class WinnowingStrategy : public CalcFingerPrintStrategy
{
private:
    int window_len;
    int k_gram_len;
    FingerPrint::hash_t HashBase;
    FingerPrint::hash_t HashValue;
    FingerPrint::hash_t ComputeNextHash(int hash_num, std::string &str);
public:
    virtual std::vector<FingerPrint> GetFingerPrint(std::istream &input, const std::string &name, size_t id);
    void Set_K_gram(int _k_gram_len);
    int Get_K_gram();
    void Set_Window_len(int _window_len);
    int Get_Window_len();
};

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



#endif //COPYDETECT_TEST_HELPER_H_H

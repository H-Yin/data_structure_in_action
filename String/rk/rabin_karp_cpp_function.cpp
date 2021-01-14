#include<iostream>
using namespace std;

int rabin_karp_search(string t, string p, size_t b, size_t r){
    size_t n = p.size(), m=t.size();
    // calculate b^n % r
    size_t power = 1;
    for(size_t i = 0; i < n; i++){
        power = (power * b ) % r;
    }
    // calculate Hash(p) and Hash(t[0,n])
    size_t hp = 0, ht = 0;
    for(size_t i =0; i < n; i++){
        ht = (ht * b + t[i]) % r;
        hp = (hp * b + p[i]) % r;
    }
    for(size_t i=0; i<m-n; i++){
        if(hp == ht){
            // compare
            size_t j = 0;
            while(j<n && t[i+j]==p[j]){
                j++;
            }
            if(j == n){
                return i;
            }
        }
        // rolling hash
        // "ht puls r" to avoid negative number
        ht = ((r + ht) * b - t[i] * power % r + t[i+n]) % r;
    }
    return -1;
}

int main(){
    string t = "For the Aho-Corasick algorithm, see:";
    string p = " th";
    size_t b = 256, r = 999983;
    cout << rabin_karp_search(t, p, b, r) << endl;
}

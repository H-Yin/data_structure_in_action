#include <iostream>
#include <string>
using namespace std;

int* get_next(string p){
    int i=0, j=-1;
    int len = p.size();
    int *next = new int[len];
    next[0] = -1;
    /*
    while(i < len-1){
        if (j ==-1 || p[i] == p[j]){
            i++;
            j++;
            if(p[i] == p[j]){
                next[i] == next[j];
            }
            else{
                next[i] = j;
            }
        }
        else{
            j = next[j];
        }
    }
    */
    while(i < len-1){
        while (j > -1 && p[i] != p[j]){
            j = next[j];
        }
        i += 1;
        j += 1;
        if (p[i] == p[j]){
            next[i] = next[j];
        }
        else{
            next[i] = j;
        }
    }
    
    return next;
}

int kmp(string t, string p){
    int i=0, j=0;
    int *next = get_next(p);
    while((i < t.size()) && (j < 0 || j < p.size())){
        if(j == -1 || t[i] == p[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    delete[] next;
    if(j>0 && j == p.size())
        return i-j;
    else
        return -1;
}

int main(){
    string t = "babcbabcabcaabcabcabcacabc";
    string p = "abcabcacab";
    cout << kmp(t, p) << endl;
    return 0;
}

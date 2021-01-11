#include <iostream>
#include <string>
using namespace std;

class KMPMatcher{
private:
    string p;
    int *next;  
    void get_next(string p){
        int i=0, j=-1;
        int len = p.size();
        next[0] = -1;
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
    }
public:
    KMPMatcher(string p):p(p){
        next = new int[p.size()];
        // DP
        get_next(p);
    }
    ~KMPMatcher(){
        delete[] next;
    }
    int match(string t){
        int i=0, j=0;
        while((i < t.size()) && (j < 0 || j < p.size())){
            if(j == -1 || t[i] == p[j]){
                i++;
                j++;
            }else{
                j = next[j];
            }
        }
        if(j>0 && j == p.size())
            return i-j;
        else
            return -1;
    }
};

int main(){
    string t = "babcbabcabcaabcabcabcacabc";
    string p = "abcab";
    KMPMatcher kmp(p);

    cout << kmp.match("babcbabcabcaabcabcabcacabc") << endl;
    cout << kmp.match("bcaabcabcabcacabc") << endl;
    return 0;
}

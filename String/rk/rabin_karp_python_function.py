
def rabin_karp_search(t, p, b=256, r=999983):
    m, n = len(t), len(p)
    # calculate b**n % r
    power = 1
    for i in range(n):
        power = power * b % r;
    # calculate hash(P) and hash[t[:l]]
    hp, ht = 0, 0 
    for i in range(n):
        hp = (hp * b + ord(p[i])) % r
        ht = (ht * b + ord(t[i])) % r

    for i in range(m-n):
        if hp == ht and p == t[i:i+n]:
            return i
        # rolling hash
        ht = ((r + ht) * b - ord(t[i]) * power % r + ord(t[i+n])) % r

def common_substring_search_by_rk(t, p, l, b=256, r=999983):
    m, n = len(t), len(p)
    power = 1
    for i in range(l):
        power = power * b % r;
    
    hp, ht = 0, 0
    ht_dict = {}
    for i in range(l):
        ht = (ht * b + ord(t[i])) % r
    ht_dict[ht] = t[:l]
    for i in range(1, m - l + 1):
        ht = ((r + ht) * b - ord(t[i-1]) * power % r + ord(t[i+l-1])) % r
        ht_dict[ht] = t[i:i+l]

    for i in range(l):
        hp = (hp * b + ord(p[i])) % r
    if hp in ht_dict and ht_dict[hp] == p[:l]:
        return p[:l]
    for i in range(1, n - l):
        hp = ((r + hp) * b - ord(p[i-1]) * power % r + ord(p[i+l-1])) % r
        if hp in ht_dict and ht_dict[hp] == p[i:i+l]:
            return p[i:i+l]
    return None

def multi_pattern_search_by_rk(t, ps, n, b=256, r=999983):
    m = len(t)
    power = 1
    for i in range(n):
        power = power * b % r;
    
    hp_dict = {}
    for p in ps:
        hp = 0
        for i in range(n):
            hp = (hp * b + ord(p[i])) % r
        hp_dict[hp] = p
    res = []
    ht = 0
    for i in range(n):
        ht = (ht * b + ord(t[i])) % r
    for i in range(0, m - n+1):
        if ht in hp_dict and hp_dict[ht] == t[i:i+n]:
            res.append((i, hp_dict[ht]))
        if i >= m - n:
            break
        ht = ((r + ht) * b - ord(t[i]) * power % r + ord(t[i+n])) % r
    return res


if __name__ == '__main__':
    print(rabin_karp_search("hello", 'll'))
    print(common_substring_search_by_rk("/pandas/core/internals/managers.py", '/core/internals/managers.py', 3))
    print(multi_pattern_search_by_rk("/pandas/core/internals/managers.py", ['.py', 'cor'], 3))


def get_next(p):
    _next = [0] *len(p)

    i, j = 0, -1
    _next[0] = -1
    '''
    while i < len(p)-1:
        if j == -1 or p[i] == p[j]:
            i += 1
            j += 1
            _next[i] = _next[j] if p[i] == p[j] else j
        else:
            j = _next[j]
    '''
    while i < len(p)-1:
        while j >= 0 and p[i] != p[j]:
            j = _next[j]
        i += 1
        j += 1
        _next[i] = _next[j] if p[i] == p[j] else j
    return _next

def kmp(t, p):
    i, j = 0, 0
    _next = get_next(p)
    while i<len(t) and j < len(p):
        if j ==-1 or t[i] == p[j]:
            i += 1
            j += 1 
        else:
            j = _next[j]
    if j == len(p):
        return i - j
    else:
        return -1

if __name__ == '__main__':
    print(kmp('tstsasdadababcabcaabcabcabcacabc', 'ababc'))

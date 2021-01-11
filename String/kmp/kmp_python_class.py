
class KMPMatcher(object):
    def __init__(self, p):
        self.p = p
        self._next = self._get_next(p)

    def _get_next(self, p):
        _next = [0] *len(p)
        i, j = 0, -1
        _next[0] = -1
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
        '''
        return _next
    
    def match(self, t):
        i, j = 0, 0
        while i<len(t) and j < len(self.p):
            if j ==-1 or t[i] == self.p[j]:
                i += 1
                j += 1 
            else:
                j = self._next[j]
        if j == len(self.p):
            return i - j
        else:
            return -1

if __name__ == '__main__':
    kmp = KMPMatcher('ababc')
    print(kmp.match('tstsasdadababcabcaabcabcabcacabc'))
    print(kmp.match('tstsacaabacb'))

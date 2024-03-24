#include <bits/stdc++.h>
#define fi(i,a,b) for(i=a;i<=b;i++)
#define ll long long
#define ff first
#define ss second
#define ii pair<int, int>
#define iii pair<ll, pair<int, int>>
#define MASK(c) (1LL << (c))
const ll N = 2e5 + 30;
const ll oo = 1e9 + 7;
const ll base = 7013;
const ll inf = 1e9 + 7;
using namespace std;

template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        if (x > y)
        {
            x = y;
            return 1;
        }
        return 0;
    }
template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        if (x < y)
        {
            x = y;
            return 1;
        }
        return 0;
    }
template<class T>
    T Abs(const T &x) {
        return (x < 0 ? -x : x);
    }

///

// Author : Hoang Minh Thai (just call me Fred Hoang).
// User's name : meanthai (available on all platforms).
// countdown 0 days before the national exam for the gifted - VOI.
/*
     /\_/\
    (  ._.)
    / >() \>()
*/

string txt, pat;
int lps[N];
ll powx[N], h[N];
int badchar[256];

void BM(string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();
    int i;
 
    for (i = 0; i < 256; i++)
        badchar[i] = -1;
 
    for (i = 0; i < m; i++)
        badchar[(int)pat[i]] = i;
 
    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pat[j] == (int)txt[s + j]) j--;
        if (j < 0) {
            cout << s + 1 << ' ';
            s += (s + m < n) ? m - badchar[(int)txt[s + m]] : 1;
        }
 
        else s += max(1, j - badchar[(int)txt[s + j]]);
    }

    return;
}

void hashing(string txt, string pat)
{
    int n = txt.length(), m = pat.length();
    txt = ' ' + txt;
    pat = ' ' + pat;
    
    powx[0] = 1;

    ll pattern_code = 0;

    for(int i = 1; i <= m; i++) 
    {
        pattern_code = (pattern_code * base + pat[i] - 'a' + 1) % oo;
    }

    for(int i = 1; i <= n; i++)
    {
        h[i] = (h[i - 1] * base + txt[i] - 'a' + 1) % oo;
        powx[i] = powx[i - 1] * base % oo;
    }

    for(int i = 1; i <= n - m + 1; i++)
    {
        if(((h[i + m - 1] - h[i - 1] * powx[i + m - 1 - i + 1] + oo * oo) % oo) == pattern_code) cout << i << ' ';
    }

    return;
}

void KMP(string txt, string pat)
{
    int n = txt.length(), m = pat.length();
    int len = 0;
    lps[0] = 0;

    for(int i = 1; i <= m; i++)
    {
        if(pat[i] == pat[len])
        {
            lps[i] = ++len;
        }
        else
        {
            if(len)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
            }
        }
    }

    int i = 0, j = 0;

    while((n - i) >= (m - j))
    {
        if(pat[j] == txt[i])
        {
            i++;
            j++;
        }

        if(j == m)
        {
            cout << i - j + 1 << ' ';
            j = lps[j - 1];
        }

        else if(i < n && pat[j] != txt[i])
        {
            if(j) j = lps[j - 1];
            else i++;
        }
    }

    return;
}

void process()
{
    cin >> txt;
    cin >> pat;
    KMP(txt, pat);
    hashing(txt, pat);
    BM(txt, pat);
    return;
}
/*
3
100 50 25a

*/
int main()
{
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("test.inp", "r", stdin);
    // freopen("test.out", "w", stdout);
    int test = 1;
    //cin >> test;
    while(test --) process();
    return 0;
}

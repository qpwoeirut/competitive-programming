#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9 + 7;
typedef pair<int, int> pii;

int solve(const string& s)
{
	int n = s.size();

	bool ok = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i] != s[0])
		{
			ok = 1;
		}
	}
	
	if (!ok)
	{
		return 0;
	}
	int ans = INF;
	for (int k = 0; k < 10; k++)
	{
		int mn = n, mx = -1;
		for (int i = 0; i < n; i++)
		{
			if (s[i] - '0' == k)
			{
				mn = min(mn, i);
				mx = max(mx, i);
			}
		}
		
		if (mx == -1 || mx == mn)
		{
			continue;
		}
		
		vector<int> mv(10, INF);
		bool ok = 1;
		bool z = 0;
		int res = 0;
		vector<int> cz;
		for (int i = 0; i < mn; i++)
		{
			if (s[i] - '0' < k)
			{
				ok = 0;
				cz.push_back(i);
				continue;
			}
			if ((cz.empty() && mv[s[i] - '0'] != INF) || (!cz.empty() && mv[s[i] - '0'] < cz[0]))
			{
				z = 1;
			}
			mv[s[i] - '0'] = min(mv[s[i] - '0'], i);
		}
		if (!ok)
		{
			if (!z)
			{
				continue;
			} else
			{
				bool ck = 0;
				for (int i = cz.back() + 1; i < mn; i++)
				{
					if (mv[s[i] - '0'] < cz[0])
					{
						ck = 1;
					}
				}
				//~ cout << ck << " " << cz[0] << " " << mn << " " << cz.back() << "\n";
				if (ck)
				{
					res += 1;
				} else
				{
					res += 2;
				}
			}
		}
		ok = 1, z = 0;
		mv = vector<int> (10,-1);
		cz.clear();
		for (int i = n - 1; i > mx; i--)
		{
			if (s[i] - '0' > k)
			{
				ok = 0;
				cz.push_back(i);
				continue;
			}
			if ((cz.empty() && mv[s[i] - '0'] != -1) || (!cz.empty() && mv[s[i] - '0'] > cz[0]))
			{
				z = 1;
			}
			mv[s[i] - '0'] = max(mv[s[i] - '0'], i);
		}
		
		if (!ok)
		{
			if (!z)
			{
				continue;
			} else
			{
				bool ck = 0;
				for (int i = cz.back() - 1; i > mx; i--)
				{
					if (mv[s[i] - '0'] > cz[0])
					{
						ck = 1;
					}
				}
				if (ck)
				{
					res += 1;
				} else
				{
					res += 2;
				}
			}
		}
		
		ans = min(ans, res + 1 + (mn != 0) + (mx != n - 1));
	}
	if (ans == INF)
	{
        return -1;
	}
    return ans;
}

int brute(const string& s) {
    set<string> visited;
    queue<pair<string, int>> q;
    q.emplace(s, 0);
    while (q.size() > 0) {
        const auto cur = q.front(); q.pop();

        if (count(cur.first.begin(), cur.first.end(), cur.first[0]) == s.size()) return cur.second;

        for (int i=0; i<cur.first.size(); ++i) {
            for (int j=i+1; j<cur.first.size(); ++j) {
                if (cur.first[i] == cur.first[j]) {
                    string nstr = cur.first;
                    for (int k=i; k<=j; ++k) nstr[k] = nstr[i];
                    if (visited.insert(nstr).second == true) q.emplace(nstr, cur.second + 1);
                }

                string nstr = cur.first;
                sort(nstr.begin() + i, nstr.begin() + j + 1);
                if (visited.insert(nstr).second == true) q.emplace(nstr, cur.second + 1);
            }
        }
    }

    return -1;
}

void test() {
    mt19937 rng(8);
    for (int n=2; n<=10; ++n) {
        cerr << "n = " << n << endl;
        for (int t=0; t<10000; ++t) {
            string s = "";
            for (int i=0; i<n; ++i) {
                s += '0' + (rng() % 10);
            }

            const int bans = brute(s);
            const int sans = solve(s);
            if (bans != sans) {
                cout << s << endl;
                cout << bans << ' ' << sans << endl;
            }
            assert(bans == sans);
        }
    }
}

int main()
{
    test();

	int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n;
        cin >> s;
        solve(s);
    }

 return 0;
}

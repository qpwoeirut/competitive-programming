#include <iostream>
#include <algorithm>
#include <map>
#include <iomanip>
#include <cassert>
using namespace std;

int N, Q;
map<int, double> A;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> Q;
    for (int i = 0, x; i < N; i++)
    {
        cin >> x;
        A[i] = x;
    }

    for (int i = 0, ql, qr; i < Q; i++)
    {
        cin >> ql >> qr;
        ql--, qr--;
        if (ql == qr)
            continue;
        auto st = A.lower_bound(ql);
        assert(st != A.end());
        auto en = A.upper_bound(qr);
        assert(en != A.begin());
        double cur = 0;
        for (auto it = st; it != en;) 
        {
            cur += it->second;
            auto tmp = it;
            it++;
            A.erase(tmp);
        }
        A[ql] = A[qr] = cur/2;
    }

    for (int i = 0; i < N; i++)
        cout << fixed << setprecision(10) << A[i] << " ";
    cout << "\n";

    return 0;
}

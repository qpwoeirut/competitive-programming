//presents.cpp created at 02/03/21 18:59:24

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;

int main() {
    freopen("presents.in", "r", stdin);
    freopen("presents.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        ll weight;
        char type;
        ll length, width, height;

        cin >> weight >> type >> length >> width >> height;

        weight /= 10;
        weight *= 5;
        ans += weight;

        ll volume = length * width * height;
        assert(volume % 10 == 0);
        volume /= 10;
        if (type == 'r') {

        } else if (type == 't') {
            //assert(volume % 2 == 0);
            volume /= 2;
        } else if (type == 'p') {
            //assert(volume % 3 == 0);
            volume /= 3;
        }

        ans += volume;
    }

    cout << ans << endl;
}


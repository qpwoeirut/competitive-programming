#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000000001;

int N;

struct Node {
    Node* lft;
    Node* rht;

    int lo, hi;

    int sum, pmax;

    int lazy;

    Node(int _lo, int _hi) {
        lft = nullptr;
        rht = nullptr;

        lo = _lo;
        hi = _hi;
        //assert(lo < hi);

        sum = 0;
        pmax = 0;
        lazy = MAX;
    }

    int query(int h) {
        if (pmax <= h) return N;
        if (lo + 1 == hi) return lo;

        prop();

        if (lft->pmax > h) return lft->query(h);
        else return rht->query(h - lft->sum);
    }

    void prop() {
        if (lft == nullptr) {
            lft = new Node(lo, (lo + hi) >> 1);
        }
        if (rht == nullptr) {
            rht = new Node((lo + hi) >> 1, hi);
        }

        if (lazy != MAX) {
            lft->sum = lazy * (lft->hi - lft->lo);
            lft->pmax = max(lft->sum, 0);
            lft->lazy = lazy;

            rht->sum = lazy * (rht->hi - rht->lo);
            rht->pmax = max(rht->sum, 0);
            rht->lazy = lazy;
        }

        lazy = MAX;
    }

    void set(int qlo, int qhi, int val) {
        if (qhi <= lo || hi <= qlo) return;
        if (qlo <= lo && hi <= qhi) {
            sum = val * (hi - lo);
            pmax = max(sum, 0);
            lazy = val;
            return;
        }
        prop();
        lft->set(qlo, qhi, val);
        rht->set(qlo, qhi, val);

        sum = lft->sum + rht->sum;
        pmax = max(lft->pmax, lft->sum + rht->pmax);
    }
};

Node* st = new Node(0, MAX);

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;

    while (true) {
        char c;
        cin >> c;

        if (c == 'I') {
            int a, b, D;
            cin >> a >> b >> D;
            st->set(a - 1, b, D);
        } else if (c == 'Q') {
            int h;
            cin >> h;
            cout << st->query(h) << '\n';
        } else if (c == 'E') {
            break;
        } else assert(0);
    }
}
/*
4
Q 1
I 1 4 2
Q 3
Q 1
I 2 2 -1
Q 3
E
*/

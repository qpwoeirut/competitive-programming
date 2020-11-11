#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 70001;

struct BigInt {
    vector<int> digits;
    bool done;

    BigInt() {
        digits = vector<int>();
        done = false;
    }
    BigInt(const string s) {
        digits = vector<int>(s.size());
        for (int i=0; i<s.size(); ++i) {
            digits[i] = (s[i] - '0');
        }
        reverse(digits.begin(), digits.end());
        done = false;
    }
    BigInt(ll x) {
        digits = vector<int>();
        while (x) {
            digits.push_back(x % 10);
            x /= 10;
        }
        reverse(digits.begin(), digits.end());
        done = false;
    }

    inline const BigInt operator+(const BigInt& other) const {
        const int n = max(digits.size(), other.digits.size());
        BigInt ret;
        ret.digits = vector<int>(n);
        bool carry = false;
        for (int i=0; i<digits.size() || i<other.digits.size(); ++i) {
            int x = i < digits.size() ? digits[i] : 0;    
            int y = i < other.digits.size() ? other.digits[i] : 0;    

            ret.digits[i] = (x + y + carry) % 10;
            carry = (x + y + carry) >= 10;
        }
        if (carry) {
            ret.digits.push_back(1);
        }
        return ret;
    }

    inline const BigInt operator-(const BigInt& other) const {
        const int n = max(digits.size(), other.digits.size());
        BigInt ret;
        ret.digits = vector<int>(n);
        for (int i=n; i>=0; --i) { 
            int x = i < digits.size() ? digits[i] : 0;    
            int y = i < other.digits.size() ? other.digits[i] : 0;    

            ret.digits[i] = x - y;
        }
        for (int i=0; i<ret.digits.size(); ++i) {
            if (ret.digits[i] < 0) {
                ret.digits[i] += 10;
                --ret.digits[i+1];
            }
        }
        while (ret.digits.back() == 0) ret.digits.pop_back();
        if (ret.digits.empty()) ret.digits.push_back(0);
        return ret;
    }
    inline const bool operator<(const BigInt& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() < other.digits.size();
        }

        if (digits.empty()) return false;
        for (int i=digits.size() - 1; i>=0; --i) {
            if (digits[i] != other.digits[i]) {
                return digits[i] < other.digits[i];
            }
        }
        return false;
    }
    inline const bool operator==(const BigInt& other) const {
        return !(*this < other) && !(other < *this);
    }
    void print() {
        for (int i=digits.size() - 1; i>=0; --i) {
            cout << digits[i];
        }
        cout << endl;
    }
};

int N;
BigInt A[MN];
int pos[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        string s;
        cin >> s;
        A[i] = BigInt(s);
    }

    for (int i=N-1; i>0; --i) {
        A[i] = A[i] - A[i-1];
    }

    list<int> order;
    BigInt cur(1);
    for (int i=0; i<N; ++i) {
        cur = BigInt(1);
        for (auto it=order.begin(); it!=order.end(); ++it) {
            if (cur == A[i]) {
                order.insert(it, i);
                cur.done = true;
                break;
            }
            cur = cur + A[*it];
        }
        if (!cur.done && cur == A[i]) {
            order.push_back(i);
            cur.done = true;
        }

        assert(cur.done);
        //cerr << "order:";for (auto it=order.begin(); it!=order.end(); ++it) {cerr << ' ' << *it;} cerr << endl;
    }

    int idx = 0;
    for (auto it=order.begin(); it!=order.end(); ++it) {
        pos[*it] = ++idx;
    }
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << pos[i];
    }
    cout << endl;
}

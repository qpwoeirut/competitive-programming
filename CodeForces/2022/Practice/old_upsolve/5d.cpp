#include <bits/stdc++.h>

using namespace std;

using dbl=long double;

dbl solve_after_limit(const dbl a, const dbl dist, const dbl v_max, const dbl v_i) {
    const dbl d_maxv = (v_max*v_max - v_i*v_i) / (2 * a);  // from v^2 = v_i^2 + 2ax
    if (d_maxv <= dist) {
        return (v_max - v_i) / a + (dist - d_maxv) / v_max;  // time to reach max speed + time at max speed
    } else {
        const dbl v_realmax = sqrt(v_i*v_i + 2*a*dist);
        return (v_realmax - v_i) / a;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << setprecision(8) << fixed;

    dbl a, v;
    dbl l, d, w;
    cin >> a >> v;
    cin >> l >> d >> w;

    const dbl t1 = w / a;  // time to accelerate to limited speed from rest
    const dbl d1 = a * t1*t1 / 2;  // distance traveled in t1 hours from rest

    if (d1 >= d || v <= w) {  // speed limit is irrelevant
        cout << solve_after_limit(a, l, v, 0) << '\n';
    } else {
        const dbl d_mid = d - d1;
        const dbl v_mid = min(v, sqrt(w*w + a*d_mid));  // from v^2 = v_0^2 + 2ax
        const dbl d_accel = (v_mid*v_mid - w*w) / (2*a);
        const dbl t_midcruise = (d_mid - 2*d_accel) / v_mid;
        const dbl t_fastslow = 2 * (v_mid - w) / a;

        const dbl t = t1 + t_fastslow + t_midcruise + solve_after_limit(a, l - d, v, w);
        cout << t << '\n';
    }
}

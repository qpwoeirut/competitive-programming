int lo = 0, hi = N;
while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (A[mid] < target) {
        lo = mid + 1;
    } else {
        hi = mid;
    }
}
int ans = lo;




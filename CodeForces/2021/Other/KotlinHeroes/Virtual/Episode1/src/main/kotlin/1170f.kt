import kotlin.math.min

fun main() {
    val (N, M, K) = readLine()!!.split(' ').map { it.toInt() }
    val A = readLine()!!.split(' ').map { it.toLong() }.sorted()
    val psum = Array(N + 1) { 0L }
    for (i in 1..N) {
        psum[i] = psum[i - 1] + A[i - 1]
    }

    if (M == 1) {
        println(0)
        return
    }

    var ans = Long.MAX_VALUE
    for (i in 0..N - M) {
        val median = i + (M / 2)

        var (lo, hi) = listOf(i, median)
        while (lo < hi) {
            val mid = (lo + hi + 1) / 2
            if (A[mid] * (mid - i) - (psum[mid] - psum[i]) <= K) {
                lo = mid
            } else {
                hi = mid - 1
            }
        }

        val incCost = A[lo] * (lo - i) - (psum[lo] - psum[i])
        val idx = min(median, lo + 1)
        val belowCt = idx - i

        val value = min(A[median], A[lo] + ((K - incCost) / (lo - i + 1)))

        val below = value * belowCt - (psum[idx] - psum[i])
        val aboveCt = i + M - idx
        val above = psum[i + M] - psum[idx] - value * aboveCt

        ans = min(ans, above + below)

//        println("i=$i med=$median idx=$idx val=$value below=$below above=$above cost=${above + below}")
    }

    println(ans)
}

/*
3 3 3
1 5 5

2 1 1000000
1 2

3 3 1000
1 99 99
 */
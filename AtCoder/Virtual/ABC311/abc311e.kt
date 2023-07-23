import kotlin.*

private fun readInt() = readLine()!!.toInt() // single int
private fun readLong() = readLine()!!.toLong() // single long
private fun readDouble() = readLine()!!.toDouble() // single double

private fun readStrings() = readLine()!!.split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of long
private fun readDoubles() = readStrings().map { it.toDouble() } // list of double

private val MN = 1e6.toInt() + 6
private val MOD = 1e9.toInt() + 7

private fun solve() {
    val (R, C, N) = readInts()
    val holes = Array<Pair<Int, Int>>(N) {
        val x = readInts()
        Pair(x[0], x[1])
    }

    val holeSum = Array(R + 1) { IntArray(C + 1) }
    holes.forEach {
        holeSum[it.first][it.second] = 1
    }

    for (r in 1 .. R) {
        for (c in 1 .. C) {
            holeSum[r][c] += holeSum[r - 1][c] + holeSum[r][c - 1] - holeSum[r - 1][c - 1]
        }
    }

    fun hasHoles(r: Int, c: Int, n: Int): Boolean {
        val r2 = r + n - 1
        val c2 = c + n - 1
        if (r2 > R || c2 > C) return true
        return holeSum[r2][c2] - holeSum[r2][c - 1] - holeSum[r - 1][c2] + holeSum[r - 1][c - 1] > 0
    }

    var ans = 0L
    for (r in 1 .. R) {
        for (c in 1 .. C) {
            var lo = 0
            var hi = R + C
            while (lo < hi) {
                val mid = (lo + hi + 1) / 2
                if (hasHoles(r, c, mid)) {
                    hi = mid - 1
                } else {
                    lo = mid
                }
            }
            ans += lo
        }
    }

    println(ans)
}

fun main() {
    val T = 1
//    val T = readInt()
    repeat(T) {
        solve()
    }
}

import kotlin.*

private fun readInt() = readLine()!!.toInt() // single int
private fun readLong() = readLine()!!.toLong() // single long
private fun readDouble() = readLine()!!.toDouble() // single double

private fun readStrings() = readLine()!!.split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of long
private fun readDoubles() = readStrings().map { it.toDouble() } // list of double

private val MN = 1e6.toInt() + 6
private val MOD = 998244353

private fun solve() {
    val (C, R) = readInts()
    val originalGrid = Array(C) { readLine()!! }
    val grid = Array(R) { idx -> originalGrid.map { it[idx] }.joinToString("") }.reversed()

    val leftmostBlack = Array(R) { idx -> grid[idx].indexOf('#').takeIf { it != -1 } ?: C }

    val dp = Array(R) { IntArray(C + 1) }
    val sumDp = Array(R) { IntArray(C + 1) }

    for (r in 0 until R) {
        for (c in 0 .. C) {
            dp[r][c] =
                if (leftmostBlack[r] < c) 0
                else if (r == 0) 1
                else sumDp[r - 1][minOf(c + 1, C)]
            sumDp[r][c] =
                if (c == 0) dp[r][c]
                else sumDp[r][c - 1] + dp[r][c]

            dp[r][c] %= MOD
            sumDp[r][c] %= MOD
        }
    }
    println(sumDp[R - 1][C])

//    println(leftmostBlack.joinToString())
//    println(dp.joinToString("\n") { it.joinToString() })
}

fun main() {
    val T = 1
//    val T = readInt()
    repeat(T) {
        solve()
    }
}

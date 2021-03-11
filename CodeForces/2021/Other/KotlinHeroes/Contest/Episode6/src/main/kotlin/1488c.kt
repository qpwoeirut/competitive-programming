import kotlin.math.*

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
    val (N, X, Y) = readInts()
    val (x, y) = listOf<Int>(min(X, Y) - 1, max(X, Y) - 1)

    var ans = MOD
    for (i in 0 until N) {
        val d1 = min(x + i, abs(i - x) + i)
        val d2 = min((N - y - 1) + (N - i - 2), abs(i+1 - y) + (N - i - 2))
        ans = min(ans, max(d1, d2))
//        println("d1=$d1, d2=$d2")
    }

    println(ans)
}

fun main() {
//    val T = 1
    val T = readInt()
    repeat(T) {
        solve()
    }
}
/*
4 1 4
 */
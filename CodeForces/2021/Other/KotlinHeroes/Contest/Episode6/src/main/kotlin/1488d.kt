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
    val (N, S) = readLongs()
    fun check(x: Long): Boolean {
        var i = 0
        var cur = x
        var sum = 0L
        while (i < N && cur > 1) {
            sum += cur
            cur = (cur + 1L) / 2
            i += 1
        }
        sum += N - i

        return sum <= S
    }


    var lo = 0L
    var hi = 2e18.toLong()

    while (lo < hi) {
        val mid: Long = (lo + hi + 1) / 2
        if (check(mid)) {
            lo = mid
        } else {
            hi = mid - 1
        }
    }

    println(lo)
}

fun main() {
//    val T = 1
    val T = readInt()
    repeat(T) {
        solve()
    }
}
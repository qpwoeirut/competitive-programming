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
    val (N, D) = readInts()
    val schedules = Array(N) { readLine()!! }

    val combined = (0 until D).map { idx ->
        schedules.all { it[idx] == 'o' }
    }

    var best = 0
    var cur = 0
    for ((i, x) in combined.withIndex()) {
        if (!x) cur = i + 1
        best = maxOf(best, i - cur + 1)
    }
    println(best)
}

fun main() {
    val T = 1
//    val T = readInt()
    repeat(T) {
        solve()
    }
}

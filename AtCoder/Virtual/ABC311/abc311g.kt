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
    val (N, M) = readInts()
    val grid = Array(N) { readInts().toIntArray() }

    val numbers = grid.mapIndexed { r, row -> row.mapIndexed { c, x -> Triple(x, r, c) } }.flatten().toTypedArray()
    numbers.sort()

    val sum = Array(N) { grid[it].copyOf() }
    for (r in 1 until N) {
        for (c in 1 until M) {
            sum[r][c] += sum[r - 1][c] + sum[r][c - 1] - sum[r - 1][c - 1]
        }
    }


}

fun main() {
    val T = 1
//    val T = readInt()
    repeat(T) {
        solve()
    }
}

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
    val grid = Array(N) { r -> readInts().mapIndexed { c, x -> Triple(x, r, c) } }

    fun checkRectangle(r1: Int, c1: Int, r2: Int, c2: Int): Int {
        if (r1 == r2 || c1 == c2) return 0

        val rect = grid
            .slice(r1 until r2)
            .map { it.slice(c1 until c2) }
        val sum = rect.sumBy { row -> row.sumBy { it.first } }
        val min = rect.flatten().minBy { it.first }!!

        val result = sum * min.first

        val left = checkRectangle(r1, c1, r2, min.third)
        val top = checkRectangle(r1, c1, min.second, c2)
        val right = checkRectangle(r1, min.third + 1, r2, c2)
        val bottom = checkRectangle(min.second + 1, c1, r2, c2)

        return arrayOf(result, left, top, right, bottom).max()!!
    }

    println(checkRectangle(0, 0, N, M))
}

fun main() {
    val T = 1
//    val T = readInt()
    repeat(T) {
        solve()
    }
}

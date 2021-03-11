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

private val p10 = listOf<Long>(1, 10, 100, 1000, 10000, 1e5.toLong(), 1e6.toLong(), 1e7.toLong(), 1e8.toLong(), 1e9.toLong())

private fun solve() {
    var (X, Y) = readLongs()

    var ans = 0
    var stop = false

    while (Y > 0 && !stop) {
        for (k in p10.size - 1 downTo 0) {
            if (Y >= X * p10[k]) {
                Y -= X * p10[k]
                ans += 1
                break
            } else if (k == 0) {
                stop = true
            }
        }
    }

    println(ans + Y)
}

fun main() {
//    val T = 1
    val T = readInt()
    repeat(T) {
        solve()
    }
}
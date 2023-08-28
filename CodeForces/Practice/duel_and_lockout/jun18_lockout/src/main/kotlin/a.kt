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

fun main() {
    val (n, m, z) = readInts()
    var ans = 0
    for (i in 1..z) {
        if (i % n == 0 && i % m == 0) ans += 1
    }
    println(ans)
}
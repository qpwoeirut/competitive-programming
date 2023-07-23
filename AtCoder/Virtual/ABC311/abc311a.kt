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
    val N = readInt()
    val S = readLine()!!.trim()

    var a = false
    var b = false
    var c = false

    for ((i, ch) in S.withIndex()) {
        when (ch) {
            'A' -> a = true
            'B' -> b = true
            'C' -> c = true
            else -> assert(false)
        }

        if (a && b && c) {
            println(i + 1)
            return
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

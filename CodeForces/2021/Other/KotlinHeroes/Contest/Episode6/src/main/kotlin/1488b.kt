import kotlin.*
import kotlin.math.min

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
    val (N, K) = readInts()

    val S = readLine()!!
    val A = Array<Int>(S.length + 1) { 0 }
    val zeros = mutableListOf<Int>()
    for (i in 1 .. S.length) {
        A[i] = A[i-1] + if (S[i-1] == '(') 1 else -1

        if (A[i] == 0) {
            zeros.add(i)
        }
    }

    var x = 0
    var i = 0
    for (zero in zeros) {
        x += (zero - i - 2) / 2
        i = zero
    }

    println(zeros.size + min(K, x))
}

fun main() {
//    val T = 1
    val T = readInt()
    repeat(T) {
        solve()
    }
}
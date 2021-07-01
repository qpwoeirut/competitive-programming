import kotlin.*
import kotlin.math.abs
import kotlin.math.max

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
    val A = readInts().sorted()
    val B = readInts().sorted()
    val M = readInt()
    val C = readInts()

    val pref = MutableList(N) { B[it] - A[it] }
    for (i in 1 until N) {
        pref[i] = max(pref[i], pref[i-1])
    }
    pref.add(pref.last())

    val suff = MutableList(N) { B[it + 1] - A[it] }
    for (i in N - 2 downTo 0) {
        suff[i] = max(suff[i], suff[i+1])
    }
    suff.add(Int.MIN_VALUE)

//    println(A)
//    println(B)
//    println(pref)
//    println(suff)

    val ans = mutableListOf<Int>()
    for (q in C) {
        var idx = A.binarySearch(q)
        if (idx < 0) idx = -(idx + 1)

//        println("A=$A, idx=$idx, q=$q")
        ans.add(maxOf(pref[idx], suff[idx], B[idx] - q))
    }
    println(ans.joinToString(" "))
}

fun main() {
    val T = 1
//    val T = readInt()
    repeat(T) {
        solve()
    }
}
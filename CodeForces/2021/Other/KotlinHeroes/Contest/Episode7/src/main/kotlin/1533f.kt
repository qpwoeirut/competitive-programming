import kotlin.*
import kotlin.math.ceil
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
    val S = readLine()!!
    val zero = S.withIndex().filter { it.value == '0' }.map { it.index }
    val one = S.withIndex().filter { it.value == '1' }.map { it.index }

    fun getNext(idx: Int, k: Int): Int {
        val zidx = (if (S[idx] == '0') zero.binarySearch(idx) else -(zero.binarySearch(idx) + 1)) + k
        val oidx = (if (S[idx] == '1') one.binarySearch(idx) else -(one.binarySearch(idx) + 1)) + k

        if (zidx >= zero.size || oidx >= one.size) {
            return S.length
        }

        return max(zero[zidx], one[oidx])
    }

    val ansArr = mutableListOf<Int>()
    for (k in 1..S.length) {
        var ans = 0
        var i = 0
        while (i < S.length) {
            ++ans
            i = getNext(i, k)
        }
        ansArr.add(ans)
    }
    println(ansArr.joinToString(" "))
}

fun main() {
//    val N = 2e5.toInt()
//    println(List(N) { ceil(N / (it * 2.0 + 3)) }.sum())
    val T = 1
//    val T = readInt()
    repeat(T) {
        solve()
    }
}
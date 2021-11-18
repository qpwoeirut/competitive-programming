import kotlin.*
import kotlin.math.*
 
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
    val A = Array<Pair<IntArray, Int>> (N) { Pair(readInts().toIntArray(), it + 1) }

    fun IntArray.isSuperior(other: IntArray): Boolean {
        var sum = 0
        for (i in 0 until 5) {
            if (this.get(i) <= other.get(i)) sum += 1
        }
        return sum >= 3
    }
    var best = A[0]
    for (arr in A) {
        if (arr.first.isSuperior(best.first)) {
            best = arr
        }
    }
    
    if (A.all { best.first.isSuperior(it.first) }) {
        println(best.second)
    } else {
        println(-1)
    }
}
 
fun main() {
    val T = readInt()
    repeat(T) {
        solve()
    }
}


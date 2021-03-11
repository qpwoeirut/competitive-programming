import kotlin.math.*
import kotlin.random.*

private fun readInt() = readLine()!!.toInt() // single int
private fun readLong() = readLine()!!.toLong() // single long
private fun readDouble() = readLine()!!.toDouble() // single double

private fun readStrings() = readLine()!!.split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of long
private fun readDoubles() = readStrings().map { it.toDouble() } // list of double

private val MN = 1e6.toInt() + 6
private val MOD = 1e9.toInt() + 7

private data class Nodeadsf(val lo: Int, val hi: Int, var mx: Int)

private fun solve(N: Int, A: List<Int>): Int {

    val PN = (N - 1).takeHighestOneBit() * 2
    val tree = Array(N * 4) {
        if (it >= PN) {
            Node(it - PN, it - PN + 1, 0)
        } else {
            Node(0, 0, 0)
        }
    }
    for (i in PN - 1 downTo 1) {
        tree[i] = Node(tree[2 * i].lo, tree[2 * i + 1].hi, 0)
    }
    fun update(node: Int, lo: Int, hi: Int, v: Int) {
        if (lo >= tree[node].hi || tree[node].lo >= hi) return
        if (lo <= tree[node].lo && tree[node].hi <= hi) {
            tree[node].mx = max(tree[node].mx, v)
            return
        }

        update(2 * node, lo, hi, v)
        update(2 * node + 1, lo, hi, v)

        tree[node].mx = max(tree[2 * node].mx, tree[2 * node + 1].mx)
    }
    fun query(node: Int, lo: Int, hi: Int): Int {
        if (lo >= tree[node].hi || tree[node].lo >= hi) return 0
        if (lo <= tree[node].lo && tree[node].hi <= hi) {
            return tree[node].mx
        }

        return max(query(2 * node, lo, hi), query(2 * node + 1, lo, hi))
    }

    val pos = Array(N + 1) { mutableListOf<Int>() }
    for ((i, x) in A.withIndex()) {
        pos[x].add(i)
    }

    val dp = Array(N + 1) { 0 }
    var ans = 0
    for ((i, x) in A.withIndex()) {
//        println("i=$i x=$x pos=${pos[x]} q=${query(N - pos[x].last())}")
        ans = max(ans, query(1, i + 1, N) + 1)
        if (pos[x].last() == i) {
            dp[i] = 0
        } else {
            dp[i] = query(1, pos[x].last() + 1, N) + 2
            update(1, pos[x].last(), pos[x].last() + 1, dp[i])
        }
        ans = max(ans, dp[i])
    }

    return ans
}

fun brute(N: Int, A: List<Int>): Int {
    fun isPalin(seq: List<Int>): Boolean {
        for (i in 0 until seq.size / 2) {
            if (seq[i] != seq[seq.size - i - 1]) return false
        }
        return true
    }

    var ans = 0
    for (i in 0 until (1.shl(N))) {
        val s = mutableListOf<Int>()
        for (j in 0 until N) {
            if ((i.shr(j) and 1) == 1) {
                s.add(A[j])
            }
        }
        if (isPalin(s)) {
            ans = max(ans, s.size)
        }
    }
    return ans
}

//fun test() {
//    for (N in 1..20) {
//        println(N)
//        repeat(10000) {
//            val ct = Array(N + 1) { 0 }
//            val A = List(N) {
//                while (true) {
//                    val x = Random.nextInt(1, (N * 2 / 3) + 2)
//                    if (ct[x] < 2) {
//                        ct[x] += 1
//                        return@List x.toInt()
//                    }
//                }
//                1
//            }
//
//            val a1 = brute(N, A)
//            val a2 = solve(N, A)
//            if (a1 != a2) {
//                println("$a1 $a2 ${a1 == a2}")
//                println("$N\n$A")
//            }
//            assertEquals(a1, a2)
//        }
//
//    }
//}

fun main() {
//    test(); return
//    val T = 1
    val T = readInt()
    repeat(T) {
        val N = readInt()
        val A = readInts()
        println(solve(N, A))
    }
}
/*
1 2 3 2 3
3 2 1 2 3 1
 */
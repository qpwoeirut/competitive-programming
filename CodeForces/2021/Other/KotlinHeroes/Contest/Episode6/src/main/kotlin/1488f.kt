//import kotlin.*
//import kotlin.math.max
//
//private fun readInt() = readLine()!!.toInt() // single int
//private fun readLong() = readLine()!!.toLong() // single long
//private fun readDouble() = readLine()!!.toDouble() // single double
//
//private fun readStrings() = readLine()!!.split(" ") // list of strings
//private fun readInts() = readStrings().map { it.toInt() } // list of ints
//private fun readLongs() = readStrings().map { it.toLong() } // list of long
//private fun readDoubles() = readStrings().map { it.toDouble() } // list of double
//
//private val MN = 1e6.toInt() + 6
//private val MOD = 1e9.toInt() + 7
//
//private data class Node(val lo: Int, val hi: Int, var mx: Int, var sum: Int, var lazy: Int)
//
//private fun solve() {
//    val N = readInt()
//    val A = readInts()
//
//    val PN = (N - 1).takeHighestOneBit() * 2
//    val tree = Array(N * 4) {
//        if (it >= PN) {
//            Node(it - PN, it - PN + 1, if (it - PN < N) A[it - PN] else 0, if (it - PN < N) A[it - PN] else 0, 0)
//        } else {
//            Node(0, 0, 0, 0, 0)
//        }
//    }
//    for (i in PN - 1 downTo 1) {
//        tree[i] = Node(tree[2 * i].lo, tree[2 * i + 1].hi, max(tree[2 * i].mx, tree[2 * i + 1].mx), tree[2 * i].sum + tree[2 * i + 1].sum,0)
//    }
//    fun prop(node: Int) {
//        tree[2 * node].mx = max(tree[2 * node].mx, tree[node].lazy)
//        tree[2 * node].lazy = max(tree[2 * node].lazy, tree[node].lazy)
//        tree[2 * node + 1].mx = max(tree[2 * node + 1].mx, tree[node].lazy)
//        tree[2 * node + 1].lazy = max(tree[2 * node + 1].lazy, tree[node].lazy)
//        tree[node].lazy = 0
//    }
//
//    fun update(node: Int, lo: Int, hi: Int, v: Int) {
//        if (lo >= tree[node].hi || tree[node].lo >= hi) return
//        if (lo <= tree[node].lo && tree[node].hi <= hi) {
//            tree[node].mx = max(tree[node].mx, v)
//            tree[node].lazy = max(tree[node].lazy, v)
//            return
//        }
//
//        prop(node)
//
//        update(2 * node, lo, hi, v)
//        update(2 * node + 1, lo, hi, v)
//
//        tree[node].mx = max(tree[2 * node].mx, tree[2 * node + 1].mx)
//    }
//
//    fun query(node: Int, lo: Int, hi: Int): Int {
//        if (lo >= tree[node].hi || tree[node].lo >= hi) return 0
//        if (lo <= tree[node].lo && tree[node].hi <= hi) {
//            return tree[node].sum
//        }
//
//        return query(2 * node, lo, hi) + query(2 * node + 1, lo, hi)
//    }
//
//    val pos = Array(N + 1) { mutableListOf<Int>() }
//    for ((i, x) in A.withIndex()) {
//        pos[x].add(i)
//    }
//
//
//}
//
//fun main() {
//    val T = 1
////    val T = readInt()
//    repeat(T) {
//        solve()
//    }
//}
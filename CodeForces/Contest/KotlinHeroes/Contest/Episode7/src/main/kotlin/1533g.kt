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
    val A = List<List<Int>>(N) { readInts() }

    val ans = mutableListOf<Int>()
    val vis = List(N) { MutableList(M) { false } }

    val K = A.sumOf { it.count { v -> v > 0 } }

    fun dfs(r: Int, c: Int) {
        if (r < 0 || r >= N || c < 0 || c >= M || vis[r][c] || A[r][c] == 0) return
//        println("$ans, $r, $c")
        vis[r][c] = true
        ans.add(A[r][c])
        dfs(r + 1, c)
        if (ans.last() != A[r][c]) {
            ans.add(A[r][c])
        }

        dfs(r, c + 1)
        if (ans.last() != A[r][c]) {
            ans.add(A[r][c])
        }

        dfs(r - 1, c)
        if (ans.last() != A[r][c]) {
            ans.add(A[r][c])
        }

        dfs(r, c - 1)
        if (ans.last() != A[r][c]) {
            ans.add(A[r][c])
        }
    }

    outer@for (r in 0 until N) {
        for (c in 0 until M) {
            if (A[r][c] > 0) {
                dfs(r, c)
                break@outer
            }
        }
    }

    outer@for (r in 0 until N) {
        for (c in 0 until M) {
            if (A[r][c] > 0 && !vis[r][c]) {
                println(-1)
                return
            }
        }
    }

    if (ans.first() == ans.last()) ans.removeLast()

    println("$K $K")
    for (r in 0 until K) {
        println(List(K) { ans[(r + it) % ans.size] }.joinToString(" "))
    }
}

fun main() {
//    val T = 1
    val T = readInt()
    repeat(T) {
        solve()
    }
}

/*
1
5 5
0 1 0 2 0
3 4 5 6 7
0 8 0 9 0
10 11 12 13 14
0 15 0 16 0
 */
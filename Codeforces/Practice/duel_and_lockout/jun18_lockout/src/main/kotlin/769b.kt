private fun readInt() = readLine()!!.toInt()
private fun readInts() = readLine()!!.split(" ").map { it.toInt() }

fun main() {
    val N = readInt()
    val A = readInts()

    val idxs = A.withIndex().sortedByDescending { it.value }.map { it.index }

    if (A.sum() < N - 1 || A[0] == 0) {
        println(-1)
        return
    }

    val available = MutableList(A[0]) { 0 }
    val moves = mutableListOf<Pair<Int,Int>>()
    for (idx in idxs) {
        if (idx == 0) continue
        moves.add(Pair(available.removeLast(), idx))
        for (x in 0 until A[idx]) {
            available.add(idx)
        }
    }

    println(moves.size)
    for ((a, b) in moves) {
        println("${a + 1} ${b + 1}")
    }
}
fun main() {
    val M = readLine()!!.toInt()
    val A = readLine()!!.split(' ').map { it.toInt() }

    val N = A.count { it == -1 }
    val ans = Array(N) { mutableListOf<Int>() }
    val active = (0 until N).toMutableSet()

    var i = 0
    while (i < M) {
        val rem = mutableSetOf<Int>()
        for (x in active) {
            if (A[i] == -1) {
                rem.add(x)
            } else {
                ans[x].add(A[i])
            }
            ++i
            if (i == M) break
        }
        for (x in rem) {
            active.remove(x)
        }
    }

    println("$N")
    for (arr in ans) {
        println("${arr.size} ${arr.joinToString(" ")}")
    }
}
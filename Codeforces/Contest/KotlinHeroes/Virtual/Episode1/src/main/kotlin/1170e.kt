fun main() {
    val (N, M) = readLine()!!.split(' ').map { it.toInt() }
    val A = readLine()!!.split(' ').map { it.toInt() }

    val doorSum = Array(N + 1) { 0 }
    for (i in 1..N) {
        doorSum[i] = doorSum[i - 1] + A[i - 1]
    }

    val Q = readLine()!!.toInt()
    for (query in 0 until Q) {
        val tmp = readLine()!!.split(' ').map { it.toInt() }
        val B = tmp.subList(1, tmp.size)

        var prev = 0
        var i = 0
        for (w in B) {
            val dist = w - prev - 1
            i = doorSum.binarySearch(doorSum[i] + dist, fromIndex = i)
            if (i < 0) {
                i = -(i + 1) - 1
            }
            prev = w
        }

        println(if (doorSum[N] - doorSum[i] <= M - B.last()) "YES" else "NO")
    }
}
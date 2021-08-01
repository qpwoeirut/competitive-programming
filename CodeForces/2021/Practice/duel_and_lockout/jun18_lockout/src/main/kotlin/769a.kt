private fun readInt() = readLine()!!.toInt()
private fun readInts() = readLine()!!.split(" ").map { it.toInt() }

fun main() {
    val N = readInt()
    val A = readInts().sorted()

    println(A[A.size / 2])
}
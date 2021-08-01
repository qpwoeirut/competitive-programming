private fun readInt() = readLine()!!.toInt()

fun gcd(a: Int, b: Int): Int {
    if (a == 0) return b
    if (b == 0) return a
    return gcd(b % a, a)
}

fun main() {
    val T = readInt()
    repeat(T) {
        var N = readInt()
        var M = 100 - N
        val g = gcd(N, M)
        N /= g
        M /= g
        println(N + M)
    }
}
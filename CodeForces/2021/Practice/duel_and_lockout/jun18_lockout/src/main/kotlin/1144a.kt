fun main() {
    val T = readLine()!!.toInt()
    repeat(T) {
        val S = readLine()!!.toList().sorted()
        var ok = true
        for (i in 0 until S.size - 1) {
            if (S[i].toInt() + 1 != S[i+1].toInt()) {
                ok = false
            }
        }

        println(if (ok) "YES" else "NO")
    }
}
fun main() {
    val N = readLine()!!.toInt()
    val A = readLine()!!.split(' ').map { it.toInt() }

    var mx1 = 0
    var mx2 = 0
    var ans = 0
    for (x in A) {
        if (mx2 > x) {
            ++ans
        }

        if (x > mx2) {
            mx2 = x
            if (mx2 > mx1) {
                val tmp = mx1
                mx1 = mx2
                mx2 = tmp
            }
        }
    }

    println(ans)
}
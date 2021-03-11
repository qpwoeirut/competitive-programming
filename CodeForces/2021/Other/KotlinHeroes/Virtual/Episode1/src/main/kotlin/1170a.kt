fun solve() {
    val (x, y) = readLine()!!.split(' ').map { it.toInt() }.sorted()
    val c = x - 1
    val b = y - c
    val a = x - c

    println("$a $b $c")
}

fun main() {
    val Q = readLine()!!.toInt()

    for (i in 1..Q) solve()
}
private fun readStrings() = readLine()!!.split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    val arr = readInts().sorted()
    val c = arr[3] - arr[2]
    val b = arr[3] - arr[1]
    val a = arr[3] - arr[0]
    println("$a $b $c")
}

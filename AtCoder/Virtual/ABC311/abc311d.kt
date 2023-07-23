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

private val chr = arrayOf(1, 0, -1, 0)
private val chc = arrayOf(0, 1, 0, -1)

@kotlin.ExperimentalStdlibApi
private fun solve() {
    val (N, M) = readInts()
    val grid = Array(N) { readLine()!! }

    val visited = Array(N) { Array(M) { Array(4) { false } } }
    val queue = ArrayDeque<Triple<Int, Int, Int>>()
    (0 .. 3).forEach {
        queue.add(Triple(1, 1, it))
        visited[1][1][it] = true
    }
    while (queue.isNotEmpty()) {
        val (r, c, dir) = queue.removeFirst()

        val dirs = if (grid[r + chr[dir]][c + chc[dir]] == '.') {
            arrayOf(dir)
        } else {
            arrayOf(0, 1, 2, 3)
        }

        for (newDir in dirs) {
            val nr = r + chr[newDir]
            val nc = c + chc[newDir]

            if (grid[nr][nc] == '.' && !visited[nr][nc][newDir]) {
                visited[nr][nc][newDir] = true
                queue.add(Triple(nr, nc, newDir))
            }
        }
    }

    println(visited.sumBy { row -> row.count { true in it } })
    // use deprecated functions so that stuff will compile on AtCoder's old Kotlin
}

@kotlin.ExperimentalStdlibApi
fun main() {
    val T = 1
//    val T = readInt()
    repeat(T) {
        solve()
    }
}

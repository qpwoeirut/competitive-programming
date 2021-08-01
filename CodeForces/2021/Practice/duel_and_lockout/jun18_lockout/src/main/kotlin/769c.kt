private val chr = arrayOf(1, 0, 0, -1)
private val chc = arrayOf(0, -1, 1, 0)
private val dir = arrayOf('D', 'L', 'R', 'U')

fun main() {
    val (N, M, K) = readLine()!!.split(' ').map { it.toInt() }
    val G = Array(N) { readLine()!! }

    if (K % 2 == 1) {
        println("IMPOSSIBLE")
        return
    }

    fun findStart(): Pair<Int,Int> {
        for (i in 0 until N) {
            for (j in 0 until M) {
                if (G[i][j] == 'X') {
                    return Pair(i, j)
                }
            }
        }
        throw Exception("sad")
    }

    val ans = mutableListOf<Char>()
    val ans2 = mutableListOf<Char>()

    var (r, c) = findStart()

    for (k in 0 until K step 2) {
        var moved = false
        for (i in 0 until 4) {
            val nr = r + chr[i]
            val nc = c + chc[i]
            if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue
            if (G[nr][nc] == '*') continue

            ans += dir[i]
            ans2 += dir[3 - i]

            r = nr
            c = nc
            moved = true
            break
        }
        if (!moved) {
            println("IMPOSSIBLE")
            return
        }
    }

    ans2.reverse()
    println((ans + ans2).joinToString(""))
}
/*
*X..
*.*.
..*.
.**.
....
*/
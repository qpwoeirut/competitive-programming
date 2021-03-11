fun main() {
    val (N, M) = readLine()!!.split(' ').map { it.toInt() }

    val adj = Array(N) { mutableMapOf<Int, Int>() }
    val ans = mutableListOf<MutableList<Int>>()
    var edgesUsed = 0
    for (i in 0 until M) {
        val (x, y) = readLine()!!.split(' ').map { it.toInt() - 1 }
        if (x == y) {
            ans.add(mutableListOf(x + 1, y + 1))
            edgesUsed += 1
        } else {
            adj[x][y] = (adj[x][y] ?: 0) + 1
            adj[y][x] = (adj[y][x] ?: 0) + 1
        }
    }

    val visited = BooleanArray(N) { false }
    val curPath = mutableListOf<Int>()
    fun findCycle(u: Int): Boolean {
//        println("u=$u path=$curPath")
        if (visited[u]) {
            visited[u] = false
            ans.add(mutableListOf(u + 1))
            while (curPath.last() != u) {
                visited[curPath.last()] = false
                ans.last().add(curPath.removeLast() + 1)
            }
            ans.last().add(curPath.removeLast() + 1)
            edgesUsed += ans.last().size - 1

//            println("added cycle=${ans.last()}")

            return true
        }

        curPath.add(u)
        visited[u] = true
        for (item in adj[u]) {
            if (item.value == 0) continue
            adj[u][item.key] = (adj[u][item.key] ?: 1) - 1
            adj[item.key][u] = (adj[item.key][u] ?: 1) - 1
            return findCycle(item.key)
        }

        return false
    }

    while (edgesUsed < M) {
        for (i in 0 until N) {
            if (adj[i].values.sum() > 0 && !findCycle(i)) {
                if (edgesUsed < M) {
                    println("NO")
                    return
                }
            }
        }
    }
    assert(edgesUsed == M)

    val sb = StringBuilder("YES\n${ans.size}\n")
    for (cycle in ans) {
        sb.append("${cycle.size} ${cycle.joinToString(" ")}\n")
    }

    print(sb)
}

/*
4 7
1 2
2 3
3 4
4 1
1 1
2 2
3 3

4 7
1 1
1 1
1 1
1 2
2 3
3 4
4 1
 */
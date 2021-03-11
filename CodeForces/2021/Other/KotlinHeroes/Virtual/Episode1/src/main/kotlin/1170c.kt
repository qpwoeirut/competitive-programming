fun main() {
    val Q = readLine()!!.toInt()

    for (testCase in 1..Q) {
        val s = readLine()!!
        val t = readLine()!!

        var ans = true
        var i = 0
        for (j in t.indices) {
            if (i == s.length) {
                ans = false
                break
            }
            if (s[i] == t[j]) {
                ++i
            } else if (i+1 < s.length && s[i] == '-' && s[i+1] == '-' && t[j] == '+') {
                i += 2
            } else {
                ans = false
                break
            }
        }

        if (i != s.length) {
            ans = false
        }
        if (ans) {
            println("YES")
        } else {
            println("NO")
        }
    }
}
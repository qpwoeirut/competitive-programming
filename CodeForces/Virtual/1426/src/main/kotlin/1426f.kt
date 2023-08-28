import kotlin.*
import kotlin.math.*

private fun readInt() = readLine()!!.toInt() // single int
private fun readLong() = readLine()!!.toLong() // single long
private fun readDouble() = readLine()!!.toDouble() // single double

private fun readStrings() = readLine()!!.split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of long
private fun readDoubles() = readStrings().map { it.toDouble() } // list of double

private val MN = 1e6.toInt() + 6
private val MOD = 1e9.toInt() + 7

private fun solve() {
    val N = readInt()
    val S = readLine()!!

    val pow3 = LongArray(N)
    pow3[0] = 1
    for (i in 1 until N) {
        pow3[i] = pow3[i - 1] * 3 % MOD
    }

    val A = LongArray(N)
    val C = LongArray(N)
    val qBefore = LongArray(N)
    val qAfter = LongArray(N)

    for (i in S.indices) {
        A[i] = if (i == 0) 0 else A[i - 1]
        qBefore[i] = if (i == 0) 0 else qBefore[i - 1]

        if (S[i] == 'a') ++A[i]
        else if (S[i] == '?') ++qBefore[i]


        C[i] = if (i == 0) 0 else C[i - 1]
        qAfter[i] = if (i == 0) 0 else qAfter[i - 1]

        if (S[N - i - 1] == 'c') ++C[i]
        else if (S[N - i - 1] == '?') ++qAfter[i]
    }
    C.reverse()
    qAfter.reverse()

//    println(A.toList())
//    println(C.toList())
//    println(qBefore.toList())
//    println(qAfter.toList())

    val questions = S.count { it == '?' }

    var ans = 0L
    for (i in S.indices) {
        if (S[i] == 'b') {
            ans += (((A[i] * C[i]) % MOD) * pow3[questions]) % MOD
            if (questions >= 1) {
                ans += (((qBefore[i] * C[i]) % MOD) * pow3[questions - 1]) % MOD
                ans += (((A[i] * qAfter[i]) % MOD) * pow3[questions - 1]) % MOD
            }
            if (questions >= 2) {
                ans += (((qBefore[i] * qAfter[i]) % MOD) * pow3[questions - 2]) % MOD
            }
        } else if (S[i] == '?' && questions >= 1) {
            ans += (((A[i] * C[i]) % MOD) * pow3[questions - 1]) % MOD
            if (questions >= 2) {
                ans += ((((qBefore[i] - 1) * C[i]) % MOD) * pow3[questions - 2]) % MOD
                ans += (((A[i] * (qAfter[i] - 1)) % MOD) * pow3[questions - 2]) % MOD
            }
            if (questions >= 3) {
                ans += ((((qBefore[i] - 1) * (qAfter[i] - 1)) % MOD) * pow3[questions - 3]) % MOD
            }
        }
        ans %= MOD
    }
    println(ans)
}

fun main() {
    val T = 1
//    val T = readInt()
    repeat(T) {
        solve()
    }
}
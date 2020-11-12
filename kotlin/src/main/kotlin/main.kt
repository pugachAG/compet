import java.io.*
import java.util.*
import java.util.ArrayList
import kotlin.math.abs

var kin = InputReader(getInput())
val kout = PrintWriter(System.out)

fun lis(mn: Int, mx: Int, a: List<Int>): Int {
    val dp = ArrayList<Int>()
    for (v in a) {
        if (v !in mn..mx) {
            continue
        }
        var l = -1
        var r = dp.lastIndex
        while (l < r) {
            val mid = (l+r+1)/2
            if (v >= dp[mid]) {
                l = mid
            } else {
                r = mid-1
            }
        }
        val j = l+1
        if (j == dp.size) {
            dp.add(v)
        } else if (dp[j] > v) {
            dp[j] = v
        }
    }
    return dp.size
}


fun solveCase() {
    val n = kin.int()
    val k = kin.int()
    val a = kin.listInt(n).withIndex().map { it.value - it.index }
    val b = kin.listInt(k).map { it-1 }.toSet()
    var mn = Int.MIN_VALUE
    var mx = Int.MAX_VALUE
    val cur = ArrayList<Int>()
    var ok = true
    var ans = 0
    for (i in 0..n) {
        if (i == n || b.contains(i)) {
            mx = if (i == n) Int.MAX_VALUE else a[i]
            if (mx < mn) {
                ok = false
            }
            val len = lis(mn, mx, cur)
            ans += cur.size - len
            cur.clear()
            mn = mx
        } else {
            cur.add(a[i])
        }
    }
    if (!ok) {
        ans = -1
    }
    kout.println(ans)
}

fun solve() {
    repeat(1) {
        solveCase()
    }
}

fun main() {
    kout.use { solve() }
}

class InputReader(stream: InputStream) {
    private val reader = BufferedReader(InputStreamReader(stream), 32768)
    private var tokenizer: StringTokenizer? = null

    fun str(): String {
        while (tokenizer?.hasMoreTokens() != true) {
            tokenizer = StringTokenizer(reader.readLine())
        }
        return tokenizer!!.nextToken()
    }

    fun <R> list(n: Int, parse: (String) -> R): List<R> {
        return (1..n).map { parse.invoke(str()) }
    }

    fun int() = str().toInt()
    fun listInt(n: Int) = list(n) { it.toInt() }
    fun long() = str().toLong()
    fun listLong(n: Int) = list(n) { it.toLong() }
}

fun getInput(): InputStream {
    val inputFile = try {
        System.getProperty("compet.input")
    } catch (ex: Exception) {
        null
    } ?: return System.`in`

    return FileInputStream({}::class.java.classLoader.getResource(inputFile).file)
}


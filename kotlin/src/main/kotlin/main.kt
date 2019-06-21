import java.io.*
import java.util.*
import kotlin.math.*

var kin = InputReader(getInput())
val kout = PrintWriter(System.out)

fun solve() {
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


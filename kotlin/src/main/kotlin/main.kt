import java.io.*
import java.util.*

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

    fun int() = str().toInt()
    fun long() = str().toLong()
}

fun getInput(): InputStream {
    val inputFile = try {
        System.getProperty("compet.input")
    } catch (ex: Exception) {
        null
    } ?: return System.`in`

    return FileInputStream({}::class.java.classLoader.getResource(inputFile).file)
}


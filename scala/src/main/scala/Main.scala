import java.io._
import java.util._
import scala.collection.mutable

object Main {
  var kin: InputReader = new InputReader(System.in)
  val kout = new PrintWriter(System.out)

  def solve(): Unit = {
    val n = kin.int()
    val a = kin.listInt(n)
    kout.println(a)
  }

  def main(args: Array[String]): Unit = {
    try {
      kin = new InputReader(new FileInputStream(classOf[InputReader].getClassLoader
        .getResource(System.getProperty("compet.input")).getFile))
    } catch {
      case _: Exception =>
    }
    try {
      solve()
    } finally {
      kout.close()
    }
  }
}

class InputReader(stream: InputStream) {
  private val reader = new BufferedReader(new InputStreamReader(stream), 32768)
  private var tokenizer: Option[StringTokenizer] = None

  def str(): String = {
    while (tokenizer.isEmpty || !tokenizer.get.hasMoreTokens) {
      tokenizer = Option(new StringTokenizer(reader.readLine()))
    }
    tokenizer.get.nextToken()
  }

  def list[R](n: Int, parse: String => R): mutable.Buffer[R] = (1 to n).map(_ => parse.apply(str())).toBuffer

  def int(): Int = str().toInt

  def listInt(n: Int): mutable.Buffer[Int] = list(n, _.toInt)

  def long(): Long = str().toLong

  def listLong(n: Int): mutable.Buffer[Long] = list(n, _.toLong)
}

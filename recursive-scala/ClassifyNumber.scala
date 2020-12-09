object ClassifyNumber extends App {
  val stdin = scala.io.StdIn
  val list = stdin.readLine.split(" ").map(_.trim.toInt).toList

  numberClassification(list).foreach(e => println("%.6f ".format(e)))

  def numberClassification(list: List[Int]): List[Float] = {
    val (amntPositives, amntNegatives) = recNumberClassification(list)
    val length = list.length

    List (
      amntPositives.asInstanceOf[Float] / list.length,
      amntNegatives.asInstanceOf[Float] / list.length,
      (length - amntNegatives - amntPositives).asInstanceOf[Float] / list.length
    )
  }

  def recNumberClassification(list: List[Int]): (Int, Int) = {
    if (list.length == 1)
      generateTupleClassification(list.head)
    else
      recNumberClassification(list.tail) ++ generateTupleClassification(list.head)
  }

  def generateTupleClassification(elem: Int) = if (elem > 0) (1, 0) else if (elem < 0) (0,1) else (0,0)
  implicit class OperationsWithTuples(tuple: (Int,Int)) {
    def ++(otherTuple: (Int,Int)) = (tuple._1 + otherTuple._1, tuple._2 + otherTuple._2)
  }
}
object CountGreatestValues extends App {
  val list = scala.io.StdIn.readLine.split(" ").map(_.trim.toInt).toList
  print(countGreatestValue(list))

  def countGreatestValue(list: List[Int]): (Int, Int) = {
    if (list.length==1)
      (list.head, 1)
    else {
      val (greaterValue, amnt) = countGreatestValue(list.tail)
      if (list.head == greaterValue)
        (greaterValue, amnt+1)
      else if (list.head > greaterValue)
        (list.head,1)
      else
        (greaterValue, amnt)
    }
  }
}
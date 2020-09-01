object GreatestSumXNumbers extends App {
  val stdin = scala.io.StdIn
  val amntParcels = stdin.readLine.toInt
  val list = stdin.readLine.split(" ").map(_.trim.toInt).toList

  print(findGreatestSum(list, amntParcels))

  def findGreatestSum(list: List[Int], amntParcels: Int): Int = {
    greatestElements(list, amntParcels).reduce((n, sum) => n+sum)
  }
  def greatestElements(list: List[Int], amntParcels: Int): List[Int] = {
    if (list.length == amntParcels)
      list
    else {
      val greatestList = greatestElements(list.tail, amntParcels)
      val (smallerIndex, smallerElement) = findSmallerElement(greatestList)
      if (list.head > smallerElement)
        greatestList.slice(0,smallerIndex) ++ greatestList.slice(smallerIndex+1, greatestList.length) :+ list.head
      else
        greatestList
    }
  }
  def findSmallerElement(list: List[Int]): (Int, Int) = {
    if (list.length==1)
      (0, list.head)
    else {
      val (smallerIndex, smaller) = findSmallerElement(list.init)
      if (list.last < smaller)
        (list.length-1, list.last)
      else
        (smallerIndex, smaller)
    }
  }
}
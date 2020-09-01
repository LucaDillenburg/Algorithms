object Fractal extends App {

  val amntLines = 32
  val spaceChar = " "

  val stdin = scala.io.StdIn
  val iterationNum = stdin.readLine.trim.toInt - 1

  val amntTrianglesVertical = math.pow(2, iterationNum)
  val triangleHeight = math.max((amntLines / amntTrianglesVertical).toInt, 1)

  val baseTriangle = (0 to triangleHeight-1).map(lineIndex => {
    val amntOnes = 1 + 2*lineIndex
    val amntUnderscoresEachSide = (2*triangleHeight - amntOnes) / 2
    spaceChar*amntUnderscoresEachSide + "1"*amntOnes + spaceChar*amntUnderscoresEachSide
  }).toList

  generateFractal(iterationNum).foreach(println(_))

  def generateFractal(iterationNumber: Int): List[String] = {
    if (iterationNumber == 0)
      baseTriangle
    else {
      val fractal = generateFractal(iterationNumber-1)
      groupStructures(fractal)
    }
  }

  def groupStructures(baseTriangle: List[String]): List[String] = {
    val amntSpacesAroundFirst = (baseTriangle(0).length/2).toInt + 1
    val firstWithSpaces = baseTriangle.map(line => spaceChar*amntSpacesAroundFirst + line + spaceChar*amntSpacesAroundFirst)
    val lastTwoStructures = baseTriangle.map(line => line + spaceChar + line)
    firstWithSpaces ++ lastTwoStructures
  }

}

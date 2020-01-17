import scala.io.Source
import org.apache.spark.{HashPartitioner, SparkConf, SparkContext}

object PageRank {

	def main(args: Array[String]): Unit = {
		val conf = new SparkConf().setAppName("PageRank").setMaster("local")
		val sc = new SparkContext(conf)

		val filePath : String = "input/web-Stanford.txt"
		val webLink = sc.textFile(filePath).map { 
			case(line) => {
				val arr = line.split("\t")
				(arr(0).toString, List(arr(1)))
			}
		}
		val webLink2 = sc.textFile(filePath).map { 
			case(line) => {
				val l: List[String] = List()
				val arr = line.split("\t")
				(arr(1).toString, l)
			}
		}
		val links = (webLink.union(webLink2))
		.reduceByKey{
			case(x,y) => {
				x:::y
			}
		}
		//Define alpha
		val alpha = 0.85
		val iterCnt = 20
		//Init pageRanks
		var ranks = links.map {
			case(start, end) => (start+"", 1.0)
		}
		//Iteration
		for(i <- 0 until iterCnt) {
			val contributions = links.join(ranks).flatMap{
				case(_, (linklist, rank)) =>
					linklist.map(dest => (dest, rank / linklist.size))
			}
			ranks = contributions.reduceByKey((x, y) => x + y)
				.map{
					case(web, v) => (web+"", (1 - alpha) + alpha * v)
			}
		}
		//Display final pageRanks
		ranks.sortByKey().foreach(println)
		ranks.coalesce(1).saveAsTextFile("output")
	}
}
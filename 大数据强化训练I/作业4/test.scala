import scala.io.Source
import org.apache.spark.{HashPartitioner, SparkConf, SparkContext}

object test {

	def main(args: Array[String]): Unit = {
		Logger.getLogger("org").setLevel(Level.OFF)
		Logger.getLogger("akka").setLevel(Level.OFF)
		val conf = new SparkConf().setAppName("PageRank").setMaster("local")
		val sc = new SparkContext(conf)

		//Define alpha
		val alpha = 0.85
		val iterCnt = 20
		//Init pageRanks
		val links = sc.parallelize(
			List(
				("A", List("A","C","D")),
				("B", List("D")),
				("C", List("B","D")),
				("D", List()))
		)
		.partitionBy(new HashPartitioner(2))
		.persist()
		links.coalesce(1).saveAsTextFile("output/links")
		var ranks = links.mapValues(_ => 1.0)
		//Iteration
		var count = 0
		for(i <- 0 until iterCnt) {
			count = count+1
			val contributions = links.join(ranks).flatMap{
				case(_, (linklist, rank)) =>
					linklist.map(dest => (dest, rank / linklist.size))
			}
			contributions.coalesce(1).saveAsTextFile("output/contribution"+count)
			ranks = contributions.reduceByKey((x, y) => x + y)
				.map{
					case(web, v) => (web+"", (1 - alpha) + alpha * v)
			}
			ranks.coalesce(1).saveAsTextFile("output/m/"+count)
		}
		//Display final pageRanks
		ranks.sortByKey().foreach(println)
		ranks.coalesce(1).saveAsTextFile("output/result")
	}
}
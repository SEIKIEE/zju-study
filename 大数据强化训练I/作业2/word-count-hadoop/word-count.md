1. 文档时unix操作系统下可打开，有很多个文档，里面是一些垃圾邮件的文字。
2. 继承mapper内部的map函数，继承reducer内部的reduce函数。map函数接收一个<key, value>键值对， 同时也会输出一个键值对。
3. reduce接收一个<key, list of values>



```Java
import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class WordCount {

  public static class TokenizerMapper 
       extends Mapper<Object, Text, Text, IntWritable>{

    private final static IntWritable one = new IntWritable(1);
    private Text word = new Text();

    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
      StringTokenizer itr = new StringTokenizer(value.toString());
      while (itr.hasMoreTokens()) {
        word.set(itr.nextToken());
        context.write(word, one);
      }
    }
  }

  public static class IntSumReducer 
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();

    public void reduce(Text key, Iterable<IntWritable> values, 
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
      for (IntWritable val : values) {
        sum += val.get();
      }
      result.set(sum);
      context.write(key, result);
    }
  }

  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();	//系统运行时加载Hadoop的默认配置
    String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
    if (otherArgs.length != 2) {
      System.err.println("Usage: wordcount <in> <out>");
      System.exit(2);
    }
    Job job = new Job(conf, "word count");	//初始化一个job任务，加载Hadoop的一些配置，命名这个job为word count
    job.setJarByClass(WordCount.class);	//使用了wordcount.class类加载器寻找包包含该类的jar包，设置该jar包为作业所用的jar包
    job.setMapperClass(TokenizerMapper.class);	//设置该job任务所使用的mapper类（拆分）
    job.setCombinerClass(IntSumReducer.class);	//设置了该Job任务所使用的Combiner类（中间结果合并）。
    //本质上是一个本地的reduce方法，节省带宽
    job.setReducerClass(IntSumReducer.class);		//设置了该Job任务所使用的Reducer类（合并）。
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    //程序输入和输出的路径。从名命令行中接受参数。
    FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
    FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
```


















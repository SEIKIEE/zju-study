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
            extends Mapper<Object, Text, Text, IntWritable> {

        private final static IntWritable one = new IntWritable(1);
        //IntWritable是 Hadoop 中实现的用于封装 Java 数据类型的类,它的原型是public IntWritable(int value)和public IntWritable()两种。
        //所以new IntWritable(1)是创建了这个类的一个对象，而数值1这是参数。在Hadoop中它相当于java中Integer整型变量，为这个变量赋值为1.

        private Text word = new Text();

        //map输入键的类型为longWritable的父类型object，map输入值的类型是text
        //map输出的键值对类型为<单词，次数>。所以map输出的key值类型为text，输出value值的类型为IntWritable
        public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            StringTokenizer itr = new StringTokenizer(value.toString());  //分隔字符串，Java默认的分隔符：空格、制表符\t、换行符\n、回车符\r
            //StringTokenizer(String str, String delim)：构造一个用来解析str的StringTokenizer对象，并提供一个指定的分隔符。
            //Scanner scan = new Scanner(textWritable.toString()).useDelimiter(" |,|\\?|\\.|'");
            while (itr.hasMoreTokens()) { //查看是否有下一个分隔符的字符串
                word.set(itr.nextToken());  //获取从当前位置到下一个分隔符的字符串
                context.write(word, one);
            }
        }
    }

    public static class IntSumReducer
            extends Reducer<Text, IntWritable, Text, IntWritable> {

        private IntWritable result = new IntWritable(); //无参构造函数，默认值为0

        public void reduce(Text key, Iterable<IntWritable> values, Context context)
                throws IOException, InterruptedException 
        {
            int sum = 0;
            for (IntWritable val : values) {
                sum += val.get();
            }
            result.set(sum);
            context.write(key, result);
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();    //系统运行时加载Hadoop的默认配置
        String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
        if (otherArgs.length != 2) {
            System.err.println("Usage: wordcount <in> <out>");
            System.exit(2);
        }
        Job job = new Job(conf, "word count");    //初始化一个job任务，加载Hadoop的一些配置，命名这个job为word count
        job.setJarByClass(WordCount.class);    //使用了wordcount.class类加载器寻找包包含该类的jar包，设置该jar包为作业所用的jar包
        job.setMapperClass(TokenizerMapper.class);    //设置该job任务所使用的mapper类（拆分）
        job.setCombinerClass(IntSumReducer.class);    //设置了该Job任务所使用的Combiner类（中间结果合并）。
        //本质上是一个本地的reduce方法，节省带宽
        job.setReducerClass(IntSumReducer.class);        //设置了该Job任务所使用的Reducer类（合并）。
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);
        //程序输入和输出的路径。从名命令行中接受参数。
        
        FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
        FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }

}
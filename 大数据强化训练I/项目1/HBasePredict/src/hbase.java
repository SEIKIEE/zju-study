import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.KeyValue;
import org.apache.hadoop.hbase.client.Get;
import org.apache.hadoop.hbase.client.HBaseAdmin;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.ResultScanner;
import org.apache.hadoop.hbase.client.Scan;

import javax.xml.crypto.dsig.keyinfo.KeyValue;
import javax.xml.transform.Result;
import java.io.*;
import java.lang.module.Configuration;
import java.util.ArrayList;

//贝叶斯分析：计算这片文章分别在垃圾邮件或者非垃圾邮件中出现的频率，选择大的相信
//在贝叶斯分类中一共需要计算的数据：
//先验概率：一篇文章中这个单词出现的次数/所有单词出现的次数 这里有一个拉普拉斯平滑的操作
// P(d|c)   把d拆掉，变成很多歌单词，然后去算上面的概率
//这个类出现的概率  P(c)
//第二个概率：这个单词在垃圾邮件中出现的频率和这个单词在非垃圾邮件中出现的频率

//预测的时候的输入：一篇没有处理过的文章
//首先进行vocabulary的构造
//然后开始计算概率。从hbase表中挖数据


//hbase中的数据：
//垃圾邮件频率和非垃圾邮件频率：只有两个百分制数据
//每个单词分别在垃圾邮件出现和非垃圾邮件中出现的概率


public class hbase {
    public static ArrayList<String> Document = new ArrayList<>();

    public static String tableName = "Probability";
    public static HTable wordFreTable;

    public static void initialize() {
        Configuration conf = HBaseConfiguration.create();
        //指定hbase所用的zookeeper集群信息
        conf.set("hbase.zookeeper.quorum", "hadoop80");
        wordFreTable = new HTable(conf, tableName);
    }

    //calculate documents' probability in each class
    //input: words in the document
    //output: 1 means spam; 0 means ham
    public static String calculate(String path) throws IOException {
        initialize();
        double spam = 0.0;
        double ham = 0.0;
        int spamCount = 0;
        int hamCount = 0;

        Get g1 = new Get("spam".getBytes());
        Result r = wordFreTable.get(g1);
        spam += Math.log(bytes2Double(r.getValue("spam".getBytes())));
        Get g2 = new Get("ham".getBytes());
        r = wordFreTable.get(g2);
        ham += Math.log(bytes2Double(result.getValue("ham".getBytes())));

        BufferedWriter writer = new BufferedWriter(new FileWriter(path));
        writer.write("doc_id,class_id");

        for (int i = 0; i < Document.size(); i++) {
            String[] doc = Document.get(i).split("\t| ");
            for (String word : doc) {
                Get get = new Get(word.getBytes());
                if (!get.isCheckExistenceOnly()) {
                    Result result = wordFreTable.get(get);
                    for (Cell cell : result.rawCells()) {
                        String colName = Bytes.toString(cell.getQualifierArray(), cell.getQualifierOffset(), cell.getQualifierLength());
                        String value = Bytes.toString(cell.getValueArray(), cell.getValueOffset(), cell.getValueLength());
                        if (colName.equals("spam")) {
                            spam += Math.log(Double.valueOf(value));
                        } else if (colName.equals("ham")) {
                            ham += Math.log(Double.valueOf(value));
                        }
                    }
                } else {
                    //word not exist
                    get = new Get("SpamSpam".getBytes());
                    Result result = wordFreTable.get(get);
                    spam += Math.log(bytes2Double(result.getValue("spam".getBytes())));
                    get = new Get("HamHam".getBytes());
                    result = wordFreTable.get(get);
                    ham += Math.log(bytes2Double(result.getValue("ham".getBytes())));
                }
            }
            if (spam > ham) {
                writer.write(i + "1");
                spamCount++;
            } else {
                writer.write(i + "0");
                hamCount++;
            }
        }
        writer.close();
        return spamCount * 1.0 / Document.size() + ", " + hamCount * 1.0 / Document.size();
    }

    //call python to clean the document
    public static void docClean(String commandpath, String[] argv) throws IOException, InterruptedException {
        String exe = "python";
        String[] cmdArr = new String[]{exe, commandpath, argv[1]，argv[2], argv[3], argv[4]};
        Process process = Runtime.getRuntime().exec(cmdArr);
        System.out.println(process.waitFor());
    }

    public static double bytes2Double(byte[] arr) {
        long value = 0;
        for (int i = 0; i < 8; i++) {
            value |= ((long) (arr[i] & 0xff)) << (8 * i);
        }
        return Double.longBitsToDouble(value);
    }

    public static void readCsv(String fileName) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(fileName));
            reader.readLine();
            String line = null;
            while ((line = reader.readLine()) != null) {
                String[] item = line.split(",");
                Document.add(item[item.length - 1]);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args) throws IOException, InterruptedException {
        String[] argv = {"todo", "todo"};
        docClean("TODO", argv); //call python
        readCsv("todo");    //read word into Document(String[])
        String result = calculate("todo");  //write result into a csv
        System.out.println(result);
    }
}

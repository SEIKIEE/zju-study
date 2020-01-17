#  SVD 图像降噪 ( image noise reduce )
## 原理
使用SVD分解图片信息矩阵，保留一部分奇异值然后重构对角矩阵，达到简单的图片降噪和压缩的目的。

## 环境依赖（environment）
- pillow or PIL 5.0.0 upper
- numpy 1.14.2 upper

## 测试运行（run）
- `python main.py`
## 效果总结（summary）
1.原始图片  

![image](test.jpg)

2.保留10%奇异值

![image](test_10%25.jpg)

2.保留50%奇异值  

![image](test_50%25.jpg)  

2.保留90%奇异值  

![image](test_90%25.jpg)


##总结
保留的奇异值越多，图片的特征保留的越明显，当奇异值减少时，图片中的像素间的差距逐渐减小。

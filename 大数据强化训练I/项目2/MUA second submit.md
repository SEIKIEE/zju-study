# MUA second submit

## 增加list数据类型

### Value.class

第一次提交如下：

```java
public String value;
```

改为：

```java
public String[] value;
```



增加：

```java
public static String getValue(Value v) {
    if (v.type != 4)
        return v.value[0];
    else {
        String result = "[ ";
        for (int i = 0; i < v.value.length; i++) {
            result = result + v.value[i] + " ";
        }
        return result + " ]";
    }
}
```

针对interpreter和operator中新出现的因为上述改动的错误，用`getValue`方法。
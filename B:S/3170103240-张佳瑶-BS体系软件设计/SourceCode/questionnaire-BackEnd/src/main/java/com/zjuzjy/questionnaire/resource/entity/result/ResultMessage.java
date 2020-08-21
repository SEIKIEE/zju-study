package com.zjuzjy.questionnaire.resource.entity.result;

import java.util.HashMap;
import java.util.Map;

public class ResultMessage {

    private Integer status;

    private String msg;

    private Map<String, Object> data = new HashMap<>();

    public ResultMessage() {

    }

    public ResultMessage(StatusCode statusCode) {
        this.status = statusCode.getStatus();
        this.msg = statusCode.getMsg();
    }

    public ResultMessage(StatusCode statusCode, Map<String, Object> data) {
        this.status = statusCode.getStatus();
        this.msg = statusCode.getMsg();
        this.data = data;
    }

    public Integer getStatus() {
        return status;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public Map<String, Object> getData() {
        return data;
    }

    public void setData(Map<String, Object> data) {
        this.data = data;
    }

    public void putData(String key, Object value) {
        this.data.put(key, value);
    }
}

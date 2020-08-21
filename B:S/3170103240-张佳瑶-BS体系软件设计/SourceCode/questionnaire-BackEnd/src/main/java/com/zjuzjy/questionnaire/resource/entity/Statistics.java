package com.zjuzjy.questionnaire.resource.entity;

@SuppressWarnings("all")
public class Statistics {
    public Object getAnswer() {
        return answer;
    }

    public void setAnswer(Object answer) {
        this.answer = answer;
    }

    public Integer getNum() {
        return num;
    }

    public void setNum(Integer num) {
        this.num = num;
    }

    Object answer;
    Integer num;

    public Double getPercent() {
        return percent;
    }

    public void setPercent(Double percent) {
        this.percent = percent;
    }

    Double percent;

}

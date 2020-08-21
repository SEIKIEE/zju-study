package com.zjuzjy.questionnaire.resource.entity;

import java.util.Date;
import java.util.List;

@SuppressWarnings("all")
public class AnswerSheet {

    private Integer answerSheetID;

    private Integer paperID;

    private Integer userID;

    private String ipAddress;

    private Date submitTime;

    private List<Answer> answerList;

    public Integer getAnswerSheetID() {
        return answerSheetID;
    }

    public void setAnswerSheetID(Integer answerSheetID) {
        this.answerSheetID = answerSheetID;
    }

    public Integer getPaperID() {
        return paperID;
    }

    public void setPaperID(Integer paperID) {
        this.paperID = paperID;
    }

    public Integer getUserID() {
        return userID;
    }

    public void setUserID(Integer userID) {
        this.userID = userID;
    }

    public String getIpAddress() {
        return ipAddress;
    }

    public void setIpAddress(String ipAddress) {
        this.ipAddress = ipAddress;
    }

    public Date getSubmitTime() {
        return submitTime;
    }

    public void setSubmitTime(Date submitTime) {
        this.submitTime = submitTime;
    }

    public List<Answer> getAnswerList() {
        return answerList;
    }

    public void setAnswerList(List<Answer> answerList) {
        this.answerList = answerList;
    }

}

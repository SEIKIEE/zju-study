package com.zjuzjy.questionnaire.resource.entity;

import com.zjuzjy.questionnaire.resource.entity.question.Question;

import javax.validation.constraints.NotNull;
import java.util.Date;
import java.util.List;

@SuppressWarnings("all")
public class Paper {

    @NotNull(message = "问卷ID不能为空")
    private Integer paperID;

    @NotNull(message = "用户ID不能为空")
    private Integer userID;

    private String papername;

    private String description;

    private Integer priority;

    private Integer status;

    private Integer maxSubmit;

    private Date startTime;

    private Date endTime;

    private List<Question> questionList;

    private Integer answerSheetNum = 0;

    public Integer getAnonymous() {
        return anonymous;
    }

    public void setAnonymous(Integer anonymous) {
        this.anonymous = anonymous;
    }

    private Integer anonymous = 0;

    public List<Question> getQuestionList() {
        return questionList;
    }

    public void setQuestionList(List<Question> questionList) {
        this.questionList = questionList;
    }

    public Integer getAnswerSheetNum() {
        return answerSheetNum;
    }

    public void setAnswerSheetNum(Integer answerSheetNum) {
        this.answerSheetNum = answerSheetNum;
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

    public String getPapername() {
        return papername;
    }

    public void setPapername(String papername) {
        this.papername = papername;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Integer getPriority() {
        return priority;
    }

    public void setPriority(Integer priority) {
        this.priority = priority;
    }

    public Integer getStatus() {
        return status;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getMaxSubmit() {
        return maxSubmit;
    }

    public void setMaxSubmit(Integer maxSubmit) {
        this.maxSubmit = maxSubmit;
    }

    public Date getStartTime() {
        return startTime;
    }

    public void setStartTime(Date startTime) {
        this.startTime = startTime;
    }

    public Date getEndTime() {
        return endTime;
    }

    public void setEndTime(Date endTime) {
        this.endTime = endTime;
    }
}

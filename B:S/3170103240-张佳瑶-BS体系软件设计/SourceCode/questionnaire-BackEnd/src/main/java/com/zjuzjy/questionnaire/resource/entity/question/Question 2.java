package com.zjuzjy.questionnaire.resource.entity.question;

import javax.validation.constraints.NotNull;
import java.util.List;

@SuppressWarnings("all")
public class Question {

    public Integer getQuestionID() {
        return questionID;
    }

    public void setQuestionID(Integer questionID) {
        this.questionID = questionID;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public Integer getRequired() {
        return required;
    }

    public void setRequired(Integer required) {
        this.required = required;
    }

    public QuestionType getType() {
        return type;
    }

    public void setType(QuestionType type) {
        this.type = type;
    }

    public List<Option> getOptions() {
        return options;
    }

    public void setOptions(List<Option> options) {
        this.options = options;
    }

    public String getMinTitle() {
        return minTitle;
    }

    public void setMinTitle(String minTitle) {
        this.minTitle = minTitle;
    }

    public String getMaxTitle() {
        return maxTitle;
    }

    public void setMaxTitle(String maxTitle) {
        this.maxTitle = maxTitle;
    }

    public Object getValue() {
        return value;
    }

    public void setValue(Object value) {
        this.value = value;
    }

    public Integer getMinVal() {
        return minVal;
    }

    public void setMinVal(Integer minVal) {
        this.minVal = minVal;
    }

    public Integer getMaxVal() {
        return maxVal;
    }

    public void setMaxVal(Integer maxVal) {
        this.maxVal = maxVal;
    }

    private Integer questionID;

    @NotNull
    private String title;

    private Integer required = 0;

    @NotNull
    private QuestionType type;

    private List<Option> options;

    private String minTitle = null;

    private String maxTitle = null;

    private Integer minVal = 0;

    private Integer maxVal = 0;

    private Object value;
}

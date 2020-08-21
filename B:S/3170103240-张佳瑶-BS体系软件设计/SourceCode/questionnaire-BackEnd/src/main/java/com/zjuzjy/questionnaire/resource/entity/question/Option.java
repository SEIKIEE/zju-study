package com.zjuzjy.questionnaire.resource.entity.question;

import java.util.List;

@SuppressWarnings("all")
public class Option {

    private Integer optionID;

    private String description;

//    private Integer isDefault = 0;

    private List<Integer> cascade;

    public Integer getOptionID() {
        return optionID;
    }

    public void setOptionID(Integer optionID) {
        this.optionID = optionID;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public List<Integer> getCascade() {
        return cascade;
    }

    public void setCascade(List<Integer> association) {
        this.cascade = association;
    }
}

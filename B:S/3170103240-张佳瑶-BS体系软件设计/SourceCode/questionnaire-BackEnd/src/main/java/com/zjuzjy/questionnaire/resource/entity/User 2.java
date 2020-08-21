package com.zjuzjy.questionnaire.resource.entity;

import javax.validation.constraints.NotNull;
import javax.validation.constraints.Pattern;
import javax.validation.constraints.Size;

@SuppressWarnings("all")
public class User {

    @NotNull(message = "用户ID不能为空")
    private Integer userID;

    @Size(min = 6, message = "用户名至少需要6个字符")
    @Size(max = 32, message = "用户名不能超过32个字符")
    private String username;

    @NotNull(message = "密码不能为空")
    @Size(min = 6, message = "密码至少需要6个字符")
    private String password;

    private String email;

    private String phoneNumber;

    public Integer getUserID() {
        return userID;
    }

    public void setUserID(Integer userID) {
        this.userID = userID;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

}

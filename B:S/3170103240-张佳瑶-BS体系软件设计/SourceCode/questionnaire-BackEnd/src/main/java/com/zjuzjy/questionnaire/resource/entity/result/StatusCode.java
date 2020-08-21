package com.zjuzjy.questionnaire.resource.entity.result;

import org.springframework.ext.common.object.Status;

public enum StatusCode implements Status {

    SERVICE_RUN_SUCCESS(200, "服务运行成功"),
    USER_LOGIN_ERROR(400,"用户名或密码错误"),
    PARAMETER_VALIDATE_ILLEGAL(400, "参数非法"),
    PARAM_REGISTED_EMAIL(400,"邮箱已注册"),
    PARAM_REGISTED_PHONENUMBER(400,"手机号已注册"),
    CODE_INVALID_TOKEN(403, "Token令牌无效，请重新登录！"),
    PARAM_IS_EMPTY(10002, "参数%s不能为空"),
    DATA_NOT_EXIST(10003, "%s不存在"),
    JSON_FORMAT_ERROR(10004, "JSON格式不正确"),
    HTTP_ACCESS_ERROR(10006, "HTTP访问异常"),
    DB_ACCESS_ERROR(80000, "数据库异常"),
    SERVICE_RUN_ERROR(500,"服务器忙，请稍后再试");


    private int status;
    private String msg;

    StatusCode(int status, String message) {
        this.status = status;
        this.msg = message;
    }

    @Override
    public boolean isSuccess() {
        return getStatus() == SERVICE_RUN_SUCCESS.getStatus();
    }

    @Override
    public int getStatus() {
        return status;
    }

    @Override
    public String getCode() {
        return name();
    }

    @Override
    public String getMsg() {
        return msg;
    }

    @Override
    public String getMsg(Object... objects) {
        if (objects == null) {
            return getMsg();
        }
        return String.format(msg, objects);
    }

    public static StatusCode getStatus(int status) {
        for (StatusCode e : StatusCode.values()) {
            if (e.getStatus() == status) {
                return e;
            }
        }
        return SERVICE_RUN_ERROR;
    }
}

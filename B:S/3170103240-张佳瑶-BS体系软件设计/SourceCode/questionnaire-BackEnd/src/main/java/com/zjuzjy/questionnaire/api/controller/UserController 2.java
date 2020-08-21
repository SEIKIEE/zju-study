package com.zjuzjy.questionnaire.api.controller;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.zjuzjy.questionnaire.domain.service.TokenService;
import com.zjuzjy.questionnaire.domain.service.UserService;
import com.zjuzjy.questionnaire.resource.entity.User;
import com.zjuzjy.questionnaire.resource.entity.result.ResultMessage;
import com.zjuzjy.questionnaire.resource.entity.result.StatusCode;
import org.springframework.dao.DuplicateKeyException;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;

@RestController
@SuppressWarnings("all")
public class UserController {
    @Resource
    UserService userService;

    @Resource
    TokenService tokenService;

    @PostMapping("/user/login")
    public ResultMessage login(@RequestBody User user, HttpServletRequest httpServletRequest) throws JsonProcessingException {
        ResultMessage resultMessage;
        String token = tokenService.getToken(httpServletRequest);
        User user1 = userService.getUser(user);
        if (user1 != null) {
            String device = httpServletRequest.getHeader("user-agent");
            if (!tokenService.hasToken(token))
                token = tokenService.createToken(user1, device);
            if (tokenService.storeToken(token, user1)) {
                resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
                resultMessage.setMsg("欢迎" + user1.getUsername() + "回来！");
                resultMessage.putData("token", token);
            } else {
                resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_ERROR);
            }
        } else {
            resultMessage = new ResultMessage(StatusCode.USER_LOGIN_ERROR);
        }
        return resultMessage;
    }

    @PostMapping("/user/regist")
    public ResultMessage regist(@RequestBody User user) {
        try {
            if (0 != userService.addUser(user)) {
                ResultMessage resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
                resultMessage.setMsg("注册成功！");
                return resultMessage;
            } else {
                return new ResultMessage(StatusCode.PARAMETER_VALIDATE_ILLEGAL);
            }
        } catch (DuplicateKeyException e) {
            if (e.getCause().getMessage().contains("email"))
                return new ResultMessage(StatusCode.PARAM_REGISTED_EMAIL);
            else return new ResultMessage(StatusCode.PARAM_REGISTED_PHONENUMBER);
        }
    }

    @GetMapping("/user/logout")
    public ResultMessage logout(HttpServletRequest httpServletRequest) {
        ResultMessage resultMessage;
        String token = tokenService.getToken(httpServletRequest);
        try {
            tokenService.deleteToken(token);
            resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
            resultMessage.setMsg("注销成功！");
        } catch (Exception e) {
            resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_ERROR);
        }
        return resultMessage;
    }
}

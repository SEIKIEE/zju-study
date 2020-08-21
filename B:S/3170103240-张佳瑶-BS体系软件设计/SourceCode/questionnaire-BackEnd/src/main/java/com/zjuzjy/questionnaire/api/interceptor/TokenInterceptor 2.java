package com.zjuzjy.questionnaire.api.interceptor;

import com.zjuzjy.questionnaire.domain.service.TokenService;
import com.zjuzjy.questionnaire.resource.entity.result.StatusCode;
import com.zjuzjy.questionnaire.util.HttpUtil;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.HandlerInterceptor;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@Component
public class TokenInterceptor implements HandlerInterceptor {
    @Resource
    TokenService tokenService;

    @Override
    public boolean preHandle(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, Object object) throws Exception {
        String token = tokenService.getToken(httpServletRequest);
        if (!tokenService.hasToken(token)) {
            HttpUtil.sendException(httpServletRequest, httpServletResponse, StatusCode.CODE_INVALID_TOKEN);
            return false;
        }
        return true;
    }
}

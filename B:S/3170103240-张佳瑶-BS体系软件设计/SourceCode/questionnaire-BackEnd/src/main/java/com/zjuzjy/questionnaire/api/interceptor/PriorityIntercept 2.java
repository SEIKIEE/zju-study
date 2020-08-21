package com.zjuzjy.questionnaire.api.interceptor;

import com.zjuzjy.questionnaire.domain.service.AnswerService;
import com.zjuzjy.questionnaire.domain.service.PaperService;
import com.zjuzjy.questionnaire.domain.service.TokenService;
import com.zjuzjy.questionnaire.resource.entity.Paper;
import com.zjuzjy.questionnaire.resource.entity.result.StatusCode;
import com.zjuzjy.questionnaire.util.HttpUtil;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.HandlerInterceptor;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

@Component
public class PriorityIntercept implements HandlerInterceptor {
    @Resource
    TokenService tokenService;

    @Resource
    PaperService paperService;

    @Override
    public boolean preHandle(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, Object handler) throws Exception {
        String regex = "/paper/(\\d+)";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(httpServletRequest.getRequestURL());

        if (matcher.find()) {
            try {
                int paperID = Integer.valueOf(matcher.group(1));
                String token = tokenService.getToken(httpServletRequest);
                int userID = tokenService.getUserByToken(token).getUserID();
                Paper paper = paperService.getPaperInfo(paperID);
                if (paper.getUserID() != userID) throw new IllegalArgumentException();
                return true;
            } catch (Exception e) {
                HttpUtil.sendException(httpServletRequest, httpServletResponse, StatusCode.PARAMETER_VALIDATE_ILLEGAL);
                return false;
            }
        } else {
            HttpUtil.sendException(httpServletRequest, httpServletResponse, StatusCode.SERVICE_RUN_SUCCESS);
            return true;
        }
    }
}

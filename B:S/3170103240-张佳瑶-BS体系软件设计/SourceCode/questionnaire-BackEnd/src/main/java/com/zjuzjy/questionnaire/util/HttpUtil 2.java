package com.zjuzjy.questionnaire.util;

import com.alibaba.fastjson.JSONObject;
import com.zjuzjy.questionnaire.resource.entity.result.ResultMessage;
import com.zjuzjy.questionnaire.resource.entity.result.StatusCode;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;

public class HttpUtil {

    public static String getUserIP(HttpServletRequest httpServletRequest) {
        String ip = httpServletRequest.getHeader("x-forwarded-for");
        if (ip == null || ip.length() == 0 || ip.equalsIgnoreCase("unknown")) {
            ip = httpServletRequest.getHeader("Proxy-Client-IP");
        }
        if (ip == null || ip.length() == 0 || ip.equalsIgnoreCase("unknown")) {
            ip = httpServletRequest.getHeader("WL-Proxy-Client-IP");
        }
        if (ip == null || ip.length() == 0 || ip.equalsIgnoreCase("unknown")) {
            ip = httpServletRequest.getRemoteAddr();
        }
        return ip != null ? ip : "UNKNOWN";
    }

    public static void sendException(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, StatusCode statusCode) throws Exception {
        httpServletResponse.reset();
        httpServletResponse.setCharacterEncoding("UTF-8");
        httpServletResponse.setContentType("application/json;charset=UTF-8");
        httpServletResponse.setHeader("Access-Control-Allow-Origin", httpServletRequest.getHeader("Origin"));
        httpServletResponse.setHeader("Access-Control-Allow-Methods", "*");
        httpServletResponse.setHeader("Access-Control-Max-Age", "3600");
        httpServletResponse.setHeader("Access-Control-Allow-Credentials", "true");
        PrintWriter writer = httpServletResponse.getWriter();
        ResultMessage resultMessage = new ResultMessage(statusCode);
        writer.print(JSONObject.toJSONString(resultMessage));
    }

}

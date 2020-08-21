package com.zjuzjy.questionnaire.domain.service;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.zjuzjy.questionnaire.resource.entity.User;
import com.zjuzjy.questionnaire.util.RedisUtil;
import org.springframework.stereotype.Service;
import org.springframework.util.DigestUtils;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import java.io.IOException;

@Service("tokenService")
@SuppressWarnings("all")
public class TokenService {
    private static final int TOKEN_LIVE_TIME = 6 * 60 * 60;
    private static final String[] devices = {"Android", "iPhone", "iPod", "iPad", "Windows Phone", "MQQBrowser"};

    @Resource
    private RedisUtil redisUtil;

    public String createToken(User user, String device) {
        StringBuilder token = new StringBuilder();
        if (checkDeviceIsMobile(device)) {
            token.append("MOBILE-");
        } else {
            token.append("PC-");
        }
        token.append(DigestUtils.md5DigestAsHex(user.getUserID().toString().getBytes()));
        return token.toString();
    }

    public String getToken(HttpServletRequest httpServletRequest) {
        return httpServletRequest.getHeader("token");
    }

    public void deleteToken(String token) {
        redisUtil.delete(token);
    }

    public boolean storeToken(String token, User user) throws JsonProcessingException {
        ObjectMapper mapper = new ObjectMapper();
        try {
            redisUtil.set(token, mapper.writeValueAsString(user), TOKEN_LIVE_TIME);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public User getUserByToken(String token) throws IOException {
        if (!redisUtil.hasKey(token)) return null;
        String value = (String) redisUtil.getValue(token);
        ObjectMapper mapper = new ObjectMapper();
        return mapper.readValue(value, User.class);
    }

    public boolean hasToken(String token) {
        return redisUtil.hasKey(token);
    }

    private static boolean checkDeviceIsMobile(String device) {
        boolean flag = false;
        if (device.contains("Windows NT") == false || (device.contains("Windows NT") && device.contains("compatible; MSIE 9.0;"))) {
            if (!device.contains("Windows NT") && !device.contains("Macintosh")) {
                for (String item : devices) {
                    if (device.contains(item)) {
                        flag = true;
                        break;
                    }
                }
            }
        }
        return flag;
    }
}

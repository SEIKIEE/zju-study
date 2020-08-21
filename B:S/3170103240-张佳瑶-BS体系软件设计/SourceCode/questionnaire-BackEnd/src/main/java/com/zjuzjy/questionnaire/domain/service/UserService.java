package com.zjuzjy.questionnaire.domain.service;

import com.zjuzjy.questionnaire.resource.entity.User;
import com.zjuzjy.questionnaire.resource.mapper.UserMapper;
import org.springframework.stereotype.Service;
import org.springframework.util.DigestUtils;

import javax.annotation.Resource;

@Service("UserService")
@SuppressWarnings("all")
public class UserService {
    @Resource
    UserMapper userMapper;

    private String encryptUserPassword(String password) {
        return DigestUtils.md5DigestAsHex(password.getBytes());
    }

    public User getUser(User user) {
        user.setPassword(encryptUserPassword(user.getPassword()));
        User user1 = userMapper.getUser(user);
        if (user1 != null) user1.setPassword(null); //屏蔽密码
        return user1;
    }

    public User getUserByID(Long userID) {
        User user = userMapper.getUserByID(userID);
        if (user != null) user.setPassword(null); //屏蔽密码
        return user;
    }

    public int updateUser(User user) {
        return userMapper.updateUser(user);
    }

    public int addUser(User user) {
        user.setPassword(encryptUserPassword(user.getPassword()));
        return userMapper.addUser(user);
    }

}

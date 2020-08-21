package com.zjuzjy.questionnaire.resource.mapper;

import com.zjuzjy.questionnaire.resource.entity.User;
import org.apache.ibatis.annotations.Mapper;

@Mapper
@SuppressWarnings("all")
public interface UserMapper {
    public User getUser(User user);

    public User getUserByID(Long userID);

    public int updateUser(User user);

    public int addUser(User user);
}

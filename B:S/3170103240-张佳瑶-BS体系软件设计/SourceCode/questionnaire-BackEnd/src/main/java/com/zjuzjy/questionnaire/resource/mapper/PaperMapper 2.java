package com.zjuzjy.questionnaire.resource.mapper;

import com.zjuzjy.questionnaire.resource.entity.Paper;
import com.zjuzjy.questionnaire.resource.entity.question.Option;
import com.zjuzjy.questionnaire.resource.entity.question.Question;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;
import java.util.Set;

@Mapper
@SuppressWarnings("all")
public interface PaperMapper {

    public int createPaper(Paper paper);

    public Paper getPaper(Integer paperID);

    public List<Paper> getUserPaper(Integer userID);

    public void deletePaper(Integer paperID);

    public void setPaperStatus(Integer paperID, Integer status);

    public Paper getPaperInfo(Integer paperID);

    public void clearPaper(Integer paperID);

    public void insertQuestions(@Param("list") List<Question> questions, Integer paperID);

    public void insertOptions(@Param("list") List<Option> options, Integer questionID);

    public void associateOptions(@Param("list") List<Integer> assLists, Integer optionID);

    public Set<Integer> getQuestionIdFromPaper(Integer paperID);

    public List<Integer> getQuestionId(Integer paperID);

}

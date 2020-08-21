package com.zjuzjy.questionnaire.resource.mapper;

import com.zjuzjy.questionnaire.resource.entity.Answer;
import com.zjuzjy.questionnaire.resource.entity.AnswerSheet;
import com.zjuzjy.questionnaire.resource.entity.AnswerStatistics;
import com.zjuzjy.questionnaire.resource.entity.Statistics;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
@SuppressWarnings("all")
public interface AnswerMapper {

    public void clearAnswerSheet(Integer paperID);

    public Integer getDailySubmitTime(Integer paperID, String ipAddress);

    public Integer getMaxSubmitTime(Integer paperID, String ipAddress);

    public void createAnswerSheet(AnswerSheet answerSheet);

    public void insertAnswer(@Param("list") List<Answer> answerList, Integer answerSheetID);

    public List<AnswerSheet> getAnswerSheetByPaperId(Integer paperID);

    public void deleteAnswerSheet(Integer paperID, Integer answerSheetID);

    public AnswerSheet getAnswerSheet(Integer answerSheetID);

    public AnswerStatistics getStatistics(Integer paperID, Integer questionID);
}

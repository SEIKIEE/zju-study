package com.zjuzjy.questionnaire.domain.service;


import com.zjuzjy.questionnaire.resource.entity.Paper;
import com.zjuzjy.questionnaire.resource.entity.question.Option;
import com.zjuzjy.questionnaire.resource.entity.question.Question;
import com.zjuzjy.questionnaire.resource.entity.question.QuestionType;
import com.zjuzjy.questionnaire.resource.mapper.AnswerMapper;
import com.zjuzjy.questionnaire.resource.mapper.PaperMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.ArrayList;
import java.util.List;

@Service("paperService")
@SuppressWarnings("all")
public class PaperService {

    @Resource
    PaperMapper paperMapper;

    @Resource
    AnswerMapper answerMapper;

    public int createPaper(Paper paper) {
        return paperMapper.createPaper(paper);
    }

    public Paper getPaper(Integer paperID) {
        return paperMapper.getPaper(paperID);
    }

    public List<Paper> getUserPaper(Integer userID) {
        return paperMapper.getUserPaper(userID);
    }

    public void deletePaper(Integer paperID) {
        paperMapper.deletePaper(paperID);
    }

    public void setPaperStatus(Integer paperID, Integer status) {
        paperMapper.setPaperStatus(paperID, status);
    }

    public Paper getPaperInfo(Integer paperID) {
        return paperMapper.getPaperInfo(paperID);
    }

    public void clearPaper(Integer paperID) {
        paperMapper.clearPaper(paperID);
        answerMapper.clearAnswerSheet(paperID);
    }

    public void updatePaperQuestion(Paper paper) {
        this.clearPaper(paper.getPaperID());
        this.insertQuestion(paper);
    }

    public void insertQuestion(Paper paper) {
        List<Question> questionList = paper.getQuestionList();
        ArrayList<Question> singleList = new ArrayList<>();
        if (questionList.size() == 0)
            return;
        paperMapper.insertQuestions(questionList, paper.getPaperID());
        for (Question item : questionList) {
            List<Option> optionList = item.getOptions();
            if (optionList == null)
                continue;
            if (item.getType() == QuestionType.SINGLE_CHOICE && item.getOptions().size() > 0) {
                paperMapper.insertOptions(optionList, item.getQuestionID());
                singleList.add(item);
            } else if (item.getType() == QuestionType.DOUBLE_CHOICE && item.getOptions().size() > 0) {
                paperMapper.insertOptions(item.getOptions(), item.getQuestionID());
            }
        }

        for (Question question : singleList) {
            for (Option option : question.getOptions()) {
                List<Integer> list = option.getCascade();
                List<Integer> casList = new ArrayList<>();
                if (list != null && list.size() > 0) {
                    for (Integer i : list) {
                        casList.add(questionList.get(i).getQuestionID());
                    }
                    paperMapper.associateOptions(casList, option.getOptionID());
                }
            }
        }
    }

    public List<Integer> getQuestionId(Integer paperID) {
        return paperMapper.getQuestionId(paperID);
    }

}

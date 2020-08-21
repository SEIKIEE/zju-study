package com.zjuzjy.questionnaire.domain.service;

import com.zjuzjy.questionnaire.resource.entity.*;
import com.zjuzjy.questionnaire.resource.mapper.AnswerMapper;
import com.zjuzjy.questionnaire.resource.mapper.PaperMapper;
import com.zjuzjy.questionnaire.util.HttpUtil;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

@Service("answerService")
@SuppressWarnings("all")
public class AnswerService {

    @Resource
    TokenService tokenService;

    @Resource
    AnswerMapper answerMapper;

    @Resource
    PaperMapper paperMapper;

    public static enum PaperStatus {

        PAPER_NOTEXIST("问卷不存在！"),
        PAPER_ERROR_STATUS("问卷已关闭！"),
        PAPER_NOT_OPEN("问卷未开放！"),
        PAPER_NOT_LOGIN("请先登录！"),
        PAPER_SUBMIT_TIME("超过填写次数！"),
        PAPER_SUCCESS("问卷填写成功！");

        private String msg;

        PaperStatus(String msg) {
            this.msg = msg;
        }

        public String getMsg() {
            return msg;
        }

        public void setMsg(String msg) {
            this.msg = msg;
        }


    }

    public PaperStatus checkPaperAccess(Paper paper, HttpServletRequest httpServletRequest) {
        String ipAddress = HttpUtil.getUserIP(httpServletRequest);
        if (paper == null) return PaperStatus.PAPER_NOTEXIST;
        if (paper.getStatus() == 0) return PaperStatus.PAPER_ERROR_STATUS;
        if ((paper.getEndTime() != null
                && paper.getStartTime().getTime() > new Date().getTime())) return PaperStatus.PAPER_NOT_OPEN;
        if (paper.getEndTime() != null
                && paper.getEndTime().getTime() < new Date().getTime())
            return PaperStatus.PAPER_ERROR_STATUS;
        if (paper.getPriority() == 1) {
            if (paper.getMaxSubmit() >= 0) {
                Integer submitTime = getDailySubmitTime(paper.getPaperID(), ipAddress);
                if (submitTime >= paper.getMaxSubmit()) {
                    return PaperStatus.PAPER_SUBMIT_TIME;
                }
            } else {
                Integer submitTime = getMaxSubmitTime(paper.getPaperID(), ipAddress);
                if (submitTime >= -1 * paper.getMaxSubmit()) {
                    return PaperStatus.PAPER_SUBMIT_TIME;
                }
            }
        } else if (paper.getPriority() == 0) {
            String token = tokenService.getToken(httpServletRequest);
            if (!tokenService.hasToken(token)) return PaperStatus.PAPER_NOT_LOGIN;
        }
        return PaperStatus.PAPER_SUCCESS;
    }

    public Integer getDailySubmitTime(Integer paperID, String ipAddress) {
        return answerMapper.getDailySubmitTime(paperID, ipAddress);
    }

    public Integer getMaxSubmitTime(Integer paperID, String ipAddress) {
        return answerMapper.getMaxSubmitTime(paperID, ipAddress);
    }

    @Transactional
    public void createAnswerSheet(AnswerSheet answerSheet) {
        answerMapper.createAnswerSheet(answerSheet);
        if (answerSheet.getAnswerList() != null && answerSheet.getAnswerList().size() > 0) {
            List<Integer> questionIdSet = paperMapper.getQuestionId(answerSheet.getPaperID());
            for (Answer answer : answerSheet.getAnswerList()) {
                if (questionIdSet.contains(answer.getAnswerID()))
                    throw new IllegalArgumentException();
            }
            answerMapper.insertAnswer(answerSheet.getAnswerList(), answerSheet.getAnswerSheetID());
        }
    }

    public List<AnswerSheet> getAnswerSheetByPaperId(Integer paperID) {
        return answerMapper.getAnswerSheetByPaperId(paperID);
    }

    public void deleteAnswerSheet(Integer paperID, Integer answerSheetID) {
        answerMapper.deleteAnswerSheet(paperID, answerSheetID);
    }

    public AnswerSheet getAnswerSheet(Integer answerSheetID) {
        return answerMapper.getAnswerSheet(answerSheetID);
    }

    public List<AnswerStatistics> getStatistics(Integer paperID, List<Integer> questionIDList) {
        List<AnswerStatistics> answerStatisticsList = new LinkedList<>();
        for (Integer questionID :
                questionIDList) {
            AnswerStatistics answerStatistics = answerMapper.getStatistics(paperID, questionID);
            if (answerStatistics == null || answerStatistics.getStatisticsList() == null || answerStatistics.getStatisticsList().size() == 0)
                continue;
            int sum = 0;
            for (Statistics statistics : answerStatistics.getStatisticsList()) {
                sum += statistics.getNum();
            }
            for (Statistics statistics : answerStatistics.getStatisticsList()) {
                statistics.setPercent(statistics.getNum() * 1.0 / sum * 100);
            }
            answerStatisticsList.add(answerStatistics);
        }
        return answerStatisticsList;
    }
}

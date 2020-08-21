package com.zjuzjy.questionnaire.api.controller;

import com.zjuzjy.questionnaire.domain.service.AnswerService;
import com.zjuzjy.questionnaire.domain.service.PaperService;
import com.zjuzjy.questionnaire.domain.service.TokenService;
import com.zjuzjy.questionnaire.resource.entity.AnswerSheet;
import com.zjuzjy.questionnaire.resource.entity.AnswerStatistics;
import com.zjuzjy.questionnaire.resource.entity.Paper;
import com.zjuzjy.questionnaire.resource.entity.result.ResultMessage;
import com.zjuzjy.questionnaire.resource.entity.result.StatusCode;
import com.zjuzjy.questionnaire.util.HttpUtil;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import java.io.IOException;
import java.util.List;

@RestController
@SuppressWarnings("all")
public class PaperControl {

    @Resource
    TokenService tokenService;

    @Resource
    PaperService paperService;

    @Resource
    AnswerService answerService;

    @PostMapping("/paper/create")
    public ResultMessage createPaper(@RequestBody Paper paper, HttpServletRequest httpServletRequest) throws IOException {
        ResultMessage resultMessage;
        String token = tokenService.getToken(httpServletRequest);
        paper.setUserID(tokenService.getUserByToken(token).getUserID());
        paper.setStatus(paper.getStatus() == null ? 0 : paper.getStatus());
        paper.setMaxSubmit(paper.getMaxSubmit() == null ? 0 : paper.getMaxSubmit());
        paperService.createPaper(paper);
        resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
        resultMessage.setMsg("问卷创建成功！");
        return resultMessage;
    }

    @GetMapping("/paper/get")
    public ResultMessage getUserPaper(HttpServletRequest httpServletRequest) {
        ResultMessage resultMessage;
        String token = tokenService.getToken(httpServletRequest);
        try {
            Integer userID = tokenService.getUserByToken(token).getUserID();
            resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
            resultMessage.putData("papers", paperService.getUserPaper(userID));
        } catch (IOException e) {
            e.printStackTrace();
            resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_ERROR);
        }
        return resultMessage;
    }

    @GetMapping("/paper/{paperID}/delete")
    public ResultMessage deletePaper(@PathVariable Integer paperID) {
        paperService.deletePaper(paperID);
        ResultMessage resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
        resultMessage.setMsg("问卷删除成功！");
        return resultMessage;
    }

    @GetMapping("paper/{paperID}/{status}")
    public ResultMessage setPaperStatus(@PathVariable Integer paperID, @PathVariable Integer status) {
        ResultMessage resultMessage;
        paperService.setPaperStatus(paperID, status);
        resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
        resultMessage.setMsg(status == 1 ? "发布成功！" : "关闭成功！");
        return resultMessage;
    }

    @PostMapping("paper/{paperID}/update")
    public ResultMessage updatePaperQuestion(@PathVariable Integer paperID, @RequestBody Paper paper) {
        ResultMessage resultMessage;
        try {
            Paper paper1 = paperService.getPaperInfo(paperID);
            if (paper1 != null && paper1.getStatus() == 0) {
                paper.setPaperID(paperID);
                paperService.updatePaperQuestion(paper);
                resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
                resultMessage.setMsg("修改成功！");
                return resultMessage;
            } else if (paper1 == null) {
                resultMessage = new ResultMessage(StatusCode.PARAMETER_VALIDATE_ILLEGAL);
                resultMessage.setMsg("问卷不存在!");
                return resultMessage;
            }
            resultMessage = new ResultMessage(StatusCode.HTTP_ACCESS_ERROR);
            resultMessage.setMsg("问卷已发布！");
            return resultMessage;
        } catch (Exception e) {
            e.printStackTrace();
            return new ResultMessage(StatusCode.SERVICE_RUN_ERROR);
        }
    }

    @GetMapping("paper/{paperID}/detail")
    public ResultMessage getPaper(@PathVariable Integer paperID) {
        Paper paper = paperService.getPaper(paperID);
        ResultMessage resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
        resultMessage.putData("paper", paper);
        return resultMessage;
    }

    @PostMapping("paper/{paperID}/submit")
    public ResultMessage submitAnswerSheet(@PathVariable Integer paperID, @RequestBody AnswerSheet answerSheet, HttpServletRequest httpServletRequest) {
        ResultMessage resultMessage;
        try {
            Paper paper = paperService.getPaperInfo(paperID);
            AnswerService.PaperStatus paperStatus = answerService.checkPaperAccess(paper, httpServletRequest);
            resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
            resultMessage.setMsg(paperStatus.getMsg());
            if (paperStatus == AnswerService.PaperStatus.PAPER_SUCCESS) {
                answerSheet.setPaperID(paperID);
                String token = tokenService.getToken(httpServletRequest);
                Integer userID = tokenService.hasToken(token) ? tokenService.getUserByToken(token).getUserID() : -1;
                if (paper.getAnonymous() == 1)
                    userID = 0;
                answerSheet.setUserID(userID);
                answerSheet.setIpAddress(HttpUtil.getUserIP(httpServletRequest));
                answerService.createAnswerSheet(answerSheet);
            } else {
                resultMessage.setStatus(StatusCode.PARAMETER_VALIDATE_ILLEGAL.getStatus());
            }
        } catch (IOException e) {
            resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_ERROR);
            e.printStackTrace();
        }
        return resultMessage;
    }

    @GetMapping("paper/{paperID}/answersheet")
    public ResultMessage getAllAnswerSheet(@PathVariable Integer paperID) {
        List<AnswerSheet> answerSheetList = answerService.getAnswerSheetByPaperId(paperID);
        Paper paper = paperService.getPaper(paperID);
        ResultMessage resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
        resultMessage.putData("answerSheetList", answerSheetList);
        resultMessage.putData("paper", paper);
        return resultMessage;
    }

    @GetMapping("paper/{paperID}/answersheet/{answerSheetID}/delete")
    public ResultMessage deleteAnswerSheet(@PathVariable Integer paperID,
                                           @PathVariable Integer answerSheetID) {
        answerService.deleteAnswerSheet(paperID, answerSheetID);
        ResultMessage resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
        resultMessage.setMsg("答卷删除成功！");
        return resultMessage;
    }

    @GetMapping("paper/{paperID}/answersheet/{answerSheetID}")
    public ResultMessage getAnswerSheetDetail(@PathVariable Integer paperID, @PathVariable Integer answerSheetID) {
        AnswerSheet answerSheet = answerService.getAnswerSheet(answerSheetID);
        Paper paper = paperService.getPaper(paperID);
        ResultMessage resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
        resultMessage.putData("answerSheet", answerSheet);
        resultMessage.putData("paper", paper);
        return resultMessage;
    }

    @GetMapping("paper/{paperID}/statistics")
    public ResultMessage getStatistics(@PathVariable Integer paperID) {
        List<Integer> questionIDs = paperService.getQuestionId(paperID);
        List<AnswerStatistics> statisticsList = answerService.getStatistics(paperID, questionIDs);
        ResultMessage resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_ERROR);
        resultMessage.putData("statisticsList", statisticsList);
        return resultMessage;
    }
}
/*
 Navicat MySQL Data Transfer

 Source Server         : localhost
 Source Server Type    : MySQL
 Source Server Version : 80018
 Source Host           : localhost
 Source Database       : questionnaire2

 Target Server Type    : MySQL
 Target Server Version : 80018
 File Encoding         : utf-8

 Date: 06/22/2020 19:03:47 PM
*/

CREATE DATABASE questionnaire;
USE questionnaire;

SET NAMES utf8;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
--  Table structure for `answer`
-- ----------------------------
DROP TABLE IF EXISTS `answer`;
CREATE TABLE `answer` (
  `answerID` int(48) NOT NULL AUTO_INCREMENT,
  `answerSheetID` int(48) NOT NULL,
  `questionID` int(48) NOT NULL,
  `answer` varchar(512) DEFAULT NULL,
  PRIMARY KEY (`answerID`),
  KEY `delete_answer` (`questionID`),
  KEY `delete_answers` (`answerSheetID`),
  CONSTRAINT `delete_answers` FOREIGN KEY (`answerSheetID`) REFERENCES `answersheet` (`answerSheetID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=99 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
--  Table structure for `answerSheet`
-- ----------------------------
DROP TABLE IF EXISTS `answerSheet`;
CREATE TABLE `answerSheet` (
  `answerSheetID` int(48) NOT NULL AUTO_INCREMENT,
  `paperID` int(48) NOT NULL,
  `userID` int(48) DEFAULT NULL,
  `ipAddress` varchar(48) DEFAULT NULL,
  `submitTime` datetime DEFAULT NULL,
  PRIMARY KEY (`answerSheetID`,`paperID`),
  KEY `paperID` (`paperID`),
  CONSTRAINT `delete_paperID` FOREIGN KEY (`paperID`) REFERENCES `paper` (`paperID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=43 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
--  Table structure for `association`
-- ----------------------------
DROP TABLE IF EXISTS `association`;
CREATE TABLE `association` (
  `optionID` varchar(11) DEFAULT NULL,
  `cascadeID` varchar(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
--  Table structure for `paper`
-- ----------------------------
DROP TABLE IF EXISTS `paper`;
CREATE TABLE `paper` (
  `paperID` int(48) NOT NULL AUTO_INCREMENT,
  `userID` int(48) NOT NULL,
  `papername` varchar(48) DEFAULT NULL,
  `description` varchar(512) DEFAULT NULL,
  `priority` int(11) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `maxSubmit` int(11) DEFAULT NULL,
  `startTime` date DEFAULT NULL,
  `endTime` date DEFAULT NULL,
  `anonymous` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`paperID`),
  KEY `user_delete` (`userID`),
  CONSTRAINT `user_delete` FOREIGN KEY (`userID`) REFERENCES `user` (`userID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
--  Table structure for `question`
-- ----------------------------
DROP TABLE IF EXISTS `question`;
CREATE TABLE `question` (
  `questionID` int(48) NOT NULL AUTO_INCREMENT,
  `paperID` int(48) NOT NULL,
  `type` int(4) DEFAULT NULL,
  `title` varchar(11) DEFAULT NULL,
  `required` int(1) DEFAULT NULL,
  `minTitle` varchar(11) DEFAULT NULL,
  `maxTitle` varchar(11) DEFAULT NULL,
  `minVal` int(11) DEFAULT NULL,
  `maxVal` int(11) DEFAULT NULL,
  PRIMARY KEY (`questionID`),
  KEY `question_delete` (`paperID`),
  CONSTRAINT `question_delete` FOREIGN KEY (`paperID`) REFERENCES `paper` (`paperID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=169 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
--  Table structure for `questionOption`
-- ----------------------------
DROP TABLE IF EXISTS `questionOption`;
CREATE TABLE `questionOption` (
  `optionID` int(48) NOT NULL AUTO_INCREMENT,
  `questionID` int(48) NOT NULL,
  `optionDescription` varchar(512) DEFAULT NULL,
  PRIMARY KEY (`optionID`),
  KEY `option_delete` (`questionID`) USING BTREE,
  CONSTRAINT `option_delete` FOREIGN KEY (`questionID`) REFERENCES `question` (`questionID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=493 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci ROW_FORMAT=DYNAMIC;

-- ----------------------------
--  Table structure for `user`
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `userID` int(48) NOT NULL AUTO_INCREMENT,
  `username` varchar(48) DEFAULT NULL,
  `password` varchar(48) DEFAULT NULL,
  `phoneNumber` varchar(16) DEFAULT NULL,
  `email` varchar(48) DEFAULT NULL,
  PRIMARY KEY (`userID`),
  UNIQUE KEY `email` (`email`),
  UNIQUE KEY `phoneNumber` (`phoneNumber`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

SET FOREIGN_KEY_CHECKS = 1;

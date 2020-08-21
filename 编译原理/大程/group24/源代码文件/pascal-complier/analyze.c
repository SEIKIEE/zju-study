@PostMapping("/user/login")
public ResultMessage login(@RequestBody User user, HttpServletRequest httpServletRequest) throws JsonProcessingException {
    ResultMessage resultMessage;
    User user1 = userService.getUser(user);
    if (user1 != null) {
        resultMessage = new ResultMessage(StatusCode.SERVICE_RUN_SUCCESS);
    } else {
        resultMessage = new ResultMessage(StatusCode.USER_LOGIN_ERROR);
    }
    return resultMessage;
}

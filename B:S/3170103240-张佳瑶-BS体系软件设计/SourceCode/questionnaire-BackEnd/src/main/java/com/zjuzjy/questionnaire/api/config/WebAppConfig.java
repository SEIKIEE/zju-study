package com.zjuzjy.questionnaire.api.config;

import com.zjuzjy.questionnaire.api.interceptor.PriorityIntercept;
import com.zjuzjy.questionnaire.api.interceptor.TokenInterceptor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;


@Configuration
public class WebAppConfig implements WebMvcConfigurer {

    private static final String tokenInterceptorPath = "/paper/**";
    private static final String paperGetInterceptorExcludePath = "/paper/get";
    private static final String paperCreateInterceptorExcludePath = "/paper/create";
    private static final String tokenInterceptorExcludePath = "/paper/*/detail";
    private static final String paperSubmitInterceptorExcludePath = "/paper/*/submit";

    @Autowired
    private TokenInterceptor tokenInterceptor;

    @Autowired
    private PriorityIntercept priorityIntercept;

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(tokenInterceptor)
                .addPathPatterns(tokenInterceptorPath)
                .excludePathPatterns(tokenInterceptorExcludePath)
                .excludePathPatterns(paperSubmitInterceptorExcludePath);
        registry.addInterceptor(priorityIntercept)
                .addPathPatterns(tokenInterceptorPath)
                .excludePathPatterns(paperGetInterceptorExcludePath)
                .excludePathPatterns(paperCreateInterceptorExcludePath)
                .excludePathPatterns(tokenInterceptorExcludePath)
                .excludePathPatterns(paperSubmitInterceptorExcludePath);
    }

}
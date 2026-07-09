//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_INPUTVIEW_H
#define AUTOMATIC_CV_FILTERING_IN_CL_INPUTVIEW_H
#pragma once
#include <string>

class InputView {
public:
    static std::string getStringInput(const std::string& prompt);
    static int getIntInput(const std::string& prompt);
    static bool getConfirmation(const std::string& prompt);
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_INPUTVIEW_H

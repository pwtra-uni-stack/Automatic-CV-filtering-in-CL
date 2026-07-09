//
// Created by ADMIN on 10/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_MENUVIEW_H
#define AUTOMATIC_CV_FILTERING_IN_CL_MENUVIEW_H
#pragma once
#include <string>
#include <vector>

class MenuView {
public:
    int showMainMenu();
    void showSubMenu(const std::string& title, const std::vector<std::string>& options);
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_MENUVIEW_H

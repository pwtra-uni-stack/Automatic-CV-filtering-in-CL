//
// Created by ADMIN on 09/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_DUPLICATECVEXCEPTION_H
#define AUTOMATIC_CV_FILTERING_IN_CL_DUPLICATECVEXCEPTION_H

#include <exception>
#include <string>

class DuplicateCVException:public std::exception{

private:

    std::string msg;

public:

    DuplicateCVException(std::string m):msg(m){}

    const char* what()const noexcept override{

        return msg.c_str();
    }

};

#endif //AUTOMATIC_CV_FILTERING_IN_CL_DUPLICATECVEXCEPTION_H

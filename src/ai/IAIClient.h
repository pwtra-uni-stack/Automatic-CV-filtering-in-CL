#ifndef AUTOMATIC_CV_FILTERING_IN_CL_IAICLIENT_H
#define AUTOMATIC_CV_FILTERING_IN_CL_IAICLIENT_H

#include <string>

class IAIClient {
public:
    virtual ~IAIClient() = default;
    virtual std::string danhGiaCV(std::string noiDungCV, std::string yeuCauJob) = 0;
};

#endif // AUTOMATIC_CV_FILTERING_IN_CL_IAICLIENT_H
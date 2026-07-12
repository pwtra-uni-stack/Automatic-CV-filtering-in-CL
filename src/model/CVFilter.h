//
// Created by ADMIN on 09/07/2026.
//

#ifndef AUTOMATIC_CV_FILTERING_IN_CL_CVFILTER_H
#define AUTOMATIC_CV_FILTERING_IN_CL_CVFILTER_H
#include "CV.h"

//Lớp cha cơ sở (Base class) thiết lập khuôn mẫu cho tính chất kế thừa & đa hình
class CVFilter {
public:
    //Hàm thuần ảo = 0 bắt buộc các lớp con bộ lọc phải ghi dè định nghĩa lại điều kiện lọc
    virtual bool match(CV cv) = 0;

    //Destructor ảo bảo đảm giải phóng bộ nhớ sạch sẽ, an toàn khi làm việc với con trỏ OOP
    virtual ~CVFilter() {}
};
#endif //AUTOMATIC_CV_FILTERING_IN_CL_CVFILTER_H

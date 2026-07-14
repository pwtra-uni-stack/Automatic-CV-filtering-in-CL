#include "parser/PdfParser.h"
#include "parser/CodeParser.h"
#include <iostream>

int main() {
    DocumentParser* bo_doc_cv = new PdfParser();
    CodeParser bo_doc_code;
    std::string du_lieu_cv = bo_doc_cv->parse("Data/UngVienA_CV.pdf");
    std::string du_lieu_code = bo_doc_code.quétThưMụcCode("Data/UngVienA_Project/");
    delete bo_doc_cv;
    std::cout << "Trích xuất xong! Sẵn sàng chuyển cho AI quét tự động." << std::endl;
    return 0;
}
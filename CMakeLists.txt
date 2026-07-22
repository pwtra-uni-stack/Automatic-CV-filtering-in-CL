cmake_minimum_required(VERSION 3.10)
project(CV_Auto)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ===== Include directories =====
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(src)
include_directories(third_party/json)

# ===== Liệt kê toàn bộ các file nguồn (.cpp) và header (.h) =====
set(SOURCES
        src/main.cpp

        # Controller & Services
        src/controller/CVController.cpp
        src/controller/CVController.h
        src/controller/CVService.cpp
        src/controller/CVService.h

        # AI Module (Gemini, Ollama, Interface)
        src/ai/IAIClient.h
        src/ai/AIFactory.h
        src/ai/GeminiClient.cpp
        src/ai/GeminiClient.h
        src/ai/OllamaClient.cpp
        src/ai/OllamaClient.h

        # Parsers & Scanners
        src/parser/PdfParser.cpp
        src/parser/CodeParser.cpp
        src/scanner/BasicScan.cpp
        src/scanner/BasicScan.h
        src/scanner/AdvancedScan.cpp
        src/scanner/AdvancedScan.h
        src/scanner/ScanEngine.cpp
        src/scanner/ScanEngine.h

        # Models & Filters
        src/model/CV.cpp
        src/model/CV.h
        src/model/CVDatabase.cpp
        src/model/CVDatabase.h
        src/model/FileManager.cpp
        src/model/FileManager.h
        src/model/SkillFilter.cpp
        src/model/SkillFilter.h
        src/model/ExperienceFilter.cpp
        src/model/ExperienceFilter.h
        src/model/EducationFilter.cpp
        src/model/EducationFilter.h

        # Views & Utils
        src/view/MenuView.cpp
        src/view/MenuView.h
        src/view/InputView.cpp
        src/view/InputView.h
        src/view/OutputView.cpp
        src/view/OutputView.h
        src/utils/EnvLoader.h
        src/utils/EnvLoader.cpp
        src/utils/Logger.cpp
        src/utils/Logger.h
)

add_executable(CV_Auto ${SOURCES})

# ===== Tìm thư viện curl =====
if(NOT CURL_ROOT)
    set(CURL_ROOT "D:/CMCU/curl-8.21.0_3-win64-mingw/curl-8.21.0_3-win64-mingw")
endif()

include_directories(${CURL_ROOT}/include)
link_directories(${CURL_ROOT}/lib)

# ===== Link thư viện libcurl và hệ thống =====
target_link_libraries(CV_Auto PRIVATE
        ${CURL_ROOT}/lib/libcurl.dll.a
        ${CURL_ROOT}/lib/libssl.a
        ${CURL_ROOT}/lib/libcrypto.a
        ${CURL_ROOT}/lib/libz.a
        ${CURL_ROOT}/lib/libzstd.a
        ${CURL_ROOT}/lib/libbrotlidec.a
        ${CURL_ROOT}/lib/libbrotlicommon.a
        ${CURL_ROOT}/lib/libnghttp2.a
        ${CURL_ROOT}/lib/libngtcp2.a
        ${CURL_ROOT}/lib/libngtcp2_crypto_libressl.a
        ${CURL_ROOT}/lib/libpsl.a
        ${CURL_ROOT}/lib/libssh2.a
        ws2_32
        wldap32
        crypt32
        bcrypt
        iphlpapi
        ole32
        uuid
)
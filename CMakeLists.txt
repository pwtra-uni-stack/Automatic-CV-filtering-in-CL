cmake_minimum_required(VERSION 3.10)
project(CV_Auto)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(src)
include_directories(third_party/json)

# ===== Liệt kê các file nguồn một cách rõ ràng =====
set(SOURCES
        src/main.cpp
        src/parser/PdfParser.cpp
        src/parser/CodeParser.cpp
        src/utils/EnvLoader.h
        src/ai/GeminiClient.h
        src/ai/GeminiClient.cpp
        # Thêm các file .cpp khác nếu có, ví dụ:
        # src/ai/GeminiClient.cpp
)

add_executable(CV_Auto ${SOURCES})

# ===== Tìm thư viện curl =====
if(NOT CURL_ROOT)
    set(CURL_ROOT "D:/CMCU/curl-8.21.0_3-win64-mingw/curl-8.21.0_3-win64-mingw")
endif()

include_directories(${CURL_ROOT}/include)
link_directories(${CURL_ROOT}/lib)

# ===== Link thư viện =====
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

# ===== Thêm nlohmann/json (header-only) =====
include_directories(third_party/json)
# Thêm file OllamaClient.cpp vào danh sách source
add_executable(Automatic-CV-filtering-in-CL
        src/main.cpp
        src/ai/GeminiClient.cpp
        src/ai/OllamaClient.cpp   # <--- Thêm dòng này
        # ... các file .cpp khác trong project
)
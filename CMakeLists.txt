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
        src/parser/DocxParser.cpp
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

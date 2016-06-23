set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp Document.cpp Document.h CMPDocument.cpp CMPDocument.h FlexLexer.h lex.yy.cc Lexer.cpp Lexer.h
        scanner.h Detector.cpp Detector.h FingerPrint.cpp FingerPrint.h CalcFingerPrintStrategy.cpp CalcFingerPrintStrategy.h)
add_executable(CopyDetect ${SOURCE_FILES})
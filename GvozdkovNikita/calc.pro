TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        functions.cpp \
        main.cpp \
        token_stream.cpp \
        variable.cpp

HEADERS += \
    Token.h \
    Token_stream.h \
    Variable.h \
    functions.h \
    std_lib_facilities.h

DISTFILES += \
    input.txt

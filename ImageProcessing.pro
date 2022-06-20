QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canny_filter.cpp \
    gaussian_filter.cpp \
    laplacian_filter.cpp \
    main.cpp \
    image_processing.cpp \
    sharpening_filter.cpp

HEADERS += \
    canny_filter.h \
    gaussian_filter.h \
    image_processing.h \
    laplacian_filter.h \
    sharpening_filter.h

FORMS += \
    image_processing.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

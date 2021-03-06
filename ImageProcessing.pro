QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    change_img_colour.cpp \
    gaussian_filter.cpp \
    gradient_filter.cpp \
    horizontalsobel_filter.cpp \
    laplacian_filter.cpp \
    main.cpp \
    image_processing.cpp \
    mean_filter.cpp \
    median_filter.cpp \
    verticalsobel_filter.cpp

HEADERS += \
    change_img_colour.h \
    gaussian_filter.h \
    gradient_filter.h \
    horizontalsobel_filter.h \
    image_processing.h \
    laplacian_filter.h \
    mean_filter.h \
    median_filter.h \
    verticalsobel_filter.h

FORMS += \
    image_processing.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

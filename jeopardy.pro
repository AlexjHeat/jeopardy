QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcategorydialog.cpp \
    board.cpp \
    category.cpp \
    categorymanager.cpp \
    editcategorydialog.cpp \
    main.cpp \
    controlwindow.cpp \
    question.cpp \
    questionseditdialog.cpp \
    removecategorydialog.cpp

HEADERS += \
    addcategorydialog.h \
    board.h \
    category.h \
    categorymanager.h \
    controlwindow.h \
    editcategorydialog.h \
    question.h \
    questionseditdialog.h \
    removecategorydialog.h

FORMS += \
    addcategorydialog.ui \
    controlwindow.ui \
    editcategorydialog.ui \
    questionseditdialog.ui \
    removecategorydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

#-------------------------------------------------
#
# Project created by QtCreator 2011-05-30T21:00:15
#
#-------------------------------------------------

QT       += core gui

TARGET = clientgui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    userinfo.cpp \
    serverinfo.cpp \
    message.cpp \
    friendlist.cpp \
    applyid.cpp \
	usermainwindow.cpp \
    talk.cpp \
    talklist.cpp \
    modifyuserinfo.cpp \
    addfriend.cpp \
    addfriendreply.cpp

HEADERS  += mainwindow.h \
    userinfo.h \
    serverinfo.h \
    message.h \
    friendlist.h \
    applyid.h \
    usermainwindow.h \
    talk.h \
    talklist.h \
    modifyuserinfo.h \
    addfriend.h \
    addfriendreply.h

FORMS    += mainwindow.ui \
    serverinfo.ui \
    applyid.ui \
    usermainwindow.ui \
    talk.ui \
    modifyuserinfo.ui \
    addfriend.ui \
    addfriendreply.ui

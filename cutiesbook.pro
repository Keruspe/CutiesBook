TEMPLATE = app
TARGET = cutiesbook
DEPENDPATH += .
INCLUDEPATH += . src

SOURCES += \
	src/application.cpp \
	src/mainwindow.cpp \
	src/main.cpp

HEADERS += \
	src/application.hpp \
	src/mainwindow.hpp


unix {
	target.path = /usr/bin/
	INSTALLS += target
}

debug {
	OBJECTS_DIR = tmp/debug
	MOC_DIR = tmp/debug
	RCC_DIR = tmp/debug
}

release {
	OBJECTS_DIR = tmp/release
	MOC_DIR = tmp/release
	RCC_DIR = tmp/release
}

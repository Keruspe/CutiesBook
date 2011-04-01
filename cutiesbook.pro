TEMPLATE = app
TARGET = cutiesbook
DEPENDPATH += .
INCLUDEPATH += . src

QMAKE_CXXFLAGS += \
	-Wall \
	-Wextra \
	-Werror

SOURCES += \
	src/application.cpp \
	src/company.cpp \
	src/contact.cpp \
	src/directory.cpp \
	src/dialogs.cpp \
	src/individual.cpp \
	src/list.cpp \
	src/mainwindow.cpp \
	src/main.cpp \
	src/number.cpp \
	src/widgets.cpp

HEADERS += \
	src/application.hpp \
	src/company.hpp \
	src/contact.hpp \
	src/directory.hpp \
	src/dialogs.hpp \
	src/individual.hpp \
	src/list.hpp \
	src/mainwindow.hpp \
	src/number.hpp \
	src/widgets.hpp


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

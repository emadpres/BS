# Add more folders to ship with the application, here
folder_01.source = qml
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

QT += declarative core qui xml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =


SOURCES += main.cpp \
    cfilebrowser.cpp \
    thumbnailiconprovider.cpp \
    cqmlfilebrowsercomponent.cpp \
    cprojectitem.cpp \
    cprojectmanagement.cpp \
    cappconfig.cpp \
    ccommandmanager.cpp \
    crepositorymanager.cpp

#qtcAddDeployment()

HEADERS += \
    cfilebrowser.h \
    thumbnailiconprovider.h \
    cqmlfilebrowsercomponent.h \
    cprojectitem.h \
    cprojectmanagement.h \
    cappconfig.h \
    ccommandmanager.h \
    crepositorymanager.h

OTHER_FILES += \
    qml/ProjectItem.qml \
    qml/main.qml \
    qml/Label.qml \
    qml/Button.qml

RESOURCES += \
    AppResource.qrc

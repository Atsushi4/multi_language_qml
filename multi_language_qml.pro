QT += quick

CONFIG += c++17

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    translations/multi_language_qml_ja_JP.ts \
    translations/multi_language_qml_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations
QM_FILES_RESOURCE_PREFIX = /i18n/

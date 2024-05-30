#include "stylehelper.h"

QString styleHelper::lightCellBgCollor() {
    return
        "QPushButton {"
        "    border: 1px solid #73614d;"  // Додано мінімальну рамку
        "    margin: 0;"
        "    padding: 0;"
        "    border-radius: 0;"
        "    background-color: #f1dbb6;"
        "}"
        "QPushButton::hover {"
        "    background-color: #e0cdab;"
        "}"
        "QPushButton::pressed {"
        "    background-color: #ccba9b;"
        "}";
}

QString styleHelper::darkCellBgCollor() {
    return
        "QPushButton {"
        "    border: 1px solid #73614d;"  // Додано мінімальну рамку
        "    margin: 0;"
        "    padding: 0;"
        "    border-radius: 0;"
        "    background-color: #b58964;"
        "}"
        "QPushButton::hover {"
        "    background-color: #a37b5a;"
        "}"
        "QPushButton::pressed {"
        "    background-color: #8f6b4f;"
        "}";
}

QString styleHelper::moveCellColor() {
    return
        "QPushButton {"
        "    border: 1px solid #73614d;"  // Додано мінімальну рамку
        "    margin: 0;"
        "    padding: 0;"
        "    border-radius: 0;"
        "    background-color: #3bd673;"
        "}"
        "QPushButton::hover {"
        "    background-color: #36c76b;"
        "}"
        "QPushButton::pressed {"
        "    background-color: #2fad5d;"
        "}";
}

QString styleHelper::captureCellColor() {
    return
        "QPushButton {"
        "    border: 1px solid #73614d;"  // Додано мінімальну рамку
        "    margin: 0;"
        "    padding: 0;"
        "    border-radius: 0;"
        "    background-color: #d6473b;"
        "}"
        "QPushButton::hover {"
        "    background-color: #c74138;"
        "}"
        "QPushButton::pressed {"
        "    background-color: #ad3931;"
        "}";
}

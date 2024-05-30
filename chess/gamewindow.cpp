#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QApplication>
#include <QIcon>

gameWindow::gameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    grid = qobject_cast <QGridLayout*>(ui->gridLayout->layout());

    lockButtons();
    setDefaultPlaygroundColor();
    setButtonIconSize();
    configurationGameAreaButtons();
    currentFigure = NULL;

}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::configurationGameAreaButtons() {

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {

            QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(i, j)->widget());

            btn->setProperty("row", i);
            btn->setProperty("column", j);

            connect(btn, &QPushButton::clicked, this, &gameWindow::onGameAreaButtonClicked);
        }
    }
}

void gameWindow::setDefaultPlaygroundColor() {

    for (int i = 0; i < grid->rowCount(); ++i) {
        for (int j = 0; j < grid->columnCount(); ++j) {

            QLayoutItem *item = grid->itemAtPosition(i, j);
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());

            if ((i + j) % 2 == 0) {
                button->setStyleSheet(styleHelper::lightCellBgCollor());
            }

            else {
                button->setStyleSheet(styleHelper::darkCellBgCollor());
            }

        }
    }
}

void gameWindow::lockButtons() {

    for (int i = 0; i < grid->rowCount(); ++i) {
        for (int j = 0; j < grid->columnCount(); ++j) {

            QLayoutItem *item = grid->itemAtPosition(i, j);
            item->widget()->setEnabled(false);
        }
    }
}

void gameWindow::setButtonIconSize() {

    for (int i = 0; i < grid->rowCount(); ++i) {
        for (int j = 0; j < grid->columnCount(); ++j) {

            QLayoutItem *item = grid->itemAtPosition(i, j);
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());
            button->setIconSize(QSize(50, 50));
        }
    }
}

void gameWindow::startGameFigurePosition() {

    //Rook
    chessBoard[0][0] = Rook(false);
    chessBoard[0][7] = Rook(false);
    chessBoard[7][0] = Rook(true);
    chessBoard[7][7] = Rook(true);

    //Knight
    chessBoard[0][1] = Knight(false);
    chessBoard[0][6] = Knight(false);
    chessBoard[7][1] = Knight(true);
    chessBoard[7][6] = Knight(true);

    //Bishop
    chessBoard[0][2] = Bishop(false);
    chessBoard[0][5] = Bishop(false);
    chessBoard[7][2] = Bishop(true);
    chessBoard[7][5] = Bishop(true);

    //King
    chessBoard[0][4] = King(false);
    chessBoard[7][4] = King(true);

    //Queen
    chessBoard[0][3] = Queen(false);
    chessBoard[7][3] = Queen(true);

    for (int i = 0; i < 8; ++i) {
        chessBoard[1][i] = Pawn(false);
        chessBoard[6][i] = Pawn(true);
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            chessBoard[i][j] = Figure();
            chessBoard[i][j].isEmpty = true;
        }
    }
}



void gameWindow::on_startButton_clicked()
{
    startGameFigurePosition();
    setDefaultPlaygroundColor();
    setDefaultFigureIcons();
    ui->startButton->setText("Restart");
    isWhitePlayerStep = true;
    hilightCurrentPlayerFigures();
}

void gameWindow::setDefaultFigureIcons() {

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {

            QLayoutItem *item = grid->itemAtPosition(i, j);
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());

            if(!chessBoard[i][j].isEmpty) {

                QIcon figureIcon(chessBoard[i][j].getIconPath());
                button->setIcon(figureIcon);
            }

            else  {

                 button->setIcon(QIcon());
            }

            // if (chessBoard[i%8][j].isWhite) {
            //     button->setEnabled(true);
            // }
        }
    }
}

void gameWindow::hilightCurrentPlayerFigures() {

    //hilight current player figures
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {

            if(chessBoard[i][j].isEmpty){
                continue;
            }

            QLayoutItem *item = grid->itemAtPosition(i, j);
            QPushButton *button = qobject_cast<QPushButton*>(item->widget());

            if(isWhitePlayerStep && chessBoard[i][j].isWhite){
                button->setEnabled(true);
            }
            else if (!isWhitePlayerStep && !chessBoard[i][j].isWhite) {
                button->setEnabled(true);
            }
            else button->setEnabled(false);
        }
    }

    //choose current figure

}

bool gameWindow::isCurrentStepFigureColor(int i, int j){

    if (!chessBoard[i][j].isEmpty && chessBoard[i][j].isWhite && isWhitePlayerStep)
        return true;

    else if (!chessBoard[i][j].isEmpty && !chessBoard[i][j].isWhite && !isWhitePlayerStep)
        return true;

    else return false;
}

void gameWindow::onGameAreaButtonClicked() {

    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    int row = btn->property("row").toInt();
    int column = btn->property("column").toInt();

    if (isCurrentStepFigureColor(row, column) && !chessBoard[row][column].isEmpty) {

        setDefaultPlaygroundColor();
        currentFigure = btn;
        displayLegalMoves(row, column);
    }

    else if (currentFigure != nullptr){

        int currentRow = currentFigure->property("row").toInt();
        int currentColumn = currentFigure->property("column").toInt();

        chessBoard[row][column] = chessBoard[currentRow][currentColumn];

        chessBoard[currentRow][currentColumn].isEmpty = true;
        chessBoard[row][column].isEmpty = false;

        QIcon icon(chessBoard[row][column].getIconPath());
        btn->setIcon(icon);
        currentFigure->setIcon(QIcon());

        currentFigure = nullptr;

        if (chessBoard[row][column].type == "Pawn" && chessBoard[row][column].isFirstMove == true) {

            chessBoard[row][column].isFirstMove = false;
        }

        setDefaultPlaygroundColor();

        if (checkTheKing()) {

            ui->label->setText("The King is Check!");
        }

        else ui->label->setText("");

        isWhitePlayerStep = !isWhitePlayerStep;
        hilightCurrentPlayerFigures();
    }
}

bool gameWindow::isMoveValid(int row, int column) {
    if (row < 0 || row >= BOARD_SIZE || column < 0 || column >= BOARD_SIZE) {
        return false;
    }

    if (isCurrentStepFigureColor(row, column)) {
        return false;
    }

    // if (chessBoard[row][column].type == "King") {
    //     return false;
    // }

    return true;
}

bool gameWindow::isCaptureValid(int row, int column) {
    if (row < 0 || row >= BOARD_SIZE || column < 0 || column >= BOARD_SIZE) {
        return false;
    }

    if (isCurrentStepFigureColor(row, column)) {
        return false;
    }

    if (chessBoard[row][column].type == "King") {
        return false;
    }

    return true;
}

void gameWindow::displayLegalMoves(int row, int column) {

    Figure &figure = chessBoard[row][column];

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {

            QLayoutItem *item = grid->itemAtPosition(i, j);

            if(!isCurrentStepFigureColor(i, j)) {

                item->widget()->setEnabled(false);
            }

            else item->widget()->setEnabled(true);
        }
    }

    QLayoutItem *item = grid->itemAtPosition(row, column);
    item->widget()->setEnabled(false);

    QString type = figure.type;

    if (type == "Pawn") {

        int direction = figure.isWhite ? -1 : 1;

        if(isCaptureValid(row + direction, column) && chessBoard[row + direction][column].isEmpty) {

            QLayoutItem *item = grid->itemAtPosition(row + direction, column);
            item->widget()->setEnabled(true);
            item->widget()->setStyleSheet(styleHelper::moveCellColor());
        }

        if(figure.isFirstMove && isCaptureValid(row + direction * 2, column) && chessBoard[row + direction][column].isEmpty && chessBoard[row + direction * 2][column].isEmpty) {

            QLayoutItem *item = grid->itemAtPosition(row + direction * 2, column);
            item->widget()->setEnabled(true);
            item->widget()->setStyleSheet(styleHelper::moveCellColor());
        }

        if (isCaptureValid(row + direction, column - 1) && !chessBoard[row + direction][column - 1].isEmpty && chessBoard[row + direction][column - 1].isWhite != figure.isWhite) {
            QLayoutItem *item = grid->itemAtPosition(row + direction, column - 1);
            item->widget()->setEnabled(true);
            item->widget()->setStyleSheet(styleHelper::captureCellColor());
        }
        if (isCaptureValid(row + direction, column + 1) && !chessBoard[row + direction][column + 1].isEmpty && chessBoard[row + direction][column + 1].isWhite != figure.isWhite) {
            QLayoutItem *item = grid->itemAtPosition(row + direction, column + 1);
            item->widget()->setEnabled(true);
            item->widget()->setStyleSheet(styleHelper::captureCellColor());
        }
    }

    if (type == "Knight") {

        int knightMoves[8][2] = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };

        for (int i = 0; i < 8; ++i) {
            int newRow = row + knightMoves[i][0];
            int newColumn = column + knightMoves[i][1];

            if (isCaptureValid(newRow, newColumn)) {
                QLayoutItem *item = grid->itemAtPosition(newRow, newColumn);
                item->widget()->setEnabled(true);

                if (chessBoard[newRow][newColumn].isEmpty) {
                    item->widget()->setStyleSheet(styleHelper::moveCellColor());
                }

                else {
                    item->widget()->setStyleSheet(styleHelper::captureCellColor());
                }
            }
        }
    }

    if (type == "Bishop") {

        int directions[4][2] = {
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };

        for (int i = 0; i < 4; ++i) {
            int newRow = row + directions[i][0];
            int newColumn = column + directions[i][1];

            while (isCaptureValid(newRow, newColumn) && chessBoard[newRow][newColumn].isEmpty) {
                QLayoutItem *item = grid->itemAtPosition(newRow, newColumn);
                item->widget()->setEnabled(true);

                newRow += directions[i][0];
                newColumn += directions[i][1];
                item->widget()->setStyleSheet(styleHelper::moveCellColor());
            }

            if (isCaptureValid(newRow, newColumn) && !chessBoard[newRow][newColumn].isEmpty && chessBoard[newRow][newColumn].isWhite != figure.isWhite) {
                QLayoutItem *item = grid->itemAtPosition(newRow, newColumn);
                item->widget()->setEnabled(true);
                item->widget()->setStyleSheet(styleHelper::captureCellColor());
            }
        }
    }

    if (type == "Rook") {

        int directions[4][2] = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        for (int i = 0; i < 4; ++i) {
            int newRow = row + directions[i][0];
            int newColumn = column + directions[i][1];

            while (isCaptureValid(newRow, newColumn) && chessBoard[newRow][newColumn].isEmpty) {
                QLayoutItem *item = grid->itemAtPosition(newRow, newColumn);
                item->widget()->setEnabled(true);

                newRow += directions[i][0];
                newColumn += directions[i][1];
                item->widget()->setStyleSheet(styleHelper::moveCellColor());
            }

            if (isCaptureValid(newRow, newColumn) && !chessBoard[newRow][newColumn].isEmpty && chessBoard[newRow][newColumn].isWhite != figure.isWhite) {
                QLayoutItem *item = grid->itemAtPosition(newRow, newColumn);
                item->widget()->setEnabled(true);
                item->widget()->setStyleSheet(styleHelper::captureCellColor());
            }
        }
    }

    if (type == "Queen") {

        int directions[8][2] = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1},
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };

        for (int i = 0; i < 8; ++i) {
            int newRow = row + directions[i][0];
            int newColumn = column + directions[i][1];

            while (isCaptureValid(newRow, newColumn) && chessBoard[newRow][newColumn].isEmpty) {
                QLayoutItem *item = grid->itemAtPosition(newRow, newColumn);
                item->widget()->setEnabled(true);

                newRow += directions[i][0];
                newColumn += directions[i][1];
                item->widget()->setStyleSheet(styleHelper::moveCellColor());
            }

            if (isCaptureValid(newRow, newColumn) && !chessBoard[newRow][newColumn].isEmpty && chessBoard[newRow][newColumn].isWhite != figure.isWhite) {
                QLayoutItem *item = grid->itemAtPosition(newRow, newColumn);
                item->widget()->setEnabled(true);
                item->widget()->setStyleSheet(styleHelper::captureCellColor());
            }
        }
    }

    if (type == "King") {

        int kingMoves[8][2] = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1},
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };

        for (int i = 0; i < 8; ++i) {
            int newRow = row + kingMoves[i][0];
            int newColumn = column + kingMoves[i][1];

            if (isCaptureValid(newRow, newColumn)) {
                QLayoutItem *item = grid->itemAtPosition(newRow, newColumn);
                item->widget()->setEnabled(true);

                if (chessBoard[newRow][newColumn].isEmpty) {
                    item->widget()->setStyleSheet(styleHelper::moveCellColor());
                }

                else {
                    item->widget()->setStyleSheet(styleHelper::captureCellColor());
                }
            }
        }
    }
}

bool gameWindow::checkTheKing() {


    //find current-color King

    int kingRow, kingColumn;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (chessBoard[i][j].type == "King" && chessBoard[i][j].isWhite != isWhitePlayerStep) {
                kingRow = i;
                kingColumn = j;
            }
            kingValidMoves[i][j] = true;
        }
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {

            Figure &figure = chessBoard[i][j];

            if (figure.isWhite != isWhitePlayerStep && figure.type != "King" && !figure.isEmpty) {

                kingValidMoves[i][j] = false;
            }

            if (figure.type == "Pawn" && figure.isWhite == isWhitePlayerStep && !figure.isEmpty) {

                int direction = figure.isWhite ? -1 : 1;

                if (isMoveValid(i + direction, j - 1)) {

                    kingValidMoves[i + direction][j - 1] = false;
                }

                if (isMoveValid(i + direction, j + 1)) {

                    kingValidMoves[i + direction][j + 1] = false;
                }
            }

            if (figure.type == "Knight" && figure.isWhite == isWhitePlayerStep && !figure.isEmpty) {

                int knightMoves[8][2] = {
                    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
                };

                for (int counter = 0; counter < 8; ++counter) {
                    int newRow = i + knightMoves[counter][0];
                    int newColumn = j + knightMoves[counter][1];

                    if (isMoveValid(newRow, newColumn)) {

                        kingValidMoves[newRow][newColumn] = false;
                    }
                }
            }

            if (figure.type == "Bishop" && figure.isWhite == isWhitePlayerStep && !figure.isEmpty) {

                int directions[4][2] = {
                    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
                };

                for (int counter = 0; counter < 4; ++counter) {
                    int newRow = i + directions[counter][0];
                    int newColumn = j + directions[counter][1];

                    while (isMoveValid(newRow, newColumn) && chessBoard[newRow][newColumn].isEmpty) {

                        newRow += directions[counter][0];
                        newColumn += directions[counter][1];
                        kingValidMoves[newRow][newColumn] = false;
                    }

                    if (isMoveValid(newRow, newColumn) && !chessBoard[newRow][newColumn].isEmpty && chessBoard[newRow][newColumn].isWhite != figure.isWhite) {
                        kingValidMoves[newRow][newColumn] = false;
                    }
                }
            }

            if (figure.type == "Rook" && figure.isWhite == isWhitePlayerStep) {

                int directions[4][2] = {
                    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
                };

                for (int counter = 0; counter < 4; ++counter) {
                    int newRow = i + directions[counter][0];
                    int newColumn = j + directions[counter][1];

                    while (isMoveValid(newRow, newColumn) && chessBoard[newRow][newColumn].isEmpty) {

                        newRow += directions[counter][0];
                        newColumn += directions[counter][1];
                        kingValidMoves[newRow][newColumn] = false;
                    }

                    if (isMoveValid(newRow, newColumn) && !chessBoard[newRow][newColumn].isEmpty && chessBoard[newRow][newColumn].isWhite != figure.isWhite) {

                        kingValidMoves[newRow][newColumn] = false;
                    }
                }
            }

            if (figure.type == "Queen" && figure.isWhite == isWhitePlayerStep) {

                int directions[8][2] = {
                    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
                    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
                };

                for (int counter = 0; counter < 8; ++counter) {
                    int newRow = i + directions[counter][0];
                    int newColumn = j + directions[counter][1];

                    while (isMoveValid(newRow, newColumn) && chessBoard[newRow][newColumn].isEmpty) {

                        newRow += directions[counter][0];
                        newColumn += directions[counter][1];
                        kingValidMoves[newRow][newColumn] = false;
                    }

                    if (isMoveValid(newRow, newColumn) && !chessBoard[newRow][newColumn].isEmpty && chessBoard[newRow][newColumn].isWhite != figure.isWhite) {

                        kingValidMoves[newRow][newColumn] = false;
                    }
                }
            }
        }
    }

    if (kingValidMoves[kingRow][kingColumn] == false) {

        return true;
    }

    else return false;
}

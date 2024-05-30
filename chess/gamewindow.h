#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#define BOARD_SIZE 8

#include "stylehelper.h"
#include "figure.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QIcon>
#include <vector>



QT_BEGIN_NAMESPACE
namespace Ui {
class gameWindow;
}
QT_END_NAMESPACE

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    gameWindow(QWidget *parent = nullptr);
    ~gameWindow();

private slots:

    void on_startButton_clicked();

    void onGameAreaButtonClicked();

private:
    Ui::gameWindow *ui;

    QGridLayout *grid;

    bool isWhitePlayerStep;

    Figure chessBoard[BOARD_SIZE][BOARD_SIZE];

    QPushButton *currentFigure;

    void setDefaultPlaygroundColor();
    void lockButtons();
    void setButtonIconSize();
    void startGameFigurePosition();
    void setDefaultFigureIcons();
    void hilightCurrentPlayerFigures();
    void configurationGameAreaButtons();
    bool isCurrentStepFigureColor(int i, int j);
    void displayLegalMoves(int row, int column);
    bool isMoveValid(int row, int column);
    bool isCaptureValid(int row, int column);
    bool checkTheKing();
    bool kingValidMoves[BOARD_SIZE][BOARD_SIZE];
};

#endif // GAMEWINDOW_H

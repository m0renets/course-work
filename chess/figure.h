    #ifndef FIGURE_H
    #define FIGURE_H

    #include <QIcon>

    class Figure
    {
    public:
        bool isEmpty;
        bool isWhite;
        bool isFirstMove;

        QString type;

        Figure() : isEmpty(true), isWhite(false), isFirstMove(true),type("") {}
        Figure(bool white) : isEmpty(false), isWhite(white), isFirstMove(true) {}
        virtual ~Figure() = default;

        QString getIconPath() {

            if (type == "King") {
                return isWhite ? "D:/IASA/coursework/chess/img/King_white.png" : "D:/IASA/coursework/chess/img/King_black.png";
            }
            else if (type == "Queen") {
                return isWhite ? "D:/IASA/coursework/chess/img/Queen_white.png" : "D:/IASA/coursework/chess/img/Queen_black.png";
            }
            else if (type == "Rook") {
                return isWhite ? "D:/IASA/coursework/chess/img/Rook_white.png" : "D:/IASA/coursework/chess/img/Rook_black.png";
            }
            else if (type == "Bishop") {
                return isWhite ? "D:/IASA/coursework/chess/img/Bishop_white.png" : "D:/IASA/coursework/chess/img/Bishop_black.png";
            }
            else if (type == "Knight") {
                return isWhite ? "D:/IASA/coursework/chess/img/Knight_white.png" : "D:/IASA/coursework/chess/img/Knight_black.png";
            }
            else if (type == "Pawn") {
                return isWhite ? "D:/IASA/coursework/chess/img/Pawn_white.png" : "D:/IASA/coursework/chess/img/Pawn_black.png";
            }
            else return "";
        }
    };

    class King : public Figure
    {
    public:
        King(bool white) : Figure(white) {type = "King";}
    };

    class Queen : public Figure
    {
    public:
        Queen(bool white) : Figure(white) {type = "Queen";}
    };

    class Rook : public Figure
    {
    public:
        Rook(bool white) : Figure(white) {type = "Rook";}
    };

    class Bishop : public Figure
    {
    public:
        Bishop(bool white) : Figure(white) {type = "Bishop";}
    };

    class Knight : public Figure
    {
    public:
        Knight(bool white) : Figure(white) {type = "Knight";}
    };

    class Pawn : public Figure
    {
    public:
        Pawn(bool white) : Figure(white) {type = "Pawn";}
    };

    #endif // FIGURE_H

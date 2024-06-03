    #ifndef FIGURE_H
    #define FIGURE_H

    #include <QIcon>

    class Figure
    {
    public:
        bool isWhite;
        //bool isFirstMove;

        QString type;

        Figure() : isWhite(false), type("") {}
        Figure(bool white) : isWhite(white) {}
        virtual ~Figure() = default;

        virtual QString getIconPath() const = 0;
    };

    class King : public Figure
    {
    public:
        King(bool white) : Figure(white) {type = "King";}

        QString getIconPath() const override {
            return isWhite ? "D:/IASA/coursework/chess/img/King_white.png" : "D:/IASA/coursework/chess/img/King_black.png";
        }
    };

    class Queen : public Figure
    {
    public:
        Queen(bool white) : Figure(white) {type = "Queen";}

        QString getIconPath() const override {
            return isWhite ? "D:/IASA/coursework/chess/img/Queen_white.png" : "D:/IASA/coursework/chess/img/Queen_black.png";
        }
    };

    class Rook : public Figure
    {
    public:
        Rook(bool white) : Figure(white) {type = "Rook";}

        QString getIconPath() const override {
            return isWhite ? "D:/IASA/coursework/chess/img/Rook_white.png" : "D:/IASA/coursework/chess/img/Rook_black.png";
        }
    };

    class Bishop : public Figure
    {
    public:
        Bishop(bool white) : Figure(white) {type = "Bishop";}

        QString getIconPath() const override {
            return isWhite ? "D:/IASA/coursework/chess/img/Bishop_white.png" : "D:/IASA/coursework/chess/img/Bishop_black.png";
        }
    };

    class Knight : public Figure
    {
    public:
        Knight(bool white) : Figure(white) {type = "Knight";}

        QString getIconPath() const override {
            return isWhite ? "D:/IASA/coursework/chess/img/Knight_white.png" : "D:/IASA/coursework/chess/img/Knight_black.png";
        }
    };

    class Pawn : public Figure
    {
    public:

        bool isFirstMove;

        Pawn(bool white) : Figure(white), isFirstMove(true) { type = "Pawn"; }

        QString getIconPath() const override {
            return isWhite ? "D:/IASA/coursework/chess/img/Pawn_white.png" : "D:/IASA/coursework/chess/img/Pawn_black.png";
        }
    };

    #endif // FIGURE_H

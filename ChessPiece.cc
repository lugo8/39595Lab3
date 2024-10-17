#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"


using Student::ChessPiece;

ChessPiece(ChessBoard &board, Color color, int row, int column): board(board), color(color), row(row), col(column){}

//return the chess piece's color

Color getColor(){
    return color;
}


//return the chess piece's row

int getRow(){
    return row;
}

//return the chess piece's column

int getColumn(){
    return column;
}


void setPosition(int setRow, int setColumn){
    row = setRow;
    column = setColumn;
}

#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"


using Student::ChessPiece;
using Student::ChessBoard;

ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column): board(board), color(color), row(row), col(column){}

//return the chess piece's color

Color ChessPiece::getColor(){
    return color;
}


//return the chess piece's row

int ChessPiece::getRow(){
    return row;
}

//return the chess piece's column

int ChessPiece::getColumn(){
    return col;
}


void ChessPiece::setPosition(int setRow, int setColumn){
    row = setRow;
    col = setColumn;
}

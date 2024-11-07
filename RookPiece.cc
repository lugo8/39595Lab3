#include "RookPiece.hh"
#include "ChessBoard.hh"

using Student::RookPiece;
using Student::ChessBoard;

//Constructor
RookPiece::RookPiece(ChessBoard& _board, Color _color, int _row, int _col) : ChessPiece(_board, _color, _row, _col){}

//Get unicode version of chesspiece
const char *RookPiece::toString()
{
    if(!(getColor() == White))
    {
        return "♜"; //black rook
    }
    else
    {
        return "♖"; //white rook
    }
}

//Determine if a piece can be moved to a certain location
bool RookPiece::canMoveToLocation(int toRow, int toColumn)
{
    //Get state of the chess piece
    int row = getRow();
    int col = getColumn();
    Color colr = getColor();
    int nRow = getBoard().getNumRows();
    int nCol = getBoard().getNumCols();

        //bad parameters
    if (row >= nRow) {return false;}
    if (col >= nCol) {return false;}
    if (row < 0) {return false;}
    if (col < 0) {return false;}
    if (toRow >= nRow) {return false;}
    if (toColumn >= nCol) {return false;}
    if (toRow < 0) {return false;}
    if (toColumn < 0) {return false;}


    Student::ChessPiece* destPiece = getBoard().getPiece(toRow, toColumn);

    //If destination has same color as current piece, cannot move there
    if(destPiece != NULL && colr == destPiece->getColor())
    {
        return false;
    }

    //Cant move to current position
    if(row == toRow && col == toColumn)
    {
        return false;
    }

    //Get number of rows/cols on board


    int currRow = row;
    int currCol = col;
 
    //While in bounds and not equal to target
    while(!(currRow == toRow && currCol == toColumn) && currRow < nRow && currCol < nCol && currRow >= 0 && currCol >= 0)
    {
        //Go in the general direction of desired position
        if(toRow > row && toColumn == col) { currRow++; }
        if(toRow < row && toColumn == col) { currRow--; }
        if(toRow == row && toColumn > col) { currCol++;}
        if(toRow == row && toColumn < col) { currCol--;} 

        //If a piece was found in between current position and desired one
        if(!(currRow == toRow && currCol == toColumn) && getBoard().getPiece(currRow, currCol) != NULL)
        {
            return false;
        }
    }

    if(currRow == toRow && currCol == toColumn)
    {
        return true;
    }

    return false;
}

Type RookPiece::getType(){
    return Rook;
}
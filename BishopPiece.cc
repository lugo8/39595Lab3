#include "BishopPiece.hh"

using Student::BishopPiece;

//Constructor
BishopPiece(Student::ChessBoard _board, Color _color, int _row, int _col) : ChessPiece(_board, _color, _row, _column), board(_board){}

//Get unicode version of chesspiece
const char *toString()
{
    if(getColor() == Black)
    {
        return "U+1FA0D";
    }
    else
    {
        return "U+1FA07";
    }
}

//Determine if a piece can be moved to a certain location
bool canMoveToLocation(int toRow, int toColumn)
{
   //Get state of the chess piece
    int row = getRow();
    int col = getColumn();
    Color colr = getColor();

    Student::ChessPiece* destPiece = board->getPiece(toRow, toColumn);

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
    int nRow = board->getNumRows();
    int nCol = board->getNumCols();

    int currRow = row;
    int currCol = col;
 
    //While in bounds and not equal to target
    while(currRow != toRow && currCol != toColumn && currRow < nRow && currCol < nCol && currRow >= 0 && currCol >= 0)
    {
        //Go in the general direction of desired position
        if(toRow > row && toColumn > col) { currRow++; currCol++;}
        if(toRow > row && toColumn < col) { currRow++; currCol--;}
        if(toRow < row && toColumn > col) { currRow--; currCol++;}
        if(toRow < row && toColumn < col) { currRow--; currCol--;} 

        //If a piece was found in between current position and desired one
        if(currRow != toRow && currCol != toColumn && board->getPiece(currRow, currCol) != NULL)
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
#include "PawnPiece.hh"

using Student::PawnPiece;

//Constructor
PawnPiece(ChessBoard _board, Color _color, int _row, int _col) : ChessPiece(_board, _color, _row, _column), board(_board){}

//Get unicode version of chesspiece
const char *toString()
{
    if(getColor() == Black)
    {
        return "U+1FA0F";
    }
    else
    {
        return "U+1FA09";
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

    //Get number of rows on board
    int nRow = board->getNumRows();

    //Normal case: one up or down based on color
    //--------------------------------------------------------------------------------------------------------------------------

    int mvLinear[2];
    if(colr == Black)
    {
        posLinear = {row + 1, col};
    }
    if(colr == White)
    {
        posLinear = {row - 1, col};
    }

    //If desired place to move is one in front of pawn, send true
    if(posLinear[0] == toRow && posLinear[1] == toColumn)
    {
        return true;
    }

    //Take care of edge case where a pawn in starting position can move forward 2 spaces
    //--------------------------------------------------------------------------------------------------------------------------

    //A black piece on row 1 can move 1 or 2 steps along the same column.
    if(colr == Black && row == 1)
    {
        posLinear[0]++;
    }
    //A white piece on row n-2 can move 1 or 2 steps along the same column
    if(colr == White && row == nRow - 2)
    {
        posLinear[0]--;
    }
    //If desired place to move is one in front of pawn, send true
    if(posLinear[0] == toRow && posLinear[1] == toColumn)
    {
        return true;
    }

    //Take care of edge case where pawn can move diagonally if there is a piece there
    //--------------------------------------------------------------------------------------------------------------------------
    posLinear[1]++;
    if(posLinear[0] == toRow && posLinear[1] == toColumn)
    {
        return true;
    }
    posLinear[1] -= 2;
    if(posLinear[0] == toRow && posLinear[1] == toColumn)
    {
        return true;
    }

    //If gotten to here, cannot move there
    return false;


}

Type getType(){
    return Pawn;
}
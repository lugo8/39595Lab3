#include "PawnPiece.hh"
#include "ChessBoard.hh"


using Student::PawnPiece;
using Student::ChessBoard;

//Constructor
PawnPiece::PawnPiece(ChessBoard& _board, Color _color, int _row, int _col) : ChessPiece(_board, _color, _row, _col){}

//Get unicode version of chesspiece
const char *PawnPiece::toString()
{
    if(!(getColor() == White))
    {
        return "♟"; //black pawn
    }
    else
    {
        return "♙"; //white Pawn
    }
}

//Determine if a piece can be moved to a certain location
bool PawnPiece::canMoveToLocation(int toRow, int toColumn)
{
    //Get state of the chess piece
    int rowP = getRow();
    int colP = getColumn();
    Color colrP = getColor();

    Student::ChessPiece* destPiece = getBoard().getPiece(toRow, toColumn);

    //If destination has same color as current piece, cannot move there
    if(destPiece != NULL && colrP == destPiece->getColor())
    {
        return false;
    }

    //Get number of rows on board
    int nRow = getBoard().getNumRows();

    //Normal case: one up or down based on color
    //--------------------------------------------------------------------------------------------------------------------------

    int posLinear[2]; //assuming this should be posLinear, not myLinear
    if(colrP == Black)
    {
        posLinear[0] = rowP + 1;
        posLinear[1] = colP;
    }
    if(colrP == White)
    {
        posLinear[0] = rowP - 1;
        posLinear[1] = colP;
    }

    //If desired place to move is one in front of pawn, send true unless there is a opponent piece there
    if(posLinear[0] == toRow && posLinear[1] == toColumn)
    {
        if(destPiece != NULL)
        {
            return false;
        }
        else{
            return true;
        }
    }

    //Take care of edge case where a pawn in starting position can move forward 2 spaces
    //--------------------------------------------------------------------------------------------------------------------------
    Student::ChessPiece* blockingPiece = NULL;
    if(posLinear[0] >= 0 && posLinear[0] < nRow)
    {
        blockingPiece = getBoard().getPiece(posLinear[0], posLinear[1]);
    }
    else
    {
        return false;
    }

    bool blocked = false;
    bool jumpTwo = false;
    //THE PAWN CAN BE BLOCKED AND CANT GO 2 ALWAYS
    if(blockingPiece != NULL)
    {
        blocked = true;
    }
        
    if(colrP == Black)
    {
        if(rowP == 1)
        {
            jumpTwo = true;
        }
        posLinear[0]++;
    }
    if(colrP == White)
    {
        if(rowP == nRow - 2)
        {
            jumpTwo = true;
        }
        posLinear[0]--;
    }

    //If desired place to move is two in front of pawn, send true, unless there is a pice there or it is blocked
    if(posLinear[0] == toRow && posLinear[1] == toColumn && jumpTwo)
    {
        if(blocked)
        {
            return false;
        }

        if(destPiece != NULL)
        {
            return false;
        }

        else
        {
            return true;
        }

    }

    //Take care of edge case where pawn can move diagonally if there is a piece there
    //--------------------------------------------------------------------------------------------------------------------------
    if(colrP == Black)
    {
        posLinear[0]--;
    }
    if(colrP == White)
    {
        posLinear[0]++;
    }
    posLinear[1]++;

    int nCols = getBoard().getNumCols();

    //Check bounds
    if(!((posLinear[0] < 0 || posLinear[0] >= nRow) || (posLinear[1] < 0 || posLinear[1] >= nCols)))
    {
        if(posLinear[0] == toRow && posLinear[1] == toColumn && destPiece != NULL)
        {
            return true;
        }
    }

    
    posLinear[1] -= 2;

    if(!((posLinear[0] < 0 || posLinear[0] >= nRow) || (posLinear[1] < 0 || posLinear[1] >= nCols)))
    {
        if(posLinear[0] == toRow && posLinear[1] == toColumn && destPiece != NULL)
        {
            return true;
        }
    }

    //If gotten to here, cannot move there
    return false;


}

Type PawnPiece::getType(){
    return Pawn;
}
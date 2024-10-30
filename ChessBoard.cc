#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
//new
#include "Chess.h"

using Student::ChessBoard;

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}

ChessBoard::ChessBoard(int numRow, int numCol)
{
    numRows = numRow;
    numCols = numCol;

    //Make vector into desired row by col matrix
    board.resize(numRow);
    for(int i = 0; i < numRow; i++)
    {
        board[i].resize(numCol);
    }

    //Initialize each piece on the board to NULL
    for(int row = 0; row < numRow; row++)
    {
        for(int col = 0; col < numCol; col++)
        {
            board[row][col] = NULL;
        }
    }
}

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn)
{
    //Remove peice in startRow, startCol if not NULL
    if(board[startRow][startColumn] != NULL)
    {
        delete board[startRow][startColumn];
        board[startRow][startColumn] = NULL;
    }

    ChessPiece* piece;

    if(ty == Pawn)
    {
        //TODO: make this work with pawn's constructor
        piece = new PawnPiece(*this, col, startRow, startColumn);
    }

    if(ty == Rook)
    {
        //TODO: make this work with rook's constructor
        piece = new RookPiece(*this, col, startRow, startColumn);
    }

    if(ty == Bishop)
    {
        //TODO: make this work with bishop's constructor
        piece = new BishopPiece(*this, col, startRow, startColumn);
    }

    /*if(ty == King)
    {
        //TODO: make this work with king's constructor
        //piece = new KingPiece();
    }*/ //make king not exist for part 1?

    board[startRow][startColumn] = piece;

}

bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn)
{
    //Get a copy of piece's attributes
    ChessPiece* ogPiece = getPiece(fromRow, fromColumn);
    Color col = ogPiece->getColor();
    Type ty = ogPiece->getType();

    if(!isValidMove(fromRow, fromColumn, toRow, toColumn) || col != getTurn())
    {
        return false;
    }

   

    //Delete old piece at original position
    delete board[fromRow][fromColumn];
    board[fromRow][fromColumn] = NULL;

    //Create piece in new positoin
    createChessPiece(col, ty, toRow, toColumn);

    //TODO: see if i need to change turn after i move?

    return true;
    
}
bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
{
    ChessPiece *movingPiece = board.at(fromRow).at(fromColumn);
    if(movingPiece == nullptr){
        return false;
    }
    return movingPiece->canMoveToLocation(toRow,toColumn); 
}

bool ChessBoard::isPieceUnderThreat(int row, int column)
{
    if(ChessBoard::getPiece(row, column) == NULL)
    {
        return false;
    }

    int numRows = getNumRows();
    int numCols = getNumCols();

    for(int r = 0; r < numRows; r++)
    {
        for(int c = 0; c < numCols; c++)
        {
            if(isValidMove(r, c, row, column))
            {
                return true;
            }
        }
    }

    return false;
    
}



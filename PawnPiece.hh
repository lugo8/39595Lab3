#ifndef __PAWNPIECE_H__
#define __PAWNPIECE_H__

#include "ChessPiece.hh"
#include "ChessBoard.hh"

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class PawnPiece : public ChessPiece
    {
    private:
        //ChessBoard* board;
        // Color color;
        // int col; //column
        // int row; //row
    public:
    //change to reference
        PawnPiece(ChessBoard& _board, Color _color, int _row, int _col);
        bool canPhysicallyMove(int toRow, int toCol);
        bool canMoveToLocation(int toRow, int toColumn);
        const char *toString();
        Type getType();

    };
}

#endif

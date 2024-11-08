#ifndef _ROOKPIECE_H__
#define _ROOKPIECE_H__

#include "ChessPiece.hh"
#include "ChessBoard.hh"

/**
 * Student implementation of a Rook chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class RookPiece : public ChessPiece
    {
    private:
        //Student::ChessBoard* board;
    public:
        RookPiece(ChessBoard& _board, Color _color, int _row, int _col);
        bool canPhysicallyMove(int toRow, int toCol);
        bool canMoveToLocation(int toRow, int toColumn);
        const char *toString();
        Type getType();
    };
}

#endif

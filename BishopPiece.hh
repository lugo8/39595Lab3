#ifndef __BISHOPPIECE_H__
#define __BISHOPPIECE_H__

#include "ChessPiece.hh"
#include "ChessBoard.hh"

/**
 * Student implementation of a Bishop chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class BishopPiece : public ChessPiece
    {
    private:
        //Student::ChessBoard* board;
    public:
        BishopPiece(ChessBoard& _board, Color _color, int _row, int _col);
        bool canMoveToLocation(int toRow, int toColumn);
        const char *toString();
        Type getType();
    };
}

#endif

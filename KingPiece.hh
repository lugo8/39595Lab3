#ifndef __KINGPIECE_H__
#define __KINGPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a King chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class KingPiece : public ChessPiece
    {
    private:
        
    public:
        KingPiece(ChessBoard& _board, Color _color, int _row, int _col);
        bool canPhysicallyMove(int toRow, int toCol);
        bool canMoveToLocation(int toRow, int toColumn);
        const char *toString();
        Type getType();
    };
}

#endif

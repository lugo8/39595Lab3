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
        //return true; //before test

        //if it would be a cussessful move but the king is now in check, the move can not be done
            ChessBoard& board = getBoard();
            Color color1 = getColor();
            //remove rook where it currently is
            board.deleteChessPiece(row, col);
            //create rook where it can so far and wants to go

            int oppKingRow = -1;
            int oppKingCol = -1; //if these are -1 it means no opp king
            //need to find opp king and replace it with a dummy pawn
            for(int ro = 0; ro < nRow; ro++)
            {
                for(int co = 0; co < nCol; co++)
                {
                    Student::ChessPiece* kingFinderOpp = board.getPiece(ro, co);
                    if(kingFinderOpp != NULL){
                        if(kingFinderOpp->getType() == King){
                            if(kingFinderOpp->getColor() != color1){ //found the opp, take its position
                                oppKingRow = kingFinderOpp->getRow(); 
                                oppKingCol = kingFinderOpp->getColumn(); 
                            }
                        }
                    }
                }
            }
            if(oppKingCol >=0 && oppKingRow >= 0){
                board.deleteChessPiece(oppKingRow, oppKingCol);// get rid of the opp king
                if(color1 == White){
                    board.createChessPiece(Black, Pawn, oppKingRow, oppKingCol);
                }else{
                    board.createChessPiece(White, Pawn, oppKingRow, oppKingCol);
                }
            }

            bool peiceReplaced = false;
            Type repType = Pawn;
            Color repColor = White;
            //check if ur replacing a peice
            if (board.getPiece(toRow, toColumn) != NULL){
                peiceReplaced = true;
                repType = board.getPiece(toRow, toColumn)->getType();
                repColor = board.getPiece(toRow, toColumn)->getColor();
                board.deleteChessPiece(toRow, toColumn);
            }else{
                peiceReplaced = false;
            }

            board.createChessPiece(color1, Rook, toRow, toColumn);

            //now check if self colored king is under threat
            for(int r = 0; r < nRow; r++)
            {
                for(int c = 0; c < nCol; c++)
                {
                    Student::ChessPiece* kingFinder = board.getPiece(r, c);
                    if(kingFinder != NULL){
                        if(kingFinder->getType() == King){
                            if(kingFinder->getColor() == color1){
                                if(board.isPieceUnderThreat(r,c)){
                                    //reset board?
                                    //remove rook where it wanted to be
                                    board.deleteChessPiece(toRow, toColumn);
                                    //create rook where it was before move attempt
                                    if(peiceReplaced){
                                        board.createChessPiece(repColor, repType, toRow, toColumn);
                                    }
                                    //reinstate the opp king if dummied
                                    if(oppKingCol >=0 && oppKingRow >= 0){
                                        board.deleteChessPiece(oppKingRow, oppKingCol);// get rid of the opp king
                                        if(color1 == White){
                                            board.createChessPiece(Black, King, oppKingRow, oppKingCol);
                                        }else{
                                            board.createChessPiece(White, King, oppKingRow, oppKingCol);
                                        }
                                    }
                                    board.createChessPiece(color1, Rook, row, col);
                                    return false;
                                }
                                
                            }
                        }
                    }
                }
            }
            //if iterated thru rows and cols and no threatened king, can move
            //remove rook where it wanted to be
            board.deleteChessPiece(toRow, toColumn);
            if(peiceReplaced){
                board.createChessPiece(repColor, repType, toRow, toColumn);
            }
            //reinstate the opp king if dummied
            if(oppKingCol >=0 && oppKingRow >= 0){
                board.deleteChessPiece(oppKingRow, oppKingCol);// get rid of the opp king
                if(color1 == White){
                    board.createChessPiece(Black, King, oppKingRow, oppKingCol);
                }else{
                    board.createChessPiece(White, King, oppKingRow, oppKingCol);
                }
            }
            //create rook where it was before move attempt
            board.createChessPiece(color1, Rook, row, col);
            return true;
    }
    

    return false;
}

Type RookPiece::getType(){
    return Rook;
}
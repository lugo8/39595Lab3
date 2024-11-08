#include "BishopPiece.hh"
#include "ChessBoard.hh"

using Student::BishopPiece;
using Student::ChessBoard;

//Constructor
BishopPiece::BishopPiece(ChessBoard& _board, Color _color, int _row, int _col) : ChessPiece(_board, _color, _row, _col){}

//Get unicode version of chesspiece
const char *BishopPiece::toString()
{
    if(!(getColor() == White))
    {
        return "♝"; //black bishop
    }
    else
    {
        return "♗"; //white bishop
    }
}

bool BishopPiece::canPhysicallyMove(int toRow, int toColumn)
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
    while(currRow != toRow && currCol != toColumn && currRow < nRow && currCol < nCol && currRow >= 0 && currCol >= 0)
    {
        //Go in the general direction of desired position
        if(toRow > row && toColumn > col) { currRow++; currCol++;}
        if(toRow > row && toColumn < col) { currRow++; currCol--;}
        if(toRow < row && toColumn > col) { currRow--; currCol++;}
        if(toRow < row && toColumn < col) { currRow--; currCol--;} 

        //If a piece was found in between current position and desired one
        if(currRow != toRow && currCol != toColumn && getBoard().getPiece(currRow, currCol) != NULL)
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

//Determine if a piece can be moved to a certain location
bool BishopPiece::canMoveToLocation(int toRow, int toColumn)
{
   //Get state of the chess piece
    int rowB = getRow();
    int colB = getColumn();
    Color colr = getColor();


    int nRow = getBoard().getNumRows();
    int nCol = getBoard().getNumCols();

        //bad parameters
    if (rowB >= nRow) {return false;}
    if (colB >= nCol) {return false;}
    if (rowB < 0) {return false;}
    if (colB < 0) {return false;}
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
    if(rowB == toRow && colB == toColumn)
    {
        return false;
    }

    //Get number of rows/cols on board


    int currRow = rowB;
    int currCol = colB;
 
    //While in bounds and not equal to target
    while(currRow != toRow && currCol != toColumn && currRow < nRow && currCol < nCol && currRow >= 0 && currCol >= 0)
    {
        //Go in the general direction of desired position
        if(toRow > rowB && toColumn > colB) { currRow++; currCol++;}
        if(toRow > rowB && toColumn < colB) { currRow++; currCol--;}
        if(toRow < rowB && toColumn > colB) { currRow--; currCol++;}
        if(toRow < rowB && toColumn < colB) { currRow--; currCol--;} 

        //If a piece was found in between current position and desired one
        if(currRow != toRow && currCol != toColumn && getBoard().getPiece(currRow, currCol) != NULL)
        {
            return false;
        }
    }

    if(currRow == toRow && currCol == toColumn)
    {
               //return true; //before test
        //simulate move and check for the bishops's king under threat
        ChessBoard& board = getBoard();
        Student::ChessPiece* target = board.getPiece(toRow, toColumn);
        if(target != NULL)
        {//there is a piece where the piece wants to move
            Color color0 = target->getColor();
            Type ty = target->getType();
            //row and col of target are just toRow and toCol

            board.deleteChessPiece(rowB,colB); //current bishop is gone
            board.deleteChessPiece(toRow,toColumn); //the piece at tarhget is gone
            board.createChessPiece(colr,Bishop,toRow,toColumn); //create the bishop where it wants to move
            //board is now simulating the desired move
            //check if my king is threatened in this board

            //need to find my king

            int kingRow = -1;
            int kingCol = -1; //if these remain -1 it means no king of my color

            for(int ro = 0; ro < nRow; ro++)
            {
                for(int co = 0; co < nCol; co++)
                {
                    Student::ChessPiece* kingFinder = board.getPiece(ro, co);
                    if(kingFinder != NULL){
                        if(kingFinder->getType() == King){
                            if(kingFinder->getColor() == colr){ //found my king, get position
                                kingRow = kingFinder->getRow(); 
                                kingCol = kingFinder->getColumn(); 
                            }
                        }
                    }
                }
            }
            //found my king, or king doesnt exist
            //if king dont exist, valid move
            if(kingCol == -1 || kingRow == -1){
                board.deleteChessPiece(toRow, toColumn); //remove the simulated bishop location
                board.createChessPiece(colr, Bishop,rowB,colB); //create the bishop where it was before check
                board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated bishop location
                    board.createChessPiece(colr, Bishop,rowB,colB); //create the bishop where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated bishop location
                    board.createChessPiece(colr, Bishop,rowB,colB); //create the bishop where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return true;
                }
            }

        }else{
            //just move piece to target and check for king
            board.deleteChessPiece(rowB,colB); //current bishop is gone
            board.createChessPiece(colr,Bishop,toRow,toColumn); //create the bishop where it wants to move
            //board is now simulating the desired move
            //check if my king is threatened in this board

            //need to find my king

            int kingRow = -1;
            int kingCol = -1; //if these remain -1 it means no king of my color

            for(int ro = 0; ro < nRow; ro++)
            {
                for(int co = 0; co < nCol; co++)
                {
                    Student::ChessPiece* kingFinder = board.getPiece(ro, co);
                    if(kingFinder != NULL){
                        if(kingFinder->getType() == King){
                            if(kingFinder->getColor() == colr){ //found my king, get position
                                kingRow = kingFinder->getRow(); 
                                kingCol = kingFinder->getColumn(); 
                            }
                        }
                    }
                }
            }
            //found my king, or king doesnt exist
            //if king dont exist, valid move
            if(kingCol == -1 || kingRow == -1){
                //reset sim board
                board.deleteChessPiece(toRow, toColumn); //remove the simulated bishop location
                board.createChessPiece(colr, Bishop,rowB,colB); //create the bishop where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated bishop location
                    board.createChessPiece(colr, Bishop,rowB,colB); //create the bishop where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated bishop location
                    board.createChessPiece(colr, Bishop,rowB,colB); //create the bishop where it was before check
                    return true;
                }
            }
        }


    }

    return false;


        



    
}

Type BishopPiece::getType(){
    return Bishop;
}
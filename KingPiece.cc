#include "KingPiece.hh"
#include "ChessBoard.hh"

using Student::KingPiece;
using Student::ChessBoard;

//Constructor
KingPiece::KingPiece(ChessBoard& _board, Color _color, int _row, int _col) : ChessPiece(_board, _color, _row, _col){}

//Get unicode version of chesspiece
const char *KingPiece::toString()
{
    if(!(getColor() == Black))
    {
        return "♔"; //white king
    }
    else
    {
        return "♚"; //black king
    }
}

bool KingPiece::canPhysicallyMove(int toRow, int toColumn)
{
    //TODO: NEED TO ADD SUPPORT FOR DIAGONAL MOVEMENT


    //Get state of the chess piece
    int row = getRow();
    int col = getColumn();
    Color colr = getColor();



    //Cant move to current position
    if(row == toRow && col == toColumn)
    {
        return false;
    }
    // outside of 1 tile range instant fail
    if(((row - toRow) > 1)||((row - toRow) < -1)) {return false;}
    if(((col - toColumn) > 1)||((col - toColumn) < -1)) {return false;}


    //Get number of rows/cols on board
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
    


    int currRow = row;
    int currCol = col;

    Student::ChessPiece* destPiece = getBoard().getPiece(toRow, toColumn);

    //If destination has same color as current piece, cannot move there
    if(destPiece != NULL && colr == destPiece->getColor())
    {
        return false;
    }

    //Go in the general direction of desired position
    //can all be ran to get diagonals
    if(toRow > row) { currRow++; }
    if(toRow < row) { currRow--; }
    if(toColumn > col) { currCol++;}
    if(toColumn < col) { currCol--;} 

//can i just delete the king? in its own function? then remake it?

    //If right position, check if under threat //NEED TO IMAGINE KING NO LONGER EXISTS AT STARTING POINT
    
    //can i copy the board without the king and check?
    if((currRow == toRow && currCol == toColumn) && currRow < nRow && currCol < nCol && currRow >= 0 && currCol >= 0)
    {
        return true;
    }

    return false;

}



//Determine if a piece can be moved to a certain location
bool KingPiece::canMoveToLocation(int toRow, int toColumn)
{
    //TODO: NEED TO ADD SUPPORT FOR DIAGONAL MOVEMENT


    //Get state of the chess piece
    int rowK = getRow();
    int colK = getColumn();
    Color colr = getColor();



    //Cant move to current position
    if(rowK == toRow && colK == toColumn)
    {
        return false;
    }
    // outside of 1 tile range instant fail
    if(((rowK - toRow) > 1)||((rowK - toRow) < -1)) {return false;}
    if(((colK - toColumn) > 1)||((colK - toColumn) < -1)) {return false;}


    //Get number of rows/cols on board
    int nRow = getBoard().getNumRows();
    int nCol = getBoard().getNumCols();

    //bad parameters
    if (rowK >= nRow) {return false;}
    if (colK >= nCol) {return false;}
    if (rowK < 0) {return false;}
    if (colK < 0) {return false;}
    if (toRow >= nRow) {return false;}
    if (toColumn >= nCol) {return false;}
    if (toRow < 0) {return false;}
    if (toColumn < 0) {return false;}
    


    int currRow = rowK;
    int currCol = colK;

    Student::ChessPiece* destPiece = getBoard().getPiece(toRow, toColumn);

    //If destination has same color as current piece, cannot move there
    if(destPiece != NULL && colr == destPiece->getColor())
    {
        return false;
    }

    //Go in the general direction of desired position
    //can all be ran to get diagonals
    if(toRow > rowK) { currRow++; }
    if(toRow < rowK) { currRow--; }
    if(toColumn > colK) { currCol++;}
    if(toColumn < colK) { currCol--;} 

//can i just delete the king? in its own function? then remake it?

    //If right position, check if under threat //NEED TO IMAGINE KING NO LONGER EXISTS AT STARTING POINT
    
    //can i copy the board without the king and check?
    if((currRow == toRow && currCol == toColumn) && currRow < nRow && currCol < nCol && currRow >= 0 && currCol >= 0)
    {
        ChessBoard& board = getBoard();

        /*for(int i = 0; i<3; i++){ //is the desired new location next to a king? if so, cant move,,,,,, unless you take the opp king...
            for(int j = 0; j < 3; j++){
                //printf("working...\n");
                //printf("i = %d, j = %d\n", i, j);
                int relativeRow = (toRow-1)+i;
                int relativeCol = (toColumn-1)+j;
               // printf("relativeRow = %d, relativeCol = %d\n", relativeRow, relativeCol);
                if(relativeCol<nCol && relativeCol >= 0 && relativeRow < nRow && relativeRow >= 0){
                    //printf("inbounds...\n");
                    Student::ChessPiece* kingFinder = board.getPiece(relativeRow, relativeCol);
                    if(kingFinder != NULL){
                        if(kingFinder->getType() == King){
                            if(kingFinder->getColor() != colr){
                                //printf("found opp king nearby...\n");
                                //printf("i = %d, j = %d\n", i, j);
                                //if(!(relativeRow == toRow && relativeCol == toColumn)){ //if the king is where we want to move to take , allow it
                                    return false;
                                //}
                            }
                        }
                    }
                }
            }
        }*/
       
       //just check if king is threatened

        
        Student::ChessPiece* target = board.getPiece(toRow, toColumn);

        //bool threat;

        //If a piece is in desired spot, change it to opposite color to see if king would be under thread
        if(target != NULL)
        {
            Color color0 = target->getColor();
            Type ty = target->getType();
            //row and col of targe are just toRow and toCol


            board.deleteChessPiece(rowK,colK); //current king is gone
            board.deleteChessPiece(toRow, toColumn); //target piece is gone
            board.createChessPiece(colr, King,toRow,toColumn); //create the King where it wants to move

            //board is now simulating the desired move
            //check if king is threatened in this board

            if(board.isPieceUnderThreat(toRow,toColumn)){//if the king is now under threat in the new location, return to original board and ret false
                board.deleteChessPiece(toRow, toColumn); //remove the simulated king location
                board.createChessPiece(colr, King,rowK,colK); //create the King where it was before check
                board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                return false;

            }else{
                board.deleteChessPiece(toRow, toColumn); //remove the simulated king location
                board.createChessPiece(colr, King,rowK,colK); //create the King where it was before check
                board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                return true;
            } 

        }

        //create chesspiece at target point and see if it is under threat
        else
        {   
            //delete kirrent king location
            board.deleteChessPiece(rowK,colK); //current king is gone
            board.createChessPiece(colr, King,toRow,toColumn); //create the King where it wants to move

            if(board.isPieceUnderThreat(toRow,toColumn)){//if the king is now under threat in the new location, return to original board and ret false
                board.deleteChessPiece(toRow, toColumn); //remove the simulated king location
                board.createChessPiece(colr, King,rowK,colK); //create the King where it was before check
                return false;

            }else{
                board.deleteChessPiece(toRow, toColumn); //remove the simulated king location
                board.createChessPiece(colr, King,rowK,colK); //create the King where it was before check
                return true;
            } 

        }

        //return !threat;
        
    }


    return false;
}

Type KingPiece::getType(){
    return King;
}
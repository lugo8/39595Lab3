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

//Determine if a piece can be moved to a certain location
bool KingPiece::canMoveToLocation(int toRow, int toColumn)
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
        ChessBoard& board = getBoard();

        // for(int i = 0; i<3; i++){ //is the desired new location next to a king? if so, cant move
        //     for(int j = 0; j < 3; j++){
        //         //printf("working...\n");
        //         //printf("i = %d, j = %d\n", i, j);
        //         int relativeRow = (toRow-1)+i;
        //         int relativeCol = (toColumn-1)+j;
        //        // printf("relativeRow = %d, relativeCol = %d\n", relativeRow, relativeCol);
        //         if(relativeCol<nCol && relativeCol >= 0 && relativeRow < nRow && relativeRow >= 0){
        //             //printf("inbounds...\n");
        //             Student::ChessPiece* kingFinder = board.getPiece(relativeRow, relativeCol);
        //             if(kingFinder != NULL){
        //                 if(kingFinder->getType() == King){
        //                     if(kingFinder->getColor() != colr){
        //                         //printf("found opp king nearby...\n");
        //                         //printf("i = %d, j = %d\n", i, j);
        //                         return false;
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }

        
        Student::ChessPiece* target = board.getPiece(toRow, toColumn);

        bool threat;

        //If a piece is in desired spot, change it to opposite color to see if king would be under thread
        if(target != NULL)
        {
            Color color0 = target->getColor();
            Type ty = target->getType();

            Color oppositeColor;
            if(color0 == White)
            {
                oppositeColor = Black;
            }
            else if(color0 == Black)
            {
                oppositeColor = White;
            }

                                //remove current king

            //board.deleteChessPiece(row, col);
            board.nullChessPiece(row, col);
            

            board.createChessPiece(oppositeColor, ty, toRow, toColumn);

            threat = board.isPieceUnderThreat(toRow, toColumn);

            board.createChessPiece(color0, ty, toRow, toColumn);

                        //place the king back
            //board.createChessPiece(colr, King, row, col); 
            board.placePiece(row, col, this);
        }

        //create chesspiece at target point and see if it is under threat
        else
        {   




            //Create piece
            //why create another board in this if block???
            // /ChessBoard& board = getBoard();
            Color color1 = getColor();            
            //remove current king

            //board.deleteChessPiece(row, col);
            board.nullChessPiece(row, col);

            board.createChessPiece(color1, King, toRow, toColumn);

            //Determine if its under thread
            threat = board.isPieceUnderThreat(toRow, toColumn);

            //Delete piece
            board.deleteChessPiece(toRow, toColumn);

            //place the king back
            //board.createChessPiece(colr, King, row, col); 
            board.placePiece(row, col, this);
            
        }

        return !threat;
        
    }


    return false;
}

Type KingPiece::getType(){
    return King;
}
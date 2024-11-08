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

bool PawnPiece::canPhysicallyMove(int toRow, int toColumn)
{
     //Get state of the chess piece
    int rowP = getRow();
    int colP = getColumn();
    Color colrP = getColor();

    int nRow = getBoard().getNumRows();
    int nCol = getBoard().getNumCols();

        //bad parameters
    if (rowP >= nRow) {return false;}
    if (colP >= nCol) {return false;}
    if (rowP < 0) {return false;}
    if (colP < 0) {return false;}
    if (toRow >= nRow) {return false;}
    if (toColumn >= nCol) {return false;}
    if (toRow < 0) {return false;}
    if (toColumn < 0) {return false;}

    Student::ChessPiece* destPiece = getBoard().getPiece(toRow, toColumn);

    //If destination has same color as current piece, cannot move there
    if(destPiece != NULL && colrP == destPiece->getColor())
    {
        return false;
    }

    //Get number of rows on board
    

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
            
            return true; //real true
            //block over...
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
             
            return true; //real true
            //block over...
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
             
            return true; //real true
            //block over...
        }
    }

    
    posLinear[1] -= 2;

    if(!((posLinear[0] < 0 || posLinear[0] >= nRow) || (posLinear[1] < 0 || posLinear[1] >= nCols)))
    {
        if(posLinear[0] == toRow && posLinear[1] == toColumn && destPiece != NULL)
        {
             
            return true; //real true
            //block over...
        }
    }

    //If gotten to here, cannot move there
    return false;
}

//Determine if a piece can be moved to a certain location
bool PawnPiece::canMoveToLocation(int toRow, int toColumn)
{
    //Get state of the chess piece
    int rowP = getRow();
    int colP = getColumn();
    Color colrP = getColor();

    int nRow = getBoard().getNumRows();
    int nCol = getBoard().getNumCols();

        //bad parameters
    if (rowP >= nRow) {return false;}
    if (colP >= nCol) {return false;}
    if (rowP < 0) {return false;}
    if (colP < 0) {return false;}
    if (toRow >= nRow) {return false;}
    if (toColumn >= nCol) {return false;}
    if (toRow < 0) {return false;}
    if (toColumn < 0) {return false;}

    Student::ChessPiece* destPiece = getBoard().getPiece(toRow, toColumn);

    //If destination has same color as current piece, cannot move there
    if(destPiece != NULL && colrP == destPiece->getColor())
    {
        return false;
    }

    //Get number of rows on board
    

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
            //replace all return true with this block of code...
             ChessBoard& board = getBoard();
            Color color1 = getColor();
            //remove piece where it currently is
            board.deleteChessPiece(rowP, colP);

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
            //create piece where it can so far and wants to go
            board.createChessPiece(color1, Pawn, toRow, toColumn);

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
                                    //remove piece where it wanted to be
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
                                    //create piece where it was before move attempt
                                    board.createChessPiece(color1, Pawn, rowP, colP);
                                    return false;
                                }
                                
                            }
                        }
                    }
                }
            }
            //if iterated thru rows and cols and no threatened king, can move
            //remove piece where it wanted to be
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
            //create piece where it was before move attempt
            board.createChessPiece(color1, Pawn, rowP, colP);
            return true; //real true
            //block over...
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
                        //replace all return true with this block of code...
             ChessBoard& board = getBoard();
            Color color1 = getColor();
            //remove piece where it currently is
            board.deleteChessPiece(rowP, colP);

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

            //create piece where it can so far and wants to go
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
            board.createChessPiece(color1, Pawn, toRow, toColumn);

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
                                    //remove piece where it wanted to be
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
                                    //create piece where it was before move attempt
                                    board.createChessPiece(color1, Pawn, rowP, colP);
                                    return false;
                                }
                                
                            }
                        }
                    }
                }
            }
            //if iterated thru rows and cols and no threatened king, can move
            //remove piece where it wanted to be
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
            //create piece where it was before move attempt
            board.createChessPiece(color1, Pawn, rowP, colP);
            return true; //real true
            //block over...
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
                        //replace all return true with this block of code...
             ChessBoard& board = getBoard();
            Color color1 = getColor();
            //remove piece where it currently is
            board.deleteChessPiece(rowP, colP);

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
            //create piece where it can so far and wants to go
            board.createChessPiece(color1, Pawn, toRow, toColumn);

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
                                    //remove piece where it wanted to be
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
                                    //create piece where it was before move attempt
                                    board.createChessPiece(color1, Pawn, rowP, colP);
                                    return false;
                                }
                                
                            }
                        }
                    }
                }
            }
            //if iterated thru rows and cols and no threatened king, can move
            //remove piece where it wanted to be
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
            //create piece where it was before move attempt
            board.createChessPiece(color1, Pawn, rowP, colP);
            return true; //real true
            //block over...
        }
    }

    
    posLinear[1] -= 2;

    if(!((posLinear[0] < 0 || posLinear[0] >= nRow) || (posLinear[1] < 0 || posLinear[1] >= nCols)))
    {
        if(posLinear[0] == toRow && posLinear[1] == toColumn && destPiece != NULL)
        {
                        //replace all return true with this block of code...
             ChessBoard& board = getBoard();
            Color color1 = getColor();
            //remove piece where it currently is
            board.deleteChessPiece(rowP, colP);


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
            //create piece where it can so far and wants to go
            board.createChessPiece(color1, Pawn, toRow, toColumn);

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
                                    //remove piece where it wanted to be
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
                                    //create piece where it was before move attempt
                                    board.createChessPiece(color1, Pawn, rowP, colP);
                                    return false;
                                }
                                
                            }
                        }
                    }
                }
            }
            //if iterated thru rows and cols and no threatened king, can move
            //remove piece where it wanted to be
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
            //create piece where it was before move attempt
            board.createChessPiece(color1, Pawn, rowP, colP);
            return true; //real true
            //block over...
        }
    }

    //If gotten to here, cannot move there
    return false;


}

Type PawnPiece::getType(){
    return Pawn;
}
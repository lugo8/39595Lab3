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
        //simulate move and check for the pawnss's king under threat
        ChessBoard& board = getBoard();
        Student::ChessPiece* target = board.getPiece(toRow, toColumn);
        if(target != NULL)
        {//there is a piece where the piece wants to move
            Color color0 = target->getColor();
            Type ty = target->getType();
            //row and col of target are just toRow and toCol

            board.deleteChessPiece(rowP,colP); //current pawn is gone
            board.deleteChessPiece(toRow,toColumn); //the piece at tarhget is gone
            board.createChessPiece(colrP,Pawn,toRow,toColumn); //create the pawn where it wants to move
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
                            if(kingFinder->getColor() == colrP){ //found my king, get position
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
                board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return true;
                }
            }

        }else{
            board.deleteChessPiece(rowP,colP); //current pawn is gone
            board.createChessPiece(colrP,Pawn,toRow,toColumn); //create the pawn where it wants to move
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
                            if(kingFinder->getColor() == colrP){ //found my king, get position
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
                board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    return true;
                }
            }
        }
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
       //simulate move and check for the pawnss's king under threat
        ChessBoard& board = getBoard();
        Student::ChessPiece* target = board.getPiece(toRow, toColumn);
        if(target != NULL)
        {//there is a piece where the piece wants to move
            Color color0 = target->getColor();
            Type ty = target->getType();
            //row and col of target are just toRow and toCol

            board.deleteChessPiece(rowP,colP); //current pawn is gone
            board.deleteChessPiece(toRow,toColumn); //the piece at tarhget is gone
            board.createChessPiece(colrP,Pawn,toRow,toColumn); //create the pawn where it wants to move
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
                            if(kingFinder->getColor() == colrP){ //found my king, get position
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
                board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return true;
                }
            }

        }else{
            board.deleteChessPiece(rowP,colP); //current pawn is gone
            board.createChessPiece(colrP,Pawn,toRow,toColumn); //create the pawn where it wants to move
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
                            if(kingFinder->getColor() == colrP){ //found my king, get position
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
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    return true;
                }
            }
        }
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
       //simulate move and check for the pawnss's king under threat
        ChessBoard& board = getBoard();
        Student::ChessPiece* target = board.getPiece(toRow, toColumn);
        if(target != NULL)
        {//there is a piece where the piece wants to move
            Color color0 = target->getColor();
            Type ty = target->getType();
            //row and col of target are just toRow and toCol

            board.deleteChessPiece(rowP,colP); //current pawn is gone
            board.deleteChessPiece(toRow,toColumn); //the piece at tarhget is gone
            board.createChessPiece(colrP,Pawn,toRow,toColumn); //create the pawn where it wants to move
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
                            if(kingFinder->getColor() == colrP){ //found my king, get position
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
                board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return true;
                }
            }

        }else{
            board.deleteChessPiece(rowP,colP); //current pawn is gone
            board.createChessPiece(colrP,Pawn,toRow,toColumn); //create the pawn where it wants to move
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
                            if(kingFinder->getColor() == colrP){ //found my king, get position
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
                board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    return true;
                }
            }
        }
        }
    }

    
    posLinear[1] -= 2;

    if(!((posLinear[0] < 0 || posLinear[0] >= nRow) || (posLinear[1] < 0 || posLinear[1] >= nCols)))
    {
        if(posLinear[0] == toRow && posLinear[1] == toColumn && destPiece != NULL)
        {
       //simulate move and check for the pawnss's king under threat
        ChessBoard& board = getBoard();
        Student::ChessPiece* target = board.getPiece(toRow, toColumn);
        if(target != NULL)
        {//there is a piece where the piece wants to move
            Color color0 = target->getColor();
            Type ty = target->getType();
            //row and col of target are just toRow and toCol

            board.deleteChessPiece(rowP,colP); //current pawn is gone
            board.deleteChessPiece(toRow,toColumn); //the piece at tarhget is gone
            board.createChessPiece(colrP,Pawn,toRow,toColumn); //create the pawn where it wants to move
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
                            if(kingFinder->getColor() == colrP){ //found my king, get position
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
                board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    board.createChessPiece(color0, ty,toRow,toColumn); //create the target piece where it was before check
                    return true;
                }
            }

        }else{
            board.deleteChessPiece(rowP,colP); //current pawn is gone
            board.createChessPiece(colrP,Pawn,toRow,toColumn); //create the pawn where it wants to move
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
                            if(kingFinder->getColor() == colrP){ //found my king, get position
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
                board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                return true;
            }else{
                //king exists, check if threatened
                if(board.isPieceUnderThreat(kingRow,kingCol)){
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    return false;
                }else{
                    board.deleteChessPiece(toRow, toColumn); //remove the simulated pawn location
                    board.createChessPiece(colrP, Pawn,rowP,colP); //create the pawn where it was before check
                    return true;
                }
            }
        }
        }
    }

    //If gotten to here, cannot move there
    return false;


}

Type PawnPiece::getType(){
    return Pawn;
}
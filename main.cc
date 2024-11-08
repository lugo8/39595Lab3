#include <assert.h>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"
#include <iostream>
//#include "Student.hh" //for our testing comment out?


void test_part1_4x4_1()
{
    // Config file content:
    // 0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // ~
    // isValidScan

    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Pawn, 2, 1);
    //sBoard.createChessPiece(Black, Pawn, 1, 1);
    sBoard.createChessPiece(Black, Rook, 1, 0);
    sBoard.createChessPiece(Black, Bishop, 2, 2);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.

    int rows = sBoard.getNumRows();
    int cols = sBoard.getNumCols();

    // for(int row1 = 0; row1 < rows; row1++)
    // {
    //     for(int col1 = 0; col1 < cols; col1++)
    //     {

            int row1 = 2;
            int col1 = 1;
            //Every position to every other position
             for(int row2 = 0; row2 < rows; row2++)
            {
                for(int col2 = 0; col2 < cols; col2++)
                {
                    std::cout << "From: " << row1 << " | " << col1 << " To: " << row2 << " | " << col2 << " Valid: " << sBoard.isValidMove(row1, col1, row2, col2) << "\n";
                }
            }
    //     }
    // }

    std::cout << sBoard.displayBoard().str();

    return;
}

void test_part2_4x4()
{
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Pawn, 2, 1);
    sBoard.createChessPiece(Black, Pawn, 1, 1);
    sBoard.createChessPiece(Black, Rook, 1, 0);
    sBoard.createChessPiece(Black, Bishop, 2, 2);

    std::cout << sBoard.displayBoard().str();

    sBoard.movePiece(2,2,3,3);
    sBoard.movePiece(1,0,1,1);

    std::cout << sBoard.displayBoard().str();

    std::cout << "Pawn under threat: " << sBoard.isPieceUnderThreat(2,1) << "\n";

    sBoard.movePiece(1,0,2,0);

    std::cout << sBoard.displayBoard().str();

    std::cout << "Pawn under threat: " << sBoard.isPieceUnderThreat(2,1) << "\n";


}

void test_part3()
{
    using Student::ChessPiece;
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(Black, Bishop, 0, 3);
    sBoard.createChessPiece(Black, Rook, 0, 3);
    sBoard.createChessPiece(White, Pawn, 2, 3);
    sBoard.createChessPiece(Black, Pawn, 3, 0);
    sBoard.createChessPiece(Black, King, 1, 2);
    sBoard.createChessPiece(White, King, 1, 0);

    std::cout << sBoard.displayBoard().str();

    sBoard.movePiece(2,3,1,3);

    std::cout << sBoard.displayBoard().str(); //FINAL STATE

    sBoard.movePiece(1,2,0,1);    

    std::cout << sBoard.displayBoard().str();

    //sBoard.movePiece(2,0,0,0);

    //std::cout << sBoard.displayBoard().str(); //FINAL STATE IN ERROR

    //sBoard.movePiece(0,2,1,2);//can move here WORKS
    //sBoard.movePiece(0,2,1,3);//can move here WORKS
    //sBoard.movePiece(0,2,0,1);//cant move here WORKS
    //sBoard.movePiece(0,2,2,2);//cant move here WORKS
    //sBoard.movePiece(0,2,1,4);//cant move here MEMORY ERROR GONE
    //sBoard.movePiece(0,2,-1,2);//cant move here MEMORY ERROR GONE
    //sBoard.movePiece(0,2,0,4);//cant move here MEMORY ERROR GONE
    //sBoard.movePiece(0,2,0,3);//cant move here FAIL

    //king is likely bocking its self durring threat detection, making a "shadow" of safety 

    //std::cout << sBoard.displayBoard().str(); //should be same, cant move there FAILLLLLL

    /*sBoard.movePiece(0,2,1,2);

    std::cout << sBoard.displayBoard().str();

    sBoard.movePiece(0,0,0,1);

    std::cout << sBoard.displayBoard().str();

    sBoard.movePiece(0,3,0,0); //two black moves in a row... not even a valid move

    std::cout << sBoard.displayBoard().str();

    sBoard.movePiece(1,2,0,1); //white king eats black rook

    std::cout << sBoard.displayBoard().str();

*/


}

//commit test alan
int main()
{
    //test_part1_4x4_1();
    //test_part2_4x4();
    test_part3();
    return EXIT_SUCCESS;
}

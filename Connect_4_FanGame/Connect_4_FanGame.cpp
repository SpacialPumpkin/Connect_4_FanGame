//Connect 4 was published by Milton Bradley / Hasbro. Connect 4 and all related characters are trademarks of Hasbro.
//This Connect 4 Fan Game written in C++ is a fan-made recreation programmed by Evan Leider.
//This project is based on the original game by Hasbro.
#include <iostream>

//prints the introduction to the game
void printIntro()
{
    std::cout << "Connect 4 was published by Milton Bradley / Hasbro." << std::endl;
    std::cout << "Connect 4 and all related characters are trademarks of Hasbro." << std::endl;
    std::cout << "You are playing a Fan-Made recreation by Evan Leider." << std::endl;
    std::cout << "This Fan Game is based on the original game by Hasbro." << std::endl;
    std::cout << std::endl;
    std::cout << "Welcome! Let's get started." << std::endl;
}

//prints the top row of the game board (Column IDs)
void printGameBoardTop(int Columns)
{
    std::cout << " ";
    //if <= 10 Columns, create ID rows with 2 char spacing
    if (Columns <= 10)
    {
        for (int i = 1; i <= Columns; i++)
        {std::cout << i << "  ";}
    }
    //if More than 10 Columns, create ID row with adjusted spacing for IDs after #9.
    else
    {
        for (int i = 1; i < 10; i++)
        {std::cout << i << "  ";}
        for (int i = 10; i <= Columns; i++)
        {std::cout << i << " ";}
    }
    std::cout << std::endl;
}

int main()
{
    printIntro();

    //BOARD VARIABLES
    const int Columns = 10; //how many Columns
    const int Rows = 10; //how many Rows
    char Board[Rows][Columns]; //2D Array for the Board
    int WinCheckCount = 4; //how many Pieces have to be the same to Trigger a Win

    //MULTI-PLAYER PLAYER ALTERNATION VARIABLES
    const int totalPlayers = 4;
    char PiecesHolder[totalPlayers]; //Storage for Player's Piece Choices
    int playerTurn = 1;
    char currPiece;

    //WINNING VARIABLES
    int HorizPiecesInLine = 0; //----------Horizontal Amount of Same Pieces in Line
    int VertPiecesInLine = 0; //-----------Vertical Amount of Same Pieces in Line
    int Diag1PiecesInLine = 0; //----------Diagonal Line #1 (in line formation of: \ shape)
    int Diag2PiecesInLine = 0; //----------Diagonal Line #2 (in line formation of: / shape)
    int Win = 0; // You Win Variable

    //FOR EVERY PLAYER - LET THEM SELECT THEIR PIECE
    for (int i = 1; i <= totalPlayers; i++)
    {
        //Choose your Piece! (a char)
        std::cout << "Player " << playerTurn << "! Choose your piece. Example: X" << std::endl;
        std::cin >> currPiece;
        PiecesHolder[playerTurn] = currPiece;
        std::cout << "Player " << playerTurn << " chose to use " << PiecesHolder[playerTurn] << "!" << std::endl;

        //increment playerTurn for next player to choose their Piece.
        if (playerTurn < totalPlayers)
        {playerTurn++;}
        else if (playerTurn == totalPlayers)
        {playerTurn = 0;}
    }

    //START THE GAME LOOP
    while (1)
    {
        printGameBoardTop(Columns);

        //initialize and print
        for (int CurrRow = 0; CurrRow < Rows; CurrRow++)
        {
            for (int CurrCol = 0; CurrCol < Columns; CurrCol++)
            {
                //initialize the Board's 2D array during the first run-through (With space chars).
                if (playerTurn == 0)
                {Board[CurrRow][CurrCol] = ' ';}

                //Print that board's cell.
                std::cout << "[" << Board[CurrRow][CurrCol] << "]";
            }
            std::cout << std::endl;
        }

        if (Win == 0) //No One Won
        {
            //start taking Input from Players
            if (playerTurn == 0)
            {playerTurn = 1;}

            int Move = 0; //input that is checked if it is acceptable.
            int MoveChecked = 0; //check for an acceptable input.

            //loop until an acceptable move is confirmed.
            while (MoveChecked == 0 && MoveChecked <= Columns)
            {
                //take in Player user input for their Move.
                std::cout << "Player " << playerTurn << "(" << PiecesHolder[playerTurn] <<
                    "): Choose a slot number for your piece." << std::endl;
                std::cin >> Move;
                //consider input, take in if it's an acceptable move.
                if (Move > 0 && Move <= Columns)
                {MoveChecked = Move;}
                std::cin.clear(); //clears errors
                std::cin.ignore(); // discards buffer
            }

            //update array with Move. (Had to do -1 due to array)
            //loop through each row starting at bottom
            for (int CurrRow = Rows; CurrRow >= 0; CurrRow--)
            {
                //if the cell is empty,
                if (Board[CurrRow][Move - 1] == ' ')
                {
                    //place the player's piece in that cell, then check for win conditions based on that piece.
                    char DroppedPieceIcon = PiecesHolder[playerTurn];
                    Board[CurrRow][Move - 1] = DroppedPieceIcon;

                    //WIN CONDITION CHECKS
                    //Vertical Scan - For Every Piece in the Column where the Piece was Dropped
                    for (int CurrRowScan = 0; CurrRowScan < Rows; CurrRowScan++)
                    {
                        //If the Piece Scanned in this Column (Move - 1) is the Same as the Dropped Piece,
                        if ((Board[CurrRowScan][Move - 1] == DroppedPieceIcon) && (VertPiecesInLine < WinCheckCount))
                            //Increment Count of the Same Pieces Found in the Same Line
                        {
                            VertPiecesInLine++;
//FOR DEBUGGING->           std::cout << " Vertical: " << VertPiecesInLine << std::endl;
                            // if the amount of Vertical Pieces found in a line was = to the Win Check Count, You Win.
                            if (VertPiecesInLine >= WinCheckCount)
                            {break;}
                        }
                        //Otherwise Reset amount of Same Piece found if a Different Piece was Found
                        else {VertPiecesInLine = 0;}
                    }
                    if (VertPiecesInLine >= WinCheckCount) { break; }

                    //Horizontal Scan - For Every Piece in the Row where the Piece was Dropped
                    for (int CurrColScan = 0; CurrColScan < Columns; CurrColScan++)
                    {
                        //If the Piece Scanned in this Row is the Same as the Dropped Piece,
                        if ((Board[CurrRow][CurrColScan] == DroppedPieceIcon) && (HorizPiecesInLine < WinCheckCount))
                            //Increment Count of the Same Pieces Found in the Same Line
                        {
                            HorizPiecesInLine++;
//FOR DEBUGGING->           std::cout << "Horizontal: " << HorizPiecesInLine << std::endl;
                            // if the amount of Horizontal Pieces found in a line was = to the Win Check Count, You Win.
                            if (HorizPiecesInLine >= WinCheckCount)
                            {break;}
                        }
                        //Otherwise Reset amount of Same Piece found if a Different Piece was Found
                        else {HorizPiecesInLine = 0;}
                    }
                    if (HorizPiecesInLine >= WinCheckCount) { break; }

                    //Start Position for Diagonals: (Y and X) for Reference:
                    //Board[CurrRow - (WinCheckCount - 1)][(Move - 1) - (WinCheckCount - 1)]

                    //Diagonal Scan #1 - For Every Piece in the Diagonal Left Up to Right Down (\ Shape)
                    //based on where the Piece was Dropped
                    int x = ((Move - 1) - (WinCheckCount - 1)); // Start at (WinCheckCount - 1) Away to Left
                    int y = (CurrRow - (WinCheckCount - 1)); // Start at (WinCheckCount - 1) Away to Top
                    for (int ScanIndex = 0; ScanIndex <= Rows; ScanIndex++)
                    {
                        //If the Piece Scanned in Diagonal (Down Right Direction in \ Shape) is Same as the Dropped Piece,
                        if ((Board[y][x] == DroppedPieceIcon) && (Diag1PiecesInLine < WinCheckCount))
                            //Increment Count of the Same Pieces Found in the Same Line
                        {
                            Diag1PiecesInLine++;
//FOR DEBUGGING->           std::cout << "Diagonal #1 ->v: " << Diag1PiecesInLine << std::endl;
                            // if the amount of Horizontal Pieces found in a line was = to the Win Check Count, You Win.
                            if (Diag1PiecesInLine >= WinCheckCount)
                            {break;}
                        }
                        //Otherwise Reset amount of Same Piece found if a Different Piece was Found
                        else {Diag1PiecesInLine = 0;}
                        //increment x and y staircase scan to right
                        x++;
                        y++;
                    }
                    if (Diag1PiecesInLine >= WinCheckCount) { break; }

                    //Diagonal Scan #2 - For Every Piece in the Diagonal Right Up to Left Down ( / Shape)
                    //based on where the Piece was Dropped
                    x = ((Move - 1) + (WinCheckCount - 1)); // Start at (WinCheckCount - 1) Away to Right
                    y = (CurrRow - (WinCheckCount - 1)); // Start at (WinCheckCount - 1) Away to Top
                    for (int ScanIndex = 0; ScanIndex <= Rows; ScanIndex++)
                    {
                        //If the Piece Scanned in Diagonal (Down Right Direction in \ Shape) is Same as the Dropped Piece,
                        if ((Board[y][x] == DroppedPieceIcon) && (Diag2PiecesInLine < WinCheckCount))
                            //Increment Count of the Same Pieces Found in the Same Line
                        {
                            Diag2PiecesInLine++;
//FOR DEBUGGING->           std::cout << " Diagonal #2 /: " << Diag2PiecesInLine << std::endl;
                            // if the amount of Diagonal Pieces found in a line was = to the Win Check Count, You Win.
                            if (Diag2PiecesInLine >= WinCheckCount)
                            {break;}
                        }
                        //Otherwise Reset amount of Same Piece found if a Different Piece was Found
                        else {Diag2PiecesInLine = 0;}
                        //increment x and y staircase scan to left
                        x--;
                        y++;
                    }
                    if (Diag2PiecesInLine >= WinCheckCount) { break; }

                    //End For Loop when piece dropped and win conditions were checked for.
                    break;
                }
            }

            //WIN CONDITION: If 4 in a Row Horizontally (<- or ->), OR Veritically (^ or v), OR
            //Diagonally by Diagonal Line #1 (\ shape), OR Diagonally by Diagonal Line #2 (/ shape).
            if ((HorizPiecesInLine >= WinCheckCount) || (VertPiecesInLine >= WinCheckCount) ||
                (Diag1PiecesInLine >= WinCheckCount) || (Diag2PiecesInLine >= WinCheckCount))
            {
                std::cout << std::endl;
                //GAME OVER Header (Stretches Based on # of Columns)
                //left side of header

                for (int i = 0; i <= Columns / 1.6; i++)
                {std::cout << "::";}

                //GAME OVER
                std::cout << "Game Over!";

                //right side of header
                for (int i = 0; i <= Columns / 1.6; i++)
                {std::cout << "::";}

                std::cout << std::endl;

                //Set Variable to You Win!
                Win = 1;
            }

            if (Win == 0) //If No One Won
            {
                //reset PiecesInLine;
                HorizPiecesInLine = 0;
                VertPiecesInLine = 0;
                Diag1PiecesInLine = 0;
                Diag2PiecesInLine = 0;

                //Next Player's Turn
                if (playerTurn < totalPlayers)
                {playerTurn++;}
                else if (playerTurn == totalPlayers)
                {playerTurn = 1;}
            }
        }

        // If You Win
        else {
            //Win Condition: If 4 in a Row Horizontally (<- or ->), OR Veritically (^ or v), OR
            //Diagonally by Diagonal Line #1 (\ shape), OR Diagonally by Diagonal Line #2 (/ shape).
            if ((HorizPiecesInLine >= WinCheckCount) || (VertPiecesInLine >= WinCheckCount) ||
                (Diag1PiecesInLine >= WinCheckCount) || (Diag2PiecesInLine >= WinCheckCount))
            {
                std::cout << "Player " << playerTurn << "(" << PiecesHolder[playerTurn] <<
                    ") Won the Game!" << std::endl;
            }
            //Hold the Screen After You Win.
            int hold = 0;
            std::cin >> hold;
        }
    }
    return 0;
}
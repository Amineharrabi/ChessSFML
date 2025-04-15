#ifndef CASTLING_H
#define CASTLING_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Castling
{
private:
    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookAMoved = false; // a-file rook (queenside)
    bool whiteRookHMoved = false; // h-file rook (kingside)
    bool blackRookAMoved = false;
    bool blackRookHMoved = false;

    // Helper function to check if a square is under attack
    bool isSquareUnderAttack(int square, int board[64], int attackingColor)
    {
        // Check attacks from pawns
        if (attackingColor == -1)
        { // Black attacking
            // Check white pawn attacks
            if (square % 8 > 0 && square - 9 >= 0 && board[square - 9] == -6)
                return true;
            if (square % 8 < 7 && square - 7 >= 0 && board[square - 7] == -6)
                return true;
        }
        else
        { // White attacking
            // Check black pawn attacks
            if (square % 8 > 0 && square + 7 < 64 && board[square + 7] == 6)
                return true;
            if (square % 8 < 7 && square + 9 < 64 && board[square + 9] == 6)
                return true;
        }

        // Knight attacks (same for both colors)
        int knightMoves[8] = {-17, -15, -10, -6, 6, 10, 15, 17};
        for (int i = 0; i < 8; i++)
        {
            int targetSquare = square + knightMoves[i];
            if (targetSquare >= 0 && targetSquare < 64)
            {
                // Check if knight movement is valid (not wrapping around the board)
                int sqRow = square / 8;
                int sqCol = square % 8;
                int tgRow = targetSquare / 8;
                int tgCol = targetSquare % 8;

                // Check if the knight's L-shape movement is valid
                if ((abs(sqRow - tgRow) == 2 && abs(sqCol - tgCol) == 1) ||
                    (abs(sqRow - tgRow) == 1 && abs(sqCol - tgCol) == 2))
                {
                    if (board[targetSquare] == 2 * attackingColor)
                        return true;
                }
            }
        }

        // Rook/Queen attacks (horizontal and vertical)
        // Check horizontally
        for (int i = (square / 8) * 8; i < (square / 8 + 1) * 8; i++)
        {
            if (i == square)
                continue;

            // Check if there's a piece between square and i
            bool blocked = false;
            int start = std::min(square, i);
            int end = std::max(square, i);
            for (int j = start + 1; j < end; j++)
            {
                if (board[j] != 0)
                {
                    blocked = true;
                    break;
                }
            }

            if (!blocked && (board[i] == 1 * attackingColor || board[i] == 4 * attackingColor))
            {
                return true;
            }
        }

        // Check vertically
        for (int i = square % 8; i < 64; i += 8)
        {
            if (i == square)
                continue;

            bool blocked = false;
            int start = std::min(square, i);
            int end = std::max(square, i);
            for (int j = start + 8; j < end; j += 8)
            {
                if (board[j] != 0)
                {
                    blocked = true;
                    break;
                }
            }

            if (!blocked && (board[i] == 1 * attackingColor || board[i] == 4 * attackingColor))
            {
                return true;
            }
        }

        // Bishop/Queen attacks (diagonals)
        // Top-left to bottom-right diagonal
        int row = square / 8;
        int col = square % 8;

        // Check top-left direction
        for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; r--, c--)
        {
            int idx = r * 8 + c;
            if (board[idx] != 0)
            {
                if (board[idx] == 3 * attackingColor || board[idx] == 4 * attackingColor)
                {
                    return true;
                }
                break;
            }
        }

        // Check bottom-right direction
        for (int r = row + 1, c = col + 1; r < 8 && c < 8; r++, c++)
        {
            int idx = r * 8 + c;
            if (board[idx] != 0)
            {
                if (board[idx] == 3 * attackingColor || board[idx] == 4 * attackingColor)
                {
                    return true;
                }
                break;
            }
        }

        // Top-right to bottom-left diagonal
        // Check top-right direction
        for (int r = row - 1, c = col + 1; r >= 0 && c < 8; r--, c++)
        {
            int idx = r * 8 + c;
            if (board[idx] != 0)
            {
                if (board[idx] == 3 * attackingColor || board[idx] == 4 * attackingColor)
                {
                    return true;
                }
                break;
            }
        }

        // Check bottom-left direction
        for (int r = row + 1, c = col - 1; r < 8 && c >= 0; r++, c--)
        {
            int idx = r * 8 + c;
            if (board[idx] != 0)
            {
                if (board[idx] == 3 * attackingColor || board[idx] == 4 * attackingColor)
                {
                    return true;
                }
                break;
            }
        }

        // King attacks
        int kingMoves[8] = {-9, -8, -7, -1, 1, 7, 8, 9};
        for (int i = 0; i < 8; i++)
        {
            int targetSquare = square + kingMoves[i];
            if (targetSquare >= 0 && targetSquare < 64)
            {
                // Check if king movement is valid (not wrapping around the board)
                int sqRow = square / 8;
                int sqCol = square % 8;
                int tgRow = targetSquare / 8;
                int tgCol = targetSquare % 8;

                // Check if the move is valid (not crossing the board edge)
                if (abs(sqRow - tgRow) <= 1 && abs(sqCol - tgCol) <= 1)
                {
                    if (board[targetSquare] == 5 * attackingColor)
                        return true;
                }
            }
        }

        return false;
    }

    // Helper to check if the king is in check
    bool isKingInCheck(int board[64], int kingColor)
    {
        // Find the king's position
        int kingPos = -1;
        for (int i = 0; i < 64; i++)
        {
            if (board[i] == 5 * kingColor)
            {
                kingPos = i;
                break;
            }
        }

        if (kingPos == -1)
            return false; // King not found (shouldn't happen in a valid game)

        // Check if the king's square is under attack
        return isSquareUnderAttack(kingPos, board, -kingColor);
    }

public:
    // Function to track piece movement
    void trackPieceMovement(int from, int to, int piece)
    {
        if (from != to)
        {
            if (piece == 5)
            { // White king
                whiteKingMoved = true;
                std::cout << "White king moved, castling no longer possible" << std::endl;
            }
            else if (piece == -5)
            { // Black king
                blackKingMoved = true;
                std::cout << "Black king moved, castling no longer possible" << std::endl;
            }
            else if (piece == 1)
            { // White rook
                if (from == 56)
                {
                    whiteRookAMoved = true;
                    std::cout << "White queenside rook moved" << std::endl;
                }
                if (from == 63)
                {
                    whiteRookHMoved = true;
                    std::cout << "White kingside rook moved" << std::endl;
                }
            }
            else if (piece == -1)
            { // Black rook
                if (from == 0)
                {
                    blackRookAMoved = true;
                    std::cout << "Black queenside rook moved" << std::endl;
                }
                if (from == 7)
                {
                    blackRookHMoved = true;
                    std::cout << "Black kingside rook moved" << std::endl;
                }
            }
        }
    }

    // Check if castling is possible
    bool canCastle(int from, int to, int piece, int board[64])
    {
        // Check if the move is a castling attempt
        if (piece == 5)
        { // White king
            // Kingside castling (e1 to g1)
            if (from == 60 && to == 62 && !whiteKingMoved && !whiteRookHMoved)
            {
                // Check if squares between king and rook are empty
                if (board[61] == 0 && board[62] == 0)
                {
                    // Check if king is not in check and doesn't pass through check
                    if (!isKingInCheck(board, 1) &&
                        !isSquareUnderAttack(61, board, -1) &&
                        !isSquareUnderAttack(62, board, -1))
                    {
                        return true;
                    }
                    else
                    {
                        std::cout << "White kingside castling not possible: king is in check or would pass through check" << std::endl;
                    }
                }
                else
                {
                    std::cout << "White kingside castling not possible: squares between king and rook are not empty" << std::endl;
                }
            }
            // Queenside castling (e1 to c1)
            else if (from == 60 && to == 58 && !whiteKingMoved && !whiteRookAMoved)
            {
                // Check if squares between king and rook are empty
                if (board[57] == 0 && board[58] == 0 && board[59] == 0)
                {
                    // Check if king is not in check and doesn't pass through check
                    if (!isKingInCheck(board, 1) &&
                        !isSquareUnderAttack(58, board, -1) &&
                        !isSquareUnderAttack(59, board, -1))
                    {
                        return true;
                    }
                    else
                    {
                        std::cout << "White queenside castling not possible: king is in check or would pass through check" << std::endl;
                    }
                }
                else
                {
                    std::cout << "White queenside castling not possible: squares between king and rook are not empty" << std::endl;
                }
            }
        }
        else if (piece == -5)
        { // Black king
            // Kingside castling (e8 to g8)
            if (from == 4 && to == 6 && !blackKingMoved && !blackRookHMoved)
            {
                // Check if squares between king and rook are empty
                if (board[5] == 0 && board[6] == 0)
                {
                    // Check if king is not in check and doesn't pass through check
                    if (!isKingInCheck(board, -1) &&
                        !isSquareUnderAttack(5, board, 1) &&
                        !isSquareUnderAttack(6, board, 1))
                    {
                        return true;
                    }
                    else
                    {
                        std::cout << "Black kingside castling not possible: king is in check or would pass through check" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Black kingside castling not possible: squares between king and rook are not empty" << std::endl;
                }
            }
            // Queenside castling (e8 to c8)
            else if (from == 4 && to == 2 && !blackKingMoved && !blackRookAMoved)
            {
                // Check if squares between king and rook are empty
                if (board[1] == 0 && board[2] == 0 && board[3] == 0)
                {
                    // Check if king is not in check and doesn't pass through check
                    if (!isKingInCheck(board, -1) &&
                        !isSquareUnderAttack(2, board, 1) &&
                        !isSquareUnderAttack(3, board, 1))
                    {
                        return true;
                    }
                    else
                    {
                        std::cout << "Black queenside castling not possible: king is in check or would pass through check" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Black queenside castling not possible: squares between king and rook are not empty" << std::endl;
                }
            }
        }
        return false;
    }

    // Perform the castling move
    void performCastle(int from, int to, int board[64], int spritepositions[64],
                       sf::Sprite sprite[64], sf::RectangleShape rectangle[64],
                       sf::Vector2f piecePositions[64])
    {
        int kingSprite = spritepositions[from];
        int rookFrom, rookTo;

        // White castling
        if (board[from] == 5)
        {
            if (to == 62)
            { // Kingside
                rookFrom = 63;
                rookTo = 61;
                std::cout << "Performing white kingside castling" << std::endl;
            }
            else
            { // Queenside
                rookFrom = 56;
                rookTo = 59;
                std::cout << "Performing white queenside castling" << std::endl;
            }
        }
        // Black castling
        else
        {
            if (to == 6)
            { // Kingside
                rookFrom = 7;
                rookTo = 5;
                std::cout << "Performing black kingside castling" << std::endl;
            }
            else
            { // Queenside
                rookFrom = 0;
                rookTo = 3;
                std::cout << "Performing black queenside castling" << std::endl;
            }
        }

        int rookSprite = spritepositions[rookFrom];

        // Move king sprite
        sprite[kingSprite].setPosition(rectangle[to].getPosition());
        piecePositions[kingSprite] = rectangle[to].getPosition();

        // Move rook sprite
        sprite[rookSprite].setPosition(rectangle[rookTo].getPosition());
        piecePositions[rookSprite] = rectangle[rookTo].getPosition();

        // Update board arrays
        spritepositions[to] = kingSprite;
        spritepositions[from] = 64; // NO_PIECE
        board[to] = board[from];
        board[from] = 0;

        spritepositions[rookTo] = rookSprite;
        spritepositions[rookFrom] = 64; // NO_PIECE
        board[rookTo] = board[rookFrom];
        board[rookFrom] = 0;

        // Update movement flags after castling
        if (board[to] == 5)
        {
            whiteKingMoved = true;
            if (rookFrom == 63)
                whiteRookHMoved = true;
            if (rookFrom == 56)
                whiteRookAMoved = true;
        }
        else
        {
            blackKingMoved = true;
            if (rookFrom == 7)
                blackRookHMoved = true;
            if (rookFrom == 0)
                blackRookAMoved = true;
        }

        std::cout << "Castling performed successfully!" << std::endl;
    }

    // Reset for testing
    void resetCastlingFlags()
    {
        whiteKingMoved = false;
        blackKingMoved = false;
        whiteRookAMoved = false;
        whiteRookHMoved = false;
        blackRookAMoved = false;
        blackRookHMoved = false;
        std::cout << "Castling flags reset" << std::endl;
    }

    // Debug function to print castling status
    void printCastlingStatus()
    {
        std::cout << "Castling Status:" << std::endl;
        std::cout << "White King moved: " << (whiteKingMoved ? "Yes" : "No") << std::endl;
        std::cout << "Black King moved: " << (blackKingMoved ? "Yes" : "No") << std::endl;
        std::cout << "White Rook A moved: " << (whiteRookAMoved ? "Yes" : "No") << std::endl;
        std::cout << "White Rook H moved: " << (whiteRookHMoved ? "Yes" : "No") << std::endl;
        std::cout << "Black Rook A moved: " << (blackRookAMoved ? "Yes" : "No") << std::endl;
        std::cout << "Black Rook H moved: " << (blackRookHMoved ? "Yes" : "No") << std::endl;
    }
};

#endif // CASTLING_H
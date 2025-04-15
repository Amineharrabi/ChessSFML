#include <SFML/Graphics.hpp>
#include <iostream>
#include "utilityBox.h"
#include "save.h"
#include "castling.h"

#include <fstream>
#define NO_PIECE 64

using namespace sf;
using namespace std;

int spritepositions[64] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
    NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
    NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
    NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
    48, 49, 50, 51, 52, 53, 54, 55,
    56, 57, 58, 59, 60, 61, 62, 63};

int board[64] = {
    -1, -2, -3, -4, -5, -3, -2, -1,
    -6, -6, -6, -6, -6, -6, -6, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    6, 6, 6, 6, 6, 6, 6, 6,
    1, 2, 3, 4, 5, 3, 2, 1};

class ChessBoard
{
private:
    const float WIDTH = 500;
    const float HEIGHT = 500;
    sf::Sprite boardSquares[64];
    sf::Texture boardTextures[64];
    sf::Texture darkSquareTexture;
    sf::Texture lightSquareTexture;
    sf::RenderWindow window;
    int selectedIndex = -1;
    bool pieceSelected = false;
    int boardState[64]; // Renamed to avoid conflict with global array
    int turn = 1;       // 1 for white, -1 for black
    bool isMove = false;
    sf::Vector2f firstpos;
    sf::Vector2f secondpos;
    sf::Vector2f piecePositions[64];
    Castling castling;

public:
    void loadtextures(Texture texture[64]);
    void loadboard(Texture texture[64], RectangleShape rectangle[64], Sprite sprite[64]);
    void MainFunctions(int u);
    void handlePieceSelection(sf::Vector2i mousePos, sf::RectangleShape rectangles[64]);
    void handlePieceMovement(sf::Vector2i pos, sf::RectangleShape rectangle[64],
                             sf::Sprite sprite[64], Identity &box);
    void resetBoardColors(sf::RectangleShape rectangle[64]);

    ChessBoard()
    {
        // Initialize board state with global array
        memcpy(boardState, board, sizeof(board));
    }
};

void ChessBoard::loadtextures(Texture texture[64])
{
    for (int i = 0; i < 64; i++)
    {
        if (spritepositions[i] == 64)
            continue;

        if (spritepositions[i] == 0 || spritepositions[i] == 7)
            texture[i].loadFromFile("images/blackRook.png");
        else if (spritepositions[i] == 1 || spritepositions[i] == 6)
            texture[i].loadFromFile("images/blackKnight.png");
        else if (spritepositions[i] == 2 || spritepositions[i] == 5)
            texture[i].loadFromFile("images/blackBishop.png");
        else if (spritepositions[i] == 3)
            texture[i].loadFromFile("images/blackQueen.png");
        else if (spritepositions[i] == 4)
            texture[i].loadFromFile("images/blackKing.png");
        else if (spritepositions[i] >= 8 && spritepositions[i] <= 15)
            texture[i].loadFromFile("images/blackPawn.png");
        else if (spritepositions[i] == 63 || spritepositions[i] == 56)
            texture[i].loadFromFile("images/whiteRook.png");
        else if (spritepositions[i] == 62 || spritepositions[i] == 57)
            texture[i].loadFromFile("images/whiteKnight.png");
        else if (spritepositions[i] == 61 || spritepositions[i] == 58)
            texture[i].loadFromFile("images/whiteBishop.png");
        else if (spritepositions[i] == 59)
            texture[i].loadFromFile("images/whiteQueen.png");
        else if (spritepositions[i] == 60)
            texture[i].loadFromFile("images/whiteKing.png");
        else if (spritepositions[i] >= 48 && spritepositions[i] <= 55)
            texture[i].loadFromFile("images/whitePawn.png");
    }
}

void ChessBoard::loadboard(Texture texture[64], RectangleShape rectangle[64], Sprite sprite[64])
{
    if (!darkSquareTexture.loadFromFile("images/square_brown_dark.png"))
    {
        cerr << "Failed to load dark square texture!" << endl;
        return;
    }
    if (!lightSquareTexture.loadFromFile("images/square_brown_light.png"))
    {
        cerr << "Failed to load light square texture!" << endl;
        return;
    }

    // Initialize board squares
    for (int i = 0; i < 64; ++i)
    {
        rectangle[i].setSize(Vector2f(WIDTH / 8, HEIGHT / 8));
        rectangle[i].setPosition((i % 8) * (WIDTH / 8), (i / 8) * (HEIGHT / 8));
        rectangle[i].setTexture((i / 8 + i % 8) % 2 == 0 ? &lightSquareTexture : &darkSquareTexture);
    }

    // Initialize piece sprites
    for (int j = 0; j < 64; j++)
    {
        if (spritepositions[j] != 64)
        {
            sprite[j].setTexture(texture[j]);
            sprite[j].setPosition(rectangle[j].getPosition());
            if (spritepositions[j] != 64)
            {
                piecePositions[spritepositions[j]] = rectangle[j].getPosition();
                float scaleX = (WIDTH / 8.0f) / texture[j].getSize().x;
                float scaleY = (HEIGHT / 8.0f) / texture[j].getSize().y;
                sprite[j].setScale(scaleX, scaleY);
            }
        }
    }
}

void ChessBoard::handlePieceSelection(sf::Vector2i mousePos, sf::RectangleShape rectangles[64])
{
    for (int i = 0; i < 64; ++i)
    {
        if (rectangles[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            // If a piece is already selected and player clicks the same piece, deselect it
            if (i == selectedIndex && pieceSelected)
            {
                resetBoardColors(rectangles);
                pieceSelected = false;
                selectedIndex = -1;
                cout << "Deselected piece." << endl;
                return;
            }

            // Check turn and piece color for new selection
            if ((turn == 1 && boardState[i] > 0) || (turn == -1 && boardState[i] < 0))
            {
                // Reset previous selection if any
                if (pieceSelected)
                {
                    resetBoardColors(rectangles);
                }

                // Select new piece
                selectedIndex = i;
                rectangles[selectedIndex].setFillColor(Color::Red);
                pieceSelected = true;
                cout << "Selected piece at: " << i << endl;
                return;
            }
        }
    }
}

void ChessBoard::handlePieceMovement(sf::Vector2i mousePos,
                                     sf::RectangleShape rectangle[64],
                                     sf::Sprite sprite[64],
                                     Identity &box)
{
    for (int i = 0; i < 64; ++i)
    {
        if (!rectangle[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            continue;
        }

        // Check if the player wants to select a different piece of their color
        if ((turn == 1 && boardState[i] > 0) || (turn == -1 && boardState[i] < 0))
        {
            // Reselect a new piece
            resetBoardColors(rectangle);
            selectedIndex = i;
            rectangle[i].setFillColor(Color::Red);
            pieceSelected = true;
            cout << "Reselected piece at: " << i << endl;
            return;
        }

        // Check for castling
        bool isCastling = castling.canCastle(selectedIndex, i, boardState[selectedIndex], boardState);

        // Check if the move is valid (either normal move or castling)
        isMove = isCastling || box.identifier(selectedIndex, i, boardState[selectedIndex], boardState);

        if (isMove && i != selectedIndex)
        {
            // Handle castling move
            if (isCastling)
            {
                castling.performCastle(selectedIndex, i, boardState, spritepositions, sprite, rectangle, piecePositions);
            }
            else
            { // Regular move
                // Handle captures safely
                if (boardState[i] != 0) // If there's a piece to capture
                {
                    // Find the captured piece's sprite index
                    int capturedSpriteIndex = spritepositions[i];
                    if (capturedSpriteIndex != NO_PIECE)
                    {
                        // Move the captured piece off-screen
                        sprite[capturedSpriteIndex].setPosition(-1000, -1000);
                    }
                }

                // Get the sprite index of the moving piece
                int movingSpriteIndex = spritepositions[selectedIndex];
                if (movingSpriteIndex != NO_PIECE)
                {
                    // Update the piece position
                    sprite[movingSpriteIndex].setPosition(rectangle[i].getPosition());
                    piecePositions[movingSpriteIndex] = rectangle[i].getPosition();

                    // Update arrays
                    spritepositions[i] = movingSpriteIndex;
                    spritepositions[selectedIndex] = NO_PIECE;
                    boardState[i] = boardState[selectedIndex];
                    boardState[selectedIndex] = 0;

                    if (selectedIndex != i && movingSpriteIndex != NO_PIECE)
                    {
                        castling.trackPieceMovement(selectedIndex, i, boardState[i]);
                    }
                    // Handle pawn promotion
                    if ((boardState[i] == 6 && i / 8 == 0) || (boardState[i] == -6 && i / 8 == 7))
                    {
                        boardState[i] = (boardState[i] > 0) ? 4 : -4; // Promote to queen
                        // You might want to update the texture here as well
                    }
                }
            }
            if (boardState[selectedIndex] == 5 || boardState[selectedIndex] == -5)
            {
                cout << "King move to " << i << ", castling possible: " << (castling.canCastle(selectedIndex, i, boardState[selectedIndex], boardState) ? "Yes" : "No") << endl;
            }

            turn *= -1; // Switch turns
            resetBoardColors(rectangle);
            pieceSelected = false;
            selectedIndex = -1;
            return;
        }
    }
}

void ChessBoard::resetBoardColors(sf::RectangleShape rectangles[64])
{
    for (int i = 0; i < 64; ++i)
    {
        rectangles[i].setFillColor((i / 8 + i % 8) % 2 == 0 ? Color(240, 217, 181) : Color(181, 136, 99));
    }
}

void ChessBoard::MainFunctions(int u)
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "CHESS");

    RectangleShape rectangles[64];
    Texture textures[64];
    Sprite sprites[64];
    Identity box;

    loadtextures(textures);
    loadboard(textures, rectangles, sprites);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (!pieceSelected)
                {
                    handlePieceSelection(mousePos, rectangles);
                }
                else
                {
                    handlePieceMovement(mousePos, rectangles, sprites, box);
                }
            }
        }

        // Draw
        window.clear();
        for (int i = 0; i < 64; ++i)
        {
            window.draw(rectangles[i]);
        }
        for (int j = 0; j < 64; ++j)
        {
            int spriteIndex = spritepositions[j];

            if (spriteIndex != NO_PIECE)
            {
                sprites[spriteIndex].setPosition(piecePositions[spriteIndex]);
                window.draw(sprites[spriteIndex]);
            }
        }
        window.display();
    }
}

# Chess Game - The Game of Kings

This project is a chess game built using **SFML (Simple and Fast Multimedia Library)**. It features a graphical user interface, piece movement logic, and special chess rules like castling. The game allows players to play against each other locally.

---

## Features

- **Graphical Chessboard**: A visually appealing chessboard with light and dark squares.
- **Piece Movement**: Supports all standard chess piece movements.
- **Special Rules**:
  - Castling (both kingside and queenside).
  - Pawn promotion to a queen.
- **Save and Load**: Save the current game state and reload it later.
- **Interactive UI**: Click-based piece selection and movement.
- **Custom Textures**: High-quality textures for pieces and board squares.

---

## Requirements

- **SFML Library**: Ensure SFML is installed on your system.
- **C++ Compiler**: A C++17-compatible compiler (e.g., g++).
- **Operating System**: Windows (tested).

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Amineharrabi/ChessSFML.git
   cd ChessSFML
   ```
2. Install SFML:
   Download SFML from SFML's official website.
   Place the include and lib directories in the src folder.
3. Build the project:

   ```
   make
   ```
make sure the dll files are in the root dir !
4. Run the game:
   ./main

Known Issues
AI Opponent: Currently, the game only supports two-player local mode.
Limited Save Slots: Only one game state can be saved at a time

## Future Improvements

Add an AI opponent for single-player mode.
Implement additional save slots.
Enhance the UI with animations and sound effects.
Adding a analysis (chess.com like) [in process]

## screenshots

![Screenshot 1](https://github.com/Amineharrabi/ChessSFML/blob/main/images/SCREENIE1.png)
![Screenshot 2](https://github.com/Amineharrabi/ChessSFML/blob/main/images/SCREENIE2.png)



  
your project tree should look like this
```
V0_chess
├─ boardpositions.txt
├─ coding
│  ├─ bishop.h
│  ├─ boardpositions.txt
│  ├─ castling.h
│  ├─ ChessBoard.h
│  ├─ graphs.h
│  ├─ king.h
│  ├─ knight.h
│  ├─ main.cpp
│  ├─ openal32.dll
│  ├─ pawn.h
│  ├─ piece.h
│  ├─ queen.h
│  ├─ README.md
│  ├─ rook.h
│  ├─ save.h
│  ├─ spritepositions.txt
│  ├─ START.h
│  └─ utilityBox.h
├─ images
│  ├─ blackBishop.png
│  ├─ blackKing.png
│  ├─ blackKnight.png
│  ├─ blackPawn.png
│  ├─ blackQueen.png
│  ├─ blackRook.png
│  ├─ board.png
│  ├─ gamepad-controller.png
│  ├─ play-button.png
│  ├─ refresh-button.png
│  ├─ rsz_1images.png
│  ├─ save-disk.png
│  ├─ save-icon-54519.png
│  ├─ SCREENIE1.png
│  ├─ SCREENIE2.png
│  ├─ square_brown_dark.png
│  ├─ square_brown_light.png
│  ├─ whiteBishop.png
│  ├─ whiteKing.png
│  ├─ whiteKnight.png
│  ├─ whitePawn.png
│  ├─ whiteQueen.png
│  └─ whiteRook.png
├─ main.exe
├─ Makefile
├─ sfml-audio-2.dll
├─ sfml-audio-d-2.dll
├─ sfml-graphics-2.dll
├─ sfml-graphics-d-2.dll
├─ sfml-network-2.dll
├─ sfml-network-d-2.dll
├─ sfml-system-2.dll
├─ sfml-system-d-2.dll
├─ sfml-window-2.dll
├─ sfml-window-d-2.dll
├─ spritepositions.txt
└─ src
   ├─ include
   │  └─ SFML
   │     FILES HERE
   ├─ lib
      FILES HERE

```

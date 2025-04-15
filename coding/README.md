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
   git clone https://github.com/your-repo/v0_chess.git
   cd v0_chess
   ```
2. Install SFML:
   Download SFML from SFML's official website.
   Place the include and lib directories in the src folder.
3. Build the project:

   ```
   make
   ```

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

![Screenshot 1](https://github.com/your-repo/v0_chess/blob/main/screenshot1.png)
![Screenshot 2](https://github.com/your-repo/v0_chess/blob/main/screenshot2.png)

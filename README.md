Quoridor Game

ABOUT AND RULES:
    This is a spin on the board game "Quoridor". The general rules of the game are:
    1- Each player can do 2 things in their move:
        1-1- Either move their bead to an unblocked cell adjacent to their current cell.
        1-2- Or they can choose a cell and block that cell with either the cells to its left and right, or the cells to its up and down.
    2- A cell is deemed 'unblocked' if:
        2-1- No player (including the current player) has blocked that cell in a previous turn.
        2-2- No other players are in that cell.
        2-3- The cell is not out of bounds!
    3- The goal of the game is to get to the middle cell in the board. The first player who gets there wins the game.

HOW TO RUN:
    The installation is fairly straight forward, Just download the folder and extract it to a desired location. Then open the terminal and navigate to that location (use the command "cd <the location>" or if you're on Ubuntu, right-click in that folder and click open in terminal). then write "./server", this will start the server on your computer using 127.0.0.1:8080. Then open the same location in a new terminal and write "./client", this will start the client that connects to the server, then all you gotta do is connect enough clients to the server and the game will start automatically.


# Installation Instructions
Make Sure that your Device has OpenGL Graphics installed. Open the terminal in the current directory and compile the game using the following command : 

```g++ chessInterface.cpp -lglut -lGL -lGLU```

And now you can execute the game using the command :  

```./a.out```

# GLChess
A Chess program using OpenGl written entirely in C++. (Yes even the piece shapes have been stored in array data!)

Contributors:
[Alan John](https://github.com/TheForeverLost)
[Amitav Soni](https://github.com/soniamitav)


This project was made for our 4th semester's academic project

This is how it looks

![Demo](https://media.giphy.com/media/f6IVaSWY3YqcWzZULL/giphy.gif)

## Running the game
It is important to run a program to check all possible legal moves which requires analysis into the rules of chess.   
The AI was made using Min-Max Technique in Game Decision Tree with Alpha-Beta pruning for time optimization.

### Possible updates
1. Parallel Processing with Iterative Deepening to improve efficiency.
2. A graphical interface menu to make it more user friendly.
3. Support for En Passant's Move.

Please feel free to suggest improvements

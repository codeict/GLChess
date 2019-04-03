# GLChess
A Chess program using OpenGl written entirely in C++
*(Python has been used to write large amounts of c++ openGL commands which will be addressed later)*

Contributors:
[Amitav Soni](https://github.com/soniamitav)

This project was made for our 3rd semester's academic project

This is how it looks

![Demo](https://media.giphy.com/media/f6IVaSWY3YqcWzZULL/giphy.gif)

## Grapical interface
As mentioned before we made it using openGL 
Drawing the pieces in openGL is advised using texture mapping as its much more effecient but as we were on tight schedule and getting bugs , we had to find a loophole.Also the structure of our code could allow us to try such a method without much delay in execution.

The above mentioned loophole are the files : 
- [printerb.cpp](https://github.com/TheForeverLost/GLChess/blob/master/printerb.cpp)<br>
- [printerw.cpp](https://github.com/TheForeverLost/GLChess/blob/master/printerw.cpp)<br>
- [PNG_to_pixelmap.ipynb](https://github.com/TheForeverLost/GLChess/blob/master/PNG_to_pixelmap.ipynb)

PNG_to_pixelmap.ipynb uses python file handling as well as Pillow Image library to read the images and produce the C++ files by printing GL c++ commands that produce the pieces.

## Running the game
It is important to run a program to check all possible legal moves which requires analysis into the rules of chess
As far as the AI is concerned , it uses a evaluation function which evaluates the cost of state of board after every move and then uses a minimax tree along with alpha beta pruning to find the best possible move.

### Possible updates
As of 4/4/19 <br>
1.The games still doesnt support pawn empassiant move so we hope to introduce that soon<br>
2.A proper graphical interface menu to make it more user friendly

Please feel free to suggest improvements


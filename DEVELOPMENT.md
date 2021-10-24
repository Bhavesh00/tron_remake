## Week 1: Exploration (4/4 - 4/9)
1. Since I am new to the idea of openFrameworks I began my exploration by reading the [openFrameworks structure](https://www.openframeworks.cc/ofBook/chapters/setup_and_project_structure.html) section of the openFrameworks book and getting a firm grasp of how openFrameworks was structured.
2. Furthermore, since I am building a video game I also read the [openFrameworks game design](https://openframeworks.cc/ofBook/chapters/game_design.html)
section of the openFrameworks and tried building some of the sample code they had provided in the section.
3. A significant add-on libraries I am using in this project is [ofxLight2D](https://github.com/bakercp/ofxLight2D), and I experimented with it 
by getting the example project to successfully build. The example project has a rotation flashlight that can be moved around the screen
using the mouse. There were also shadows in various parts of the screen because of the light source. Furthermore, I played around with 
various parameters such as the angle, color, and radius to see how it affected the lighting. I will be creating similar lights for my project, 
except they will be positioned in front of the motorcycles and will move along with them.
4. Because the other significant library I am using is the openFrameworks Sound library, I experimented with it by adding background
music and sounds to the of-snake program for extra credit. For example, I produced an eating sound whenever the snake ate a food block.
5. Finally, I also explored the add-on [ofxExplosion](https://github.com/armadillu/ofxExplosion) library that I might also use in my 
project if time permits. I tried to get the example project to succesfully build, but I kept running into compilation errors. However,
I have identified the issue to be a duplicate symbol error, and will be going to office hours to get some outside help in solving it.

## Week 2: Beginning of Development (4/10 - 4/17)
### Things Done:

4/14: 
1. Found artwork for the bike and edited it so that there were two bikes: a red one and a blue one.

4/15:
1. I was able to get the core bike movement mechanics to work so that one bike can be controlled with WASD and another can be
controlled with the arrow keys simultaneously.
2. Made background screen black and added background music to the game.
3. I prevented bikes from going off the screen by creating a method that checks the position and direction of the bike and then
stops the bike from moving if they are heading off the screen.

4/16:
1. Added red and blue light trails for the red and blue bikes respectively.

4/17:
1. Decomposed my code by adding a separate Bike class that contains helper functions and variables that significantly reduced the amount 
of repeated code and made my code easier to understand.
2. Allowed the game to be paused and unpaused when the 'P' key is pressed.
3. Added test cases for bike movement.

### Bugs Encountered:
1. The openframeworks rotate90 method did not work as I expected it to because it caused my bike to look out of proportion when 
I rotated the image. I fixed this by storing four separate images for each bike with each image containing the bike in a different direction.
2. I ran into a bug where only a single block for the light trail was being drawn at the current position. I realized that I needed to store 
the positions of all of the previous light trails. So I fixed this bug by storing all of the light trail positions in a vector of type ofVec2f and then
looped through the vector it in the draw() function and drew rectangles at the corresponding position.
3. Light trails are disconnected when the bike turns. This bug has not been fixed yet but I will be fixing it by looking into the coordinates and placing the loaded 
images in the correct spot.
4. I ran into a bug where the catch test suite does not run I get an error saying the following: "Error(s) in input: Unrecognised token: -N." 
I have not fixed the bug yet, but will be going to office hours to find a solution.

## Week 3: Continuing Development (4/17 - 4/24)
### Things Done:
4/21:
1. Make movement less choppy by having them centered at the stored position rather than drawing them at the stored position since 
openFrameworks takes the top left point of an image as the drawing point.
2. Fixed the light trails so that they are no longer disconnected when the bike turns.
3. I also fixed the boundary collisions to match the updated bike positions.
4. Removed various magic numbers in my code by turning them into constants.

4/22:
1. Added basic collision sensing so that the game stops when a bike runs into a light trail.
2. Modified the basic collision system to be a bit more advanced and handle some edge cases.
3. Added a explosion sound effect that is played when a bike crashes into a light trail or into an edge boundary.
4. Created a game over text that displays which player won the game. Used the ofTrueTypeFont library to customize the size and 
type of font used for the text.
5. Allowed the game to be restarted by pressing 'R' after the game has finished.

4/23:
1. Finished adding lights to the front of the bikes using the ofxLight2D add-on library.
2. Refined the collision system to further cover edge cases.

### Bugs Encountered:
1. The bike is able to turn when the game is paused. I fixed this bug by making sure the game state is not in pause when checking for
user input.
2. The game lags after a while when it is paused and unpaused. I fixed this bug by preventing the position of the paused light trail from
being continously added to the light trail position vector while the game is paused.
3. The basic collision system I implemented can be exploited by the player by turning onto the light trail since I am currently only checking
if the front tip of the bike is touching a light trail. I can patch this exploit by building a more advanced collision system by checking for
more points within the bike rather than just the front tip.
4. The lights were displayed in a circular shape eventhough I set the angle of the light. I then realized that I had to convert the 
angle measurement to radians using the ofDegToRad() method.

## Week 4: Finishing Up The Game (4/25 - 5/1)
4/30:
1. Made pause message that gets displayed when the game is paused.
2. Created a scoreboard that gets displayed when a player wins a round.
3. Added lighted obstacles that appear in random colors and ends the game when a player collides with them.

5/1:
1. Created a starting game menu that displays the Tron game logo as well as the muting / pausing controls. I decided to let the users 
press 'G' to begin the game rather than having a button that they would have to click.
2. Allowed the players to mute/unmute game sounds and music by pressing 'M'.
3. Removed magic numbers from the code and turned them into constants in the header file.
4. Moved the offset constants to a separate header file in order to organize the constants in the ofApp.h header file.
5. Decomposed various parts of my code by adding helper methods in the ofApp.cpp file.
6. Added tests for various helper methods that check for collisions to make sure they are functioning properly.

### Bugs Encountered:
1. The game displays various elements at the wrong location when the game is run on a different size screen than my MacBook Pro.
I can fix this bug by making sure that the elements are drawn relative to the width and height of the screen by using ofGetWidth() and
ofGetHeight(), as well as constant offsets.
2. The obstacles were not creating shadows as seen in the ofxLight2D demo video. It might be a compatability issue with the operating 
system's  version of openGL since I am using MacBook Pro, but I am not completely sure. I decided to do a workaround by creating
my own light under each of the obstacles of the same color as the obstacle.
3. The obstacles when added are placed above the bikes so that the bikes are sometimes hidden under the obstacles. This issue 
occurs because the light system from the ofxLight2D library has its own draw method that automatically gets called under the hood which 
means that the light obstacle gets drawn above the bike each frame. It cannot be changed since the bikes cannot be added to the light
system since they are not light objects.
4. When adding tests, I was not able to create tests for certain helper methods in ofApp.h since they were declared private. I was able
to fix this by making both the helper functions I was testing and certain variables public and static in the ofApp.h header file.

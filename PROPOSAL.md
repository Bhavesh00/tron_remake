# Final Project Proposal
## Overview
The project that I am planning on creating is a 2D Tron motorcycle game similar to the original 
[arcade game](https://tron.fandom.com/wiki/TRON_(arcade_game)?file=Tron_Arcade_Lightcycles.png). 
The way the game will work is that there will be two Tron motorcycles that have continuous
light trails behind them as they move across the screen. If a player runs into their own light trail
into the opponent's light trail, into an obstacle, or an edge boundary, they will die and lose the game.

## Inspiration
The inspiration for this Tron game comes from the of-snake example since there is a somewhat similar mechanic - the
player cannot run into their own light trail that they create from their motorcycle. Furthermore, I really enjoyed playing the Tron arcade
games when I was younger, so I am inspired to build a version that has more features and better graphics by using openFrameworks.

## Game Features
1. Local Multiplayer mode that will allow the user to play with a friend on the same device by using WASD and the arrow keys.
2. Game menu screen that will let the player start the game by pressing 'G'.
3. Tron motorcycles will have a bright trail behind them as well as a headlight shining in front of them. Therefore, shadow-like effects will 
appear from the lighting in the game screen.
4. Background music will be playing throughout the game with the option to turn it off by pressing 'M'.
5. The game can be paused and unpaused by pressing 'P' during the game.
6. Explosion sound when bike crashes into a light trail, boundary edges, or a obstacle which is followed by a game over screen that will 
allow the user to play the game again,

## Libraries That Will Be used:
1. Core 2D graphics library from openFrameworks in order to display various images and fonts for the game.
2. Core Sound library from openFrameworks in order to create background sounds and music for the game.
3. Add-on [ofxLight2D library](https://github.com/bakercp/ofxLight2D) for openFrameworks in order to create the lighting for the 
headlight of the motorcycle and possibly for the trail behind them as well. This library also also provides the shadows that will be used 
throughout the game screen.

## Other Features/Libraries If Time Permits:
1. Creating a scoreboard that keeps track of the player scores.
2. Lighted obstacles of random colors present on the screen that will force players to move around them. 
3. Using the add-on [ofxExplosion](https://github.com/armadillu/ofxExplosion) library for openFrameworks to create an explosion 
animation whenever a motorcycle crashes into a light trail.
4. Creating a scoreboard keeping track of the player scores.
5. Allowing players to have up to three lives, and respawning their motorcycles if they still have a life remaining.
6. Single player mode that will allow the user to play against a motorcycle controlled by a basic AI.

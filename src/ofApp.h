// Created by Bhaveshkumar Manivannan (bm12).

#pragma once

#include "ofMain.h"
#include "bike.h"
#include "LightSystem2D.h"
#include "offset_constants.h"

class ofApp : public ofBaseApp {
  private:
    const float center_x = ofGetWidth() / 2;
    const float center_y = ofGetHeight() / 2;
    const float red_bike_starting_x = 50;
    const float red_bike_starting_y = 100;
    const float blue_bike_starting_x = ofGetWidth() - 50;
    const float blue_bike_starting_y = ofGetHeight() - 100;
    const float text_x_position = 520;
    const float bike_light_view_angle_degrees = 90; // View angle of the light.
    const float bike_light_angle_right = 0; // Angle when light faces right.
    const float bike_light_angle_down = 90; // Angle when light faces down.
    const float bike_light_angle_left = 180; // Angle when light faces left.
    const float bike_light_angle_up = 270; // Angle when light faces up.
    const float font_line_height = 34.0f;
    const float font_letter_spacing = 1.035; // Spacing between letters.
    const float obstacle_dimension_half = 25;
    const float obstacle_light_radius = 450; // Radius of the light present under the obstacle.
  
    const int bike_width = 88;
    const int bike_height = 38;
    const int game_logo_width = 550;
    const int game_logo_height = 238;
    const int background_gradient_start = 10; // Used in setting the background color of the screen.
    const int red_trail_r_color = 255;
    const int red_trail_g_color = 7;
    const int red_trail_b_color = 7;
    const int blue_trail_r_color = 24;
    const int blue_trail_g_color = 202;
    const int blue_trail_b_color = 230;
    const int rgb_white = 255;
    const int font_size = 30; // The overall size of the font.
    const int font_dpi = 72; // Number of pixel dots per inch for the fonts.
  
    static const int screen_width = 1440;
    static const int screen_height = 900;
    static const int steps = 10; // The number of pixels the bike moves each frame.
    static const int steps_half = 5;
    static const int bike_width_half = 44;
    static const int bike_height_half = 19;
    static const int obstacle_dimension = 50; // Square dimension of the obstacle.
  
    std::string game_over_message; // This game over message displays the winner.
    ofImage game_logo;
    ofSoundPlayer background_music;
    ofSoundPlayer explosion_sound;
    ofTrueTypeFont verdana_font;
    ofx::LightSystem2D light_system;
    std::vector<ofVec2f> obstacle_positions;
    Bike red_bike{red_bike_starting_x, red_bike_starting_y, Bike::RIGHT, "red_bike_up.png", "red_bike_down.png",
      "red_bike_right.png", "red_bike_left.png"};
    Bike blue_bike{blue_bike_starting_x, blue_bike_starting_y, Bike::LEFT, "blue_bike_up.png", "blue_bike_down.png",
      "blue_bike_right.png", "blue_bike_left.png"};
  
    // This 2D bool vector stores true if the corresponding position has a collision, and false otherwise.
    bool collisions[screen_width][screen_height] = {false};
  
    // This boolean stores the state of the game mute option so that it can be toggled by the player.
    bool game_mute = false;
  
    // This enum was taken from the ofsnake example and it defines the possible states that the game can be in.
    typedef enum {
      GAME_MENU = 0,
      GAME_START,
      GAME_PAUSE,
      GAME_OVER
    } GameState;
  
    GameState game_state;
  
    // This function draws the bike for the appropriate direction and position. It takes in a Bike object.
    void drawBike(Bike bike);
  
    // This function draws a bike light in front of a bike. It takes in a Bike object, the x and y position where the
    // light should be drawn, and the angle that the light should be facing.
    void drawBikeLight(Bike bike, float x_position, float y_position, float light_angle);
  
    // This function draws the trail following the bike. It takes in a Bike object.
    void drawBikeTrail(Bike bike);
  
    // This function draws the game menu screen.
    void drawGameMenu();
  
    // This function draws the game paused screen.
    void drawGamePaused();
  
    // This function draws the game over screen.
    void drawGameOver();
  
    // This function draws four obstacles (Shape2D objects) on the screen with lights placed under them.
    void drawObstacles();
  
    // This function checks for game over instances such as the bikes running into the wall boundaries or into a
    // light trail.
    void handleGameOver();
  
    // This function handles the WASD and arrow key movements that the players press. It also makes sure that the player
    // can't move in the 180 degrees from the current direction. It takes in the value of the key pressed.
    void handleMovementKeys(int key);
  
    // Reset the game so that it can be played again.
    void reset();
  
    // This functions resets the positions and directions of the bikes.
    void resetPositionAndDirection();
  
    // This function resets the collisions bool array so that it only stores false values.
    void resetCollisions();
  
  public:
    // openFrameworks Core Functions.
    void setup();
    void update();
    void draw();
  
    // openFrameworks Event Handlers.
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
  
    // This function checks if a bike has gone off one of the four sides of the screen. It takes in the x and y position
    // of the bike and takes in the current direction of the bike. Returns true if it did go off the screen, and false
    // otherwise.
    static bool isBikeOffScreen(float x, float y, Bike::BikeDirection current_direction);
  
    // This function checks if a bike has collided with a light trail or an obstacle. It takes in a Bike object and
    // a 2D bool array storing the collisions. It returns true if the Bike has collided with a light trail, and false
    // otherwise.
    static bool bikeCollidingWithObject(Bike bike, bool collisions[screen_width][screen_height]);
  
    // This function sets the points within the obstacles to true in the collision boolean array. It takes in a vector
    // containing all the obstacle positions and a 2D bool array storing the collisions.
    static void addObstacleCollisions(std::vector<ofVec2f> obstacle_positions, bool collisions[screen_width][screen_height]);
  
    // This function sets the points within the bike light trail to true in the collision boolean array. It takes in a
    // Bike object and a 2D bool array storing the collisions.
    static void addLightTrailCollisions(Bike bike, bool collisions[screen_width][screen_height]);
};

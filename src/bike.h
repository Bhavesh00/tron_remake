// Created by Bhaveshkumar Manivannan (bm12).
#ifndef bike_h
#define bike_h

#include "ofMain.h"
#include "ofImage.h"
#include "ofVec2f.h"
#include "LightSystem2D.h"

class Bike {
  public:
    const int steps = 10; // The number of steps the bike moves each tick.
  
    ofVec2f position; // The current position of the bike.
    ofImage bike_image; // The image for the bike.
    bool direction_updated = false; // This stores whether or not the direction of the bike was updated in the last tick.
    std::vector<ofVec2f> trail_positions; // This stores all of the light trail positions that are on the window.
    ofx::Light2D::SharedPtr light; // This is the light in front of the bike.
    int score = 0;
  
    // The following strings store the different images for the bike.
    std::string up_image;
    std::string down_image;
    std::string right_image;
    std::string left_image;
  
    // This enum was taken from the ofsnake example and it defines the possible directions that the bike can be in.
    typedef enum {
      UP = 0,
      DOWN,
      RIGHT,
      LEFT
    } BikeDirection;
  
    BikeDirection direction; // Stores the bike's current direction.
  
    // Constructors.
    Bike();
    Bike(float start_x, float start_y, Bike::BikeDirection start_dir, std::string up_image, std::string down_image,
         std::string right_image, std::string left_image);
  
    // This function updates the position of the bike.
    void move();
};

#endif /* bike_h */

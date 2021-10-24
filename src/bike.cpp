// Created by Bhaveshkumar Manivannan (bm12).

#include "bike.h"

using std::string;

// Default constructor.
Bike::Bike() {};

Bike::Bike(float start_x, float start_y, Bike::BikeDirection start_dir, string up_image, string down_image,
           string right_image, string left_image) {
  // Initialize values.
  position = ofVec2f(start_x, start_y);
  direction = start_dir;
  this->up_image = up_image;
  this->down_image = down_image;
  this->right_image = right_image;
  this->left_image = left_image;
}

void Bike::move() {
  // Check the various directions and change the position by steps accordingly.
  if (direction == UP) {
    position = ofVec2f(position.x, position.y - steps);
  } else if (direction == DOWN) {
    position = ofVec2f(position.x, position.y + steps);
  } else if (direction == RIGHT) {
    position = ofVec2f(position.x + steps, position.y);
  } else if (direction == LEFT) {
    position = ofVec2f(position.x - steps, position.y);
  }
}

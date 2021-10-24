// Created by Bhaveshkumar Manivannan (bm12).
// This class tests the Tron Game.
#define CATCH_CONFIG_RUNNER
#include <stdio.h>
#include "catch.hpp"
#include "ofApp.h"
#include "ofApp.cpp"
#include "bike.h"
#include "bike.cpp"
#include "LightSystem2D.h"

// This main class was inspired by this CS 126 Piazza post: https://piazza.com/class/jqsxr0jwnw95wu?cid=1395
int main (int argc, char* argv[]) {
  int result = Catch::Session().run(1, argv);
  return result;
}

// The following tests check if the Bike movement is functioning properly.
TEST_CASE("Bike Move Right", "[bike_move_right]") {
  Bike bike{0, 240, Bike::RIGHT, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  bike.move();
  REQUIRE(bike.position.x == 10);
}

TEST_CASE("Bike Move Left", "[bike_move_left]") {
  Bike bike{20, 240, Bike::LEFT, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  bike.move();
  REQUIRE(bike.position.x == 10);
}

TEST_CASE("Bike Move Up", "[bike_move_up]") {
  Bike bike{0, 240, Bike::UP, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  bike.move();
  REQUIRE(bike.position.y == 230);
}

TEST_CASE("Bike Move Down", "[bike_move_down]") {
  Bike bike{0, 240, Bike::DOWN, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  bike.move();
  REQUIRE(bike.position.y == 250);
}

// The following tests check if the isBikeOffScreen(...) method is functioning properly.
TEST_CASE("Bike Off Screen Up", "[bike_off_screen_up]") {
  Bike bike{0, -50, Bike::UP, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  REQUIRE(ofApp::isBikeOffScreen(bike.position.x, bike.position.y, bike.direction));
}

TEST_CASE("Bike Off Screen Down", "[bike_off_screen_down]") {
  Bike bike{0, 950, Bike::DOWN, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  REQUIRE(ofApp::isBikeOffScreen(bike.position.x, bike.position.y, bike.direction));
}

TEST_CASE("Bike Off Screen Left", "[bike_off_screen_left]") {
  Bike bike{-50, 0, Bike::LEFT, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  REQUIRE(ofApp::isBikeOffScreen(bike.position.x, bike.position.y, bike.direction));
}

TEST_CASE("Bike Off Screen Right", "[bike_off_screen_left]") {
  Bike bike{1490, 0, Bike::RIGHT, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  REQUIRE(ofApp::isBikeOffScreen(bike.position.x, bike.position.y, bike.direction));
}

// The following test checks if the bikeCollidingWithObject(...) method is functioning properly.
TEST_CASE("Bike Colliding With Object", "[bike_colliding_with_object]") {
  bool collisions[1440][900] = {false};
  Bike bike{500, 500, Bike::RIGHT, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  collisions[500][500] = true;
  REQUIRE(ofApp::bikeCollidingWithObject(bike, collisions));
}

// The following tests check if addObstacleCollisions(...) method is functioning properly.
TEST_CASE("Add Obstacle Collisions", "[add_obstacle_collisions]") {
  bool collisions[1440][900] = {false};
  std::vector<ofVec2f> obstacle_positions;
  obstacle_positions.push_back(ofVec2f(500, 500));
  ofApp::addObstacleCollisions(obstacle_positions, collisions);
  REQUIRE(collisions[500][500]);
}

// The following tests check if addLightTrailCollisions(...) method is functioning properly.
TEST_CASE("Add Light Trail Collisions", "[add_light_trail_collisions]") {
  Bike bike{500, 500, Bike::RIGHT, "red_bike_up.png", "red_bike_down.png", "red_bike_right.png", "red_bike_left.png"};
  bool collisions[1440][900] = {false};
  ofApp::addLightTrailCollisions(bike, collisions);
  REQUIRE(collisions[500][500]);
  REQUIRE(collisions[504][500]);
}

// Created by Bhaveshkumar Manivannan (bm12).

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Set the game state
  game_state = GAME_MENU;
  
  // Set the background color.
  ofBackgroundGradient(ofColor(background_gradient_start), ofColor(0));
  
  // Load the background music.
  background_music.load("Daft Punk-Derezzed.mp3");
  background_music.setLoop(true);
  background_music.play();
  
  // Add the obstacles to the screen.
  drawObstacles();
  
  // Load the images for the bikes.
  red_bike.bike_image.load("red_bike_right.png");
  blue_bike.bike_image.load("blue_bike_left.png");
  
  // Load the game logo image.
  game_logo.load("Tron-logo.png");
  
  // Load the explosion sound effect.
  explosion_sound.load("explosion.mp3");
  
  // Add the bike lights to the light system.
  red_bike.light = std::make_shared<ofx::Light2D>();
  blue_bike.light = std::make_shared<ofx::Light2D>();
  light_system.add(red_bike.light);
  light_system.add(blue_bike.light);
  
  // Load the font used in the game over screen. The following four lines of code was taken from the openFrameworks
  // "fontExample" program that was provided with the openFrameworks downloaded package.
  ofTrueTypeFont::setGlobalDpi(font_dpi);
  verdana_font.load("verdana.ttf", font_size, true, true);
  verdana_font.setLineHeight(font_line_height);
  verdana_font.setLetterSpacing(font_letter_spacing);
}

//--------------------------------------------------------------
void ofApp::update() {
  // Check to make sure that the game has started.
  if (game_state == GAME_START) {
    // Check to make sure the red bike is in the screen.
    if (!isBikeOffScreen(red_bike.position.x, red_bike.position.y, red_bike.direction)) {
      red_bike.move();
    }
    
    // Check to make sure the blue bike is in the screen.
    if (!isBikeOffScreen(blue_bike.position.x, blue_bike.position.y, blue_bike.direction)) {
      blue_bike.move();
    }
    
    // Add the light trail positions to the light trail position vectors.
    red_bike.trail_positions.push_back(ofVec2f(red_bike.position.x - steps_half, red_bike.position.y - steps_half));
    blue_bike.trail_positions.push_back(ofVec2f(blue_bike.position.x - steps_half, blue_bike.position.y - steps_half));
    
    // Check if a game over scenario has occurred.
    handleGameOver();
    
    // Add all of the points within the current red bike light trail to the collisions array.
    addLightTrailCollisions(red_bike, collisions);
    
    // Add all of the points within the current blue bike light trail to the collisions array.
    addLightTrailCollisions(blue_bike, collisions);
    
    // Add the points within the obstacles to the collision array.
    addObstacleCollisions(obstacle_positions, collisions);
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Set the background color.
  ofBackgroundGradient(ofColor(background_gradient_start), ofColor(0));
  
  // Draw the red bike trail.
  ofFill();
  ofSetColor(red_trail_r_color, red_trail_g_color, red_trail_b_color);
  drawBikeTrail(red_bike);
  
  // Draw the blue bike trail.
  ofSetColor(blue_trail_r_color, blue_trail_g_color, blue_trail_b_color);
  drawBikeTrail(blue_bike);
  
  // Reset the openFrameworks drawing color.
  ofSetColor(rgb_white, rgb_white, rgb_white);
  
  // Handle drawing the red bike.
  drawBike(red_bike);
  
  // Handle drawing the blue bike.
  drawBike(blue_bike);
  
 if (game_state == GAME_MENU) {
    // Display the game menu screen.
    drawGameMenu();
  } else if (game_state == GAME_PAUSE) {
    // Display the game paused message.
    drawGamePaused();
    
  } else if (game_state == GAME_OVER) {
    // Display the game over message.
    drawGameOver();
  }
}

//--------------------------------------------------------------
void ofApp::drawBike(Bike bike) {
  // Check if the bike's direction was updated in the last frame in order to prevent lag from loading images.
  if (bike.direction_updated) {
    // Load the bike images and draw them.
    if (bike.direction == Bike::UP) {
      bike.bike_image.load(bike.up_image);
      bike.bike_image.draw(bike.position.x - bike_height_half, bike.position.y - bike_width_half, bike_height, bike_width);
      drawBikeLight(bike, bike.position.x, bike.position.y - bike_width_half, bike_light_angle_up);
      
    } else if (bike.direction == Bike::DOWN) {
      bike.bike_image.load(bike.down_image);
      bike.bike_image.draw(bike.position.x - bike_height_half, bike.position.y - bike_width_half, bike_height, bike_width);
      drawBikeLight(bike, bike.position.x, bike.position.y + bike_width_half, bike_light_angle_down);
      
    } else if (bike.direction == Bike::RIGHT) {
      bike.bike_image.load(bike.right_image);
      bike.bike_image.draw(bike.position.x - bike_width_half, bike.position.y - bike_height_half, bike_width, bike_height);
      drawBikeLight(bike, bike.position.x + bike_width_half, bike.position.y, bike_light_angle_right);
      
    } else if (bike.direction == Bike::LEFT) {
      bike.bike_image.load(bike.left_image);
      bike.bike_image.draw(bike.position.x - bike_width_half, bike.position.y - bike_height_half, bike_width, bike_height);
      drawBikeLight(bike, bike.position.x - bike_width_half, bike.position.y, bike_light_angle_left);
    }
    bike.direction_updated = false;
    
  } else if (bike.direction == Bike::UP || bike.direction == Bike::DOWN) {
    // Draw the vertically-oriented bike images. This will prevent the bike from being loaded every frame if the
    // direction has not changed.
    bike.bike_image.draw(bike.position.x - bike_height_half, bike.position.y - bike_width_half, bike_height, bike_width);
    if (bike.direction == Bike::UP) {
      drawBikeLight(bike, bike.position.x, bike.position.y - bike_width_half, bike_light_angle_up);
    } else {
      drawBikeLight(bike, bike.position.x, bike.position.y + bike_width_half, bike_light_angle_down);
    }
    
  } else {
    // Draw the horizontally-oriented bike images. This will prevent the bike from being loaded every frame if the
    // direction has not changed.
    bike.bike_image.draw(bike.position.x - bike_width_half, bike.position.y - bike_height_half, bike_width, bike_height);
    if (bike.direction == Bike::RIGHT) {
      drawBikeLight(bike, bike.position.x + bike_width_half, bike.position.y, bike_light_angle_right);
    } else {
      drawBikeLight(bike, bike.position.x - bike_width_half, bike.position.y, bike_light_angle_left);
    }
  }
}

//--------------------------------------------------------------
void ofApp::drawBikeLight(Bike bike, float x_position, float y_position, float light_angle) {
  // Update the bike's light so it can be drawn automatically by the light system in the next frame.
  bike.light->setPosition(ofVec3f(x_position, y_position));
  bike.light->setViewAngle(ofDegToRad(bike_light_view_angle_degrees));
  bike.light->setAngle(ofDegToRad(light_angle));
}

//--------------------------------------------------------------
void ofApp::drawBikeTrail(Bike bike) {
  // Loop through the bike's trail positions vector and draw rectangles at each position.
  for (int i = 0; i < bike.trail_positions.size(); i++) {
    ofDrawRectangle(bike.trail_positions[i], steps, steps);
  }
}

//--------------------------------------------------------------
void ofApp::drawGameMenu() {
  // Display the game menu.
  game_logo.draw(center_x- game_logo_horizontal_offset, center_y - game_logo_vertical_offset,
                 game_logo_width, game_logo_height);
  verdana_font.drawString("Press 'G' to Play.", center_x - play_message_horizontal_offset,
                          play_message_vertical_offset);
  verdana_font.drawString("Press 'M' to mute all sounds and 'P' to pause the game.", center_x -
                          mute_message_horizontal_offset, mute_message_vertical_offset);
}

//--------------------------------------------------------------
void ofApp::drawGamePaused() {
  // The following line of code was taken from the openFrameworks "fontExample" program that was provided with the
  // openFrameworks downloaded package.
  verdana_font.drawString("Game Paused. Press 'P' to Unpause.", center_x - game_paused_message_horizontal_offset,
                          center_y);
}

//--------------------------------------------------------------
void ofApp::drawGameOver() {
  // The following line of code was taken from the openFrameworks "fontExample" program that was provided with the
  // openFrameworks downloaded package.
  verdana_font.drawString(game_over_message, center_x - game_over_message_horizontal_offset,
                          game_over_message_vertical_offset);
  
  // Display the player scores below the game over message.
  verdana_font.drawString("Red Score: " + to_string(red_bike.score), center_x - red_score_horizontal_offset,
                          score_vertical_offset);
  verdana_font.drawString("Blue Score: " + to_string(blue_bike.score), center_x + blue_score_horizontal_offset,
                          score_vertical_offset);
}

//--------------------------------------------------------------
void ofApp::drawObstacles() {
  // Store the obstacle positions in the vector. The obstacles are located at four separate corners.
  obstacle_positions.push_back(ofVec2f(red_bike_starting_x + obstacle_horizontal_offset, red_bike_starting_y +
                                       obstacle_vertical_offset));
  obstacle_positions.push_back(ofVec2f(red_bike_starting_x + obstacle_horizontal_offset, blue_bike_starting_y -
                                       obstacle_vertical_offset));
  obstacle_positions.push_back(ofVec2f(blue_bike_starting_x - obstacle_horizontal_offset - obstacle_dimension,
                                       blue_bike_starting_y - obstacle_vertical_offset));
  obstacle_positions.push_back(ofVec2f(blue_bike_starting_x - obstacle_horizontal_offset - obstacle_dimension,
                                       red_bike_starting_y + obstacle_vertical_offset));
  
  // Loop through the vector of obstacle positions and add the obstacles with lights at the corresponding positions
  // to the screen.
  for (int i = 0; i < obstacle_positions.size(); i++) {
    // Display the square obstacle in a random color. The following lines of code were referenced from the ofxLight2D
    // add-on provided example program.
    ofx::Shape2D::SharedPtr obstacle = std::make_shared<ofx::Shape2D>();
    ofFloatColor obstacle_color(ofRandomuf(), ofRandomuf(), ofRandomuf(), 1);
    obstacle->setColor(obstacle_color);
    ofRectangle obstacle_rect(obstacle_positions[i], obstacle_dimension, obstacle_dimension);
    obstacle->setShape(ofPolyline::fromRectangle(obstacle_rect));
    
    // Add the obstacle to the light system.
    light_system.add(obstacle);
    
    // Place lights under the obstacles to create an artificial shadow-like effect.
    ofx::Light2D::SharedPtr obstacle_light = std::make_shared<ofx::Light2D>();
    ofVec3f position(obstacle_positions[i].x + obstacle_dimension_half, obstacle_positions[i].y + obstacle_dimension_half, 
                     0);
    obstacle_light->setPosition(position);
    obstacle_light->setRadius(obstacle_light_radius);
    obstacle_light->setColor(obstacle_color);
    
    // Add the obstacle light to the light system.
    light_system.add(obstacle_light);
  }
}

//--------------------------------------------------------------
void ofApp::addObstacleCollisions(vector<ofVec2f> obstacle_positions, bool collisions[screen_width][screen_height]) {
  // Loop through the list of obstacle positions.
  for (int i = 0; i < obstacle_positions.size(); i++) {
    // Update the collisions array with all of the points within the obstacles.
    for (int x = (int) (obstacle_positions[i].x); x < (int) (obstacle_positions[i].x + obstacle_dimension); x++) {
      for (int y = (int) (obstacle_positions[i].y); y < (int) (obstacle_positions[i].y + obstacle_dimension); y++) {
        collisions[x][y] = true;
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::addLightTrailCollisions(Bike bike, bool collisions[screen_width][screen_height]) {
  // Loop through the points in the light trail rectangle at the current position and set them to true in the collisions
  // array.
  for (int x = (int) (bike.position.x - steps_half); x < (int) (bike.position.x - steps_half + steps); x++) {
    for (int y = (int) (bike.position.y - steps_half); y < (int) (bike.position.y - steps_half + steps); y++) {
      collisions[x][y] = true;
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  // Work with only uppercase versions of the keyboard.
  key = toupper(key);
  
  // Process User Input for movement, making sure that the player can't move in the 180 degrees from the current
  // direction.
  if (game_state == GAME_START) {
    handleMovementKeys(key);
  }
  
  if (key == 'P') {
    // The game will be paused and unpaused when the 'P' key is pressed.
    if (game_state == GAME_PAUSE) {
      // The game is already paused, so unpause if the game isn't muted.
      if (!game_mute) {
        background_music.setPaused(false);
      }
      game_state = GAME_START;
      
    } else if (game_state == GAME_START) {
      // The game is not over yet, so pause the game.
      game_state = GAME_PAUSE;
      background_music.setPaused(true);
    }
    
  } else if (key == 'R' && game_state == GAME_OVER) {
    // The game will be reset when the 'R' key is pressed and the game is already over.
    reset();
    
  } else if (key == 'M') {
    // The game music and sounds will be muted and unmuted when the 'M' key is pressed.
    if (!game_mute) {
      // Mute the music.
      background_music.setPaused(true);
      game_mute = true;
    } else {
      // Unmute the music.
      background_music.setPaused(false);
      game_mute = false;
    }
    
  } else if (key == 'G') {
    // The game will progress from the game menu and start playing when the 'G' key is pressed.
    if (game_state == GAME_MENU) {
     game_state = GAME_START;
    }
  }
}

//--------------------------------------------------------------
bool ofApp::isBikeOffScreen(float x, float y, Bike::BikeDirection current_direction) {
  // Use the current direction to check the corresponding sides of the screen.
  if (current_direction == Bike::RIGHT && x + bike_width_half + steps >= screen_width) {
    return true;
    
  } else if (current_direction == Bike::LEFT && x - bike_width_half - steps <= 0) {
    return true;
    
  } else if (current_direction == Bike::UP && y - bike_width_half - steps <= 0) {
    return true;
    
  } else if (current_direction == Bike::DOWN && y + bike_width_half + steps >= screen_height) {
    return true;
  }
  return false;
}
        
//--------------------------------------------------------------
bool ofApp::bikeCollidingWithObject(Bike bike, bool collisions[screen_width][screen_height]) {
  // Check if a bike is touching a collision square in its current direction.
  if (bike.direction == Bike::RIGHT) {
    // Loop through and check if the bike is colliding with a collision square.
    for (int x = (int) (bike.position.x); x <= (int) (bike.position.x + bike_width_half + steps); x++) {
      if (collisions[x][(int) bike.position.y]) {
        return true;
      }
    }
    
  } else if (bike.direction == Bike::LEFT) {
    // Loop through and check if the bike is colliding with a collision square.
    for (int x = (int) (bike.position.x - bike_width_half - steps); x <= (int) (bike.position.x); x++) {
      if (collisions[x][(int) bike.position.y]) {
        return true;
      }
    }
    
  } else if (bike.direction == Bike::UP) {
    // Loop through and check if the bike is colliding with a collision square.
    for (int y = (int) (bike.position.y - bike_width_half - steps); y <= (int) (bike.position.y); y++) {
      if (collisions[(int) bike.position.x][y]) {
        return true;
      }
    }
    
  } else if (bike.direction == Bike::DOWN) {
    // Loop through and check if the bike is colliding with a collision square.
    for (int y = (int) (bike.position.y); y <= (int) (bike.position.y + bike_width_half + steps); y++) {
      if (collisions[(int) bike.position.x][y]) {
        return true;
      }
    }
  }
  return false;
}

//--------------------------------------------------------------
void ofApp::handleGameOver() {
  // Check if the red or blue bike has ran into the edge boundary or an object.
  if (isBikeOffScreen(red_bike.position.x, red_bike.position.y, red_bike.direction) ||
      bikeCollidingWithObject(red_bike, collisions)) {
    // Play the explosion sound if teh game is not muted.
    if (!game_mute) {
      explosion_sound.play();
    }
    
    // Increment score and display game over message.
    game_state = GAME_OVER;
    blue_bike.score++;
    game_over_message = "The blue player has won. Press 'R' to play again.";

  } else if (isBikeOffScreen(blue_bike.position.x, blue_bike.position.y, blue_bike.direction) ||
             bikeCollidingWithObject(blue_bike, collisions)) {
    // Play the explosion sound if the game is not muted.
    if (!game_mute) {
      explosion_sound.play();
    }
    
    // Increment score and display game over message.
    game_state = GAME_OVER;
    red_bike.score++;
    game_over_message = "The red player has won. Press 'R' to play again.";
  }
}

//--------------------------------------------------------------
void ofApp::handleMovementKeys(int key) {
  // Handle the WASD keys.
  if (key == 'W' && red_bike.direction != Bike::DOWN) {
    red_bike.direction = Bike::UP;
    red_bike.direction_updated = true;
    
  } else if (key == 'A' && red_bike.direction != Bike::RIGHT) {
    red_bike.direction = Bike::LEFT;
    red_bike.direction_updated = true;
    
  } else if (key == 'S' && red_bike.direction != Bike::UP) {
    red_bike.direction = Bike::DOWN;
    red_bike.direction_updated = true;
    
  } else if (key == 'D' && red_bike.direction != Bike::LEFT) {
    red_bike.direction = Bike::RIGHT;
    red_bike.direction_updated = true;
  }
  
  // Handle the arrow keys.
  if (key == OF_KEY_UP && blue_bike.direction != Bike::DOWN) {
    blue_bike.direction = Bike::UP;
    blue_bike.direction_updated = true;
    
  } else if (key == OF_KEY_LEFT && blue_bike.direction != Bike::RIGHT) {
    blue_bike.direction = Bike::LEFT;
    blue_bike.direction_updated = true;
    
  } else if (key == OF_KEY_DOWN && blue_bike.direction != Bike::UP) {
    blue_bike.direction = Bike::DOWN;
    blue_bike.direction_updated = true;
    
  } else if (key == OF_KEY_RIGHT && blue_bike.direction != Bike::LEFT) {
    blue_bike.direction = Bike::RIGHT;
    blue_bike.direction_updated = true;
  }
}

//--------------------------------------------------------------
void ofApp::reset() {
  // Reset the position and direction of the bikes.
  resetPositionAndDirection();
  
  // Clear the vectors storing the light trail positions for each bike.
  red_bike.trail_positions.clear();
  blue_bike.trail_positions.clear();
  
  // Reset the collisions bool array so that it only contains false values.
  resetCollisions();
  
  // Reset game over message to empty string.
  game_over_message = "";
  
  // Update the game state.
  game_state = GAME_START;
}

//--------------------------------------------------------------
void ofApp::resetPositionAndDirection() {
  // Set the values to their starting values.
  red_bike.position.x = red_bike_starting_x;
  red_bike.position.y = red_bike_starting_y;
  red_bike.direction = Bike::RIGHT;
  blue_bike.position.x = blue_bike_starting_x;
  blue_bike.position.y = blue_bike_starting_y;
  blue_bike.direction = Bike::LEFT;
}

//--------------------------------------------------------------
void ofApp::resetCollisions() {
  // Reset the collisions bool array so that it only contains false values.
  for (int x = 0; x < screen_width; x++) {
    for (int y = 0; y < screen_height; y++) {
      collisions[x][y] = false;
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
  
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
  
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
  
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
  
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
  
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
  
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
  
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
  
}

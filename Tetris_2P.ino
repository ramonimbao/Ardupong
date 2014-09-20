#include <TVout.h>
//#include <fontALL.h>

TVout TV;

int P1_PIN = A0;
int P2_PIN = A1;

int P1_y = 0;
int P2_y = 0;

int P1_SCORE = 0;
int P2_SCORE = 0;

// W = 128, H = 96
//center the ball
int BALL_X = 64;
int BALL_Y = 48;

int BALL_XDIR = 1;
int BALL_YDIR = 1;
// 00 = down-left
// 01 = down-right
// 10 = up-left
// 11 = up-right

void setup() {
  TV.begin(_NTSC);
  Serial.begin(9600);
  
  randomSeed(analogRead(A5));
  
  // Choose a new random direction for the ball
  BALL_XDIR *= (random(2) == 1 ? -1 : 1);
  BALL_YDIR *= (random(2) == 1 ? -1 : 1);
  
  delay(2000);
}

void loop() {
  P1_y = min(analogRead(P1_PIN) / 1023.0 * 80.0, 80);
  P2_y = min(analogRead(P2_PIN) / (1023.0 * 3.3 / 5.0) * 80.0, 80);
  
  /*Serial.print("P1: ");
  Serial.println(P1_y);
  Serial.print("P2: ");
  Serial.println(P2_y);*/
  
  
  // Clear screen
  TV.clear_screen();
  
  // draw P1's paddle
  TV.draw_rect(4, P1_y, 2, 16, WHITE);
  
  // draw P2's paddle
  TV.draw_rect(122, P2_y, 2, 16, WHITE);
  
  // draw the middle
  for (int _y = 0; _y < 96; _y += 8) {
    TV.draw_rect(63, _y, 2, 4, WHITE);
  }
  
  // draw the scores
  TV.print(29, 7, P1_SCORE);
  TV.print(49, 7, P2_SCORE);
  
  // draw the ball
  TV.draw_rect(BALL_X, BALL_Y, 2, 2, INVERT);
  
  // move the ball
  BALL_X += BALL_XDIR;
  BALL_Y += BALL_YDIR;
  
  // handle collision checks
  // upper and lower walls
  if (BALL_Y < 0) {
    BALL_Y = 0;
    BALL_YDIR = -BALL_YDIR;
  }
  
  if (BALL_Y > 128) {
    BALL_Y = 128;
    BALL_YDIR = -BALL_YDIR;
  }
  
  // P1 paddle
  if (BALL_X == 5) {
    if (BALL_Y >= P1_y && BALL_Y <= P1_y + 16) {
      BALL_X = 6;
      BALL_XDIR = -BALL_XDIR;
    }
  }
  
  // P2 paddle
  if (BALL_X == 122) {
    if (BALL_Y >= P2_y && BALL_Y <= P2_y + 16) {
      BALL_X = 121;
      BALL_XDIR = -BALL_XDIR;
    }
  }
  
  // left wall
  if (BALL_X < 0) {
    score(2);
  }
  
  if (BALL_X > 128) {
    score(1);
  }
  

  // delay
  TV.delay(60);
  
}

void score(int player) {
  BALL_X = 64;
  BALL_Y = 48;
  
  if (player == 1) {
    P1_SCORE++;
  }
  else if (player == 2) {
    P2_SCORE++;
  }
  delay(2000);
}

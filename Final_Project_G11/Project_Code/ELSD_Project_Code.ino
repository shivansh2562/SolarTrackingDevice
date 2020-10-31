#include <Servo.h>

Servo horizontalmotor;
Servo verticalmotor;

int ldr_top_left = 0;
int ldr_top_right = 1;
int ldr_bottom_left = 2;
int ldr_bottom_right = 3;

int top_left = 0;
int top_right = 0;
int bottom_left = 0;
int bottom_right = 0;

int vertical = 90;
int horizontal = 90;

int avg_top = 0;
int avg_bottom = 0;
int avg_left = 0;
int avg_right = 0;

int vertical_threshold = 2;
int horizontal_threshold = 2;

void setup()
{
  horizontalmotor.attach(10);
  verticalmotor.attach(9);
  horizontalmotor.write(vertical);
  verticalmotor.write(horizontal);
  Serial.begin(9600);
}

void loop()
{
  top_left = analogRead(ldr_top_left);
  top_right = analogRead(ldr_top_right);
  bottom_left = analogRead(ldr_bottom_left);
  bottom_right = analogRead(ldr_bottom_right);
  
  avg_top = (top_left + top_right)/2;
  avg_bottom = (bottom_left + bottom_right)/2;
  avg_left = (top_left + bottom_left)/2;
  avg_right = (top_right+bottom_right)/2;

  Serial.println("\ntop_left : ");
  Serial.print(top_left);

  Serial.println("\ntop_right : ");
  Serial.print(top_right);

  Serial.println("\nbottom_left : ");
  Serial.print(bottom_left);

  Serial.println("\nbottom_right : ");
  Serial.print(bottom_right);
  
  if( ((avg_top - avg_bottom) > vertical_threshold ) && (vertical>10))
  {
    Serial.println("\nVerical Motor LOW");
    Serial.print(vertical);
    vertical--;
    verticalmotor.write(vertical);
  }
  
  if(((avg_bottom - avg_top) > vertical_threshold) && (vertical<170))
  {
    Serial.println("\nVerical Motor HIGH");
    Serial.print(vertical);
    vertical++;
    verticalmotor.write(vertical);
  }
  
  if(((avg_left - avg_right) > horizontal_threshold) && (horizontal>10))
  {
    Serial.println("\nHorizontal Motor LOW");
    Serial.print(horizontal);
    horizontal--;
    horizontalmotor.write(horizontal);
  }
  
  if(((avg_right - avg_left) > horizontal_threshold) && (horizontal<170))
  {
    Serial.println("\nHorizontal Motor HIGH");
    Serial.print(horizontal);
    horizontal++;
    horizontalmotor.write(horizontal);
  }
  
  delay(100);
}


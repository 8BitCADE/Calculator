#include <Arduboy2.h>
Arduboy2 aboy;
#include "sprites.h"


typedef struct point {
  int x;
  int y;
};

#include "controller.h"
Controller Controller;

int X_Constant = 9;//9

int FirstDigit = 0;
int signOption = 0;
String Sign[4] = {"+", "-", "x", "/"};
int SecondDigit = 0;

int Option = 0;
int LastYPos;
int LastXPos;
double UPlastPressedTime;
double DOWNlastPressedTime;
double Sum;
int int_sum;

String mystring;
String equation[5] = {"0","+","0","=","0"};


String Title_Sign[8] = {"+", "-", "x", "/", "+", "-", "x", "/"};

class math {
  public:
    math();
    double a;
    double b;
    int sign;
    math(int temp_a, int temp_sign, int temp_b) {
      a = temp_a;
      b = temp_b;
      sign = temp_sign;
    }
    double calculate() {
      switch (sign) {
        case 0: //"+"
          return a + b;
          break;
        case 1://"-"
          return a - b;
          break;
        case 2://"*"
          return a * b;
          break;
        case 3://"/"
          return a / b;
          break;
        default:
          return 0;
      }
    }
};

void splashscreen() {
  aboy.clear();
  aboy.setTextSize(1);
  aboy.drawRect(0, 0, 128, 64, WHITE);

  aboy.setCursor(19, 8);
  aboy.print("8");
  aboy.display();
  digitalWrite(3, LOW);
  delay(500);

  aboy.setCursor(25, 8);
  aboy.print("Bit");
  aboy.display();
  digitalWrite(10, LOW);
  delay(500);

  aboy.setCursor(49, 8);
  aboy.print("Calculator");
  aboy.display();
  digitalWrite(9, LOW);
  delay(500);
  
  digitalWrite(3, HIGH);digitalWrite(10, HIGH);digitalWrite(9, HIGH);
  delay(500);

  aboy.setTextSize(2);
  for (int i; i < 8; i++) {
    aboy.setCursor(16 + (i * 12), 24);
    aboy.print(Title_Sign[i]);
    aboy.display();
    digitalWrite(3, LOW);digitalWrite(10, LOW);digitalWrite(9, LOW);
    delay(150);
    digitalWrite(3, HIGH);digitalWrite(10, HIGH);digitalWrite(9, HIGH);
    delay(150);
  }

  delay(150 * 2);
  aboy.setTextSize(1);
  aboy.setCursor(7, 50);
  aboy.setTextSize(1);
  
  digitalWrite(3, LOW);digitalWrite(10, LOW);digitalWrite(9, LOW);

  aboy.print("An App By Jack Daly");
  aboy.display();
  delay(150);
  
  digitalWrite(3, HIGH);digitalWrite(10, HIGH);digitalWrite(9, HIGH);
  delay(1000);
  
  aboy.clear();
}

void setup() {
  aboy.boot();
  //Allows us to prepare the arduboy library without the arduboy splashscreen
  
  pinMode(10, OUTPUT); //Yellow
  pinMode(3, OUTPUT);  //Green
  pinMode(9, OUTPUT);  //Red

  aboy.clear();
  Serial.begin(9600);

  splashscreen();
}

void loop() {
  aboy.clear();
  
  aboy.setCursor(19, 2);
  aboy.setTextSize(1);
  aboy.print("+ - / x + - / x");

  aboy.setCursor(19, 54);
  aboy.print("+ - / x + - / x");

  Check_Range_X(0, 2);
  Controller.update();

  aboy.setCursor(9, 24);//27
  aboy.setTextSize(2);
  
  equation[0] = FirstDigit;
  equation[1] = Sign[signOption];
  equation[2] = SecondDigit;
  math math(FirstDigit, signOption, SecondDigit);
  Sum = math.calculate();

  if ((int_sum = (int)Sum) == Sum) { //(int_sum = (int)Sum) == Sum
    int_sum = (int)Sum;
    equation[4] = int_sum;
  }
  else {
    equation[4] = Sum;
  }



  mystring = equation[0] + equation[1] + equation[2] + equation[3] + equation[4];
  aboy.print(mystring);

  switch (Controller.position.x) { //X SHIFT
    
    case 0:
      switch (Controller.position.y - LastYPos) {
        case -1: FirstDigit -= 1; break;
        case 0: break;
        case 1: FirstDigit += 1; break;
      }

      buttonUp(X_Constant + (6 * numOfDigits(FirstDigit)) - 5, 15); buttonDown(X_Constant + (6 * numOfDigits(FirstDigit)) - 5, 42); break;

    case 1:
      if ((signOption + (Controller.position.y - LastYPos )) >= 0 and (signOption + (Controller.position.y - LastYPos )) <= 3) {
        switch (Controller.position.y - LastYPos) {
          case -1: signOption -= 1; break;
          case 0: break;
          case 1: signOption += 1; break;
        }
      }
      buttonUp(X_Constant + (12 * numOfDigits(FirstDigit)) + (6 * numOfDigits(signOption)) - 5, 15); buttonDown(X_Constant + (12 * numOfDigits(FirstDigit)) + (6 * numOfDigits(signOption)) - 5, 42); break; 

    case 2:
      switch (Controller.position.y - LastYPos) {
        case -1: SecondDigit -= 1; break;
        case 0: break;
        case 1: SecondDigit += 1; break;
      }

      buttonUp(X_Constant + (12 * numOfDigits(FirstDigit)) + (12 * numOfDigits(signOption)) + (6 * numOfDigits(SecondDigit)) - 5, 15); buttonDown(X_Constant + (12 * numOfDigits(FirstDigit)) + (12 * numOfDigits(signOption)) + (6 * numOfDigits(SecondDigit)) - 5, 42); break;
  }

  LastYPos = Controller.position.y;
  LastXPos = Controller.position.x;

  aboy.display();
}

void buttonUp(int xpos, int ypos) {
  if (Controller.position.y - LastYPos == 1) {
    UPlastPressedTime = millis();
    Sprites::drawOverwrite(xpos, ypos - 2, upButtonFill, 0);
  }
  else if ((millis() - UPlastPressedTime) < 150) {
    Sprites::drawOverwrite(xpos, ypos - 2, upButtonFill, 0);
  }
  else {
    Sprites::drawOverwrite(xpos, ypos, upButtonNoFill, 0);
  }
}

void buttonDown(int xpos, int ypos) {
  if (Controller.position.y - LastYPos == -1) {
    DOWNlastPressedTime = millis();
    Sprites::drawOverwrite(xpos, ypos + 2, downButtonFill, 0);
  }
  else if ((millis() - DOWNlastPressedTime) < 150) {
    Sprites::drawOverwrite(xpos, ypos + 2, downButtonFill, 0);
  }
  else {
    Sprites::drawOverwrite(xpos, ypos, downButtonNoFill, 0);
  }
}

void Check_Range_X(int lowrange, int highrange)
{
  if (Controller.position.x <= lowrange) {
    Controller.LEFTButtonCanBePress = 0;
    Controller.RIGHTButtonCanBePress = 1;
  }
  else if (Controller.position.x >= highrange) {
    Controller.LEFTButtonCanBePress = 1;
    Controller.RIGHTButtonCanBePress = 0;
  }
  else {
    Controller.LEFTButtonCanBePress = 1;
    Controller.RIGHTButtonCanBePress = 1;
  }
}



int numOfDigits(int integer){
  String string = (String)integer;
  return string.length();
}

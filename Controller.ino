Controller::Controller()
{
  Serial.print("BUTTON TEST BUTTON TEST");
  position.x = 0;
  position.y = 0;
}

void Controller::update()
{
  if (aboy.pressed(UP_BUTTON) and previousUPButtonPressed == 1 and (millis() - lastHoldTime) > 150 and UPButtonCanBePress) { 
    lastHoldTime = millis();
    position.y += 1;
  }
  if ((aboy.pressed(DOWN_BUTTON) == 1 and previousDOWNButtonPressed == 1 and (millis() - lastHoldTime) > 150) and DOWNButtonCanBePress) {
    lastHoldTime = millis();
    position.y -= 1;
  }
  if (aboy.pressed(LEFT_BUTTON) and previousLEFTButtonPressed == 1 and (millis() - lastHoldTime) > 150 and LEFTButtonCanBePress) {
    lastHoldTime = millis();
    position.x -= 1;
  }
  if ((aboy.pressed(RIGHT_BUTTON) == 1 and previousRIGHTButtonPressed == 1 and (millis() - lastHoldTime) > 150) and RIGHTButtonCanBePress) {
    lastHoldTime = millis();
    position.x += 1;
  }
  if (aboy.pressed(A_BUTTON) and previousAButtonPressed == 1 and (millis() - A_lastHoldTime) > 250) { 
    A_lastHoldTime = millis();
    AButtonPressed = true;
  }
  else {
    AButtonPressed = false;
  }
  if ((aboy.pressed(B_BUTTON) == 1 and previousBButtonPressed == 1 and (millis() - B_lastHoldTime) > 250) ) {
    B_lastHoldTime = millis();
    BButtonPressed = true;
  }
  else {
    BButtonPressed = false;
  }
  previousUPButtonPressed = aboy.pressed(UP_BUTTON);
  previousDOWNButtonPressed = aboy.pressed(DOWN_BUTTON);
  previousLEFTButtonPressed = aboy.pressed(LEFT_BUTTON);
  previousRIGHTButtonPressed = aboy.pressed(RIGHT_BUTTON);
  previousAButtonPressed = aboy.pressed(A_BUTTON);
  previousBButtonPressed = aboy.pressed(B_BUTTON);
}

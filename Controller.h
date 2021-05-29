class Controller
{
  public:
    //CONSTRUCTOR
    Controller();
    //Create from the point structure a position varaible. This will be used to move the cursor
    point position;
    //Define the method UPDATE used to update the controls every loop
    void update();

    //BOOLEAN VARIABLES THAT STORES WHETHER BUTTON PRESSED IS A/B
    bool AButtonPressed;
    bool BButtonPressed;

    //BOOLEAN VARIABLE THAT STORES WHETHER THE PREVIOUS BUTTON WAS PRESSED
    bool previousUPButtonPressed;
    bool previousDOWNButtonPressed;
    bool previousLEFTButtonPressed;
    bool previousRIGHTButtonPressed;
    bool previousAButtonPressed;
    bool previousBButtonPressed;

    //BOOLEAN VARIABLES THAT CHECKS IF THE BUTTON PRESS IS UPDATED (A/B PRESSED)
    bool AButtonWasPressed;
    bool BButtonWasPressed;


    //BOOLEAN VARIABLES THAT CHECKS IF THE BUTTON CAN BE PRESSED. USED FOR COLLISION/RESTRICTION
    bool UPButtonCanBePress = 1;
    bool DOWNButtonCanBePress = 1;
    bool LEFTButtonCanBePress = 1;
    bool RIGHTButtonCanBePress = 1;

    //HOLDS POSITION OF 'CURSOR' OR CHARACTER
    int pos;

    long debounceDelay = 75; //TIME WAITED UNTILL NEXT BUTTON IS INPUTTED
    long currenttime = 0; //CURRENT TIME
    long A_lastHoldTime = 100;
    long B_lastHoldTime = 100;
    long lastHoldTime = 100;

};

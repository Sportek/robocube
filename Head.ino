//===============================
//      Defines
//===============================

#define WEEL_1 3
/*#define WEEL_2 2
#define WEEL_3 3
#define WEEL_4 4*/

#define DETECTOR_1 5
#define DETECTOR_2 6
#define DETECTOR_3 7

#define ACTIVE_BUTTON 8


//===============================
//      Variables
//===============================

boolean detect = false;
boolean activated = false;


//===============================
//        Setup
//===============================


void setup() {


  pinMode(WEEL_1, OUTPUT);
  Serial.begin(9600);
  delay(1000);

  // put your setup code here, to run once:

}

//===============================
//        Main | Loop
//===============================


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(WEEL_1, LOW);
  Serial.println("test");
  delay(500);
  

}


/*
  Activate while pushing button

*/

void activating() {
  if(digitalRead(ACTIVE_BUTTON) == 5) {

  }
}

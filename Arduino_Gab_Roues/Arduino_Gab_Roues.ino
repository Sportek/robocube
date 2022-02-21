int first_right[2] = {2, 3};
int first_left[2] = {4, 5};
int second_right[2] = {8, 9};
int second_left[2] = {10, 11};


void setup() {
   pinMode(second_right[0], OUTPUT);
   pinMode(second_right[1], OUTPUT);
}

void loop() {
  // second right recule
   //digitalWrite(second_right[0], HIGH);
   //digitalWrite(second_right[1], LOW);
   //delay(1000);


   // second right avance
   //digitalWrite(second_right[1], HIGH);
   //digitalWrite(second_right[0], LOW);

  goLeft();


  delay(1000);
}




void goLeft() {
  right(true);
  left(false);
}


void goRight() {
  left(true);
  right(false);
}


void goForward() {
  left(true);
  right(true);
}


void goBackward() {
  left(false);
  right(false);
}

void right(bool bol) {
  if(bol) {
   digitalWrite(second_right[1], HIGH);
   digitalWrite(second_right[0], LOW);
   digitalWrite(first_right[1], HIGH);
   digitalWrite(first_right[0], LOW);
  } else {
   digitalWrite(second_right[0], HIGH);
   digitalWrite(second_right[1], LOW);
   digitalWrite(first_right[0], HIGH);
   digitalWrite(first_right[1], LOW);
  }
}


void left(bool bol) {
  if(bol) {
    digitalWrite(second_left[1], HIGH);
    digitalWrite(second_left[0], LOW);
    digitalWrite(first_left[1], HIGH);
    digitalWrite(first_left[0], LOW);
  } else {
   digitalWrite(second_left[0], HIGH);
   digitalWrite(second_left[1], LOW);
   digitalWrite(first_left[0], HIGH);
   digitalWrite(first_left[1], LOW);
  }
}
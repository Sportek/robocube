int vitesse = 50;

/*
 * Définition des pins utilisés pour le robot.
 * */


/*
 * Roues
 * */
int first_right[2] = {2, 3, 6};
int first_left[2] = {4, 5, 7};
int second_right[2] = {8, 9, 12};
int second_left[2] = {10, 11, 13};

/*
 * Capteurs
 * */

int NSensor[2] = {22, 23};
int second_sensor[2] = {14, 15};
int third_sensor[2] = {16, 17};
int fourth_sensor[2] = {18, 19};

enum Direction { forward, backward, left, right };

void setup() {

    /*
     * Définition des pins utilisés au lancement
     * */

    /*
     * Roues
     * */
    pinMode(first_right[0], OUTPUT);
    pinMode(first_right[1], OUTPUT);

    pinMode(first_left[0], OUTPUT);
    pinMode(first_left[1], OUTPUT);

    pinMode(second_right[0], OUTPUT);
    pinMode(second_right[1], OUTPUT);

    pinMode(second_left[0], OUTPUT);
    pinMode(second_left[1], OUTPUT);

    pinMode(22, OUTPUT);
    pinMode(24, OUTPUT);

    /*
    * Capteurs
    */

    /*TODO*/
}

void loop() {
    analogWrite(7, 255);
    analogWrite(6, 255);
    getDirection(Direction::right);
    delay(1000);
    analogWrite(7, 100);
    analogWrite(6, 100);
    delay(1000);
}


void doRotation(Direction direction, int time) {

}

void getDirection(Direction direction) {
    analogWrite(first_left[2], vitesse);
    analogWrite(second_left[2], vitesse);
    analogWrite(first_right[2], vitesse);
    analogWrite(second_right[2], vitesse);
    switch (direction) {
        case forward:
            goLeft(Direction::forward);
            goRight(Direction::forward);
            break;
        case backward:
            goLeft(Direction::backward);
            goRight(Direction::backward);
            break;
        case right:
            goLeft(Direction::forward);
            goRight(Direction::backward);
            break;
        case left:
            goRight(Direction::forward);
            goLeft(Direction::backward);
            break;
    }
};

void goRight(Direction direction) {
    switch (direction) {
        case forward:
            digitalWrite(first_right[1], HIGH);
            digitalWrite(second_right[1], HIGH);

            digitalWrite(first_right[0], LOW);
            digitalWrite(second_right[0], LOW);
            break;
        case backward:
            digitalWrite(first_right[1], LOW);
            digitalWrite(second_right[1], LOW);

            digitalWrite(first_right[0], HIGH);
            digitalWrite(second_right[0], HIGH);
            break;
    }
}

void goLeft(Direction direction) {
    switch (direction) {
        case forward:
            digitalWrite(first_left[1], HIGH);
            digitalWrite(second_left[1], HIGH);

            digitalWrite(first_left[0], LOW);
            digitalWrite(second_left[0], LOW);
            break;
        case backward:
            digitalWrite(first_left[0], HIGH);
            digitalWrite(second_left[0], HIGH);

            digitalWrite(second_left[1], LOW);
            digitalWrite(first_left[1], LOW);
            break;
    }
}

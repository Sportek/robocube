enum Direction { forward, backward, left, right, stop };
Direction direction;
int vitesse = 100; // Ceci n'est pas la vitesse, c'est (50/255*100)% des capacités du moteur.
int rotationTime = 20; // En secondes

/*
 * Définition des pins utilisés pour le robot.
 * */


/*
 * Roues
 * */

/*
 * Les ports [0] servent à faire avancer le robot lorsqu'ils sont à HIGH.
 * Les ports [1] servent à faire reculer le robot lorsqu'ils sont à HIGH.
 * Les ports [2] servent à définir la vitesse du robot. Entre 0 et 255
 * (0 signifie que ça n'avance pas alors que 255 signifie  que le moteur est à pleine capacitée).
 * */
int first_right[3] = {4, 5, 12};
int first_left[3] = {2, 3, 13};
int second_right[3] = {8, 9, 7};
int second_left[3] = {10, 11, 6};

/*
 * Capteurs
 * */

int NSensor[2] = {22, 23};
int second_sensor[2] = {14, 15};
int third_sensor[2] = {16, 17};
int fourth_sensor[2] = {18, 19};

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

    /*
     * Vitesse des roues
     */

    pinMode(first_right[2], OUTPUT);
    pinMode(first_left[2], OUTPUT);

    pinMode(second_right[2], OUTPUT);
    pinMode(second_left[2], OUTPUT);

    /*
    * Capteurs
    */

    /*TODO*/
}

void loop() {
    setDirection(Direction::left);
    analogWrite(first_left[2], vitesse);
    analogWrite(second_left[2], vitesse);
    analogWrite(first_right[2], vitesse);
    analogWrite(second_right[2], vitesse);
    // Serial.print(direction);
    delay(10000);
}


void doRotation(Direction direction, int time) {

}

/*
 * À utiliser pour set les directions.
 * */
void setDirection(Direction direction) {
    analogWrite(first_left[2], vitesse);
    analogWrite(second_left[2], vitesse);
    analogWrite(first_right[2], vitesse);
    analogWrite(second_right[2], vitesse);
    switch (direction) {
        case forward:
            goLeft(Direction::forward);
            goRight(Direction::forward);
            direction = Direction::forward;
            break;
        case backward:
            goLeft(Direction::backward);
            goRight(Direction::backward);
            direction = Direction::backward;
            break;
        case right:
            goLeft(Direction::forward);
            goRight(Direction::backward);
            direction = Direction::right;
            break;
        case left:
            goRight(Direction::forward);
            goLeft(Direction::backward);
            direction = Direction::left;
            break;
        case stop:
            digitalWrite(first_right[0], LOW);
            digitalWrite(second_right[0], LOW);
            digitalWrite(first_left[0], LOW);
            digitalWrite(second_left[0], LOW);
            direction = Direction::stop;
            break;
    }
};
/*
 * Ne pas utiliser
 * */
void goRight(Direction direction) {
    switch (direction) {
        case backward:
            digitalWrite(first_right[1], HIGH);
            digitalWrite(second_right[1], HIGH);

            digitalWrite(first_right[0], LOW);
            digitalWrite(second_right[0], LOW);
            break;
        case forward:
            digitalWrite(first_right[1], LOW);
            digitalWrite(second_right[1], LOW);

            digitalWrite(first_right[0], HIGH);
            digitalWrite(second_right[0], HIGH);
            break;
    }
}
/*
 * Ne pas utiliser
 * */
void goLeft(Direction direction) {
    switch (direction) {
        case backward:
            digitalWrite(first_left[1], HIGH);
            digitalWrite(second_left[1], HIGH);

            digitalWrite(first_left[0], LOW);
            digitalWrite(second_left[0], LOW);
            break;
        case forward:
            digitalWrite(first_left[0], HIGH);
            digitalWrite(second_left[0], HIGH);

            digitalWrite(second_left[1], LOW);
            digitalWrite(first_left[1], LOW);
            break;
    }
}

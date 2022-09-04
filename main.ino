#include "SR04.h"

enum Direction {
    forward, backward, left, right, stop, up, down
};
Direction direction;
int vitesse = 100; // Ceci n'est pas la vitesse, c'est (50/255*100)% des capacités du moteur.
int rotationTime = 150; // En millisecondes et multiplié par 20
int pulleyTime = 1000 * 2.5; // En millisecondes
int distance_magnet = 12; // Magnet
float percentage = 1.20;

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
int pulley[2] = {50, 51};

// int distance;

int magnet = 52;

/*
 * Capteurs
 * */

/*
 * Les ports [0] servent à ... (trigPin)
 * Les ports [1] servent à ... (echoPin)
 * */
int north_sensor[2] = {22, 23};
int south_sensor[2] = {26, 27};
int east_sensor[2] = {24, 25};
int west_sensor[2] = {28, 29};

SR04 north = SR04(north_sensor[1], north_sensor[0]);
SR04 south = SR04(south_sensor[1], south_sensor[0]);
SR04 east = SR04(east_sensor[1], east_sensor[0]);
SR04 west = SR04(west_sensor[1], west_sensor[0]);


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

    pinMode(north_sensor[0], OUTPUT);
    pinMode(north_sensor[1], INPUT);

    pinMode(south_sensor[0], OUTPUT);
    pinMode(south_sensor[1], INPUT);

    pinMode(west_sensor[0], OUTPUT);
    pinMode(west_sensor[1], INPUT);

    pinMode(east_sensor[0], OUTPUT);
    pinMode(east_sensor[1], INPUT);

    pinMode(magnet, OUTPUT);


    /*
     * Vitesse des roues
     */

    pinMode(first_right[2], OUTPUT);
    pinMode(first_left[2], OUTPUT);

    pinMode(second_right[2], OUTPUT);
    pinMode(second_left[2], OUTPUT);



    /*
     * Connection à la console pour récupérer des informations lorsqu'on test.
     * */
    Serial.begin(9600);
    delay(1000);

      /*
    * Set les vitesses
    **/

    setSpeed(vitesse);

    /*
     * Lancement du robot
     * */

    /*
     * Découverte de la cible la moins éloignée.
     * */

     delay(500); // Délai de 10 secondes pour s'éloigner

    long betterDirection[2];
    long startRotation = millis();
    setDirection(Direction::right);
    for (int i = 0; i < 25; ++i) {
        long actualDirection[2];
        long north_direction = north.Distance();
        Serial.println(north_direction);
        actualDirection[0] = north_direction;
        actualDirection[1] = millis();
        if (!betterDirection[0] || actualDirection[0] < betterDirection[0]) {

          /*
          * TODO: À revérifier ici, mais ça devrait être correct.
          */
            betterDirection[0] = north_direction;
            betterDirection[1] = actualDirection[1];
        }
        delay(rotationTime);
    }


    /*
     * Le robot se tourne afin qu'il soit dirigé vers le bloc.
     * */

    while(betterDirection[0] * percentage <= north.Distance()) {
      Serial.println(betterDirection[0]);
        Serial.println("-----------------------------------");
      Serial.println(north.Distance());
      setDirection(Direction::right);
      delay(200);
      setDirection(Direction::stop);
      delay(200);
    }

    setDirection(Direction::right);
    delay(500);

    /*
     * TODO
     * Faire un système pour se replacer si jamais c'est pas correct.
     * */

    setDirection(Direction::stop);

    /*
     * Approcher le robot jusqu'à atteindre le bloc.
     * */

    setSpeed(75);
    while(north.Distance() >= distance_magnet) {
        setDirection(Direction::forward);
    }

    /*
     * Arrêter le robot, préparer le robot à remonter le bloc.
     * */
    setDirection(Direction::stop);

    /*
     * Descendre l'aimant
     * */

    movePulley(Direction::down);
    delay(pulleyTime);
    movePulley(Direction::stop);

    /*
     * Activer l'aimant
     * */

    activeMagnet(true);

    /*
     * Remonter l'aimant
     * */

    movePulley(Direction::up);
    delay(pulleyTime);
    movePulley(Direction::stop);
    setSpeed(75);

    /*
    * Se dirige vers l'arrière pendant 2s.
    **/
    setDirection(Direction::backward);
    delay(2000);
    setDirection(Direction::stop);


    /*
    * Descend l'aimant
    **/
    movePulley(Direction::down);
    delay(pulleyTime);
    movePulley(Direction::stop);


    /*
    * Désactive l'aimant
    **/
    activeMagnet(false);

    /*
    * Remonte l'aimant
    **/
    movePulley(Direction::up);
    delay(pulleyTime);
    movePulley(Direction::stop);
}

void loop() {
    /*
     * Rien n'est fait ici pour le moment.
     * */
}


/*
 * Déplacer la poulie
 * Direction::up: Monter
 * Direction::down: Descendre
 * */
void movePulley(Direction direction) {
    if (direction == Direction::up) {
        digitalWrite(pulley[0], LOW);
        digitalWrite(pulley[1], HIGH);
    }
    if (direction == Direction::down) {
        digitalWrite(pulley[0], HIGH);
        digitalWrite(pulley[1], LOW);
    }
     if (direction == Direction::stop) {
      digitalWrite(pulley[0], LOW);
      digitalWrite(pulley[1], LOW);
    }
    return;
}



/*
 * Activer/Désactiver l'aimant
 * true: activé
 * false: désactivé
 * */
void activeMagnet(bool activate) {
    digitalWrite(52, activate ? HIGH : LOW);
}

/*
 * À utiliser pour set les directions.
 * */
void setDirection(Direction direction) {
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
            digitalWrite(first_right[1], LOW);
            digitalWrite(second_right[1], LOW);
            digitalWrite(first_left[1], LOW);
            digitalWrite(second_left[1], LOW);
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

void setSpeed(int value) {
  analogWrite(first_left[2], value);
    analogWrite(second_left[2], value);
    analogWrite(first_right[2], value);
    analogWrite(second_right[2], value);
}

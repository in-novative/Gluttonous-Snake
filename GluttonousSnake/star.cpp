#include "star.h"

star::star(int misc1, int misc2){
    timer1.setInterval(misc1);
    timer2.setInterval(misc2);
    timer1.start();
    timer2.stop();
    setStarPosition(0, 0);
}

void star::setStarPosition(uint x, uint y) {
    star_x = x;
    star_y = y;
}

bomb::bomb(int misc1, int misc2) {
    timer1.setInterval(misc1);
    timer2.setInterval(misc2);
    timer1.start();
    timer2.stop();
    setBombPosition(0, 0);
}

void bomb::setBombPosition(uint x, uint y) {
    bomb_x = x;
    bomb_y = y;
}

sun::sun(int misc1, int misc2) {
    timer1.setInterval(misc1);
    timer2.setInterval(misc2);
    timer1.start();
    timer2.stop();
    setSunPosition(0, 0);  // Assuming you have a function like setSunPosition to initialize sun's position
}

void sun::setSunPosition(uint x, uint y) {
    sun_x = x;
    sun_y = y;
}

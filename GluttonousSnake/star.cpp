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

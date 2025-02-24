#ifndef STAR_H
#define STAR_H

#include "QtHeader.h"

class star {
public:
    star(int misc1, int misc2);
    void setStarPosition(uint x, uint y);
    inline QPair<uint, uint> getStarPosition() { return QPair<uint, uint>(star_x, star_y); }
    inline void timerStart(uint i) { (i == 1) ? timer1.start() : timer2.start(); }
    inline void timerStop(uint i) { (i == 1) ? timer1.stop() : timer2.stop(); }
    inline bool timerActive(uint i) { return (i == 1) ? timer1.isActive() : timer2.isActive(); }
    inline QTimer* getTimer(uint i) { return (i == 1) ? &timer1 : &timer2; }
private:
    QTimer timer1, timer2;
    uint star_x, star_y;
};

class bomb {
public:
    bomb(int misc1, int misc2);
    void setBombPosition(uint x, uint y);
    inline QPair<uint, uint> getBombPosition() { return QPair<uint, uint>(bomb_x, bomb_y); }
    inline void timerStart(uint i) { (i == 1) ? timer1.start() : timer2.start(); }
    inline void timerStop(uint i) { (i == 1) ? timer1.stop() : timer2.stop(); }
    inline bool timerActive(uint i) { return (i == 1) ? timer1.isActive() : timer2.isActive(); }
    inline QTimer* getTimer(uint i) { return (i == 1) ? &timer1 : &timer2; }
private:
    QTimer timer1, timer2;
    uint bomb_x, bomb_y;
};

class sun {
public:
    sun(int misc1, int misc2);
    void setSunPosition(uint x, uint y);
    inline QPair<uint, uint> getSunPosition() { return QPair<uint, uint>(sun_x, sun_y); }
    inline void timerStart(uint i) { (i == 1) ? timer1.start() : timer2.start(); }
    inline void timerStop(uint i) { (i == 1) ? timer1.stop() : timer2.stop(); }
    inline bool timerActive(uint i) { return (i == 1) ? timer1.isActive() : timer2.isActive(); }
    inline QTimer* getTimer(uint i) { return (i == 1) ? &timer1 : &timer2; }
private:
    QTimer timer1, timer2;
    uint sun_x, sun_y;
};

#endif // STAR_H

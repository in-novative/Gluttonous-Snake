#ifndef STARTINTERFACE_H
#define STARTINTERFACE_H

#include "QtHeader.h"
#include "game.h"

class interface{
public:
    interface();
    ~interface();
    void beginInterface();
    void gameInterface();
    void rankInterface();
    void helpInterface();
    inline void startGame(int i) { _game = new game(i); }
    inline void endGame() { delete _game; _game = nullptr; }
    inline game* getGame() { return _game; }
private:
    game *_game = nullptr;
};

extern interface *userInterface;

#endif // STARTINTERFACE_H

#ifndef WATCHY_FOOFINGERS_H
#define WATCHY_FOOFINGERS_H

#include <Watchy.h>
#include "fonts/MotorolaScreentype10pt7b.h"
#include "fonts/MADESunflower_trim38pt7b.h"


class WatchyFooFingers : public Watchy{
    public:
        WatchyFooFingers();
        void drawWatchFace();
        void drawDate();
        void drawBattery();
};

#endif

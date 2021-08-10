#ifndef WATCHY_FOOFINGERS_H
#define WATCHY_FOOFINGERS_H

#include <Watchy.h>
#include "fonts/MotorolaScreentype8pt7b.h"
#include "fonts/Bebas_Regular60pt7b.h"
#include "fonts/Bebas_Regular30pt7b.h"


class WatchyFooFingers : public Watchy{
    public:
        WatchyFooFingers();
        void drawWatchFace();
        void drawDate();
        void drawBattery();
        void drawWeather();
};

#endif

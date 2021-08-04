#include "Watchy_FooFingers.h"

WatchyFooFingers::WatchyFooFingers(){} //constructor

void WatchyFooFingers::drawWatchFace(){
    display.fillScreen(GxEPD_BLACK);
    display.drawBitmap(0, 0, bg, DISPLAY_WIDTH, DISPLAY_HEIGHT, GxEPD_BLACK);
  
    int x = 100;
    int y = 125;
      
    int16_t x1, y1;
    uint16_t w, h;

    String s_currentTime = "";
    
    if(currentTime.Hour < 10){
       s_currentTime.concat("0");
    }
    s_currentTime.concat(currentTime.Hour);
    s_currentTime.concat(":");
    if(currentTime.Minute < 10){
      s_currentTime.concat("0");
    }
    s_currentTime.concat(currentTime.Minute);
    
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&GAMEPLAY_198728pt7b);
    display.setTextWrap(false);
    display.getTextBounds(s_currentTime, x, y, &x1, &y1, &w, &h);
    display.setCursor(x - w / 2, y);
    display.print(s_currentTime);
}

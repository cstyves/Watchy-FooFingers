#include "Watchy_FooFingers.h"
#include "FooFingers_sprites.h"

WatchyFooFingers::WatchyFooFingers(){} //constructor

void WatchyFooFingers::drawWatchFace(){
    display.fillScreen(GxEPD_BLACK);
    display.drawBitmap(0, 0, foofingers_img_bg, DISPLAY_WIDTH, DISPLAY_HEIGHT, GxEPD_BLACK);
  
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
    display.setFont(&MADESunflower_trim38pt7b);
    display.setTextWrap(false);
    display.getTextBounds(s_currentTime, x, y, &x1, &y1, &w, &h);
    display.setCursor(x - w / 2, y);
    display.print(s_currentTime);

    /* Other functions */

    this->drawDate();
    this->drawBattery();
}

void WatchyFooFingers::drawDate(){
    /* Build date output top left : DayOfWeek, Month Day */
    String s_currentDate = "";
    String dayOfWeek = dayStr(currentTime.Wday);
    String curMonth = monthShortStr(currentTime.Month);
    String shortDayOfWeek = dayOfWeek.substring(0,3);

    s_currentDate.concat(shortDayOfWeek);
    s_currentDate.concat(", ");
    s_currentDate.concat(curMonth);
    s_currentDate.concat(" ");
    s_currentDate.concat(currentTime.Day);

    switch (currentTime.Day){
      case 1:
      case 21:
      case 31:
        s_currentDate.concat("st");
      break;
      case 2:
      case 22:
        s_currentDate.concat("nd");
      break;
      case 3:
      case 23:
        s_currentDate.concat("rd");
      break;
      default:
        s_currentDate.concat("th");
      break;
    }
    
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&MotorolaScreentype8pt7b);
    display.setTextWrap(false);
    display.setCursor(5,22);
    display.print(s_currentDate);
}

void WatchyFooFingers::drawBattery(){
    
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
    if(VBAT > 4.1){
        batteryLevel = 4;
        display.drawBitmap(167, 7, foofingers_img_bat100, 28, 13, GxEPD_WHITE);
    }
    else if(VBAT > 3.95 && VBAT <= 4.1){
        batteryLevel = 3;
        display.drawBitmap(167, 7, foofingers_img_bat75, 28, 13, GxEPD_WHITE);
    }
    else if(VBAT > 3.88 && VBAT <= 3.95){
        batteryLevel = 2;
        display.drawBitmap(167, 7, foofingers_img_bat50, 28, 13, GxEPD_WHITE);
    } 
    else if(VBAT > 3.80 && VBAT <= 3.95){
        batteryLevel = 1;
        display.drawBitmap(167, 7, foofingers_img_bat25, 28, 13, GxEPD_WHITE);
    }    
    else if(VBAT <= 3.80){
        batteryLevel = 0;
        display.drawBitmap(167, 7, foofingers_img_bat0, 28, 13, GxEPD_WHITE);
    }
}

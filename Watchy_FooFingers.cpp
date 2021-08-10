#include "Watchy_FooFingers.h"
#include "FooFingers_sprites.h"

WatchyFooFingers::WatchyFooFingers(){} //constructor

void WatchyFooFingers::drawWatchFace(){
    display.fillScreen(GxEPD_BLACK);
    //display.drawBitmap(0, 0, foofingers_img_bg, DISPLAY_WIDTH, DISPLAY_HEIGHT, GxEPD_BLACK);
  
    int x = 100;
    int y = 125;
      
    int16_t x1, y1;
    uint16_t w, h;

    String s_currentTime = "";
    String s_currentHour = "";
    String s_currentMin = "";
    
    if(currentTime.Hour < 10){
       s_currentHour.concat("0");
    }
    s_currentHour.concat(currentTime.Hour);
    
    s_currentTime.concat(s_currentHour);
    s_currentTime.concat(":");
    
    if(currentTime.Minute < 10){
      s_currentMin.concat("0");
    }
    s_currentMin.concat(currentTime.Minute);

    s_currentTime.concat(s_currentMin);

    // s_currentTime formated : HH:MM

    // DISPLAY HOUR:MIN
    /*
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&MADESunflower_trim38pt7b);
    display.setTextWrap(false);
    display.getTextBounds(s_currentTime, x, y, &x1, &y1, &w, &h);
    display.setCursor(x - w / 2, y);
    display.print(s_currentTime);
    */

    display.setTextColor(GxEPD_WHITE);
    display.setFont(&Bebas_Regular60pt7b);
    display.getTextBounds(s_currentHour, 20, 95, &x1, &y1, &w, &h);
    display.setCursor(20, 145);
    display.print(s_currentHour);

    display.drawBitmap(20, 55, foofingers_img_alpha_90_80, 90, 80, GxEPD_BLACK);
    
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&Bebas_Regular30pt7b);
    display.getTextBounds(s_currentHour, 130, 75, &x1, &y1, &w, &h);
    display.setCursor(130, 102);
    display.print(s_currentMin);

    /* Other functions */

    this->drawDate();
    this->drawBattery();
    this->drawWeather();
    this->drawSteps();
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
    display.setFont(&MotorolaScreenType_w_degree8pt7b);
    display.setTextWrap(false);
    display.setCursor(5,22);
    display.print(s_currentDate);
}

void WatchyFooFingers::drawBattery(){
    
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
    if(VBAT > 4.1){
        batteryLevel = 4;
        display.drawBitmap(167, 8, foofingers_img_bat100, 28, 13, GxEPD_WHITE);
    }
    else if(VBAT > 3.95 && VBAT <= 4.1){
        batteryLevel = 3;
        display.drawBitmap(167, 8, foofingers_img_bat75, 28, 13, GxEPD_WHITE);
    }
    else if(VBAT > 3.88 && VBAT <= 3.95){
        batteryLevel = 2;
        display.drawBitmap(167, 8, foofingers_img_bat50, 28, 13, GxEPD_WHITE);
    } 
    else if(VBAT > 3.80 && VBAT <= 3.95){
        batteryLevel = 1;
        display.drawBitmap(167, 8, foofingers_img_bat25, 28, 13, GxEPD_WHITE);
    }    
    else if(VBAT <= 3.80){
        batteryLevel = 0;
        display.drawBitmap(167, 8, foofingers_img_bat0, 28, 13, GxEPD_WHITE);
    }
}

void WatchyFooFingers::drawWeather(){

    weatherData currentWeather = getWeatherData();

    int8_t temperature = currentWeather.temperature;
    int16_t weatherConditionCode = currentWeather.weatherConditionCode;   

    //display.setFont(&DSEG7_Classic_Regular_39);
    int16_t  x1, y1;
    uint16_t w, h;

    String tempText = "";
    tempText.concat(temperature);
    if(strcmp(TEMP_UNIT, "metric") == 0){
      tempText.concat("°C");
    }else{
      tempText.concat("°F");
    }
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&MotorolaScreenType_w_degree8pt7b);
    display.setTextWrap(false);
    display.setCursor(170, 190);
    display.println(tempText);
    
    //display.getTextBounds(String(temperature), 100, 150, &x1, &y1, &w, &h);
    //display.setCursor(155 - w, 150);
    //display.println(temperature);
    //display.drawBitmap(165, 110, strcmp(TEMP_UNIT, "metric") == 0 ? celsius : fahrenheit, 26, 20, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    const unsigned char* weatherIcon;

    //https://openweathermap.org/weather-conditions
    if(weatherConditionCode > 801){//Cloudy
    weatherIcon = foofingers_img_cloudy;
    }else if(weatherConditionCode == 801){//Few Clouds
    weatherIcon = foofingers_img_cloudsun;  
    }else if(weatherConditionCode == 800){//Clear
    weatherIcon = foofingers_img_sunny;  
    }else if(weatherConditionCode >=700){//Atmosphere
    weatherIcon = foofingers_img_cloudy; 
    }else if(weatherConditionCode >=600){//Snow
    weatherIcon = foofingers_img_snow;
    }else if(weatherConditionCode >=500){//Rain
    weatherIcon = foofingers_img_rain;  
    }else if(weatherConditionCode >=300){//Drizzle
    weatherIcon = foofingers_img_drizzle;
    }else if(weatherConditionCode >=200){//Thunderstorm
    weatherIcon = foofingers_img_thunderstorm; 
    }else
    return;
    display.drawBitmap(128, 110, weatherIcon, 48, 48, GxEPD_WHITE);
}

void WatchyFooFingers::drawSteps(){
    uint32_t stepCount = sensor.getCounter();

    const unsigned char* stepIcon;

    if(stepCount > 0 && stepCount <= 3999){
        stepIcon = foofingers_img_step_goal_1;
    }
    else if(stepCount > 4000 && stepCount <= 8000){
        stepIcon = foofingers_img_step_goal_2;
    }
    else if(stepCount > 8001){
        stepIcon = foofingers_img_step_goal_3;
    }
    
    display.drawBitmap(10, 168, stepIcon, 38, 23, GxEPD_WHITE);
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&MotorolaScreenType_w_degree8pt7b);
    display.setTextWrap(false);
    display.setCursor(55, 190);
    display.println(stepCount);
}

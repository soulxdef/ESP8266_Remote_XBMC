#include <TickerScheduler.h>
//#include"LED.h"

TickerScheduler ts(1);

String LoadTS()
{
    ts.add(0, 10000, [&](void*) {RandomColor();}, nullptr,true);//Добавляю задачу 0 с интервалом 30 сек, вызов перелива RGB
    return "Cron Enable";
}


void handle_ts()
{
    LedMode();
    ts.update();
}
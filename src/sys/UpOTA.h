#include <ESP8266HTTPUpdateServer.h> 
#include <ESP8266WebServer.h>
//#define OTAUSER         "admin"    // Логин для входа в OTA
//#define OTAPASSWORD     "admin"    // Пароль для входа в ОТА
//#define OTAPATH         "/firmware"// Путь, который будем дописывать после ip адреса в браузере.
//#define SERVERPORT      80         // Порт для входа, он стандартный 80 это
//ESP8266WebServer HTTP(80);

ESP8266WebServer HTTP(80);
ESP8266HTTPUpdateServer httpUpdater;
String http_init()
{
    httpUpdater.setup(&HTTP);   
    HTTP.begin(80);
    return "Module : UPDATE SERVER Enable";
}
void  Handle_http()
{
    HTTP.handleClient();
}
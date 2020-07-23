#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266SSDP.h>

//IPAddress ip(192,168,0,88);
//IPAddress gateway(192,168,0,1);
//IPAddress subnet(255,255,255,0);
DNSServer dnsServer;

bool StartAPMode() {
  IPAddress apIP(192, 168, 4, 1);
  IPAddress staticGateway(192, 168, 4, 1);
  IPAddress staticSubnet(255, 255, 255, 0);
  //jsonWrite(configJson, "ip", apIP.toString()); 
  // Отключаем WIFI
  WiFi.disconnect();
  // Меняем режим на режим точки доступа
  WiFi.mode(WIFI_AP);
  // Задаем настройки сети
  WiFi.softAPConfig(apIP, staticGateway, staticSubnet);
  //Включаем DNS
  dnsServer.start(53, "*", apIP);
  // Включаем WIFI в режиме точки доступа с именем и паролем
  // хронящихся в переменных _ssidAP _passwordAP
  String _ssidAP = jsonRead(configJson, "AP");
  String _passwordAP = jsonRead(configJson, "passAP");
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
  return true;
}

String wifi_init()
{
  int ns = 0;
  HTTP.on("/restart", HTTP_GET, []() {
    String restart = HTTP.arg("device");          // Получаем значение device из запроса
    if (restart == "ok") {                         // Если значение равно Ок
      HTTP.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
      ESP.restart();                                // перезагружаем модуль
    }
    else {                                        // иначе
      HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
    }
  });
  HTTP.on("/debug", HTTP_GET, []() {
    String debug = HTTP.arg("value"); 
    configJson = jsonWrite(configJson,"Debug", debug);
    saveConfig();         
    HTTP.send(200, "text / plain", "Debug :" + debug);
  });
  HTTP.on("/config.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", configJson);
  });
  HTTP.on("/ssid", HTTP_GET, []() {
  jsonWrite(configJson, "ssid", HTTP.arg("ssid"));
  jsonWrite(configJson, "password", HTTP.arg("password"));
  saveConfig();                 // Функция сохранения данных во Flash
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });
  String ssid = jsonRead(configJson,"ssid");
  String pass = jsonRead(configJson,"pass");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);   //WiFi connection
  //WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(50);
    if(ns == 10)
    {
      if(StartAPMode())
      {
      return "Module : WiFi AP mode";
      }else
      {
        return"Eror start APmod";
      }
      
    }
  }

  return "Module : WiFi Enable";
}

String SSDP_init() {
  String chipID = String( ESP.getChipId() ) + "-" + String( ESP.getFlashChipId() );
  // SSDP дескриптор
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
   // --------------------Получаем SSDP со страницы
  HTTP.on("/ssdp", HTTP_GET, []() {
    String ssdp = HTTP.arg("ssdp");
  configJson= jsonWrite(configJson, "SSDP", ssdp);
  //configJson =jsonWrite(configSetup, "SSDP", ssdp);
  SSDP.setName(jsonRead(configJson, "SSDP"));
  saveConfig();                 // Функция сохранения данных во Flash
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });
  //Если версия  2.0.0 закаментируйте следующую строчку
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(jsonRead(configJson, "SSDP"));
  SSDP.setSerialNumber(chipID);
  SSDP.setURL("/");
  SSDP.setModelName("tech");
  SSDP.setModelNumber(chipID + "/" + jsonRead(configJson, "SSDP"));
  SSDP.setModelURL("192.168.0.102");
  SSDP.setManufacturer("Craft Naotebis");
  SSDP.setManufacturerURL("91.193.252.201");
  SSDP.begin();
  return "SSDP Enable";
}


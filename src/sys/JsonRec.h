#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>



String jsonpost(String &json)
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  char JSONmessageBuffer[300];
  root.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  HTTPClient httpg;
  httpg.begin("http://kodi:123583121X@192.168.0.104:8088/jsonrpc");
  httpg.addHeader("Content-Type", "application/json");
  int httpCode = httpg.POST(JSONmessageBuffer);
  Serial.println("----------------- ");
  Serial.println("json Buffer : "+ String(JSONmessageBuffer));
  Serial.println("----------------- ");
  String payload = httpg.getString();

  DynamicJsonBuffer jsonBufferRe;
  JsonObject& roots = jsonBuffer.parseObject(payload);
  char JSONmessageBuffers[300];
  roots.prettyPrintTo(JSONmessageBuffers, sizeof(JSONmessageBuffers));

  Serial.println("----------------- ");
  Serial.println("json payload : "+ String(JSONmessageBuffers));
  Serial.println("----------------- ");
  //Debag_console(payload);
  httpg.end();
  //json = loadJsondef(json);
  return payload;
}

String jsonWrite(String &json, String name, String volume) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  Serial.println("json Write : "+ json);
  return json;
}
String jsonWrite(String &json, String name, int volume) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  return json;
}
String jsonWrite(String &json,String params,String name, int value)
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonObject& data = root.createNestedObject(params);
  data.set(name,value);
  json = "";
  root.printTo(json);
  return json;
}
String jsonWrite(String &json,String params,String name, String value)
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonObject& data = root.createNestedObject(params);
  data.set(name,value);
  json = "";
  root.printTo(json);
  return json;
}
String jsonWrite(String &json,String params,String name, int value,String name2,int value2)
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonObject& data = root.createNestedObject(params);
  data.set(name, value);
  data.set(name2, value2);
  json = "";
  root.printTo(json);
  return json;
}

String loadJsondef(String &json)
{
    json = "{}";
    json = jsonWrite(json,"jsonrpc","2.0");
    return json;
}

int jsonReadtoInt(String &json, String name) 
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  return root[name];
}

int getPlayerID(String &json, String name, String volume )
{
  int ids=0;
  String s = "playerid";
  json = jsonWrite(json, name, volume);
  json = jsonpost(json);
  ids = jsonReadtoInt(json,s);
  return ids;
}

String jsonRead(String &json, String name) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  return root[name].as<String>();
}

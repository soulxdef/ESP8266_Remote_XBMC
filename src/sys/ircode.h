#include "IRremoteESP8266.h"
#include <IRrecv.h>
#include <IRutils.h>
#include "JsonRec.h"
//#include "debag.h"

const uint16_t kRecvPin = 14; // Пин считывания кодов
IRrecv irrecv(kRecvPin);
decode_results results;
String json="{}";
String jsonPlaerID="{}";
int id;
uint64_t temp;

String ircode_init()
{
    irrecv.enableIRIn();
    return "Modele : IR Eneble";
}

void Recive_code()
{
  if (irrecv.decode(&results)) 
  { 
    temp = results.value;
    //json = "";
    json = loadJsondef(json);
    jsonPlaerID = loadJsondef(jsonPlaerID);
    serialPrintUint64(results.value, HEX);
      switch (results.value) 
      {
        case 0xE0E0A659:       
          json = jsonWrite(json,"method","Input.Left");
          json = jsonpost(json);
          break;
        case 0xE0E046B9:
          json = jsonWrite(json,"method","Input.Right");
          json = jsonpost(json);
          break;
        case 0xE0E006F9:
          json = jsonWrite(json,"method","Input.Up");
          json = jsonpost(json);
          break;
        case 0xE0E08679:
          json = jsonWrite(json,"method","Input.Down");
          json = jsonpost(json);
          break;
        case 0xE0E016E9:
          json = jsonWrite(json,"method","Input.Select");
          json = jsonpost(json);
          break;
        case 0xE0E01AE5:
          json = jsonWrite(json,"method","Input.Back");
          json = jsonpost(json);
          break;
        case 0xE0E0F807:
          json = jsonWrite(json,"method","Input.Info");
          json = jsonpost(json);
          break;
        case 0xE0E0A857:
          json = jsonWrite(json,"method","Input.ContextMenu");
          json = jsonpost(json);
          break;
        case 0xE0E06897:
          json = jsonWrite(json,"method","Input.ShowOSD");
          json = jsonpost(json);
          break;
        case 0xE0E0B44B:
          json = jsonWrite(json,"method","Input.Home");
          json = jsonpost(json);
          break;
        case 0xE0E0E21D:
          json = jsonWrite(json,"method","Player.PlayPause");
          id = 1; //getPlayerID(jsonPlaerID,"method","Player.GetActivePlayers");
          json = jsonWrite(json,"params","playerid",id);
          json = jsonpost(json);

          break;
        case 0xE0E052AD:
          json = jsonWrite(json,"method","Player.Stop");
          id = 1; //getPlayerID(jsonPlaerID,"method","Player.GetActivePlayers");
          json = jsonWrite(json,"params","playerid",id);
          json = jsonpost(json);
          break;
        case 0xE0E012ED:
          json = jsonWrite(json,"method","Player.SetSpeed");
          id = 1 ; //getPlayerID(jsonPlaerID,"method","Player.GetActivePlayers"); //not work
          json += jsonWrite(json,"params","playerid",id,"speed",16);
          json = jsonpost(json);
          break;
        case 0xE0E0A25D:
          json = jsonWrite(json,"method","Player.SetSpeed");
          id = 1; //getPlayerID(jsonPlaerID,"method","Player.GetActivePlayers");
          json = jsonWrite(json,"params","playerid",id,"speed",-16);
          json = jsonpost(json);
          break;
        case 0xE0E036C9:
          json = jsonWrite(json,"method","Application.SetVolume");
          json = jsonWrite(json,"params","volume","increment");
          json = jsonpost(json);
          break;
        case 0xE0E028D7:
          json = jsonWrite(json,"method","Application.SetVolume");
          json = jsonWrite(json,"params","volume","decrement");
          json = jsonpost(json);
          break;
        case 0xE0E0F20D:
          //Debag_xbmc("KODI","Shutdown");
          json = jsonWrite(json,"method","System.Shutdown");
          json = jsonWrite(json,"id", 1);
          json = jsonpost(json);  
          break;
        case 0xE0E0D629:

          break;

        //RGB ttx- вкл/выкл
        case 0xE0E034CB:
        
          break;
        case 0xE0E0609F:
         
          break;
        case 0xE0E010EF:
          
          break;
        case 0xE0E0906F:
          
          break;

        case 0xE0E08877:
        
          
          break;
      }
      irrecv.resume(); // принимаем следующую команду
      delay(50);
    }
}
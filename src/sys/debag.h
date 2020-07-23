void Debag_xbmc(String name, String value)
{
    String s;
    String json;
    json = loadJsondef(json);
    json = jsonWrite(json,name,value);
    s = jsonpost(json);
    //Debag_console(s);
}

void Debag_console(String s)
{
    Serial.println(s);
    Serial.println("---------------------");
   // if(jsonRead(configJson,"Debug")=="true")
    //{
        //Debag_xbmc("Debug :",s);
    //}
}

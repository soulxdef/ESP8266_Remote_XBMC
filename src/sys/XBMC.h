#include "ircode.h"
#include "UpOTA.h"
#include "fs.h"
#include "wifi.h"
#include "debag.h"
#include "LED.h"
#include "cron.h"

void LoadModules()
{  
    Debag_console(loadconfig());
    Debag_console(http_init());
    Debag_console(ircode_init());  
    Debag_console(FS_init());
    Debag_console(SSDP_init());
    Debag_console(wifi_init());  
    Debag_console(RGB_init());
    Debag_console(LoadTS());     
}
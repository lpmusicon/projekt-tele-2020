#include "configurator.h"


void deleteFile(fs::FS &fs, const char * path)//to potem sie wywali do jakeigos cpp
{
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path))
    {
        Serial.println("Cfg file deleted");
    } else 
    {
        Serial.println("Cfg file delete failed");
    }
}

void configurationLoad(fs::FS &fs, const char * path,String &ssid, String &pass)
{
    
    File file = fs.open(path);
    if(!file || file.isDirectory()) //Write cfg file
    {
        Serial.println("Failed to open file for reading");
        Serial.println("Making new cfg file");
        file = fs.open(path, FILE_WRITE);
        if(!file)
        {
            Serial.println("Failed to open file for writing");
        }
        else
        {
          if(file.print("Moje super Wiffi\n123456789\n"))
          {
              Serial.println("File written");
          }
          else 
          {
              Serial.println("Write failed");
          }
        }
    }
    else  //Read cfg file
    {
        char sign;
        ssid="";
        pass="";

        Serial.println("Read from file:");

        while(file.available() && sign!='\n') /* SSID */
        {
            sign=file.read();
            //Serial.write(sign);
            if(sign!='\n')
                ssid+=sign;
        }
        do /* Password */
        {
            sign=file.read();
            //Serial.write(sign);
            if(sign!='\n')
                pass+=sign;
        } while (file.available() && sign!='\n');
    }
    Serial.println("SSID: "+ssid);
    Serial.println("PASS: "+pass);
}
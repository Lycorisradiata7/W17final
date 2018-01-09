#include <LWiFi.h>

char ssid[] = "406-1";      //  your network SSID (name)
char pass[] = "ntuedorm";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int MIC_PIN = 16;
int led = 13;
int micval=0;
int status = WL_IDLE_STATUS;

WiFiServer server(80);
String webSite;

void setup() {
  Serial.begin(115200);      // initialize serial communication
  
  pinMode(MIC_PIN, INPUT); 
  
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);
    
    status = WiFi.begin(ssid, pass);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
    int mic = analogRead(MIC_PIN);
    // 讀取麥克風輸出

  //Serial.println(mic);
  if(mic>=620 && mic<640) micval=0;
  else if((mic>=640 && mic<670)||(mic>=590&& mic<620 )) micval=1;
  else if((mic>=670 && mic<700)||(mic>=560&& mic<590 )) micval=2;
  else if((mic>=700 && mic<750)||(mic>=510&& mic<560 )) micval=3;
  else if((mic>=750 && mic<800)||(mic>=460&& mic<510 )) micval=4;
  else if((mic>=800 && mic<850)||(mic>=410&& mic<460 )) micval=5;
  else if((mic>=850 && mic<900)||(mic>=360&& mic<410 )) micval=6;
  else if((mic>=900 && mic<1000)||(mic>=260&& mic<360 )) micval=7;
  else if((mic>=1000 && mic<1100)||(mic>=160&& mic<260 )) micval=8;
  else micval=9;

  
  
  Serial.println(micval);
  delay(1000);
  WiFiClient client = server.available();   // listen for incoming clients
      
  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";   // make a String to hold incoming data from the client
  
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Refresh:1");
            
            if(micval==1){webSite=""; buildWeb1();}
            else if(micval==2) {webSite="";buildWeb2();}
            else if(micval==3) {webSite="";buildWeb3();}
            else if(micval==4) {webSite="";buildWeb4();}
            else if(micval==5) {webSite="";buildWeb5();}
            else if(micval==6) {webSite="";buildWeb6();}
            else if(micval==7) {webSite="";buildWeb7();}
            else if(micval==8) {webSite="";buildWeb8();}
            else if(micval==9) {webSite="";buildWeb9();}
            else  {webSite="";buildWeb();}
         
            client.println();
            client.print(webSite);
           
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void buildWeb(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }

void buildWeb1(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }

void buildWeb2(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }

void buildWeb3(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }

void buildWeb4(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }

void buildWeb5(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }

void buildWeb6(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }

void buildWeb7(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height:70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }

void buildWeb8(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 10%; height: 10%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }


void buildWeb9(){
  webSite += "<html>";
  webSite += "<head>\n";
  webSite += "  <meta charset='UTF-8'\n>";
  webSite += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite += "  <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
  webSite += "  <title>聲音圖騰 Sound Totem</title>\n";
  webSite += "  <style media=\"screen\" type=\"text/css\">";
  webSite += "  body{ background-color: #696969;  }";
  webSite += "  .BG{width:360px; height:360px; margin: 35% auto; background-color: #c0c0c0;}";
  webSite += "  .ROW{width: 100%; height: 33.3%;  }";
  webSite += "  .COL{width: 33.3%; height: 100%; position: relative;  }";
  webSite += "  .s18-3838{ padding: 10% 10%; background-color: #5f4b8b; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);  }";
  webSite += "  .float-left{ float: left;  }";
  webSite += "  .clear{ clear: both;  }";
  webSite += "  </style>";
  webSite += "</head>\n";
  webSite += "<body>";
  webSite += "  <div class=\"BG\">";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height:70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "    <div class=\"ROW\">";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"COL float-left\">";
  webSite += "        <div class=\"s18-3838\" style=\"width: 70%; height: 70%;\"></div>";
  webSite += "      </div>";
  webSite += "      <div class=\"clear\"></div>";
  webSite += "    </div>";
  webSite += "  </div>";
  webSite += "</body></html>";
  webSite += "}";
  }


#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Change to match your settings
IPAddress ip(192, 168, 2, 100);
IPAddress myDns(192,168,2, 1);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);
//No need to edit anything below

EthernetServer server(23);
boolean alreadyConnected = false;

void setup() {
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  server.begin();
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.print("Chat server address: ");
  Serial.println(Ethernet.localIP());
  Serial.println("================================");
  Serial.println("|    ARDUINO TELNET CHATROOM   |");
  Serial.println("|         Serial: READY        |");
  Serial.println("================================");
}
void loop() {
  EthernetClient client = server.available();

  if (client) {
    if (!alreadyConnected) {
      client.flush();
      client.print("ACCESS @");
      client.print(Ethernet.localIP()); 
      client.println(" GRANTED");
      client.println("================================");
      client.println("|    ARDUINO TELNET CHATROOM   |");
      client.println("|       Client: VERIFIED       |");
      client.println("|        Server: ONLINE        |");
      client.println("================================");
      alreadyConnected = true;
      Serial.println("[*] New client has connected [*]");
    }}
    while (client.available() > 0) {
      char thisChar = client.read();
      
      server.write(thisChar);
      Serial.write(thisChar);
    }
  }

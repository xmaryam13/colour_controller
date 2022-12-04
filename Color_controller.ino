// To connect with WiFi
#include<WiFi.h>

//  To make our device as server
#include<WebServer.h>

//  ssid , password
const char ssid[] = "SKYT2I1W";
const char password[] = "9gj91php1egL";

//  RGb led pins
const byte r_pin = 25;
const byte g_pin = 26;
const byte b_pin = 27;

//  defining channels
const byte r_channel = 0;
const byte g_channel = 1;
const byte b_channel = 2;

//  defining frequency and reolution
const byte frequency = 5000;
const byte resolution = 8;

//  starting a server at port 80
WebServer server(80);

void setup() {

  //  setting frequency and resolution at channels
  ledcSetup(r_channel , frequency , resolution);
  ledcSetup(g_channel , frequency , resolution);
  ledcSetup(b_channel , frequency , resolution);

  //  attaching GPIOs
  ledcAttachPin(r_pin , r_channel);
  ledcAttachPin(g_pin , g_channel);
  ledcAttachPin(b_pin , b_channel);

  //   starting serial communication
  Serial.begin(115200);

  //  connecting with the WiFi and printing IP Address
  Serial.print("Connecting with : ");
  Serial.println(ssid);
  WiFi.begin(ssid , password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with the Network !");
  Serial.print("IP address assgined by the access point : ");
  Serial.println(WiFi.localIP());

  //  Define APIs
  server.on("/", handle_root);
  server.on("/red", handle_red);
  server.on("/blue",handle_blue);
  server.on("/green",handle_green);
  server.on("/yellow",handle_yellow);
  server.on("/magenta",handle_magenta);
  server.on("/orange",handle_orange);
  server.on("/cyan",handle_cyan);

  server.onNotFound(handle_notfound);

  //  Define API, if other APIs are not found






  //  start the server
  Serial.begin(9600);
  delay(100);

  Serial.println("HTTP Server started");

}

void loop() {
  server.handleClient();
  //  to handle the client requests at APIs
}

void handle_root() {
  Serial.println("No colour");
  String html = generate_html();
  server.send(200, "text/html", html);
}

void handle_red() {
  Serial.println("Red");
  String html = generate_html();
  color_generator(255, 0, 0);
  server.send(200, "text/html", html);
}

void handle_green() {
  Serial.println("Green");
  String html = generate_html();
  color_generator(0, 255, 0);
  server.send(200, "text/html", html);
}

void handle_blue() {
  Serial.println("Blue");
  String html = generate_html();
  color_generator(0, 0, 255);
  server.send(200, "text/html", html);
}

void handle_yellow() {
  Serial.println("Yellow");
  String html = generate_html();
  color_generator(255, 255, 0);
  server.send(200, "text/html", html);
}

void handle_orange() {
  Serial.println("Orange");
  String html = generate_html();
  color_generator(255, 165, 0);
  server.send(200, "text/html", html);
}

void handle_cyan() {
  Serial.println("Cyan");
  String html = generate_html();
  color_generator(0, 255, 255);
  server.send(200, "text/html", html);
}

void handle_magenta() {
  Serial.println("Magenta");
  String html = generate_html();
  color_generator(255, 0, 255);
  server.send(200, "text/html", html);
}

void color_generator(byte r , byte g , byte b) {
  ledcWrite(r_channel , r);
  ledcWrite(g_channel , g);
  ledcWrite(b_channel , b);
}


//  generating HTML Page
String generate_html() {

  String html = "<!DOCTYPE html>\n";
  html += "<html lang=\"en\">\n";
  html += "<head>\n";
  html += "<meta charset=\"UTF-8\">\n";
  html += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  html += "<title>ESP32 RGB CONTROLLER</title>\n";
  html += "</head>\n";
  html += "<body>\n";
  html += "<div style=\"padding-left: 50%; padding-top: 10%;\">\n";
  html += "<h1>COLOR GENERATOR</h1>\n";
  html += "</div>\n";

  html += "<div style=\"padding-left: 40%;\">\n";
  html += "<a href=\"/red\"><button>Red</button></a>\n";
  html += "<a href=\"/green\"><button>Green</button></a>\n";
  html += "<a href=\"/blue\"><button>Blue</button></a>\n";
  html += "<a href=\"/yellow\"><button>Yellow</button></a>\n";
  html += "<a href=\"/cyan\"><button>Cyan</button></a>\n";
  html += "<a href=\"/magenta\"><button>Magenta</button></a>\n";
  html += "<a href=\"/orange\"><button>Orange</button></a>\n";
  html += "</div>\n";

  html += "</body>\n";
  html += "</html>\n";

  return html;
}

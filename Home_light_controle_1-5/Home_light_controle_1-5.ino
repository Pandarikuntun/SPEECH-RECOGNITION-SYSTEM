/************ LIBRARIES ************/
// Core WiFi library for ESP8266
#include <ESP8266WiFi.h>

// Web server library to create HTTP server
#include <ESP8266WebServer.h>

// SinricPro cloud library (for Alexa / voice control)
#include <SinricPro.h>
#include <SinricProSwitch.h>

/************ WIFI CREDENTIALS ************/
// Your mobile hotspot / router name
#define WIFI_SSID "Redmi 9 Power"

// WiFi password
#define WIFI_PASS "TULASIRAM"

/************ SINRIC PRO CREDENTIALS ************/
// App key from SinricPro dashboard
#define APP_KEY    "369a87ad-eea2-4275-8e0e-5ec89897c28c"

// App secret from SinricPro dashboard
#define APP_SECRET "9c31a0dc-38bb-407d-b569-ed4ac049a605-f1cbff0c-a08c-466c-8ee2-da36ae752a1b"

// Device ID for the smart switch
#define DEVICE_ID  "6948e5706dbd335b28f8fc4d"

/************ PIN DEFINITIONS ************/
// LED connected to GPIO5 (D1)
#define LED_PIN     5

// Push button connected to GPIO4 (D2)
#define BUTTON_PIN  4

// IR sensor connected to GPIO16 (D0)
#define IR_PIN      16

// Create web server object on port 80
ESP8266WebServer server(80);

/************ GLOBAL VARIABLES ************/
// Stores ON/OFF state from web or SinricPro
bool webLedState = false;

// Brightness value (0–100 because PWM range is set to 100)
int brightness = 512;   // default brightness

// Stores IR sensor status text
String irStatus = "Not Detected";

// Stores LED status text
String ledStatus = "OFF";

/************ SINRIC CALLBACK FUNCTION ************/
// This function runs when Alexa / SinricPro changes power state
bool onPowerState(const String &, bool &state) {

  // Store ON/OFF state
  webLedState = state;

  if (state) {
    // If ON → glow LED with selected brightness
    analogWrite(LED_PIN, brightness);
    ledStatus = "ON";
  } else {
    // If OFF → turn LED off
    digitalWrite(LED_PIN, LOW);
    ledStatus = "OFF";
  }
  return true;   // confirmation to SinricPro
}

/************ WEB PAGE HANDLER ************/
// This function sends HTML page to browser
void handleRoot() {

  // HTML + CSS + JavaScript code
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP8266 Smart LED</title>

<style>
/* Page background */
body {
  background: linear-gradient(135deg,#667eea,#764ba2);
  font-family: 'Segoe UI', sans-serif;
  text-align: center;
  color: white;
  margin: 0;
  padding: 0;
}

/* Card design */
.card {
  background: white;
  color: #333;
  max-width: 350px;
  margin: 40px auto;
  padding: 25px;
  border-radius: 15px;
  box-shadow: 0 10px 25px rgba(0,0,0,0.3);
}

/* LED circle */
.led {
  width: 60px;
  height: 60px;
  border-radius: 50%;
  margin: 15px auto;
  background: black;
  box-shadow: 0 0 10px red;
}

/* LED ON animation */
.on {
  background: #2ecc71;
  box-shadow: 0 0 20px #2ecc71;
}

/* Button style */
button {
  width: 120px;
  padding: 12px;
  margin: 10px;
  font-size: 16px;
  border: none;
  border-radius: 8px;
  color: white;
  cursor: pointer;
}

#onBtn { background: #27ae60; }
#offBtn { background: #e74c3c; }

/* Slider style */
input[type=range] {
  width: 100%;
  margin-top: 10px;
}

.status {
  font-weight: bold;
}
</style>
</head>

<body>

<div class="card">
  <h2>HOME Smart LED</h2>

  <div id="ledIcon" class="led"></div>

  <p>LED: <span id="led" class="status">OFF</span></p>
  <p>IR Sensor: <span id="ir" class="status">Not Detected</span></p>

  <!-- ON / OFF Buttons -->
  <button id="onBtn" onclick="fetch('/on')">ON</button>
  <button id="offBtn" onclick="fetch('/off')">OFF</button>

  <!-- Brightness slider -->
  <p>Brightness: <span id="val">50</span></p>
  <input type="range" min="0" max="100" value="50"
         oninput="updateBrightness(this.value)">
</div>

<script>
// Send brightness value to ESP8266
function updateBrightness(v){
  document.getElementById("val").innerHTML = v;
  fetch('/slider?value=' + v);
}

// Auto update LED & IR status every 500ms
setInterval(() => {
  fetch('/ledstatus').then(r=>r.text()).then(d=>{
    document.getElementById("led").innerHTML = d;
    document.getElementById("ledIcon").className =
      d === "ON" ? "led on" : "led";
  });

  fetch('/irstatus').then(r=>r.text()).then(d=>{
    document.getElementById("ir").innerHTML = d;
  });
}, 500);
</script>

</body>
</html>
)rawliteral";

  // Send webpage to browser
  server.send(200, "text/html", html);
}

/************ SETUP FUNCTION ************/
void setup() {

  // Start serial monitor
  Serial.begin(9600);

  // Configure pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(IR_PIN, INPUT);

  // Set PWM range (0–100)
  analogWriteRange(100);

  // Turn LED OFF initially
  digitalWrite(LED_PIN, LOW);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  // Print ESP8266 IP address
  Serial.println(WiFi.localIP());

  // Web routes
  server.on("/", handleRoot);

  server.on("/on", []() {
    webLedState = true;
    analogWrite(LED_PIN, brightness);
    ledStatus = "ON";
    server.send(200, "text/plain", "ON");
  });

  server.on("/off", []() {
    webLedState = false;
    digitalWrite(LED_PIN, LOW);
    ledStatus = "OFF";
    server.send(200, "text/plain", "OFF");
  });

  server.on("/slider", []() {
    if (server.hasArg("value")) {
      brightness = server.arg("value").toInt();
      webLedState = true;
      analogWrite(LED_PIN, brightness);
      ledStatus = "ON";
    }
    server.send(200, "text/plain", "OK");
  });

  // Status endpoints
  server.on("/irstatus", []() { server.send(200,"text/plain",irStatus); });
  server.on("/ledstatus", []() { server.send(200,"text/plain",ledStatus); });

  // Start web server
  server.begin();

  // SinricPro setup
  SinricProSwitch &sw = SinricPro[DEVICE_ID];
  sw.onPowerState(onPowerState);
  SinricPro.begin(APP_KEY, APP_SECRET);
}

/************ LOOP FUNCTION ************/
void loop() {

  // Handle web requests
  server.handleClient();

  // Handle SinricPro events
  SinricPro.handle();

  // Read button and IR sensor
  bool btn = digitalRead(BUTTON_PIN);
  bool ir  = digitalRead(IR_PIN);

  // Update IR sensor status
  irStatus = (ir == LOW) ? "Detected" : "Not Detected";

  // If button OR IR OR web command → LED ON
  if (btn == LOW || ir == LOW || webLedState) {
    analogWrite(LED_PIN, brightness);
    ledStatus = "ON";
  } else {
    digitalWrite(LED_PIN, LOW);
    ledStatus = "OFF";
  }
}

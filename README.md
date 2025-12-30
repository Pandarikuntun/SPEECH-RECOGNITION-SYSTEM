# SPEECH-RECOGNITION-SYSTEM

**********. INTRODUCTION

Speech recognition is a technology that enables machines to understand and process human voice commands. In embedded systems, speech recognition can be used to control devices such as LEDs, motors, relays, home appliances, and robots.
This project focuses on designing and implementing a basic speech recognition system that recognizes predefined voice commands and performs corresponding actions using an embedded board (such as Arduino, ESP8266, ESP32, or Raspberry Pi).

************. OBJECTIVES

To design a command-based speech recognition system
To interface a speech input module or cloud-based speech service with an embedded controller
To control electrical devices using voice commands
To demonstrate a working real-time system
To understand speech-to-text processing, command matching, and device control

************. SYSTEM OVERVIEW
The system works by:
Capturing human speech using a microphone
Converting speech into text (speech recognition)
Matching the recognized text with predefined commands
Sending control signals to devices
Performing the required action (ON/OFF, OPEN/CLOSE, etc.)

*********. BLOCK DIAGRAM
<img width="998" height="548" alt="Image" src="https://github.com/user-attachments/assets/01e5893d-c8e0-4c41-a778-fb2f61fa99b4" />
*********. HARDWARE REQUIREMENTS
Component	Description
Embedded Board	ESP8266 / ESP32 / Arduino / Raspberry Pi
Microphone	In-built / External microphone
Relay Module	Controls AC or DC devices
LED	Device for demonstration
Power Supply	5V / 3.3V
Connecting Wires	Jumper wires

********. SOFTWARE REQUIREMENTS

Software	Purpose
Arduino IDE	Code development
Embedded C / C++	Programming language
Speech Recognition API	Google Speech / Alexa / Sinric Pro
Wi-Fi Library	Network connectivity
Serial Monitor	Debugging

*****************. SPEECH RECOGNITION METHODS

.1 Offline Speech Recognition
Uses local processing
Limited vocabulary
Example: Voice recognition modules (HM2007)

*********Advantages

No internet required
Faster response

*******Disadvantages

Limited accuracy
Fixed commands only

.2 Online (Cloud-Based) Speech Recognition

Uses internet-based services
High accuracy
Example: Google Assistant, Alexa, Sinric Pro

*******Advantages
High accuracy
Natural language support

********Disadvantages

Internet dependency
Latency issues

***********. COMMAND-BASED CONTROL LOGIC

Example commands:
“Turn ON light”
“Turn OFF light”

Command Matching:
If recognized_command == "Turn on light"
    → LED ON
Else if recognized_command == "Turn off light"
    → LED OFF

******. EMBEDDED SYSTEM DESIGN

.1 Input Section

Microphone captures speech
Voice command sent to speech recognition engine

.2 Processing Section

Speech converted to text
Command compared with predefined list

.3 Output Section

GPIO pins activated
Relay or LED controlled

*********. FLOW CHART
START
  |
Initialize WiFi & Speech API
  |
Wait for Voice Command
  |
Speech Recognized?
  |
Yes
  |
Compare Command
  |
Execute Device Action
  |
Repeat



**************. WORKING DEMONSTRATION
Demo Steps:
Power ON the embedded board
Connect to Wi-Fi
Speak command using mobile app / assistant
Speech is converted to text
Embedded board receives command
Device responds instantly
Example:
Command: “Turn ON light”
Output: LED glows

********. RESULTS

Accurate recognition of predefined commands
Real-time response observed
Reliable device control using voice

********. APPLICATIONS

Smart Home Automation
Assistive Technology for Disabled
Voice-controlled Robots
Industrial Automation
IoT-based Device Control

**********. ADVANTAGES

Hands-free operation
User-friendly interface
Reduces manual effort
Scalable system

*********. LIMITATIONS

Noise affects accuracy
Internet dependency (for cloud-based)
Limited commands in basic systems

**********. FUTURE ENHANCEMENTS

Add multi-language support
Use AI-based natural language processing
Integrate mobile app dashboard

Control multiple devices
Implement offline speech recognition

********. CONCLUSION

A basic speech recognition system using an embedded board successfully demonstrates how voice commands
can control devices efficiently. The project integrates speech processing, embedded programming, and device control,
making it highly relevant for IoT and smart automation applications.

[
PowerPoint slides

Proteus simulation](https://github.com/user-attachments/assets/f7311395-d24d-4e8b-9906-60958850b916)

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>

#define LED_BLUE 10 
#define LED_RED 8 
#define buzzer 7


const char *ssid = "ESPBia";
const char *password = "pacotinho1";

WebServer server(80);
void setup() {
pinMode(LED_BLUE, OUTPUT);
pinMode(LED_RED, OUTPUT);
Serial.begin(115200);

WiFi.softAP(ssid,password);
IPAddress myIP = WiFi.softAPIP();
Serial.print("SSID: ");
Serial.println(ssid);
Serial.print("AP IP address: ");
Serial.println(myIP);
server.begin();
Serial.println("Servidor Iniciado");

server.on("/",handleRoot);
server.on("/on", handleOn);
server.on("/off", handleOff);
server.on("/empate", handleEmpate);
server.on("/blue", handleBlue);

server.begin();
Serial.println("HTTP server strated");
}

void handleRoot(){
String html = "";
html += "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Jogo da velha</title> </head> <body> <div class=\"board\" data-board> <div class=\"cell\" data-cell></div> <div class=\"cell\" data-cell></div> <div class=\"cell\" data-cell></div> <div class=\"cell\" data-cell></div> <div class=\"cell\" data-cell></div> <div class=\"cell\" data-cell></div> <div class=\"cell\" data-cell></div> <div class=\"cell\" data-cell></div> <div class=\"cell\" data-cell></div> </div> <div class=\"winning-message\" data-winning-message> <a class=\"winning-message-text\" data-winning-message-text id=\"texto\" >X Venceu!</a> <a class=\"winning-message-button\" data-restart-button href=\"/off\">Reiniciar</a> </div> <style> *{ box-sizing: border-box; margin: 0; padding: 0; } body{ height: 100vh; width: 100vw; background: linear-gradient(90deg,rgba(65,184,131,1)0%,rgba(0,212,255,1)100%); } .board{ display: grid; width: 100%; height: 100%; justify-content: center; align-content: center; justify-items: center; align-items: center; grid-template-columns: repeat(3,auto); } .board.x .cell:not(.x):not(.circle):hover::after, .board.x .cell:not(.x):not(.circle):hover::before, .board.circle .cell:not(.x):not(.circle):hover::before, .board.circle .cell:not(.x):not(.circle):hover::after { background: rgb(255, 255,255,0.3) !important; } .cell{ width: 100px; height: 100px; border: 2px solid white; display:flex; justify-content: center; align-items: center; } .cell:nth-child(1), .cell:nth-child(2), .cell:nth-child(3){ border-top: none; } .cell:nth-child(1), .cell:nth-child(4), .cell:nth-child(7){ border-left: none; } .cell:nth-child(3), .cell:nth-child(6), .cell:nth-child(9){ border-right: none; } .cell:nth-child(7), .cell:nth-child(8), .cell:nth-child(9){ border-bottom: none; } .cell.x,.cell.circle{ cursor:not-allowed; } .cell.x::before, .cell.x::after, .board.x .cell:not(.x):not(.circle):hover::after, .board.x .cell:not(.x):not(.circle):hover::before{ content: \"\"; height: calc(100px*0.15); width: calc(100px*0.9); background: rgb(245, 77, 77); position: absolute; } .cell.x::before, .board.x .cell:not(.x):not(.circle):hover::before{ transform: rotate(45deg); } .cell.x::after, .board.x .cell:not(.x):not(.circle):hover::after{ transform: rotate(-45deg); } .cell.circle::before, .cell.circle::after, .board.circle .cell:not(.circle):not(.x):hover::after, .board.circle .cell:not(.circle):not(.x):hover::before{ content: \"\"; height: calc(100px*0.9); width: calc(100px*0.9); background: rgb(82, 82, 252); position: absolute; border-radius: 50%; } .winning-message{ display: none; position: fixed; top:0; left:0; right:0; bottom: 0; justify-content: center; align-items: center; background-color: rgba(0,0,0,0.8); flex-direction: column; } .winning-message-button{ text-decoration: none; font-size: 2.5rem; background-color: rgba(65,184,131,1); padding: 10px 15px; cursor: pointer; border-radius: 15px; border: none; margin-top: 16px; color: white; } .winning-message-button:hover{ color:rgba(65,184,131,1); background-color: white; } .winning-message-text{ text-decoration: none; font-size: 3.5rem; color: white; } .show-winning-message{ display: flex; } </style> <script> const cellElements = document.querySelectorAll(\"[data-cell]\"); const board = document.querySelector(\"[data-board]\"); const winningMessageTextElement = document.querySelector( \"[data-winning-message-text]\" ); const winningMessage = document.querySelector(\"[data-winning-message]\"); const restartButton = document.querySelector(\"[data-restart-button]\"); let isCircleTurn;let O = \"O\";let X = \"X\";let resultX = X.link(\"/on\"); let resultO = O.link(\"/blue\"); let empate = \"Empate!\"; let resultEm = empate.link(\"/empate\") ;const winningCombinations = [ [0, 1, 2], [3, 4, 5], [6, 7, 8], [0, 3, 6], [1, 4, 7], [2, 5, 8], [0, 4, 8], [2, 4, 6], ]; const startGame = () => { isCircleTurn = false; for (const cell of cellElements) { cell.classList.remove(\"circle\"); cell.classList.remove(\"x\"); cell.removeEventListener(\"click\", handleClick); cell.addEventListener(\"click\", handleClick, { once: true }); } setBoardHoverClass(); winningMessage.classList.remove(\"show-winning-message\"); }; const endGame = (isDraw) => { if (isDraw) { winningMessageTextElement.innerHTML = \"Empate!\" + resultEm; } else { winningMessageTextElement.innerHTML = isCircleTurn ? \"O Venceu!\" + resultO : \"X Venceu!\" + resultX; } winningMessage.classList.add(\"show-winning-message\"); }; const checkForWin = (currentPlayer) => { return winningCombinations.some((combination) => { return combination.every((index) => { return cellElements[index].classList.contains(currentPlayer); }); }); }; const checkForDraw = () => { return [...cellElements].every((cell) => { return cell.classList.contains(\"x\") || cell.classList.contains(\"circle\"); }); }; const placeMark = (cell, classToAdd) => { cell.classList.add(classToAdd); }; const setBoardHoverClass = () => { board.classList.remove(\"circle\"); board.classList.remove(\"x\"); if (isCircleTurn) { board.classList.add(\"circle\"); } else { board.classList.add(\"x\"); } }; const swapTurns = () => { isCircleTurn = !isCircleTurn; setBoardHoverClass(); }; const handleClick = (e) => { const cell = e.target; const classToAdd = isCircleTurn ? \"circle\" : \"x\"; placeMark(cell, classToAdd); const isWin = checkForWin(classToAdd);  const isDraw = checkForDraw(); if (isWin) { endGame(false); } else if (isDraw) { endGame(true); } else { swapTurns(); } }; startGame(); restartButton.addEventListener(\"click\", startGame); </script> </body> </html>";
  server.send(200,"text/html",html);
}

void handleOn(){
  digitalWrite(LED_RED,1);
  handleRoot();
}

void handleBlue(){
  digitalWrite(LED_BLUE,1);
  handleRoot();
}

void handleEmpate(){
  digitalWrite(LED_BLUE,1);
  digitalWrite(LED_RED,1);
  handleRoot();
}

void handleOff(){
  digitalWrite(LED_BLUE,0);
  digitalWrite(LED_RED,0);
  tone(buzzer, 392, 1000);
  handleRoot();
}

void loop() {
server.handleClient();
delay(2);
}

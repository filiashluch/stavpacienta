var connection = new WebSocket('ws://'+location.hostname+':81/');
var button_1_status = 0;
var button_2_status = 0;
var temp_data = 0;
var hum_data = 0;
var bpm_data = 0;
var SpO2_data = 0;
var bodytemperature_data = 0;
connection.onmessage = function(event){
  var full_data = event.data;
  console.log(full_data);
  var data = JSON.parse(full_data);
  temp_data = data.temp;
  hum_data = data.hum;
  var bpm_data = data.bpm;
  var SpO2_data = data.SpO2;
  var bodytemperature_data = data.bodytemperature;
  document.getElementById("temp_meter").value = temp_data;
  document.getElementById("temp_value").innerHTML = temp_data;
  document.getElementById("hum_meter").value = hum_data;
  document.getElementById("hum_value").innerHTML = hum_data;
  document.getElementById("bpm_meter").value = bpm_data;
  document.getElementById("bpm_value").innerHTML = bpm_data;
  document.getElementById("SpO2_meter").value = SpO2_data;
  document.getElementById("SpO2_value").innerHTML = SpO2_data;
  document.getElementById("bodytemperature_meter").value = bodytemperature_data;
  document.getElementById("bodytemperature_value").innerHTML = bodytemperature_data;
}
function button_1_on()
{
   button_1_status = 1; 
  console.log("LED 1 is ON");
  send_data();
}
function button_1_off()
{
  button_1_status = 0;
console.log("LED 1 is OFF");
send_data();
}
function button_2_on()
{
   button_2_status = 1; 
  console.log("LED 2 is ON");
  send_data();
}
function button_2_off()
{
  button_2_status = 0;
console.log("LED 2 is OFF");
send_data();
}
function send_data()
{
  var full_data = '{"LED1" :'+button_1_status+',"LED2":'+button_2_status+'}';
  connection.send(full_data);
}
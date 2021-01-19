var password;
var pass1 = "admin1";

password = prompt('Zadejte heslo', ' ');

if (password == pass1)
  alert('Spravne heslo!');
else {
  window.location = "";
}
var connection = new WebSocket('ws://' + location.hostname + ':81/');
var button_1_status = 0;
var button_2_status = 0;
var temp_data = 0;
var hum_data = 0;
var tep_data = 0;
var ox_data = 0;
var bodytemp_data = 0;
connection.onmessage = function (event) {
  var full_data = event.data;
  console.log(full_data);
  var data = JSON.parse(full_data);
  temp_data = data.temp;
  hum_data = data.hum;
  tep_data = data.tep;
  ox_data = data.ox;
  bodytemp_data = data.bodytemp;
  document.getElementById("temp_meter").value = temp_data;
  document.getElementById("temp_value").innerHTML = temp_data;
  document.getElementById("hum_meter").value = hum_data;
  document.getElementById("hum_value").innerHTML = hum_data;
  document.getElementById("bpm_meter").value = tep_data;
  document.getElementById("bpm_value").innerHTML = tep_data;
  document.getElementById("SpO2_meter").value = ox_data;
  document.getElementById("SpO2_value").innerHTML = ox_data;
  document.getElementById("bodytemperature_meter").value = bodytemp_data;
  document.getElementById("bodytemperature_value").innerHTML = bodytemp_data;
}
function button_1_on() {
  button_1_status = 1;
  send_data();
}
function button_1_off() {
  button_1_status = 0;
  send_data();
}
function button_2_on() {
  button_2_status = 1;
  send_data();
}
function button_2_off() {
  button_2_status = 0;
  send_data();
}
function send_data() {
  var full_data = '{"LED1" :' + button_1_status + ',"LED2":' + button_2_status + '}';
  connection.send(full_data);
}
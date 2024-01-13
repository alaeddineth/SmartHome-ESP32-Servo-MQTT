const express = require('express');
const mqtt = require('mqtt');

const app = express();
const PORT = 3000;

// Set up MQTT client
const mqttClient = mqtt.connect('mqtt://test.mosquitto.org');  // Replace with your MQTT broker address
const mqttTopic = 'MOTORSERVO';

mqttClient.on('connect', () => {
  console.log('Connected to MQTT broker');
  mqttClient.subscribe(mqttTopic);
});

mqttClient.on('message', (topic, message) => {
  // Forward the received data to the web dashboard
  io.emit('MOTORSERVO', message.toString());
  console.log('I received a message from the mqtt =' + message.toString());

});

// Set up Express server
const server = app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});

// Set up Socket.io for real-time communication with the web dashboard
const io = require('socket.io')(server);

app.use(express.static('public'));


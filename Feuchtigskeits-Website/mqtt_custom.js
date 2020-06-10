
//settings for MQTT Broker
var host = '192.168.178.190';
var port = 9001;
var clientID = "Moistursensor_Webpage"; //by connect with random number 0-99
var topic = '#';
var useSSL = false;
var cleansession = true;
var mqtt;
var reconnectTimeout = 2000;

//for drawing diagrams
var diag_counter = 0;
var diag_counter2 = 0;

var line1 = [[new Date(), 46], [new Date(), 40]];
var line2 = [[new Date(), 20]];

function MQTTconnect() {
	if (typeof path == "undefined") {
		path = '/mqtt';
	}
	//Create Client instance
	mqtt = new Paho.MQTT.Client(host, port, path, clientID + parseInt(Math.random() * 100, 10));
	
	var options = {
		timeout: 3,
		useSSL: useSSL,
		cleanSession: cleansession,
		onSuccess: onConnect,
		onFailure: function (message) {
			$('#status').html("Connection failed: " + message.errorMessage + "Retrying...");
			//after timeout start function MQTTconnect again
			setTimeout(MQTTconnect, reconnectTimeout);
		}
	};
	
	//callback handlers
	mqtt.onConnectionLost = onConnectionLost;
	mqtt.onMessageArrived = onMessageArrived;
	console.log("Host: "+ host + ", Port: " + port + ", Path: " + path + " SSL: " + useSSL);
	//connecting client
	mqtt.connect(options);
};

//called when connecting
function onConnect() {
	$('#status').html('Connected to ' + host + ':' + port + path);
	//subscribes to var topic
	mqtt.subscribe(topic, {qos: 0});
	$('#topic').html(topic);
};

//called by lost connection
function onConnectionLost(response) {
	setTimeout(MQTTconnect, reconnectTimeout);
	if (response.errorCode !== 0) {
		$('#status').html("Connection lost: " + response.errorMessage + ". Reconnecting...");
		console.log("onConnectionLost:"+response.errorMessage);
		}
};

//MOST IMPORTANT
//called on every arrived message
function onMessageArrived(message) {
	var topic = message.destinationName;
	var payload = message.payloadString;
	console.log("Topic: " + topic + ", Message payload: " + payload);
	//changes id "message" to topic, payload
	$('#message').html(topic + ', ' + payload);
	
	var message = topic.split('/');
	
	if (message[0] == "plants") {
		var plantNr = message[1];
		var sensor = message[2];
		var timestamp = Date.now();
		
		switch (plantNr) {
			case '1': 
			
				switch (sensor) {
					case 'signal':
						$('#P1_Sig').text(payload + ' dBm');
						break;
					case 'temp':
						$('#P1_Temp').text(payload + ' °C');
						
						line2[diag_counter2] = [new Date(), payload];
						diag_counter2++;
						/* if (diag_counter2 > 10)
							diag_counter2 = 0; */
						drawDiag2(line2);
						
						break;
					case 'hum':
						$('#P1_Hum').html(payload + '<span style="font-family: Arial,Helvetica,sans-serif;"> %</span>');
						
						line1[diag_counter] = [new Date(), payload];
						diag_counter++;
						/*if (diag_counter > 10)
							diag_counter = 0;*/
						drawDiag1(line1);
						
						break;
				}
				break;	
				
			case '2': 
			
				switch (sensor) {
					case 'signal':
						$('#P2_Sig').text(payload + ' dBm');
						break;
					case 'temp':
						$('#P2_Temp').text(payload + ' °C');
						break;
					case 'hum':
						$('#P2_Hum').html(payload + '<span style="font-family: Arial,Helvetica,sans-serif;"> %</span>');
						break;
				}
				break;	
			
			default: console.log('Error: Data do not match the MQTT topic.'); 
			break;	
		}
	}
};

$(document).ready(
	function() {
		console.log( "ready for mqtt!" );
		MQTTconnect();
	}
);

function SendMessage (topic, payload) {
	mqtt.send(
		topic,
		payload,
		0, //qos: best effort
		false //retained: false = only to current subs
	)
}
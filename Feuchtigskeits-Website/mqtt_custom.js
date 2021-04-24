//settings for MQTT Broker
var host = '192.168.169.100';
var port = 9001;
var clientID = "Moistursensor_Webpage"; //by connect with random number 0-99
var topic = '#';
var useSSL = false;
var cleansession = true;
var mqtt;
var reconnectTimeout = 2000;

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
	$('#topic').html(' , subscribed to: ' + topic);
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
	//filtering debug messages from esp
	if(topic.includes('plants')) 
		console.log("Topic: " + topic + ", Message payload: " + payload); 
	//changes id "message" to topic, payload
	$('#message').html(topic + ', ' + payload);
	
	var message = topic.split('/');
	
	check_for_table(message, payload);
};

function SendMessage (topic, payload) {
	mqtt.send(
		topic,
		payload,
		0, //qos: best effort
		false //retained: false = only to current subs
	)
}

$(document).ready(
	function() {
		MQTTconnect();
		console.log( "ready for mqtt!" );
	}
);
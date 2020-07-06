
//filled by $(document).ready at the bottom
var hum_data 	= [[new Date(), 0]];
var temp_data 	= [[new Date(), 0]];
var water_data 	= [[new Date(), 0]];

//for drawing diagrams
var hum_counter = 0;
var tmp_counter = 0;
var wtr_counter = 0;

//get stored data
function get_localData(stored_element, element_data, element_counter, titel) {
	console.log("getting stored Data...");
	if (localStorage.getItem(stored_element) != null) {
		console.log("Data found: " + titel);
		var tempString 		= localStorage.getItem(stored_element);
		var splitString 	= tempString.split(',');
		var temp_counter 	= 0;
		while (temp_counter < splitString.length) {
			if(parseInt(splitString[temp_counter+1]) < 100) {
				element_data[element_counter] = [splitString[temp_counter], splitString[temp_counter+1]];
				element_counter++;
			}
			temp_counter = temp_counter + 2;
		}
		console.log(element_data);
		return element_data
	}
	else {
		console.log("No Data for " + titel);
		return element_data[element_counter] = [[new Date(), 0]];
	}
}
//extra function as we can't return two vars in the fkt above
function update_counter(data_array) {
	if (data_array.length == 1)
		return 0;
	else
		return data_array.length;
}

//for debugging if strang data is inserted, can be called by console
function clear_data() {
	localStorage.removeItem('stored_temp_data');
	localStorage.removeItem('stored_hum_data');
	console.log("cleared data");
}

//checks incoming message for relevance
function check_for_table(message, payload) {
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
						temp_data[tmp_counter] = [new Date(), payload];
						tmp_counter++;
						water_data[wtr_counter] = [new Date(), Math.floor(Math.random() * 100)];
						wtr_counter++;
						localStorage.setItem('stored_temp_data',temp_data);
						drawDiag2(temp_data);
						
						break;
					case 'hum':
						$('#P1_Hum').html(payload + '<span style="font-family: Arial,Helvetica,sans-serif;"> %</span>');
						
						hum_data[hum_counter] = [new Date(), payload];
						hum_counter++;
						localStorage.setItem('stored_hum_data',hum_data);
						drawDiag1(hum_data);
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
		if (localStorage.getItem('stored_temp_data') != null)
			document.title = temp_data[tmp_counter-1][1] + "°C / " + hum_data[hum_counter-1][1] + "%";
	}
}

//called by buttonclick in mainpage
function startWater() {
	console.log(document.getElementById("watertime").value);
	SendMessage ("water_ctrl", document.getElementById("watertime").value);
	console.log( "sent water command - time: " + document.getElementById("watertime").value ); 
			
}

$(document).ready(
	function() {
		hum_data = get_localData('stored_hum_data', hum_data, hum_counter, 'hum');
		hum_counter = update_counter(hum_data);
		temp_data = get_localData('stored_temp_data', temp_data, tmp_counter, 'temp');
		tmp_counter = update_counter(temp_data);
	}
);


//filled by $(document).ready at the bottom
var hum_data 	= [[new Date(), 0]];
var temp_data 	= [[new Date(), 0]];
var hum_data_24h = [[new Date(), 0]];

//for drawing diagrams
var hum_counter = 0;
var tmp_counter = 0;
var hum_data_24h_counter = 0;
var yesterday = new Date();
yesterday.setDate(yesterday.getDate() - 1);

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
				element_data[element_counter] = [new Date(splitString[temp_counter]), splitString[temp_counter+1]];
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
						localStorage.setItem('stored_temp_data',temp_data);
						drawDiag2(temp_data);
						
						break;
					case 'hum':
						$('#P1_Hum').html(payload + '<span style="font-family: Arial,Helvetica,sans-serif;"> %</span>');
						
						hum_data[hum_counter] = [new Date(), payload];
						hum_counter++;
						localStorage.setItem('stored_hum_data',hum_data);
						
						yesterday = new Date();
						yesterday.setDate(yesterday.getDate() - 1);

						hum_data_24h_counter = 0;
						hum_data_24h = [[new Date(), 0]];
						for (var tmp = 0; tmp < hum_counter; tmp++) {
							if (hum_data[tmp][0] > yesterday) {
								hum_data_24h[hum_data_24h_counter] = hum_data[tmp];
								hum_data_24h_counter++;
							}
						}
						drawDiag1(hum_data_24h);
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
	
	//check for water commands
	if (message[0] == "water_ctrl") {
		update_table_water(payload);
	}
	
	//updates page title
	if (tmp_counter>0 && hum_counter>0)
		document.title = temp_data[tmp_counter-1][1] + "°C / " + hum_data[hum_counter-1][1] + "%" + " / " + document.getElementById("P1_WaterTime").innerHTML;
}

//Daily watertimekeeping
var water_amount = 0;
var water_day = new Date().getDay()

//called by buttonclick in mainpage
function startWater() {
	var watertime = document.getElementById("watertime").value;
	SendMessage ("water_ctrl", watertime);
	console.log( "sent water command - time: " + watertime );
}

//change watertime
function update_table_water(payload) {
	console.log("updating water table");
	var today = new Date().getDay();
	if (water_day = today) {
		water_amount = water_amount + parseInt(payload);
	} else {
		water_amount = parseInt(payload);
		water_day = today;
	}
	
	localStorage.setItem('stored_water_amount',water_amount);
	localStorage.setItem('stored_water_day',water_day);
	
	if (water_amount > 60) {
		var water_min = (water_amount - water_amount % 60) / 60;
		var water_sek = water_amount % 60;
		$('#P1_WaterTime').text(water_min + ':' + ("00" + water_sek).slice(-2) + ' min');
	} else $('#P1_WaterTime').text(water_amount + ' s');
}

$(document).ready(
	function() {
		hum_data = get_localData('stored_hum_data', hum_data, hum_counter, 'hum');
		hum_counter = update_counter(hum_data);
		temp_data = get_localData('stored_temp_data', temp_data, tmp_counter, 'temp');
		tmp_counter = update_counter(temp_data);
		
		if (localStorage.getItem('stored_water_amount')  != null) {
			water_amount = parseInt(localStorage.getItem('stored_water_amount'));
			water_day = parseInt(localStorage.getItem('stored_water_day'));
			update_table_water(0);
		}
	}
);

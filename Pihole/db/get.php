<?php
   	
	
	include("connect.php");
   	$mysqli=Connection();

	$temp1	= isset($_GET['temp1']) ? $_GET['temp1'] : "666";
	$hum_p1	= isset($_GET['hum_p1']) ? $_GET['hum_p1'] : "666";
	$hum_r1	= isset($_GET['hum_r1']) ? $_GET['hum_r1'] : "666";
	$wlan1	= isset($_GET['wlan1']) ? $_GET['wlan1'] : "666";
	echo "Temp: ",$temp1,"°C Hum: ", $hum_p1,"% HumRaw: ", $hum_r1," RSSI: ", $wlan1,"dBm<br>";
	
	
	//Create our INSERT SQL query.
	$query = 	"INSERT INTO plant1 (temperature, hum_percentage, hum_raw, wlan_sig) 
							VALUES (?, ?, ?, ?)"; 
	
	$stmt = $mysqli->prepare($query);
	//4 ints given
	$stmt->bind_param("iiii", $temp1, $hum_p1, $hum_r1, $wlan1);
	$stmt->execute();
	if ($stmt->affected_rows === 0) exit('No rows updated');
	if ($stmt->affected_rows > 0) echo $stmt->affected_rows,' Row(s) inserted!<br>';
	
	$stmt->close();
?>

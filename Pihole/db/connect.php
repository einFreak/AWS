<?php
	
	function Connection(){
		$server="localhost";
		$user="esp8266";
		$pass="AutoWatering!";
		$db="aws";
		
		$mysqli = new mysqli($server, $user, $pass, $db);
		if($mysqli->connect_error) {
			exit('Error connecting to database'); //Should be a message a typical user could understand in production
		}
		mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
		$mysqli->set_charset("utf8mb4");
		
		return $mysqli;
	}
?>

<?php

	include("connect.php"); 	
	
	$mysqli=Connection();

	$sql_cmd1="SELECT * FROM plant1 ORDER BY timestamp DESC";
	$sql_cmd2="SELECT timestamp, temperature FROM plant1 ORDER BY timestamp DESC";
	
	$stmt = $mysqli->prepare($sql_cmd1);
	$stmt->execute();
	$result = $stmt->get_result();
	if($result->num_rows === 0) exit('No rows');
	
	$stmt2 = $mysqli->prepare($sql_cmd2);
	$stmt2->execute();
	$arr = $stmt2->get_result()->fetch_all(MYSQLI_NUM);
	if(!$arr) exit('No rows');
	
	echo "[";
    while ($row = $result->fetch_assoc()) { 
		echo "['";
		echo $row["timestamp"];
		echo "', ";
		echo $row["temperature"];
		echo "], ";
	}
	echo "]";
	$stmt->close();
	?>

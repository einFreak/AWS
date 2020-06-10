<?php
		echo "<br><br>Test<br>";
		include("connect.php"); 	
		$mysqli=Connection();

		$sql_cmd2="SELECT timestamp, temperature FROM plant1 ORDER BY timestamp DESC";
		
		$stmt2 = $mysqli->prepare($sql_cmd2);
		$stmt2->execute();
		$line2 = $stmt2->get_result()->fetch_all(MYSQLI_NUM);
		if(!$line2) exit('No rows');
		$db_temp = var_export($line2, true);
		$stmt2->close();
?>
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
	var_export($arr);
	$stmt2->close();
?>

<html>
   <head>
      <title>Sensor Data</title>
   </head>
<body>
   <h1>Temperature / moisture sensor readings</h1>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Timestamp&nbsp;</td>
			<td>&nbsp;Temperature 1&nbsp;</td>
			<td>&nbsp;Moisture 1&nbsp;</td>
		</tr>

    <?php while ($row = $result->fetch_assoc()) { ?>
		<tr>
		<td><?php echo $row["timestamp"]; ?></td>
		<td><?php echo $row["temperature"]; ?></td>
		<td><?php echo $row["hum_percentage"];?></td>
		</tr>
	<?php 
	} 
	$stmt->close();?>

   </table>
</body>
</html>

<?php
header('Content-Type: application/json');

//$mysqli = new mysqli("localhost", "root", "Bobby", "temaAjax");
$mysqli = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");
if ($mysqli->connect_errno) {
    echo json_encode(["error" => "Failed to connect to MySQL"]);
    exit();
}

$result = $mysqli->query("SELECT DISTINCT Oras1 FROM trasee ORDER BY Oras1");
$departures = [];
while ($row = $result->fetch_assoc()) {
    $departures[] = $row['Oras1'];
}

echo json_encode($departures);
?>

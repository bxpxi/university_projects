<?php
header('Content-Type: application/json');

//$mysqli = new mysqli("localhost", "root", "Bobby", "temaAjax");
$mysqli = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");
if ($mysqli->connect_errno) {
    http_response_code(500);
    echo json_encode(["error" => "Failed to connect to MySQL: " . $mysqli->connect_error]);
    exit;
}

$result = $mysqli->query("SELECT id FROM clienti ORDER BY id");
$ids = [];
while ($row = $result->fetch_assoc()) {
    $ids[] = $row['id'];
}
echo json_encode($ids);
?>

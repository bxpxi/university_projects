<?php
//$conn = new mysqli("localhost", "root", "Bobby", "temaAjax");
$conn = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");

$field = $_GET['field'];
$allowed = ['producator', 'procesor', 'memorie', 'hdd', 'placa_video'];

if (!in_array($field, $allowed)) {
  http_response_code(400);
  exit;
}

$result = $conn->query("SELECT DISTINCT $field FROM notebooks ORDER BY $field");
$data = [];

while ($row = $result->fetch_assoc()) {
  $data[] = $row[$field];
}

echo json_encode($data);

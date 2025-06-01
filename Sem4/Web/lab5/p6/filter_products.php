<?php
//$conn = new mysqli("localhost", "root", "Bobby", "temaAjax");
$conn = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");
$params = json_decode(file_get_contents("php://input"), true);

$sql = "SELECT * FROM notebooks WHERE 1";
$types = '';
$values = [];

foreach (['producator', 'procesor', 'memorie', 'hdd', 'placa_video'] as $field) {
  if (!empty($params[$field])) {
    $sql .= " AND $field = ?";
    $types .= is_numeric($params[$field]) ? 'i' : 's';
    $values[] = $params[$field];
  }
}

$stmt = $conn->prepare($sql);
if ($types) $stmt->bind_param($types, ...$values);

$stmt->execute();
$result = $stmt->get_result();
$data = [];

while ($row = $result->fetch_assoc()) {
  $data[] = $row;
}

echo json_encode($data);

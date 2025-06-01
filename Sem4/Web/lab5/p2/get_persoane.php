<?php
header('Content-Type: application/json');

$limit = 3;
$page = isset($_GET['page']) ? intval($_GET['page']) : 0;
$offset = $page * $limit;

//$mysqli = new mysqli("localhost", "root", "Bobby", "temaAjax");
$mysqli = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");
if ($mysqli->connect_errno) {
    echo json_encode(["error" => "DB connection error"]);
    exit();
}

$totalResult = $mysqli->query("SELECT COUNT(*) as total FROM persoane");
$total = $totalResult->fetch_assoc()['total'];

$stmt = $mysqli->prepare("SELECT * FROM persoane LIMIT ? OFFSET ?");
$stmt->bind_param("ii", $limit, $offset);
$stmt->execute();
$result = $stmt->get_result();

$data = [];
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

echo json_encode([
    "total" => $total,
    "limit" => $limit,
    "page" => $page,
    "data" => $data
]);
?>

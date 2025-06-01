<?php
header('Content-Type: application/json');

if (!isset($_GET['departure'])) {
    echo json_encode([]);
    exit();
}

$departure = $_GET['departure'];

//$mysqli = new mysqli("localhost", "root", "Bobby", "temaAjax");
$mysqli = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");
if ($mysqli->connect_errno) {
    echo json_encode(["error" => "Failed to connect to MySQL"]);
    exit();
}

$stmt = $mysqli->prepare("SELECT Oras2 FROM trasee WHERE Oras1 = ?");
$stmt->bind_param("s", $departure);
$stmt->execute();
$result = $stmt->get_result();

$arrivals = [];
while ($row = $result->fetch_assoc()) {
    $arrivals[] = $row['Oras2'];
}

echo json_encode($arrivals);
?>

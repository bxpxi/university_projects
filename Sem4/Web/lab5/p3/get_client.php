<?php
header("Content-Type: application/json");

$id = $_GET['id'] ?? null;
//$mysqli = new mysqli("localhost", "root", "Bobby", "temaAjax");
$mysqli = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");

if (!$mysqli->connect_error && $id !== null) {
    $stmt = $mysqli->prepare("SELECT * FROM clienti WHERE id = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($row = $result->fetch_assoc()) {
        echo json_encode($row);
    } else {
        echo json_encode(["error" => "Client not found"]);
    }
} else {
    echo json_encode(["error" => "Invalid connection or missing ID"]);
}
?>

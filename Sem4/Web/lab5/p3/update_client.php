<?php
$data = json_decode(file_get_contents("php://input"), true);

//$mysqli = new mysqli("localhost", "root", "Bobby", "temaAjax");
$mysqli = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");
$stmt = $mysqli->prepare("UPDATE clienti SET nume=?, prenume=?, telefon=?, email=? WHERE id=?");
$stmt->bind_param("ssssi", $data['nume'], $data['prenume'], $data['telefon'], $data['email'], $data['id']);
$stmt->execute();

echo json_encode(["status" => "success"]);
?>

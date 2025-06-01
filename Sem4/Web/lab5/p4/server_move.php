<?php
header("Content-Type: application/json");
$data = json_decode(file_get_contents("php://input"), true);

$tabla = $data["tabla"];

function checkWin($symbol, $t) {
    for ($i = 0; $i < 3; $i++) {
        if ($t[$i][0] === $symbol && $t[$i][1] === $symbol && $t[$i][2] === $symbol) return true;
        if ($t[0][$i] === $symbol && $t[1][$i] === $symbol && $t[2][$i] === $symbol) return true;
    }
    if ($t[0][0] === $symbol && $t[1][1] === $symbol && $t[2][2] === $symbol) return true;
    if ($t[0][2] === $symbol && $t[1][1] === $symbol && $t[2][0] === $symbol) return true;
    return false;
}

function tablaPlina($t) {
    foreach ($t as $row) {
        foreach ($row as $cell) {
            if ($cell === "") return false;
        }
    }
    return true;
}

$libere = [];
for ($i = 0; $i < 3; $i++) {
    for ($j = 0; $j < 3; $j++) {
        if ($tabla[$i][$j] === "") $libere[] = [$i, $j];
    }
}

if (checkWin("X", $tabla)) {
    echo json_encode(["tabla" => $tabla, "gata" => true, "mesaj" => "Ai câștigat!"]);
    exit;
}

if (tablaPlina($tabla)) {
    echo json_encode(["tabla" => $tabla, "gata" => true, "mesaj" => "Remiză!"]);
    exit;
}

if (!empty($libere)) {
    $mutare = $libere[array_rand($libere)];
    $tabla[$mutare[0]][$mutare[1]] = "0";

    if (checkWin("0", $tabla)) {
        echo json_encode(["tabla" => $tabla, "gata" => true, "mesaj" => "Calculatorul a câștigat!"]);
        exit;
    }
}

if (tablaPlina($tabla)) {
    echo json_encode(["tabla" => $tabla, "gata" => true, "mesaj" => "Remiză!"]);
    exit;
}

echo json_encode(["tabla" => $tabla, "gata" => false]);

<?php

$mysqli = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");
if ($mysqli->connect_error) {
    die("Eroare la conectarea bazei de date: " . $mysqli->connect_error);
}

function e($str) {
    return htmlspecialchars($str, ENT_QUOTES, 'UTF-8');
}

$plecare = trim($_POST['plecare'] ?? '');
$sosire = trim($_POST['sosire'] ?? '');
$doar_directe = isset($_POST['directe']);

if ($plecare === '' || $sosire === '') {
    die('Datele de plecare/sosire sunt obligatorii!');
}

if ($doar_directe) {
    $stmt = $mysqli->prepare("SELECT * FROM trenuri WHERE localitate_plecare = ? AND localitate_sosire = ?");
    $stmt->bind_param("ss", $plecare, $sosire);
    $stmt->execute();
    $rezultate = $stmt->get_result()->fetch_all(MYSQLI_ASSOC);
    $stmt->close();
} else {
    $stmt1 = $mysqli->prepare("SELECT * FROM trenuri WHERE localitate_plecare = ? AND localitate_sosire = ?");
    $stmt1->bind_param("ss", $plecare, $sosire);
    $stmt1->execute();
    $directe = $stmt1->get_result()->fetch_all(MYSQLI_ASSOC);
    $stmt1->close();

    // si care nu sunt directe
    $stmt2 = $mysqli->prepare(
        "SELECT t1.nr_tren AS tren1_nr, t1.tip_tren AS tren1_tip, t1.localitate_plecare AS plecare1, t1.localitate_sosire AS legatura, t1.ora_plecare AS ora_plecare1, t1.ora_sosire AS ora_sosire1,
                t2.nr_tren AS tren2_nr, t2.tip_tren AS tren2_tip, t2.localitate_plecare AS legatura2, t2.localitate_sosire AS sosire2, t2.ora_plecare AS ora_plecare2, t2.ora_sosire AS ora_sosire2
         FROM trenuri t1
         JOIN trenuri t2 ON t1.localitate_sosire = t2.localitate_plecare
         WHERE t1.localitate_plecare = ? AND t2.localitate_sosire = ?
           AND t1.ora_sosire < t2.ora_plecare"
    );
    $stmt2->bind_param("ss", $plecare, $sosire);
    $stmt2->execute();
    $legaturi = $stmt2->get_result()->fetch_all(MYSQLI_ASSOC);
    $stmt2->close();

    $rezultate = ['directe' => $directe, 'legaturi' => $legaturi];
}
?>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8" />
    <title>Rezultate cautare trenuri</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        table { border-collapse: collapse; width: 100%; margin-top: 20px; }
        th, td { border: 1px solid #ccc; padding: 8px; text-align: left; }
        th { background-color: #eee; }
        a { text-decoration: none; color: blue; }
        a:hover { text-decoration: underline; }
    </style>
</head>
<body>
    <h1>Rezultate cautare trenuri</h1>
    <p><a href="trenuri.html">← Înapoi la formular</a></p>

    <?php if ($doar_directe): ?>
        <?php if (!empty($rezultate)): ?>
            <table>
                <thead>
                    <tr>
                        <th>Nr. tren</th>
                        <th>Tip tren</th>
                        <th>Plecare</th>
                        <th>Sosire</th>
                        <th>Ora plecare</th>
                        <th>Ora sosire</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($rezultate as $tren): ?>
                        <tr>
                            <td><?= e($tren['nr_tren']) ?></td>
                            <td><?= e($tren['tip_tren']) ?></td>
                            <td><?= e($tren['localitate_plecare']) ?></td>
                            <td><?= e($tren['localitate_sosire']) ?></td>
                            <td><?= e($tren['ora_plecare']) ?></td>
                            <td><?= e($tren['ora_sosire']) ?></td>
                        </tr>
                    <?php endforeach; ?>
                </tbody>
            </table>
        <?php else: ?>
            <p>Nu s-au gasit curse directe pentru aceste localitati.</p>
        <?php endif; ?>
    <?php else: ?>
        <h2>Curse directe</h2>
        <?php if (!empty($rezultate['directe'])): ?>
            <table>
                <thead>
                    <tr>
                        <th>Nr. tren</th>
                        <th>Tip tren</th>
                        <th>Plecare</th>
                        <th>Sosire</th>
                        <th>Ora plecare</th>
                        <th>Ora sosire</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($rezultate['directe'] as $tren): ?>
                        <tr>
                            <td><?= e($tren['nr_tren']) ?></td>
                            <td><?= e($tren['tip_tren']) ?></td>
                            <td><?= e($tren['localitate_plecare']) ?></td>
                            <td><?= e($tren['localitate_sosire']) ?></td>
                            <td><?= e($tren['ora_plecare']) ?></td>
                            <td><?= e($tren['ora_sosire']) ?></td>
                        </tr>
                    <?php endforeach; ?>
                </tbody>
            </table>
        <?php else: ?>
            <p>Nu s-au gasit curse directe pentru aceste localitati.</p>
        <?php endif; ?>

        <h2>Curse cu legatura</h2>
        <?php if (!empty($rezultate['legaturi'])): ?>
            <table>
                <thead>
                    <tr>
                        <th>Tren 1 Nr</th>
                        <th>Tip</th>
                        <th>Plecare</th>
                        <th>Legătură</th>
                        <th>Ora plecare</th>
                        <th>Ora sosire</th>
                        <th>Tren 2 Nr</th>
                        <th>Tip</th>
                        <th>Legătură</th>
                        <th>Sosire</th>
                        <th>Ora plecare</th>
                        <th>Ora sosire</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($rezultate['legaturi'] as $leg): ?>
                        <tr>
                            <td><?= e($leg['tren1_nr']) ?></td>
                            <td><?= e($leg['tren1_tip']) ?></td>
                            <td><?= e($leg['plecare1']) ?></td>
                            <td><?= e($leg['legatura']) ?></td>
                            <td><?= e($leg['ora_plecare1']) ?></td>
                            <td><?= e($leg['ora_sosire1']) ?></td>

                            <td><?= e($leg['tren2_nr']) ?></td>
                            <td><?= e($leg['tren2_tip']) ?></td>
                            <td><?= e($leg['legatura2']) ?></td>
                            <td><?= e($leg['sosire2']) ?></td>
                            <td><?= e($leg['ora_plecare2']) ?></td>
                            <td><?= e($leg['ora_sosire2']) ?></td>
                        </tr>
                    <?php endforeach; ?>
                </tbody>
            </table>
        <?php else: ?>
            <p>Nu s-au gasit curse cu legatura pentru aceste localitati.</p>
        <?php endif; ?>
    <?php endif; ?>
</body>
</html>

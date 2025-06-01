<?php
$mysqli = new mysqli("localhost", "bpir3489", "YzUxYjM2NzMx", "bpir3489");
if ($mysqli->connect_error) {
    die("Eroare conectare BD: " . $mysqli->connect_error);
}

function e($str) {
    return htmlspecialchars($str, ENT_QUOTES, 'UTF-8');
}

$nr = isset($_GET['nr']) ? (int)$_GET['nr'] : 10;
if ($nr <= 0 || $nr > 100) $nr = 10;

$page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
if ($page < 1) $page = 1;

$result = $mysqli->query("SELECT COUNT(*) as total FROM produse");
$total = $result->fetch_assoc()['total'];
$result->free();

$total_pag = ceil($total / $nr);
if ($page > $total_pag) $page = $total_pag;

$start = ($page -1) * $nr;

$stmt = $mysqli->prepare("SELECT * FROM produse LIMIT ?, ?");
$stmt->bind_param("ii", $start, $nr);
$stmt->execute();
$res = $stmt->get_result();
$produse = $res->fetch_all(MYSQLI_ASSOC);
$stmt->close();
?>

<!DOCTYPE html>
<html lang="ro">
<head>
<meta charset="UTF-8">
<title>Produse paginat</title>
<style>
    body { font-family: Arial, sans-serif; margin: 20px; }
    table { border-collapse: collapse; width: 100%; margin-top: 20px; }
    th, td { border: 1px solid #ccc; padding: 8px; }
    th { background-color: #eee; }
    nav a { margin: 0 5px; text-decoration: none; color: blue; }
    nav a:hover { text-decoration: underline; }
</style>
</head>
<body>
    <h1>Produse</h1>

    <form method="get" action="produse.php">
        <label for="nr">Numar produse pe pagina:</label>
        <select name="nr" id="nr" required>
            <option value="5" <?= $nr == 5 ? 'selected' : '' ?>>5</option>
            <option value="10" <?= $nr == 10 ? 'selected' : '' ?>>10</option>
            <option value="20" <?= $nr == 20 ? 'selected' : '' ?>>20</option>
        </select>
        <button type="submit">Seteaza</button>
    </form>

    <?php if(count($produse) > 0): ?>
    <table>
        <thead>
            <tr>
                <th>ID</th>
                <th>Nume</th>
                <th>Descriere</th>
                <th>Pret</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach($produse as $prod): ?>
                <tr>
                    <td><?= e($prod['id']) ?></td>
                    <td><?= e($prod['nume']) ?></td>
                    <td><?= e($prod['descriere']) ?></td>
                    <td><?= e($prod['pret']) ?> RON</td>
                </tr>
            <?php endforeach; ?>
        </tbody>
    </table>

    <nav>
        <?php if($page > 1): ?>
            <a href="produse.php?nr=<?= $nr ?>&page=<?= $page - 1 ?>">&laquo; Anterior</a>
        <?php endif; ?>
        <?php if($page < $total_pag): ?>
            <a href="produse.php?nr=<?= $nr ?>&page=<?= $page + 1 ?>">Urmator &raquo;</a>
        <?php endif; ?>
    </nav>

    <?php else: ?>
        <p>Nu exista produse de afisat.</p>
    <?php endif; ?>

    <p><a href="produse.html">Inapoi la setare nr produse pe pagina</a></p>
</body>
</html>

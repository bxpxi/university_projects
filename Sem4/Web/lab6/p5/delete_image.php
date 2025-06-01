<?php
session_start();

if (!isset($_SESSION['username'])) {
    header("Location: login.php");
    exit();
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["image_id"])) {
    
    $servername = "localhost";
    $username = "bpir3489";
    $password = "YzUxYjM2NzMx";
    $dbname = "bpir3489";
    

    /*
    $servername = "localhost";
    $username = "root";
    $password = "Bobby";
    $dbname = "temaphp";
    */

    $conn = new mysqli($servername, $username, $password, $dbname);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $image_id = $_POST["image_id"];
    $username = $_SESSION['username'];

    $stmt = $conn->prepare("DELETE FROM images WHERE id = ? AND username = ?");
    $stmt->bind_param("is", $image_id, $username);
    $stmt->execute();

    if ($stmt->affected_rows > 0) {
        echo "Image deleted successfully.";
    } else {
        echo "Error deleting image.";
    }

    $conn->close();
}

header("Location: profile.php");
exit();
?>
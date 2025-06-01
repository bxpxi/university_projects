<?php
session_start();


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

$username = $_POST['username'];
$sql = "SELECT * FROM users WHERE nume = '$username'";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    $_SESSION['username'] = $username;
    header('Location: profile.php');
    exit();
} else {
    echo "Invalid username.";
    echo '<form action="'. $_SERVER['HTTP_REFERER'] .'" method="get">';
    echo '<button type="submit">Back</button>';
    echo '</form>';
}

$conn->close();
?>
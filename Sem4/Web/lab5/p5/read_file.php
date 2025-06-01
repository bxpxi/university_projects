<?php
$base = realpath(__DIR__ . '/root');
$path = isset($_GET['path']) ? $_GET['path'] : '';
$fullPath = realpath($base . '/' . $path);

if (!$fullPath || strpos($fullPath, $base) !== 0 || is_dir($fullPath)) {
    http_response_code(400);
    echo 'Invalid file.';
    exit;
}

echo htmlspecialchars(file_get_contents($fullPath));

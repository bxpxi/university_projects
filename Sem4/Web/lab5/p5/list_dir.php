<?php
$base = realpath(__DIR__ . '/root'); 
$path = isset($_GET['path']) ? $_GET['path'] : '';

$fullPath = realpath($base . '/' . $path);

if (!$fullPath || strpos($fullPath, $base) !== 0) {
    http_response_code(400);
    echo json_encode(['error' => 'Invalid path']);
    exit;
}

$items = scandir($fullPath);
$result = [];

foreach ($items as $item) {
    if ($item === '.' || $item === '..') continue;

    $itemPath = $fullPath . '/' . $item;
    $isDir = is_dir($itemPath);
    $result[] = [
        'name' => $item,
        'isDir' => $isDir
    ];
}

header('Content-Type: application/json');
echo json_encode($result);

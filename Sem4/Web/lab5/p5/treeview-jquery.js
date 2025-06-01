function createNode(item, currentPath) {
  const $li = $('<li>').text(item.name);

  if (item.isDir) {
    $li.addClass('folder');
    $li.on('click', function (e) {
      e.stopPropagation();
      if ($li.data('loaded')) return;

      $.getJSON('list_dir.php', { path: currentPath + '/' + item.name }, function (data) {
        const $ul = $('<ul>');
        data.forEach(subItem => {
          $ul.append(createNode(subItem, currentPath + '/' + item.name));
        });
        $li.append($ul);
        $li.data('loaded', true);
      });
    });
  } else {
    $li.addClass('file');
    $li.on('click', function (e) {
      e.stopPropagation();
      $.get('read_file.php', { path: currentPath + '/' + item.name }, function (data) {
        $('#fileContent').text(data);
      });
    });
  }

  return $li;
}

$(function () {
  $.getJSON('list_dir.php', { path: '' }, function (data) {
    const $ul = $('<ul>');
    data.forEach(item => {
      $ul.append(createNode(item, ''));
    });
    $('#treeView').append($ul);
  });
});

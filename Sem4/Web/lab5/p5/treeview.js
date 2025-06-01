function createNode(item, currentPath) {
  const li = document.createElement('li');
  li.textContent = item.name;

  if (item.isDir) {
    li.classList.add('folder');
    li.addEventListener('click', function (e) {
      e.stopPropagation();
      if (li.dataset.loaded) return;

      fetch(`list_dir.php?path=${encodeURIComponent(currentPath + '/' + item.name)}`)
        .then(res => res.json())
        .then(data => {
          const ul = document.createElement('ul');
          data.forEach(subItem => {
            ul.appendChild(createNode(subItem, currentPath + '/' + item.name));
          });
          li.appendChild(ul);
          li.dataset.loaded = true;
        });
    });
  } else {
    li.classList.add('file');
    li.addEventListener('click', function (e) {
      e.stopPropagation();
      fetch(`read_file.php?path=${encodeURIComponent(currentPath + '/' + item.name)}`)
        .then(res => res.text())
        .then(content => {
          document.getElementById('fileContent').textContent = content;
        });
    });
  }

  return li;
}

function loadRoot() {
  fetch('list_dir.php?path=')
    .then(res => res.json())
    .then(data => {
      const ul = document.createElement('ul');
      data.forEach(item => {
        ul.appendChild(createNode(item, ''));
      });
      document.getElementById('treeView').appendChild(ul);
    });
}

document.addEventListener('DOMContentLoaded', loadRoot);

function fetchOptions(field) {
  fetch(`load_options.php?field=${field}`)
    .then(res => res.json())
    .then(data => {
      const select = document.getElementById(field);
      select.innerHTML = `<option value="">-- toate --</option>`;
      data.forEach(value => {
        const opt = document.createElement('option');
        opt.value = value;
        opt.textContent = value;
        select.appendChild(opt);
      });
    });
}

function filterProducts() {
  const fields = ['producator', 'procesor', 'memorie', 'hdd', 'placa_video'];
  const data = {};
  fields.forEach(f => {
    data[f] = document.getElementById(f).value;
  });

  fetch('filter_products.php', {
    method: 'POST',
    headers: {'Content-Type': 'application/json'},
    body: JSON.stringify(data)
  })
  .then(res => res.json())
  .then(products => {
    const results = document.getElementById('results');
    if (products.length === 0) {
      results.innerHTML = 'Niciun rezultat.';
      return;
    }

    let html = '<table><tr><th>Nume</th><th>Producător</th><th>Procesor</th><th>Memorie</th><th>HDD</th><th>Placa video</th></tr>';
    products.forEach(p => {
      html += `<tr>
        <td>${p.nume}</td><td>${p.producator}</td><td>${p.procesor}</td>
        <td>${p.memorie}</td><td>${p.hdd}</td><td>${p.placa_video}</td>
      </tr>`;
    });
    html += '</table>';
    results.innerHTML = html;
  });
}

document.addEventListener('DOMContentLoaded', () => {
  ['producator', 'procesor', 'memorie', 'hdd', 'placa_video'].forEach(field => {
    fetchOptions(field);
    document.getElementById(field).addEventListener('change', filterProducts);
  });

  filterProducts(); 
});

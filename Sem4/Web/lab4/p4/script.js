$(document).ready(function () {
  $('th').on('click', function () {
    const type = $(this).data('type'); 
    const index = parseInt($(this).data(type === 'row' ? 'col' : 'row'));

    if (type === 'row') {
      sortTableByRow('#tabel', index);
    } else {
      sortTableByColumn('#tabel2', index);
    }
  });

  function sortTableByRow(tableId, colIndex) {
    const rows = $(tableId).find('tr').slice(1).get();
    const isNumeric = $.isNumeric($(rows[0]).children().eq(colIndex).text());

    rows.sort((a, b) => {
      let A = $(a).children().eq(colIndex).text();
      let B = $(b).children().eq(colIndex).text();
      if (isNumeric) { A = parseFloat(A); B = parseFloat(B); }
      return A > B ? 1 : -1;
    });

    const asc = $(tableId).data('asc');
    if (asc) rows.reverse();
    $(tableId).data('asc', !asc);

    $.each(rows, function (_, row) {
      $(tableId).append(row);
    });
  }

  function sortTableByColumn(tableId, rowIndex) {
    const table = $(tableId);
    const row = table.find('tr').eq(rowIndex);
    const cells = row.find('td').get();
    const isNumeric = $.isNumeric($(cells[0]).text());

    const asc = table.data('asc-' + rowIndex) || false;

    const indices = cells.map((cell, i) => i);

    indices.sort((i, j) => {
      let A = $(cells[i]).text(), B = $(cells[j]).text();
      if (isNumeric) { A = parseFloat(A); B = parseFloat(B); }
      return A > B ? 1 : -1;
    });

    if (asc) indices.reverse();
    table.data('asc-' + rowIndex, !asc);

    
    table.find('tr').each(function () {
      const tds = $(this).find('td').get();
      const reordered = indices.map(i => $(tds[i]).clone());
      $(this).find('td').remove();
      $(this).append(reordered);
    });
  }
});

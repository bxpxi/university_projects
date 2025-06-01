function fetchOptions(field) {
  $.getJSON("load_options.php", { field }, function(data) {
    const $select = $("#" + field);
    $select.html('<option value="">-- toate --</option>');
    data.forEach(function(val) {
      $select.append(`<option value="${val}">${val}</option>`);
    });
  });
}

function filterProducts() {
  const data = {
    producator: $("#producator").val(),
    procesor: $("#procesor").val(),
    memorie: $("#memorie").val(),
    hdd: $("#hdd").val(),
    placa_video: $("#placa_video").val()
  };

  $.ajax({
    url: "filter_products.php",
    method: "POST",
    contentType: "application/json",
    data: JSON.stringify(data),
    success: function(products) {
      if (products.length === 0) {
        $("#results").html("Niciun rezultat.");
        return;
      }

      let html = "<table><tr><th>Nume</th><th>Producator</th><th>Procesor</th><th>Memorie</th><th>HDD</th><th>Placa video</th></tr>";
      products.forEach(p => {
        html += `<tr>
          <td>${p.nume}</td><td>${p.producator}</td><td>${p.procesor}</td>
          <td>${p.memorie}</td><td>${p.hdd}</td><td>${p.placa_video}</td>
        </tr>`;
      });
      html += "</table>";
      $("#results").html(html);
    }
  });
}

$(function () {
  ['producator', 'procesor', 'memorie', 'hdd', 'placa_video'].forEach(field => {
    fetchOptions(field);
    $("#" + field).on("change", filterProducts);
  });

  filterProducts();
});

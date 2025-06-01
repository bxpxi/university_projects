function sortBy(n) {
    var tabel = document.getElementById('tabel1')
    var tipSort = ""
    var a, b, i, j
    var rows = tabel.rows

    a=rows[1].getElementsByTagName("td")[n-1].innerHTML.toLowerCase()
    b=rows[2].getElementsByTagName("td")[n-1].innerHTML.toLowerCase()

    if(!isNaN(parseInt(a)) && !isNaN(parseInt(b))) {
        a = parseInt(a)
        b = parseInt(b)
    }

    if(a > b) { 
        tipSort = "asc"
    } else {
        tipSort = "desc"
    }

    for(i=1;i<rows.length-1;i++) {
        for(j=i+1;j<rows.length;j++) {
            var ok = false
            a = rows[i].getElementsByTagName("td")[n-1].innerHTML.toLowerCase()
            b = rows[j].getElementsByTagName("td")[n-1].innerHTML.toLowerCase()

            if(!isNaN(parseInt(a)) && !isNaN(parseInt(b))) {
                a = parseInt(a)
                b = parseInt(b)
            }

            if(tipSort == "asc") {
                if(a>b) {
                    ok=true
                }
            } else if(tipSort == "desc") {
                if(a<b) {
                    ok=true
                }
            }

            if(ok) {
                var aux = rows[i].innerHTML
                rows[i].innerHTML = rows[j].innerHTML
                rows[j].innerHTML = aux
            }
        }
        console.log("i=",i)
    }
}

function sortBy2(n) {
    var tabel = document.getElementById("tabel2")
    var tipSort = ""
    var a, b, i, j, k
    var rows = tabel.rows
    var row = rows[n-1]

    a=row.getElementsByTagName("td")[0].innerHTML.toLowerCase()
    b=row.getElementsByTagName("td")[1].innerHTML.toLowerCase()

    if(!isNaN(parseInt(a)) && !isNaN(parseInt(b))) {
        a = parseInt(a)
        b = parseInt(b)
    }

    if(a > b) { 
        tipSort = "asc"
    } else {
        tipSort = "desc"
    }

    for(i=0;i<row.cells.length-2;i++) {
        for(j=i+1;j<row.cells.length-1;j++) {
            var ok=false
            a=row.getElementsByTagName("td")[i].innerHTML.toLowerCase()
            b=row.getElementsByTagName("td")[j].innerHTML.toLowerCase()

            if(!isNaN(parseInt(a)) && !isNaN(parseInt(b))) {
                a = parseInt(a)
                b = parseInt(b)
            }

            if(tipSort == "asc") {
                if(a>b) {
                    ok=true
                }
            } else if(tipSort == "desc") {
                if(a<b) {
                    ok=true
                }
            }

            if(ok) {
                for(k=0;k<rows.length;k++) {
                    var tempCol = rows[k].getElementsByTagName("td")[i].innerHTML;
                    var tempVal = rows[k].getElementsByTagName("td")[j].innerHTML;
                    rows[k].getElementsByTagName("td")[i].innerHTML = tempVal
                    rows[k].getElementsByTagName("td")[j].innerHTML = tempCol
                }
            }
        }
    }
}
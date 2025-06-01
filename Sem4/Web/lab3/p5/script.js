document.addEventListener("DOMContentLoaded", function() {
    setCurrent(0);

    setInterval(function() {
        var currentIndex = getCurrentIndex()
        var elems = document.querySelectorAll("#list li")
        var nr = elems.length
        currentIndex++
        if(currentIndex === nr) {
            currentIndex = 0
        }
        setCurrent(currentIndex)
    }, 5000)
})

function changeImage(n) {
    var elems = document.querySelectorAll("#list li")
    var nr = elems.length
    var currentIndex = getCurrentIndex()
    if(n==1) {
        currentIndex++;
        if(currentIndex === nr) {
            currentIndex = 0
        }
    } else {
        currentIndex--
        if(currentIndex === -1) {
            currentIndex = nr - 1
        }
    }
    setCurrent(currentIndex)
}

function setCurrent(index) {
    var valDiv = document.getElementById("currentImage")
    valDiv.innerHTML = ''
    var elem = document.querySelectorAll("#list li")[index]
    var image = elem.firstElementChild.cloneNode(true)
    var link = document.createElement("a")
    link.href = elem.lastElementChild.href
    link.appendChild(image)
    valDiv.appendChild(link)
}

function getCurrentIndex() {
    var elems = document.querySelectorAll("#list li")
    var valDiv = document.getElementById("currentImage")
    var nr = elems.length
    var currentIndex = 0
    for(let i=0;i<nr;i++) {
        if(valDiv.querySelector("img").src === elems[i].querySelector("img").src) {
            if(valDiv.querySelector("a").ahref === elems[i].querySelector("a").ahref) {
                currentIndex = i
            }
        }
    }
    return currentIndex
}
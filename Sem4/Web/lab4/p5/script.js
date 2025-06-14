$(document).ready(function() {
    setCurrent(0);

    setInterval(function() {
        var currentIndex = getCurrentIndex();
        var elems = $("#lista li");
        var nr = elems.length;

        currentIndex++;
        if (currentIndex === nr) {
            currentIndex = 0;
        }
        setCurrent(currentIndex);
    }, 3000);

    $("#prevButton").click(function() {
        changeImg(-1);
    });

    $("#nextButton").click(function() {
        changeImg(1);
    });
});

function changeImg(n) {
    var elems = $("#lista li");
    var nr = elems.length;

    var currentIndex = getCurrentIndex();

    if (n === 1) {
        currentIndex++;
        if (currentIndex === nr) {
            currentIndex = 0;
        }
    } else {
        currentIndex--;
        if (currentIndex === -1) {
            currentIndex = nr - 1;
        }
    }
    setCurrent(currentIndex);
}

function setCurrent(ind) {
    var valDiv = $("#imgCurenta");
    valDiv.empty(); 
    var element = $("#lista li").eq(ind);
    var imagine = element.find("img").clone();
    var link = $("<a>").attr("href", element.find("a").attr("href")).append(imagine);
    valDiv.append(link);
}

function getCurrentIndex() {
    var elems = $("#lista li");
    var valDiv = $("#imgCurenta");

    var nr = elems.length;
    var currentIndex = 0;

    elems.each(function(i, el) {
        if ($(el).find("img").attr("src") === valDiv.find("img").attr("src")) {
            if ($(el).find("a").attr("href") === valDiv.find("a").attr("href")) {
                currentIndex = i;
            }
        }
    });

    return currentIndex;
}

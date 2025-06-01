$(document).ready(function() {
    const tabel = $('#tabel').empty();
    let values = ["1.jpg", "1.jpg", '2.jpg', '2.jpg', '3.jpg', '3.jpg', '4.jpg', '4.jpg', '5.jpg', '5.jpg', '6.jpg', '6.jpg', '7.jpg', '7.jpg', '8.jpg', '8.jpg'];

    values.forEach(function (src) {
        const img = new Image();
        img.src = src;
    });

    for (let i = values.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [values[i], values[j]] = [values[j], values[i]];
    }

    const n = Math.floor(Math.sqrt(values.length));
    let firstClicked = null;
    let secondClicked = null;
    let isChecking = false;

    function checkMatching($item) {
        if (isChecking || $item.hasClass('revealed')) return;

        const imgPath = $item.data('img');
        const img = $('<img>').attr('src', imgPath);
        $item.append(img).addClass('revealed');

        if (!firstClicked) {
            firstClicked = $item;
        } else if (!secondClicked) {
            secondClicked = $item;
            isChecking = true;

            if (firstClicked.data('img') === secondClicked.data('img')) {
                firstClicked = null;
                secondClicked = null;
                isChecking = false;
            } else {
                setTimeout(() => {
                    firstClicked.add(secondClicked)
                        .removeClass('revealed')
                        .empty()
                        .css('background-color', 'palevioletred');
                    firstClicked = null;
                    secondClicked = null;
                    isChecking = false;
                }, 1000);
            }
        }
    }

    for (let i = 0; i < n; i++) {
        const row = $('<tr>');
        for (let j = 0; j < n; j++) {
            const value = values[i * n + j];
            const cell = $('<td>')
                .data('img', value)
                .on('click', function() {
                    checkMatching($(this));
                });
            row.append(cell);
        }
        tabel.append(row);
    }
});

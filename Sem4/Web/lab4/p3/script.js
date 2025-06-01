$(document).ready(function() {
    const tabel = $('#tabel').empty();
    let values = [1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8];

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

        $item.text($item.data('value')).addClass('revealed');

        if (!firstClicked) {
            firstClicked = $item;
        } else if (!secondClicked) {
            secondClicked = $item;
            isChecking = true;

            if (firstClicked.data('value') === secondClicked.data('value')) {
                firstClicked = null;
                secondClicked = null;
                isChecking = false;
            } else {
                setTimeout(() => {
                    firstClicked.add(secondClicked).removeClass('revealed').text('');
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
                .data('value', value)
                .css('background-color', 'palevioletred')
                .on('click', function() {
                    checkMatching($(this));
                });
            row.append(cell);
        }
        tabel.append(row);
    }
});

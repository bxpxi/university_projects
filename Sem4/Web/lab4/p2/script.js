$(document).ready(function() {
    $('#submit').click(function() {
        var nume = $('#nume').val()
        var data_nasterii = new Date($('#data_nasterii').val())
        var varsta = $('#varsta').val()
        var email = $('#email').val()
        var mesaj = ''

        var valid = 1
        if(nume.length == 0) {
            valid = 0
            mesaj += 'Numele nu a fost completat.<br>'
        }
        for(let c of nume)
            if(c >= '0' && c <= '9') {
                valid = 0
                mesaj += 'Numele poate contine doar litere.<br>'
            }
        if(valid == 0)
            $('#nume').css('border-color', 'red')
        else
            $('#nume').css('border-color', 'black')

        valid = 1
        if(!data_nasterii || isNaN(data_nasterii.getTime())) {
            valid = 0
            mesaj += 'Data nasterii nu a fost completata.<br>'
        }
        if(data_nasterii > Date.now()) {
            valid = 0
            mesaj += 'Data nasterii nu poate fi in viitor.<br>'
        }
        if(valid == 0)
            $('#data_nasterii').css('border-color', 'red')
        else
            $('#data_nasterii').css('border-color', 'black')

        valid = 1
        if(varsta < 0 || varsta > 120) {
            valid = 0
            mesaj += 'Varsta nu poate fi negativa sau mai mare ca 120.<br>'
        }
        if(valid == 0)
            $('#varsta').css('border-color', 'red')
        else
            $('#varsta').css('border-color', 'black')

        valid = 1
        if(email.length == 0) {
            valid = 0
            mesaj += 'Email-ul nu a fost completat.<br>'
        }
        if(!email.match(/^[^\s@]+@[^\s@]+\.[^\s@]+$/)) {
            valid = 0
            mesaj += 'Email-ul nu este valid.<br>'
        }
        if(valid == 0)
            $('#email').css('border-color', 'red')
        else
            $('#email').css('border-color', 'black')

        if(mesaj == '')
            $('#mesaj').html('Totul e corect! Felicitari!')
        else
            $('#mesaj').html(mesaj)
    })
})

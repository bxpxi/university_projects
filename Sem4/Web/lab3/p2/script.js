function validate() {
    let nume = document.getElementById('nume').value;
    let varsta = document.getElementById('varsta').value;
    let email = document.getElementById('email').value;
    let data_nasterii = document.getElementById('data_nasterii').value;
    let message = "";

    let valid = 1;

    if(nume.length == 0) {
        ok = 0;
        message += "Numele nu poate fi necompletat.<br>"
    }
    for(let ch of nume) {
        if(!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
            ok = 0;
            message += "Nume invalid.<br>"
        }
    }
    if(ok == 0) {
        document.getElementById('nume').style.borderColor = "red";
    }

    valid = 1;
    if(!data_nasterii) {
        valid = 0;
        message += "Data nasterii nu poate fi necompletata.<br>"
    }
    if(data_nasterii > Date.now()) {
        valid = 0;
        message += "Data nasterii invalida.<br>"
    }
    if(valid == 0) {
        document.getElementById('data_nasterii').style.borderColor = "red"
    }

    valid = 1
    if(varsta.length == 0) {
        valid = 0
        message += "Varsta nu poate fi necompletata.<br>"
    }
    for(let char of varsta) {
        if(!(char >= '0' && char <= '9')) {
            valid = 0
            message += 'Varsta invalida.<br>'
        }
    }
    if(valid == 0) {
        document.getElementById('varsta').style.borderColor = 'red'
    }

    valid = 1
    if(email.length == 0) {
        valid = 0
        message += "Email nu poate fi necompletat.<br>"
    }
    if(!email.match(/^.*@.*$/g)) {
        valid = 0
        message += "Email invalid.<br>"
    }
    if(valid == 0) {
        document.getElementById('email').style.borderColor = 'red'
    }

    if(message == "") {
        document.getElementById("message").innerHTML = "Corect!!"
    } else {
        document.getElementById("message").innerHTML = message
    }
}

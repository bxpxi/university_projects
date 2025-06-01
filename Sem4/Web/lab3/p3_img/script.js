const tabel = document.getElementById("tabel");
tabel.innerHTML = "";
let values = [1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8];
let imgString = ["1.png", "2.webp", "3.jpg", "4.png", "5.png", "6.webp", "7.jpg", "8.jpg"]

for (let i = values.length - 1; i > 0; i--) {
   const j = Math.floor(Math.random() * (i + 1));
   [values[i], values[j]] = [values[j], values[i]];
}

const dim = Math.sqrt(values.length);
for(let i = 0; i < dim; i++){
	var row = tabel.insertRow(i);
	for(let j = 0; j < dim; j++){
		const item = document.createElement("td");
		item.textContent = values[dim * i + j];
		item.style.backgroundColor = "black";
		row.insertCell(j).appendChild(item);
		item.addEventListener("click",()=>checkItems(item));
	}
	tabel.appendChild(row);
}

let firstItem = null;
let secondItem = null;

function checkItems(item){
	if(item.style.backgroundColor === "white"){
		return;
	}

	item.style.backgroundColor = "white";
	var index = item.textContent;
	item.style.backgroundImage = `url(${imgString[index - 1]})`;

	if(firstItem === null)
		firstItem = item;
	else if(secondItem === null){
		secondItem = item;

		if(firstItem.textContent === secondItem.textContent){
			firstItem = null;
			secondItem = null;
		}
		else{
			setTimeout(() => {
				firstItem.style.backgroundColor = "black";
				secondItem.style.backgroundColor = "black";
				firstItem.style.backgroundImage = "";
				secondItem.style.backgroundImage = "";
				firstItem = null;
				secondItem = null;
			}, 1000);
		}
	}
}

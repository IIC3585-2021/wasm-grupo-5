import Module from "./main.js"



const makePtrOfArray = (myModule, matrix) => {
    const n = matrix.length;
    console.log("hola");
    console.log(matrix);
    console.log("hola");

    const arrayPtr = myModule._calloc(n, 4);
    for (let i = 0; i < n; i++) {
        let rowsPtr = myModule._calloc(n, 4);
        myModule.setValue(arrayPtr + i * 4, rowsPtr, "i32");
        for (let j = 0; j < n; j++) {
            myModule.setValue(rowsPtr + j * 4, matrix[i][j], "i32");
        }
    }
    return arrayPtr;
}

const getCost = (myModule, ptr) => {
    let costo = myModule.getValue(ptr, "i32");
    return costo;
}

function buildMatrix() {
    let inputValue = document.getElementById('input-show').innerHTML;
    var meanWhile = inputValue.split(",").map(item => item.split("/").map(item2 => item2.split("-")));
    var dict = {}

    let i = 0;
    while (i < meanWhile.length) {
        dict[meanWhile[i][0][0]]={};
        dict[meanWhile[i][0][1]]={};
        i++;
    }
    let j = 0;
    while (j < meanWhile.length) {
        let origen = meanWhile[j][0][0];
        let destino = meanWhile[j][0][1];
        let distancia = meanWhile[j][1][0];
        dict[origen][destino]=distancia;
        dict[destino][origen]=distancia;
        j++;
    }

    const origenes=Object.keys(dict);
    let matriz = []

    let k = 0;
    while (k < origenes.length) {
        let lista = []
        let destinos= Object.keys(dict[origenes[k]]);

        let s = 0;
        while (s < origenes.length) {
            if (origenes[s] == origenes[k]) {
                lista.push(0);
            }
            else if (!destinos.includes(origenes[s])) {
                lista.push(-1)
            }
            else if (destinos.includes(origenes[s])) {
                lista.push(parseInt(dict[origenes[k]][origenes[s]]))
            }
            s++;
        }
        matriz.push(lista);
        k++;
    }
    return [origenes,matriz];
};

let inputListo = "";
let addBtn  = document.getElementById('agregar-union');
addBtn.onclick = () => {
    let pormientas = "";
    let origen = document.getElementById('origen').value;
    let destino = document.getElementById('destino').value;
    let distancia = document.getElementById('distancia').value;
    if (inputListo.length > 0) {
        pormientas += ","+origen+"-"+destino+"/"+distancia;
    }
    else {
        pormientas += origen+"-"+destino+"/"+distancia;
    }
    document.getElementById('origen').value = '';
    document.getElementById('destino').value = '';
    document.getElementById('distancia').value = '';
    inputListo += pormientas;
    document.getElementById('input-show').innerHTML = inputListo;
}


Module().then(function (mymod) {
    let solveBtn = document.getElementById("button-grafo");
    solveBtn.onclick = () => {

        let [origenes, matrix] = buildMatrix();
        let n = matrix.length;

        let arrPtr = makePtrOfArray(mymod, matrix);
        let mejorsuma = mymod._calloc(1, 4);
        mymod.setValue(mejorsuma, 999, "i32")
        let mejorsecuencia = mymod._calloc(n, 4);
        let camino = mymod._calloc(n, 4);
        let visited = mymod._calloc(n, 4);

        let startDate = window.performance.now();
        mymod._findpath(arrPtr, n, mejorsuma, mejorsecuencia, camino, visited);
        let endDate = window.performance.now();

        let costo = mymod.getValue(mejorsuma, "i32");
        let caminofinal = "-> ";
        for (let i=0; i<n; i++){
            var elem = mymod.getValue(mejorsecuencia + 4*i, "i32");
            caminofinal += origenes[elem] + " -> ";
        }

        console.log(caminofinal);
        alert(`TIEMPO DE EJECUCION: ${endDate-startDate}\n COSTO TOTAL: ${costo}\n CAMINO A RECORRER: ${caminofinal}`)
    }
})



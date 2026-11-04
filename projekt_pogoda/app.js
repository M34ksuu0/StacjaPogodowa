
const tabela = document.getElementById("tabela");
const wyniki = document.getElementById("wyniki");

function pokazTabele(element, dane) {

    element.innerHTML = "";

    for (let i = 0; i < dane.size(); i++) {

        const p = dane.get(i);

        const tr = document.createElement("tr");

        [
            p.id,
            p.data,
            p.temperatura + " °C",
            p.wiatr
        ].forEach(wartosc => {

            const td = document.createElement("td");

            td.textContent = wartosc;

            tr.appendChild(td);
        });

        element.appendChild(tr);
    }

    dane.delete();
}


// Automatyczne wczytywanie pliku a.txt
async function wczytajPlik() {

    try {

        document.getElementById("status").textContent =
            "Wczytywanie danych pogodowych...";

        const odpowiedz = await fetch("a.txt");

        if (!odpowiedz.ok) {
            throw new Error("Nie znaleziono pliku a.txt");
        }

        const tekst = await odpowiedz.text();

        // Przekazanie danych do C++
        Module.wczytajDane(tekst);

        if (!Module.czySaDane()) {
            throw new Error("Brak poprawnych pomiarów.");
        }

        Module.daneWczytane = true;

        // Pobranie wszystkich danych
        const dane = Module.pobierzDane();

        document.getElementById("liczba").textContent =
            dane.size();

        pokazTabele(tabela, dane);

        // Minimalna temperatura
        const min = Module.pobierzMinimum();

        document.getElementById("minimum").textContent =
            min.temperatura + " °C";

        document.getElementById("dataMinimum").textContent =
            min.data;

        document.getElementById("status").textContent =
            "Pomyślnie wczytano dane z a.txt.";

    }
    catch (error) {

        document.getElementById("status").textContent =
            "Błąd: " + error.message;

    }
}


// Wyszukiwanie pomiarów powyżej progu
document.getElementById("szukaj").addEventListener("click", function() {

    if (!Module.czyGotowy || !Module.daneWczytane) {

        document.getElementById("wynikInfo").textContent =
            "Dane nie są jeszcze dostępne.";

        return;
    }

    const prog = document.getElementById("prog").value;

    if (
        prog.trim() === "" ||
        !Number.isFinite(Number(prog))
    ) {

        document.getElementById("wynikInfo").textContent =
            "Podaj poprawny próg temperatury.";

        return;
    }

    // Wywołanie metody C++
    const znalezione = Module.szukaj(Number(prog));

    document.getElementById("wynikInfo").textContent =
        "Znaleziono pomiarów: " + znalezione.size();

    pokazTabele(wyniki, znalezione);

});


// Uruchomienie po załadowaniu WebAssembly
Module.onRuntimeInitialized = async function() {

    Module.czyGotowy = true;

    await wczytajPlik();

};

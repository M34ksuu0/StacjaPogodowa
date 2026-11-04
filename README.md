# 🌤️ Stacja Pogodowa - System Obsługi Pomiarów

Prosta aplikacja konsolowa napisana w języku **C++**, służąca do zarządzania i analizy danych meteorologicznych (pomiarów temperatury oraz prędkości wiatru) wczytywanych z pliku tekstowego.

## 🚀 Funkcje programu

1. **Wczytywanie danych z pliku (`a.txt`)** – automatyczne parsowanie danych rozdzielanych średnikami do struktury obiektowej z obsługą wyjątków (np. w przypadku braku pliku).
2. **Wyznaczanie minimum** – wyszukiwanie i prezentacja rekordu z najniższą zarejestrowaną temperaturą.
3. **Dynamiczne filtrowanie bazy** – wyszukiwanie pomiarów powyżej progu temperatury zdefiniowanego interaktywnie przez użytkownika.
4. **Bezpieczeństwo typów** – wykorzystanie nowoczesnych mechanizmów C++ takich jak `std::vector`, `size_t` oraz bezpieczna konwersja typów danych (`stod`).

## 📋 Struktura danych wejściowych

Program przetwarza dane z pliku tekstowego o nazwie `a.txt`. Każda linia pliku musi reprezentować jeden rekord, gdzie poszczególne pola są rozdzielone średnikami (`;`) według schematu:
```text
identyfikator_stacji;data_pomiaru;temperatura;predkosc_wiatru
```

### Przykład zawartości pliku `a.txt`:
```text
ST01;2026-11-01;12.5;4.2
ST02;2026-11-02;18.1;5.0
ST03;2026-11-03;8.3;12.1
```

## 🛠️ Wymagania i Uruchomienie

### Wymagania
* Kompilator obsługujący standard **C++11** lub nowszy (np. GCC, Clang, MSVC).

### Kompilacja (CLI)
Aby skompilować program za pomocą g++, wykonaj w terminalu poniższe polecenie:
```bash
g++ -std=c++11 main.cpp -o stacja_pogodowa
```

### Uruchomienie
1. Upewnij się, że plik danych `a.txt` znajduje się w tym samym katalogu co plik wykonywalny programu.
2. Uruchom program:
```bash
./stacja_pogodowa
```

## 💻 Przykład działania programu

```text
--- Wszystkie pomiary ---
ID: ST01 | Data: 2026-11-01 | Temperatura: 12.5°C | Wiatr: 4.2 m/s
ID: ST02 | Data: 2026-11-02 | Temperatura: 18.1°C | Wiatr: 5 m/s
ID: ST03 | Data: 2026-11-03 | Temperatura: 8.3°C | Wiatr: 12.1 m/s

--- Rekord z minimalna temperatura ---
ID: ST03 | Data: 2026-11-03 | Temp: 8.3°C | Wiatr: 12.1 m/s

Podaj prog temperatury, powyzej ktorego chcesz wyszukac pomiary: 10.0

--- Pomiary z temperatura wyzsza niz 10°C ---
ID: ST01 | Data: 2026-11-01 | Temp: 12.5°C | Wiatr: 4.2 m/s
ID: ST02 | Data: 2026-11-02 | Temp: 18.1°C | Wiatr: 5 m/s

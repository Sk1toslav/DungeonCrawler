Markdown
# ⚔️ Dungeon Crawler: Carnage

Dungeon Crawler je temná, plně objektová RPG hra v konzoli napsaná v moderním C++. Hráč se ujímá role hrdiny, který sestupuje do nebezpečného podzemního labyrintu o 100 patrech s jediným cílem – porazit finálního bosse jménem *Carnage, THE RED DRAGON*.

Hra klade důraz na atmosféru, nekompromisní souboje (permadeath), správu inventáře a průzkum neznámého prostředí.

---

## 🌟 Hlavní vlastnosti (Features)

* **Generování dungeonu a mapy:** Podzemí se skládá ze 100 pater, která se dynamicky načítají z externího souboru `maps.txt`.
* **Taktický soubojový systém:** Tahové souboje proti nestvůrám s využitím základního útoku a riskantní **Krvavé magie (Blood Magic)**. Ta výměnou za hrdinovu vlastní HP uděluje nepříteli absolutní poškození (True Damage) ignorující jakoukoliv obranu.
* **Systém progrese (Leveling):** Za porážené nepřátele získává hrdina zkušenosti (XP). Zvyšování úrovně automaticky vylepšuje atributy (maximální HP, útok, obranu i sílu magie).
* **Interaktivní inventář a loot:** Truhly v podzemí ukrývají lektvary, zbraně a brnění. Vybavení přepisuje hrdinovy bonusové sloty bez trvalého znečištění základních statistik.
* **Perzistence dat (Save/Load):** Plně funkční obousměrná serializace a deserializace aktuálního stavu hry do souboru `savegame.txt`.
* **Hřbitov padlých (Graveyard):** Síň slávy zaznamenávající jména, dosažená patra a úrovně hrdinů, kteří v podzemí nalezli svou smrt (ukládá se do `graveyard.txt`).

---

## 🏗️ Architektura projektu a OOP principy

Projekt striktně dodržuje principy objektově orientovaného programování (OOP) a moderní standardy jazyka C++:

1. **Dědičnost a Polymorfismus:** * Třídy `Hero` a `Enemy` dědí ze společného předka `Character`.
   * Předměty (`Potion`, `Weapon`, `Accessories`) dědí z abstraktní třídy `Item`. Čištění a použití předmětů probíhá polymorfně přes virtuální metody `virtual void use(Character &target)` a `virtual void info()`.
2. **Správa paměti (RAII):** Celý projekt se zcela vyhýbá surovým ukazatelům a ručnímu volání `delete`. Pro instanciaci hrdiny, nepřátel a inventáře jsou exkluzivně využívány chytré ukazatele `std::unique_ptr` ve spojení s `std::make_unique`.
3. **Bezpečné přetypování:** Pro identifikaci a ukládání specifických typů předmětů z vektorů je využíván `dynamic_cast` s kontrolou platnosti.
4. **Const korektnost:** Metody, které nemodifikují vnitřní stav objektů (např. gettery atributů), jsou důsledně označeny klíčovým slovem `const`.
5. **Přetěžování operátorů:** Třída `Character` má přetížený operátor streamu `friend std::ostream &operator<<(std::ostream &os, const Character &c)`, což umožňuje elegantní a sjednocené vypisování bojovníků v souboji.

---

## 📁 Struktura souborů

* `rpg.cpp` – Hlavní smyčka programu, úvodní menu a zpracování uživatelského vstupu.
* `Game.h` / `Game.cpp` – Logika vykreslování mapy, pohyb v patře, interakce s políčky a soubojový cyklus (`encounter`).
* `Character.h` / `Character.cpp` – Rodičovská třída entit, správa HP, poškození, obrany a výpočty *True Damage*.
* `Hero.h` / `Hero.cpp` – Třída hráče rozšiřující vlastnosti o levelování, krvavou magii a batoh s předměty.
* `Enemy.h` / `Enemy.cpp` – Třída nepřátel uchovávající odměny za zabití (`xpReward`).
* `Item.h` / `Item.cpp` – Abstraktní třída předmětů a její odvozené specializace (lektvary, zbraně, doplňky).
* `SaveLoad.h` / `SaveLoad.cpp` – I/O operace se soubory (ukládání/načítání stavu a zápis na hřbitov).
* `maps.txt` – Externí datový soubor definující rozložení jednotlivých pater podzemí.

---

## ⚙️ Požadavky a závislosti (Dependencies)

Projekt nevyžaduje **žádné externí ani nestandardní knihovny**. 
* **Překladač:** Jakýkoliv překladač s podporou standardu **C++14** nebo vyššího (např. `g++` / GCC, MSVC, Clang).
* **OS:** Windows (nativně či přes MSYS64/MinGW), Linux nebo macOS.

---

## 🚀 Návod k sestavení a spuštění

### A. Sestavení pomocí Visual Studio Code (Doporučeno)

Projekt obsahuje předpřipravený soubor `tasks.json` pro překladač GCC (`ucrt64`).
1. Otevřete kořenovou složku projektu ve VS Code.
2. Stiskněte klávesovou zkratku **`Ctrl + Shift + B`**.
3. Překladač automaticky sestaví všechny `.cpp` soubory a v kořenové složce vytvoří spustitelný soubor **`rpg.exe`**.

### B. Sestavení přes Příkazový řádek (Terminál)

V terminálu otevřete složku s projektem a zadejte:

    g++ -std=c++14 -Wall rpg.cpp Game.cpp Hero.cpp Enemy.cpp Character.cpp Item.cpp SaveLoad.cpp -o rpg.exe

Následně hru spusťte příkazem:
* Na Windows: `.\rpg.exe`
* Na Linuxu/macOS: `./rpg.exe`

### C. Sestavení pomocí nástroje Make

Pokud máte v systému nainstalovaný nástroj Make, stačí v terminálu zadat:

    make

---

## 🎮 Ovládání hry

### Hlavní menu
* **`N`** – Spuštění nové hry (vyžádá si zadání jména hrdiny).
* **`L`** – Načtení pozice ze souboru `savegame.txt`.
* **`G`** – Zobrazení hřbitova padlých hrdinů z `graveyard.txt`.
* **`E`** – Ukončení aplikace.

### Pohyb v Dungeonu
* **`W` / `A` / `S` / `D`** – Pohyb hrdiny po mapě (Nahoru / Doleva / Dolů / Doprava).
* **`I`** – Otevření inventáře a výběr předmětu k použití.
* **`V`** – Uložení aktuální pozice a stavu mapy.
* **`Q`** – Návrat do hlavního menu.

### Bojový režim
* **`A`** – Fyzický útok zbraní.
* **`B`** – Krvavá magie (True Damage za cenu vlastních HP).
* **`R`** – Pokus o útěk z boje.

---

## 🗺️ Modding: Vlastní mapy podzemí

Hra umožňuje plné přizpůsobení mapových podkladů úpravou souboru **`maps.txt`**. Každá mapa je tvořena mřížkou ASCII znaků a jednotlivá patra jsou od sebe oddělena samostatným řádkem obsahujícím pouze znak pomlčky (`-`).

**Legenda znaků:**
* `*` – Neprostupná stěna.
* `.` – Volná chodba / podlaha.
* `E` – Nepřítel (Monster / Boss).
* `C` – Truhla s náhodným vybavením.
* `D` – Dveře pro sestup do hlubšího patra.

*Příklad definice patra v maps.txt:*

    **************
    *............*
    *..E.........*
    *.**.**......*
    *......*.....*
    *..E...*.....*
    *.....C*****.*
    *........D...*
    **************
    -

Kodas atlieka 3 užduotis:
1. Suranda kiekvieną žodį faile ir jeigu jis pasikartoja daugiau negu vieną kartą, išvedamas jis ir to žodžio pasikartojimų skaičius. Kadangi
   straipsnis lietuvių kalba (bet yra ir rusiškų žodžių), tai naudotos bitinės (bitwise) operacijos, kad būtų galima atrinkti ir tas raides
   (nes kitaip jos tiesiog praleidžiamos). Taip pat parašytos funkcijos, kurios leižia išlaikyti left lygiuotę, nes kadangi ne ASCII raidės
   užima daugiau nei 1 baitą, tai susigadina formatavimas. Naudojama map duomenų struktūra.
2. Kiekvienam surastam žodžiui (kuris pasikartoja daugiau nei vieną kartą) surandamos eilutės, kuriose jis yra (jei žodis toje pačioje eilutėje
   pasikartoja kelis kartus, tai eilutės numeris vis tiek išveamas tik vieną kartą). Naudojama map duomenų struktūra. 1 ir 2 užduočių rezultatai
   išvedami į failą rez.txt.
4. Naudojant regex, surandami visi URL'ai ir tada dar kartą patikrinama pereinant per plėtinių set'ą (kuris įkeliamas iš duoto failo). Išvedama
   į kitą failą - rez_urls.txt. Naudojama set duomenų struktūra.

# ATP Cup

## Descriere
În cadrul _Turneului Internațional de Tenis ATP Cup_, fiecare stat participant are un lot de jucători. Acest lot urmează să-și reprezinte țara într-o succesiune de meciuri jucate contra membrilor celorlalte loturi. Se dorește realizarea unei soluții software care să automatizeze desfășurarea turneului

## Instrumente necesare
Pentru funcționarea (corectă) a programul este recomandată folosirea OS Linux, fie ca OS principal, fie folosind o mașină virtuală sau folosindu-ne de __Linux Subsystem for Windows__ (pe care îl recomand întrucât o mașină virtuală este de obicei destul de lentă, iar full Linux OS pare un commitment prea mare). 

Odată ce e rezolvat acest prerequisite, putem trece la celelalte lucruri esențiale. Deschidem __Command Prompt__ și introducem următoarea comandă pentru a intra în Linux Subsystem.
```
bash
```
După aceea va fi necesară rularea următoarelor comenzi pentru instalarea diferitor programe.
```
sudo apt-get install gcc

sudo apt-get install make
```


În interiorul folderului în care se găsește programul _trebuie_ să existe un fișier
**cerinte.in** și un fișier __date.in__.

## Input


Prima linie a fișierului __date.in__ va conține un număr natural, reprezentând numărul țărilor participante. În continuare, pentru fiecare țară participantă se vor găsi următoarele date:

* Un număr natural, reprezentând __numărul de jucători al lotului__, pe o linie
* __Numele țării__, pe următoarea linie
* __Numele, prenumele și scorul personal al unui jucător__, pe câte o linie pentru fiecare jucător în parte


## Cerințe

* Fișierul __cerinte.in__ va conține pe prima linie 5 cifre (0 sau 1) separate printr-un spațiu. Fiecare cifră corespunde fiecărei cerințe, iar valoarea ei hotărăște dacă fișierul __rezultate.out__ va conține ieșirea cerinței respective.
* Exemplu: “1 1 1 0 0”. Se vor rezolva doar cerințele 1, 2 și 3, deoarece cifrele corespunzătoare lor sunt “1”, cifrele corespunzătoare cerințelor 4 și 5 sunt “0”.
* În cazul în care a 5-a cifră este “1”, adică cerința 5 trebuie rezolvată, pe următoarele două linii ale fișierului se vor găsi numele, prenumele și scorul personal după terminarea turneului a doi jucători. Acestea reprezintă datele de intrare pentru cerința 5 (detalii mai jos).

Exemplu:
>   1 1 1 1 1

>  Haas Tommy 56
 
>  Federer Roger 87
* Se vor rezolva toate cerințele, iar datele de intrare pentru cerința 5 sunt “Haas Tommy 56” și “Federer Roger 87”


## Output cerințe
În fișierul __rezultate.out__ se vor afișa următoarele, numerotate în funcție de cerințe:
1.  Toate țările participante
2.  Toate țările participante, __după__ ce au fost eliminate câteva (dacă a fost cazul) pentru a avea un număr de 2ⁿ țări (altfel nu ar putea avea loc turneul)
3.  Meciurile dintre jucători, împreună cu scorul global al țărilor, afișându-se la finalul fiecărei etape statele câștigătoare
4.  Clasamentul jucătorilor ultimelor patru țări rămase în turneu, în ordine descrescătoare
5.  Numărul de jucători din clasament aflați între cele două persoane menționate în __cerinte.in__ (dacă există)

## How to
După ce au fost instalate lucrurile necesare revine întrebarea "Ce facem acum?".

Acum că este cunoscut ce presupune programul, input-ul necesar și output-ul preconizat, putem deschide _Command Prompt_, navigăm până în folderul unde se află programul cu comanda _cd_. Odată ajunși acolo introducem comanda _bash_ după care putem introduce următoarea comandă:
```
./tenis cerinte.in date.in rezultate.out
```
Unde:
* ./tenis reprezintă numele executabilului de rulat
* cerinte.in este fișierul de unde vor fi citite cerințele
* date.in fișierul de unde vor fi citite datele de intrare
* rezultate.out este fișierul unde vor fi scrise datele de ieșire (rezultatul turneului)

---
---
## Detalii tehnice
Pentru detalii în legătură cu funcțiile folosite se pot inspecta comentariile fișierele _liste.c_, _stack.c_, _queue.c_, _BST.c_, _files.c_, cât și _miscellaneous.c_
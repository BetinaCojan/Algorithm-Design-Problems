# algorithm-design-problems
PA 1


	I) Problema 1 - Gigel si tabelele walsh

Pentru rezolvarea problemei nu este necesara construirea matricei walsh, ci doar aflarea fiecarui cadran a coordonatelor primite in fisierul de input in fiecare matrice de dimensiuni mai mici.

Valorile din al 4-lea cadran al oricarei matrice walsh reprezinta matricea walsh de dimensiuni N/2 negata, ceea ce inseamna ca putem nega valoarea initiala (0) de atatea ori in cate astfel de cadrane a aparut coordonata. De fiecare data cand trecem la matricea de dimensiuni N/2, trebuie sa avem grija sa translatam coordonata curenta, in functie de cadranul in care se afla (daca e in cadranul 2, schimbam doar y-ul, daca e in cadranul 3, schimbam doar x-ul, daca in 4 schimbam ambele).
  
Complexitatea temporala a algoritmului este O(K*log(N)), deoarece avem K inputuri, iar pentru fiecare input injumatatim N-ul pana ajunge la 1.
Complexitatea spatiala este O(1), deoarece salvam doar cateva constante.

	II) Problema 2 - Gigel si cuvintele criptate

Algoritmul utilizat este unul de tip Greedy si se bazeaza pe calcului unei metrici de dominanta a unei litere pe fiecare cuvant. Definim functia solve_for_letters care se ocupa cu gasirea numarului maxim de cuvinte pe care atunci cand le concatenam, litera letter este dominanta. Aceasta functie creeaza un vector, in care fiecare valoare reprezinta cat de dominanta este litera in fiecare cuvant. Practic, calculeaza de cate ori apare litera si se raporteaza la jumatea lungimii.
	
Exemplu pentru litera a:

aabb -> 0 (litera apare fix de jumatatea lungimii, deci nu influenteaza)
abbb -> -1 (litera apare de mai putine ori decat jumatatea, deci influenteaza negativ cu 1)				
aaab -> 1 (litera apare de mai multe ori, deci pozitiv 1)
bbbb -> -2 (litera apare de 2 ori mai putin decat necesar) samd

In acest mod, putem sorta descrescator toate aceste metrici, si sa  aflam numarul maxim de metrici care insumate dau suma > 0.
Aplicam algoritmul pentru fiecare litera posibila si aflam maximul.
Complexitatea temporala este O(NlogN), deoarece folosim sortare prin comparatii de chei. Mai exact, Teta(26 * (L + NlogN)) (sau ceva asemanator)

	III) Problema 3 - Gigel si Prinel

Algoritmul este format din 3 etape:
	1) Aflarea tuturor divizorilor numerelor de la 1 la max_target printr-un ciur
	2) Aflarea tuturor operatiilor pentru fiecare numar de la 1 la max_target printr-o algoritm care se aseamana cu BFS. (se scoata un element din coada, si pentru fiecare divizor al sau se completeaza vectorul pentru elementul curent + divizor, si se adauga in coada)
	3) Avand la dispozitie numarul de operatii pentru fiecare target in parte, se aplica rezolvarea de la problema rucsacului, in care trebuie sa alegem profitul maxim, astfel incat greutatea sa nu depaseasca K (greutate = operatii)

Complexitatea temporala este:
	1) O(N * (1 + 1/2 + 1/3 + .. + 1/N)) ~= O(N)
	2) tot O(N), deoarece doar se trece prin fiecare divizor in parte
	3) O(N * K)

Deci complexitatea finala ar trebuie si fie O(N * K)
	
	Linkuri folosite:
	https://www.geeksforgeeks.org/find-all-divisors-of-first-n-natural-numbers/
	https://infoarena.ro/job_detail/608485?action=view-source

	IV) Problema 4 - Gigel si cheia de la portofel

Algoritmul se bazeaza pe programare dinamica, asemanatoare cu implementarea algoritmului de numararea a unui substring intr-un string. Singura diferenta este aparitia semnelor intrebarii. Formula pentru DP este urmatoarea:
	
	DP[i][j] = numarul de substringuri S[0:i] care apar in K[0:i]
	DP[i][j] = DP[i][j-1] + DP[i-1][j-1], daca S[i] == '?'
	DP[i][j] = DP[i][j-1] + no_letters * DP[i-1][j-1] daca S[i] == K[j]
	DP[i][j] = DP[i][j-1] altfel

Dat fiind faptul ca '?' se expandeaza la toate caractere posibile, atunci cand intalnim '?', doar o parte din expandarile respenctive sunt valabile, iar cand intalnim S[i] == K[j], toate expandarile sunt valabile, deci de aceea in acest caz inmultim cu numarul de litere distincte.

La final, exista sansa ca numarul de '?' sa fie mai mare decat numarul de expandari facute de noi (len(S)), si trebuie inmultit in continuare cu no_letters. De asemena exista sansa ca numarul de '?' sa fie mai mica, deci trebuie impartit cu no_letters (pentru ca am facut niste imultiri in plus).  
Complexitate temporala: O(len(S) * len(K)), unde oricum S e f mic, deci O(len(K))

	V) Bonus - Gigel regele comertului

Algoritmul de rezolvare se bazeaza pe urmatoarea observatie: numarul necesar de negustori pentru a activa oricare X orase este egal cu numarul de negustori pentru X - 1 orase + distantele maxime pentru activarea urmatorului oras. De aceea, putem calcula numarul minim de negustori necesari pentru activarea oricaror X orase, unde X este 1, 2, 3 ... N. Pentru X = 1, numarul de negustori necesari este suma maxima dintre 2 rute consecutive. Pentru X = 2, gasim urmatoarele 2 rute care dau suma maxima, fara ca acestea sa se suprapuna cu cele precedente. Repetam procesul pana nu mai raman rute neactivate.

Pentru implementare, am construit un vector de distante dintre orasele consecutive. Cautam acele doua rute consecutive care dau suma maxima, adaugam suma la vectorul de negustori, si eliminam rutele din vector pentru a ne asigura ca nu se suprapun la iteratiile viitoare. Daca mai ramane o singura ruta, adaugam valoarea ei la vectorul de negustori. Atunci cand ramanem fara rute de activat, inseamna ca am gasit numarul maxim de negustori necesari pentru activarea tuturor oraselor.

In final, cu acest vector de negustori construit, raspundem pe rand la intrebarile cerute, cautand in ce interval se afla numarul de negustori.
Complexitatea este O(N^2) pentru aflarea negustorilor necesari pentru toti X, si O(Q * N) pentru a raspunde la intrebari. Acel N apare din cauza faptului ca trebuie sa iteram prin vectorul de negustori de fiecare data.

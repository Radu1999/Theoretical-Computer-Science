# Enuntul problemei:
	Se da o lista initiala de rank-uri (nr naturale) care se pot repeta. Se pot efectua urmatoarele operatii:
	1 x : se va insera un rankul x in lista
	2 0/1 : in cazul 2 0 se va elimina rankul minim, iar in cazul 2 1 rankul maxim (doar o aparitie a lor - ex: la 12 23 23 dupa operatia 2 1 va ramane 12 23)
    3 : se va scrie in stdout rankul minim curent
	4 : se va scrie in stdout rankul maxim curent


Sablon test intrare:
  - Pe prima linie se afla numarul de rankuri n.
  - Pe a doua linie se afla n rank-uri (nr naturale). Pe a 3-a linie se va afla numarul de operatii k. 
  - Pe urmatoarele k linii se vor afla operatiile ce neceseita efectuare.
# in:
	5
    23 12 33 7 19
    8
    1 6
    3
    2 1
    2 1
    2 1
    2 0
    4

# out:
    6
    12
    7

  Explicatie: initial elementul minim este 7 si cel maxim 33. Prima comanda insereaza 6, deci acum elementul minim devine 6. A doua comanda scrie minimul curent: 6. Urmatoarele 3 comenzi sterg maximul, maximul curent ajungand 33->23->19->7. Comanda 2 0 sterge minimul, minimul curent devenind 7. Ultima comanda afiseaza maximul: 7.
  
 # Generare de teste in:
  

Am scris programul testgenerator.cpp care genereaza 20 de teste in mod aleator forlosind rand().

 # Generare de teste out:
 
 Am rezolvat testele .in folosind algoritmul urmator: am sortat lista de rank-uri, iar la fiecare operatie de insert gaseam cu cautare dinamica pozitia si inseram.
 Sursa se afla in generatorTesteOut.cpp.
 
 
 
 # Algoritm 1:
 
 Prima abordare foloseste MinMaxHeap. Astfel, insertia este O(loh n). stergerea elementului maxim si minim este O(log n), iar gasirea lor este o(1).
 Implementarea se bazeaza pe cea din repo-ul de git: [Min-Max Heap](https://github.com/frankpeng7/Min-Max-Heap). La ea am adaugat functia buildMinMaxHeap care construieste structura in O(n).

| Fisier | Rol |
| ------ | ------ |
| algo1.h |structura si functiile|
| algo1.cpp | implementarea functiilor|
| algo1_test.cpp | testarea solutiei |
 
 # Algoritm 2:
A doua abordare foloseste Red Black Tree modificat, ajungandu-se la stergere maxim si minim in O(log n) si gasire in O(1). Implementarea se bazeaza pe [Red-Black Tree | Set 3 (Delete)](https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/) . Am modificat structura astfel incat sa functioneze si cu duplicate. Pentru gasire maxim si minim tin 2 pointeri la nodurile respective(maximum si minimum) si monitorizez orice operatie unde are trebui sa ii repozitionez (insert, delete).

  | Fisier | Rol |
| ------ | ------ |
| algo2.h |structura si functiile|
| algo2.cpp | implementarea functiilor|
| algo2_test.cpp | testarea solutiei |


 # Makefile
Construirea executabilelor test1 pentru algoritmul 1 si test2 pentru algoritmul 2 se face ruland:
```sh
make build
```

Testarea solutiilor se face:
```sh
./test1 < inFile > outFile
```
```sh
./test2 < inFile > outFile
```

La final curatati cu:
```sh
make clean
```



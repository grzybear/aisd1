# Podziały - rekurencja/iteracja
**Podział** liczby n to reprezentacja tej liczby jako sumy dodatnich liczb całkowitych: n=n1+n2+...+nr, takich że n1≥n2≥...≥nr. Liczby n1,n2,...,nr nazywamy **składnikami**.

Podział $19=5+3+3+2+2+2+2$ możemy zapisać jako $53^22^4$, natomiast podział $19=5+2+2+2+2+2+2+2$ możemy zapisać jako $52^7$.
Stąd indeksy górne w takim zapisie to odpowiednio $124$ oraz $107$, tak więc $5+3+3+2+2+2+2$ jest większe od $5+2+2+2+2+2+2+2$, 
ponieważ $124$ jest większe od $107$ (patrząc z lewej pierwsza nieidentyczna pozycja zawiera $2$ i $0$, a $2>0$, stąd $124>107$).
Jeśli nie zrozumiałeś, zerknij na zapis w zasadniczym twierdzeniu arytmetyki.
## Zadanie

Rozpoczynając od najmniejszego podziału, wypisz wszystkie [podziały liczby naturalnej](https://en.wikipedia.org/wiki/Partition_(number_theory)) n, składające się z liczb pierwszych, z których największa to k. 

Uwaga:
Ze względu na złożoność obliczeniową problemu liczba n zmieści się w bajcie.
## Input

W pierwszej linii: liczba kolejnych linii
W kolejnych liniach po spacji: n oraz k

## Output

W kolejnych liniach podziały, w których składniki są rozdzielone znakiem plus. W przypadku gdy podział nie istnieje nie wypisuj żadnych danych.

## Example

### Input
3  
12 5  
5 2  
27 17

### Output
5+3+2+2  
5+5+2  
17+2+2+2+2+2  
17+3+3+2+2  
17+5+3+2  
17+5+5  
17+7+3

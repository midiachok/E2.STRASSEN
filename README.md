1. Defiujem štruktúru MAT: obsahuje dvojrozmerné pole matrix a size, ktorý určuje veľkosť matice (size=n, v kontexte 2^n x 2^n).
2. Funkcia na konštrukciu matice constr() alokuje pamäť pre matice a inicializuje ich.
3. Funkcia na deštrukciu matice destr() uvoľňuje alokovanú pamäť.
4. Funkcia na naplnenie matice fill() ponúka, ako chceme zadať hodnoty matice.
5. Funkcia na zobrazenie matice show() tlačí obsah matice na obrazovku.
6. Funkcia na sčítanie a odčítanie matíc add_subtract_matrix() sčíta alebo odčíta dve matice v závislosti od hodnoty add. 
7. Funkcia na násobenie matíc pomocou Strassenovho algoritmu mat_multiply_strassen() pracuje takto:
a) Ak je veľkosť matice 1, vynásobí jediné prvky a skončí.
b) Inak rozdelí matice A a B na štyri submatice a vykoná výpočty podľa Strassenovho algoritmu.
c) Výsledné submatice spočíta a uloží do výslednej matice C.

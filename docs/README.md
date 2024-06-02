# Graphs and stuff like that (Grafy i takie tam)

## English version

Graphs are an important data structure used in computer science. The task is to load graphs and determine the following parameters:

1.  the degree sequence
2.  the number of components
3.  bipartiteness
4.  the eccentricity of vertices (within the components)
5.  planarity
6.  vertices colours (consecutive natural numbers from 1) obtained using algorithms:
    1. greedy (the vertex order according to its number)
    2. LF method (ties are solved by the vertex number)
    3. SLF method (ties are solved by highest vertex degree, and if there is still a tie choose the vertex with the lowest number)
7.  the number of different C4 subgraphs
8.  the number of the graph complement's edges

### Input

In the first line there's a number _k_ of graphs.  
The following lines contain _k_ graph data sets.  
A single data set contains a number _n_ - the graph order - and _n_ lists of neighbours for each vertex. A list contains the number of neighbours (_s_) and _s_ neighbours IDs.  
Neighbours IDs are numbers from 1 to _n_.

### Output

You should print _k_ sets of responses. Each set should contain the designated parameters in the order in which the parameters are listed. For point:

- 1, 4, 6a, 6b, 6c you should print sequence of _n_ numbers;
- 7, 8 you should print a number;
- 2, 3, 5 you should print a character `T` or `F` (true/false).

### Optionality

Only points (parameters) 1 and 2 are required. If any of the point is not implemented, please enter a single `?` character as the output.  
Score for a graph parameter will only be included if this parameter is correctly determined in each data set.  
The score for each parameter is 10% of the total score.

## Wersja polska

Grafy są istotną strukturą danych używaną w informatyce. Zadanie polega na wczytaniu grafów i wyznaczeniu następujących parametrów:

1.  ciągu stopniowego
2.  liczby składowych spójności
3.  dwudzielności grafu
4.  acentryczności wierzchołków (w ramach składowych spójności)
5.  planarności grafu
6.  kolory wierzchołków (kolejne liczby naturalne od 1) uzyskane za pomocą algorytmów:
    1.  zachłannego w kolejności wierzchołków zgodnej z numerem wierzchołka
    2.  metodą LF (remisy rozwiązujemy przy pomocy numeru wierzchołka)
    3.  metodą SLF (w przypadku remisu wybierz wierzchołek z najwyższym stopniem, a jeśli nadal jest remis to wierzchołek o najmniejszym indeksie)
7.  liczba różnych podgrafów C4
8.  liczba krawędzi dopełnienia grafu

### Wejście

W pierwszej linii znajduje się liczba _k_ grafów.  
W kolejnych liniach znajduje się _k_ zestawów danych grafów.  
Pojedynczy zestaw danych zawiera liczbę _n_ - rząd grafu - oraz listę sąsiadów w postaci liczba sąsiadów (_s_) wraz z _s_ identyfikatorami sąsiadów.  
Identyfikatory sąsiadów to liczby z zakresu od 1 do _n_.

### Wyjście

Należy wypisać k zestawów odpowiedzi.  
Każdy zestaw powinien zawierać wyznaczone parametry w kolejności w jakiej parametry są wypisane. W przypadku punktów:

- 1, 4, 6a, 6b, 6c należy wypisać ciąg n liczb;
- 7, 8 należy wypisać liczbę;
- 2, 3, 5 należy wypisać T lub F (prawda/fałsz).

### Opcjonalność

W zadaniu jedynie podpunkty 1 i 2 są wymagane. Jeśli jakiś z podpunktów nie będzie realizowany, to w odpowiedzi należy wpisać pojedynczy znak `?`.  
Punktacja za parametr grafu zostaną uwzględnione tylko wtedy, jeśli w każdym zestawie danych ten parametr zostanie prawidłowo wyznaczony.  
Punktacja za każdy z parametrów to 10% całkowitej punktacji.

## [Przykłady/Examples](../tests/)

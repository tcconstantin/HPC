# HPC - High Performance Computing

MPI
Problem:
• Dispunem de n procese pi, i=0,..,n-1, și m fișiere text fj, j=0,..,m-1 Fișierul fj conține lj caractere (lj≥10.000).
• Procesul p0 primește un cuvânt c pe care îl distribuie celorlalte procese.
• Apoi, procesul p0 repartizează fiecărui proces pi, i=1,..,n-1 un set de fișiere astfel încât
numărul de caractere conținute de fișierele asignate sa fie aproximativ
Notăm cu qi numărul fișierelor repartizate procesului pi
• Procesului pi trebuie sa prelucreze fișierele asignate pentru a determina numărul de apariții ale cuvântului c în fișierule repartizate. Pentru aceasta pi va utiliza qi procese worker. Fiecare worker va analiza un fișier.
• La final, procesul p0 va “cunoaște” numărul de apariții ale cuvântului c în cele m fișiere.

from colonia import *

colonia = Colonia([[0,22,50,48,29],
                [22,0,30,34,32],
                [50,30,0,22,23],
                [48,34,22,0,35],
                [29,32,23,35,0]], 0.01, 0.1, 10)

percursos, dists = colonia.rodar(6)

for aux, percurso in enumerate(percursos):
    print(percurso, dists[aux])
from caminho import *
import random
import math
from itertools import combinations

class Colonia:
    def __init__(self, distancias, evap, ferInicial, attFer):
        self.evap = evap
        self.ferInicial = ferInicial
        self.attFer = attFer

        for i in range(len(distancias)):
            for j in range(len(distancias)):
                if i != j:
                    distancias[i][j] = Caminho(distancias[i][j], ferInicial)

        self.caminhos = distancias

    def rodar(self, numIt):
            for _ in range(numIt):
                for z, linha in enumerate(self.caminhos):
                    somatorioP = 0
                    for h, caminho in enumerate(linha):
                        if z != h:
                            caminho.tn = arredondar(caminho.t * caminho.n)
                            somatorioP += caminho.tn

                    for c, caminho2 in enumerate(linha):
                        if z != c:
                            caminho2.p = arredondar(arredondar(caminho2.tn / somatorioP) * 100)

                percursos = []
                distsPercorridas = []
                for j in range(len(self.caminhos)):
                    percurso = [j]
                    distPercorrida = 0
                    for ele in percurso:
                        indices = []
                        probabilidades = []
                        for k, caminho in enumerate(self.caminhos[ele]):
                            if k not in percurso:
                                indices.append(k)
                                probabilidades.append(caminho.p)
                        if(len(probabilidades) == 0):
                            break
                        escolha = metodo_da_roleta(probabilidades)
                        percurso.append(indices[escolha])
                        distPercorrida += self.caminhos[ele][indices[escolha]].distancia
                    
                    distPercorrida += self.caminhos[percurso[-1]][j].distancia
                    percurso.append(j)
                    percursos.append(percurso)
                    distsPercorridas.append(distPercorrida)

                conjuntos = list(combinations(range(len(self.caminhos)), 2))
                for conjunto in conjuntos:
                    #print(conjunto[0], " ",conjunto[1],end=" ")
                    somatorio = arredondar((1-self.evap) * self.caminhos[conjunto[0]][conjunto[1]].n)
                    #print(somatorio, end=" ")
                    for x, percurso in enumerate(percursos):
                        #print(percurso, end=" ")
                        for y in range(len(percurso)-1):
                            if percurso[y] in conjunto and percurso[y+1] in conjunto:
                                #print(self.attFer, ",", distsPercorridas[x], end=" ")
                                somatorio += arredondar(self.attFer / distsPercorridas[x])
                        #print()
                    self.caminhos[conjunto[0]][conjunto[1]].n = arredondar(somatorio)
                    self.caminhos[conjunto[1]][conjunto[0]].n = arredondar(somatorio)

            return percursos, distsPercorridas



def metodo_da_roleta(probabilidades):
    max = probabilidades[0]
    for prob in probabilidades:
        if prob > max:
            max = prob
    
    indices = []

    for x, prob2 in enumerate(probabilidades):
        if prob2 == max:
            indices.append(x)

    return random.choice(indices)
    
        
def arredondar(valor):
    aux = valor * 1000
    parte_decimal = aux % 1

    if parte_decimal >= 0.5:
        return math.ceil(aux) / 1000
    
    return math.floor(aux) / 1000


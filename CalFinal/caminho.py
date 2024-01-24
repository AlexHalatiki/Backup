class Caminho:
    def __init__(self, distancia, n):
        self.distancia = distancia
        self.t = round(1 / distancia, 3) if distancia != 0 else 0.0
        self.n = n
        self.tn = 0
        self.p = 0

    def print(self):
        print(f"{self.distancia} {self.t} {self.n} {self.tn} {self.p}")
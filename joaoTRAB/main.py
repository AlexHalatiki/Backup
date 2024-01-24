testes = []

# essa parte e para ler os dados, quando M e N forem 0 sai do loop
while True:
    teste = []

    # le uma entrada e na linha 45 separa a entrada a partir do espaco, por exemplo, 15 10, vai virar o numero 15 inteiro e o numero 10 inteiro, sendo que o primeiro vai ser o M e o segundo o N
    M = int(input("\nDigite o valor de M (tamanho da cadeia p):\n"))
    N = int(input("Digite o valor de N (tamanho da cadeia t):\n"))

    if(M == 0 and N == 0):
        break
    
    p = input("Digite a cadeia p:\n").upper()
    t = input("Digite a cadeia t:\n").upper()

    # cada conjunto de dados se refere a um teste, entao cada conjunto de dados (teste) lido, adicionamos num vetor de testes, que sao todos os testes a se fazer
    teste.append(M)
    teste.append(N)
    teste.append(p)
    teste.append(t)
    testes.append(teste)


for c in range(len(testes)):
    p = testes[c][2]
    t = testes[c][3]

    pComplementarInvertido = ""

    # faz o complemento da cadeia, ou seja, ACT vira TGA
    for caractere in p:
        if(caractere == 'C'):
            pComplementarInvertido += 'G'
        if(caractere == 'G'):
            pComplementarInvertido += 'C'
        if(caractere == 'A'):
            pComplementarInvertido += 'T'
        if(caractere == 'T'):
            pComplementarInvertido += 'A'
    
    # Faz o inverso, ou seja, se for TGA vai retornar AGT
    # [:: -1] é usado para criar uma cópia invertida de uma sequência, como uma lista ou uma string.
    # O primeiro dois pontos (:) indica que queremos considerar a partir do primeiro elemento da string, incluindo ele.
    # O segundo dois pontos (:) indica que queremos considerar até o último elemento da string.
    # O -1 após o segundo dois pontos indica que queremos percorrer a sequência de forma reversa, indo do último elemento até o primeiro. Se fosse 1 ao inves de -1, a string ficaria igual.
    pComplementarInvertido = pComplementarInvertido[::-1]

    ocorrenciasDiretas = []
    ocorrenciasComplementarInvertida = []

    #logica para encontrar as ocorrencias, e quando acha a ocorrencia, adiciona a posicao no vetor de ocorrencias declarado acima que no final e retornado
    for indice in range(len(t)):
        if(t[indice] == p[0]):
            indiceAux = indice + 1
            diferente = False
            for aux in range(1, len(p)):
                if(t[indiceAux] != p[aux]):
                    diferente = True
                    break
                indiceAux += 1
            
            if(not diferente):
                ocorrenciasDiretas.append(indice + 1)
            
        if(t[indice] == pComplementarInvertido[0]):
            indiceAux = indice + 1
            diferente = False
            for aux2 in range(1, len(pComplementarInvertido)):
                if(t[indiceAux] != pComplementarInvertido[aux2]):
                    diferente = True
                    break
                indiceAux += 1
            
            if(not diferente):
                ocorrenciasComplementarInvertida.append(indice + 1)

    # printa os dados no console
    print(f"\nTeste {c + 1}")

    print("ocorrencia direta: ", end="")
    if(not ocorrenciasDiretas):
        print(0, end="")
    else:
        for ocorrencia in ocorrenciasDiretas:
            print(f"{ocorrencia} ", end="")

    if(not ocorrenciasComplementarInvertida):
        print(0, end="")
    else:
        print("\nocorrencia complementar invertida: ", end="")
        for ocorrencia in ocorrenciasComplementarInvertida:
            print(f"{ocorrencia} ", end="")

    print()
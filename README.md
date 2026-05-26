# Slides para apresentação
https://www.canva.com/design/DAHKVSFS1Ec/81HbMS1YZKKcgfbIG4VEjg/edit

#para compilar
Requisitos:
- Ter o compilador g++ (MinGW-w64 no Windowns) instalado.
- Alternativa: usar Visual Studio (projeto C++).

Passos rápidos:

1) Abra o terminal na pasta do projeto;
2) Compile tudo com g++:

g++ GraphWarper.cpp Graph.cpp GraphReader.cpp ListGraph.cpp MatrixGraph.cpp TestAll.cpp main.cpp -Iheadders -std=c++17 -O2 -o main.exe

3) Para Windowns, Rode o programa com o arquivo de exemplo:
.\main.exe GraphFile_Model.graph

Já para Linux rode:
g++ *.cpp -o main && ./main

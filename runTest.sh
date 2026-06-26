echo "iniciando compilador e rodando"
g++ source/*.cpp main.cpp -Iheadders -o testeExecuçcao
chmod +x testeExecuçcao
./testeExecuçcao
echo "arquivo execultado com sucesso\n"
rm testeExecuçcao
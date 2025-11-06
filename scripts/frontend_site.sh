#!/bin/bash

# Clona o repositório
git clone https://github.com/Passa-pra-Elas/passa-pra-elas-frontend.git

# Entra na pasta do projeto
cd passa-pra-elas-frontend || exit

# Instala as dependências do projeto
npm install

# Inicia o servidor de desenvolvimento
npm run dev &

# Aguarda alguns segundos para o servidor iniciar
sleep 5

# Abre o navegador na URL desejada
xdg-open "http://localhost:5173/jogos/teste" >/dev/null 2>&1 &
# Se estiver no macOS, substitua por open.
# Se estiver no Windows (Git Bash), substitua por start.
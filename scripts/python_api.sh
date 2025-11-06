#!/bin/bash

# Clona o repositório
git clone https://github.com/Passa-pra-Elas/backend-api-python.git

# Entra na pasta do projeto
cd backend-api-python || exit

# Executa o servidor FastAPI em modo desenvolvimento
fastapi dev main.py
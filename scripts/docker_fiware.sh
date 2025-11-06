#!/bin/bash

# Atualiza os pacotes do sistema
echo "🔄 Atualizando pacotes do sistema..."
sudo apt update && sudo apt upgrade -y

# Instala Docker e Docker Compose
echo "🐋 Instalando Docker e Docker Compose..."
sudo apt install -y docker.io docker-compose

# Clona o repositório do FIWARE Descomplicado
echo "📦 Clonando repositório FIWARE Descomplicado..."
git clone https://github.com/fabiocabrini/fiware.git

# Entra no diretório do projeto
cd fiware || exit

# Sobe os containers com Docker Compose
echo "🚀 Montando o sistema com Docker Compose..."
sudo docker-compose up -d

echo "✅ Sistema montado com sucesso!"

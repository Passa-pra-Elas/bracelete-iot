## Braceletes - IoT

**Integrantes**
|Nome|RM|
|--|--|
|Lucas de Almeida Pires | RM: 562757 |
|Daniel Oliveira de Souza | RM: 566284 |
|João Pedro Raimundo Marcilio | RM: 561603 |
|Lucas Zanella Clemente | RM: 563880 |
|João Pedro Ribeiro Palermo | RM: 562077 |

Este projeto foi desenvolvido pelo Nexus Group para a nova plataforma **Passa pra Elas**, com o objetivo de revolucionar a análise de desempenho e a segurança das atletas em campo. O futebol é um esporte dinâmico, onde cada movimento conta. Com nosso bracelete com GPS, conseguimos capturar dados precisos sobre o posicionamento e a performance das jogadoras durante os jogos apadrinhados pela plataforma. Além de poder transmitir ao vivo as posições das atletas aos torcedores, os técnicos podem fazer pequenos ajustes táticos e insights de desempenho, possibilitando transformar o resultado de uma partida e impulsionar a carreira de nossas atletas.

Esse dispositivo tem a capacidade de **trazer as coordenadas geográficas de cada jogadora em relação ao campo** , sendo a latitude e longitude da jogadoras durante a partida, em **tempo real**.

Link para o Wokwi: https://wokwi.com/projects/442169258263160833
Link para o vídeo: https://youtu.be/0-A1nG2uKU4

## 🎯 Objetivo

Capturar e distribuir dados de performance em tempo real, gerando insights para o público e métricas decisivas para olheiros.


## 🛠 Tecnologias e Componentes

### Componentes
- **ESP32** (ou equivalente)
- **GPS Neo-6m**
- **Antena**
- **Bateria Externa**
- Jumpers e Protoboard


### Requisitos técnicos
-   Ambiente em nuvem ou possibilidade de self-hot
-   Conexão 2.4GHz de Internet
-   Roteador Wi-Fi

Algumas bibliotecas que devem estar em seu sistema antes de compilar o código:

| Biblioteca |Função|
|--|--|
| [WiFi.h](https://docs.arduino.cc/libraries/wifi) | Permite que o Arduino/ESP32 conecte-se a internet por pontos de acesso (Wi-Fi) |
|[PubSubClient.h](https://docs.arduino.cc/libraries/pubsubclient)| Permite que o arduino mande e receba mensagens utilizando o protocolo MQTT |
|[TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)| Permite interagir com o módulo GPS e trazer as informações obtidas por ele para enviar pelo protocolo MQTT |



## 📦 Funcionalidades

### Posicionamento em Campo 🗾
Determina a localização exata de cada jogadora através de coordenadas de latitude e longitude.
    
### Análise de Movimentação 📝
Utiliza o fluxo de coordenadas para gerar mapas de calor e analisar o posicionamento tático.
    
### Integração de Dados ⛓
Conecta-se à nossa plataforma de backend (FIWARE) para processar e armazenar as informações de cada atleta.
    
### Envio para Análise ✉️
Transmite os dados de localização em tempo real para endpoints HTTP, alimentando a plataforma de scouting e as transmissões ao vivo.

## Como instalar

- **Logue na sua plataforma de nuvem (no tutorial sera feito no azure)**
1. Acesse Máquina Virtual e vamos criar uma nova instância de uma VM
<img width="400" height="auto" alt="image" src="https://github.com/user-attachments/assets/4c05dd7b-c1a5-47fe-8444-25a0533ec0fa" />

2. Durante a configuração (seleção de plano, região, nome) selecione um OS de distribuição Linux (Recomendado Debian ou Ubuntu)
<img width="700" height="auto" alt="image" src="https://github.com/user-attachments/assets/cc497b34-cdfe-4c65-9560-142b1f0f5b75" />


3. Selecione um modelo de VM que tenha no mínimo 1 cpu e 1GiB de memória de ram, e adicione memória interna até atingir no mínimo 20GB
<img width="700" height="auto" alt="image" src="https://github.com/user-attachments/assets/9f7105e6-f22e-4437-b423-20e022a19195" />


4. Configure um IP Público
<img width="700" height="auto" alt="image" src="https://github.com/user-attachments/assets/9cb8da4e-68a3-474b-acd9-c46408728f37" />


5. Revise a máquina e crie ela caso esteja de acordo  
<img width="700" height="auto" alt="image" src="https://github.com/user-attachments/assets/cb2e2f3a-48dd-42bf-9a08-67dddfbffa53" />

6. E por último, após a criação da VM, libere as seguintes portas de entrada
<img width="1007" height="200" alt="image" src="https://github.com/user-attachments/assets/1ea3822d-a251-4a29-a772-e5842d396c99" />  

- **Instalação do Docker no ambiente Linux (Feito em um sistema com gerenciador de pacotes "apt")**  
1. Digite apt upgrade para atualizar a lista de pacotes do sistema  
```sudo apt upgrade -y```

2. Vamos instalar o docker e o docer-compose no sistema  
```sudo apt install docker.io && sudo apt install docker-compose```

3. Faça download do fiware descomplicado usando o git  
```git clone https://github.com/fabiocabrini/fiware```

4. Entre no diretório  
```cd fiware```

5. Faça o buld  do projeto no docker  
```sudo docker-compose up -d```

**Pronto sistema montado!**

> [!NOTE]
> é importante que você mude as variáveis **SSID**, **PASSWORD** e de **BROKER_MQTT** do arquivo <b>sketch.ino</b>, para que fique de acordo com o seu ambiente desejado. Os valores encontrados nesse repositório, no sketch.ino referem-se **nesse projeto em específico**
---

### Como usar

1 - Importe o postman-collection desse reposítorio em seu Postman para ter os caminhos da API na mão.

   1.1 - Verifique os healthchecks do projeto para verificar se a conexão é estabelecidade.

2 - Registre seu dispositivo no <b>3. Provisioning a GPS</b>. (Veja o exemplo do body)

3 - Após a etapa anterior, registre os comandos do dispositivo registrado para habilitar a transferência de dados pela rede em <b>4. Registering GPS Commands</b>. (Veja o exemplo do body)

4 - Pronto! Ele está preparado para ser usado. Aproveite e entre no caminho <b>7. Result of  GPS Coordenates</b> para ver a localização atual da jogadora com o bracelete.

Extra - A plataforma já vem com opções de STH e Orion Broker juntas para mais funções, como obtenção de históricos e recebimento de dados novos. Confira eles dentro da documentação do Postman.

---
Feito pelo grupo Nexus Consulting

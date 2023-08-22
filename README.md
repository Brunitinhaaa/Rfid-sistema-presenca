# Rfid-sistema-presenca
![image](https://github.com/Brunitinhaaa/TCC-sistema-presenca-RFID/assets/104976135/93c4f819-a239-4647-aed3-7f8c47659aca)

O objetivo deste projeto se dá a partir de uma solução de gerenciamento sobre o controle de entrada e saída, frequência e deslocamento de pessoas, registrada para consulta.

O projeto **RFID Sistema de Presença** tem como objetivo oferecer uma solução de gerenciamento para o controle de entrada e saída, frequência e deslocamento de pessoas, registrado para consulta. O sistema utiliza a tecnologia RFID (Radio-Frequency Identification) para identificar e registrar as presenças das pessoas por meio de cartões RFID.

## Funcionamento

O sistema utiliza um leitor RFID (módulo MFRC522) conectado a um Arduino Uno para ler os cartões RFID dos usuários. O código realiza as seguintes operações:

1. **Configuração Inicial:** Inicializa a comunicação SPI (Serial Peripheral Interface), configura os pinos do leitor RFID (RST_PIN e SS_PIN) e define as portas para os LEDs indicadores e o som.

2. **Loop Principal:**
   - Verifica se um novo cartão RFID foi apresentado ao leitor.
   - Lê o código do cartão RFID e armazena-o na variável `card_ID`.
   - Compara o `card_ID` com os códigos dos cartões cadastrados (por exemplo, `Aluno1`, `Aluno2`).
   - Com base na comparação, identifica o aluno correspondente e realiza as operações necessárias, como registrar a entrada/saída no Excel virtual e acender os LEDs indicadores.
   - Se o cartão não for reconhecido, emite um alerta sonoro e pisca o LED vermelho.
   - Após um intervalo de tempo, reseta o valor de `card_ID` para o próximo ciclo.

3. **Excel Virtual:**
   - Através da porta serial, o sistema envia os dados para um software de planilha (Excel).
   - As informações incluem: ID, data, nome do aluno, número do aluno, ID do cartão RFID, horário de entrada/saída.
   - Os dados são formatados no padrão CSV, permitindo que sejam diretamente importados para o Excel para análise posterior.

## Pré-requisitos

- Bibliotecas:
  - [SPI](https://www.arduino.cc/en/reference/SPI) (comunicação SPI)
  - [MFRC522](https://github.com/miguelbalboa/rfid) (controle do módulo RFID)
  - [TimeLib](https://www.arduino.cc/reference/en/libraries/timelib/) (gerenciamento de tempo)

## Compilação e Execução

1. Certifique-se de ter as bibliotecas necessárias instaladas em sua IDE Arduino.
2. Conecte o módulo RFID ao Arduino seguindo o layout de pinos indicado no código.
3. Carregue o código no Arduino e execute-o.
4. O sistema lerá os cartões RFID e registrará as entradas e saídas dos alunos.

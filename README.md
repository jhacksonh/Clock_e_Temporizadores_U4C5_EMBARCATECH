# Documentação do Projeto: Semáforo com Temporizador Periódico

## Visão Geral

Este projeto simula um semáforo usando o microcontrolador **Raspberry Pi Pico W**. Três LEDs (vermelho, amarelo e verde) representam as luzes do semáforo, mudando de cor a cada **3 segundos**. Além disso, o microcontrolador exibe mensagens na porta serial para indicar o estado atual do semáforo.

## Componentes Utilizados

- **Raspberry Pi Pico W** (microcontrolador)
- **3 LEDs** (Vermelho, Amarelo e Verde)
- **3 Resistores** de 330 Ω (para limitar a corrente nos LEDs)

## Como Funciona?

1. O semáforo inicia com o **LED vermelho aceso**.
2. Após **3 segundos**, o LED muda para **amarelo**.
3. Depois de mais **3 segundos**, muda para **verde**.
4. Esse ciclo se repete continuamente.
5. A cada **1 segundo**, o microcontrolador imprime uma mensagem informando o estado atual do semáforo.

## Estrutura do Código

### Principais Definições

- `TIMER_ACTIVE_MS`: Define o tempo de troca do LED (**3 segundos**).
- `PINS_RGB[3]`: Armazena os GPIOs conectados aos LEDs.
- `INDEX`: Indica qual LED deve estar aceso.
- `timer`: Variável usada para o temporizador.
- `informations[3]`: Lista de mensagens para cada cor do semáforo.
- `information`: Mensagem que será exibida na serial.

### Funções do Código

#### `ConfigPins(uint pin, bool InorOut)`

Configura os pinos GPIO dos LEDs.

#### `Signal()`

Ativa o LED correspondente e atualiza a mensagem do semáforo.

#### `repeating_timer_callback(struct repeating_timer *t)`

Função chamada automaticamente pelo temporizador para alternar os LEDs.

#### `main()`

Inicializa os LEDs, configura o temporizador e entra no loop infinito, exibindo mensagens a cada segundo.

## Exemplo de Saída no Terminal

```
Sinal vermelho, não atravessar
Sinal vermelho, não atravessar
Sinal vermelho, não atravessar
Mudando Cor do Sinal...
Sinal amarelo, atravessar com cuidado
Sinal amarelo, atravessar com cuidado
Sinal amarelo, atravessar com cuidado
Mudando Cor do Sinal...
Sinal verde, atravessar
Sinal verde, atravessar
Sinal verde, atravessar
Mudando Cor do Sinal...
```

## Ligações no Raspberry Pi Pico W

| LED      | GPIO |
| -------- | ---- |
| Vermelho | 13   |
| Amarelo  | 12   |
| Verde    | 11   |

Cada LED está ligado ao Raspberry Pi Pico W por meio de um resistor de **330 Ω** para evitar danos.


## Como Rodar o Projeto no Wokwi e VS Code

O projeto já está configurado para rodar no **Wokwi** diretamente pelo **VS Code**. Para executar a simulação:

1. Clone o repositório do projeto.
2. Importe o projeto no **VS Code** usando a extensão **Raspbarry Pi Pico**.
3. Instale a extensão **Wokwi**.
4. Compile o projeto.
5. Localize o arquivo `diagram.json` na raiz do projeto.
6. Execute o `diagram.json`.
7. O simulador abrirá automaticamente, permitindo rodar o código sem precisar do hardware físico.

## Testes com BitDogLab
1. Compile e envie o código do arquivo .uf2 para a **BitDogLab**.
2. Use um monitor serial para visualizar as mensagens do semáforo.

## Conclusão

Este projeto demonstra o uso de **temporizadores periódicos** no Raspberry Pi Pico W para criar um semáforo funcional. Ele ensina conceitos de manipulação de **GPIOs**, uso de **temporizadores** e **comunicação serial**. Além disso, com o **Wokwi** e o **VS Code**, é possível testar tudo sem precisar do hardware físico, facilitando o desenvolvimento e a depuração do código.

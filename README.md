# Projeto de Monitoramento de Temperatura e Movimento com Sensor DHT22 e PIR 
## Projeto SmartEnergy

## Descrição
Este projeto monitora temperatura, umidade e movimento utilizando os sensores **DHT22** e **PIR**, além de um LED que simula o acionamento de um ar-condicionado. O sistema é controlado por um microcontrolador, como o Arduino, e realiza ações com base nas condições detectadas.

## Funcionalidades
- **Detecção de Movimento**: 
  - Ativa o sistema de monitoramento ao detectar movimento com o sensor PIR.
- **Monitoramento de Temperatura e Umidade**:
  - Mede a temperatura e umidade ambiente utilizando o sensor DHT22.
  - Calcula a média móvel dos últimos valores medidos.
- **Controle de Temperatura**:
  - Aciona um LED para simular o funcionamento de um ar-condicionado caso a temperatura média ultrapasse 24°C.
  - Desliga o LED quando a temperatura retorna a níveis normais.

## Componentes Necessários
### Hardware
- Sensor DHT22 (temperatura e umidade).
- Sensor PIR (detecção de movimento).
- LED (simulação do ar-condicionado).
- Placa Arduino ou similar.
- Resistores e jumpers.

### Software
- Arduino IDE para desenvolvimento do código.
- Node-RED para criar um dashboard visual.

## Configurações
- Limite de temperatura: configurável pela constante `highTempThreshold` no código (padrão: 24°C).
- Tempo de ativação: ajustável pela constante `activeTime` (padrão: 250 segundos).

## Como Funciona
1. O sistema permanece inativo até que o sensor PIR detecte movimento.
2. Após a ativação, o sensor DHT22 realiza leituras periódicas de temperatura e umidade.
3. Os valores medidos são utilizados para calcular a média móvel.
4. Se a temperatura média ultrapassar 24°C:
   - O LED é aceso para simbolizar o acionamento do ar-condicionado.
   - Um alerta é exibido no monitor serial.
5. O sistema retorna ao estado inativo após o tempo definido (`activeTime`) ou na ausência de movimento.

## Extensões Futuras
- Integração com redes Wi-Fi ou Bluetooth para monitoramento remoto.
- Conexão com plataformas IoT para armazenamento e visualização dos dados.
- Controle de dispositivos reais como ventiladores ou ar-condicionados.

## Exemplo de Uso
### Conexão de Hardware
- Conecte o sensor PIR ao pino digital 3.
- Conecte o sensor DHT22 ao pino digital 2.
- Conecte o LED ao pino digital 4 (com um resistor apropriado).

### Dashboard (Opcional)
- Use Node-RED para criar um dashboard visual exibindo os valores de temperatura e umidade.


# Projeto Final – Análise de Estratégias de Escalonamento no Zephyr RTOS

Este projeto foi desenvolvido como parte da disciplina **DCC403 – Sistemas Operacionais** na Universidade Federal de Roraima (UFRR).

## 📋 Descrição do Projeto

O objetivo foi implementar e analisar **três tarefas concorrentes** em um sistema baseado no **Zephyr RTOS**, testando diferentes estratégias de escalonamento:

- **Preemptivo com prioridade fixa**
- **Round-Robin**
- **Cooperativo**

Cada tarefa representa um componente típico de um sistema embarcado:

| Tarefa   | Função                     | Frequência | Prioridade |
|----------|----------------------------|------------|------------|
| Sensor   | Leitura de sensor          | 500 ms     | Alta       |
| Teclado  | Comunicação com teclado    | 1000 ms    | Média      |
| Display  | Atualização do display     | 2000 ms    | Baixa      |

## ⚙️ Estrutura do Projeto

- `src/main.c`: código principal com as três tarefas.
- `prj.conf`: configurações do Zephyr (printk, console, escalonamento, etc).
- `README.md`: orientação geral do projeto.

## 🚀 Estratégias de Escalonamento Testadas

### 1. Preemptivo por Prioridade (padrão)

- Prioridades diferentes:
  ```c
  #define PRIORIDADE_SENSOR 0
  #define PRIORIDADE_TECLADO 1
  #define PRIORIDADE_DISPLAY 2
  ```
- A tarefa do Sensor tem maior prioridade e preempção é automática.

### 2. Round-Robin

- Todas as tarefas com mesma prioridade:
  ```c
  #define PRIORIDADE_SENSOR 1
  #define PRIORIDADE_TECLADO 1
  #define PRIORIDADE_DISPLAY 1
  ```
- Configuração no `prj.conf`:
  ```ini
  CONFIG_TIMESLICING=y
  CONFIG_TIMESLICE_SIZE=10
  ```

### 3. Cooperativo

- Prioridades cooperativas usando `K_PRIO_COOP(n)`:
  ```c
  #define PRIORIDADE_SENSOR  K_PRIO_COOP(0)
  ```
- Controle manual com `k_yield()` após cada execução:
  ```c
  void sensor_thread(void) {
      while (1) {
          printk("[Sensor] Tempo: %d ms\n", k_uptime_get());
          k_msleep(500);
          k_yield();
      }
  }
  ```

## 📦 Requisitos e Instalação

### 📥 O que instalar:

- [Zephyr SDK](https://docs.zephyrproject.org/latest/develop/toolchains/zephyr_sdk.html)
- qemu-system-x86
- Python 3 + `west` (gerenciador de projetos Zephyr)
- Git
- Pacotes de build (CMake, Ninja, etc)

### ⚙️ Como configurar o ambiente:

```bash
# Instale o qemu
sudo dnf install qemu-system-x86 

# Instale o west
pip install west

# Baixe e configure o Zephyr
west init zephyrproject
cd zephyrproject
west update
west zephyr-export
```

> Certifique-se de ter definido as variáveis de ambiente: `ZEPHYR_BASE`, `ZEPHYR_TOOLCHAIN_VARIANT`, etc.

## ▶️ Como Compilar e Executar

```bash
# Vá até o diretório do projeto
cd escalonamento

# Compile para sua placa (ex: qemu_x86, nrf52, etc)
west build -b <sua_placa> .

# Para simular com QEMU (se compatível)
west build -t run
```

### 📡 Para placas físicas:

```bash
# Grave o firmware
west flash

# Veja os logs da UART
screen /dev/ttyUSB0 115200
```

## 📊 Resultados Observados

| Estratégia     | Comportamento                                                   |
|----------------|------------------------------------------------------------------|
| Preemptivo     | Sensor domina, tarefas de menor prioridade podem atrasar        |
| Round-Robin    | Execução justa entre tarefas com divisão de tempo equitativa    |
| Cooperativo    | Controle manual da CPU; tarefas só cedem com `k_yield()`        |

## 👨‍💻 Autores

- **Luciano dos Santos Nascimento**
- **Wesley Silva Araújo**


## Simulador 
 - Usamos o QEMU do zephyr rtos

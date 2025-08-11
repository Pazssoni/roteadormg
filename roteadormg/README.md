# roteadormg

Projeto OMNeT++ para simulação de roteamento distribuído (Distance Vector) com coleta de métricas e verificação de consistência.

## Requisitos
- OMNeT++ 6.x instalado e configurado no PATH

## Estrutura
- `src/RouterNode.ned`: módulo simples que implementa o algoritmo de vetor de distâncias
- `src/Monitor.ned`: módulo simples que cria enlaces, coleta métricas e imprime o resumo final
- `src/RoutingNet.ned`: rede com `numNodes` nós e um `Monitor`
- `src/Routing.msg`: definição de mensagem de atualização de roteamento
- `src/*.cc`, `src/*.h`: implementação em C++
- `omnetpp.ini`: 5 topologias configuradas em seções distintas

## Como compilar
1. Gere as mensagens (opp_msgc é chamado automaticamente pelo makefile do OMNeT++)
2. No diretório raiz do projeto, execute:

```bash
opp_makemake -f --deep -O out -o roteadormg
make -j$(nproc)
```

Isso criará os binários em `out/`.

## Como executar
Escolha uma topologia (Topologia1 .. Topologia5):

```bash
./out/roteadormg -u Cmdenv -c Topologia1 -n src omnetpp.ini
```

A saída deverá conter:
- Matriz de custos mínimos correta (calculada centralmente pelo Monitor)
- Número total de mensagens trocadas
- Tempo de convergência
- Verificação de consistência das tabelas dos nós
#!/bin/bash
# Testes da Bolsa de Valores - fase 1
# Uso: ./testar.sh   (na pasta do projeto, depois de "make")
# Não mexe no bvdata.txt: trabalha com cópias numa pasta temporária.

BV="$(pwd)/bv"
LOGS="$(pwd)/logs_teste"          # os bv.log de cada teste ficam guardados aqui
rm -rf "$LOGS"; mkdir -p "$LOGS"
DIR=$(mktemp -d)
cd "$DIR"
OK=0; FALHOU=0

N=0
guarda_log() { # guarda o bv.log do teste anterior antes de começar o próximo
    if [ -f bv.log ]; then N=$((N+1)); mv bv.log "$LOGS/teste_$N.log"; fi
}

verifica() {   # verifica "descrição" comando_de_teste...
    local desc="$1"; shift
    if "$@"; then echo "  OK     $desc"; OK=$((OK+1))
    else          echo "  FALHOU $desc"; FALHOU=$((FALHOU+1)); fi
}

echo "1. Ficheiro com linhas estragadas"
cat > teste.txt <<FIM
Frisa 10120 5.00 6.32
Teste abc 5.0
Galp 50000 10.00 14.85
SoNome
EDP 80000 2.50 3.47 lixo
FIM
guarda_log
"$BV" teste.txt 9000 > saida.txt 2>&1
verifica "termina sem erro"                  [ $? -eq 0 ]
verifica "carrega as 2 empresas válidas"     grep -q "2 empresas carregadas" bv.log
verifica "linha 2 ignorada no log"           grep -q "Linha 2 ignorada" bv.log
verifica "linha 4 ignorada no log"           grep -q "Linha 4 ignorada" bv.log
verifica "linha 5 ignorada no log"           grep -q "Linha 5 ignorada" bv.log
verifica "ficheiro regravado só com válidas" [ "$(wc -l < teste.txt)" -eq 2 ]
verifica "não ficou nenhum .tmp"             [ ! -e teste.txt.tmp ]

echo "2. Ficheiro que não existe"
guarda_log
"$BV" nao_existe.txt > /dev/null 2>&1
verifica "termina com erro"                  [ $? -ne 0 ]
verifica "erro registado no log"             grep -qi "não consegui abrir 'nao_existe.txt'" bv.log
verifica "não criou o ficheiro"              [ ! -e nao_existe.txt ]

echo "3. Argumentos inválidos"
"$BV" teste.txt 80 > /dev/null 2>&1;      verifica "recusa porta 80"          [ $? -ne 0 ]
"$BV" teste.txt 70000 > /dev/null 2>&1;   verifica "recusa porta 70000"       [ $? -ne 0 ]
"$BV" a b c > /dev/null 2>&1;             verifica "recusa argumentos a mais" [ $? -ne 0 ]

echo "4. Valores incoerentes no ficheiro"
cat > teste.txt <<FIM
Frisa 10120 5.00 6.32
Galp -5 10.00 14.85
EDP 80000 0 3.47
Sonae 100 1.00 -2
Frisa 1 1.00 1.00
NOS 0 5.00 3.92
FIM
guarda_log
"$BV" teste.txt > /dev/null 2>&1
verifica "carrega só Frisa e NOS"            grep -q "2 empresas carregadas" bv.log
verifica "rejeita ações negativas"           grep -q "Linha 2 ignorada (ações por colocar negativas)" bv.log
verifica "rejeita valor nominal 0"           grep -q "Linha 3 ignorada (valor nominal" bv.log
verifica "rejeita cotação negativa"          grep -q "Linha 4 ignorada (cotação" bv.log
verifica "rejeita empresa repetida"          grep -q "Linha 5 ignorada (empresa repetida)" bv.log
verifica "NOS com 0 ações é aceite"          grep -q "^NOS 0 " teste.txt

echo "5. Validação de ordens (demonstração no arranque)"
cat > teste.txt <<FIM
Galp 50000 10.00 14.85
EDP 80000 2.50 3.47
FIM
guarda_log
"$BV" teste.txt > /dev/null 2>&1
verifica "Galp aceite"                       grep -q "ORDEM VÁLIDA.*Galp" bv.log
verifica "empresa inexistente rejeitada"     grep -q "REJEITADA.*não existe" bv.log
verifica "quantidade negativa rejeitada"     grep -q "REJEITADA.*Quantidade" bv.log

echo "6. Categorias dos logs [LOG] [WARNING] [ERROR]"
cat > teste.txt <<FIM
Galp 50000 10.00 14.85
Teste abc 5.0
EDP 80000 2.50 3.47
FIM
guarda_log
"$BV" teste.txt > saida.txt 2>&1
verifica "todas as linhas do bv.log têm categoria" \
    bash -c "! grep -vE '^\[[0-9-]+ [0-9:]+\] \[(LOG|WARNING|ERROR)\] ' bv.log"
verifica "categoria também aparece no terminal"  grep -qE '\] \[(LOG|WARNING|ERROR)\] ' saida.txt
verifica "arranque é [LOG]"                      grep -q  "\[LOG\].*empresas carregadas" bv.log
verifica "linha estragada é [WARNING]"           grep -q  "\[WARNING\].*Linha 2 ignorada" bv.log
verifica "ordem válida é [LOG]"                  grep -q  "\[LOG\].*ORDEM VÁLIDA" bv.log
verifica "ordem rejeitada é [WARNING]"           grep -q  "\[WARNING\].*REJEITADA" bv.log
guarda_log
"$BV" nao_existe.txt > /dev/null 2>&1
verifica "ficheiro inexistente é [ERROR]"        grep -qi "\[ERROR\].*consegui abrir" bv.log

guarda_log
echo
echo "Logs dos testes guardados em: $LOGS"
echo "Resultado: $OK OK, $FALHOU falhados"
rm -rf "$DIR"
[ $FALHOU -eq 0 ]

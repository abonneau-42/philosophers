#!/bin/bash

N=50  # nombre d'exécutions
total=0

for i in $(seq 1 $N); do
    # On récupère uniquement le temps réel (real) de la commande `time`
    t=$( { time ./philo 20 401 200 200 > /dev/null; } 2>&1 | grep real | awk '{print $2}' )
    
    # Convertir temps format mm:ss.sss en secondes
    IFS='m' read -r min rest <<< "$t"
    sec=${rest%s}
    sec=${sec}s
    sec=${sec%%s}
    sec_float=$(echo "$min * 60 + $sec" | bc -l)

    total=$(echo "$total + $sec_float" | bc -l)
done

avg=$(echo "scale=3; $total / $N" | bc -l)
echo "Temps moyen d'exécution : $avg secondes"

#!/usr/bin/env bash
# Mesure l'écart (ms) entre le 1ᵉʳ log et le log "died"
# et vérifie qu'il reste <= MARGIN.

set -euo pipefail
BIN=./philo
ITER=30          # nombre d'itérations
ARGS="50 400 200 200"   # n  t_die t_eat t_sleep
MARGIN=10        # tolérance en millisecondes

t_die=$(echo "$ARGS" | awk '{print $2}')
fail=0

red()  { printf "\e[31m%s\e[0m\n" "$*"; }
green(){ printf "\e[32m%s\e[0m\n" "$*"; }

for i in $(seq 1 "$ITER"); do
  OUT=$(mktemp)
  "$BIN" $ARGS >"$OUT" &
  pid=$!
  wait "$pid"

first=$(head -n1 "$OUT" \
        | sed $'s/\x1b\\[[0-9;]*m//g' \
        | awk '{print $1}')
death=$(grep " died" "$OUT" \
        | sed $'s/\x1b\\[[0-9;]*m//g' \
        | awk '{print $1}')

  if [[ -z "$death" || -z "$first" ]]; then
    red "run $i : log manquant"
    cat "$OUT"
    rm -f "$OUT"
    exit 1
  fi

  real=$((death - first))
  diff=$((real - t_die)); ((diff<0)) && diff=$((-diff))

  if (( diff > MARGIN )); then
    red "run $i : dérive ${diff} ms (attendu $t_die, réel $real)"
    fail=1
  else
    green "run $i : dérive ${diff} ms OK"
  fi
  rm -f "$OUT"
done

if (( fail == 0 )); then
  green "Tous les runs dans ±${MARGIN} ms ✅"
else
  red   "Au moins un run hors marge ❌"
  exit 1
fi

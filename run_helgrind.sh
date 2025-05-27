#!/usr/bin/env bash
set -euo pipefail
BIN=./philo
LOG=$(mktemp)

tests=(
  "2   600 200 200 10"
  "2   800 200 200 10"
  "8   400 200 200 10"
  "199 610 200 200 10"
)

red()  { printf "\e[31m%s\e[0m\n" "$*"; }
green(){ printf "\e[32m%s\e[0m\n" "$*"; }

for args in "${tests[@]}"; do
  printf "Helgrind %-25s … " "$args"
  if valgrind --error-exitcode=42 --quiet --tool=helgrind \
        "$BIN" $args >"$LOG" 2>&1; then
    green OK
  else
    red "DATA-RACE détectée !"
    cat "$LOG"; exit 1
  fi
done
green "Tous les tests Helgrind sont clean ✅"
rm -f "$LOG"

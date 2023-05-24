#!/bin/bash

pids=$(pgrep philo_bonus)

if [ -z "$pids" ]; then
  echo "not running."
  exit 0
fi
for pid in $pids; do
  kill $pid
done



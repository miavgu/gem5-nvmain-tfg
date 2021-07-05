#!/bin/bash
redis-server &
sleep 5s
/sbin/m5 resetstats
redis-benchmark -n 10000 -t get,set,lpush,lpop
/sbin/m5 exit

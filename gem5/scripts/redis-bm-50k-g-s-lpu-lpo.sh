#!/bin/bash
redis-server &
sleep 5
/sbin/m5 resetstats
redis-benchmark -n 50000 -t get,set,lpush,lpop
/sbin/m5 exit

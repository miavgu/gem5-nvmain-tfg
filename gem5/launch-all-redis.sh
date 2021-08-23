date > incio_all_redis.txt
./launch-frfcfs10k.sh
sleep 1m
./launch-frfcfscache10k.sh
sleep 1m
./launch-frfcfs25k.sh
sleep 1m
./launch-frfcfscache25k.sh
sleep 1m
./launch-frfcfs50k.sh
sleep 1m
./launch-frfcfscache50k.sh
date > fin_all_redis.txt

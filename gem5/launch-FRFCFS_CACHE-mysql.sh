date > inicio_FRFCFScache-mysql.txt
build/X86/gem5.fast --outdir=FRFCFScache-mysql configs/example/fs.py --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/NVM_2CH_FRFCFS-CACHE.config --cpu-type=TimingSimpleCPU --kernel=$M5_PATH/binaries/x86_64-vmlinux-4.19.83 --disk-image=$M5_PATH/disks/parsec.img --caches --l1i_size=32kB --l1i_assoc=8 --l1d_size=32kB --l1d_assoc=8 --l2cache --l2_size=256kB --l2_assoc=8 --script=scripts/mysql-10000.sh > stats_nvmain_frfcfscache-mysql.txt 
date > fin_FRFCFScache-mysql.txt

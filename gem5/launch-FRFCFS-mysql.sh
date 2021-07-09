date > inicio_FRFCFS-mysql.txt
build/X86/gem5.opt --outdir=FRFCFS-mysql configs/example/fs.py --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/NVM_2CH_FRFCFS.config --cpu-type=TimingSimpleCPU --kernel=binaries/x86_64-vmlinux-4.19.83 --disk-image=disks/parsec.img --caches --l1i_size=32kB --l1i_assoc=8 --l1d_size=32kB --l1d_assoc=8 --l2cache --l2_size=256kB --l2_assoc=8 --script=scripts/mysql-1000.sh > stats_nvmain_frfcfs-mysql.txt 
date > fin_FRFCFS-mysql.txt

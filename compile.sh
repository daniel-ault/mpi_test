
mpicc pi.c -o ../bin/pi.a
qsub run_pi.sh
qstat -u dault
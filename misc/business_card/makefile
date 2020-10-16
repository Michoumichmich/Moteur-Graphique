.PHONY:
exec:
	mpic++ -o card business_card_demo.cpp -O3 -std=c++11

run: exec
	mpirun -np $(shell nproc) -oversubscribe ./card > test.ppm

mpi_install:
	sudo apt-get install libopenmpi-dev openmpi-bin libhdf5-openmpi-dev

clean:
	rm card test.ppm
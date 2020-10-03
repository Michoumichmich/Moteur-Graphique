.PHONY:
all:
	mpic++ -o card business_card_demo.cpp

run:
	mpirun -np $(shell nproc) -oversubscribe ./card > test.ppm

mpi_install:
	sudo apt-get install libopenmpi-dev openmpi-bin libhdf5-openmpi-dev
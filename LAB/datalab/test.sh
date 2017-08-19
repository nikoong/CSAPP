echo "do dlc"
./dlc -e bits.c
echo "make btese"
make clean
make fshow ishow
make btest
./btest

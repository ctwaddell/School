SHELL	:= sh
#	Quick and dirty make file to test all code submissions against
#	input files

#	Define the executable targets
all: GM AR D E SUR GWR GR driver
alltests: test_GM test_AR test_D test_E test_SUR test_GWR test_GR test_driver

#	Initial setup - copy code from src to current folder
setup:
	cp src/enigma.h . 
	cp src/enigma_sol.h .
	cp src/test_GM.c .
	cp src/test_AR.c .
	cp src/test_D.c .
	cp src/test_E.c .
	cp src/test_SUR.c .
	cp src/test_GWR.c .
	cp src/test_GR.c .
	cp src/test_driver.c .
	mkdir -p tests

#	Executables follow
GM: test_GM.c enigma_functions.c
	gcc -g test_GM.c enigma_functions.c -o test_GM -w
	mkdir -p tests/GM
	mv test_GM tests/GM/
	cp inputs/input_GM* tests/GM/

AR: test_AR.c enigma_functions.c
	gcc -g test_AR.c enigma_functions.c -o test_AR -w
	mkdir -p tests/AR
	mv test_AR tests/AR/
	cp inputs/input_AR* tests/AR/

D: test_D.c enigma_functions.c
	gcc -g test_D.c enigma_functions.c -o test_D -w
	mkdir -p tests/D
	mv test_D tests/D/
	cp inputs/input_D* tests/D/

E: test_E.c enigma_functions.c
	gcc -g test_E.c enigma_functions.c -o test_E -w
	mkdir -p tests/E
	mv test_E tests/E/
	cp inputs/input_E* tests/E/

SUR: test_SUR.c enigma_functions.c
	gcc -g test_SUR.c enigma_functions.c -o test_SUR -w
	mkdir -p tests/SUR
	mv test_SUR tests/SUR/
	cp inputs/input_SUR* tests/SUR/

GWR: test_GWR.c enigma_functions.c
	gcc -g test_GWR.c enigma_functions.c -o test_GWR -w
	mkdir -p tests/GWR
	mv test_GWR tests/GWR/
	cp inputs/input_GWR* tests/GWR/

GR: test_GR.c enigma_functions.c
	gcc -g test_GR.c enigma_functions.c -o test_GR -w
	mkdir -p tests/GR
	mv test_GR tests/GR/
	cp inputs/input_GR* tests/GR/

driver: test_driver.c 
	gcc -g test_driver.c enigma_functions.c -o test_driver -w
	mkdir -p tests/driver
	mv test_driver tests/driver/
	cp inputs/input_driver* tests/driver/

#	Define the test commands
test_GM:
	tests/GM/./test_GM < tests/GM/input_GM_1 > tests/GM/output_GM_1
	tests/GM/./test_GM < tests/GM/input_GM_2 > tests/GM/output_GM_2
	tests/GM/./test_GM < tests/GM/input_GM_3 > tests/GM/output_GM_3
	tests/GM/./test_GM < tests/GM/input_GM_4 > tests/GM/output_GM_4
	tests/GM/./test_GM < tests/GM/input_GM_5 > tests/GM/output_GM_5
	cat tests/GM/output_GM_* >> final_GM_output

test_GR:
	tests/GR/./test_GR < tests/GR/input_GR_1 > tests/GR/output_GR_1
	tests/GR/./test_GR < tests/GR/input_GR_2 > tests/GR/output_GR_2
	tests/GR/./test_GR < tests/GR/input_GR_3 > tests/GR/output_GR_3
	tests/GR/./test_GR < tests/GR/input_GR_4 > tests/GR/output_GR_4
	cat tests/GR/output_GR_* >> final_GR_output

test_AR:
	tests/AR/./test_AR < tests/AR/input_AR_1 > tests/AR/output_AR_1
	tests/AR/./test_AR < tests/AR/input_AR_2 > tests/AR/output_AR_2
	tests/AR/./test_AR < tests/AR/input_AR_3 > tests/AR/output_AR_3
	tests/AR/./test_AR < tests/AR/input_AR_4 > tests/AR/output_AR_4
	tests/AR/./test_AR < tests/AR/input_AR_5 > tests/AR/output_AR_5
	tests/AR/./test_AR < tests/AR/input_AR_6 > tests/AR/output_AR_6
	tests/AR/./test_AR < tests/AR/input_AR_7 > tests/AR/output_AR_7
	tests/AR/./test_AR < tests/AR/input_AR_8 > tests/AR/output_AR_8
	cat tests/AR/output_AR_* >> final_AR_output

test_D:
	tests/D/./test_D < tests/D/input_D_1 > tests/D/output_D_1
	tests/D/./test_D < tests/D/input_D_2 > tests/D/output_D_2
	tests/D/./test_D < tests/D/input_D_3 > tests/D/output_D_3
	tests/D/./test_D < tests/D/input_D_4 > tests/D/output_D_4
	tests/D/./test_D < tests/D/input_D_5 > tests/D/output_D_5
	tests/D/./test_D < tests/D/input_D_6 > tests/D/output_D_6
	tests/D/./test_D < tests/D/input_D_7 > tests/D/output_D_7
	tests/D/./test_D < tests/D/input_D_8 > tests/D/output_D_8
	cat tests/D/output_D_* >> final_D_output

test_driver:
	tests/driver/./test_driver < tests/driver/input_driver_1 > tests/driver/output_driver_1
	tests/driver/./test_driver < tests/driver/input_driver_2 > tests/driver/output_driver_2
	tests/driver/./test_driver < tests/driver/input_driver_3 > tests/driver/output_driver_3
	tests/driver/./test_driver < tests/driver/input_driver_4 > tests/driver/output_driver_4
	cat tests/driver/output_driver_* >> final_driver_output

test_E:
	tests/E/./test_E < tests/E/input_E_1 > tests/E/output_E_1
	tests/E/./test_E < tests/E/input_E_2 > tests/E/output_E_2
	tests/E/./test_E < tests/E/input_E_3 > tests/E/output_E_3
	tests/E/./test_E < tests/E/input_E_4 > tests/E/output_E_4
	tests/E/./test_E < tests/E/input_E_5 > tests/E/output_E_5
	tests/E/./test_E < tests/E/input_E_6 > tests/E/output_E_6
	tests/E/./test_E < tests/E/input_E_7 > tests/E/output_E_7
	tests/E/./test_E < tests/E/input_E_8 > tests/E/output_E_8
	cat tests/E/output_E* >> final_E_output

test_GWR:
	tests/GWR/./test_GWR < tests/GWR/input_GWR_1 > tests/GWR/output_GWR_1
	tests/GWR/./test_GWR < tests/GWR/input_GWR_2 > tests/GWR/output_GWR_2
	tests/GWR/./test_GWR < tests/GWR/input_GWR_3 > tests/GWR/output_GWR_3
	tests/GWR/./test_GWR < tests/GWR/input_GWR_4 > tests/GWR/output_GWR_4
	tests/GWR/./test_GWR < tests/GWR/input_GWR_5 > tests/GWR/output_GWR_5
	cat tests/GWR/output_GWR* >> final_GWR_output

test_SUR:
	tests/SUR/./test_SUR < tests/SUR/input_SUR_1 > tests/SUR/output_SUR_1
	tests/SUR/./test_SUR < tests/SUR/input_SUR_2 > tests/SUR/output_SUR_2
	tests/SUR/./test_SUR < tests/SUR/input_SUR_3 > tests/SUR/output_SUR_3
	tests/SUR/./test_SUR < tests/SUR/input_SUR_4 > tests/SUR/output_SUR_4
	cat tests/SUR/output_SUR* >> final_SUR_output

#	Remove all setup
clean:
	rm -rf tests/
	rm test_*
	rm enigma.h
	rm enigma_sol.h

#	Remove all init
delete:
	rm -rf src/
	rm -rf inputs/
	rm Makefile

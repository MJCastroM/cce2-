@echo off
echo Compilando el decodificador con: make
make
echo Generando archivo con: utils\\Windows\\brstchannel.exe -q 256 -n 56 -s 1753049393 -R 500000 test_files/test_original.dat
utils\\Windows\\brstchannel.exe -q 256 -n 56 -s 1753049393 -R 500000 test_files/test_original.dat
echo.
echo Codificando el archivo con: utils\\Windows\\rsencode.exe -m 8 -n 64 -r 8 -L 1 -8 test_files/test_original.dat test_files/test_original.rse
utils\\Windows\\rsencode.exe -m 8 -n 64 -r 8 -L 1 -8 test_files/test_original.dat test_files/test_original.rse
echo.
echo Primera Configuracion
echo "rho = 0,01 y delta = 0,05"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.05 --rho 0.01 -s 1753049981 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.05 --rho 0.01 -s 1753049981 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,01 y delta = 0,10"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.10 --rho 0.01 -s 1753050262 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.10 --rho 0.01 -s 1753050262 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,01 y delta = 0,25"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.25 --rho 0.01 -s 1753050505 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.25 --rho 0.01 -s 1753050505 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,01 y delta = 0,50"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.50 --rho 0.01 -s 1753050695 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.50 --rho 0.01 -s 1753050695 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,01 y delta = 0,75"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.01 -s 1753050854 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.01 -s 1753050854 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,01 y delta = 0,90"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.90 --rho 0.01 -s 1753051018 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.90 --rho 0.01 -s 1753051018 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo Segunda Configuracion
echo "rho = 0,0001 y delta = 0,75"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.0001 -s 1753201974 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.0001 -s 1753201974 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,0003 y delta = 0,75"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.0003 -s 1753202119 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.0003 -s 1753202119 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,001 y delta = 0,75"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.001 -s 1753202282 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.001 -s 1753202282 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,003 y delta = 0,75"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.003 -s 1753202429 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.003 -s 1753202429 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,01 y delta = 0,75"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.01 -s 1753202580 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.01 -s 1753202580 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,03 y delta = 0,75"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.03 -s 1753202731 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.03 -s 1753202731 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo "rho = 0,1 y delta = 0,75"
echo.
echo Simulando canal ruidoso con: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.1 -s 1753202958 test_files/test_original.rse
utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.1 -s 1753202958 test_files/test_original.rse
echo.
echo Decodificando con: rsdecode.exe 64 8 .\test_files\test_original.brst
rsdecode.exe 64 8 .\test_files\test_original.brst
echo.
echo Comparando archivo original con el decodificado con: utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
utils\\Windows\\diffblock.exe -m 8 -n 56 .\test_files\test_original.dat .\test_files\test_original.out
echo.
echo Fin del test.
cmd /k
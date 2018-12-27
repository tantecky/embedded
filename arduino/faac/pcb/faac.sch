EESchema Schematic File Version 4
LIBS:faac-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L mysyms:BatCon J1
U 1 1 5C25B880
P 2650 2250
F 0 "J1" H 2808 2257 50  0000 L CNN
F 1 "BatCon" H 2808 2166 50  0000 L CNN
F 2 "myfoots:BatCon" H 2700 2350 50  0001 C CNN
F 3 "" H 2700 2350 50  0001 C CNN
	1    2650 2250
	0    1    1    0   
$EndComp
$Comp
L mysyms:Reg3V3 U3
U 1 1 5C25B9C3
P 4400 1750
F 0 "U3" H 4650 1700 50  0000 L CNN
F 1 "Reg3V3" H 4650 1600 50  0000 L CNN
F 2 "myfoots:Reg3V3" H 4450 1850 50  0001 C CNN
F 3 "" H 4450 1850 50  0001 C CNN
	1    4400 1750
	-1   0    0    1   
$EndComp
$Comp
L mysyms:HPD8407-F U1
U 1 1 5C25BB2A
P 3200 3500
F 0 "U1" H 2850 3350 50  0000 L CNN
F 1 "HPD8407-F" H 2500 3450 50  0000 L CNN
F 2 "myfoots:HPD8407-F" H 3250 3600 50  0001 C CNN
F 3 "" H 3250 3600 50  0001 C CNN
	1    3200 3500
	1    0    0    -1  
$EndComp
$Comp
L mysyms:ProMini U2
U 1 1 5C25BBA0
P 4300 3450
F 0 "U2" H 4300 4365 50  0000 C CNN
F 1 "ProMini" H 4300 4274 50  0000 C CNN
F 2 "myfoots:ProMini" H 4300 3450 50  0001 C CNN
F 3 "" H 4300 3450 50  0001 C CNN
	1    4300 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5C25BD17
P 2850 2500
F 0 "#PWR0101" H 2850 2250 50  0001 C CNN
F 1 "GND" H 2855 2327 50  0000 C CNN
F 2 "" H 2850 2500 50  0001 C CNN
F 3 "" H 2850 2500 50  0001 C CNN
	1    2850 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2350 2850 2350
Wire Wire Line
	2850 2350 2850 2500
Wire Wire Line
	3050 3350 3050 3250
Wire Wire Line
	3050 2350 2850 2350
Connection ~ 2850 2350
$Comp
L power:GND #PWR01
U 1 1 5C25BEEA
P 4350 2000
F 0 "#PWR01" H 4350 1750 50  0001 C CNN
F 1 "GND" H 4355 1827 50  0000 C CNN
F 2 "" H 4350 2000 50  0001 C CNN
F 3 "" H 4350 2000 50  0001 C CNN
	1    4350 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1900 4350 2000
Wire Wire Line
	4450 1900 4450 2000
Wire Wire Line
	4450 2000 4350 2000
Connection ~ 4350 2000
Wire Wire Line
	2800 2200 4250 2200
Wire Wire Line
	4250 2200 4250 1900
Wire Wire Line
	3800 2900 3250 2900
Wire Wire Line
	3250 2900 3250 3350
Wire Wire Line
	4550 1900 4550 2350
Wire Wire Line
	4550 2350 3600 2350
Wire Wire Line
	3150 2350 3150 3350
Wire Wire Line
	3800 3800 3550 3800
Wire Wire Line
	3550 3800 3550 3250
Wire Wire Line
	3550 3250 3050 3250
Connection ~ 3050 3250
Wire Wire Line
	3050 3250 3050 2350
Wire Wire Line
	3800 3600 3600 3600
Wire Wire Line
	3600 3600 3600 2350
Connection ~ 3600 2350
Wire Wire Line
	3600 2350 3150 2350
$Comp
L power:GND #PWR02
U 1 1 5C25C3DB
P 4950 3650
F 0 "#PWR02" H 4950 3400 50  0001 C CNN
F 1 "GND" H 4955 3477 50  0000 C CNN
F 2 "" H 4950 3650 50  0001 C CNN
F 3 "" H 4950 3650 50  0001 C CNN
	1    4950 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3600 4950 3600
Wire Wire Line
	4950 3600 4950 3650
Wire Wire Line
	3350 3350 3450 3350
$Comp
L mysyms:Device_Antenna AE1
U 1 1 5C24F6CE
P 3450 4000
F 0 "AE1" H 3650 3900 50  0000 R CNN
F 1 "Device_Antenna" H 4100 4000 50  0000 R CNN
F 2 "myfoots:antenna" H 3450 4000 50  0001 C CNN
F 3 "" H 3450 4000 50  0001 C CNN
	1    3450 4000
	-1   0    0    1   
$EndComp
Wire Wire Line
	3450 3350 3450 3800
$EndSCHEMATC

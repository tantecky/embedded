EESchema Schematic File Version 4
EELAYER 30 0
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
L Connector:Barrel_Jack_Switch J1
U 1 1 60570E09
P 1000 1100
F 0 "J1" H 1000 1350 50  0000 C CNN
F 1 "Barrel_Jack_Switch" H 1057 1326 50  0001 C CNN
F 2 "" H 1050 1060 50  0001 C CNN
F 3 "~" H 1050 1060 50  0001 C CNN
	1    1000 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 605751F1
P 1600 1900
F 0 "R1" H 1659 1946 50  0000 L CNN
F 1 "330R" H 1659 1855 50  0000 L CNN
F 2 "" H 1600 1900 50  0001 C CNN
F 3 "~" H 1600 1900 50  0001 C CNN
	1    1600 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1100 1300 1200
Wire Wire Line
	1300 1400 1300 1200
Connection ~ 1300 1200
$Comp
L power:GND #PWR0101
U 1 1 60CEFEF2
P 1300 1400
F 0 "#PWR0101" H 1300 1150 50  0001 C CNN
F 1 "GND" H 1305 1227 50  0000 C CNN
F 2 "" H 1300 1400 50  0001 C CNN
F 3 "" H 1300 1400 50  0001 C CNN
	1    1300 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C2
U 1 1 60CF1BD2
P 1750 1100
F 0 "C2" H 1700 1350 50  0000 L CNN
F 1 "1000u" H 1750 900 50  0000 C CNN
F 2 "" H 1750 1100 50  0001 C CNN
F 3 "~" H 1750 1100 50  0001 C CNN
	1    1750 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C1
U 1 1 60CF0E52
P 1500 1100
F 0 "C1" H 1450 1350 50  0000 L CNN
F 1 "1000u" H 1500 900 50  0000 C CNN
F 2 "" H 1500 1100 50  0001 C CNN
F 3 "~" H 1500 1100 50  0001 C CNN
	1    1500 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 60CF37BB
P 2000 1100
F 0 "C3" H 1950 1350 50  0000 L CNN
F 1 "10u" H 2000 900 50  0000 C CNN
F 2 "" H 2000 1100 50  0001 C CNN
F 3 "~" H 2000 1100 50  0001 C CNN
	1    2000 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 60CF4F89
P 2200 1100
F 0 "C4" H 2150 1350 50  0000 L CNN
F 1 "10u" H 2200 900 50  0000 C CNN
F 2 "" H 2200 1100 50  0001 C CNN
F 3 "~" H 2200 1100 50  0001 C CNN
	1    2200 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1200 1500 1200
Connection ~ 1500 1200
Wire Wire Line
	1500 1200 1750 1200
Connection ~ 1750 1200
Wire Wire Line
	1750 1200 2000 1200
Connection ~ 2000 1200
Wire Wire Line
	2000 1200 2200 1200
Wire Wire Line
	2200 1000 2000 1000
Connection ~ 1500 1000
Wire Wire Line
	1500 1000 1300 1000
Connection ~ 1750 1000
Wire Wire Line
	1750 1000 1500 1000
Connection ~ 2000 1000
Wire Wire Line
	2000 1000 1750 1000
$Comp
L power:+5V #PWR0102
U 1 1 60CF8456
P 2400 1000
F 0 "#PWR0102" H 2400 850 50  0001 C CNN
F 1 "+5V" H 2400 1150 50  0000 C CNN
F 2 "" H 2400 1000 50  0001 C CNN
F 3 "" H 2400 1000 50  0001 C CNN
	1    2400 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1000 2400 1000
Connection ~ 2200 1000
$Comp
L Device:C_Small C5
U 1 1 60CFB7B9
P 6200 1250
F 0 "C5" H 6300 1250 50  0000 L CNN
F 1 "10u" H 6050 1250 50  0000 C CNN
F 2 "" H 6200 1250 50  0001 C CNN
F 3 "~" H 6200 1250 50  0001 C CNN
	1    6200 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 60CFD4EC
P 6200 1400
F 0 "#PWR0103" H 6200 1150 50  0001 C CNN
F 1 "GND" H 6205 1227 50  0000 C CNN
F 2 "" H 6200 1400 50  0001 C CNN
F 3 "" H 6200 1400 50  0001 C CNN
	1    6200 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1400 6200 1400
Wire Wire Line
	5750 1100 6200 1100
$Comp
L power:+3V3 #PWR0104
U 1 1 60D01780
P 6200 1000
F 0 "#PWR0104" H 6200 850 50  0001 C CNN
F 1 "+3V3" H 6200 1150 50  0000 C CNN
F 2 "" H 6200 1000 50  0001 C CNN
F 3 "" H 6200 1000 50  0001 C CNN
	1    6200 1000
	1    0    0    -1  
$EndComp
Connection ~ 6200 1100
Wire Wire Line
	6200 1150 6200 1100
Wire Wire Line
	6200 1350 6200 1400
Connection ~ 6200 1400
$Comp
L Device:Jumper_NC_Small JP1
U 1 1 60D0A524
P 5850 1000
F 0 "JP1" H 5850 1100 50  0000 C CNN
F 1 "Jumper_NC_Small" H 5850 1121 50  0001 C CNN
F 2 "" H 5850 1000 50  0001 C CNN
F 3 "~" H 5850 1000 50  0001 C CNN
	1    5850 1000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 60D0BA6E
P 6000 1000
F 0 "#PWR0105" H 6000 850 50  0001 C CNN
F 1 "+5V" H 6000 1150 50  0000 C CNN
F 2 "" H 6000 1000 50  0001 C CNN
F 3 "" H 6000 1000 50  0001 C CNN
	1    6000 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 1000 6000 1000
Wire Wire Line
	6200 1000 6200 1100
Wire Wire Line
	5750 1300 5750 1400
Wire Wire Line
	5750 1200 5750 1300
Connection ~ 5750 1300
Connection ~ 5750 1400
$Comp
L ESP32_mini:mini_esp32 U1
U 1 1 60573223
P 5200 900
F 0 "U1" H 5250 950 50  0000 C CNN
F 1 "mini_esp32" H 5450 -1700 50  0001 C CNN
F 2 "" H 5350 1000 50  0001 C CNN
F 3 "" H 5350 1000 50  0001 C CNN
	1    5200 900 
	1    0    0    -1  
$EndComp
$EndSCHEMATC

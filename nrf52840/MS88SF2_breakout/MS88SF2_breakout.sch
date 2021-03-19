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
NoConn ~ 3300 2500
NoConn ~ 3300 2400
$Comp
L MS88SF2:MS88SF2 U1
U 1 1 604DDC15
P 2750 1650
F 0 "U1" H 2400 2100 50  0000 C CNN
F 1 "MS88SF2" H 3050 600 50  0000 C CNN
F 2 "MS88SF2:MS88SF2" H 2150 1950 50  0001 C CNN
F 3 "" H 2150 1950 50  0001 C CNN
	1    2750 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 604E0833
P 2100 1300
F 0 "#PWR0101" H 2100 1050 50  0001 C CNN
F 1 "GND" V 2105 1172 50  0000 R CNN
F 2 "" H 2100 1300 50  0001 C CNN
F 3 "" H 2100 1300 50  0001 C CNN
	1    2100 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 1300 2150 1300
$Comp
L power:+3V3 #PWR0102
U 1 1 604E1F53
P 2050 2600
F 0 "#PWR0102" H 2050 2450 50  0001 C CNN
F 1 "+3V3" V 2065 2728 50  0000 L CNN
F 2 "" H 2050 2600 50  0001 C CNN
F 3 "" H 2050 2600 50  0001 C CNN
	1    2050 2600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2050 2600 2150 2600
$Comp
L power:GND #PWR0103
U 1 1 604E2FE3
P 2050 2500
F 0 "#PWR0103" H 2050 2250 50  0001 C CNN
F 1 "GND" V 2055 2372 50  0000 R CNN
F 2 "" H 2050 2500 50  0001 C CNN
F 3 "" H 2050 2500 50  0001 C CNN
	1    2050 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 2500 2050 2500
Text GLabel 2250 1400 0    50   Input ~ 0
P1.13
Text GLabel 2250 1500 0    50   Input ~ 0
P1.15
Text GLabel 2250 1600 0    50   Input ~ 0
P0.02
Text GLabel 2250 1700 0    50   Input ~ 0
P0.29
Text GLabel 2250 1800 0    50   Input ~ 0
P0.31
Text GLabel 2250 1900 0    50   Input ~ 0
P0.26
Text GLabel 2250 2000 0    50   Input ~ 0
P0.04
Text GLabel 2250 2100 0    50   Input ~ 0
P0.06
Text GLabel 2250 2200 0    50   Input ~ 0
P0.08
Text GLabel 2250 2300 0    50   Input ~ 0
P1.09
Text GLabel 2250 2400 0    50   Input ~ 0
P0.12
Text GLabel 3300 1300 2    50   Input ~ 0
P0.10
Text GLabel 3300 1400 2    50   Input ~ 0
P0.09
Text GLabel 3300 1500 2    50   Input ~ 0
SWCLK
Text GLabel 3300 1600 2    50   Input ~ 0
SWDIO
Text GLabel 3300 1700 2    50   Input ~ 0
P1.00
Text GLabel 3300 1800 2    50   Input ~ 0
P0.24
Text GLabel 3300 1900 2    50   Input ~ 0
P0.22
Text GLabel 3300 2000 2    50   Input ~ 0
P0.20
Text GLabel 3300 2100 2    50   Input ~ 0
P0.18
Text GLabel 3300 2200 2    50   Input ~ 0
P0.15
Text GLabel 3300 2300 2    50   Input ~ 0
P0.13
$Comp
L power:+3V3 #PWR0104
U 1 1 604E2CF1
P 3450 2600
F 0 "#PWR0104" H 3450 2450 50  0001 C CNN
F 1 "+3V3" V 3400 2700 50  0000 L CNN
F 2 "" H 3450 2600 50  0001 C CNN
F 3 "" H 3450 2600 50  0001 C CNN
	1    3450 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 2600 3450 2600
$Comp
L !mysyms:Conn_01x14_Male J2
U 1 1 604F62FB
P 6750 1950
F 0 "J2" H 7000 2700 50  0000 R CNN
F 1 "Conn_01x14_Male" H 7150 1200 50  0000 R CNN
F 2 "!myfoots:PinHeader_1x14_P2.54mm_Vertical_2row" H 6750 1950 50  0001 C CNN
F 3 "~" H 6750 1950 50  0001 C CNN
	1    6750 1950
	-1   0    0    -1  
$EndComp
NoConn ~ 6550 2650
NoConn ~ 6550 2550
NoConn ~ 6550 2450
Text GLabel 6550 1350 0    50   Input ~ 0
P0.10
$Comp
L power:GND #PWR0105
U 1 1 604FACBA
P 5650 1300
F 0 "#PWR0105" H 5650 1050 50  0001 C CNN
F 1 "GND" V 5655 1172 50  0000 R CNN
F 2 "" H 5650 1300 50  0001 C CNN
F 3 "" H 5650 1300 50  0001 C CNN
	1    5650 1300
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x14_Male J1
U 1 1 604E45A1
P 5450 1900
F 0 "J1" H 5700 2650 50  0000 C CNN
F 1 "Conn_01x14_Male" H 5550 1100 50  0000 C CNN
F 2 "!myfoots:PinHeader_1x14_P2.54mm_Vertical" H 5450 1900 50  0001 C CNN
F 3 "~" H 5450 1900 50  0001 C CNN
	1    5450 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 604FBC16
P 5650 2600
F 0 "#PWR0106" H 5650 2450 50  0001 C CNN
F 1 "+3V3" V 5650 2700 50  0000 L CNN
F 2 "" H 5650 2600 50  0001 C CNN
F 3 "" H 5650 2600 50  0001 C CNN
	1    5650 2600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 604FD03B
P 5650 2500
F 0 "#PWR0107" H 5650 2250 50  0001 C CNN
F 1 "GND" V 5655 2372 50  0000 R CNN
F 2 "" H 5650 2500 50  0001 C CNN
F 3 "" H 5650 2500 50  0001 C CNN
	1    5650 2500
	0    -1   -1   0   
$EndComp
Text GLabel 6550 1550 0    50   Input ~ 0
SWCLK
Text GLabel 6550 1650 0    50   Input ~ 0
SWDIO
Text GLabel 6550 1750 0    50   Input ~ 0
P1.00
Text GLabel 6550 1850 0    50   Input ~ 0
P0.24
Text GLabel 6550 1950 0    50   Input ~ 0
P0.22
Text GLabel 6550 2350 0    50   Input ~ 0
P0.13
Text GLabel 6550 2250 0    50   Input ~ 0
P0.15
Text GLabel 6550 2150 0    50   Input ~ 0
P0.18
Text GLabel 6550 2050 0    50   Input ~ 0
P0.20
Text GLabel 6550 1450 0    50   Input ~ 0
P0.09
Text GLabel 5650 1400 2    50   Input ~ 0
P1.13
Text GLabel 5650 1500 2    50   Input ~ 0
P1.15
Text GLabel 5650 1600 2    50   Input ~ 0
P0.02
Text GLabel 5650 1700 2    50   Input ~ 0
P0.29
Text GLabel 5650 1800 2    50   Input ~ 0
P0.31
Text GLabel 5650 1900 2    50   Input ~ 0
P0.26
Text GLabel 5650 2000 2    50   Input ~ 0
P0.04
Text GLabel 5650 2100 2    50   Input ~ 0
P0.06
Text GLabel 5650 2200 2    50   Input ~ 0
P0.08
Text GLabel 5650 2300 2    50   Input ~ 0
P1.09
Text GLabel 5650 2400 2    50   Input ~ 0
P0.12
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6050B1DE
P 2150 1300
F 0 "#FLG0101" H 2150 1375 50  0001 C CNN
F 1 "PWR_FLAG" H 2150 1473 50  0000 C CNN
F 2 "" H 2150 1300 50  0001 C CNN
F 3 "~" H 2150 1300 50  0001 C CNN
	1    2150 1300
	1    0    0    -1  
$EndComp
Connection ~ 2150 1300
Wire Wire Line
	2150 1300 2100 1300
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6050BD97
P 2150 2600
F 0 "#FLG0102" H 2150 2675 50  0001 C CNN
F 1 "PWR_FLAG" H 2150 2773 50  0000 C CNN
F 2 "" H 2150 2600 50  0001 C CNN
F 3 "~" H 2150 2600 50  0001 C CNN
	1    2150 2600
	-1   0    0    1   
$EndComp
Connection ~ 2150 2600
Wire Wire Line
	2150 2600 2250 2600
$Comp
L power:+3V3 #PWR01
U 1 1 605494B9
P 4100 1400
F 0 "#PWR01" H 4100 1250 50  0001 C CNN
F 1 "+3V3" H 3850 1550 50  0000 L CNN
F 2 "" H 4100 1400 50  0001 C CNN
F 3 "" H 4100 1400 50  0001 C CNN
	1    4100 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 6054AB55
P 4100 1500
F 0 "C1" H 4192 1546 50  0000 L CNN
F 1 "10uF" H 4192 1455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4100 1500 50  0001 C CNN
F 3 "~" H 4100 1500 50  0001 C CNN
	1    4100 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6054C5D3
P 4100 1600
F 0 "#PWR02" H 4100 1350 50  0001 C CNN
F 1 "GND" H 4050 1450 50  0000 R CNN
F 2 "" H 4100 1600 50  0001 C CNN
F 3 "" H 4100 1600 50  0001 C CNN
	1    4100 1600
	1    0    0    -1  
$EndComp
$EndSCHEMATC

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
NoConn ~ 4150 2600
NoConn ~ 4150 2500
$Comp
L MS88SF2:MS88SF2 U1
U 1 1 604DDC15
P 3600 1750
F 0 "U1" H 3250 2200 50  0000 C CNN
F 1 "MS88SF2" H 3900 700 50  0000 C CNN
F 2 "MS88SF2:MS88SF2" H 3000 2050 50  0001 C CNN
F 3 "" H 3000 2050 50  0001 C CNN
	1    3600 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 604E0833
P 2950 1400
F 0 "#PWR0101" H 2950 1150 50  0001 C CNN
F 1 "GND" V 2955 1272 50  0000 R CNN
F 2 "" H 2950 1400 50  0001 C CNN
F 3 "" H 2950 1400 50  0001 C CNN
	1    2950 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	3100 1400 3000 1400
$Comp
L power:+3V3 #PWR0102
U 1 1 604E1F53
P 2900 2700
F 0 "#PWR0102" H 2900 2550 50  0001 C CNN
F 1 "+3V3" V 2915 2828 50  0000 L CNN
F 2 "" H 2900 2700 50  0001 C CNN
F 3 "" H 2900 2700 50  0001 C CNN
	1    2900 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 2700 3000 2700
$Comp
L power:GND #PWR0103
U 1 1 604E2FE3
P 2900 2600
F 0 "#PWR0103" H 2900 2350 50  0001 C CNN
F 1 "GND" V 2905 2472 50  0000 R CNN
F 2 "" H 2900 2600 50  0001 C CNN
F 3 "" H 2900 2600 50  0001 C CNN
	1    2900 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	3100 2600 2900 2600
Text GLabel 3100 1500 0    50   Input ~ 0
P1.13
Text GLabel 3100 1600 0    50   Input ~ 0
P1.15
Text GLabel 3100 1700 0    50   Input ~ 0
P0.02
Text GLabel 3100 1800 0    50   Input ~ 0
P0.29
Text GLabel 3100 1900 0    50   Input ~ 0
P0.31
Text GLabel 3100 2000 0    50   Input ~ 0
P0.26
Text GLabel 3100 2100 0    50   Input ~ 0
P0.04
Text GLabel 3100 2200 0    50   Input ~ 0
P0.06
Text GLabel 3100 2300 0    50   Input ~ 0
P0.08
Text GLabel 3100 2400 0    50   Input ~ 0
P1.09
Text GLabel 3100 2500 0    50   Input ~ 0
P0.12
Text GLabel 4150 1400 2    50   Input ~ 0
P0.10
Text GLabel 4150 1500 2    50   Input ~ 0
P0.09
Text GLabel 4150 1600 2    50   Input ~ 0
SWCLK
Text GLabel 4150 1700 2    50   Input ~ 0
SWDIO
Text GLabel 4150 1800 2    50   Input ~ 0
P1.00
Text GLabel 4150 1900 2    50   Input ~ 0
P0.24
Text GLabel 4150 2000 2    50   Input ~ 0
P0.22
Text GLabel 4150 2100 2    50   Input ~ 0
P0.20
Text GLabel 4150 2200 2    50   Input ~ 0
P0.18
Text GLabel 4150 2300 2    50   Input ~ 0
P0.15
Text GLabel 4150 2400 2    50   Input ~ 0
P0.13
$Comp
L power:+3V3 #PWR0104
U 1 1 604E2CF1
P 4300 2700
F 0 "#PWR0104" H 4300 2550 50  0001 C CNN
F 1 "+3V3" V 4250 2800 50  0000 L CNN
F 2 "" H 4300 2700 50  0001 C CNN
F 3 "" H 4300 2700 50  0001 C CNN
	1    4300 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	4150 2700 4300 2700
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
P 3000 1400
F 0 "#FLG0101" H 3000 1475 50  0001 C CNN
F 1 "PWR_FLAG" H 3000 1573 50  0000 C CNN
F 2 "" H 3000 1400 50  0001 C CNN
F 3 "~" H 3000 1400 50  0001 C CNN
	1    3000 1400
	1    0    0    -1  
$EndComp
Connection ~ 3000 1400
Wire Wire Line
	3000 1400 2950 1400
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6050BD97
P 3000 2700
F 0 "#FLG0102" H 3000 2775 50  0001 C CNN
F 1 "PWR_FLAG" H 3000 2873 50  0000 C CNN
F 2 "" H 3000 2700 50  0001 C CNN
F 3 "~" H 3000 2700 50  0001 C CNN
	1    3000 2700
	-1   0    0    1   
$EndComp
Connection ~ 3000 2700
Wire Wire Line
	3000 2700 3100 2700
$Comp
L power:+3V3 #PWR01
U 1 1 605494B9
P 1500 2150
F 0 "#PWR01" H 1500 2000 50  0001 C CNN
F 1 "+3V3" H 1250 2300 50  0000 L CNN
F 2 "" H 1500 2150 50  0001 C CNN
F 3 "" H 1500 2150 50  0001 C CNN
	1    1500 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 6054AB55
P 1500 2300
F 0 "C1" H 1592 2346 50  0000 L CNN
F 1 "10uF" H 1592 2255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1500 2300 50  0001 C CNN
F 3 "~" H 1500 2300 50  0001 C CNN
	1    1500 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6054C5D3
P 1500 2450
F 0 "#PWR02" H 1500 2200 50  0001 C CNN
F 1 "GND" H 1450 2300 50  0000 R CNN
F 2 "" H 1500 2450 50  0001 C CNN
F 3 "" H 1500 2450 50  0001 C CNN
	1    1500 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 6073E9CF
P 1500 1550
F 0 "BT1" H 1618 1646 50  0000 L CNN
F 1 "Battery_Cell" H 1618 1555 50  0000 L CNN
F 2 "!myfoots:CR2032_holder" V 1500 1610 50  0001 C CNN
F 3 "~" V 1500 1610 50  0001 C CNN
	1    1500 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 6073F63F
P 1500 1650
F 0 "#PWR04" H 1500 1400 50  0001 C CNN
F 1 "GND" H 1450 1500 50  0000 R CNN
F 2 "" H 1500 1650 50  0001 C CNN
F 3 "" H 1500 1650 50  0001 C CNN
	1    1500 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR03
U 1 1 6073FACD
P 1500 1350
F 0 "#PWR03" H 1500 1200 50  0001 C CNN
F 1 "+3V3" H 1250 1500 50  0000 L CNN
F 2 "" H 1500 1350 50  0001 C CNN
F 3 "" H 1500 1350 50  0001 C CNN
	1    1500 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2200 1500 2150
Wire Wire Line
	1500 2400 1500 2450
$EndSCHEMATC

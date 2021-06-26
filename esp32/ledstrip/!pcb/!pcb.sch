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
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 1050 1060 50  0001 C CNN
F 3 "~" H 1050 1060 50  0001 C CNN
	1    1000 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 605751F1
P 7050 2200
F 0 "R1" V 7150 2150 50  0000 L CNN
F 1 "330R" V 6950 2100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 7050 2200 50  0001 C CNN
F 3 "~" H 7050 2200 50  0001 C CNN
	1    7050 2200
	0    -1   -1   0   
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
P 2050 1100
F 0 "C2" H 2000 1350 50  0000 L CNN
F 1 "1000u" H 2050 900 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P5.00mm" H 2050 1100 50  0001 C CNN
F 3 "~" H 2050 1100 50  0001 C CNN
	1    2050 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C1
U 1 1 60CF0E52
P 1800 1100
F 0 "C1" H 1750 1350 50  0000 L CNN
F 1 "1000u" H 1800 900 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P5.00mm" H 1800 1100 50  0001 C CNN
F 3 "~" H 1800 1100 50  0001 C CNN
	1    1800 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 60CF37BB
P 2300 1100
F 0 "C3" H 2250 1350 50  0000 L CNN
F 1 "10u" H 2300 900 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 2300 1100 50  0001 C CNN
F 3 "~" H 2300 1100 50  0001 C CNN
	1    2300 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 60CF4F89
P 2500 1100
F 0 "C4" H 2450 1350 50  0000 L CNN
F 1 "10u" H 2500 900 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 2500 1100 50  0001 C CNN
F 3 "~" H 2500 1100 50  0001 C CNN
	1    2500 1100
	1    0    0    -1  
$EndComp
Connection ~ 1800 1200
Wire Wire Line
	1800 1200 2050 1200
Connection ~ 2050 1200
Wire Wire Line
	2050 1200 2300 1200
Connection ~ 2300 1200
Wire Wire Line
	2300 1200 2500 1200
Wire Wire Line
	2500 1000 2300 1000
Connection ~ 2050 1000
Wire Wire Line
	2050 1000 1800 1000
Connection ~ 2300 1000
Wire Wire Line
	2300 1000 2050 1000
$Comp
L power:+5V #PWR0102
U 1 1 60CF8456
P 2700 1000
F 0 "#PWR0102" H 2700 850 50  0001 C CNN
F 1 "+5V" H 2700 1150 50  0000 C CNN
F 2 "" H 2700 1000 50  0001 C CNN
F 3 "" H 2700 1000 50  0001 C CNN
	1    2700 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1000 2700 1000
Connection ~ 2500 1000
$Comp
L Device:C_Small C5
U 1 1 60CFB7B9
P 6000 1250
F 0 "C5" H 6100 1250 50  0000 L CNN
F 1 "10u" H 5850 1250 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 6000 1250 50  0001 C CNN
F 3 "~" H 6000 1250 50  0001 C CNN
	1    6000 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 60CFD4EC
P 6000 1400
F 0 "#PWR0103" H 6000 1150 50  0001 C CNN
F 1 "GND" H 6005 1227 50  0000 C CNN
F 2 "" H 6000 1400 50  0001 C CNN
F 3 "" H 6000 1400 50  0001 C CNN
	1    6000 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0104
U 1 1 60D01780
P 6000 1000
F 0 "#PWR0104" H 6000 850 50  0001 C CNN
F 1 "+3V3" H 6000 1150 50  0000 C CNN
F 2 "" H 6000 1000 50  0001 C CNN
F 3 "" H 6000 1000 50  0001 C CNN
	1    6000 1000
	1    0    0    -1  
$EndComp
Connection ~ 6000 1100
Wire Wire Line
	6000 1150 6000 1100
Wire Wire Line
	6000 1350 6000 1400
Connection ~ 6000 1400
$Comp
L power:+5V #PWR0105
U 1 1 60D0BA6E
P 5800 1000
F 0 "#PWR0105" H 5800 850 50  0001 C CNN
F 1 "+5V" H 5800 1150 50  0000 C CNN
F 2 "" H 5800 1000 50  0001 C CNN
F 3 "" H 5800 1000 50  0001 C CNN
	1    5800 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1000 5800 1000
Wire Wire Line
	6000 1000 6000 1100
Wire Wire Line
	5450 1300 5450 1400
Wire Wire Line
	5450 1200 5450 1300
Connection ~ 5450 1300
$Comp
L ESP32_mini:mini_esp32 U1
U 1 1 60573223
P 4900 900
F 0 "U1" H 4950 950 50  0000 C CNN
F 1 "ESP32 MINI" H 5150 -1700 50  0000 C CNN
F 2 "ESP32_mini:ESP32_mini" H 5050 1000 50  0001 C CNN
F 3 "" H 5050 1000 50  0001 C CNN
	1    4900 900 
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR04
U 1 1 60D587F2
P 7850 1200
F 0 "#PWR04" H 7850 1050 50  0001 C CNN
F 1 "+3V3" H 7850 1350 50  0000 C CNN
F 2 "" H 7850 1200 50  0001 C CNN
F 3 "" H 7850 1200 50  0001 C CNN
	1    7850 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 1200 7850 1200
Wire Wire Line
	7000 1100 7000 850 
Wire Wire Line
	7000 850  7700 850 
Wire Wire Line
	7700 850  7700 1100
$Comp
L power:GND #PWR01
U 1 1 60D59CDE
P 6700 1100
F 0 "#PWR01" H 6700 850 50  0001 C CNN
F 1 "GND" H 6705 927 50  0000 C CNN
F 2 "" H 6700 1100 50  0001 C CNN
F 3 "" H 6700 1100 50  0001 C CNN
	1    6700 1100
	1    0    0    -1  
$EndComp
Text GLabel 7000 1200 0    50   Input ~ 0
WS
Text GLabel 7000 1300 0    50   Input ~ 0
SCK
Wire Wire Line
	6700 1100 7000 1100
Text GLabel 4400 1900 0    50   Input ~ 0
SCK
Text GLabel 4400 2000 0    50   Input ~ 0
WS
Connection ~ 7000 1100
$Comp
L _syms:INMP441 U2
U 1 1 60D57530
P 7350 550
F 0 "U2" H 7350 150 50  0000 C CNN
F 1 "INMP441" H 7450 -350 50  0000 C CNN
F 2 "_my:INMP441" H 7400 -150 50  0001 C CNN
F 3 "" H 7400 -150 50  0001 C CNN
	1    7350 550 
	1    0    0    -1  
$EndComp
Text GLabel 7700 1300 2    50   Input ~ 0
SD
Text GLabel 4400 2300 0    50   Input ~ 0
SD
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 60D5F55E
P 7450 2200
F 0 "J2" H 7530 2196 50  0000 L CNN
F 1 "Conn_01x03" H 7530 2151 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7450 2200 50  0001 C CNN
F 3 "~" H 7450 2200 50  0001 C CNN
	1    7450 2200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 60D614E5
P 7250 2100
F 0 "#PWR02" H 7250 1950 50  0001 C CNN
F 1 "+5V" H 7250 2250 50  0000 C CNN
F 2 "" H 7250 2100 50  0001 C CNN
F 3 "" H 7250 2100 50  0001 C CNN
	1    7250 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 60D61A8B
P 7250 2300
F 0 "#PWR03" H 7250 2050 50  0001 C CNN
F 1 "GND" H 7255 2127 50  0000 C CNN
F 2 "" H 7250 2300 50  0001 C CNN
F 3 "" H 7250 2300 50  0001 C CNN
	1    7250 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 2200 7250 2200
Text GLabel 6950 2200 0    50   Input ~ 0
STRIP
Text GLabel 4400 3400 0    50   Input ~ 0
STRIP
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 60D6C46F
P 6000 1100
F 0 "#FLG0102" H 6000 1175 50  0001 C CNN
F 1 "PWR_FLAG" V 6000 1228 50  0001 L CNN
F 2 "" H 6000 1100 50  0001 C CNN
F 3 "~" H 6000 1100 50  0001 C CNN
	1    6000 1100
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 60D6C917
P 6000 1400
F 0 "#FLG0103" H 6000 1475 50  0001 C CNN
F 1 "PWR_FLAG" V 6000 1528 50  0001 L CNN
F 2 "" H 6000 1400 50  0001 C CNN
F 3 "~" H 6000 1400 50  0001 C CNN
	1    6000 1400
	0    1    1    0   
$EndComp
NoConn ~ 4400 1100
NoConn ~ 4400 2800
NoConn ~ 4400 2700
NoConn ~ 4400 2600
NoConn ~ 4400 2500
NoConn ~ 4400 1000
NoConn ~ 4400 1300
$Comp
L Device:Jumper_NC_Small JP1
U 1 1 60D0A524
P 5650 1000
F 0 "JP1" H 5650 1100 50  0000 C CNN
F 1 "Jumper_NC_Small" H 5650 1121 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5650 1000 50  0001 C CNN
F 3 "~" H 5650 1000 50  0001 C CNN
	1    5650 1000
	1    0    0    -1  
$EndComp
Connection ~ 2700 1000
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 60D6B663
P 2700 1000
F 0 "#FLG0101" H 2700 1075 50  0001 C CNN
F 1 "PWR_FLAG" V 2700 1128 50  0001 L CNN
F 2 "" H 2700 1000 50  0001 C CNN
F 3 "~" H 2700 1000 50  0001 C CNN
	1    2700 1000
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 1100 6000 1100
Wire Wire Line
	5450 1400 6000 1400
Connection ~ 5450 1400
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 60D73BA1
P 5500 1000
F 0 "#FLG0104" H 5500 1075 50  0001 C CNN
F 1 "PWR_FLAG" V 5500 1128 50  0001 L CNN
F 2 "" H 5500 1000 50  0001 C CNN
F 3 "~" H 5500 1000 50  0001 C CNN
	1    5500 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1000 5500 1000
Connection ~ 5500 1000
Wire Wire Line
	5500 1000 5550 1000
NoConn ~ 5450 2600
NoConn ~ 5450 2500
NoConn ~ 5450 2400
NoConn ~ 5450 2300
NoConn ~ 5450 2200
NoConn ~ 5450 2000
NoConn ~ 5450 2100
NoConn ~ 5450 1500
Text Notes 4950 3700 0    50   ~ 0
Open JP1 before programming
NoConn ~ 4400 1200
NoConn ~ 4400 1400
NoConn ~ 4400 1500
NoConn ~ 4400 1600
NoConn ~ 4400 1700
NoConn ~ 4400 1800
NoConn ~ 4400 2100
NoConn ~ 4400 2200
NoConn ~ 4400 2400
NoConn ~ 4400 2900
NoConn ~ 4400 3000
NoConn ~ 4400 3100
NoConn ~ 4400 3200
NoConn ~ 4400 3300
$Comp
L Switch:SW_SPST SW1
U 1 1 60D7909A
P 1500 1000
F 0 "SW1" H 1500 1143 50  0000 C CNN
F 1 "SW_SPST" H 1500 1144 50  0001 C CNN
F 2 "_my:sw" H 1500 1000 50  0001 C CNN
F 3 "~" H 1500 1000 50  0001 C CNN
	1    1500 1000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 60D6F6DC
P 1150 2300
F 0 "H1" H 1250 2303 50  0000 L CNN
F 1 "MountingHole_Pad" H 1250 2258 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1150 2300 50  0001 C CNN
F 3 "~" H 1150 2300 50  0001 C CNN
	1    1150 2300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 60D6FB0D
P 1550 2300
F 0 "H3" H 1650 2303 50  0000 L CNN
F 1 "MountingHole_Pad" H 1650 2258 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1550 2300 50  0001 C CNN
F 3 "~" H 1550 2300 50  0001 C CNN
	1    1550 2300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 60D6FDCC
P 1150 2650
F 0 "H2" H 1250 2653 50  0000 L CNN
F 1 "MountingHole_Pad" H 1250 2608 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1150 2650 50  0001 C CNN
F 3 "~" H 1150 2650 50  0001 C CNN
	1    1150 2650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 60D6FF9B
P 1550 2650
F 0 "H4" H 1650 2653 50  0000 L CNN
F 1 "MountingHole_Pad" H 1650 2608 50  0001 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1550 2650 50  0001 C CNN
F 3 "~" H 1550 2650 50  0001 C CNN
	1    1550 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 60D7024C
P 1350 2800
F 0 "#PWR05" H 1350 2550 50  0001 C CNN
F 1 "GND" H 1355 2627 50  0000 C CNN
F 2 "" H 1350 2800 50  0001 C CNN
F 3 "" H 1350 2800 50  0001 C CNN
	1    1350 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 2400 1350 2400
Wire Wire Line
	1350 2400 1350 2750
Connection ~ 1350 2400
Wire Wire Line
	1350 2400 1550 2400
Wire Wire Line
	1700 1000 1800 1000
Connection ~ 1800 1000
Wire Wire Line
	1300 1200 1800 1200
Wire Wire Line
	1150 2750 1350 2750
Connection ~ 1350 2750
Wire Wire Line
	1350 2750 1350 2800
Wire Wire Line
	1350 2750 1550 2750
$EndSCHEMATC

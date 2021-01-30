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
L MCU_Module:WeMos_D1_mini U1
U 1 1 6015095A
P 2600 2300
F 0 "U1" H 1750 1450 50  0000 C CNN
F 1 "WeMos_D1_mini" H 1850 1600 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 2600 1150 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 750 1150 50  0001 C CNN
	1    2600 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 60152D8B
P 2600 3250
F 0 "#PWR0101" H 2600 3000 50  0001 C CNN
F 1 "GND" H 2605 3077 50  0000 C CNN
F 2 "" H 2600 3250 50  0001 C CNN
F 3 "" H 2600 3250 50  0001 C CNN
	1    2600 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 60157AD0
P 2400 1400
F 0 "C1" V 2300 1400 50  0000 C CNN
F 1 "10u" V 2500 1400 50  0000 C CNN
F 2 "" H 2400 1400 50  0001 C CNN
F 3 "~" H 2400 1400 50  0001 C CNN
	1    2400 1400
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 6015A97C
P 2800 1400
F 0 "C2" V 2700 1400 50  0000 C CNN
F 1 "10u" V 2900 1400 50  0000 C CNN
F 2 "" H 2800 1400 50  0001 C CNN
F 3 "~" H 2800 1400 50  0001 C CNN
	1    2800 1400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6015B61C
P 3000 1400
F 0 "#PWR0102" H 3000 1150 50  0001 C CNN
F 1 "GND" H 3005 1227 50  0000 C CNN
F 2 "" H 3000 1400 50  0001 C CNN
F 3 "" H 3000 1400 50  0001 C CNN
	1    3000 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6015C1D2
P 2200 1400
F 0 "#PWR0103" H 2200 1150 50  0001 C CNN
F 1 "GND" H 2205 1227 50  0000 C CNN
F 2 "" H 2200 1400 50  0001 C CNN
F 3 "" H 2200 1400 50  0001 C CNN
	1    2200 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1400 2300 1400
Wire Wire Line
	2500 1400 2500 1500
Wire Wire Line
	2700 1400 2700 1500
Wire Wire Line
	2900 1400 3000 1400
$Comp
L power:+3V3 #PWR0104
U 1 1 6015DE6E
P 2700 1100
F 0 "#PWR0104" H 2700 950 50  0001 C CNN
F 1 "+3V3" H 2715 1273 50  0000 C CNN
F 2 "" H 2700 1100 50  0001 C CNN
F 3 "" H 2700 1100 50  0001 C CNN
	1    2700 1100
	1    0    0    -1  
$EndComp
Connection ~ 2500 1400
$Comp
L power:+5V #PWR0105
U 1 1 6015EE3A
P 2500 1100
F 0 "#PWR0105" H 2500 950 50  0001 C CNN
F 1 "+5V" H 2515 1273 50  0000 C CNN
F 2 "" H 2500 1100 50  0001 C CNN
F 3 "" H 2500 1100 50  0001 C CNN
	1    2500 1100
	1    0    0    -1  
$EndComp
Connection ~ 2700 1400
$Comp
L !mysyms:rxb U2
U 1 1 601603AC
P 5150 2250
F 0 "U2" V 5054 2478 50  0000 L CNN
F 1 "rxb" V 5145 2478 50  0000 L CNN
F 2 "" H 5150 2100 50  0001 C CNN
F 3 "" H 5150 2100 50  0001 C CNN
	1    5150 2250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 60162F5D
P 4600 1650
F 0 "#PWR0106" H 4600 1400 50  0001 C CNN
F 1 "GND" H 4605 1477 50  0000 C CNN
F 2 "" H 4600 1650 50  0001 C CNN
F 3 "" H 4600 1650 50  0001 C CNN
	1    4600 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 60163A70
P 4600 2700
F 0 "#PWR0107" H 4600 2450 50  0001 C CNN
F 1 "GND" H 4605 2527 50  0000 C CNN
F 2 "" H 4600 2700 50  0001 C CNN
F 3 "" H 4600 2700 50  0001 C CNN
	1    4600 2700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 60164C95
P 4700 2250
F 0 "#PWR0108" H 4700 2100 50  0001 C CNN
F 1 "+5V" H 4715 2423 50  0000 C CNN
F 2 "" H 4700 2250 50  0001 C CNN
F 3 "" H 4700 2250 50  0001 C CNN
	1    4700 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1950 4900 1950
Wire Wire Line
	4900 1950 4900 2250
Wire Wire Line
	4900 2500 5000 2500
Wire Wire Line
	4900 2250 4700 2250
Connection ~ 4900 2250
Wire Wire Line
	4900 2250 4900 2500
$Comp
L !mysyms:bme280pbc U3
U 1 1 6016A9C6
P 6150 2050
F 0 "U3" V 6600 1900 50  0000 L CNN
F 1 "BME280" V 6650 2150 50  0000 L CNN
F 2 "" V 6100 2150 50  0001 C CNN
F 3 "" V 6100 2150 50  0001 C CNN
	1    6150 2050
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR0109
U 1 1 60173A7C
P 6200 1900
F 0 "#PWR0109" H 6200 1750 50  0001 C CNN
F 1 "+3V3" H 6215 2073 50  0000 C CNN
F 2 "" H 6200 1900 50  0001 C CNN
F 3 "" H 6200 1900 50  0001 C CNN
	1    6200 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 60174CC7
P 6550 2000
F 0 "#PWR0110" H 6550 1750 50  0001 C CNN
F 1 "GND" H 6555 1827 50  0000 C CNN
F 2 "" H 6550 2000 50  0001 C CNN
F 3 "" H 6550 2000 50  0001 C CNN
	1    6550 2000
	1    0    0    -1  
$EndComp
Text GLabel 3000 2500 2    50   Input ~ 0
CLK
Text GLabel 3000 2600 2    50   Input ~ 0
DIO
Text GLabel 3000 2100 2    50   Input ~ 0
SDA
Text GLabel 3000 2000 2    50   Input ~ 0
SCL
Text GLabel 6200 2100 2    50   Input ~ 0
SCL
Wire Wire Line
	6200 2000 6550 2000
Text GLabel 6200 2200 2    50   Input ~ 0
SDA
Text GLabel 5000 2800 0    50   Input ~ 0
ANT
Wire Wire Line
	4600 2600 4600 2700
Connection ~ 4600 2700
Wire Wire Line
	4600 2600 5000 2600
Wire Wire Line
	4600 2700 5000 2700
Text GLabel 3000 2400 2    50   Input ~ 0
DATA
Text GLabel 5000 1750 0    50   Input ~ 0
DATA
Wire Wire Line
	4600 1650 5000 1650
NoConn ~ 2200 2200
NoConn ~ 2200 2300
NoConn ~ 2200 1900
Text GLabel 3000 1800 2    50   Input ~ 0
A0
Text GLabel 3000 1900 2    50   Input ~ 0
D0
Text GLabel 3000 2200 2    50   Input ~ 0
D3
Text GLabel 3000 2300 2    50   Input ~ 0
D4
Text GLabel 3000 2700 2    50   Input ~ 0
D8
Wire Wire Line
	2700 1100 2700 1400
Wire Wire Line
	2500 1100 2500 1200
Wire Wire Line
	2600 3100 2600 3250
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 60179DA7
P 4000 1450
F 0 "J1" H 4080 1492 50  0000 L CNN
F 1 "Conn_01x05" H 4080 1401 50  0000 L CNN
F 2 "" H 4000 1450 50  0001 C CNN
F 3 "~" H 4000 1450 50  0001 C CNN
	1    4000 1450
	1    0    0    -1  
$EndComp
Text GLabel 3800 1250 0    50   Input ~ 0
A0
Text GLabel 3800 1350 0    50   Input ~ 0
D0
Text GLabel 3800 1450 0    50   Input ~ 0
D3
Text GLabel 3800 1550 0    50   Input ~ 0
D4
Text GLabel 3800 1650 0    50   Input ~ 0
D8
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 6017C7BC
P 4400 3350
F 0 "J2" H 4480 3392 50  0000 L CNN
F 1 "Conn_01x01" H 4480 3301 50  0000 L CNN
F 2 "" H 4400 3350 50  0001 C CNN
F 3 "~" H 4400 3350 50  0001 C CNN
	1    4400 3350
	1    0    0    -1  
$EndComp
Text GLabel 4200 3350 0    50   Input ~ 0
ANT
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6017DB92
P 2500 1200
F 0 "#FLG0101" H 2500 1275 50  0001 C CNN
F 1 "PWR_FLAG" V 2500 1327 50  0000 L CNN
F 2 "" H 2500 1200 50  0001 C CNN
F 3 "~" H 2500 1200 50  0001 C CNN
	1    2500 1200
	0    -1   -1   0   
$EndComp
Connection ~ 2500 1200
Wire Wire Line
	2500 1200 2500 1400
$EndSCHEMATC

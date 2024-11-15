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
P 1500 2100
F 0 "U1" H 850 3500 50  0000 C CNN
F 1 "WeMos_D1_mini" H 2200 1000 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 1500 950 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H -350 950 50  0001 C CNN
	1    1500 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 60152D8B
P 1500 3050
F 0 "#PWR0101" H 1500 2800 50  0001 C CNN
F 1 "GND" H 1505 2877 50  0000 C CNN
F 2 "" H 1500 3050 50  0001 C CNN
F 3 "" H 1500 3050 50  0001 C CNN
	1    1500 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 60157AD0
P 1300 1200
F 0 "C1" V 1200 1200 50  0000 C CNN
F 1 "10u" V 1400 1200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1300 1200 50  0001 C CNN
F 3 "~" H 1300 1200 50  0001 C CNN
	1    1300 1200
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 6015A97C
P 1700 1200
F 0 "C2" V 1600 1200 50  0000 C CNN
F 1 "10u" V 1800 1200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1700 1200 50  0001 C CNN
F 3 "~" H 1700 1200 50  0001 C CNN
	1    1700 1200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6015B61C
P 1900 1200
F 0 "#PWR0102" H 1900 950 50  0001 C CNN
F 1 "GND" H 1905 1027 50  0000 C CNN
F 2 "" H 1900 1200 50  0001 C CNN
F 3 "" H 1900 1200 50  0001 C CNN
	1    1900 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6015C1D2
P 1100 1200
F 0 "#PWR0103" H 1100 950 50  0001 C CNN
F 1 "GND" H 1105 1027 50  0000 C CNN
F 2 "" H 1100 1200 50  0001 C CNN
F 3 "" H 1100 1200 50  0001 C CNN
	1    1100 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1200 1200 1200
Wire Wire Line
	1400 1200 1400 1300
Wire Wire Line
	1600 1200 1600 1300
Wire Wire Line
	1800 1200 1900 1200
$Comp
L power:+3V3 #PWR0104
U 1 1 6015DE6E
P 1600 900
F 0 "#PWR0104" H 1600 750 50  0001 C CNN
F 1 "+3V3" H 1615 1073 50  0000 C CNN
F 2 "" H 1600 900 50  0001 C CNN
F 3 "" H 1600 900 50  0001 C CNN
	1    1600 900 
	1    0    0    -1  
$EndComp
Connection ~ 1400 1200
$Comp
L power:+5V #PWR0105
U 1 1 6015EE3A
P 1400 900
F 0 "#PWR0105" H 1400 750 50  0001 C CNN
F 1 "+5V" H 1415 1073 50  0000 C CNN
F 2 "" H 1400 900 50  0001 C CNN
F 3 "" H 1400 900 50  0001 C CNN
	1    1400 900 
	1    0    0    -1  
$EndComp
Connection ~ 1600 1200
$Comp
L !mysyms:rxb U2
U 1 1 601603AC
P 3500 1600
F 0 "U2" V 2600 900 50  0000 L CNN
F 1 "RXB6" V 4300 1650 50  0000 L CNN
F 2 "!myfoots:rxb" H 3500 1450 50  0001 C CNN
F 3 "" H 3500 1450 50  0001 C CNN
	1    3500 1600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 60162F5D
P 2950 1000
F 0 "#PWR0106" H 2950 750 50  0001 C CNN
F 1 "GND" H 2955 827 50  0000 C CNN
F 2 "" H 2950 1000 50  0001 C CNN
F 3 "" H 2950 1000 50  0001 C CNN
	1    2950 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 60163A70
P 2950 2050
F 0 "#PWR0107" H 2950 1800 50  0001 C CNN
F 1 "GND" H 2955 1877 50  0000 C CNN
F 2 "" H 2950 2050 50  0001 C CNN
F 3 "" H 2950 2050 50  0001 C CNN
	1    2950 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 60164C95
P 3050 1600
F 0 "#PWR0108" H 3050 1450 50  0001 C CNN
F 1 "+5V" H 3065 1773 50  0000 C CNN
F 2 "" H 3050 1600 50  0001 C CNN
F 3 "" H 3050 1600 50  0001 C CNN
	1    3050 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 1300 3250 1300
Wire Wire Line
	3250 1300 3250 1600
Wire Wire Line
	3250 1850 3350 1850
Wire Wire Line
	3250 1600 3050 1600
Connection ~ 3250 1600
Wire Wire Line
	3250 1600 3250 1850
$Comp
L !mysyms:bme280pbc U3
U 1 1 6016A9C6
P 4900 1250
F 0 "U3" V 4550 950 50  0000 L CNN
F 1 "BME280" V 5300 1450 50  0000 L CNN
F 2 "!myfoots:4pinI2C" V 4850 1350 50  0001 C CNN
F 3 "" V 4850 1350 50  0001 C CNN
	1    4900 1250
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR0109
U 1 1 60173A7C
P 4950 1100
F 0 "#PWR0109" H 4950 950 50  0001 C CNN
F 1 "+3V3" H 4965 1273 50  0000 C CNN
F 2 "" H 4950 1100 50  0001 C CNN
F 3 "" H 4950 1100 50  0001 C CNN
	1    4950 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 60174CC7
P 5300 1200
F 0 "#PWR0110" H 5300 950 50  0001 C CNN
F 1 "GND" H 5305 1027 50  0000 C CNN
F 2 "" H 5300 1200 50  0001 C CNN
F 3 "" H 5300 1200 50  0001 C CNN
	1    5300 1200
	1    0    0    -1  
$EndComp
Text GLabel 1900 2300 2    50   Input ~ 0
CLK
Text GLabel 1900 2400 2    50   Input ~ 0
DIO
Text GLabel 1900 1900 2    50   Input ~ 0
SDA
Text GLabel 1900 1800 2    50   Input ~ 0
SCL
Text GLabel 4950 1300 2    50   Input ~ 0
SCL
Wire Wire Line
	4950 1200 5300 1200
Text GLabel 4950 1400 2    50   Input ~ 0
SDA
Text GLabel 3350 2150 0    50   Input ~ 0
ANT
Wire Wire Line
	2950 1950 2950 2050
Connection ~ 2950 2050
Wire Wire Line
	2950 1950 3350 1950
Wire Wire Line
	2950 2050 3350 2050
Text GLabel 1900 2200 2    50   Input ~ 0
DATA
Text GLabel 3350 1100 0    50   Input ~ 0
DATA
Wire Wire Line
	2950 1000 3350 1000
NoConn ~ 1100 2000
NoConn ~ 1100 2100
NoConn ~ 1100 1700
Text GLabel 1900 1600 2    50   Input ~ 0
A0
Text GLabel 1900 1700 2    50   Input ~ 0
D0
Text GLabel 1900 2000 2    50   Input ~ 0
D3
Text GLabel 1900 2100 2    50   Input ~ 0
D4
Text GLabel 1900 2500 2    50   Input ~ 0
D8
Wire Wire Line
	1600 900  1600 1200
Wire Wire Line
	1400 900  1400 1000
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 60179DA7
P 1450 4200
F 0 "J1" H 1530 4242 50  0000 L CNN
F 1 "GPIO" H 1530 4151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 1450 4200 50  0001 C CNN
F 3 "~" H 1450 4200 50  0001 C CNN
	1    1450 4200
	1    0    0    -1  
$EndComp
Text GLabel 1250 4000 0    50   Input ~ 0
A0
Text GLabel 1250 4100 0    50   Input ~ 0
D0
Text GLabel 1250 4200 0    50   Input ~ 0
D3
Text GLabel 1250 4300 0    50   Input ~ 0
D4
Text GLabel 1250 4400 0    50   Input ~ 0
D8
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 6017C7BC
P 3250 2850
F 0 "J2" H 3330 2892 50  0000 L CNN
F 1 "Conn_01x01" H 3330 2801 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3250 2850 50  0001 C CNN
F 3 "~" H 3250 2850 50  0001 C CNN
	1    3250 2850
	1    0    0    -1  
$EndComp
Text GLabel 3050 2850 0    50   Input ~ 0
ANT
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6017DB92
P 1400 1000
F 0 "#FLG0101" H 1400 1075 50  0001 C CNN
F 1 "PWR_FLAG" V 1400 1127 50  0000 L CNN
F 2 "" H 1400 1000 50  0001 C CNN
F 3 "~" H 1400 1000 50  0001 C CNN
	1    1400 1000
	0    -1   -1   0   
$EndComp
Connection ~ 1400 1000
Wire Wire Line
	1400 1000 1400 1200
$Comp
L !mysyms:oled U4
U 1 1 6015EBC4
P 6200 1250
F 0 "U4" V 5800 950 50  0000 C CNN
F 1 "OLED" V 6650 1650 50  0000 C CNN
F 2 "!myfoots:4pinI2C" V 6150 1350 50  0001 C CNN
F 3 "" V 6150 1350 50  0001 C CNN
	1    6200 1250
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR01
U 1 1 6015F7B7
P 6250 1100
F 0 "#PWR01" H 6250 950 50  0001 C CNN
F 1 "+3V3" H 6265 1273 50  0000 C CNN
F 2 "" H 6250 1100 50  0001 C CNN
F 3 "" H 6250 1100 50  0001 C CNN
	1    6250 1100
	1    0    0    -1  
$EndComp
Text GLabel 6250 1300 2    50   Input ~ 0
SCL
Text GLabel 6250 1400 2    50   Input ~ 0
SDA
$Comp
L power:GND #PWR02
U 1 1 60160948
P 6600 1200
F 0 "#PWR02" H 6600 950 50  0001 C CNN
F 1 "GND" H 6605 1027 50  0000 C CNN
F 2 "" H 6600 1200 50  0001 C CNN
F 3 "" H 6600 1200 50  0001 C CNN
	1    6600 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1200 6250 1200
Wire Wire Line
	1500 2900 1500 2950
$Comp
L !mysyms:led U5
U 1 1 60163EA9
P 4800 2750
F 0 "U5" V 4425 2598 50  0000 C CNN
F 1 "LED" V 5200 3150 50  0000 C CNN
F 2 "!myfoots:4pinTM1637" V 4750 2850 50  0001 C CNN
F 3 "" V 4750 2850 50  0001 C CNN
	1    4800 2750
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR04
U 1 1 601661B6
P 4850 2600
F 0 "#PWR04" H 4850 2450 50  0001 C CNN
F 1 "+3V3" H 4865 2773 50  0000 C CNN
F 2 "" H 4850 2600 50  0001 C CNN
F 3 "" H 4850 2600 50  0001 C CNN
	1    4850 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 60166F3C
P 5150 2700
F 0 "#PWR05" H 5150 2450 50  0001 C CNN
F 1 "GND" H 5155 2527 50  0000 C CNN
F 2 "" H 5150 2700 50  0001 C CNN
F 3 "" H 5150 2700 50  0001 C CNN
	1    5150 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2700 5150 2700
Text GLabel 4850 2900 2    50   Input ~ 0
CLK
Text GLabel 4850 2800 2    50   Input ~ 0
DIO
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 6016876C
P 3100 4200
F 0 "J3" H 3180 4242 50  0000 L CNN
F 1 "Conn_01x01" H 3180 4151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3100 4200 50  0001 C CNN
F 3 "~" H 3100 4200 50  0001 C CNN
	1    3100 4200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 6016910D
P 2900 4200
F 0 "#PWR03" H 2900 4050 50  0001 C CNN
F 1 "+5V" H 2915 4373 50  0000 C CNN
F 2 "" H 2900 4200 50  0001 C CNN
F 3 "" H 2900 4200 50  0001 C CNN
	1    2900 4200
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6016A863
P 1500 2950
F 0 "#FLG0102" H 1500 3025 50  0001 C CNN
F 1 "PWR_FLAG" V 1500 3077 50  0000 L CNN
F 2 "" H 1500 2950 50  0001 C CNN
F 3 "~" H 1500 2950 50  0001 C CNN
	1    1500 2950
	0    -1   -1   0   
$EndComp
Connection ~ 1500 2950
Wire Wire Line
	1500 2950 1500 3050
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 60169893
P 4600 4100
F 0 "H1" H 4700 4103 50  0000 L CNN
F 1 "MountingHole_Pad" H 4700 4058 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 4600 4100 50  0001 C CNN
F 3 "~" H 4600 4100 50  0001 C CNN
	1    4600 4100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 6016A8E6
P 5100 4100
F 0 "H3" H 5200 4103 50  0000 L CNN
F 1 "MountingHole_Pad" H 5200 4058 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 5100 4100 50  0001 C CNN
F 3 "~" H 5100 4100 50  0001 C CNN
	1    5100 4100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 6016ADFE
P 4600 4550
F 0 "H2" H 4700 4553 50  0000 L CNN
F 1 "MountingHole_Pad" H 4700 4508 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 4600 4550 50  0001 C CNN
F 3 "~" H 4600 4550 50  0001 C CNN
	1    4600 4550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 6016B18D
P 5100 4550
F 0 "H4" H 5200 4553 50  0000 L CNN
F 1 "MountingHole_Pad" H 5200 4508 50  0001 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 5100 4550 50  0001 C CNN
F 3 "~" H 5100 4550 50  0001 C CNN
	1    5100 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 4200 4850 4200
Wire Wire Line
	4850 4200 4850 4650
Wire Wire Line
	4850 4650 5100 4650
Connection ~ 4850 4200
Wire Wire Line
	4850 4200 5100 4200
Wire Wire Line
	4600 4650 4850 4650
Connection ~ 4850 4650
$Comp
L power:GND #PWR06
U 1 1 6016C9D5
P 4850 4650
F 0 "#PWR06" H 4850 4400 50  0001 C CNN
F 1 "GND" H 4855 4477 50  0000 C CNN
F 2 "" H 4850 4650 50  0001 C CNN
F 3 "" H 4850 4650 50  0001 C CNN
	1    4850 4650
	1    0    0    -1  
$EndComp
$Comp
L !mysyms:bme280pbc U6
U 1 1 6017FC57
P 7600 1200
F 0 "U6" V 7250 900 50  0000 L CNN
F 1 "SPARE" V 8000 1400 50  0000 L CNN
F 2 "!myfoots:4pinI2C" V 7550 1300 50  0001 C CNN
F 3 "" V 7550 1300 50  0001 C CNN
	1    7600 1200
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR07
U 1 1 6017FC5D
P 7650 1050
F 0 "#PWR07" H 7650 900 50  0001 C CNN
F 1 "+3V3" H 7665 1223 50  0000 C CNN
F 2 "" H 7650 1050 50  0001 C CNN
F 3 "" H 7650 1050 50  0001 C CNN
	1    7650 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 6017FC63
P 8000 1150
F 0 "#PWR08" H 8000 900 50  0001 C CNN
F 1 "GND" H 8005 977 50  0000 C CNN
F 2 "" H 8000 1150 50  0001 C CNN
F 3 "" H 8000 1150 50  0001 C CNN
	1    8000 1150
	1    0    0    -1  
$EndComp
Text GLabel 7650 1250 2    50   Input ~ 0
SCL
Wire Wire Line
	7650 1150 8000 1150
Text GLabel 7650 1350 2    50   Input ~ 0
SDA
Wire Wire Line
	2900 4300 2900 4200
Connection ~ 2900 4200
$Comp
L !mysyms:bme280pbc U7
U 1 1 60193573
P 8800 1200
F 0 "U7" V 8450 900 50  0000 L CNN
F 1 "SPARE2" V 9200 1400 50  0000 L CNN
F 2 "!myfoots:4pinI2C" V 8750 1300 50  0001 C CNN
F 3 "" V 8750 1300 50  0001 C CNN
	1    8800 1200
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR09
U 1 1 601937DF
P 8850 1050
F 0 "#PWR09" H 8850 900 50  0001 C CNN
F 1 "+3V3" H 8865 1223 50  0000 C CNN
F 2 "" H 8850 1050 50  0001 C CNN
F 3 "" H 8850 1050 50  0001 C CNN
	1    8850 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 601937E9
P 9200 1150
F 0 "#PWR010" H 9200 900 50  0001 C CNN
F 1 "GND" H 9205 977 50  0000 C CNN
F 2 "" H 9200 1150 50  0001 C CNN
F 3 "" H 9200 1150 50  0001 C CNN
	1    9200 1150
	1    0    0    -1  
$EndComp
Text GLabel 8850 1250 2    50   Input ~ 0
SCL
Wire Wire Line
	8850 1150 9200 1150
Text GLabel 8850 1350 2    50   Input ~ 0
SDA
$EndSCHEMATC

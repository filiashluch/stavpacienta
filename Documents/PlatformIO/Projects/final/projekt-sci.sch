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
L Sensor:DHT11 U?
U 1 1 6004A9AA
P 5550 3650
F 0 "U?" H 5306 3696 50  0000 R CNN
F 1 "DHT11" H 5306 3605 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 5550 3250 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 5700 3900 50  0001 C CNN
	1    5550 3650
	1    0    0    -1  
$EndComp
$Comp
L eec:MAX30100 U?
U 1 1 6004BF3F
P 6100 1600
F 0 "U?" H 6600 1865 50  0000 C CNN
F 1 "MAX30100" H 6600 1774 50  0000 C CNN
F 2 "Maxim_Integrated-90-0461-0-0-*" H 6100 2000 50  0001 L CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX30100.pdf" H 6100 2100 50  0001 L CNN
F 4 "IC" H 6100 2200 50  0001 L CNN "category"
F 5 "" H 6100 2300 50  0001 L CNN "digikey description"
F 6 "" H 6100 2400 50  0001 L CNN "digikey part number"
F 7 "Yes" H 6100 2500 50  0001 L CNN "lead free"
F 8 "dab0caa6bd171e03" H 6100 2600 50  0001 L CNN "library id"
F 9 "Maxim Integrated" H 6100 2700 50  0001 L CNN "manufacturer"
F 10 "" H 6100 2800 50  0001 L CNN "mouser part number"
F 11 "SMT_MAX30100" H 6100 2900 50  0001 L CNN "package"
F 12 "Yes" H 6100 3000 50  0001 L CNN "rohs"
F 13 "" H 6100 3100 50  0001 L CNN "temperature range high"
F 14 "" H 6100 3200 50  0001 L CNN "temperature range low"
	1    6100 1600
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Temperature:DS18B20 U?
U 1 1 6004DCAB
P 8050 5450
F 0 "U?" H 7820 5496 50  0000 R CNN
F 1 "DS18B20" H 7820 5405 50  0000 R CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 7050 5200 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 7900 5700 50  0001 C CNN
	1    8050 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 3700 5850 3650
Wire Wire Line
	5550 1800 5550 3350
Wire Wire Line
	6100 1600 3200 1600
Wire Wire Line
	3200 1600 3200 1800
Wire Wire Line
	7100 2600 7100 2700
$Comp
L Device:R R?
U 1 1 6005622C
P 7500 1800
F 0 "R?" V 7293 1800 50  0000 C CNN
F 1 "4.7K R" V 7384 1800 50  0000 C CNN
F 2 "" V 7430 1800 50  0001 C CNN
F 3 "~" H 7500 1800 50  0001 C CNN
	1    7500 1800
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 6005643A
P 7500 1900
F 0 "R?" V 7293 1900 50  0000 C CNN
F 1 "4.7K R" V 7384 1900 50  0000 C CNN
F 2 "" V 7430 1900 50  0001 C CNN
F 3 "~" H 7500 1900 50  0001 C CNN
	1    7500 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 1900 7350 1900
Wire Wire Line
	5550 1800 6100 1800
Connection ~ 6100 1800
Wire Wire Line
	6100 1800 7100 1800
Connection ~ 7100 1800
Wire Wire Line
	7100 1800 7350 1800
Connection ~ 3800 3400
Wire Wire Line
	3800 3400 3800 3500
Wire Wire Line
	7650 1900 7650 3400
$Comp
L Device:LED D?
U 1 1 6004EA2C
P 2300 5000
F 0 "D?" H 2293 5217 50  0000 C CNN
F 1 "GREEN LED" H 2293 5126 50  0000 C CNN
F 2 "" H 2300 5000 50  0001 C CNN
F 3 "~" H 2300 5000 50  0001 C CNN
	1    2300 5000
	1    0    0    -1  
$EndComp
Connection ~ 7100 2700
Wire Wire Line
	7100 2700 7100 4600
Wire Wire Line
	5550 4600 7100 4600
Connection ~ 5550 4600
Wire Wire Line
	5550 4600 5550 3950
$Comp
L Device:LED D?
U 1 1 6004F50F
P 2300 5300
F 0 "D?" H 2293 5517 50  0000 C CNN
F 1 "RED LED" H 2293 5426 50  0000 C CNN
F 2 "" H 2300 5300 50  0001 C CNN
F 3 "~" H 2300 5300 50  0001 C CNN
	1    2300 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3700 5850 3700
Wire Wire Line
	7650 3400 3800 3400
Wire Wire Line
	3200 4600 5550 4600
Wire Wire Line
	3800 4100 3800 4000
Wire Wire Line
	3100 1800 3200 1800
Connection ~ 5550 1800
Connection ~ 3200 1800
Connection ~ 3800 1800
Wire Wire Line
	3800 1800 5550 1800
Wire Wire Line
	3200 1800 3800 1800
Wire Wire Line
	2450 5300 2700 5300
Wire Wire Line
	2450 5000 2700 5000
$Comp
L Device:R R?
U 1 1 60051D10
P 2850 5300
F 0 "R?" V 2643 5300 50  0000 C CNN
F 1 "330R" V 2734 5300 50  0000 C CNN
F 2 "" V 2780 5300 50  0001 C CNN
F 3 "~" H 2850 5300 50  0001 C CNN
	1    2850 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 1800 3800 2100
Connection ~ 3800 3300
Wire Wire Line
	3800 3300 3800 3400
Connection ~ 3800 3200
Connection ~ 3800 3100
Wire Wire Line
	3800 3200 3800 3300
Wire Wire Line
	3800 3100 3800 3200
Connection ~ 3800 3000
Connection ~ 3800 2900
Wire Wire Line
	3800 3000 3800 3100
Wire Wire Line
	3800 2900 3800 3000
Connection ~ 3800 2800
Connection ~ 3800 2700
Wire Wire Line
	3800 2800 3800 2900
Wire Wire Line
	3800 2700 3800 2800
Connection ~ 3800 2600
Connection ~ 3800 2500
Wire Wire Line
	3800 2600 3800 2700
Wire Wire Line
	3800 2500 3800 2600
Connection ~ 3800 2400
Connection ~ 3800 2300
Wire Wire Line
	3800 2400 3800 2500
Wire Wire Line
	3800 2300 3800 2400
Connection ~ 3800 2200
Connection ~ 3800 2100
Wire Wire Line
	3800 2200 3800 2300
Wire Wire Line
	3800 2100 3800 2200
Connection ~ 3800 4100
$Comp
L esp32_devkit_v1_doit:ESP32_DevKit_V1_DOIT U?
U 1 1 60047E85
P 3200 3200
F 0 "U?" H 3200 4781 50  0000 C CNN
F 1 "ESP32_DevKit_V1_DOIT" H 3200 4690 50  0000 C CNN
F 2 "ESP32_DevKit_V1_DOIT:esp32_devkit_v1_doit" H 2750 4550 50  0001 C CNN
F 3 "https://aliexpress.com/item/32864722159.html" H 2750 4550 50  0001 C CNN
	1    3200 3200
	1    0    0    -1  
$EndComp
Connection ~ 3800 4200
Wire Wire Line
	3800 4200 3800 4100
Wire Wire Line
	3800 4300 3800 4200
$Comp
L Device:R R?
U 1 1 60050A09
P 2850 5000
F 0 "R?" V 2643 5000 50  0000 C CNN
F 1 "330R" V 2734 5000 50  0000 C CNN
F 2 "" V 2780 5000 50  0001 C CNN
F 3 "~" H 2850 5000 50  0001 C CNN
	1    2850 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 5000 3100 5000
Wire Wire Line
	3000 5300 3100 5300
Wire Wire Line
	3100 4600 3100 5000
Connection ~ 3100 5000
Wire Wire Line
	3100 5000 3100 5300
Wire Wire Line
	2150 5000 1800 5000
Wire Wire Line
	1800 5000 1800 5650
Wire Wire Line
	1800 5650 4050 5650
Wire Wire Line
	4050 5650 4050 4000
Wire Wire Line
	4050 4000 3800 4000
Connection ~ 3800 4000
Wire Wire Line
	2150 5300 1950 5300
Wire Wire Line
	1950 5300 1950 5500
Wire Wire Line
	1950 5500 3950 5500
Wire Wire Line
	3950 5500 3950 4100
Wire Wire Line
	3950 4100 3800 4100
$Comp
L Device:R R?
U 1 1 60093C4E
P 8050 4800
F 0 "R?" H 7980 4754 50  0000 R CNN
F 1 "4.7K R" H 7980 4845 50  0000 R CNN
F 2 "" V 7980 4800 50  0001 C CNN
F 3 "~" H 8050 4800 50  0001 C CNN
	1    8050 4800
	-1   0    0    1   
$EndComp
Wire Wire Line
	8050 5150 8050 4950
Wire Wire Line
	8050 4650 8050 1200
Wire Wire Line
	8050 1200 3200 1200
Wire Wire Line
	3200 1200 3200 1600
Connection ~ 3200 1600
Wire Wire Line
	8050 5750 4500 5750
Wire Wire Line
	4500 5750 4500 2200
Wire Wire Line
	4500 2200 3800 2200
Wire Wire Line
	8350 5450 8350 6000
Wire Wire Line
	8350 6000 3200 6000
Wire Wire Line
	3200 6000 3200 4600
Connection ~ 3200 4600
$EndSCHEMATC

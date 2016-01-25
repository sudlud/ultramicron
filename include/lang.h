#ifndef __lang_H
#define __lang_H

#ifndef LANG_EN
///////////////////////////////////////////////////////
// Menu
#define LANG_ALARM     "�������"
#define LANG_SLEEP     "���"
#define LANG_SOUND     "����"
#define LANG_VIBRO     "�����"
#define LANG_USBMODE   "����� USB"
#define LANG_CLEARDO   "����� ����"
#define LANG_REBOOT    "�������/����"
#define LANG_CONTRAST  "��������"
#define LANG_REVERSE   "������"
#define LANG_COUNT     "����"
#define LANG_VOLTAGE   "����������"
#define LANG_OFF       "����"
#define LANG_KEY       "����"
#define LANG_QUARTZ    "�����"
#define LANG_ON        "���"
#define LANG_ALARM2    "����"
#define LANG_USEC      "%u���"
#define LANG_UMKR      "%u���"
#define LANG_UMKZV     "%4.2f���"
#define LANG_UHZ       "%u ��"
#define LANG_UV        "%uB"
#define LANG_V4PUMP    "�������"
#define LANG_UV4PUMP   "%u���"
#define LANG_UNITS     "�������"
#define LANG_BWINDOW   "����"
#define LANG_BWINDOW_  "%2.1fD��"
#define LANG_BPROCENT  "B-����."
#define LANG_BPROCENT_ "%3u"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Dose
#define LANG_TIME 	    "�����"
#define LANG_DATE 	    "����"
#define LANG_MAXFON     "�������� ����"
#define LANG_DOSE10M    "���� �� 10���"
#define LANG_DOSEHOUR   "���� �� ���"
#define LANG_DOSE24H    "���� �� �����"
#define LANG_DOSEWEEK   "���� �� ������"
#define LANG_DOSEMONTH  "���� �� �����"
#define LANG_DOSE2MONTH "���� 2 ������"
#define LANG_DOSECALC   "  *������*   "
#define LANG_DOSECALCZV "  *������*   "
#define LANG_9UMKR      "%9u ���"
#define LANG_9UMKZV     "%8.2f ����"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Screen
#define LANG_MENU     "      ����      "
#define LANG_STAT     "   ����������   "
#define LANG_AKB3VVV  "���  |+3�  |��"
#define LANG_PUMP     "�������"
#define LANG_IMPMINAR "���/� | �������."
#define LANG_CALC2    "������"
#define LANG_4IDN     "%4i��."

#define LANG_DALL     "�����  %5i"
#define LANG_DIMP     "���.   %5i"
#define LANG_DTIME    "����� %6i"
#define LANG_DSENS    "������ %5i"

#define LANG_ABOUT    "  � ���������   "
#define LANG_DOZIK    "  ������-������ "
#define LANG_AUTHOR   "   (c)Shodan    "
#define LANG_CITY     " �.���� 2014-16�"
#define LANG_SITE     " �����������.net"
#define LANG_BUILD    " ��������:"
///////////////////////////////////////////////////////

#define LANG_POWEROFF " ����������.... "

#define LANG_REBOOTPR "������������...."
#define LANG_DONTOTO1 "   �� �������   "
#define LANG_DONTOTO2 "   �� ��������! "
#define LANG_USBON    "USB �����������"
#define LANG_USBOFF   "USB  ��������"

#define LANG_UR       "���"
#define LANG_UZ       "���"
#define LANG_UZV      "����"
#define LANG_H        " � "
///////////////////////////////////////////////////////

#else

///////////////////////////////////////////////////////
// Menu
#define LANG_ALARM    "Alarm"
#define LANG_SLEEP    "Sleep"
#define LANG_SOUND    "Sound"
#define LANG_VIBRO    "Vibro"
#define LANG_USBMODE  "USB state"
#define LANG_CLEARDO  "Clr dose"
#define LANG_REBOOT   "Reboot/off"
#define LANG_CONTRAST "Contrast"
#define LANG_REVERSE  "Reverse"
#define LANG_COUNT    "Count"
#define LANG_VOLTAGE  "Voltage"
#define LANG_ON       "on"
#define LANG_OFF      "off"
#define LANG_KEY      "key"
#define LANG_QUARTZ   "Quarz"
#define LANG_ALARM2   "alrm"
#define LANG_USEC     "%usec"
#define LANG_UMKR     "%uuRh"
#define LANG_UMKZV    "%4.2fusV"
#define LANG_UHZ      "%u Hz"
#define LANG_UV       "%uV"
#define LANG_V4PUMP   "Pump"
#define LANG_UV4PUMP  "%uT"
#define LANG_UNITS    "Units"
#define LANG_BWINDOW  "Window"
#define LANG_BWINDOW_ "%2.1fDmm"
#define LANG_BPROCENT "B-proc."
#define LANG_BPROCENT_ "%9u%%"

///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Dose
#define LANG_TIME 	    "Time"
#define LANG_DATE 	    "Date"
#define LANG_MAXFON     "Radiation max"
#define LANG_DOSE10M    "10 min dose"
#define LANG_DOSEHOUR   "Hour dose"
#define LANG_DOSE24H    "Day dose"
#define LANG_DOSEWEEK   "Week dose"
#define LANG_DOSE2MONTH "2 Month dose"
#define LANG_DOSEMONTH  "Month dose"
#define LANG_DOSECALC   " *CALC*     "
#define LANG_DOSECALCSV " *CALC*     "
#define LANG_9UMKR      "%9u uR"
#define LANG_9UMKZV     "%8.2f uSv"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Screen
#define LANG_MENU     "      Menu      "
#define LANG_STAT     "   Statistic    "
#define LANG_ABOUT    "      About     "

#define LANG_AKB3VVV  "BAT  |+3V  |HV"
#define LANG_PUMP     "Pump  "
#define LANG_IMPMINAR "imp/m | uptime  "
#define LANG_CALC2    "calc  "
#define LANG_4IDN     "%4iday"

#define LANG_DALL     "All    %5i"
#define LANG_DIMP     "Imp.   %5i"
#define LANG_DTIME    "Time  %6i"
#define LANG_DSENS    "Sensor %5i"

#define LANG_DOZIK    "  Ultra-Micron  "
#define LANG_AUTHOR   " (c)Shodan,Tula "
#define LANG_CITY     " Russia 2014-16 "
#define LANG_SITE     "xn--h1aeegel.net"
#define LANG_BUILD    " FW Build:"
///////////////////////////////////////////////////////

#define LANG_POWEROFF "Power off...... "

#define LANG_REBOOTPR "Rebooting......."
#define LANG_DONTOTO1 "  DO NOT TOUCH  "
#define LANG_DONTOTO2 "  ANY KEYS!!!   "
#define LANG_USBON    "USB enabled"
#define LANG_USBOFF   "USB disabled"

#define LANG_UR       "uR"
#define LANG_UZ       "uSv"
#define LANG_UZV      "uSv"
#define LANG_H        " h "
///////////////////////////////////////////////////////


#endif
#endif

#include <stdio.h>
#include <string.h>
#include "main.h"
	
MenuItem Menu_list[max_struct_index] = {
  
  //������   �����          ���� �������� 0   ���� 1          ���� ������ ��� 1  ������ ����� ���� ��������                             �������  ��������  ������   ������� �� ����������     �� ���������� 
  {  0x00, LANG_ALARM,	    LANG_OFF,					"",		          LANG_UMKR,	   &Settings.Alarm_level,                                  0,       10000,    60,      &plus_alarm,              &minus_alarm},
  {  0x00, LANG_SLEEP,		  LANG_OFF,					"",			        LANG_USEC,	   &Settings.Sleep_time,                                   10,      10240,    40,      &plus_sleep,              &minus_sleep},
  {  0x00, LANG_SOUND,      LANG_OFF,					LANG_ON,	      LANG_KEY,	     &Settings.Sound,                                        0,       2,        0,       &plus_one,                &minus_one},
#ifdef version_401
	{  0x00, LANG_VIBRO,      LANG_OFF,    		  LANG_ON, 		    LANG_ALARM2,   &Settings.Vibro,                                        0,       2,        0x00,    &plus_one,                &minus_one},
#else
	{  0x00, LANG_USBMODE,    LANG_OFF,    		  LANG_ON, 		    "",      		   &Settings.USB,                                          0x00,    0x00,     0x00,    &usb_activate,            &usb_deactivate},
#endif
  {  0x00, LANG_CLEARDO,    "*",   						"*",		        "*",	         0x00,                                                   0x00,    0x00,     0x00,    &plus_doze_reset,         0x00},
  {  0x00, LANG_REBOOT,     "*",   						"*",		        "*",	         0x00,                                                   0x00,    0x00,     0x00,    &plus_reboot,             &minus_poweroff},
	{  0x00, LANG_UNITS,      LANG_UR,    		  LANG_UZV, 	    "",      		   &Settings.units,                                        0x00,    0x01,     0x00,    &plus_one, 		           &minus_one},
  {  0x01, LANG_CONTRAST,   "",		  					"",			        "%u",  	       &Settings.contrast,                                     0,       15,       0,       &plus_one,                &minus_one},
  {  0x01, LANG_REVERSE,    LANG_OFF,					"",			        "%u",	         &Settings.Display_reverse,                              0,       3,        0,       &plus_one,                &minus_one},
  {  0x01, LANG_COUNT,      "",		  					"",			        LANG_USEC,	   &Settings.Second_count,                                 200,     1450,     250,     &plus_ten,                &minus_ten},
	{  0x01, "LSI",		        LANG_QUARTZ,			"",			        LANG_UHZ,	     &Settings.LSI_freq,                            	       26000,   56000,    38000,   &plus_500,                &minus_500},
	{  0x01, LANG_V4PUMP,     "",								"",			        LANG_UV4PUMP,  &Settings.v4_target_pump,                       	       4,       14,       11,      &plus_one,                &minus_one},
	{  0x01, LANG_VOLTAGE,	  "",		  					"",			        LANG_UV,	     &Settings.Geiger_voltage,                               300,     450,      380,     &plus_ten,                &minus_ten},
// �������� �� ���� ����		if(menu_struct_index == 13) ! ��������� � ���� ��� ��������� ������� ������� ����!
	{  0x01, LANG_BWINDOW,    "",								"",			        LANG_BWINDOW_, &Settings.Beta_window,                       	         1,       100,       20,     &plus_one,                &minus_one},
	{  0x01, LANG_BPROCENT,   "",								"",			        LANG_BPROCENT_,&Settings.Beta_procent,                       	         1,       100,       37,     &plus_one,                &minus_one}
	/*	{  0x01, "��������",	    "",		  						"",			        	"%u���",	     &Settings.Pump_Energy,                                  150,     450,      250,     &plus_50,                 &minus_50},
  {  0x00, "���������",		  "����",							"",			        	"%u���",	     &Settings.Led_Sleep_time,                               0,       300,      30,      &plus_sleep,              &minus_sleep},
  {  0x01, "����",	        "",		  						"",			        	"%u���",	     &Settings.Sound_freq,                                   1,       10,       8,       &plus_one,                &minus_one}
  {  0x01, "�����������",	  "���",  						"����",		       	"",	           &Settings.Power_comp,                                   0,       1,        0,       &plus_one,                &minus_one}
  {  0x01, "���",	    		  "%u",		  					"%u",			       	"%u",			     &RTC_Time.Hour,                        						     0,       23,       0,       &plus_one,                &minus_one},
  {  0x01, "������",	 		  "%u",								"%u",			       	"%u",		  	   &RTC_Time.Minute,                     								   0,       59,       0,       &plus_one,                &minus_one},
  {  0x01, "�������",	      "%u",								"%u",			       	"%u",		    	 &RTC_Time.Second,                              				 0,       59,       0,       &plus_one,                &minus_one},
  {  0x01, "����",	   		  "%u",		  					"%u",			       	"%u",			     &RTC_Time.Day,                          							   1,       31,       0,       &plus_one,                &minus_one},
  {  0x01, "�����",	 			  "%u",								"%u",			       	"%u",		  	   &RTC_Time.Month,                          							 1,       12,       0,       &plus_one,                &minus_one},
  {  0x01, "���",	   		  	"%u",								"%u",			       	"%u",		    	 &RTC_Time.Year,                            			       2014,    2050,     0,       &plus_one,                &minus_one}
  {  0x01, "����. ��/x",	  "",									"",			        	".%01u%%",	   &Settings.Geiger_angle_of_counter_characteristics,      1,       9,        5,       &plus_one,                &minus_one},
  {  0x01, "����. ��",	    "",									"",			        	"%u%%",	       &Settings.HV_ADC_Corr,                                  1,       99,       42,      &plus_one,                &minus_one},
  {  0x01, "�� ���/����",	  "",									"",			        	"%u���",	     &Settings.pump_pulse_by_impulse,                        1,       40,       5,       &plus_one,                &minus_one},
  {  0x00, "����������",    "*",		  					"*",		        	"*",	         0x00,                                                   0x00,    0x00,     0x00,    &plus_poweroff,           0x00},
  {  0x01, "�� �����.",	    "",									"",			        	"%u",	         &Settings.pump_skvagennost,                             1,       50,       8,       &plus_one,                &minus_one}
*/
};
//////////////////////////////////////////////////////////////////////////////////////////////////



void main_screen()
{
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;

  
  uint32_t battery_procent, i=0,x=0;
   
  //������ �������� ��������� 3.5� = 0% 4.0� = 100%
  battery_procent=ADCData.Batt_voltage;
  battery_procent-=3500;
  battery_procent/=5;
  if(ADCData.Batt_voltage<3500){LcdBatt(82, 19, 82+10, 19+19, 0);}//������ ���������ADCData.Batt_voltage
  else LcdBatt(84, 19, 84+10, 19+19, battery_procent);//������ ���������ADCData.Batt_voltage

  if (main_menu_stat>8)main_menu_stat=1;
  if (main_menu_stat<1)main_menu_stat=8;

  if(DataUpdate.Need_update_mainscreen_counters==ENABLE) // ���� ��������� ���������� ���������
  {
		DataUpdate.Need_update_mainscreen_counters=DISABLE;
		Max_fon=0;
		Doze_day_count=0;
		Doze_week_count=0;
		Doze_month_count=0;
		Doze_hour_count=0;		
		Doze_2month_count=0;
		
		for(i=doze_length_2month;i>0;i--)		
		{
			if(i<doze_length_hour ) Doze_hour_count+= flash_read_massive(i,dose_select);    // ������ ��������� ����
			if(i<doze_length_day  ) Doze_day_count+=  flash_read_massive(i,dose_select);// ������ ������� ����
			if(i<doze_length_week ){Doze_week_count+= flash_read_massive(i,dose_select);// ������ ��������� ����
															x=flash_read_massive(i,max_fon_select);
															if(x>Max_fon)Max_fon=x;                      // ������ ������������� ����
														 }
			if(licensed==ENABLE)
			{
				if(i<doze_length_month) Doze_month_count+= flash_read_massive(i,dose_select);// ������ �������� ����
				if(i<doze_length_2month)Doze_2month_count+=flash_read_massive(i,dose_select);// ������ �������� ����
			}
		}
	}

  switch (main_menu_stat)
	{
		case 0x01:
			sprintf (lcd_buf, LANG_TIME); // ����� � ����� �������� ��������
			LcdString(1,4); // // ������� ������� ������� ���������� ������
			sprintf (lcd_buf, LANG_DATE); // ����� � ����� �������� ��������
			LcdString(1,5); // // ������� ������� ������� ���������� ������
		
			RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
			RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);

			sprintf(lcd_buf,"%0.2d.%0.2d.%0.2d", RTC_DateStructure.RTC_Date, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Year);
			LcdString(7,5); // // ������� ������� ������� ���������� ������
			sprintf(lcd_buf,"%0.2d:%0.2d:%0.2d", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
			LcdString(7,4); // // ������� ������� ������� ���������� ������

			break;
	// -----------------------------------------
		case 0x02:
			sprintf (lcd_buf, LANG_MAXFON); // ����� � ����� �������� ��������
			LcdString(1,4); // // ������� ������� ������� ���������� ������
			
			if(!Settings.units)
			{
				sprintf (lcd_buf, LANG_9UMKR, Max_fon); // ����� � ����� �������� ��������
			} else {
				sprintf (lcd_buf, LANG_9UMKZV, convert_mkr_sv(Max_fon)); // ����� � ����� �������� ��������
			}
			LcdString(1,5); // // ������� ������� ������� ���������� ������
      break;
	// -----------------------------------------
		case 0x03:
			sprintf (lcd_buf, LANG_DOSE10M); // ����� � ����� �������� ��������
			LcdString(1,4); // // ������� ������� ������� ���������� ������
			
			if(flash_read_massive(doze_length_10m,dose_select)>0)
			{
				//��� �� ��� massive/(3600/����� �����)
				if(!Settings.units)
				{
					sprintf (lcd_buf, LANG_9UMKR, (flash_read_massive(doze_length_10m,dose_select)*(Settings.Second_count>>2))/900); // ����� � ����� �������� ��������
				} else {
					sprintf (lcd_buf, LANG_9UMKZV, convert_mkr_sv((flash_read_massive(doze_length_10m,dose_select)*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				}
			} else {
				sprintf (lcd_buf, LANG_DOSECALC); // ����� � ����� �������� ��������
			}
			LcdString(1,5); // // ������� ������� ������� ���������� ������
      break;
		// -----------------------------------------
		case 0x04:
			sprintf (lcd_buf, LANG_DOSEHOUR); // ����� � ����� �������� ��������
			LcdString(1,4); // // ������� ������� ������� ���������� ������
		
			if(flash_read_massive(doze_length_hour,dose_select)>0)
			{
				if(!Settings.units)
				{
					sprintf (lcd_buf, LANG_9UMKR, ((Doze_hour_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				} else {
					sprintf (lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_hour_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				}
			} else {
				sprintf (lcd_buf, LANG_DOSECALC); // ����� � ����� �������� ��������
			}
			LcdString(1,5); // // ������� ������� ������� ���������� ������
      break;
  // -----------------------------------------
		case 0x05:
			sprintf (lcd_buf, LANG_DOSE24H); // ����� � ����� �������� ��������
			LcdString(1,4); // // ������� ������� ������� ���������� ������		
			
			if(flash_read_massive(doze_length_day,dose_select)>0) // ����
			{
				if(!Settings.units)
				{
					sprintf (lcd_buf, LANG_9UMKR, ((Doze_day_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				} else {
					sprintf (lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_day_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				}
			} else {
				sprintf (lcd_buf, LANG_DOSECALC); // ����� � ����� �������� ��������
			}

			LcdString(1,5); // // ������� ������� ������� ���������� ������
      break;
  // -----------------------------------------
		case 0x06:
			sprintf (lcd_buf, LANG_DOSEWEEK); // ����� � ����� �������� ��������
			LcdString(1,4); // // ������� ������� ������� ���������� ������
		
			if(flash_read_massive(doze_length_week,dose_select)>0) // ������
			{
				if(!Settings.units)
				{
					sprintf (lcd_buf, LANG_9UMKR, ((Doze_week_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				} else {
					sprintf (lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_week_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				}
			} else {
				sprintf (lcd_buf, LANG_DOSECALC); // ����� � ����� �������� ��������
			}

			LcdString(1,5); // // ������� ������� ������� ���������� ������
      break;
  // -----------------------------------------

			
// -----------------------------------------
		case 0x07:
			sprintf (lcd_buf, LANG_DOSEMONTH); // ����� � ����� �������� ��������
			LcdString(1,4); // // ������� ������� ������� ���������� ������
		
			if(flash_read_massive(doze_length_month,dose_select)>0) // ������
			{
				if(!Settings.units)
				{
					sprintf (lcd_buf, LANG_9UMKR, ((Doze_month_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				} else {
					sprintf (lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_month_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				}
			} else {
				sprintf (lcd_buf, LANG_DOSECALC); // ����� � ����� �������� ��������
			}

			LcdString(1,5); // // ������� ������� ������� ���������� ������
      break;
  // -----------------------------------------
			
			// -----------------------------------------
		case 0x08:
			sprintf (lcd_buf, LANG_DOSE2MONTH); // ����� � ����� �������� ��������
			LcdString(1,4); // // ������� ������� ������� ���������� ������
		
			if(flash_read_massive(doze_length_2month,dose_select)>0) // ������
			{
				if(!Settings.units)
				{
					sprintf (lcd_buf, LANG_9UMKR, ((Doze_2month_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				} else {
					sprintf (lcd_buf, LANG_9UMKZV, convert_mkr_sv((Doze_2month_count*(Settings.Second_count>>2))/900)); // ����� � ����� �������� ��������
				}
			} else {
				sprintf (lcd_buf, LANG_DOSECALC); // ����� � ����� �������� ��������
			}

			LcdString(1,5); // // ������� ������� ������� ���������� ������
      break;
  // -----------------------------------------

    default: 
			break;
	}

	
    Draw_fon_digit(1, 1, 0);
    Draw_fon_graph(2, 94, 67-25, 67);

	if(auto_speedup_factor>1)
	{
		sprintf (lcd_buf, "x%1u", auto_speedup_factor); // ����� � ����� �������� ��������
		LcdString(12,3); // // ������� ������� ������� ���������� ������
	}
    LcdUpdate(); // ���������� ������ �� ��������������� �����-������ �� �������
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
void menu_screen()
{
  char para_string[20];
  char tmp_string[20];
  uint16_t menu_page,i,j; 
  //���������� ����
  
  sprintf (lcd_buf, LANG_MENU);
  LcdStringInv(1,1);
  
  if(menu_select==0)
  {
    menu_page=0;
  }else{

		if(hidden_menu){
			menu_page=(menu_select-1)/(max_string_count-start_offset);// ����������� �������� ���� (������)
		}else{
			if(menu_select<=max_public_string_count)
			{
				menu_page=(menu_select-1)/(max_string_count-start_offset);// ����������� �������� ���� (���������)
			} else {
				menu_page=0;
			}
		}
  }
	
  for(i=0;i<(max_string_count-start_offset);i++)
  {
    uint32_t fill_len=0; 
    uint32_t para_len=0; 
    uint32_t text_len=0; 
    uint32_t menu_struct_index=0; 
		float tmp;
    
    menu_struct_index=(menu_page*(max_string_count-start_offset))+i; // ���������� ����� � ���������
    if (menu_struct_index>=max_struct_index)break; // ���� ���� ���������
		if((menu_struct_index>=max_public_string_count) && (!hidden_menu))break; // ���� �� �������� ���������� ����
    
    
    // ����������� ������� ������, ����� ������� ����� �������� ��������� ������� �� ������ ������ � ���������� (�������� �� ������� ����)
    
    // ��������� �������� ��������� "10���"
    switch(*Menu_list[menu_struct_index].Parameter_value)
    {
      case 0:  // ���� �������� ��������� ����� ����, ���� ��� �� ���������������� �� ���� ������
        if(Menu_list[menu_struct_index].Param_is_0[0] != '\0')
        { sprintf (para_string,  Menu_list[menu_struct_index].Param_is_0); break;}
      
      case 1:  // ���� �������� ��������� ����� �������, ���� ��� �� ���������������� �� ���� ������
        if(Menu_list[menu_struct_index].Param_is_1[0] != '\0')
        { sprintf (para_string,  Menu_list[menu_struct_index].Param_is_1);  break;}
      
      default:  // �� ���� ��������� ������� ������� �� �������
        sprintf (para_string,  Menu_list[menu_struct_index].Param_is_N, *Menu_list[menu_struct_index].Parameter_value); 
        break;
    }
    
		// �������� �� ����
		if((menu_struct_index == 0) && Settings.units)
			sprintf (para_string,  LANG_UMKZV, convert_mkr_sv(*Menu_list[menu_struct_index].Parameter_value)); 

		// �������� �� ���� ����
		if(menu_struct_index == 13)
		{
			tmp=*Menu_list[menu_struct_index].Parameter_value;
			tmp=tmp/10;
			sprintf (para_string,  LANG_BWINDOW_, tmp);
		}
		
    para_len=strlen(para_string);                  // ������ ���������
    text_len=strlen(Menu_list[menu_struct_index].Text);            // ����� ������
    fill_len=max_string_len - para_len - text_len; // ������� ��������� ������ ��������
    
    sprintf (tmp_string, Menu_list[menu_struct_index].Text);             // ����� ����� �������             "���"
    for(j=0;j<fill_len;j++) strcat(tmp_string, " "); // �������� ��������� ����������   "���      "
    
    // ����� �� �����
    // ���� ������ �� ������, �� ������������. �� ���� �� ����� � ����� ����, �� ������������ ������ ��������
    sprintf (lcd_buf,  tmp_string); // ������� � ������ �� ����� "���      "
    if(menu_select==menu_struct_index+1 && enter_menu_item==DISABLE) // ����������� ���������
    {LcdStringInv(1,i+start_offset+1);} 
    else
    {LcdString(1,i+start_offset+1);}
    
    sprintf (lcd_buf,  para_string); // ������� � ������ �� �������� "10 ���"
    if(menu_select==menu_struct_index+1)               // ����������� ���������
    {LcdStringInv(1+text_len+fill_len,i+start_offset+1);} 
    else
    {LcdString(1+text_len+fill_len,i+start_offset+1);}
    
  }
  
  LcdUpdate();
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
void stat_screen()
{
  switch(stat_screen_number)
  {
  case 0: 
		sprintf (lcd_buf, LANG_STAT);
		LcdStringInv(1,1);
  
		sprintf(lcd_buf, LANG_VOLTAGE); // ������� �� �������
		LcdString(1,2); // // ������� ������� ������� ���������� ������ �� ������ 8
  
		sprintf(lcd_buf, LANG_AKB3VVV); // ������� �� �������
		LcdString(1,3); // // ������� ������� ������� ���������� ������ �� ������ 8
  
		sprintf(lcd_buf, "%1i.%02i",ADCData.Batt_voltage/1000,(ADCData.Batt_voltage%1000)/10); // ������� �� �������
		LcdString(1,4); // // ������� ������� ������� ���������� ������ �� ������ 8
  
		sprintf(lcd_buf, "|%1i.%02i",ADCData.Power_voltage/1000,(ADCData.Power_voltage%1000)/10); // ������� �� �������
		LcdString(6,4); // // ������� ������� ������� ���������� ������ �� ������ 8
  
		sprintf(lcd_buf, "|%3i",Settings.Geiger_voltage); // ������� �� �������
		LcdString(12,4); // // ������� ������� ������� ���������� ������ �� ������ 8

		sprintf(lcd_buf, LANG_PUMP); // ������� �� �������
		LcdString(1,6); // // ������� ������� ������� ���������� ������ �� ������ 8
  
		sprintf(lcd_buf, LANG_IMPMINAR); // ������� �� �������
		LcdString(1,7); // // ������� ������� ������� ���������� ������ �� ������ 8
  
		if(pump_counter_avg_impulse_by_1sec[1]==0){sprintf(lcd_buf, LANG_CALC2);} // ������� �� �������
		else                                       sprintf(lcd_buf, "%5i ",pump_counter_avg_impulse_by_1sec[1]); // ������� �� �������
		LcdString(1,8); // // ������� ������� ������� ���������� ������ �� ������ 8
  
		sprintf(lcd_buf, LANG_4IDN,working_days); // ������� �� �������
		LcdString(9,8); // // ������� ������� ������� ���������� ������ �� ������ 8
		break;

#ifdef debug
	case 2:
/*
  	sprintf (lcd_buf, "30 R %9i", flash_read_Doze_massive(61)); LcdString(1,1);
  	sprintf (lcd_buf, "31 R %9i", flash_read_Doze_massive(62)); LcdString(1,2);
  	sprintf (lcd_buf, "32 R %9i", flash_read_Doze_massive(63));	LcdString(1,3);
  	sprintf (lcd_buf, "0  F %09X", flash_read_Doze_massive(64));	LcdString(1,4);
  	sprintf (lcd_buf, "1  F %09X", flash_read_Doze_massive(65));	LcdString(1,5);
  	sprintf (lcd_buf, "2  F %09X", flash_read_Doze_massive(66));	LcdString(1,6);
  	sprintf (lcd_buf, "3  F %09X", flash_read_Doze_massive(67));	LcdString(1,7);
  	sprintf (lcd_buf, "4  F %09X", flash_read_Doze_massive(68));	LcdString(1,8);

*/
	
		sprintf (lcd_buf, LANG_DALL,    Wakeup.total_wakeup); 	 	LcdString(1,1);
		sprintf (lcd_buf, "RTC    %5i", Wakeup.rtc_wakeup);   		LcdString(1,2);
		sprintf (lcd_buf, "tim9   %5i", Wakeup.tim9_wakeup); 	 	  LcdString(1,3);
		sprintf (lcd_buf, LANG_DIMP,    Wakeup.pump_wakeup); 			LcdString(1,4);
		sprintf (lcd_buf, "COMP2  %5i", Wakeup.comp_wakeup); 			LcdString(1,5);
		sprintf (lcd_buf, LANG_DTIME,   debug_wutr/2); 	        	LcdString(1,7);
		sprintf (lcd_buf, LANG_DSENS,   Wakeup.sensor_wakeup);  		LcdString(1,8);

	break;
#endif
	
	case 1:

		sprintf (lcd_buf, LANG_ABOUT);
		LcdStringInv(1,1);
  
		sprintf (lcd_buf, LANG_DOZIK);
		LcdString(1,3);
  	sprintf (lcd_buf, LANG_AUTHOR);
		LcdString(1,4);
		sprintf (lcd_buf, LANG_CITY);
		LcdString(1,5);
		sprintf (lcd_buf, LANG_SITE);
		LcdString(1,6);
	 sprintf (lcd_buf, LANG_BUILD);
	 LcdString(1,7);
	 sprintf (lcd_buf, "     %s",__DATE__);
	 LcdString(1,8);
		break;
	
	default:
		stat_screen_number=0;
		break;
  }
	LcdUpdate();
}
//////////////////////////////////////////////////////////////////////////////////////////////////

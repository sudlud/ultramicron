#include <stdio.h>
#include <stdint.h>
#include "STM32L1xx.h"                  // Device header

#include "main.h"


uint16_t key; // ������ ������� ������ [012]
uint32_t ix;
uint32_t ix_update;

uint16_t Detector_massive[Detector_massive_pointer_max+1];
uint32_t ram_Doze_massive[doze_length+1]; // 1 ������ = 10 �����, �� ���������� �����
uint32_t ram_max_fon_massive[doze_length+1]; // 1 ������ = 10 �����, �� ���������� �����
uint16_t USB_maxfon_massive_pointer=0;
uint16_t USB_doze_massive_pointer=0;
uint16_t current_pulse_count=0;
uint8_t pump_count=0;

uint32_t Doze_day_count=0;
uint32_t Doze_week_count=0;
uint32_t Doze_hour_count=0;
uint32_t Doze_month_count=0;
uint32_t Doze_2month_count=0;
uint32_t Max_fon=0;
uint8_t  main_menu_stat=1;
uint16_t Detector_massive_pointer=0;
uint8_t  auto_speedup_factor=0;
uint32_t USB_not_active=0;
uint32_t last_count_pump_on_impulse=0;
FunctionalState pump_on_impulse=DISABLE;
uint32_t menu_select=0;
#ifdef debug
uint32_t debug_wutr=0;
#endif
FunctionalState enter_menu_item=DISABLE;
uint8_t screen=1;
uint8_t stat_screen_number=0;
uint16_t pump_counter_avg_impulse_by_1sec[2];
uint32_t fon_level=0;
FunctionalState poweroff_state=DISABLE;
FunctionalState hidden_menu=DISABLE;
FunctionalState Pump_on_alarm=DISABLE;
FunctionalState licensed=DISABLE;

uint32_t unlock_0_serial=0;
uint32_t unlock_1_serial=0;
uint32_t unlock_2_serial=0;
uint32_t unlock_3_serial=0;

uint32_t working_days=0;

uint32_t madorc_impulse=0;

FunctionalState Sound_key_pressed=DISABLE;

DataUpdateDef DataUpdate;
ADCDataDef ADCData;
SettingsDef Settings;
AlarmDef Alarm;
PowerDef Power;
#ifdef debug
WakeupDef Wakeup;
#endif


/////////////////////////////////////////////////////////////////////////////////////////
int main(void)

{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x3000);  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	set_msi();
#ifndef debug
	DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STANDBY | DBGMCU_STOP, DISABLE);
#endif
		
  set_bor();
	Power.sleep_now=DISABLE;
	
	DataUpdate.Need_erase_flash=ENABLE;
	
  Settings.Geiger_voltage=360; // ���������� �� ������� 360 �����
  Settings.Pump_Energy=350;    // ������� ������� 350 ���
	DataUpdate.current_flash_page=0;
	
	io_init(); // ������������� ������ ��

	eeprom_write_default_settings(); // ��������, �������� �� EEPROM
  eeprom_read_settings(); // ������ �������� �� EEPROM
  screen=1;
	Power.USB_active=DISABLE;
	Power.sleep_time=Settings.Sleep_time;
  Power.Display_active=ENABLE;
	
	ADCData.DAC_voltage_raw=0x610;

	licensed=check_license(); // �������� ��������

  dac_init();
	comp_init();
	comp_on();
	timer9_Config(); // ������������� ������ �������	
	timer10_Config();
	tim2_Config();
	sound_activate();
	delay_ms(100);
	sound_deactivate();
//--------------------------------------------------------------------
	RTC_Config();	   // ������������� ����
//--------------------------------------------------------------------
// ������������� �������
//--------------------------------------------------------------------
	delay_ms(50); // ��������� ��������� ����������
  display_on(); 
  LcdInit(); 
  LcdClear(); 
//--------------------------------------------------------------------
  adc_init();
  delay_ms(100);
  adc_calibration();
	delay_ms(10);
//--------------------------------------------------------------------
  EXTI8_Config();
#ifdef version_401
  EXTI9_Config();
#endif
	EXTI3_Config();
  EXTI4_Config();
  EXTI6_Config();
		
	DataUpdate.Need_batt_voltage_update=ENABLE;
	
	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))hidden_menu=ENABLE; // �������� ��������� ������� ����
	
	delay_ms(500); // ��������� ��������� ����������
		
  while(1) 
/////////////////////////////////
  {
		if(DataUpdate.RTC_tick_update==ENABLE)	RTC_tick_processing();
		if(DataUpdate.Need_fon_update==ENABLE)	geiger_calc_fon();
    if(key>0)																keys_proccessing();
		if(DataUpdate.Need_batt_voltage_update)	adc_check_event();

		////////////////////////////////////////////////////

		
		if((Power.sleep_time>0)&&(!Power.Display_active))sleep_mode(DISABLE); // ���� ������� ��� ��������, � ������� ��� ��� �����������, ��������� ���������� � �������� �������
    
		if(Power.Display_active)
    {
			if(Power.sleep_time==0 && !Alarm.Alarm_active) sleep_mode(ENABLE);  // ������� ��� �������� �� ����, � ������� ��� �������, �� ��������� ��� � �������� ����������
			if(DataUpdate.Need_display_update==ENABLE)
			{
				DataUpdate.Need_display_update=DISABLE;
				LcdClear_massive();
				if (screen==1)main_screen();
				if (screen==2)menu_screen();
				if (screen==3)stat_screen();
			}
///////////////////////////////////////////////////////////////////////////////
		}

		#ifdef version_401
		if((!Power.USB_active) && (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))){
			usb_activate(0x0); // ���� ������� USB ������ ���������� �������� USB
		}
#endif

		if(!Power.USB_active)		// ���� USB �� �������, ����� ������� � ���
		{
			if(current_pulse_count<30)      // ���� ������� �� �����������, �� ����� ���� � ���
			{
				if(DataUpdate.RTC_tick_update==ENABLE)	RTC_tick_processing();

				if(!Power.Pump_active && !Power.Sound_active)
				{
#ifndef debug
					PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);    // ��������� � ���
#endif
#ifdef debug
 					Wakeup.total_wakeup++;
					DataUpdate.Need_display_update=ENABLE;
#endif

				} else
				{
						PWR_EnterSleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);
#ifdef debug
  					Wakeup.total_wakeup++;
						DataUpdate.Need_display_update=ENABLE;
#endif
				}
				if(DataUpdate.RTC_tick_update==ENABLE)	RTC_tick_processing();
			}
		} else USB_work(); 		// ���� USB �������, ����������� �������� ������
#ifdef debug
 		Wakeup.total_cycle++;
		DataUpdate.Need_display_update=ENABLE;
#endif

  }
/////////////////////////////////////////////////////////////////////////////// 
}

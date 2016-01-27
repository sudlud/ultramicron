#include "stm32l1xx.h"
#include "main.h"

__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
__IO TestStatus DataMemoryProgramStatus = PASSED;
uint32_t NbrOfPage = 0, j = 0, Address = 0;

//**************************************************************************
// ������ ���������� �� ���������
    void eeprom_write_default_settings(void)
    {
      if(eeprom_read(Second_count_address) == 0x00)
      { 
        Settings.Alarm_level=50;
        Settings.Sound=ENABLE;
        Settings.Sleep_time=80;
        Settings.Display_reverse=2;
				Settings.Second_count=250;
				Settings.LSI_freq=37000;
				Settings.Geiger_voltage=360;
				Settings.Power_comp=0;
				Settings.Vibro=0;
				Settings.v4_target_pump=8;
				Settings.units=0;
				Settings.Beta_window=20;
				Settings.Beta_procent=37;
        eeprom_write_settings(); // ������
      }  
    }
//**************************************************************************

void eeprom_write_settings(void)
{
	
  //������ ���������� � EEPROM
  if(eeprom_read(Alarm_level_address)    !=Settings.Alarm_level)    eeprom_write(Alarm_level_address,    Settings.Alarm_level);
  if(eeprom_read(Sleep_time_address)     !=Settings.Sleep_time )    eeprom_write(Sleep_time_address,     Settings.Sleep_time);
  if(eeprom_read(contrast_address)       !=Settings.contrast)       eeprom_write(contrast_address,       Settings.contrast);
  if(eeprom_read(Display_reverse_address)!=Settings.Display_reverse)eeprom_write(Display_reverse_address,Settings.Display_reverse);
	if(eeprom_read(Second_count_address)   !=Settings.Second_count)   eeprom_write(Second_count_address,   Settings.Second_count);
	if(eeprom_read(Sound_address)          !=Settings.Sound)          eeprom_write(Sound_address,          Settings.Sound);
	if(eeprom_read(Power_comp_address)     !=Settings.Power_comp)     eeprom_write(Power_comp_address,     Settings.Power_comp);
	if(eeprom_read(Vibro_address)     		 !=Settings.Vibro)          eeprom_write(Vibro_address,          Settings.Vibro);
	if(eeprom_read(Geiger_voltage_address) !=Settings.Geiger_voltage) eeprom_write(Geiger_voltage_address, Settings.Geiger_voltage);
	if(eeprom_read(v4_target_pump_address) !=Settings.v4_target_pump) eeprom_write(v4_target_pump_address, Settings.v4_target_pump);
	if(eeprom_read(Beta_window_address)    !=Settings.Beta_window)    eeprom_write(Beta_window_address,    Settings.Beta_window);
	if(eeprom_read(Beta_procent_address)   !=Settings.Beta_procent)   eeprom_write(Beta_procent_address,   Settings.Beta_procent);
	if(eeprom_read(units_address)          !=Settings.units)          eeprom_write(units_address,          Settings.units);
	if(Settings.LSI_freq != 0x00) // ���� ���������� �����, ������� ���������� ������������
	{
		if(eeprom_read(LSI_freq_address)       !=Settings.LSI_freq)       eeprom_write(LSI_freq_address,       Settings.LSI_freq);
	}
	Power.led_sleep_time=Settings.Sleep_time-3;
}

//**************************************************************************
void eeprom_apply_settings(void)
{
  if(eeprom_read(contrast_address)!=Settings.contrast)       
	{
		display_off();
		delay_ms(200);
		display_on();
	}
	// -------------------------------------------------------------------
  if(eeprom_read(Display_reverse_address)!=Settings.Display_reverse)
	{
		display_off();
		delay_ms(200);
		display_on();
	}
	
  if(eeprom_read(units_address)!=Settings.units)
	{
		if(licensed!=ENABLE)Settings.units=0;
	}
	
	if(licensed==ENABLE)
	// -------------------------------------------------------------------
  if(eeprom_read(v4_target_pump_address)!=Settings.v4_target_pump)
	{
		reset_TIM_prescallers_and_Compare();	
	}
	// -------------------------------------------------------------------
	if(eeprom_read(Geiger_voltage_address) !=Settings.Geiger_voltage) 
 	{
		dac_reload(); //������������� � ��� ����� ���������� ������� �������
 	}
	// -------------------------------------------------------------------
	if(eeprom_read(LSI_freq_address)       !=Settings.LSI_freq)
  {
		if(Settings.LSI_freq != 0x00) // ���� ���������� �����, ������� ���������� ������������
		{
			eeprom_write(LSI_freq_address,Settings.LSI_freq);   NVIC_SystemReset();
		}
	}
}

//**************************************************************************

void eeprom_read_settings(void)
{
  //������ ���������� �� EEPROM
  Settings.Alarm_level=           eeprom_read(Alarm_level_address);
  Settings.Sleep_time=            eeprom_read(Sleep_time_address);
  Settings.contrast=              eeprom_read(contrast_address);
  Settings.Display_reverse=				eeprom_read(Display_reverse_address);
  Settings.Second_count=          eeprom_read(Second_count_address);
	Settings.Sound=                 eeprom_read(Sound_address);
  Settings.LSI_freq=  			      eeprom_read(LSI_freq_address);  
	Settings.Power_comp= 			      eeprom_read(Power_comp_address);  
	Settings.Vibro= 			  		    eeprom_read(Vibro_address);  
	Settings.Geiger_voltage=				eeprom_read(Geiger_voltage_address);
	Settings.v4_target_pump=				eeprom_read(v4_target_pump_address);
	Settings.units=		          		eeprom_read(units_address);
	Settings.serial0=	          		eeprom_read(unlock_0_address);
	Settings.serial1=	          		eeprom_read(unlock_1_address);
	Settings.serial2=	          		eeprom_read(unlock_2_address);
	Settings.serial3=	          		eeprom_read(unlock_3_address);
	Settings.Beta_window=       		eeprom_read(Beta_window_address);
	Settings.Beta_procent=       		eeprom_read(Beta_procent_address);


	Power.led_sleep_time=Settings.Sleep_time-3;
}


//**************************************************************************
void eeprom_erase(void)
{
  DATA_EEPROM_Unlock(); // ������������� ����� �������
  
  /* Clear all pending flags */      
  FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR
                  | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);	
  
  /*  Data EEPROM Fast Word program of FAST_DATA_32 at addresses defined by 
  DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR */  
  Address = DATA_EEPROM_START_ADDR;
  
  NbrOfPage = ((DATA_EEPROM_END_ADDR - Address) + 1 ) >> 2; 
  
  /* Erase the Data EEPROM Memory pages by Word (32-bit) */
  for(j = 0; j < NbrOfPage; j++)
  {
    FLASHStatus = DATA_EEPROM_EraseWord(Address + (4 * j));
  }
  DATA_EEPROM_Lock();
  
  /* Check the correctness of written data */
  while(Address < DATA_EEPROM_END_ADDR)
  {
    if(*(__IO uint32_t*)Address != 0x0)
    {
      DataMemoryProgramStatus = FAILED;
      //������ �������� !!!!
      return;
    }
    Address = Address + 4;
  }
  
}



//************************************************************************
uint32_t eeprom_read(uint32_t address_of_read)
{
  
  /* Clear all pending flags */      
  FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR
                  | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);	
  
  /*  Data EEPROM Fast Word program of FAST_DATA_32 at addresses defined by 
  DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR */  
  Address = DATA_EEPROM_START_ADDR+address_of_read;
  if(Address > DATA_EEPROM_END_ADDR)
  {
    // ������ ��� ��������� eeprom !!!!
    return 0x00;
  }
  
  // ������ ������
  return  *(__IO uint32_t*)Address;
}



//************************************************************************

void eeprom_write(uint32_t address_of_read, uint32_t data)
{
  
  DATA_EEPROM_Unlock(); // ������������� ����� �������
  
  /* Clear all pending flags */      
  FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR
                  | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);	
  
  /*  Data EEPROM Fast Word program of FAST_DATA_32 at addresses defined by 
  DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR */  
  Address = DATA_EEPROM_START_ADDR+address_of_read;
  if(Address > DATA_EEPROM_END_ADDR)
  {
    // ������ ��� ��������� eeprom !!!!
    DATA_EEPROM_Lock();
    return;
  }
  
  // ������ ������ �� ������
  FLASHStatus = DATA_EEPROM_ProgramWord(Address, data);
  DATA_EEPROM_Lock();  
  
  if(FLASHStatus != FLASH_COMPLETE)
  {
    // ������ ������ eeprom !!!!
    return;
  }
  FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR
                  | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR);
  
  
  // �������� ���������� ������ 
  if(*(__IO uint32_t*)Address != data)
  {
    DataMemoryProgramStatus = FAILED;
    // ������ ������ !!!!!
    return;
  }
  
  
  
}


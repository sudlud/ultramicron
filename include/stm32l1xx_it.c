#include "stm32l1xx_it.h"
#include "main.h"


uint16_t tmpCC1[2] = {0, 0};
extern __IO uint32_t CaptureNumber, PeriodValue;
uint32_t IC1ReadValue1 = 0, IC1ReadValue2 =0;


// ===============================================================================================


// ===============================================================================================
void NMI_Handler(void)
{
}

  void HardFault_Handler(void)
{
while (1)
  {
}
}
    
/**
* @brief  This function handles Memory Manage exception.
* @param  None
* @retval None
*/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Bus Fault exception.
* @param  None
* @retval None
*/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Usage Fault exception.
* @param  None
* @retval None
*/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles SVCall exception.
* @param  None
* @retval None
*/
void SVC_Handler(void)
{
}

/**
* @brief  This function handles Debug Monitor exception.
* @param  None
* @retval None
*/
void DebugMon_Handler(void)
{
}

/**
* @brief  This function handles PendSVC exception.
* @param  None
* @retval None
*/
void PendSV_Handler(void)
{
}

/**
* @brief  This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler(void)
{
  extern uint32_t msTicks;
  msTicks++;		// инкремент счётчика времени
}
/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

/**
* @brief  This function handles PPP interrupt request.
* @param  None
* @retval None
*/
/*void PPP_IRQHandler(void)
{
}*/

/**
* @}
*/ 

// =======================================================
// Прерывание по нажатию кнопки 0
void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
	if(!poweroff_state)
		{
			if(Alarm.Alarm_active && !Alarm.User_cancel)
			{
				Alarm.User_cancel=ENABLE;
			}
			else
			{
				if(Power.Display_active)
				{
					key|=0x1; // Кнопка Меnu
				}
			}
			Sound_key_pressed=ENABLE;
			check_wakeup_keys();
		}
		EXTI_ClearITPendingBit(EXTI_Line3);
  }
}

// =======================================================
// Прерывание по нажатию кнопки 1
void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4) != RESET)
  {
		if(!poweroff_state)  
		{
			if(Power.Display_active)
			{      
				key|=0x4;   // Кнопка -
			}    
			Sound_key_pressed=ENABLE;
			check_wakeup_keys();
		}
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

// =======================================================
// Прерывание по импульсу от датчикав 1 и кнопки 2
void EXTI9_5_IRQHandler(void)
{

#ifdef debug
		Wakeup.sensor_wakeup++;
#endif
  if(EXTI_GetITStatus(EXTI_Line6) != RESET) // Кнопка
  {
    EXTI_ClearITPendingBit(EXTI_Line6);
		if(!poweroff_state)
		{
			if(Power.Display_active)
			{
					key|=0x2; // Кнопка +
			}
			Sound_key_pressed=ENABLE;
			check_wakeup_keys();
		}
	}
#ifdef version_401
  if(EXTI_GetITStatus(EXTI_Line9) != RESET) // Подключено USB
  {
    EXTI_ClearITPendingBit(EXTI_Line9);
		if(!poweroff_state)
		{
			sound_activate();
			Power.sleep_time=Settings.Sleep_time;
			Power.led_sleep_time=Settings.Sleep_time-3;
		}			
  }
#endif
  if(EXTI_GetITStatus(EXTI_Line8) != RESET) // Импульс датчика
  {
		EXTI_ClearITPendingBit(EXTI_Line8);
		if(!poweroff_state)  
		{		
			Detector_massive[Detector_massive_pointer]++;  // Добавляем пойманную частицу к счетчику  
			ram_Doze_massive[0]++;	           					// Увеличение суточного массива дозы

			if(Settings.Sound == 1 && !(Alarm.Alarm_active && !Alarm.User_cancel))
			{
				if(Power.Display_active)
				{
					sound_activate();
				}
			}
			if(Power.Pump_active==DISABLE)
			{
				if(last_count_pump_on_impulse>5)
				{
					pump_on_impulse=ENABLE;
					Pump_now(ENABLE);
					last_count_pump_on_impulse=0;
				} else last_count_pump_on_impulse++;
			}
		}
	}
}


// =======================================================
// Прерывание при конце интервала одного импульса накачки
void TIM9_IRQHandler(void)
{
#ifdef debug	
	Wakeup.tim9_wakeup++;
#endif
	if((TIM9->CCER & (TIM_CCx_Enable << TIM_Channel_1)) && !poweroff_state)
	{
		current_pulse_count++;
		pump_counter_avg_impulse_by_1sec[0]++;
/*
		if(COMP->CSR  & COMP_CSR_INSEL) // если компаратор активен
		{
			if(Power.Pump_active==DISABLE) Pump_now(DISABLE); 
		}else{
			comp_on();
		}
*/

	}
	TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
}

// ========================================================
// генерация звука на динамик
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		if(!poweroff_state)
		{
			if(Alarm.Alarm_active && !Alarm.User_cancel)
			{
				Alarm.Alarm_beep_count++;
				if(Alarm.Alarm_beep_count==50)   TIM_SetAutoreload(TIM10, 32  );
				if(Alarm.Alarm_beep_count==100) {TIM_SetAutoreload(TIM10, 16  );Alarm.Alarm_beep_count=0;}
			}

			if((Alarm.Alarm_active && Alarm.User_cancel) || !Alarm.Alarm_active)
			{
				if(Power.Sound_active == ENABLE)
				{	
					if(Sound_key_pressed) // нажатие кнопки
					{
						if(Alarm.Tick_beep_count>40)
								{
									Alarm.Tick_beep_count=0;
									sound_deactivate();
								} else Alarm.Tick_beep_count++;
							
					} else if(Alarm.Tick_beep_count>3) // тик датчика
							{
								Alarm.Tick_beep_count=0;
								sound_deactivate();
							} else Alarm.Tick_beep_count++;
			} else sound_deactivate();
		}
	}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////
// Секундный тик
////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RTC_Alarm_IRQHandler(void) { // Тик каждые 4 секунды
#ifdef debug
	Wakeup.rtc_wakeup++;
#endif
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET) 
	{
		RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
		Set_next_alarm_wakeup(); // установить таймер просыпания на +4 секунды
		if(Pump_on_alarm==ENABLE)Pump_now(ENABLE); // оптимизируем накачку вынося из вейкап таймера
		DataUpdate.RTC_tick_update=ENABLE;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RTC_WKUP_IRQHandler (void)
{
#ifdef debug	
	Wakeup.pump_wakeup++;
#endif	
	EXTI_ClearITPendingBit(EXTI_Line20);
	if(!poweroff_state)
	{
		if(RTC_GetITStatus(RTC_IT_WUT) != RESET)
		{
			RTC_ClearITPendingBit(RTC_IT_WUT);
			if(!Power.Pump_active)
			{
				Pump_now(ENABLE);
			}
		} 
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void COMP_IRQHandler(void)
{
	uint32_t i;	
	extern uint16_t current_pulse_count;
#ifdef debug	
	Wakeup.comp_wakeup++;
#endif	
  if(EXTI_GetITStatus(EXTI_Line22) != RESET)
  {
	 if(!poweroff_state)
	 {
		// Зафиксирован выброс нужной амплитуды, выключаем накачку
		{
			Pump_now(DISABLE);
		 	if(!pump_on_impulse)
			{
				i=RTC->WUTR;
				if(current_pulse_count>20) // если подключена мощьная нагрузка типа мультиметра, резко ускаряем накачку.
				{
					if(i>0x80)
					{
#ifdef version_401 // Для версии 4+ делить на 4 для стабилизации накачки
						i>>=2; // ускоренное деление на 4
#else
						i>>=4; // ускоренное деление на 16
#endif
					}else
					{
						i=0x8; // Если делить нельзя, то = 4 мс
					}
				} else
				{
					if(i<0x8)i=0x8;
					if(current_pulse_count>2) // Если количество импульсов велико, то напряжения не достаточно, ускоряем накачку.
					{ 
						if(i>0x0010)i>>=1; // деление на 2
					} else 
#ifdef version_401 // Для версии 4+ накачка немного более агресивна
					{ // Количество импульсов накачки мало, значит можно увеличить интервал между импульсами.
							i<<=1; // умножаем на 2
							if(i>0x1E00)i=0x2000; // придел 4 секунды
					}
#else
					{ // Количество импульсов накачки мало, значит можно увеличить интервал между импульсами.
						if(i<0x7FFF) //Если больше половины от максимума
						{
							i<<=1; // умножаем на 2
						} else 
						{
							// если умножать на 2 уже нельзя, просто прибавляем до придела
							i=i+0x2000; // + 4 секунды
							if(i>0xFFFF)i=0xFFFF; // придел 32 секунды
						}
					}
#endif

				} 
#ifdef debug
				debug_wutr=i;
#endif

#ifdef version_401 // Для версии 4+				
				if(i==0x2000)
				{
					RTC_ITConfig(RTC_IT_WUT, DISABLE);
					RTC_WakeUpCmd(DISABLE);
					Pump_on_alarm=ENABLE;
				} else
				{
					RTC_ITConfig(RTC_IT_WUT, ENABLE);
					Pump_on_alarm=DISABLE;
#endif
					if(RTC->WUTR!=i)
					{
						while(RTC_WakeUpCmd(DISABLE)!=SUCCESS);
						RTC_SetWakeUpCounter(i); 			// Установить таймаут просыпания
						while(RTC_WakeUpCmd(ENABLE)!=SUCCESS);
					}
#ifdef version_401 // Для версии 4+				
				}
#endif
				current_pulse_count=0;
			} else {
				//last_count_pump_on_impulse=current_pulse_count;
				pump_on_impulse=DISABLE;
			}
		}
	}
		EXTI_ClearITPendingBit(EXTI_Line22);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB Low Priority interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_IRQHandler(void)
{
  USB_Istr();
}

/*******************************************************************************
* Function Name  : USB_FS_WKUP_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void USB_FS_WKUP_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

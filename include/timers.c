#include "stm32l1xx_tim.h"
#include "main.h"

/////////////////////////////////////////////////////////////////////////////////
void sound_activate(void)
{
	if(Power.USB_active==DISABLE)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		if(Power.Display_active==ENABLE)
		{
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
			TIM10->EGR |= 0x0001;  // ������������� ��� UG ��� ��������������� ������ ��������
			TIM2->EGR  |= 0x0001;  // ������������� ��� UG ��� ��������������� ������ ��������
			TIM_CCxCmd(TIM10, TIM_Channel_1, TIM_CCx_Enable); // ��������� ������ ���������
			TIM_Cmd(TIM2, ENABLE);
			Alarm.Tick_beep_count=0;
			Power.Sound_active=ENABLE;
#ifdef version_401
			if(Settings.Vibro==1                                 )GPIO_SetBits(GPIOA,GPIO_Pin_15);// ���������� ����������
			if((Settings.Vibro>1) && (Alarm.Alarm_active==ENABLE))GPIO_SetBits(GPIOA,GPIO_Pin_15);// ���������� ����������
#endif
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
void sound_deactivate(void)
{	

	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	TIM_Cmd(TIM2, DISABLE);
	
	TIM_CCxCmd(TIM10, TIM_Channel_1, TIM_CCx_Disable); // ��������� ������ ���������

	TIM_SetAutoreload(TIM10, 16 );
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);

  Power.Sound_active=DISABLE;      
	Sound_key_pressed=DISABLE;

#ifdef version_401
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);// ��-���������� ����������
#endif

}
/////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////
void reset_TIM_prescallers_and_Compare(void)
{
	uint32_t pump_period;
	
	delay_ms(20);
	SystemCoreClockUpdate();
	
	TIM_PrescalerConfig(TIM10,(uint32_t) (SystemCoreClock /  128000) - 1,TIM_PSCReloadMode_Immediate); // ������� ������� 128 ���
	TIM_PrescalerConfig(TIM2, (uint32_t) (SystemCoreClock /     800) - 1,TIM_PSCReloadMode_Immediate); // �������� (1 ��� = 1.25��)
	TIM_PrescalerConfig(TIM9, (uint32_t) (SystemCoreClock / 4000000) - 1,TIM_PSCReloadMode_Immediate); // 0.25 ���

#ifdef version_401
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
	{
		pump_period=(Settings.v4_target_pump*4200)/5000; // ������ ������� ������� (������ 1,75���*4.2�/5.0� ���������� USB=1.25���)
	} else {
		pump_period=(Settings.v4_target_pump*4200)/ADCData.Batt_voltage; // ������ ������� ������� (������ 1,75���*4.2�/3.3� ���������� ���=2.0���)
	}
#else
	pump_period=(352*Settings.Pump_Energy)/ADCData.Batt_voltage; // ���������� ������� �������
	if((pump_period>32) && (Settings.LSI_freq==0))pump_period=32; // �� ��������� ����������� ������� ��� ����� 3.*
#endif

	TIM_SetCompare1(TIM9,pump_period); // ���������� ������� �������
}
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
void timer9_Config(void) // ��������� �������
{
TIM_TimeBaseInitTypeDef TIM_BaseConfig;
TIM_OCInitTypeDef TIM_OCConfig;
NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

  TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1; // ������������� ����� �������, ����� - PWM1
  TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;   // ���������� - ����� �������
  TIM_OCConfig.TIM_Pulse = Settings.v4_target_pump;   
  TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High; // ���������� => ����� - ��� ������� (+3.3V)

  TIM_BaseConfig.TIM_Prescaler = (uint16_t) (SystemCoreClock / 4000000) - 1; // �������� (1 ��� = 0.25���)
  TIM_BaseConfig.TIM_ClockDivision = 0;
#ifdef version_401
  TIM_BaseConfig.TIM_Period = 560;  // ��������� �������, �� ������!  ����� ���������� ����� (������������) 140��� (������� ������� 1�/140���=** ���)
#else
  TIM_BaseConfig.TIM_Period = 560;  // ����� ���������� ����� (������������) 140���
#endif
  TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up; // ������ �� ���� �� TIM_Period
  
  
  TIM_DeInit(TIM9); // ��-�������������� ������ �9
  
// ��� � ����� - �������������� ����������� �������, ���� ������ - ��������.
  TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM9, ENABLE);
	
	TIM_TimeBaseInit(TIM9, &TIM_BaseConfig);
  TIM_OC1Init(TIM9, &TIM_OCConfig);  // �������������� ������ ����� ������� �9 (� HD ��� PB13)

  // ��� � ����� - �������������� ����������� �������, ���� ������ - ��������.
  TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM9, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM9_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);

  TIM9->EGR |= 0x0001;  // ������������� ��� UG ��� ��������������� ������ ��������
  TIM_CCxCmd(TIM9, TIM_Channel_1, TIM_CCx_Disable); // ��������� �������
  TIM_Cmd(TIM9, ENABLE);
}
/////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////
void timer10_Config(void) // ��������� �����
{
TIM_TimeBaseInitTypeDef TIM_BaseConfig;
TIM_OCInitTypeDef TIM_OCConfig;
GPIO_InitTypeDef   GPIO_InitStructure;
	
	TIM_TimeBaseStructInit(&TIM_BaseConfig);
	TIM_OCStructInit(&TIM_OCConfig);
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);

  TIM_BaseConfig.TIM_ClockDivision = 0;
  TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_BaseConfig.TIM_Prescaler = (uint32_t) (SystemCoreClock / 128000) - 1; // ������� ������� 32 ���
  TIM_BaseConfig.TIM_Period = 16;  // ~8 ���
  TIM_OCConfig.TIM_Pulse = 8; // ������������ ~50% 
  // ��� � ����� - �������������� ����������� �������, ���� ������ - ��������.

	TIM_DeInit(TIM10); // ��-�������������� ������ �10

  TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM10, ENABLE);

// ===============================================================================================  
  // �������
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;           // �����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  // ��������� ������������
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_TIM10);
// ===============================================================================================  

	TIM_TimeBaseInit(TIM10, &TIM_BaseConfig);
  TIM_OC1Init(TIM10, &TIM_OCConfig);  // �������������� ������ ����� �������

	TIM_CCxCmd(TIM10, TIM_Channel_1, TIM_CCx_Enable); // ��������� ������ �����
  TIM_Cmd(TIM10, ENABLE);
}
///////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////
void tim2_Config()
{
TIM_TimeBaseInitTypeDef TIM_BaseConfig;
NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseStructInit(&TIM_BaseConfig);

  TIM_BaseConfig.TIM_Prescaler = (uint16_t) (SystemCoreClock / 800) - 1; // �������� (1 ��� = 10��)
  TIM_BaseConfig.TIM_ClockDivision = 0;
  TIM_BaseConfig.TIM_Period = 1;  // ����� ���������� �����
  TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_TimeBaseInit(TIM2, &TIM_BaseConfig);

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM2->EGR |= 0x0001;  // ������������� ��� UG ��� ��������������� ������ ��������
  TIM_Cmd(TIM2, ENABLE);
	
}
/////////////////////////////////////////////////////////////////////////////////

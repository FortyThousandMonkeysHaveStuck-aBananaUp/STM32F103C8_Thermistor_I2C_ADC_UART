#define STM32F103xB
#include "stm32f1xx.h"
//Fatal Error[Pe1696]: cannot open source file "stm32f103xb.h" C:\Users\Pz\Desktop\Education STM_C-C++\0_Testing\CMSIS_learning_3_UART_I2C\For the video\0_Additional files\stm32f1xx.h 131 
//Fatal Error[Pe1696]: cannot open source file "core_cm3.h" C:\Users\Pz\Desktop\Education STM_C-C++\0_Testing\CMSIS_learning_3_UART_I2C\For the video\0_Additional files\stm32f103xb.h 132 
//Fatal Error[Pe1696]: cannot open source file "cmsis_version.h" C:\Users\Pz\Desktop\Education STM_C-C++\0_Testing\CMSIS_learning_3_UART_I2C\For the video\0_Additional files\core_cm3.h 63 
//Fatal Error[Pe1696]: cannot open source file "cmsis_compiler.h" C:\Users\Pz\Desktop\Education STM_C-C++\0_Testing\CMSIS_learning_3_UART_I2C\For the video\0_Additional files\core_cm3.h 115 
//Fatal Error[Pe1696]: cannot open source file "cmsis_iccarm.h" C:\Users\Pz\Desktop\Education STM_C-C++\0_Testing\CMSIS_learning_3_UART_I2C\For the video\0_Additional files\cmsis_compiler.h 55 

/*Functions prototypes*/
void System_Clock_Config(void);
void ADC2_Config(void);
void ADC2_Start(char channel);
void user_delay(unsigned long wait);
void I2C2_Config(void);
void Get_I2C2_temperature_from_the_LM75_sensor(char address, char data, char * I2C2_Result);
void UART2_Config(void);
void UART2_Send_Char(char symbol);
void UART2_Send_String(char * pointer);

/*Varaibles*/
unsigned int ADC2_Result=0;
char I2C2_temperature[2];
unsigned int temperature_array[128]={
2850,//000 C
2829,//001 C
2810,//002 C
2777,//003 C
2746,//004 C
2724,//005 C
2697,//006 C
2659,//007 C
2617,//008 C
2578,//009 C
2539,//010 C
2505,//011 C
2461,//012 C
2426,//013 C
2389,//014 C
2350,//015 C
2314,//016 C
2279,//017 C
2239,//018 C
2196,//019 C
2156,//020 C
2114,//021 C
2041,//022 C
1992,//023 C
1959,//024 C
1919,//025 C
1893,//026 C
1864,//027 C
1951,//028 C
1815,//029 C
1700,//030 C
1650,//031 C
1292,//032 C
1281,//033 C
1207,//034 C
1167,//035 C
1106,//036 C
1046,//037 C
980,//038 C
900,//039 C
873,//040 C
839,//041 C
822,//042 C
0760,//043 C
0732,//044 C
0700,//045 C
0666,//046 C
0654,//047 C
0630,//048 C
0607,//049 C
0601,//050 C
596,//051 C
590,//052 C
585,//053 C
580,//054 C
0577,//055 C
0575,//056 C
0573,//057 C
0565,//058 C
578,//059 C
0577,//060 C
781,//061 C
0763,//062 C
0737,//063 C
0716,//064 C
698,//065 C
680,//066 C
658,//067 C
0643,//068 C
0621,//069 C
0617,//070 C
591,//071 C
0575,//072 C
0554,//073 C
0546,//074 C
0512,//075 C
0505,//076 C
484,//077 C
0475,//078 C
0472,//079 C
0463,//080 C
0442,//081 C
0431,//082 C
0422,//083 C
0415,//084 C
395,//085 C
389,//086 C
0372,//087 C
0374,//088 C
0350,//089 C
0333,//090 C
329,//091 C
0316,//092 C
0313,//093 C
308,//094 C
292,//095 C
290,//096 C
282,//097 C
275,//098 C
266,//099 C
258,//100 C
0250,//101 C
0236,//102 C
0220,//103 C
219,//104 C
0203,//105 C
0201,//106 C
188,//107 C
183,//108 C
0173,//109 C
168,//110 C
169,//111 C
0164,//112 C
0151,//113 C
0154,//114 C
148,//115 C
0141,//116 C
0141,//117 C
0136,//118 C
0131,//119 C
0130,//120 C
0126,//121 C
0121,//122 C
0112,//123 C
0106,//124 C
0106,//125 C
97,//126 C
0077//127 C
};
char temperature_discharge[4];
unsigned int difference=0;
char value_number=0;
char number_symbols[10]={//windows-1251
0x30, //0
0x31, //1
0x32, //2
0x33, //3
0x34, //4
0x35, //5
0x36, //6
0x37, //7
0x38, //8
0x39  //9
};

typedef enum{
M_was_received,
T_was_received,
nothing
}Flags;

Flags UART2_Flag=nothing;

/*Interrutps*/
//ADC2
void ADC1_2_IRQHandler(void)
{
  if(ADC2->SR&ADC_SR_EOC)
  {
    ADC2_Result=ADC2->DR;// <=4095
  }
}

//UART2
void USART2_IRQHandler(void)
{
  if(USART2->SR&USART_SR_RXNE)
  {
    //M
    if(USART2->DR=='M'){UART2_Flag=M_was_received;}//Send the temperature array
    
    //T
    if(USART2->DR=='T'){UART2_Flag=T_was_received;}
  }
}
void main(void)
{
/* Config*/
  //System clock
  System_Clock_Config();
  
  //ADC2_Config
  ADC2_Config();
  ADC2_Start(0);
  
  //I2C2_Config
  I2C2_Config();

  //UART2_Config
  UART2_Config();

  //UART2_Send_String("Hellow from the Earth!\n");

  while(4)
  {
  
#define GET_THE_TEMPERATURE_ARRAY
#ifdef GET_THE_TEMPERATURE_ARRAY
  
    //Get the temperature_array[128]
    Get_I2C2_temperature_from_the_LM75_sensor(0x90, 0x00, I2C2_temperature);
    
    if((*(I2C2_temperature+1)&0xE0)==0)
    {
      ADC2_Start(0);
      temperature_array[*(I2C2_temperature+0)]=ADC2_Result;
    }

    if(UART2_Flag==M_was_received)
    {
      UART2_Flag=nothing;
      
      
      
      //Send the temperature array
      //        "={\r"
      //        "xxxx,//xxxx C\r"          (!,!)
      //        "};\r"
      
      //        "={\r"
      UART2_Send_Char('=');
      UART2_Send_Char('{');
      UART2_Send_Char('\r');
      
      //        "xxxx,//xxx C\r"          (!,!)
      for(char i=0; i<128; i++)
      {
        temperature_discharge[0]=(temperature_array[i]/1000)%10;//Sxxx -> 000S
        temperature_discharge[1]=(temperature_array[i]/100)%10;//xSxx -> 00xS
        temperature_discharge[2]=(temperature_array[i]/10)%10;//xxSx -> 0xxS
        temperature_discharge[3]=temperature_array[i]%10;//xxxS -> xxxS
        
        UART2_Send_Char(number_symbols[temperature_discharge[0]]);
        UART2_Send_Char(number_symbols[temperature_discharge[1]]);
        UART2_Send_Char(number_symbols[temperature_discharge[2]]);
        UART2_Send_Char(number_symbols[temperature_discharge[3]]);
        
        if(i!=127){UART2_Send_Char(',');}
        UART2_Send_Char('/');
        UART2_Send_Char('/');
        
        temperature_discharge[1]=(i/100)%10;//xSxx -> 00xS
        temperature_discharge[2]=(i/10)%10;//xxSx -> 0xxS
        temperature_discharge[3]=i%10;//xxxS -> xxxS
        
        UART2_Send_Char(number_symbols[temperature_discharge[1]]);
        UART2_Send_Char(number_symbols[temperature_discharge[2]]);
        UART2_Send_Char(number_symbols[temperature_discharge[3]]);
        
        UART2_Send_Char(' ');
        UART2_Send_Char('C');
        UART2_Send_Char('\r');
      }
      
      
      //        "};\r"
      UART2_Send_Char('}');
      UART2_Send_Char(';');
      UART2_Send_Char('\r');
      
    }
    //Send the temperature_array[] via UART2
    
#endif
    
    
    //Save the temperature_array[] in source code
    
    //Find the temperature in temperature_array
    //Send the thermistor temperature via UART2
    
    if(UART2_Flag==T_was_received)
    {
      UART2_Flag=nothing;
      
      difference=3000;
      value_number=0;
      ADC2_Start(0);
      
      for(char i=0; i<128; i++)
      {
        
        if((ADC2_Result<temperature_array[i])&&((temperature_array[i]-ADC2_Result)<difference))
        {
          value_number=i;
          difference=temperature_array[i]-ADC2_Result;
        } else if((ADC2_Result>=temperature_array[i])&&((ADC2_Result-temperature_array[i])<difference))
        {
          value_number=i;
          difference=ADC2_Result-temperature_array[i];
        }
      }
      
      //        "xxx C\r"
        temperature_discharge[1]=(value_number/100)%10;//xSxx -> 00xS
        temperature_discharge[2]=(value_number/10)%10;//xxSx -> 0xxS
        temperature_discharge[3]=value_number%10;//xxxS -> xxxS
        
        UART2_Send_Char(number_symbols[temperature_discharge[1]]);
        UART2_Send_Char(number_symbols[temperature_discharge[2]]);
        UART2_Send_Char(number_symbols[temperature_discharge[3]]);
        
        UART2_Send_Char(' ');
        UART2_Send_Char('C');
        UART2_Send_Char('\r');
    }
  }
}

/*Functions bodies*/
  void System_Clock_Config(void)
  {
    //Steps
    //1 Flash latency
    //2 Enable HSE and wait for
    //3 PLL multiplication factor
    //4 PLL entry clock source
    //5 Enable PLL and wait for
    //6 Set the prescalers
      //HPRE
      //PPRE1
      //PPRE2
    //7 SW and wait for
  
    //1 Flash latency
    FLASH->ACR|=FLASH_ACR_LATENCY_1;
    
    //2 Enable HSE and wait for
    RCC->CR|=RCC_CR_HSEON;
    while(!(RCC->CR&RCC_CR_HSERDY));
    
    //3 PLL multiplication factor
    RCC->CFGR|=RCC_CFGR_PLLMULL9;
    
    //4 PLL entry clock source
    RCC->CFGR|=RCC_CFGR_PLLSRC;
    
    //5 Enable PLL and wait for
    RCC->CR|=RCC_CR_PLLON;
    while(!(RCC->CR&RCC_CR_PLLRDY));
    
    //6 Set the prescalers
      //HPRE is not divided
      RCC->CFGR&=~RCC_CFGR_HPRE;
      
      //PPRE1 is divided by 2
      RCC->CFGR|=RCC_CFGR_PPRE1_DIV2;
      
      //PPRE2 isn't divided
      RCC->CFGR&=~RCC_CFGR_PPRE2;
      
    //7 SW and wait for
    RCC->CFGR|=RCC_CFGR_SW_PLL;
    while(!(RCC->CFGR&RCC_CFGR_SWS_PLL));
  }

/*ADC2*/
  void ADC2_Config(void)
  {
    //Steps
    //1 Clocks
    //2 Prescaler APB2/6
    //3 Set pins in input mode
    //4 Sampling time
    //5 Sequence length
    //6 Data alingnment
    //7 Interrupts
    //8 Self-calibration
    //9 Enable ADC2
  
    //1 Clocks
    RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR|=RCC_APB2ENR_ADC2EN;
    
    //2 Prescaler APB2/6
    RCC->CFGR|=RCC_CFGR_ADCPRE_DIV6;
    
    //3 Set the pin in input mode
    //PA0
    GPIOA->CRL&=~GPIO_CRL_MODE0;//00
    GPIOA->CRL&=~GPIO_CRL_CNF0;//00
    
    //4 Sampling time
    ADC2->SMPR2|=ADC_SMPR2_SMP0;
    
    //5 Sequence length
    ADC2->SQR1&=~ADC_SQR1_L;
    
    //6 Data alingnment
    ADC2->CR2&=~ADC_CR2_ALIGN;//0 for right alignment
    
    //7 Interrupts
    ADC2->CR1|=ADC_CR1_EOCIE;
    NVIC_SetPriority(ADC1_2_IRQn, 1);
    NVIC_EnableIRQ(ADC1_2_IRQn);
    
    //8 Self-calibration
    ADC2->CR2&=~ADC_CR2_ADON;
    user_delay(5000);
    
    ADC2->CR2|=ADC_CR2_RSTCAL;
    user_delay(5000);
    //while(ADC2->CR2&ADC_CR2_RSTCAL);
    
    ADC2->CR2|=ADC_CR2_CAL;
    while(ADC2->CR2&ADC_CR2_CAL);
    
    //9 Enable ADC2
    ADC2->CR2|=ADC_CR2_ADON;
    user_delay(5000);
  }

void ADC2_Start(char channel)
{
//Steps
//1 Reset SR
//2 Select the channel
//3 Start the conversion

//1 Reset SR
ADC2->SR=0;

//2 Select the channel
ADC2->SQR3=channel;

//3 Start the conversion
ADC2->CR2|=ADC_CR2_ADON;
}

/*I2C2*/
  void I2C2_Config(void)
  {
    //Steps
    //1 Clocks
    //2 Reset I2C2
    //3 Alternate function for pins
    //4 Peripheral clock enable
    //5 Clock control register
    //6 Rise time
    //7 PE
  
    //1 Clocks
    RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR|=RCC_APB1ENR_I2C2EN;
    
    //2 Reset I2C2
    I2C2->CR1|=I2C_CR1_SWRST;
    I2C2->CR1&=~I2C_CR1_SWRST;
    
    //3 Alternate function for pins
      //PB10 as SCL
      GPIOB->CRH|=GPIO_CRH_MODE10;//11: Output mode, max speed 50 MHz.
      GPIOB->CRH|=GPIO_CRH_CNF10;//11: Alternate function output Open-drain
      
      //PB11 as SDA
      GPIOB->CRH|=GPIO_CRH_MODE11;//11: Output mode, max speed 50 MHz.
      GPIOB->CRH|=GPIO_CRH_CNF11;//11: Alternate function output Open-drain
      
    //4 Peripheral clock enable
    I2C2->CR2|=36;
    
    //5 Clock control register
    I2C2->CCR=180;//=0xB4
    
    //6 Rise time
    I2C2->TRISE=36+1;
    
    //7 PE
    I2C2->CR1|=I2C_CR1_PE;
  }

void Get_I2C2_temperature_from_the_LM75_sensor(char address, char data, char * I2C2_Result)
{
  //Steps
  //1 POS? ACK
  //2 Start and wait for
  //3 Send the slave address
  //4 Send the data
  //5 Start and wait for//Restart
  //6 Send the slave address plus the bit for reading
  //7 Read the data
  //8 Stop
  //9 Read the last second byte

  //1 POS? ACK
  I2C2->CR1&=~I2C_CR1_POS;
  I2C2->CR1|=I2C_CR1_ACK;
  
  //2 Start and wait for
  I2C2->CR1|=I2C_CR1_START;
  while(!(I2C2->SR1&I2C_SR1_SB));
  
  //3 Send the slave address
  I2C2->DR=address;
  while(!(I2C2->SR1&I2C_SR1_ADDR));
  I2C2->SR2;
  
  //4 Send the data
  while(!(I2C2->SR1&I2C_SR1_TXE));
  I2C2->DR=data;
  while(!(I2C2->SR1&I2C_SR1_BTF));
  
  //5 Start and wait for//Restart
  I2C2->CR1|=I2C_CR1_START;
  while(!(I2C2->SR1&I2C_SR1_SB));
  
  //6 Send the slave address plus the bit for reading
  I2C2->DR=address+1;
  while(!(I2C2->SR1&I2C_SR1_ADDR));
  I2C2->SR2;
  
  //7 Read the data
  while(!(I2C2->SR1&I2C_SR1_RXNE));
  *(I2C2_temperature+0)=I2C2->DR;
  
  //8 Stop
  I2C2->CR1|=I2C_CR1_STOP;
  
  //9 Read the last second byte
  while(!(I2C2->SR1&I2C_SR1_RXNE));
  *(I2C2_temperature+1)=I2C2->DR;
}

/*UART*/

  void UART2_Config(void)
  {
    //Steps
    //1 Clocks
    //2 Alternate function for pins
    //3 UE
    //4 M bit
    //5 Baud rate
    //6 Enable transmitter/receiver
    //7 Interrupts
    //8 Reset the SR
  
    //1 Clocks
    RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
    RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
    
    //2 Alternate function for pins
    //PA2 as TX
    GPIOA->CRL|=GPIO_CRL_MODE2;//11 as output
    GPIOA->CRL&=~GPIO_CRL_CNF2;//00
    GPIOA->CRL|=GPIO_CRL_CNF2_1;//10
    
    //PA3 as RX
    GPIOA->CRL&=~GPIO_CRL_MODE3;//00 as input
    GPIOA->CRL&=~GPIO_CRL_CNF3;//00
    GPIOA->CRL|=GPIO_CRL_CNF3_0;//01
    
    //3 UE
    USART2->CR1|=USART_CR1_UE;
    
    //4 M bit
    USART2->CR1&=~USART_CR1_M;
    
    //5 Baud rate
    USART2->BRR=0x47; //for baud rate 512000        
    //0x008D;//for baud rate 256000
    
    //6 Enable transmitter/receiver
    USART2->CR1|=USART_CR1_TE;
    USART2->CR1|=USART_CR1_RE;
    
    //7 Interrupts
    USART2->CR1|=USART_CR1_RXNEIE;
    NVIC_SetPriority(USART2_IRQn, 1);
    NVIC_EnableIRQ(USART2_IRQn);
    
    //8 Reset the SR
    USART2->SR=0;
  }

void UART2_Send_Char(char symbol)
{
//Steps
//1 Write the symbol in the DR
//2 Wait for the TC bit to set

//1 Write the symbol in the DR
USART2->DR=symbol;

//2 Wait for the TC bit to set
while(!(USART2->SR&USART_SR_TC));
}

void UART2_Send_String(char * pointer)//"dsfkjlksd\n"
{while(*pointer!='\n')UART2_Send_Char(*pointer++);}

void user_delay(unsigned long wait)
{while(--wait);}
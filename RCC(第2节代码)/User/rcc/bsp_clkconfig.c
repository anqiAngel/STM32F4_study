#include "bsp_clkconfig.h"

void User_SetSysClock(void)
{
/******************************************************************************/
/*            PLL (clocked by HSE) used as System clock source                */
/******************************************************************************/
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  /* Enable HSE */
  // 使能HSE
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
  /* Wait till HSE is ready and if Time out is reached exit */
  // 等待HSE启动稳定,如果超时则退出
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
  // HSE启动成功
  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* Select regulator voltage output Scale 1 mode */
    // 选择电压调节器的模式为1
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
    /* HCLK = SYSCLK / 1*/
    // 配置AHB1总线分频数
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    /* PCLK2 = HCLK / 2*/
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
    /* PCLK1 = HCLK / 4*/
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
    /* Configure the main PLL */
    // 配置主PLL
    RCC->PLLCFGR = 25 | (336 << 6) | (((2 >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSE) | (7 << 24);
    /* Enable the main PLL */
    // 使能PLL
    RCC->CR |= RCC_CR_PLLON;
    /* Wait till the main PLL is ready */
    // 等待主PLL稳定
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
    // 配置flash预取值,指令缓存、数据缓存、等待周期
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
    /* Select the main PLL as system clock source */
    // 选择主PLL作为系统时钟源
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    /* Wait till the main PLL is used as system clock source */
    // 等待PLL被用作系统时钟
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
         // 如果HSE启动失败用户自行在这里添加代码解决
  }
}

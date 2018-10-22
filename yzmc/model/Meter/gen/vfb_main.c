#include "Meter_sys_types.h"

extern bool Escher_run_flag;

extern FUNC(void, RTE_APPL_CODE) ib_Display_ru_Display_Initialize( Rte_Instance self );
extern FUNC(void, RTE_APPL_CODE) ib_LED_ru_LED_Initialize( Rte_Instance self );
extern FUNC(void, RTE_APPL_CODE) ib_Buzzer_ru_Buzzer_Initialize( Rte_Instance self );
extern FUNC(void, RTE_APPL_CODE) ib_Meter_ru_Meter_Initialize( Rte_Instance self );
extern FUNC(void, RTE_APPL_CODE) ib_SignalBlock_ru_SignalBlock_Initialize( Rte_Instance self );

extern FUNC(void, RTE_APPL_CODE) ib_Display_ru_DisplayTimer( Rte_Instance self );
extern FUNC(void, RTE_APPL_CODE) ib_LED_ru_LEDTimer( Rte_Instance self );
extern FUNC(void, RTE_APPL_CODE) ib_Buzzer_ru_BuzzerTimer( Rte_Instance self );
extern FUNC(void, RTE_APPL_CODE) ib_Meter_ru_MeterTimer( Rte_Instance self );
extern FUNC(void, RTE_APPL_CODE) ib_SignalBlock_ru_SignalBlockTimer( Rte_Instance self );

int main( int argc, char ** argv )
{
  ib_Display_ru_Display_Initialize(0);
  ib_LED_ru_LED_Initialize(0);
  ib_Buzzer_ru_Buzzer_Initialize(0);
  ib_Meter_ru_Meter_Initialize(0);
  ib_SignalBlock_ru_SignalBlock_Initialize(0);

  // Cause the internal clocks of each component to tick
  while ( true == Escher_run_flag ) {
	  ib_Display_ru_DisplayTimer(0);
	  ib_LED_ru_LEDTimer(0);
	  ib_Buzzer_ru_BuzzerTimer(0);
	  ib_Meter_ru_MeterTimer(0);
	  ib_SignalBlock_ru_SignalBlockTimer(0);
  }

  return 0;
}


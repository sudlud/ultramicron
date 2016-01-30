#ifndef __services_user_H
#define __services_user_H

void Pump_now(FunctionalState);
void check_wakeup_keys(void);
FunctionalState check_license(void);
float convert_mkr_sv(uint32_t);
void recalculate_fon(void);
void RTC_tick_processing(void);
void sleep_mode(FunctionalState);
void geiger_calc_fon(void);

#endif

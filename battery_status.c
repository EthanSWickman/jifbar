#include <stdio.h>
#include <string.h>

#include "battery_status.h"

void SetBatteryString(char* batteryString) {
  FILE* openFile = fopen("/sys/class/power_supply/BAT0/capacity","r");
  
  char battPercentage[5];

  fgets(battPercentage, 3, openFile);

  if (battPercentage[strlen(battPercentage) - 1] == '\n') {
    battPercentage[strlen(battPercentage) - 1] = '\0';
  }

  fclose(openFile);

  openFile = fopen("/sys/class/power_supply/BAT0/status", "r");

  int battStatus = fgetc(openFile);

  fclose(openFile); 

  if (battStatus == 'C') {
    strcat(battPercentage, "%+");
  }
  else if (battStatus == 'D') {
    strcat(battPercentage, "%-");
  }
  else {
    strcat(battPercentage, "%*");
  }

  strcpy(batteryString, battPercentage);
} 
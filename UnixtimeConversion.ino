/* This sketch was created in order to convert the time given by a DS3231 RTC to unixtime, when using the DS1307
library. It requires a large number of variables to overcome the ATMEGAs inherent weekness for certain calculations.
The Scripts accuracy can be tested against http://www.epochconverter.com.

Created March 28, 2015
By Kevin Fundarek

GPU license. 
*/


#include <Wire.h>
#include <DS1307.h>
#include <math.h>

int rtc[7];
unsigned long Current_Time;
int Months_Past;
int Days_From_Months;
int Year_Type;
int Leap_Year_Correction_Factor;
float Past_Days;
unsigned long Past_Seconds;
unsigned long Current_Seconds;
unsigned long Total_Seconds;
unsigned long Seconds_From_Hours;
unsigned long Hour_In_Minutes;
int Seconds_From_Minutes;
int Hour;
int DST_Correction_Factor;
int Days_Since[] = {0, 31, 59, 90, 120, 151, 
                    181, 212, 243, 273, 304, 334};


void setup()
{
  Serial.begin(9600);
  /*
  RTC.stop();
  RTC.set(DS1307_SEC,1);
  RTC.set(DS1307_MIN,23);
  RTC.set(DS1307_HR,12);
  RTC.set(DS1307_DOW,1);
  RTC.set(DS1307_DATE,1);
  RTC.set(DS1307_MTH,10);
  RTC.set(DS1307_YR,7);
  RTC.start();
  */
}

void loop()
{
  RTC.get(rtc,true);

  
  //Create variable to account for current year being a leap year 
  int Year_Type = (rtc[6] % 4);
  if (Year_Type == 0){
     Leap_Year_Correction_Factor = 1;
    }
  else
    {
    Leap_Year_Correction_Factor = 0;
    }
  
  //Create variable to define number of days elapsed in previous months 
  Months_Past = (rtc[5] - 1);
  Days_From_Months = Days_Since[Months_Past];

   //Create variable to correct for US Day light savings time
  if (rtc[6] == 2015 && (Days_From_Months + rtc[4]) >= 67 && (Days_From_Months + rtc[4]) <= 305){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2016 && (Days_From_Months + rtc[4]) >= 73 && (Days_From_Months + rtc[4]) <= 311){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2017 && (Days_From_Months + rtc[4]) >= 71 && (Days_From_Months + rtc[4]) <= 309){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2018 && (Days_From_Months + rtc[4]) >= 70 && (Days_From_Months + rtc[4]) <= 308){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2019 && (Days_From_Months + rtc[4]) >= 69 && (Days_From_Months + rtc[4]) <= 307){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2020 && (Days_From_Months + rtc[4]) >= 68 && (Days_From_Months + rtc[4]) <= 306){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2021 && (Days_From_Months + rtc[4]) >= 73 && (Days_From_Months + rtc[4]) <= 311){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2022 && (Days_From_Months + rtc[4]) >= 72 && (Days_From_Months + rtc[4]) <= 310){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2023 && (Days_From_Months + rtc[4]) >= 71 && (Days_From_Months + rtc[4]) <= 309){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2024 && (Days_From_Months + rtc[4]) >= 70 && (Days_From_Months + rtc[4]) <= 308){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2025 && (Days_From_Months + rtc[4]) >= 68 && (Days_From_Months + rtc[4]) <= 306){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2026 && (Days_From_Months + rtc[4]) >= 67 && (Days_From_Months + rtc[4]) <= 305){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2027 && (Days_From_Months + rtc[4]) >= 73 && (Days_From_Months + rtc[4]) <= 311){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2028 && (Days_From_Months + rtc[4]) >= 72 && (Days_From_Months + rtc[4]) <= 310){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2029 && (Days_From_Months + rtc[4]) >= 70 && (Days_From_Months + rtc[4]) <= 308){
    DST_Correction_Factor = 3600;
    }
  else if (rtc[6] == 2030 && (Days_From_Months + rtc[4]) >= 69 && (Days_From_Months + rtc[4]) <= 307){
    DST_Correction_Factor = 3600;
    }
  else {
    DST_Correction_Factor = 0;
    }


  Past_Days = (((rtc[6] - 1970) * 365.25) + Days_From_Months +(rtc[4] - 1) + Leap_Year_Correction_Factor);
  Past_Seconds = (Past_Days * 86400);
  Hour = (rtc[2] - 1);
  Hour_In_Minutes = (Hour * 60);
  Seconds_From_Hours = (Hour_In_Minutes * 60);
  Seconds_From_Minutes = (rtc[1] * 60);
  Current_Seconds = (Seconds_From_Hours + Seconds_From_Minutes + rtc[0]);
  Total_Seconds = (Past_Seconds + Current_Seconds); 
  Current_Time = (Total_Seconds - DST_Correction_Factor);

  Serial.print(Current_Time);
  Serial.println();


  delay(1000);

}
 

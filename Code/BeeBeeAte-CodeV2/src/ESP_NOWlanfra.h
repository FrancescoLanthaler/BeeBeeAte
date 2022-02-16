#ifndef ESP_NOW_H
#define ESP_NOW_H

extern void SetupESPNOW();
extern void sendESPNOW();

// Empfangene Daten
extern int receive_Richtung;
extern int receive_Wert;
#endif
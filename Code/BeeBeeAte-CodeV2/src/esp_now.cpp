#include <Arduino.h>
#include <esp_now.h>
#include <ESP_NOWlanfra.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0x4C, 0xA0, 0x8C}; // Mac-Adresse

// Empfangene Daten
int receive_Richtung;
int receive_Wert;

String success; // Senden erfolgreich

// Struktur des Austausches
typedef struct struct_message
{ // Status, Wert
  int Richtung;
  int Wert;
} struct_message;

struct_message receive_Data; // Create a struct_message to receive data.

// Callback when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  receive_Richtung = receive_Data.Richtung;
  receive_Wert = receive_Data.Wert;
}

void SetupESPNOW()
{
  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv); //--> Register for a callback function that will be called when data is received
}

void sendESPNOW()
{
  Serial.println(receive_Richtung);
  Serial.println(receive_Wert);
  delay(5000);
}
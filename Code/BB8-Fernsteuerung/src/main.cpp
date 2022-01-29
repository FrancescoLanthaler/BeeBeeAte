#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x78, 0xE3, 0x6D, 0x15, 0xF0, 0x70}; // Mac-Adresse

// zu sendende Variablen
int send_Status;
int send_Wert;

// Empfangene Daten
int receive_Status;
int receive_Wert;

String success; // Senden erfolgreich

// Struktur des Austausches
typedef struct struct_message
{ // Status, Wert
  int Status;
  int Wert;
} struct_message;

struct_message send_Data; // Create a struct_message to send data.

struct_message receive_Data; // Create a struct_message to receive data.

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  if (status == 0)
  {
    success = "Delivery Success :)";
  }
  else
  {
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  receive_Status = receive_Data.Status;
  receive_Wert = receive_Data.Wert;
}

void setup()
{
  Serial.begin(9600);

  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

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

void loop()
{
  // Set values to send
  send_Status = random(256, 555);
  send_Wert = random(0, 255);         //Werden im fertigen Program außerhalb definiert
  send_Data.Status = send_Status;
  send_Data.Wert = send_Wert;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&send_Data, sizeof(send_Data));

  if (result != ESP_OK)
  {
    Serial.println("Error sending the data");
  }
  Serial.println(receive_Status);
  Serial.println(receive_Wert);
  delay(5000);
}
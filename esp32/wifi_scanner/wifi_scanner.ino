#include "WiFi.h"

void setup() {
  Serial.begin(115200);

  // Define o modo do Wi-Fi como estação (WIFI_STA)
  WiFi.mode(WIFI_STA); 
  // Desconecta-se de qualquer rede anterior para garantir que o scan funcione corretamente
  WiFi.disconnect();
  delay(100);

  Serial.println("Iniciando a varredura de redes Wi-Fi...");
}

void loop() {
  Serial.println("Scan iniciado.");
/*
  // O WiFi.scanNetworks retorna o número de redes encontradas
  int n = WiFi.scanNetworks();
  Serial.println("Scan finalizado.");

  if (n == 0) {
    Serial.println("Nenhuma rede encontrada.");
  } else {
    Serial.print(n);
    Serial.println(" redes encontradas:");
    for (int i = 0; i < n; ++i) {
      // Exibe os dados de cada rede
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i)); // Nome da rede
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i)); // Intensidade do sinal em dBm
      Serial.print(" dBm)");
      
      // Exibe o tipo de criptografia
      printEncryptionType(WiFi.encryptionType(i));
      
      Serial.println();
    }
  }
  
  // Exclui os resultados para liberar memória
  WiFi.scanDelete();
  
  // Aguarda 5 segundos antes de fazer uma nova varredura
  delay(5000);
}

// Função auxiliar para imprimir o tipo de criptografia
void printEncryptionType(wifi_auth_mode_t encryptionType) {
  switch (encryptionType) {
    case WIFI_AUTH_OPEN:
      Serial.print(" [Aberto]");
      break;
    case WIFI_AUTH_WEP:
      Serial.print(" [WEP]");
      break;
    case WIFI_AUTH_WPA_PSK:
      Serial.print(" [WPA_PSK]");
      break;
    case WIFI_AUTH_WPA2_PSK:
      Serial.print(" [WPA2_PSK]");
      break;
    case WIFI_AUTH_WPA_WPA2_PSK:
      Serial.print(" [WPA/WPA2_PSK]");
      break;
    case WIFI_AUTH_WPA2_ENTERPRISE:
      Serial.print(" [WPA2_ENTERPRISE]");
      break;
    case WIFI_AUTH_WPA3_PSK:
      Serial.print(" [WPA3_PSK]");
      break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
      Serial.print(" [WPA2/WPA3_PSK]");
      break;
    default:
      Serial.print(" [Desconhecido]");
      break;
  }
  */
  delay(10000);
}

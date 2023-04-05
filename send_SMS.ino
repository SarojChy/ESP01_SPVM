void sendSMS() {


  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  //      String url = "/trigger/NoPadAvailable/json/with/key/cka51GGRNGQmk8KBWBE56L";
  //  Serial.print("Requesting URL: ");
  //      Serial.println(url);

  client.print(String("GET ") + uid.c_str() + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(1000);
}

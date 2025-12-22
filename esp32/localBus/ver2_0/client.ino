String curl_GET(String url){
  String payload = "";
  int httpResponseCode = 0;
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(url);
    http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      payload = http.getString();
    }
    http.end();
  }
  String out = "{\"code\":"+String(httpResponseCode)+",\"payload\":"+payload+"}";
  return out;
}

String curl_POST(String url, String params){  
  String payload = "";
  int httpResponseCode = 0;
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(url);
    http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpResponseCode = http.POST(params);
    if (httpResponseCode > 0) {
      payload = http.getString();
    }
    http.end();
    payload = payload=="" ? "[]" : payload;
  }
  String out = "{\"code\":"+String(httpResponseCode)+",\"payload\":"+payload+"}";
  return out;
}
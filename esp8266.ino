#include <SoftwareSerial.h>                                  
#include <LiquidCrystal.h>

LiquidCrystal lcd (13,12,4,5,6,7);

String agAdi = "YOUR_NETWORK_NAME";       
String agSifresi = "YOUR_NETWORK_PASSWORD";                       

int rxPin = 10;                                               
int txPin = 11;                                               

int current_mode = 0;

int delay_value = 1000;

String ip = "184.106.153.149";   
SoftwareSerial esp(rxPin, txPin);     
void setup() {                                            
  lcd.begin(16,2);
  Serial.begin(9600);                            
  Serial.println("Başlatılıyor");
  esp.begin(115200);                                                                      
  esp.println("AT");                                   
  Serial.println("AT Gönderildi");
  lcd.print("AT Gonderildi.");
  while(!esp.find("OK")){                                  
    esp.println("AT");
    Serial.println("ESP8266 ile iletişim kurulamadı.");
  }
  lcd.clear();
                 
  Serial.println("OK Komutu Alındı");
  esp.println("AT+CWMODE=1");                             
  lcd.print("Modul Ayari.");
  while(!esp.find("OK")){                                 
    esp.println("AT+CWMODE=1");
    Serial.println("Modül Ayarı Yapılıyor....");
  }
  lcd.clear();
  Serial.println("Modül Client olarak ayarlandı");
  Serial.println("Ağa Baglaniliyor...");
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");  
  lcd.print("Aga baglaniliyor.");
  while(!esp.find("OK"));                                   
  Serial.println("Ağa Bağlanıldı.");
  lcd.clear();
  lcd.print("Aga baglanildi");
  delay(1000);
  lcd.clear();

}

void loop() {
  
  esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");     
  if(esp.find("Error")){                                  
    Serial.println("AT+CIPSTART Error");
  }
  if(current_mode == 0){
    lcd.setCursor(4,1);
    lcd.print(Time());
    lcd.setCursor(6,0);
    lcd.print("Saat");
    
  }
  else if(current_mode == 1){
    lcd.setCursor(3,1);
    lcd.print(covid_cases());
    lcd.setCursor(3,0);
    lcd.print("Covid Vaka");
    
  }
  else if(current_mode == 2){
    lcd.setCursor(2,1);
    lcd.println(covid_deaths());
    lcd.setCursor (2,0);
    lcd.print("Covid Olum");

  }
  else if(current_mode == 3){
     lcd.setCursor(4,1);
    lcd.println(altin());
    lcd.setCursor(5,0);
    lcd.print("Altin");
  }
  else if(current_mode == 4){
    lcd.setCursor(4,1);
    lcd.print(dolar());
    lcd.setCursor(5,0);
    lcd.print("Dolar");
  }
  else if(current_mode == 5){
    lcd.setCursor(5,1);
    lcd.print(euro());
    lcd.setCursor(6,0);
    lcd.print("Euro");
  }

           
  delay(3000);
  current_mode+=1;
  if(current_mode > 5){
    current_mode = 0;
  }
  lcd.clear(); 
  
}
String Time()
{

  String rest = "AT+CIPSEND=90";
  rest += "\r\n";
  sendData(rest, delay_value, 0);


  String hostt = "GET /apps/thinghttp/send_request?api_key=1VGXJR2KPHCLQ2AP";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Time = sendData(hostt, delay_value, 0); 
  
 int index=Time.indexOf("<noscript>");
 int other_index = Time.indexOf("</noscript>");
 Time = Time.substring(index+10,other_index);

  return (Time);

  
}

String altin()
{

 

  String rest = "AT+CIPSEND=90";
  rest += "\r\n";
  sendData(rest, delay_value, 0); 


  String hostt = "GET /apps/thinghttp/send_request?api_key=DXZO3J2RS04POBIP";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Altin = sendData(hostt, delay_value, 0);  

 int index=Altin.indexOf("<span");
 int other_index = Altin.indexOf("</span>");
  Altin = Altin.substring(index+23,other_index);

  return (Altin);

  
}

String covid_deaths(){
  String rest = "AT+CIPSEND=90";
  rest += "\r\n";
  sendData(rest, delay_value, 0); 


  String hostt = "GET /apps/thinghttp/send_request?api_key=CN339ON8L48HM1DL";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Nufus = sendData(hostt, delay_value, 0); 
  
 int index=Nufus.indexOf(':');
  Nufus = Nufus.substring(index+1,index+9);
  return (Nufus);
}

String covid_cases()
{

 

  String rest = "AT+CIPSEND=90";
  rest += "\r\n";
  sendData(rest, delay_value, 0); 


  String hostt = "GET /apps/thinghttp/send_request?api_key=4SZMGA8ZTL4X9EX2";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Nufus = sendData(hostt, delay_value, 0);  
  
 int index=Nufus.indexOf(':');
  Nufus = Nufus.substring(index+1,index+11);
  return (Nufus);

  
}

String dolar(){
    String rest = "AT+CIPSEND=90";
  rest += "\r\n";
  sendData(rest, delay_value, 0); 


  String hostt = "GET /apps/thinghttp/send_request?api_key=KZLW40GKMM387198";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Nufus = sendData(hostt, delay_value, 0); 

 int index=Nufus.indexOf("<span");
 int other_index = Nufus.indexOf("</span>");
 Nufus = Nufus.substring(index+23,other_index);
  
  return (Nufus);
}

String euro(){
    String rest = "AT+CIPSEND=90";
  rest += "\r\n";
  sendData(rest, delay_value, 0); 


  String hostt = "GET /apps/thinghttp/send_request?api_key=8C9627VWDLK2Z5YZ";
  hostt += "\r\n";
  hostt += "Host:api.thingspeak.com";
  hostt += "\r\n\r\n\r\n\r\n\r\n";
  String Nufus = sendData(hostt, delay_value, 0);
  
 int index=Nufus.indexOf("<span");
 int other_index = Nufus.indexOf("</span>");
 Nufus = Nufus.substring(index+23,other_index);
  
  return (Nufus);
}


String sendData(String komut, const int zamangecen, boolean debug)
{
  String response = "";

  esp.print(komut); 

  long int Zaman = millis();

  while ( (Zaman + zamangecen) > millis())
  {
    while (esp.available())
    {

    
      char c = esp.read(); 
      response += c; 
    }
  }

  if (debug)
  {
    Serial.print(response);
  }
  
  return response;
}

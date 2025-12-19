  /* EEPROM FUNCTIONS  */


void gravar(int endereco,String dados){
  
  Serial.println(dados);
  Serial.println("****** INICIA GRAVAÇÃO ******");

  int tam = dados.length();
  EEPROM.begin(endereco+tam+1);

  for(int i=0; i < tam; i++){
     EEPROM.write(endereco+i, dados[i]);    
  }

  EEPROM.write(endereco+tam, 0xff);
  EEPROM.commit();//Salva o dado na EEPROM.  
  EEPROM.end();  

  Serial.println("Dado salvo na EEPROM.");
  
}

void gravar_hex(int endereco, String valor){
    byte b = (byte) strtoul(valor.c_str(), nullptr, 16);
    EEPROM.begin(4096);
    EEPROM.write(endereco, b);  
    EEPROM.end();
}

String ler(int endereco){
  String resp = "";
  EEPROM.begin(4096);  
  int i = endereco;
  int ascii = EEPROM.read(i);

  while(ascii < 0xff){
    resp += char(ascii);
    i++;
    ascii = EEPROM.read(i);    
  }

  EEPROM.end();
  return resp;
}

int ler_hex(int endereco){
  EEPROM.begin(4096);  
  int resp = EEPROM.read(endereco);
  EEPROM.end();
  return resp;
}


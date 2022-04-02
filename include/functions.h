/*******************************************************
 * By Chema'22 v0.6RC
 * 
 * Autómata para Seritrade
 * 
 * Funciones del programa
 * 
 * los endstops están a gnd (LOW) en not triguered
 * se desconectan al activarse, como tenemos un pullup
 * en estas entradas, está en HIGH (true) al activarse
 * 
 * VF2 => arriba/abajo
 * VF1 => delante/detrás
 *
 * 
 * *****************************************************/

void leebotonera(){

  //pedalval=!digitalRead(pedal); //pedal 
  int reading=!digitalRead(pedal); //pedal 
  if(reading != lastP){
      lastDebounceTP=millis();
      lastP=reading;
  }
  if((millis()-lastDebounceTP)>=debounceDelay){
      if(reading != pedalval){
          pedalval=reading;
          //cambios=true;
      }
  }

  //hval=!digitalRead(horz); //boton delante/detrás
  reading = !digitalRead(horz); //boton delante/detrás
  //if(hval != lasthval){
  if(reading != lasthval){
      lastDebounceTh=millis();
      lasthval=reading;
  }
  if((millis()-lastDebounceTh)>=debounceDelay){
      if (reading != hval){
        hval = reading;
        //lasthval = hval;
        //cambios=true;
      }
  }
  reading=!digitalRead(vert);
  //vval=!digitalRead(vert); //botón subir/bajar
  //if(vval != lastvval){
  if(reading != lastvval){
      lastDebounceTv=millis();
      lastvval=reading;
  }
  if((millis()-lastDebounceTv)>=debounceDelay){
      if(reading != vval){
          vval=reading;
          //lastvval=vval;
          //cambios=true;
      }
  }
    reading=!digitalRead(lbutt); //boton limpieza
    //limpieza=!digitalRead(lbutt); //boton limpieza
  if(reading != lastlimpieza){
      lastDebounceLP=millis();
      lastlimpieza=reading;
  }
  if((millis()-lastDebounceLP)>=debounceDelay){
      if(reading != limpieza){
          limpieza=reading;
          cambios=true;
      }
  }
    reading=!digitalRead(semibutt); //botón semiauto
    //semiauto=!digitalRead(semibutt); //botón semiauto
  if(reading != lastsemiauto){
      lastDebounceSE=millis();
      lastsemiauto=reading;
  }
  if((millis()-lastDebounceSE)>=debounceDelay){
      if(reading != semiauto){
          semiauto=reading;
          cambios=true;
      }
  }

}
void printa()
{
  //Serial.println("********************************************************************");
  Serial.print(" Front: ");
  Serial.print(frontval);
  Serial.print(" Back: ");
  Serial.print(backval);
  Serial.print(" Up: ");
  Serial.print(upval);
  Serial.print(" Dw: ");
  Serial.print(downval);
  Serial.print(" BV: ");
  Serial.print(vval);
  Serial.print(" BH: ");
  Serial.print(hval);
  Serial.print(" P: ");
  Serial.print(pedalval);
  Serial.print(" P2: ");
  Serial.print(pedal2);
  Serial.print(" movement: ");
  switch (movement)
  {
  case PABAJO:
      Serial.print("2DOWN");
      break;
  case PARRIBA:
      Serial.print("2UP");
      break;
  case PALANTE:
      Serial.print("2FRONT");
      break;
  case PATRAS:
      Serial.print("2BACK");
      break;
  case PARADO:
      Serial.print("PARADO");
      break;
  }
  
  Serial.print(" posit: ");
  switch (position)
  {
  case ATRAS_ARRIBA:
      Serial.print("atras-arriba");
      break;
  case ATRAS_ABAJO:
      Serial.print("atras-abajo");
      break;
  case DELANTE_ABAJO:
      Serial.print("delante-abajo");
      break;
  case DELANTE_ARRIBA:
      Serial.print("delante-arriba");
      break;
  }
  Serial.print(" Limp: ");
  Serial.print(limpieza);
  Serial.print(" Semi: ");
  Serial.println(semiauto);
  //delay(2000);
}
void leestops(){
    //int posv=0;
    //int posh=0;
  //upval=!digitalRead(endup); //endstops
  int reading=!digitalRead(endup);
    //Serial.print(reading);
  if(reading != lastupval){
      lastDebounceUP=millis();
      lastupval=reading;
  }
  if((millis()-lastDebounceUP) >= debounceDelayS){
      if(reading != upval){
          upval=reading;
          //cambios=true;
          //position-=1;
          //if(upval) posv=0;
      }
  }


  //downval=!digitalRead(enddown);
  reading=!digitalRead(enddown);
    //Serial.print(reading);
  if(reading != lastdownval){
      lastDebounceDW=millis();
      lastdownval=reading;
  }
  if((millis()-lastDebounceDW)>=debounceDelayS){
      if(reading != downval){
          downval=reading;
          //cambios=true;
          //position+=1;
          //if(downval) posv=1;
      }
  }



  //(upval || downval) ? movev = false : movev = true;

  //frontval=digitalRead(endfront);
  reading=digitalRead(endfront);
    //Serial.print(reading);
  if(reading != lastfrontval){
      lastDebounceFR=millis();
      lastfrontval=reading;
  }
  if((millis()-lastDebounceFR)>=debounceDelayS){
      if(reading != frontval){
          frontval=reading;
          //cambios=true;
          //position+=2;
          //if(frontval) posh=2;
      }
  }



  //backval=digitalRead(endback);
    reading=digitalRead(endback);
    //Serial.println(reading);
  if(reading != lastbackval){
      lastDebounceFR=millis();
      lastbackval=reading;
  }
  if((millis()-lastDebounceBK)>=debounceDelayS){
      if(reading != backval){
          backval=reading;
          //cambios=true;
          //position-=2;
         // if(backval) posh=0;
      }
  }
  //if (cambios) position=posh+posv;
    position=0;
    if(downval) position+=1;
    if(frontval) position+=2;
}
void mueveVF1(uint8_t direc){
    // movemos VF1 hacia direc, true=delante
    digitalWrite(VF1dir,direc);
    digitalWrite(VF1speed,direc);
    digitalWrite(VF1p,activa);
    (direc) ? movement = PALANTE : movement = PATRAS;
    if(DEBUG) Serial.println(movement);
    cambios=true;
    
}
void para(uint8_t motor){
    // si motor=true VF1 else VF2
    if(motor) {
        digitalWrite(VF1p,apaga);
        //moveh=false;
        movement=PARADO;
    }else{
        digitalWrite(VF2p,apaga);
        //movev=false;
        movement=PARADO;
    }
    cambios=true;
}
void mueveVF2(uint8_t direc)
{
    // movemos VF2 hacia direc, true=arriba
    digitalWrite(VF2dir,direc);
    digitalWrite(VF2p,activa);
    if(direc) { 
        movement = PARRIBA;
     }else{
         movement = PABAJO;
     }
    if(DEBUG) Serial.println(movement);
    cambios=true;

}
void valvulas(uint8_t sentido){
    if (sentido){
        // true es estaba imprimiendo asi que vamos a recoger
        digitalWrite(air1,HIGH);
        if(DEBUG) Serial.print(" aire1 apagado ");
        digitalWrite(air2,LOW);
        if(DEBUG) Serial.println("aire2 encendido");
    }else{
        //false es estaba recogiendo así que vamos a printar
        digitalWrite(air1,LOW);
        if(DEBUG) Serial.println("aire1 encendido");
        digitalWrite(air2,HIGH);
        if(DEBUG) Serial.print(" aire2 apagado ");
        
    }
}


void checkbut(void){
 
    if(semiauto){ //el selector manual/semi está en semi
       // if(!movement){   //y estamos parados
       if(movement) position=99;
            // para saber si se acaba de pulsar pedal uso una 2a variable de estado
            if(pedalval){
                if(!pedal2){ //se acaba de pulsar el pedal
                    if (position==ATRAS_ARRIBA){ //está en la posición correcta... empezamos el workflow
                    pedal2=true;
                    mueveVF2(TODOWN);
                    //cambios=true;
                    }
                }


            }else if(pedal2){ //el else hace que no inicie hasta que suelte el pedal
                switch (position) {
                case ATRAS_ARRIBA:
                    //atras arriba fin
                    pedal2=false;
                    break;
                case ATRAS_ABAJO:
                    //atras abajo
                    mueveVF1(TOFRONT);
                    break;
                case DELANTE_ARRIBA:
                    //delante arriba
                    //Pausa???????????????????????????
                    if(pausado3){ // ya hemos pasado por esto, comprobar time
                        unsigned long currentm=millis();
                        if(currentm-timePause3 >= timePauseVal){
                            mueveVF1(TOBACK);
                            pausado3 = false;
                        }
                    }else{
                        pausado3=true;
                        timePause3=millis();
                    }
                    
                    break;
                case DELANTE_ABAJO:
                    //delante abajo
                    if(DEBUG) Serial.print(" estamos para parar ");
                    if(DEBUG) Serial.print(pausado2);
                    if(pausado2){ // ya hemos pasado por esto, comprobar time
                        unsigned long currentm=millis();
                        if(DEBUG) Serial.print("estamos esperando");
                        if(currentm-timePause2 >= timePauseVal){
                            mueveVF2(TOUP);
                            pausado2 = false;
                            if(!limpieza) valvulas(true);
                        }
                    }else{
                        if(DEBUG) Serial.print("estamos pausando");
                        pausado2=true;
                        timePause2=millis();
                    }                    
                    
                    break;
                default:
                    // si entra aquí, estamos en movimiento o 99
                    break;
                }
            }
       // }
    }else{ //no estamos semiauto
        if(hval){
            //Serial.println("pulsado H");
            if(!paradah){ //final recorrido se para
                if(movement==0){ //inicia movimiento
                    switch (position)
                    {
                    case ATRAS_ARRIBA:
                    case ATRAS_ABAJO:
                        mueveVF1(TOFRONT);
                        //cambios=true;
                        break;
                    case DELANTE_ABAJO:
                        //nada bueno aqui
                        break;
                    case DELANTE_ARRIBA:
                        mueveVF1(TOBACK);
                        //cambios=true;
                        break;
                    }
                }
            }
        }else{ 
            if(movement >= 3) para(VF1);
            //para(VF1);
            //if(paradah) 
            paradah=false;
            //cambios=true;
        }
        
        if(vval){
            if(paradav==false){ //final de recorrido quiero que pare
                if(movement==0){ //inicia movimiento
                    //cambios=true;
                    switch (position)
                    {
                    case ATRAS_ARRIBA: 
                    case DELANTE_ARRIBA:
                        mueveVF2(TODOWN);
                        break;
                    case ATRAS_ABAJO: 
                    case DELANTE_ABAJO:
                        mueveVF2(TOUP);
                        break;
                    }
                }

            }
        }else{
            if(movement==1 || movement==2) para(VF2);
            //para(VF2);
            if(paradav) paradav=false;
            //cambios=true;
        }
    }
}

void sensorLanaPecho () { // Funcion donde esta el sensado

  sensorValue = analogRead(analogInPin); // Lectura sensor
  filteredSensorValue = adcFilter1.filter(sensorValue);

  //Serial.print("sensorValue : ");
  //Serial.println(sensorValue);

  //Serial.print("sensorValue : ");
  //Serial.println(filteredSensorValue);

  Serial.print("sensorValue : ");
  Serial.print(sensorValue);
  Serial.print(",");

  Serial.print("sensorValue : ");
  Serial.print(filteredSensorValue);
  Serial.print(",");

  // calculate the means of the misDatosMax y misDatosMin // el promedio

  for (int i = 0; i < (sizeof(misDatosMax) / sizeof(misDatosMax[0])); i++) {
    moyenneMax = misDatosMax[i] + moyenneMax;
  }
  
  moyenneMax = moyenneMax / (sizeof(misDatosMax) / sizeof(misDatosMax[0]));
  
  Serial.print("Moyenne Max : ");
  Serial.println(moyenneMax);

  for (int i = 0; i < (sizeof(misDatosMin) / sizeof(misDatosMin[0])); i++) {
    moyenneMin = misDatosMin[i] + moyenneMin;
  }
  
  moyenneMin = moyenneMin / (sizeof(misDatosMin) / sizeof(misDatosMin[0]));

  Serial.print("Moyenne Min : ");
  Serial.println(moyenneMin);

  // autoAdjust();  // En caso sensorValue is outside the range seen during calibration, add that value to a spot in the misDatosMin or misDatosMax arrays 

  filteredSensorValue = constrain(filteredSensorValue, moyenneMin, moyenneMax);
  outputValue = map(filteredSensorValue, moyenneMin, moyenneMax, 1, 10); // Mapeo con el promedio de misDatosMax y Min
  
  Serial.print("outputValue : ");
  Serial.println(outputValue);

  if (outputValue >= 3 )//si es mayor que el umbral
  {
    digitalWrite (LED_BUILTIN, HIGH);//prendo led
    datoL2 = 2;//guardo dato
  //  Serial.println("breathing in <<<<<<<<<<<<<<<<<<<<< ");
  }
  else if (outputValue < 3  )//si es menor que el umbral
  {
    digitalWrite (LED_BUILTIN, LOW);//apago led
    datoL2 = 1;//guardo dato
  //  Serial.println("<<<<<<<<<<<<<<<<<< breathing out");
  }

  counter++;
    
  if (counter == (sizeof(misDatosMax) / sizeof(misDatosMax[0]))) {
    counter = 0; // Reset
  }
  Serial.print("counter : ");
  Serial.println(counter);

  moyenneMin = 0; // Reset los promedios
  moyenneMax = 0; 
}

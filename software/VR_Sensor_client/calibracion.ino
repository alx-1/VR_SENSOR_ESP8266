
void calibracion () {

  //Serial.println(" ");
  //Serial.println("Calibración...");

  while (numberofMeasures < 150) {

    sensorValue = analogRead(analogInPin); // Lectura del sensor
    filteredSensorValue = adcFilter1.filter(sensorValue);
    
  //  Serial.print("sensorValue :");
  //  Serial.println(sensorValue);

    // record the maximum sensor value // from https://www.arduino.cc/en/Tutorial/BuiltInExamples/Calibration
    if (filteredSensorValue > sensorMax) {
      sensorMax = filteredSensorValue;
    }

    // record the minimum sensor value
    if (filteredSensorValue < sensorMin) {
      sensorMin = filteredSensorValue;
    }

    numberofMeasures++;
    //Serial.print("numberofMeasures :");
    //Serial.println(numberofMeasures);

    delay(100);

  }

  // write values to the arrays
  for (int i = 0; i < (sizeof(misDatosMax) / sizeof(misDatosMax[0])); i++) {
    misDatosMax[i] = sensorMax;
  }

  for (int i = 0; i < (sizeof(misDatosMin) / sizeof(misDatosMin[0])); i++) {
    misDatosMin[i] = sensorMin;
  }

  // populate the cyclePositionDetect array with the ultimate reading of sensorValue
  //  for (int i = 0; i < (sizeof( cyclePositionDetect) / sizeof( cyclePositionDetect[0])); i++) {
  //    cyclePositionDetect[i] = sensorValue;
  //  }

  storedSensorValue = filteredSensorValue;
  
  calibrate = 0; // calibración completa

//  Serial.println(" ");
//  Serial.print("sensorMax : ");
//  Serial.println(sensorMax);
//  Serial.print("sensorMin : ");
//  Serial.println(sensorMin);
//  Serial.println(" ");
//  Serial.println("----- Calibración completa -----");
//  Serial.println(" ");

}

//void autoAdjust() {
//
//  // we need to determine where we are in the cycle in order to adjust max and min if needed
//  // this needs to be refined with a promedia of the last x values and then we add one to the sensorMin and sensorMax arrays
//  // subtract two incoming values to find out where we are in the cycle
//  // If bias has changed, ajoute la sensorValue min ou max
//
//  cyclePositionDetect[unCompteur] = sensorValue;
//
//  for (int i = 0; i < (sizeof( cyclePositionDetect) / sizeof( cyclePositionDetect[0])); i++) {
//    monTotal =  cyclePositionDetect[i] + monTotal;
//  }
//
//  maMoyenne = monTotal / (sizeof( cyclePositionDetect) / sizeof( cyclePositionDetect[0])); // Fait la moyenne
//
//  monTotal = 0; // Remise de monTotal à 0
//
//  unCompteur++;
//
//  if (unCompteur == (sizeof( cyclePositionDetect) / sizeof( cyclePositionDetect[0]))) {
//    unCompteur = 0;
//  }
//
//  maDiff = maMoyenne - viejaMoyenne;   // compare ma moyenne
//
//  Serial.print("Ma différence : ");
//  Serial.println(maDiff);
//
//  // check if we have had a change if direction and if so, in which direction
//
//  if (abs(maDiff) > 2) { // '2' est une genre de filtre contre le bruit dans le signal, augmenter au besoin
//
//    if ( maDiff > 0 ) {   // check if we have had a change if direction and if so which one...
//      Serial.print("+ + + + + + + + : ");
//      Serial.println(maMoyenne);
//      // set increasing indicator to true
//      flagBias = true;
//      if (flagBias != oldFlagBias) { // bias changed from neg to pos
//        misDatosMin[counter] = sensorValue; // add a value to the sliding array, only once per change of bias
//        oldFlagBias = flagBias;
//      }
//
//    }
//    else if ( maDiff < 0 ) {
//      Serial.print("- - - - - - - - : ");
//      Serial.println(maMoyenne);
//      // set increase indicator to false
//      flagBias = false;
//      if (flagBias != oldFlagBias) { // bias changed from pos to neg
//        misDatosMax[counter] = sensorValue;
//        oldFlagBias = flagBias;
//      }
//    }
//
//    else {
//      Serial.print("= = = = = = = = = : ");
//      Serial.println(maMoyenne);
//    }
//
//    viejaMoyenne = maMoyenne;
//
//    //    if (sensorValue > moyenneMax) { // Entonces add to the Max array
//    //      misDatosMax[counter] = sensorValue; // write this once we started moving down so store the value in the misDatosArray
//    //      }
//    //
//    //      else if (sensorValue < moyenneMin) { // Add to the Min array
//    //      misDatosMin[counter] = sensorValue;
//    //      }
//  }
//}

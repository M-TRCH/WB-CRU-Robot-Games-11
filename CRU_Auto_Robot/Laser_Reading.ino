void Check_Start()
{ 
  drive(0, 0, -150);delay(400);drive(0, 0, 0); //R
  delay(1000);
  
  while(1)
  {
    digitalWrite(Sensor_R, HIGH);
    digitalWrite(Sensor_L, LOW);
    
    if (!sensor.init())
    {
      Serial.println("Failed to detect and initialize sensor!");
    }
    sensor.startContinuous();
    Serial.println(sensor.readRangeContinuousMillimeters());
    if(sensor.readRangeContinuousMillimeters() <= 70) { break; }
    else{ drive(0, 0 ,0); }
  }
  digitalWrite(Sensor_R, LOW);
  digitalWrite(Sensor_L, LOW);
  delay(2500);

  drive(0, 0, 150);delay(800);drive(0, 0, 0);  //L
  delay(1000);
  
  while(1)
  {
    digitalWrite(Sensor_R, LOW);
    digitalWrite(Sensor_L, HIGH);
    
    if (!sensor.init())
    {
      Serial.println("Failed to detect and initialize sensor!");
    }
    
    sensor.startContinuous();
    Serial.println(sensor.readRangeContinuousMillimeters());
    if(sensor.readRangeContinuousMillimeters() <= 70) { break; }
    else{ drive(0, 0 ,0); }
  }
  
  digitalWrite(Sensor_R, LOW);
  digitalWrite(Sensor_L, LOW);
  delay(2500);
}

void Check_Start_O()
{
  drive(0, 0, 150);delay(400);drive(0, 0, 0);  //L
  delay(1000);
  
  while(1)
  {
    digitalWrite(Sensor_R, LOW);
    digitalWrite(Sensor_L, HIGH);
    
    if (!sensor.init())
    {
      Serial.println("Failed to detect and initialize sensor!");
    }
    
    sensor.startContinuous();
    Serial.println(sensor.readRangeContinuousMillimeters());
    if(sensor.readRangeContinuousMillimeters() <= 70) { break; }
    else{ drive(0, 0 ,0); }
  }
  
  digitalWrite(Sensor_R, LOW);
  digitalWrite(Sensor_L, LOW);
  delay(2500);
}

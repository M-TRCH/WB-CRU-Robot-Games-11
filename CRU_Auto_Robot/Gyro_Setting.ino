void Read_Gyro()
{
  if (!dmpReady) return;
  while (!mpuInterrupt && fifoCount < packetSize)
  {
  }

  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  fifoCount = mpu.getFIFOCount();

  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();

  } else if (mpuIntStatus & 0x02) {

    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    mpu.getFIFOBytes(fifoBuffer, packetSize);

    fifoCount -= packetSize;
#ifdef OUTPUT_READABLE_YAWPITCHROLL
    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    //    Serial.print("ypr\t");
    //    Serial.print(ypr[0] * 180 / M_PI);
    //    Serial.print("\t");
    //    Serial.print(ypr[1] * 180 / M_PI);
    //    Serial.print("\t");
    //    Serial.println(ypr[2] * 180 / M_PI);

    degree = (ypr[0] * 180) / M_PI;

#endif

  }
}

void Gyro_set()
{
  long timer = millis();
  while (millis() - timer <= 18000)
  {
    Read_Gyro();
    Setpoint = degree;
  }
}

void PID_Gyro(int N_S)
{
  Read_Gyro();
  Error = (Setpoint + N_S) - degree;
  
  P = Error ;
  I = I + P ;
  D = Error - P_error ;

  P_error = Error;

  pid = P * Kp + I * Ki + D * Kd ;
}

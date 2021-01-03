unsigned int timer_1, timer_2;

void Set_Heading(int Ceta, int timer)
{
  timer_1 = millis();
  timer_2 = timer + timer_1;

  while (timer_1 <= timer_2)
  {
     PID_Gyro(Ceta); 
     drive(0, 0, pid);
     
     timer_1 = millis();
  }
  drive(0, 0, 0);
}

void Oblique_F(int timer)
{
  timer_1 = millis();
  timer_2 = timer + timer_1;

  while (timer_1 <= timer_2)
  {
     PID_Gyro(90); 
     drive(150, 20, pid);
     
     timer_1 = millis();
  }
  drive(0, 0, 0);
}

void Oblique_B(int timer)
{
  timer_1 = millis();
  timer_2 = timer + timer_1;

  while (timer_1 <= timer_2)
  {
     PID_Gyro(-90); 
     drive(150, 345, pid);
     
     timer_1 = millis();
  }
  drive(0, 0, 0);
}

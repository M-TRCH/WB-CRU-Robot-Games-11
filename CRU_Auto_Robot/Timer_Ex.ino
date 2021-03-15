//-------------------------------------Start & Finish-------------------------------------//
void Oblique_F(int timer)
{
  drive(Speed, 20, 0);
  delay(timer);
  drive(0, 0, 0);
}

void Oblique_B(int timer)
{
  drive(Speed, 345, 0);
  delay(timer);
  drive(0, 0, 0);
}

//-------------------------------------Set_Arm-------------------------------------//
void Set(int timer)
{
  Rotate_joint.rotate(2, -405); //C
  Kept_joint.rotate(2, -450); //Down
  delay(timer);
}
//-------------------------------------Last_Mission-------------------------------------//
void Stop_Mission(int Sp)
{  
  delay(200);
  drive(Speed, 270, 0); delay(800); drive(0, 0, 0);
  drive(Speed, 0, 0); delay(1000); drive(0, 0, 0);
  drive(150, 0, 0); delay(700); drive(0, 0, 0);
  //drive(Speed, 0, 0); delay(1700); drive(0, 0, 0);
}
//-------------------------------------Start_Mission-------------------------------------//
void Start_Mission() 
{ 
  drive(0, 0, 150);delay(200);drive(0, 0, 0);delay(500); 
} 

///////////////////////////////////////////////////////////////////////////////////////////////////
void Last()
{
  drive(Speed, 180, 0);delay(2000);drive(0, 0, 0);
  drive(Speed, 90, 0);delay(700);drive(0, 0, 0);
  drive(Speed, 180, 0);delay(700);drive(0, 0, 0);
  drive(Speed, 270, 0);delay(1000);drive(0, 0, 0);
}

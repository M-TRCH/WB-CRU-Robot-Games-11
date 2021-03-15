//-------------------------------------Move_Normal-------------------------------------//
void FD(int timer)
{
  drive(150, 90, 0);
  delay(timer);
  drive(0, 0, 0);
}

void BK(int timer)
{
  drive(Speed_min, 270, 0);
  delay(timer);
  drive(0, 0, 0);
}
//-------------------------------------Curve_Drive-------------------------------------//
void Curve_R(int timer)
{
  drive(250, 0, 70); //40
  delay(timer);
  drive(0, 0, 0);
}

void Curve_L(int timer)
{
  drive(250, 180, -70); //40
  delay(timer);
  drive(0, 0, 0);
}
//-------------------------------------Arm_Control-------------------------------------//
void Mission_L()
{
  Rotate_joint.rotate(2, -465); //L
  Kept_joint.rotate(2, -450); //Down
  delay(700);
  digitalWrite(servo, HIGH);delay(1000);
  Kept_joint.rotate(2, -360); //Up
  delay(700);
  Rotate_joint.rotate(2, -585); //CC
  delay(500);
  Kept_joint.rotate(2, -450); //Down
  delay(1000);
  digitalWrite(servo, LOW);delay(700);
  Rotate_joint.rotate(2, -405); //C
  delay(500);
}

void Mission_R()
{
  Rotate_joint.rotate(2, -345); //R
  Kept_joint.rotate(2, -450); //Down
  delay(700);
  digitalWrite(servo, HIGH);delay(1000);
  Kept_joint.rotate(2, -360); //Up
  delay(700);
  Rotate_joint.rotate(2, -585); //CC
  delay(1500);
  Kept_joint.rotate(2, -450); //Down
  delay(1000);
  digitalWrite(servo, LOW);delay(700);
  Rotate_joint.rotate(2, -405); //C
  delay(500);
}
//---------------------------------------------//
void Mission_R1()
{
  Rotate_joint.rotate(2, -345); //R
  Kept_joint.rotate(2, -450); //Down
  delay(700);
  digitalWrite(servo, HIGH);delay(200);
}
void Mission_R2()
{
  Kept_joint.rotate(2, -360); //Up
  delay(200);
  Rotate_joint.rotate(2, -405); //C
  delay(200);
}
void Mission_R3()
{
  Rotate_joint.rotate(2, -585); //CC
  delay(1100);
  Kept_joint.rotate(2, -450); //Down
  delay(1000);
  digitalWrite(servo, LOW);delay(700);
  Rotate_joint.rotate(2, -405); //C
  delay(500);
}
//---------------------------------------------//
void Mission_L1()
{
  Rotate_joint.rotate(2, -465); //L
  Kept_joint.rotate(2, -450); //Down
  delay(700);
  digitalWrite(servo, HIGH);delay(200);
}
void Mission_L2()
{
  Kept_joint.rotate(2, -360); //Up
  delay(200);
  Rotate_joint.rotate(2, -405); //C
  delay(200);
}
void Mission_L3()
{
  Rotate_joint.rotate(2, -585); //CC
  delay(1100);
  Kept_joint.rotate(2, -450); //Down
  delay(1000);
  digitalWrite(servo, LOW);delay(700);
  Rotate_joint.rotate(2, -405); //C
  delay(500); 
  Kept_joint.rotate(2, -360); //Up
  delay(500); 
}

/*
Rotate_joint.rotate(2, -585); //CC
Rotate_joint.rotate(2, -405); //C
Rotate_joint.rotate(2, -465); //L
Rotate_joint.rotate(2, -345); //R

Kept_joint.rotate(2, -450); //Down
Kept_joint.rotate(2, -360); //Up
*/

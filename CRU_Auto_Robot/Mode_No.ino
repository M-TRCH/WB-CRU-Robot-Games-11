int Sp_FD_No = 1000;

void Red_Duo()
{
  Check_Start();
  
  pixy.init();
  pixy.setLamp(1, 1);
  
  Start_Mission();
  Mission_R1();
  Oblique_F(Ob_F); 
  
  FD(1000);
  BK(Sp_BK);
  Curve_R(curve_r);

  //--2--//
  Mission_R2();
  FD(Sp_FD_No);
  Mission_R3();
  BK(Sp_BK);
  Mission_L1();
  Curve_R(curve_rr);  

  //--3--//
  Mission_L2();
  FD(Sp_FD_No);
  Mission_L3();
  BK(Sp_BK);
  Curve_L(curve_l);

  //--3--//
  Tracking(Green_Object);
  FD(Sp_FD);
  
  Stop_Mission(Speed);
  pixy.setLamp(0, 0);
   
  while(1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Blue_Duo()
{
  Check_Start();
  
  pixy.init();
  pixy.setLamp(1, 1);
  
  Start_Mission();
  Mission_L1();
  Oblique_F(Ob_F);
  
  //--1--// 
  Mission_L2();   
  FD(Sp_FD_No);
  Mission_L3();
  BK(Sp_BK);
  Mission_R1();
  Curve_R(curve_r); 
  
  //--2--//
  Mission_R2();
  FD(Sp_FD_No);
  Mission_R3(); 
  BK(Sp_BK);
  Curve_R(curve_r);
  
  //--3--//
  FD(Sp_FD_No);
  
  Stop_Mission(Speed);
  pixy.setLamp(0, 0);
   
  while(1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Green_Duo()
{
  Check_Start();
  
  pixy.init();
  pixy.setLamp(1, 1);
  
  Start_Mission();
  Mission_R1();
  Oblique_F(Ob_F);

  FD(1000);
  BK(Sp_BK);
  
  Curve_R(curve_r); 
  
  //--2--//
  Mission_R2();
  FD(Sp_FD_No);
  Mission_R3();
  BK(Sp_BK);
  Mission_L1();
  Curve_R(curve_r);  

  //--3--//
  Mission_L2();
  FD(Sp_FD_No);
  Mission_L3();
  Stop_Mission(250);
  pixy.setLamp(0, 0);

  while(1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Red()
{
  Check_Start_O();
  
  pixy.init();
  pixy.setLamp(1, 1);
  
  Start_Mission();
  Mission_L1();
  Oblique_F(Ob_F);
  
  FD(1000);
  BK(Sp_BK); 

  Curve_L(curve_l);

  //--4--//
  Mission_L2();
  FD(Sp_FD_No);
  Mission_L3();
  BK(Sp_BK);
  Curve_L(curve_l);  

  //--3--//
  FD(Sp_FD_No);
  
  Stop_Mission(Speed);
  pixy.setLamp(0, 0);
   
  while(1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Blue()
{
  Check_Start_O();
  
  pixy.init();
  pixy.setLamp(1, 1);
  
  Start_Mission();
  Mission_L1();
  Oblique_F(Ob_F); 

  //--1--//
  Mission_L2();
  FD(Sp_FD_No);
  Mission_L3();
  BK(Sp_BK);
  Curve_R(curve_rr);  

  //--3--//
  FD(Sp_FD_No);
  
  Stop_Mission(Speed);
  pixy.setLamp(0, 0);
   
  while(1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Gray()
{
  Check_Start_O();
  
  pixy.init();
  pixy.setLamp(1, 1);
  
  Start_Mission();
  Mission_L1();
  Oblique_F(Ob_F);
  
  FD(1000);
  BK(Sp_BK);
  
  Curve_R(curve_r); 
  
  //--2--//
  Mission_L2();
  FD(Sp_FD_No);
  Mission_L3();
  BK(Sp_BK);
  
  Curve_R(curve_r);
  FD(Sp_FD_No);
  Stop_Mission(250);
  pixy.setLamp(0, 0);
   
  while(1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Green()
{
  Check_Start_O();
  
  pixy.init();
  pixy.setLamp(1, 1);
  
  Start_Mission();
  Mission_L1();
  Oblique_F(Ob_F);
  
  FD(1000);
  BK(Sp_BK); 

  //--3--//
  Curve_R(curve_rr);
  Mission_L2();
  FD(Sp_FD_No);
  Mission_L3();
  
  Stop_Mission(Speed);
  pixy.setLamp(0, 0);
   
  while(1);
}

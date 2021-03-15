//---------------Area---------------//
int Blue_Object  = -13000; 
int Gray_Object  = 20000; 
int Green_Object = -13000; 
int Red_Object   = 7000;
//---------------Time---------------//
int Speed     = 250;
int Speed_min = 150;
int Ob_F      = 1350; 
 
int curve_r  = 1400; //Normal
int curve_rr = 2600; //Expert
int curve_l  = 1350; //Expert

int Sp_FD = 1000;
int Sp_BK = 500;
///////////////////////////////////////////////////////////////////////////////////////////////////
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
  Tracking(Gray_Object);
  FD(Sp_FD);
  Mission_R3();
  BK(Sp_BK);
  Mission_L1();
  Curve_R(curve_rr);  

  //--3--//
  Mission_L2();
  Tracking(Red_Object);
  FD(Sp_FD);
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
  Tracking(Blue_Object);
  FD(Sp_FD);
  Mission_L3();
  BK(Sp_BK);
  Mission_R1();
  Curve_R(curve_r); 
  
  //--2--//
  Mission_R2();
  Tracking(Gray_Object);
  FD(Sp_FD);
  Mission_R3(); 
  BK(Sp_BK);
  Curve_R(curve_r);
  
  //--3--//
  Tracking(Green_Object);
  FD(Sp_FD);
  
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
  Tracking(Gray_Object);
  FD(Sp_FD);
  Mission_R3();
  BK(Sp_BK);
  Mission_L1();
  Curve_R(curve_r);  

  //--3--//
  Mission_L2();
  Tracking(Green_Object);
  FD(Sp_FD);
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
  Tracking(Red_Object);
  FD(Sp_FD);
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
  Tracking(Blue_Object);
  FD(Sp_FD);
  Mission_L3();
  BK(Sp_BK);
  Curve_R(curve_rr);  

  //--3--//
  Tracking(Green_Object);
  FD(Sp_FD);
  
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
  Tracking(Gray_Object);
  FD(Sp_FD);
  Mission_L3();
  BK(Sp_BK);
  
  Curve_R(curve_r);
  Tracking(Green_Object);
  FD(Sp_FD);
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
  Tracking(Green_Object);
  FD(Sp_FD);
  Mission_L3();
  
  Stop_Mission(Speed);
  pixy.setLamp(0, 0);
   
  while(1);
}

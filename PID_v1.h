#ifndef PID_v1_h
#define PID_v1_h
#define LIBRARY_VERSION	1.3.0

#ifdef USE_64bit_FLOATINGPOINT // use double precision floats
  #define FPsz_t  double
#else // default to 32bit (single precision) floats
  #define FPsz_t  float
#endif /* USE_64bit_FLOATINGPOINT */

class PID
{


  public:

  //Constants used in some of the functions below
  #define AUTOMATIC	1
  #define MANUAL	0
  #define DIRECT  0
  #define REVERSE  1
  #define P_ON_M 0
  #define P_ON_E 1

  //commonly used functions **************************************************************************
    PID(FPsz_t*, FPsz_t*, FPsz_t*,        // * constructor.  links the PID to the Input, Output, and
        FPsz_t, FPsz_t, FPsz_t, int, int);//   Setpoint.  Initial tuning parameters are also set here.
                                          //   (overload for specifying proportional mode)

    PID(FPsz_t*, FPsz_t*, FPsz_t*,        // * constructor.  links the PID to the Input, Output, and
        FPsz_t, FPsz_t, FPsz_t, int);     //   Setpoint.  Initial tuning parameters are also set here

    void SetMode(int Mode);               // * sets PID to either Manual (0) or Auto (non-0)

    bool Compute();                       // * performs the PID calculation.  it should be
                                          //   called every time loop() cycles. ON/OFF and
                                          //   calculation frequency can be set using SetMode
                                          //   SetSampleTime respectively

    void SetOutputLimits(FPsz_t, FPsz_t); // * clamps the output to a specific range. 0-255 by default, but
										                      //   it's likely the user will want to change this depending on
										                      //   the application



  //available but not commonly used functions ********************************************************
    void SetTunings(FPsz_t, FPsz_t,       // * While most users will set the tunings once in the
                    FPsz_t);         	    //   constructor, this function gives the user the option
                                          //   of changing tunings during runtime for Adaptive control
    void SetTunings(FPsz_t, FPsz_t,       // * overload for specifying proportional mode
                    FPsz_t, int);

	void SetControllerDirection(int);	  // * Sets the Direction, or "Action" of the controller. DIRECT
										  //   means the output will increase when error is positive. REVERSE
										  //   means the opposite.  it's very unlikely that this will be needed
										  //   once it is set in the constructor.
    void SetSampleTime(int);              // * sets the frequency, in Milliseconds, with which
                                          //   the PID calculation is performed.  default is 100



  //Display functions ****************************************************************
	FPsz_t GetKp();						  // These functions query the pid for interal values.
	FPsz_t GetKi();						  //  they were created mainly for the pid front-end,
	FPsz_t GetKd();						  // where it's important to know what is actually
	int GetMode();						  //  inside the PID.
	int GetDirection();					  //

  private:
	void Initialize();

	FPsz_t dispKp;				// * we'll hold on to the tuning parameters in user-entered
	FPsz_t dispKi;				//   format for display purposes
	FPsz_t dispKd;				//

	FPsz_t kp;                  // * (P)roportional Tuning Parameter
  FPsz_t ki;                  // * (I)ntegral Tuning Parameter
  FPsz_t kd;                  // * (D)erivative Tuning Parameter

	int controllerDirection;
	int pOn;

    FPsz_t *myInput;              // * Pointers to the Input, Output, and Setpoint variables
    FPsz_t *myOutput;             //   This creates a hard link between the variables and the
    FPsz_t *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are.  with pointers we'll just know.

	unsigned long lastTime;
	FPsz_t outputSum, lastInput;

	unsigned long SampleTime;
	FPsz_t outMin, outMax;
	bool inAuto, pOnE;
};
#endif


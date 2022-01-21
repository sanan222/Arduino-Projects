void setup(){
 
}

void loop(){
  // put your main code here, to run repeatedly:
  currentTime = millis();
  elapsedTime = currentTime - previousTime;

  error = setPoint - input;
  cumError += error * elapsedTime;  // cumulative error (integral of the error)
  rateError = (error - lastError)/elapsedTime;  // rate of the error (derivative)
  output = Kp * error + Ki * cumError + Kd * rateError;
  lastError = error;
  previousTime = currentTime;
  
}
  
   

/* ---------------------------------------------*/
/* Print to LCD for Set Mode (Time Lapse)       */
/* -------------------------------------------- */

void functionPrintSMTimeLapse()
{
  lcd.clear();
  lcd.noCursor();
  lcd.print("Set Mode");
  lcd.setCursor(0,1);
  lcd.print(" Time Lapse");
}

/* ---------------------------------------------*/
/* Print to LCD for Set Mode (Time Lapse B)       */
/* -------------------------------------------- */

void functionPrintSMTimeLapseB()
{
  lcd.clear();
  lcd.noCursor();
  lcd.print("Set Mode");
  lcd.setCursor(0,1);
  lcd.print(" Time Lapse (B)");
}

/* ---------------------------------------------*/
/* Print to LCD for Set Mode (Trigger)          */
/* -------------------------------------------- */

void functionPrintSMTrigger()
{
  lcd.clear();
  lcd.noCursor();
  lcd.print("Set Mode");
  lcd.setCursor(0,1);
  lcd.print(" Trigger");
}

/* ---------------------------------------------*/
/* Print to LCD for Set Mode (Manual)           */
/* -------------------------------------------- */

void functionPrintSMManual()
{
  lcd.clear();
  lcd.noCursor();
  lcd.print("Set Mode");
  lcd.setCursor(0,1);
  lcd.print(" Manual");
}

/* ---------------------------------------------*/
/* Print to LCD for Set Option for Time Lapse   */
/* -------------------------------------------- */

void functionPrintSOTimeLapse()
{
  lcd.clear();
  lcd.print("Time Lapse");
  lcd.setCursor(0,1);
  lcd.print("Delay = ");
  functionPrintSeconds(optionDelayTime);
  lcd.setCursor(11,1);
  lcd.cursor();
}

/* ---------------------------------------------*/
/* Print to LCD for Set Option for Time Lapse (B) */
/* -------------------------------------------- */

void functionPrintSOTimeLapseB()
{
  lcd.clear();
  lcd.print("Time Lapse (B)");
  lcd.setCursor(0,1);
  lcd.print("D=");
  functionPrintSeconds(optionDelayTimeB);
  lcd.print("  S=");
  functionPrintSeconds(optionBulbTime);
  if (optionCursorDelay) {
    lcd.setCursor(5,1);
  }
  else {
    lcd.setCursor(13,1);
  }
  lcd.cursor();
}

/* ---------------------------------------------*/
/* Print to LCD for Set Option for Trigger      */
/* -------------------------------------------- */

void functionPrintSOTrigger()
{
  lcd.clear();
  lcd.print("Trigger");
  lcd.setCursor(0,1);
  lcd.print("Tr: ");
  functionPrintTriggerOption(optionTriggerLevel);
  lcd.print(" D: ");
  functionPrintTriggerDelay(optionTriggerDelay);
  if (optionCursorDelay == 1) {
    lcd.setCursor(14,1);
  }
  else {
    lcd.setCursor(4,1);
  }
  lcd.cursor();
}

/* ---------------------------------------------*/
/* Print selected trigger level (High/Low)      */
/* -------------------------------------------- */

void functionPrintTriggerOption(boolean TriggerLevel)
{
  if (TriggerLevel) {
    lcd.print("High");
  }
  else {
    lcd.print("Low ");
  }
}

/* ---------------------------------------------*/
/* Print delay time for trigger                 */
/* -------------------------------------------- */

void   functionPrintTriggerDelay(int delayTime)
{
  if (delayTime < 100) {
    lcd.print("0");
    if (delayTime < 10) {
      lcd.print("0");
    }
  }
  lcd.print(delayTime);
}


/* ---------------------------------------------*/
/* Print to LCD for Set Option for Manual       */
/* -------------------------------------------- */

void functionPrintSOManual()
{
  lcd.clear();
  lcd.noCursor();
  lcd.print("Manual");
  lcd.setCursor(0,1);
  lcd.print("Press Z to shoot");
}

/* ---------------------------------------------*/
/* Print to LCD for Set Option for Manual       */
/* -------------------------------------------- */

void functionPrintTimeLapseRun()
{
  lcd.clear();
  lcd.noCursor();
  lcd.print("Shooting ...");
  lcd.setCursor(0,1);
  lcd.print("Press c to stop");
}

/* ---------------------------------------------*/
/* Print to LCD that waiting for low trigger    */
/* -------------------------------------------- */

void functionPrintTriggerWait()
{
  lcd.clear();
  lcd.noCursor();
  lcd.print("Trigger - Wait");
  lcd.setCursor(0,1);
  lcd.print("Use c to exit");
}

/* ---------------------------------------------*/
/* Print to LCD that waiting trigger            */
/* -------------------------------------------- */

void functionPrintTriggerReady()

{
  lcd.clear();
  lcd.noCursor();
  lcd.print("Trigger - Ready");
  lcd.setCursor(0,1);
  lcd.print("Use c to exit");
}

/* ---------------------------------------------*/
/* Print selected time in current lcd position  */
/* -------------------------------------------- */

void functionPrintSeconds(int time)
{
  if (time < 10) {
    lcd.print("   ");
  }
  else if (time < 100) {
    lcd.print("  ");
  }
  else if (time < 1000) {
    lcd.print(" ");
  }
  lcd.print(time);
}

/* ---------------------------------------------*/
/* Take a shot                                  */
/* -------------------------------------------- */

void functionPhotoShot()
{
  digitalWrite(pinCameraFocus, HIGH);
  delay(shotFocusHold);
  digitalWrite(pinCameraShot, HIGH);
  delay(shotTriggerHold);
  digitalWrite(pinCameraShot, LOW);
  delay(shotFocusHoldPost);
  digitalWrite(pinCameraFocus, LOW);
//  Serial.println("Take a photo");
}

/* ---------------------------------------------*/
/* Start a shot (bulb mode)                     */
/* -------------------------------------------- */

void functionPhotoBegin()
{
  digitalWrite(pinCameraFocus, HIGH);
  delay(shotFocusHold);
  digitalWrite(pinCameraShot, HIGH);
  inBulbShot = 1;
//  Serial.println("Start Photo ........");
}

/* ---------------------------------------------*/
/* Finish a shot (bulb mode)                     */
/* -------------------------------------------- */

void functionPhotoEnd()
{

  digitalWrite(pinCameraShot, LOW);
  delay(shotFocusHoldPost);
  digitalWrite(pinCameraFocus, LOW);
  inBulbShot = 0;
//  Serial.println("........End Photo");
}



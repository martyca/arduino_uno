/* Arduino USB HID Keyboard sketch.
 *  
*/

/* Modifiers go into the first bit of the 8 bit map. (buf[0]) */
  #define KEY_LEFT_CTRL   0x01
  #define KEY_LEFT_SHIFT  0x02
  #define KEY_LEFT_ALT    0x03
  #define KEY_LEFT_GUI    0x04
  #define KEY_RIGHT_CTRL  0x10
  #define KEY_RIGHT_SHIFT 0x20
  
  #define KEY_ErrorRollOver 0x01  /* Keyboard ErrorRollOver */
  #define KEY_POSTFail 0x02 /* Keyboard POSTFail */
  #define KEY_ErrorUndefined 0x03 /* Keyboard ErrorUndefined */
  #define KEY_a 0x04  /* Keyboard a and A */
  #define KEY_b 0x05  /* Keyboard b and B */
  #define KEY_c 0x06  /* Keyboard c and C */
  #define KEY_d 0x07  /* Keyboard d and D */
  #define KEY_e 0x08  /* Keyboard e and E */
  #define KEY_f 0x09  /* Keyboard f and F */
  #define KEY_g 0x0A  /* Keyboard g and G */
  #define KEY_h 0x0B  /* Keyboard h and H */
  #define KEY_i 0x0C  /* Keyboard i and I */
  #define KEY_j 0x0D  /* Keyboard j and J */
  #define KEY_k 0x0E  /* Keyboard k and K */
  #define KEY_l 0x0F  /* Keyboard l and L */
  #define KEY_m 0x10  /* Keyboard m and M */
  #define KEY_n 0x11  /* Keyboard n and N */
  #define KEY_o 0x12  /* Keyboard o and O */
  #define KEY_p 0x13  /* Keyboard p and P */
  #define KEY_q 0x14  /* Keyboard q and Q */
  #define KEY_r 0x15  /* Keyboard r and R */
  #define KEY_s 0x16  /* Keyboard s and S */
  #define KEY_t 0x17  /* Keyboard t and T */
  #define KEY_u 0x18  /* Keyboard u and U */
  #define KEY_v 0x19  /* Keyboard v and V */
  #define KEY_w 0x1A  /* Keyboard w and W */
  #define KEY_x 0x1B  /* Keyboard x and X */
  #define KEY_y 0x1C  /* Keyboard y and Y */
  #define KEY_z 0x1D  /* Keyboard z and Z */
  #define KEY_1 0x1E  /* Keyboard 1 and ! */
  #define KEY_2 0x1F  /* Keyboard 2 and @ */
  #define KEY_3 0x20  /* Keyboard 3 and # */
  #define KEY_4 0x21  /* Keyboard 4 and $ */
  #define KEY_5 0x22  /* Keyboard 5 and % */
  #define KEY_6 0x23  /* Keyboard 6 and ^ */
  #define KEY_7 0x24  /* Keyboard 7 and & */
  #define KEY_8 0x25  /* Keyboard 8 and * */
  #define KEY_9 0x26  /* Keyboard 9 and ( */
  #define KEY_0 0x27  /* Keyboard 0 and ) */
  #define KEY_ENTER 0x28  /* Keyboard Return (ENTER) */
  #define KEY_ESC 0x29  /* Keyboard ESCAPE */
  #define KEY_DEL 0x2A  /* Keyboard DELETE (Backspace) */
  #define KEY_TAB 0x2B  /* Keyboard Tab */
  #define KEY_SPACE 0x2C  /* Keyboard Spacebar */
  #define KEY_DASH 0x2D /* Keyboard - and (underscore) */
  #define KEY_EQUAL 0x2E  /* Keyboard = and + */
  #define KEY_LEFT_BRACKET 0x2F /* Keyboard [ and { */
  #define KEY_RIGHT_BRACKET 0x30  /* Keyboard ] and } */
  #define KEY_BACK_SLASH 0x31 /* Keyboard \ and | */
  #define KEY_NUMBER 0x32 /* Keyboard Non-US # and ~ */
  #define KEY_COLON 0x33  /* Keyboard ; and : */
  #define KEY_QUOTE 0x34  /* Keyboard ' and " */
  #define KEY_BACKTICK 0x35 /* Keyboard Grave Accent and Tilde */
  #define KEY_COMMA 0x36  /* Keyboard, and < */
  #define KEY_POINT 0x37  /* Keyboard . and > */
  #define KEY_SLASH 0x38  /* Keyboard / and ? */
  #define KEY_CAPS 0x39 /* Keyboard Caps Lock */
  #define KEY_F1 0x3A /* Keyboard F1 */
  #define KEY_F2 0x3B /* Keyboard F2 */
  #define KEY_F3 0x3C /* Keyboard F3 */
  #define KEY_F4 0x3D /* Keyboard F4 */
  #define KEY_F5 0x3E /* Keyboard F5 */
  #define KEY_F6 0x3F /* Keyboard F6 */
  #define KEY_F7 0x40 /* Keyboard F7 */
  #define KEY_F8 0x41 /* Keyboard F8 */
  #define KEY_F9 0x42 /* Keyboard F9 */
  #define KEY_F10 0x43  /* Keyboard F10 */
  #define KEY_F11 0x44  /* Keyboard F11 */
  #define KEY_F12 0x45  /* Keyboard F12 */
  #define KEY_PRT_SCR 0x46  /* Keyboard PrintScreen */
  #define KEY_SCR_LCK 0x47  /* Keyboard Scroll Lock */
  #define KEY_PAUSE 0x48  /* Keyboard Pause */
  #define KEY_INS 0x49  /* Keyboard Insert */
  #define KEY_HOME 0x4A /* Keyboard Home */
  #define KEY_PAGEUP 0x4B /* Keyboard PageUp */
  #define KEY_DELFOR 0x4C /* Keyboard Delete Forward */
  #define KEY_END 0x4D  /* Keyboard End */
  #define KEY_PAGEDOWN 0x4E /* Keyboard PageDown */
  #define KEY_RIGHT 0x4F  /* Keyboard RightArrow */
  #define KEY_LEFT 0x50 /* Keyboard LeftArrow */
  #define KEY_DOWN 0x51 /* Keyboard DownArrow */
  #define KEY_UP 0x52 /* Keyboard UpArrow */


int buttonState = 0;
uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */

int KEY_STRING[]= {KEY_a, KEY_i, KEY_s, KEY_l, KEY_i, KEY_n, KEY_n, KEY_ENTER}; /* Character array */
int MOD_STRING[]= {KEY_LEFT_SHIFT, 0, 0, 0, 0, 0, 0, 0};                        /* Modifier array */
int ARRAY_LENGTH = 8;                                                           /* Array length */

void setup() 
{
  Serial.begin(9600);
  delay(200);
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  pinMode(4, INPUT_PULLUP);
}

void loop() 
{
  buttonState = digitalRead(4);
  
  if (buttonState == LOW) {
    for(int x = 0; x < 8; x++){
      pressKey(KEY_STRING[x], MOD_STRING[x]);
      }
  } else {
  digitalWrite(13, LOW);
  }
}
void pressKey(int KEY, int MOD) /* Key press function (KEY is character, MOD is modifier) */
{
  buf[0] = MOD;
  buf[2] = KEY;
  Serial.write(buf, 8); // Send keypress
  releaseKey();
}
void releaseKey() /* Key release function. */
{
  delay(10);
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key
  delay(10);
}

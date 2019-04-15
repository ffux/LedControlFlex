#include <LedControl.h>

LedControl lc=LedControl(14,10,16,4);  // Pins: DIN,CLK,CS, # of Display connected

// Delay between Frames
unsigned long delayTime=100;

// My display order is currently right to left, so this array is used to flip the index
int displayIndexArray[] =
{
  4,
  3,
  2,
  1
};

// Test arrays for individual displays
byte blank[] =
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
byte number1[] =
{
  B00000000,
  B00010000,
  B00110000,
  B00010000,
  B00010000,
  B00010000,
  B00111000,
  B00000000
};

byte number2[] =
{
  B00000000,
  B00111100,
  B01000010,
  B00000100,
  B00011000,
  B00100000,
  B01111110,
  B00000000
};

byte number3[] =
{
  B00000000,
  B00111100,
  B01000010,
  B00000100,
  B00011000,
  B01000010,
  B00111100,
  B00000000
};

byte number4[] =
{
  B00000000,
  B00001000,
  B00011000,
  B00101000,
  B01001000,
  B01111100,
  B00001000,
  B00000000
};

// Array definitions for receiving bytes from the interpreter
// If these are not updated they will show the display index from 1-4
byte displayArray0[] =
{
  B00000000,
  B00010000,
  B00110000,
  B00010000,
  B00010000,
  B00010000,
  B00111000,
  B00000000
};
byte displayArray1[] =
{
  B00000000,
  B00111100,
  B01000010,
  B00000100,
  B00011000,
  B00100000,
  B01111110,
  B00000000
};
byte displayArray2[] =
{
  B00000000,
  B00111100,
  B01000010,
  B00000100,
  B00011000,
  B01000010,
  B00111100,
  B00000000
};
byte displayArray3[] =
{
  B00000000,
  B00001000,
  B00011000,
  B00101000,
  B01001000,
  B01111100,
  B00001000,
  B00000000
};

// 2d array of the full-screen image
// Ideally this will be set by loaded by an external memory source in a more user-friendly fashion, using bitmaps
int fullScreenImage[8][32] =
{
  {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
  {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1},
  {1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
  {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Uses bitwise operators to convert 8 integers to a byte
byte convertIntArrayToByte(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7)
{
  byte x = B00000000;
  if (i0 == 1)
  {
    x = x | B10000000;
  }
  if (i1 == 1)
  {
    x = x | B01000000;
  }
  if (i2 == 1)
  {
    x = x | B00100000;
  }
  if (i3 == 1)
  {
    x = x | B00010000;
  }
  if (i4 == 1)
  {
    x = x | B00001000;
  }
  if (i5 == 1)
  {
    x = x | B00000100;
  }
  if (i6 == 1)
  {
    x = x | B00000010;
  }
  if (i7 == 1)
  {
    x = x | B00000001;
  }
  return x;
  Serial.println("array converted to byte: ");
  Serial.println(x, BIN);
}

void convertFullScreenImageToByteArrays()
{
  Serial.println("convertFullScreenImageToByteArrays started");
  // Split FullScreenImage array to 8x8 grids and pass rows to convertIntArrayToByte() to convert
  // Loop through rows
  for (int row = 0; row < 8; row++)
  {
    displayArray0[row] = convertIntArrayToByte(fullScreenImage[row][0],fullScreenImage[row][1],fullScreenImage[row][2],fullScreenImage[row][3],fullScreenImage[row][4],fullScreenImage[row][5],fullScreenImage[row][6],fullScreenImage[row][7]);
    Serial.println("displayArray0 = ");
    Serial.println(displayArray0[row], BIN);
  }
  for (int row = 0; row < 8; row++)
  {
    displayArray1[row] = convertIntArrayToByte(fullScreenImage[row][8],fullScreenImage[row][9],fullScreenImage[row][10],fullScreenImage[row][11],fullScreenImage[row][12],fullScreenImage[row][13],fullScreenImage[row][14],fullScreenImage[row][15]);
  }
  for (int row = 0; row < 8; row++)
  {
    displayArray2[row] = convertIntArrayToByte(fullScreenImage[row][16],fullScreenImage[row][17],fullScreenImage[row][18],fullScreenImage[row][19],fullScreenImage[row][20],fullScreenImage[row][21],fullScreenImage[row][22],fullScreenImage[row][23]);
  }
  for (int row = 0; row < 8; row++)
  {
    displayArray3[row] = convertIntArrayToByte(fullScreenImage[row][24],fullScreenImage[row][25],fullScreenImage[row][26],fullScreenImage[row][27],fullScreenImage[row][28],fullScreenImage[row][29],fullScreenImage[row][30],fullScreenImage[row][31]);
  }
}

void setup()
{
//  Serial.begin(9600);
//  while (!Serial) ;
  Serial.println("Setup started");
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,5);  // Set intensity levels
  lc.setIntensity(1,5);
  lc.setIntensity(2,5);
  lc.setIntensity(3,5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
  convertFullScreenImageToByteArrays();
  Serial.println("Setup finished");
}

// this can be updated to loop through a something like totalDisplays instead of being restricted to 4
void writeFullDisplay()
{
  // first screen write
    for (int i = 0; i < 8; i++)
  {
    lc.setRow(displayIndexArray[1],i,displayArray0[i]);
  }
  // second screen write
    for (int i = 0; i < 8; i++)
  {
    lc.setRow(displayIndexArray[2],i,displayArray1[i]);
  }
  // third screen write
    for (int i = 0; i < 8; i++)
  {
    lc.setRow(displayIndexArray[3],i,displayArray2[i]);
  }
  // fourth screen write
    for (int i = 0; i < 8; i++)
  {
    lc.setRow(displayIndexArray[4],i,displayArray3[i]);
  }
}

// Write to displays and clear one by one
void loop()
{
    writeFullDisplay();
    delay(delayTime);
    lc.clearDisplay(3);
    lc.clearDisplay(2);
    lc.clearDisplay(1);
    lc.clearDisplay(0);
}

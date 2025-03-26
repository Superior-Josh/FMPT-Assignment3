
void AESOperation_1400088d0(longlong input,longlong keyScheduleWithIV)

{
  undefined i;
  
  XorRoundkey(0,input,keyScheduleWithIV);
  for (i = 1; i < 10; i = i + 1) {
    SubBytes(input);
    ShiftRows(input);
    MixColomns(input);
    XorRoundkey(i,input,keyScheduleWithIV);
  }
  SubBytes(input);
  ShiftRows(input);
  XorRoundkey(10,input,keyScheduleWithIV);
  return;
}


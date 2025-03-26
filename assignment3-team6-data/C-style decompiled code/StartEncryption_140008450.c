
void StartEncryption_140008450
               (longlong keyScheduleWithIV,undefined8 *buffer,uint size)

{
  undefined8 *plaintext;
  ulonglong i;
  undefined8 *IV;
  
  IV = (undefined8 *)(keyScheduleWithIV + 0xb0);
  plaintext = buffer;
  for (i = 0; i < size; i = i + 0x10) {
    PlaintextXorIV_14000acb0((longlong)plaintext,(longlong)IV);
    AESOperation_1400088d0((longlong)plaintext,keyScheduleWithIV);
    IV = plaintext;
    plaintext = plaintext + 2;
  }
  copy_14000c700((undefined8 *)(keyScheduleWithIV + 0xb0),IV,0x10);
  return;
}


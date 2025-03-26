
void PlaintextXorIV_14000acb0(longlong plaintext,longlong IV)

{
  undefined i;
  
  for (i = 0; i < 0x10; i = i + 1) {
    *(byte *)(plaintext + (ulonglong)i) =
         *(byte *)(plaintext + (ulonglong)i) ^ *(byte *)(IV + (ulonglong)i);
  }
  return;
}


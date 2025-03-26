
void InitEncryption_140008790
               (longlong keyScheduleWithIV,longlong key_addr,
               undefined8 *IV_address)

{
  KeyExpansion_140009f80(keyScheduleWithIV,key_addr);
  copy_14000c700((undefined8 *)(keyScheduleWithIV + 0xb0),IV_address,0x10);
  return;
}


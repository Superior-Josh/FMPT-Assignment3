
void AES_Encrypt_140007080(LPCWSTR input_path, LPCWSTR output_path)

{
  bool bVar1;
  BOOL BVar2;
  DWORD DVar3;
  undefined auStackY_158[32];
  uint local_110[2];
  HANDLE local_108;
  undefined8 *buffer;
  HANDLE local_f8;
  uint *local_f0;
  undefined4 local_e8;
  undefined context_array[192];
  ulonglong local_18;

  local_18 = DAT_140086038 ^ (ulonglong)auStackY_158;
  local_f8 = (HANDLE)0xffffffffffffffff;
  local_108 = (HANDLE)0xffffffffffffffff;
  buffer = (undefined8 *)0x0;
  printf((char *)L"Starting encryption.\n");
  /* Open plaintext file */
  local_f8 = CreateFileW(input_path, 1, 1, (LPSECURITY_ATTRIBUTES)0x0, 3, 0x80,
                         (HANDLE)0x0);
  if (local_f8 == (HANDLE)0xffffffffffffffff)
  {
    DVar3 = GetLastError();
    thunk_FUN_140007510(L"Error opening plaintext file!\n", DVar3);
  }
  else
  {
    printf((char *)L"Successfully opened plaintext file, %s. \n", input_path);
    /* Create encrypted file */
    local_108 = CreateFileW(output_path, 2, 1, (LPSECURITY_ATTRIBUTES)0x0, 4, 0x80,
                            (HANDLE)0x0);
    if (local_108 == (HANDLE)0xffffffffffffffff)
    {
      DVar3 = GetLastError();
      thunk_FUN_140007510(L"Error opening destination file!\n", DVar3);
    }
    else
    {
      printf((char *)L"Successfully created destination file, %s. \n",
             output_path);
      local_e8 = 0x3e0;
      buffer = (undefined8 *)_malloc_base(0x3f0);
      if (buffer == (undefined8 *)0x0)
      {
        thunk_FUN_140007510(L"Not enough memory to allocate file buffer. \n",
                            0x8007000e);
      }
      else
      {
        printf((char *)L"%i file buffer has been allocated. \n", 0x3f0);
        local_f0 = (uint *)0x0;
        local_f0 = (uint *)_malloc_base(4);
        bVar1 = false;
        do
        {
          /* Write 16 bytes IV */
          BVar2 = WriteFile(local_108, IV_140086010, 0x10, local_110,
                            (LPOVERLAPPED)0x0);
          if (BVar2 == 0)
          {
            DVar3 = GetLastError();
            thunk_FUN_140007510(L"Error writing padding size.\n", DVar3);
            goto LAB_1400073da;
          }
          printf((char *)L"IV successfully added to file.\n");
          BVar2 = ReadFile(local_f8, buffer, 0x3f0, local_110, (LPOVERLAPPED)0x0);
          if (BVar2 == 0)
          {
            DVar3 = GetLastError();
            thunk_FUN_140007510(L"Error reading plaintext!\n", DVar3);
            goto LAB_1400073da;
          }
          if (local_110[0] < 0x3f0)
          {
            bVar1 = true;
          }
          *local_f0 = local_110[0];
          BVar2 = WriteFile(local_108, local_f0, 4, local_110, (LPOVERLAPPED)0x0);
          if (BVar2 == 0)
          {
            DVar3 = GetLastError();
            thunk_FUN_140007510(L"Error writing padding size.\n", DVar3);
            goto LAB_1400073da;
          }
          printf((char *)L"Length of file buffer successfully added to file.\n");
          printf((char *)L"Starting CBC encryption.\n");
          InitEncryption_140008790((longlong)context_array, 0x140086000,
                                   (undefined8 *)IV_140086010);
          StartEncryption_140008450((longlong)context_array, buffer, 0x3f0);
          printf((char *)L"Successfully encrypted file buffer. Writing to destination fi le...\n");
          /* Write encryted file */
          BVar2 = WriteFile(local_108, buffer, 0x3f0, local_110, (LPOVERLAPPED)0x0);
          if (BVar2 == 0)
          {
            DVar3 = GetLastError();
            thunk_FUN_140007510(L"Error writing ciphertext.\n", DVar3);
            goto LAB_1400073da;
          }
        } while (!bVar1);
        thunk_FUN_14003d334(local_f0);
      }
    }
  }
LAB_1400073da:
  if (local_f8 != (HANDLE)0x0)
  {
    CloseHandle(local_f8);
  }
  if (local_108 != (HANDLE)0x0)
  {
    CloseHandle(local_108);
  }
  thunk_FUN_14000ae80(local_18 ^ (ulonglong)auStackY_158);
  return;
}

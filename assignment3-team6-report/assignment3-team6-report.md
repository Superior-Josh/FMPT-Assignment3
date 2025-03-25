# Assignment3-Team6-Report

您的目标是：

1. 使用逆向工程工具分析恶意软件的代码，找出它在做什么。
2. 确定恶意软件的目标文件/目录。
3. 恢复恶意软件用来锁定目标文件/目录的密钥/密码。
4. 汉克备份了最重要的文件，但这些文件已经被勒索软件加密。使用恢复的密钥/密码，编程一个能够解密汉克文件的工具。



我们希望每组提交一份报告，描述您的取证分析结果，涵盖 “您的目标 ”中提到的各个方面。

报告记录分析的所有步骤。报告长度必须控制在 3 至 5 页之间。

我们只要求简明扼要地提供必要的信息。需要考虑的重要方面：结构、适当的详细程度、清晰度、可复制性、完整性。



```c++
DWORD GetCurrentDirectory(
  [in]  DWORD  nBufferLength,
  [out] LPTSTR lpBuffer
);

BOOL WriteFile(
  [in]                HANDLE       hFile,
  [in]                LPCVOID      lpBuffer,
  [in]                DWORD        nNumberOfBytesToWrite,
  [out, optional]     LPDWORD      lpNumberOfBytesWritten,
  [in, out, optional] LPOVERLAPPED lpOverlapped
);

BOOL ReadFile(
  [in]                HANDLE       hFile,
  [out]               LPVOID       lpBuffer,
  [in]                DWORD        nNumberOfBytesToRead,
  [out, optional]     LPDWORD      lpNumberOfBytesRead,
  [in, out, optional] LPOVERLAPPED lpOverlapped
);
```



<img src="D:\Cyber-Security\LM Forensics, Malware, and Penetration Testing\assignment3\assignment3-team6-report\img\Call Trees.png" alt="Call Trees" style="zoom:50%;" />

## 函数分析

### AES_Encrypt_140007080

### EncryptAndRenameFiles_140007590

```c++
    do
    {
      /* Exclude Directory */
      if ((local_10e8.dwFileAttributes & 0x10) == 0)
      {
        CopyWPath_140007bc0(local_a68, 0x104, dir);
        input_addr = local_a68;
        ConcatWPath_140007b20(input_addr, 0x104, local_10e8.cFileName);
        GetModuleFileNameW((HMODULE)0x0, local_858, 0x104);
        thunk_FUN_14000c700((undefined8 *)local_e98,
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
            ConcatWPath_140007b20(output_addr, 0x104, (short *)&DAT_140070fd8);
            ConcatWPath_140007b20(output_addr, 0x104, local_10e8.cFileName);
            AES_Encrypt_140007080(input_addr, output_addr);
            DeleteFileW(input_addr);
          }
        }
      }
      BVar3 = FindNextFileW(local_1110, &local_10e8);
    } 
```



下面是对代码逻辑的详细分析，说明了AES加密针对哪些文件：

1. **遍历文件列表**
    代码通过调用 Windows API 函数 `FindFirstFileW` 和 `FindNextFileW` 遍历指定目录下的所有文件。

   ```c
   if ((local_10e8.dwFileAttributes & 0x10) == 0) {
       // 处理非目录文件
       ...
   }
   ```

   只有当文件的属性不包含目录标记（即 `dwFileAttributes & 0x10 == 0`）时，才认为是普通文件，从而进入后续处理流程。

2. **排除已经加密的文件**
    在处理每个文件时，代码先调用 `thunk_FUN_14000c700`，将文件名的前6个字符复制到 `local_e98` 中，然后与字符串 `"~en"` 进行比较：

   ```c
   iVar2 = wcscmp(local_e98, L"~en");
   if (iVar2 != 0) {
       ...
   }
   ```

   如果文件名的前6个字符为 `"~en"`，则认为该文件已经被处理过（或作为特殊标识），不再对其进行加密。

3. **排除自身文件**
    通过调用 `GetModuleFileNameW` 得到当前程序（恶意软件）的完整路径，并使用 `PathFindFileNameW` 提取出文件名后，代码将当前正在处理的文件名与之进行比较：

   ```c
   _Str2 = PathFindFileNameW(local_858);
   iVar2 = wcscmp(local_10e8.cFileName, _Str2);
   if (iVar2 != 0) {
       ...
   }
   ```

   如果发现文件名与当前程序自身相同，则不会对其进行加密，从而避免加密恶意软件自身。

4. **执行AES加密**
    如果满足上述条件（文件不是目录、文件名不以 `"~en"` 开头且不是恶意软件自身），则构造目标输出路径，并调用 `AES_Encrypt_140007080` 对文件进行AES加密。加密完成后，原始文件会通过 `DeleteFileW` 被删除。

   ```c
   AES_Encrypt_140007080(input_addr, output_addr);
   DeleteFileW(input_addr);
   ```

------

#### **总结**

**AES加密针对的是：**

- 指定目录下的所有**普通文件**（即非目录文件），
- **排除**文件名前6个字符为 `"~en"` 的文件（通常代表已经加密或标记过的文件），
- **排除**当前程序自身（防止自我加密）。

这一逻辑保证了加密操作仅作用于用户的数据文件，而不会干扰恶意软件自身或已经加密的文件。



### RansomwareProcessor_140008240

```c++
  WCHAR dir [264];

  printf((char *)L"Getting current directory. ");
  GetCurrentDirectoryW(0x104,dir);
  EncryptAndRenameFiles_140007590(dir);
```



## Appendix

**恶意软件样本相关数据**

- 反汇编/反编译代码的关键片段（如加密算法实现、密钥处理逻辑）
- 发现的配置数据（如硬编码密钥、加密路径、C2服务器地址）
- 重要的寄存器/内存地址信息（如存放密钥的位置）

**加密目标相关数据**

- 恶意软件加密的示例文件（Hank 备份中的加密文件示例，最好是小文件）
- 加密前后文件的对比（如相同文件在加密前后的结构变化）
- 如果找到解密密钥，解密后的示例文件

**分析过程中的日志或工具输出**

- 逆向工程工具的分析结果（如 Ghidra 反编译代码的截图、Radare2 分析的寄存器值）
- 调试工具（如 x64dbg、WinDbg）的关键日志
- 用于解密的 Python/C 程序代码及运行结果



## Academic Conduct & Plagiarism:

We take plagiarism seriously. By submitting your solution, you agree that:

1. The submission is your group's own work and that you have not worked with others in preparing this assignment.
2. Your submitted solutions and report were written by you and **in your own words**, except for any materials from published or other sources which are clearly indicated and acknowledged as such by appropriate referencing.
3. The work is not copied from any other person's work (published or unpublished), web site, book or other source, and has not previously been submitted for assessment either at the University of Birmingham or elsewhere.
4. You have not asked, or paid, others to prepare any part of this work.
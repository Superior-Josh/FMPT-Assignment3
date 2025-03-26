
/* WARNING: Function: _guard_dispatch_icall replaced with injection:
   guard_dispatch_icall */

ulonglong RansomwareEntryPoint_14000afe0(void)

{
  code *pcVar1;
  bool bVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  longlong *plVar6;
  ulonglong uVar7;
  ulonglong *puVar8;
  undefined8 unaff_RBX;

  uVar3 = (uint)unaff_RBX;
  uVar4 = __scrt_initialize_crt(1);
  if ((char)uVar4 == '\0')
  {
    thunk_FUN_14000be5c(7);
  }
  else
  {
    bVar2 = false;
    uVar4 = __scrt_acquire_startup_lock();
    uVar3 = (uint)CONCAT71((int7)((ulonglong)unaff_RBX >> 8), (char)uVar4);
    if (DAT_140087828 != 1)
    {
      if (DAT_140087828 == 0)
      {
        DAT_140087828 = 1;
        uVar5 = _initterm_e((undefined8 *)&DAT_140070330,
                            (undefined8 *)&DAT_1400707a0);
        if ((int)uVar5 != 0)
        {
          return 0xff;
        }
        _initterm((undefined8 *)&DAT_140070000, (undefined8 *)&DAT_140070220);
        DAT_140087828 = 2;
      }
      else
      {
        bVar2 = true;
      }
      __scrt_release_startup_lock((char)uVar4);
      plVar6 = (longlong *)thunk_FUN_14000be38();
      if ((*plVar6 != 0) &&
          (uVar7 = __scrt_is_nonwritable_in_current_image((longlong)plVar6),
           (char)uVar7 != '\0'))
      {
        (*(code *)*plVar6)(0);
      }
      puVar8 = (ulonglong *)thunk_FUN_14000be44();
      if ((*puVar8 != 0) &&
          (uVar7 = __scrt_is_nonwritable_in_current_image((longlong)puVar8),
           (char)uVar7 != '\0'))
      {
        _register_thread_local_exe_atexit_callback(*puVar8);
      }
      __scrt_get_show_window_mode();
      _get_wide_winmain_command_line();
      uVar3 = RansomwareProcessor();
      uVar7 = __scrt_is_managed_app();
      if ((char)uVar7 != '\0')
      {
        if (!bVar2)
        {
          _cexit();
        }
        __scrt_uninitialize_crt(true, '\0');
        return (ulonglong)uVar3;
      }
      goto LAB_14000b141;
    }
  }
  thunk_FUN_14000be5c(7);
LAB_14000b141:
  thunk_FUN_14003fe9c(uVar3);
  thunk_FUN_14003fe38(uVar3);
  pcVar1 = (code *)swi(3);
  uVar7 = (*pcVar1)();
  return uVar7;
}

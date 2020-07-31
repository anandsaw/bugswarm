
/* WARNING: Function: __x86.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void swish_init(void)

{
  Sforeign_symbol("osi_bind_statement",_DAT_00024004);
  Sforeign_symbol("osi_chmod",_DAT_0002400c);
  Sforeign_symbol("osi_clear_statement_bindings",_DAT_00024010);
  Sforeign_symbol("osi_close_SHA1",_DAT_00024014);
  Sforeign_symbol("osi_close_database",_DAT_00024018);
  Sforeign_symbol("osi_close_path_watcher",_DAT_0002401c);
  Sforeign_symbol("osi_close_port",_DAT_00024020);
  Sforeign_symbol("osi_close_tcp_listener",_DAT_00024024);
  Sforeign_symbol("osi_connect_tcp",_DAT_00024028);
  Sforeign_symbol("osi_exit",_DAT_0002402c);
  Sforeign_symbol("osi_finalize_statement",_DAT_00024030);
  Sforeign_symbol("osi_get_SHA1",_DAT_00024034);
  Sforeign_symbol("osi_get_argv",_DAT_00024038);
  Sforeign_symbol("osi_get_bytes_used",_DAT_0002403c);
  Sforeign_symbol("osi_get_callbacks",_DAT_00024040);
  Sforeign_symbol("osi_get_error_text",_DAT_00024044);
  Sforeign_symbol("osi_get_executable_path",_DAT_00024048);
  Sforeign_symbol("osi_get_file_size",_DAT_0002404c);
  Sforeign_symbol("osi_get_hostname",_DAT_00024050);
  Sforeign_symbol("osi_get_hrtime",_DAT_00024054);
  Sforeign_symbol("osi_get_ip_address",_DAT_00024058);
  Sforeign_symbol("osi_get_last_insert_rowid",_DAT_0002405c);
  Sforeign_symbol("osi_get_pid",_DAT_00024060);
  Sforeign_symbol("osi_get_real_path",_DAT_00024064);
  Sforeign_symbol("osi_get_sqlite_status",_DAT_00024068);
  Sforeign_symbol("osi_get_stat",_DAT_0002406c);
  Sforeign_symbol("osi_get_statement_columns",_DAT_00024070);
  Sforeign_symbol("osi_get_statement_expanded_sql",_DAT_00024074);
  Sforeign_symbol("osi_get_tcp_listener_port",_DAT_00024078);
  Sforeign_symbol("osi_get_temp_directory",_DAT_0002407c);
  Sforeign_symbol("osi_get_time",_DAT_00024080);
  Sforeign_symbol("osi_hash_data",_DAT_00024084);
  Sforeign_symbol("osi_init",_DAT_00024088);
  Sforeign_symbol("osi_interrupt_database",_DAT_0002408c);
  Sforeign_symbol("osi_is_quantum_over",_DAT_00024090);
  Sforeign_symbol("osi_kill",_DAT_00024094);
  Sforeign_symbol("osi_list_directory",_DAT_00024098);
  Sforeign_symbol("osi_list_uv_handles",_DAT_0002409c);
  Sforeign_symbol("osi_listen_tcp",_DAT_000240a0);
  Sforeign_symbol("osi_make_directory",_DAT_000240a4);
  Sforeign_symbol("osi_make_uuid",_DAT_000240a8);
  Sforeign_symbol("osi_open_SHA1",_DAT_000240ac);
  Sforeign_symbol("osi_open_database",_DAT_000240b0);
  Sforeign_symbol("osi_open_fd",_DAT_000240b4);
  Sforeign_symbol("osi_open_file",_DAT_000240b8);
  Sforeign_symbol("osi_prepare_statement",_DAT_000240bc);
  Sforeign_symbol("osi_read_port",_DAT_000240c0);
  Sforeign_symbol("osi_remove_directory",_DAT_000240c4);
  Sforeign_symbol("osi_rename",_DAT_000240c8);
  Sforeign_symbol("osi_reset_statement",_DAT_000240cc);
  Sforeign_symbol("osi_set_quantum",_DAT_000240d0);
  Sforeign_symbol("osi_start_signal",_DAT_000240d4);
  Sforeign_symbol("osi_stop_signal",_DAT_000240d8);
  Sforeign_symbol("osi_spawn",_DAT_000240dc);
  Sforeign_symbol("osi_spawn_detached",_DAT_000240e0);
  Sforeign_symbol("osi_step_statement",_DAT_000240e4);
  Sforeign_symbol("osi_unlink",_DAT_000240e8);
  Sforeign_symbol("osi_watch_path",_DAT_000240ec);
  Sforeign_symbol("osi_write_port",_DAT_000240f0);
  if (g_aux_init != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000104ba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*g_aux_init)();
    return;
  }
  return;
}


/* WARNING: Function: __x86.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void * get_boot_fn(void)

{
  FILE **ppFVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  void *__dest;
  uint *puVar6;
  uint *puVar7;
  size_t __n;
  int in_GS_OFFSET;
  bool bVar8;
  undefined4 local_8024;
  uint local_8020 [8192];
  int local_20;
  undefined4 uStack20;
  
  uStack20 = 0x104d9;
  local_20 = *(int *)(in_GS_OFFSET + 0x14);
  local_8024 = 0x8000;
  iVar3 = uv_exepath(local_8020,&local_8024);
  ppFVar1 = _GLOBAL_OFFSET_TABLE_;
  if (-1 < iVar3) {
    *(char **)(_GLOBAL_OFFSET_TABLE_ + 0x395) = "function_inlined: strlen";
    *(char **)(ppFVar1 + 0x7c8) = "function_inlined: strlen";
    puVar7 = local_8020;
    do {
      puVar6 = puVar7;
      uVar4 = *puVar6 + 0xfefefeff & ~*puVar6;
      uVar5 = uVar4 & 0x80808080;
      puVar7 = puVar6 + 1;
    } while (uVar5 == 0);
    bVar8 = (uVar4 & 0x8080) == 0;
    bVar2 = (byte)uVar5;
    if (bVar8) {
      bVar2 = (byte)(uVar5 >> 0x10);
    }
    if (bVar8) {
      puVar7 = (uint *)((int)puVar6 + 6);
    }
    __n = (int)puVar7 + ((-3 - (uint)CARRY1(bVar2,bVar2)) - (int)local_8020);
    __dest = malloc(__n + 6);
    if (__dest == (void *)0x0) {
      *(char **)(ppFVar1 + 0x612) = "function_inlined: fprintf";
      fwrite("malloc failed\n",1,0xe,*_GLOBAL_OFFSET_TABLE_);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    *(char **)(ppFVar1 + 0x542) = "function_inlined: strrchr";
    memcpy(__dest,local_8020,__n);
    iVar3 = *(int *)(in_GS_OFFSET + 0x14);
    *(undefined4 *)((int)__dest + __n) = 0x6f6f622e;
    *(undefined *)((undefined4 *)((int)__dest + __n) + 1) = 0x74;
    *(undefined *)((int)__dest + __n + 5) = 0;
    if (local_20 == iVar3) {
      return __dest;
    }
    __stack_chk_fail_local();
  }
  perror("uv_exepath");
                    /* WARNING: Subroutine does not return */
  exit(1);
}


/* WARNING: Function: __x86.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void __regparm3 scheme_init(int param_1,undefined4 *param_2,undefined4 param_3)

{
  char *__s;
  size_t sVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  bool bVar5;
  bool bVar6;
  byte bVar7;
  
  bVar7 = 0;
  __s = (char *)get_boot_fn();
  Sscheme_init(0);
  bVar5 = param_1 == 0;
  bVar6 = param_1 == 1;
  *(undefined4 *)(_GLOBAL_OFFSET_TABLE_ + 0x7d4) = 0x110ac;
  if (1 < param_1) {
    iVar2 = 10;
    pbVar3 = (byte *)param_2[1];
    pbVar4 = (byte *)"--verbose";
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar5 = *pbVar3 < *pbVar4;
      bVar6 = *pbVar3 == *pbVar4;
      pbVar3 = pbVar3 + (uint)bVar7 * -2 + 1;
      pbVar4 = pbVar4 + (uint)bVar7 * -2 + 1;
    } while (bVar6);
    if ((!bVar5 && !bVar6) == bVar5) {
      sVar1 = strlen(__s);
      bVar5 = sVar1 < 10;
      bVar6 = sVar1 == 10;
      if (10 < sVar1) {
        iVar2 = 0xb;
        pbVar3 = (byte *)(__s + (sVar1 - 0xb));
        pbVar4 = (byte *)"/swish.boot";
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar5 = *pbVar3 < *pbVar4;
          bVar6 = *pbVar3 == *pbVar4;
          pbVar3 = pbVar3 + (uint)bVar7 * -2 + 1;
          pbVar4 = pbVar4 + (uint)bVar7 * -2 + 1;
        } while (bVar6);
        if ((!bVar5 && !bVar6) == bVar5) {
          Sset_verbose(1);
        }
      }
    }
  }
  Sregister_boot_file(__s);
  osi_set_argv(param_1,param_2);
  g_aux_init = param_3;
  Sbuild_heap(*param_2,0x10000);
  free(__s);
  osi_init();
  return;
}


/* WARNING: Function: __x86.get_pc_thunk.cx replaced with injection: get_pc_thunk_cx */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __regparm3 swish_start(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  *(undefined4 *)(_GLOBAL_OFFSET_TABLE_ + 0x748) = 0x110db;
  iVar2 = _setjmp(_DAT_00026070);
  iVar1 = _GLOBAL_OFFSET_TABLE_;
  if (iVar2 == 0) {
    *(undefined4 *)(_GLOBAL_OFFSET_TABLE_ + 0x9c) = 1;
    uVar3 = Sscheme_start(param_1,param_2);
    *(undefined4 *)(iVar1 + 0xa0) = uVar3;
  }
  Sscheme_deinit();
  return *(undefined4 *)(_GLOBAL_OFFSET_TABLE_ + 0xa0);
}


/* WARNING: Function: __x86.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void process_sd_bus_message(void)

{
  int iVar1;
  undefined4 uVar2;
  int in_GS_OFFSET;
  undefined4 local_14;
  int local_10;
  undefined4 uStack12;
  
  uStack12 = 0x107a7;
  local_10 = *(int *)(in_GS_OFFSET + 0x14);
  local_14 = 0;
  while( true ) {
    iVar1 = sd_bus_process(system_bus,&local_14);
    if (iVar1 == 0) break;
    sd_bus_message_unref(local_14);
  }
  if (local_10 == *(int *)(in_GS_OFFSET + 0x14)) {
    return;
  }
  uVar2 = __stack_chk_fail_local();
  uVar2 = Sstring_to_symbol(uVar2);
  uVar2 = Stop_level_value(uVar2);
  osi_add_callback_list(uVar2,0x26);
  return;
}


/* WARNING: Function: __x86.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void __regparm3 request_call(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = Sstring_to_symbol(param_1);
  uVar1 = Stop_level_value(uVar1);
  osi_add_callback_list(uVar1,0x26);
  return;
}


/* WARNING: Function: __x86.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void __regparm3 match_login1_manager_signal(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  int in_GS_OFFSET;
  undefined local_110 [256];
  int local_10;
  
  local_10 = *(int *)(in_GS_OFFSET + 0x14);
  uVar1 = __snprintf_chk(local_110,0x100,1,0x100,
                                                  
                         "type=\'signal\',sender=\'org.freedesktop.login1\',path=\'/org/freedesktop/login1\',interface=\'org.freedesktop.login1.Manager\',member=\'%s\'"
                         ,param_1);
  if (0xff < uVar1) {
    perror("snprintf");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  iVar2 = sd_bus_add_match(system_bus,0,local_110,handle_message,param_1);
  if (-1 < iVar2) {
    if (local_10 == *(int *)(in_GS_OFFSET + 0x14)) {
      return;
    }
    __stack_chk_fail_local();
  }
  perror("sd_bus_add_match");
                    /* WARNING: Subroutine does not return */
  exit(1);
}


/* WARNING: Function: __x86.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

int handle_message(undefined4 param_1,int param_2)

{
  int __status;
  int in_GS_OFFSET;
  int local_24;
  int local_20;
  undefined4 uStack20;
  
  uStack20 = 0x10919;
  local_20 = *(int *)(in_GS_OFFSET + 0x14);
  __status = sd_bus_message_has_signature(param_1,&LC73);
  if (__status == 0) {
    __status = -0x26;
  }
  else {
    __status = sd_bus_message_read(param_1,&LC73,&local_24);
    if (-1 < __status) {
      if (*_GLOBAL_OFFSET_TABLE_ == param_2) {
        if (local_24 != 0) {
          sd_notify(0,"STOPPING=1");
          request_call();
          __status = 0;
          goto LAB_0001097c;
        }
        __status = local_24;
        if (*_GLOBAL_OFFSET_TABLE_ != *_GLOBAL_OFFSET_TABLE_) goto LAB_0001097c;
      }
      else {
        __status = 0;
        if (*_GLOBAL_OFFSET_TABLE_ != param_2) goto LAB_0001097c;
      }
      request_call();
      __status = 0;
    }
  }
LAB_0001097c:
  if (local_20 == *(int *)(in_GS_OFFSET + 0x14)) {
    return __status;
  }
  __stack_chk_fail_local();
  scheme_init(&_GLOBAL_OFFSET_TABLE_,param_2,param_1);
  __status = swish_start();
  if (_GLOBAL_OFFSET_TABLE_[0x29] == 0) {
    return __status;
  }
                    /* WARNING: Subroutine does not return */
  _exit(__status);
}


/* WARNING: Function: __x86.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void swish_run(void)

{
  int __status;
  
  scheme_init();
  __status = swish_start();
  if (*(int *)(_GLOBAL_OFFSET_TABLE_ + 0xa4) == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  _exit(__status);
}


/* WARNING: Function: __x86.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

int swish_service(void)

{
  undefined4 *puVar1;
  int __status;
  int iVar2;
  
  scheme_init();
  __status = sd_bus_default_system(&system_bus);
  if (__status < 0) {
    perror("sd_bus_default_system");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  __status = sd_bus_get_fd(system_bus);
  puVar1 = _GLOBAL_OFFSET_TABLE_;
  if (__status < 0) {
    perror("sd_bus_get_fd");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  __status = uv_poll_init(*_GLOBAL_OFFSET_TABLE_,poll_handle,__status);
  if (__status != 0) {
    perror("uv_poll_init");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  match_login1_manager_signal();
  match_login1_manager_signal();
  __status = uv_poll_start(poll_handle,0xd,process_sd_bus_message);
  if (__status == 0) {
    sd_notify(0,"READY=1");
    __status = swish_start();
    sd_bus_unref(system_bus);
    uv_poll_stop(poll_handle);
    uv_close(poll_handle,0);
    osi_get_callbacks(0,0);
    iVar2 = uv_loop_close(*puVar1);
    _GLOBAL_OFFSET_TABLE_[0x29] = iVar2;
    if (iVar2 == 0) {
      return __status;
    }
                    /* WARNING: Subroutine does not return */
    _exit(__status);
  }
  perror("uv_poll_start");
                    /* WARNING: Subroutine does not return */
  exit(1);
}


/* WARNING: This is an inlined function */

void __x86_get_pc_thunk_cx(void)

{
  return;
}


/* WARNING: This is an inlined function */

void __x86_get_pc_thunk_bx(void)

{
  return;
}


/* WARNING: Control flow encountered bad instruction data */

void Sforeign_symbol(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void osi_get_callbacks(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void osi_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void uv_exepath(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void * malloc(size_t __size)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void * memcpy(void *__dest,void *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void exit(int __status)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void __stack_chk_fail_local(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void perror(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void Sscheme_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

size_t strlen(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void Sset_verbose(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void Sregister_boot_file(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void osi_set_argv(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void Sbuild_heap(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void free(void *__ptr)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int _setjmp(__jmp_buf_tag *__env)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void Sscheme_deinit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void Sscheme_start(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void sd_bus_message_unref(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void sd_bus_process(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void Sstring_to_symbol(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void Stop_level_value(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void osi_add_callback_list(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void __snprintf_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void sd_bus_add_match(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void sd_bus_message_has_signature(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void sd_bus_message_read(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void sd_notify(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void _exit(int __status)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void sd_bus_default_system(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void sd_bus_get_fd(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void uv_poll_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void uv_poll_start(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void sd_bus_unref(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void uv_poll_stop(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void uv_close(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void uv_loop_close(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


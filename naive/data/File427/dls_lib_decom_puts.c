
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
tsk_fs_blkls(long param_1,ulong param_2,undefined8 param_3,undefined8 param_4,uint param_5)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  time_t tVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  code *pcVar7;
  undefined8 local_2028 [1023];
  undefined local_29;
  
  if ((param_2 & 4) == 0) {
    if ((param_2 & 2) == 0) {
      pcVar7 = print_block;
    }
    else {
      iVar1 = gethostname((char *)local_2028,0x1fff);
      uVar5 = stderr;
      if (iVar1 < 0) {
        if (_tsk_verbose != 0) {
          piVar2 = __errno_location();
          pcVar3 = strerror(*piVar2);
          tsk_fprintf(uVar5,"blkls_lib: error getting hostname: %s\n",pcVar3,pcVar3);
        }
        marker296._14152_8_ = "function_inlined: strcpy";
        local_2028[0] = 0x6e776f6e6b6e75;
      }
      local_29 = 0;
      marker296._15960_8_ = "function_inlined: strcpy";
      tsk_printf();
      tVar4 = time((time_t *)0x0);
      tsk_printf("blkls|%s||%lu|%s\n",local_2028,tVar4);
      tsk_printf("addr|alloc\n");
      param_5 = param_5 | 0x10;
      pcVar7 = print_list;
    }
    uVar5 = tsk_fs_block_walk(param_1,param_3,param_4,(ulong)param_5,pcVar7,local_2028);
  }
  else {
    uVar5 = (**(code **)(param_1 + 0x128))
                      (param_1,*(undefined8 *)(param_1 + 0x28),*(undefined8 *)(param_1 + 0x30),1,
                       slack_inode_act,local_2028);
  }
  uVar6 = CONCAT71((int7)((ulong)uVar5 >> 8),1);
  if ((char)uVar5 == '\0') {
    uVar6 = 0;
  }
  return uVar6;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 slack_inode_act(long param_1,undefined8 *param_2)

{
  char cVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"slack_inode_act: Processing meta data: %lu\n",
                *(undefined8 *)(*(long *)(param_1 + 0x10) + 8));
  }
  if ((*(byte *)(*(long *)(param_1 + 0x18) + 0x70) & 1) == 0) {
    *param_2 = *(undefined8 *)(*(long *)(param_1 + 0x10) + 0x20);
    cVar1 = tsk_fs_file_walk(param_1,1,slack_file_act,param_2);
    if (cVar1 != '\0') {
      if (_tsk_verbose != 0) {
        tsk_fprintf(stderr,"slack_inode_act: error walking file: %lu",
                    *(undefined8 *)(*(long *)(param_1 + 0x10) + 8));
      }
      tsk_error_reset();
    }
  }
  else {
    uVar2 = tsk_fs_file_attr_getsize(param_1);
    if (0 < (int)uVar2) {
      uVar4 = 0;
      do {
        lVar3 = tsk_fs_file_attr_get_idx(param_1,(ulong)uVar4);
        if ((lVar3 != 0) && ((*(byte *)(lVar3 + 0x10) & 2) != 0)) {
          *param_2 = *(undefined8 *)(lVar3 + 0x30);
          cVar1 = tsk_fs_file_walk_type
                            (param_1,(ulong)*(uint *)(lVar3 + 0x28),(ulong)*(ushort *)(lVar3 + 0x2c)
                             ,1,slack_file_act,param_2);
          if (cVar1 != '\0') {
            if (_tsk_verbose != 0) {
              tsk_fprintf(stderr,"slack_inode_act: error walking file: %lu",
                          *(undefined8 *)(*(long *)(param_1 + 0x10) + 8));
            }
            tsk_error_reset();
          }
        }
        uVar4 = uVar4 + 1;
      } while (uVar2 != uVar4);
    }
  }
  return 0;
}


undefined8 print_list(long param_1)

{
  undefined *puVar1;
  
  puVar1 = &DAT_00100541;
  if ((*(uint *)(param_1 + 0x20) & 1) == 0) {
    puVar1 = &DAT_00100543;
  }
  tsk_printf("%lu|%s\n",*(undefined8 *)(param_1 + 0x18),puVar1);
  return 0;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 print_block(long param_1)

{
  size_t sVar1;
  int *piVar2;
  char *pcVar3;
  undefined8 uVar4;
  
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"write block %lu\n",*(undefined8 *)(param_1 + 0x18));
  }
  sVar1 = fwrite(*(void **)(param_1 + 0x10),(ulong)*(uint *)(*(long *)(param_1 + 8) + 0x58),1,stdout
                );
  uVar4 = 0;
  if (sVar1 != 1) {
    tsk_error_reset();
    tsk_error_set_errno();
    piVar2 = __errno_location();
    pcVar3 = strerror(*piVar2);
    tsk_error_set_errstr("blkls_lib: error writing to stdout: %s",pcVar3);
    uVar4 = 2;
  }
  return uVar4;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
slack_file_act(long param_1,undefined8 param_2,undefined8 param_3,void *param_4,size_t param_5,
              undefined8 param_6,size_t *param_7)

{
  size_t __n;
  int *piVar1;
  char *pcVar2;
  undefined8 uVar3;
  
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"slack_file_act: File: %lu Remaining File:  %ld  Buffer: %u\n",
                *(undefined8 *)(*(long *)(param_1 + 0x10) + 8),*param_7,param_5);
  }
  __n = *param_7;
  if ((long)__n < (long)param_5) {
    if (__n != 0) {
      memset(param_4,0,__n);
      *param_7 = 0;
    }
    __n = fwrite(param_4,param_5,1,stdout);
    uVar3 = 0;
    if (__n != 1) {
      tsk_error_reset();
      tsk_error_set_errno();
      piVar1 = __errno_location();
      pcVar2 = strerror(*piVar1);
      tsk_error_set_errstr("blkls_lib: error writing to stdout: %s",pcVar2);
      uVar3 = 2;
    }
  }
  else {
    *param_7 = __n - param_5;
    uVar3 = 0;
  }
  return uVar3;
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int * __errno_location(void)

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

int gethostname(char *__name,size_t __len)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void * memset(void *__s,int __c,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

char * strerror(int __errnum)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

time_t time(time_t *__timer)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_error_reset(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_error_set_errno(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_error_set_errstr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fprintf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_block_walk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_file_attr_get_idx(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_file_attr_getsize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_file_walk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_file_walk_type(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_printf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


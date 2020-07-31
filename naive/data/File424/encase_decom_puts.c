
ulong encase_test(FILE *param_1)

{
  long in_RAX;
  size_t sVar1;
  ulong uVar2;
  long local_18;
  
  uVar2 = 0;
  local_18 = in_RAX;
  fseeko(param_1,0,0);
  sVar1 = fread(&local_18,1,8,param_1);
  if (sVar1 == 8) {
    uVar2 = (ulong)(local_18 == 0xff0a0d48534148);
  }
  return uVar2;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long encase_open(void)

{
  FILE *__stream;
  long lVar1;
  size_t sVar2;
  void *local_d8;
  wchar_t *local_d0;
  wchar_t local_c8 [4];
  undefined4 local_b8;
  undefined4 uStack180;
  undefined4 uStack176;
  undefined4 uStack172;
  undefined8 local_a8;
  
  lVar1 = hdb_binsrch_open();
  if (lVar1 == 0) {
    return 0;
  }
  *(undefined4 *)(lVar1 + 0x208) = 5;
  __stream = *(FILE **)(lVar1 + 0x2c0);
  local_d8 = (void *)(lVar1 + 8);
  memset(local_d8,0,0x200);
  if (__stream != (FILE *)0x0) {
    local_b8 = 0;
    uStack180 = 0;
    uStack176 = 0;
    uStack172 = 0;
    local_c8[0] = L'\0';
    local_c8[1] = 0;
    local_c8[2] = 0;
    local_c8[3] = 0;
    local_a8 = 0;
    fseeko(__stream,0x408,0);
    local_d0 = local_c8;
    sVar2 = fread(local_d0,4,0x27,__stream);
    if (sVar2 == 0x27) {
      sVar2 = wcslen(local_d0);
      tsk_UTF16toUTF8(1,&local_d0,local_c8 + sVar2,&local_d8,lVar1 + 0x56,1);
      goto LAB_00100128;
    }
  }
  if (_tsk_verbose != 0) {
    fwrite("Error getting name from Encase hash db; using file name instead",0x3f,1,stderr);
  }
  hdb_base_db_name_from_path(lVar1);
LAB_00100128:
  *(undefined8 *)(lVar1 + 0x268) = 0x100180;
  *(undefined8 *)(lVar1 + 0x2c8) = 0x100380;
  return lVar1;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 encase_make_index(undefined8 *param_1)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  size_t sVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  long lVar8;
  undefined auVar9 [16];
  undefined local_68 [16];
  ushort local_58;
  undefined local_56;
  undefined local_48 [16];
  ushort local_38;
  undefined local_36;
  
  cVar1 = hdb_binsrch_idx_initialize();
  if (cVar1 == '\0') {
    if (_tsk_verbose != 0) {
      fprintf(stderr,"Extracting Data from Database (%s)\n",*param_1);
    }
    marker269._2896_8_ = "function_inlined: memset";
    local_48 = _LCPI2_0;
    local_36 = 0x30;
    local_38 = 0x3030;
    marker269._6856_8_ = "function_inlined: memset";
    local_68 = _LCPI2_0;
    local_56 = 0x30;
    local_58 = 0x3030;
    lVar8 = 0;
    fseek((FILE *)param_1[0x58],0x480,0);
    uVar5 = 0;
    uVar7 = 0;
    while (sVar4 = fread(local_68,1,0x12,(FILE *)param_1[0x58]), sVar4 == 0x12) {
      uVar5 = uVar5 + 1;
      marker269._8312_8_ = "function_inlined: memcmp";
      uVar3 = CONCAT17(0xff,CONCAT16(0xff,CONCAT15(0xff,CONCAT14(0xff,CONCAT13(0xff,CONCAT12(0xff,
                                                  CONCAT11(-((char)(local_38 >> 8) ==
                                                            SUB161(ZEXT816((ulong)local_58) >> 8,0))
                                                           ,-((char)local_38 == (char)local_58))))))
                                    ));
      auVar9 = CONCAT115(-(SUB161(local_68 >> 0x78,0) == local_48[15]),
                         CONCAT114(-(SUB161(local_68 >> 0x70,0) == local_48[14]),
                                   CONCAT113(-(SUB161(local_68 >> 0x68,0) == local_48[13]),
                                             CONCAT112(-(SUB161(local_68 >> 0x60,0) == local_48[12])
                                                       ,CONCAT111(-(SUB161(local_68 >> 0x58,0) ==
                                                                   local_48[11]),
                                                                  CONCAT110(-(SUB161(local_68 >>
                                                                                     0x50,0) ==
                                                                             local_48[10]),
                                                                            CONCAT19(-(SUB161(
                                                  local_68 >> 0x48,0) == local_48[9]),
                                                  CONCAT18(-(SUB161(local_68 >> 0x40,0) ==
                                                            local_48[8]),
                                                           CONCAT17(-(SUB161(local_68 >> 0x38,0) ==
                                                                     local_48[7]),
                                                                    CONCAT16(-(SUB161(local_68 >>
                                                                                      0x30,0) ==
                                                                              local_48[6]),
                                                                             CONCAT15(-(SUB161(
                                                  local_68 >> 0x28,0) == local_48[5]),
                                                  CONCAT14(-(SUB161(local_68 >> 0x20,0) ==
                                                            local_48[4]),
                                                           CONCAT13(-(SUB161(local_68 >> 0x18,0) ==
                                                                     local_48[3]),
                                                                    CONCAT12(-(SUB161(local_68 >>
                                                                                      0x10,0) ==
                                                                              local_48[2]),
                                                                             CONCAT11(-(SUB161(
                                                  local_68 >> 8,0) == local_48[1]),
                                                  -(SUB161(local_68,0) == local_48[0])))))))))))))))
                        ) &
               CONCAT115(0xff,CONCAT114(0xff,CONCAT113(0xff,CONCAT112(0xff,CONCAT111(0xff,CONCAT110(
                                                  0xff,CONCAT19(0xff,CONCAT18(0xff,uVar3))))))));
      iVar2 = pmovmskb((uint)local_58,auVar9);
      if (iVar2 != 0xffff) {
        cVar1 = hdb_binsrch_idx_add_entry_bin
                          (SUB168(auVar9,0),(ulong)local_58,uVar3,param_1,local_68,0x10,lVar8);
        if (cVar1 != '\0') {
          pcVar6 = "encase_make_index";
          goto LAB_0010019d;
        }
        uVar7 = uVar7 + 1;
        marker269._12160_8_ = "function_inlined: memcpy";
        local_48 = local_68;
        local_38 = local_58;
        lVar8 = lVar8 + 0x12;
      }
    }
    if (uVar7 == 0) {
      tsk_error_reset();
      tsk_error_set_errno(0x1000000b);
      uVar3 = tsk_error_set_errstr("encase_makeindex: No valid entries found in database");
      goto LAB_001001a4;
    }
    if (_tsk_verbose != 0) {
      fprintf(stderr,"  Valid Database Entries: %d\n",(ulong)uVar5);
      pcVar6 = "(optimized)";
      if (uVar7 == uVar5) {
        pcVar6 = "";
      }
      fprintf(stderr,"  Index File Entries %s: %d\n",pcVar6,(ulong)uVar7);
    }
    cVar1 = hdb_binsrch_idx_finalize(param_1);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  pcVar6 = "encase_makeindex";
LAB_0010019d:
  uVar3 = tsk_error_set_errstr2(pcVar6);
LAB_001001a4:
  return CONCAT71((int7)((ulong)uVar3 >> 8),1);
}


/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
encase_get_entry(long param_1,char *param_2,char *param_3,undefined8 param_4,code *param_5,
                undefined8 param_6)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  char *__s2;
  undefined8 local_d0;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined2 local_b8;
  undefined local_b6;
  int local_ac;
  char *local_a8;
  char *local_a0;
  code *local_98;
  undefined8 local_90;
  ulong local_88;
  ulong local_80;
  ulong local_78;
  ulong local_70;
  ulong local_68;
  ulong local_60;
  char local_58 [40];
  
  local_98 = param_5;
  local_90 = param_6;
  if (_tsk_verbose != 0) {
    fprintf(stderr,"encase_getentry: Lookup up hash %s at offset %ld\n",param_2,param_3);
  }
  sVar2 = strlen(param_2);
  if (sVar2 == 0x20) {
    marker269._568_8_ = "function_inlined: memset";
    local_c8 = 0;
    local_c4 = 0;
    local_c0 = 0;
    local_bc = 0;
    local_b6 = 0;
    local_b8 = 0;
    iVar3 = 0;
    fseeko(*(FILE **)(param_1 + 0x2c0),(__off_t)param_3,0);
    local_d0 = 0x10040f;
    sVar2 = fread(&local_c8,1,0x12,*(FILE **)(param_1 + 0x2c0));
    if (sVar2 == 0x12) {
      iVar3 = 0;
      local_a0 = param_2;
      do {
        __s2 = local_a0;
        local_60 = (ulong)(uint)(int)local_c8._3_1_;
        local_68 = (ulong)(uint)(int)(char)local_c4;
        local_70 = (ulong)(uint)(int)local_c4._1_1_;
        local_78 = (ulong)(uint)(int)local_c4._2_1_;
        local_80 = (ulong)(uint)(int)local_c4._3_1_;
        local_88 = (ulong)(uint)(int)(char)local_c0;
        local_ac = iVar3;
        local_a8 = param_3;
        snprintf(local_58,0x21,"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
                 (ulong)(uint)(int)(char)local_c8,(ulong)(uint)(int)local_c8._1_1_,
                 (ulong)(uint)(int)local_c8._2_1_,local_60,local_68,local_70,local_78,local_80,
                 local_88,(ulong)(uint)(int)local_c0._1_1_,(ulong)(uint)(int)local_c0._2_1_,
                 (ulong)(uint)(int)local_c0._3_1_,(ulong)(uint)(int)(char)local_bc,
                 (ulong)(uint)(int)local_bc._1_1_,(ulong)(uint)(int)local_bc._2_1_,
                 (ulong)(uint)(int)local_bc._3_1_,local_d0);
        iVar1 = strcasecmp(local_58,__s2);
        param_2 = local_a8;
        iVar3 = local_ac;
        if (iVar1 != 0) goto joined_r0x001005d5;
        local_d0 = (*local_98)(param_1,__s2,&DAT_00100706,local_90);
        if ((int)local_d0 == 1) {
          return 0;
        }
        if ((int)local_d0 == 2) goto LAB_00100597;
        param_3 = local_a8 + 0x12;
        local_d0 = 0x10054f;
        sVar2 = fread(&local_c8,1,0x12,*(FILE **)(param_1 + 0x2c0));
        iVar3 = 1;
      } while (sVar2 == 0x12);
    }
    iVar1 = feof(*(FILE **)(param_1 + 0x2c0));
    param_2 = param_3;
    if (iVar1 == 0) {
      tsk_error_reset();
      tsk_error_set_errno(0x10000002);
      local_d0 = tsk_error_set_errstr("encase_getentry: Error reading database");
      goto LAB_00100597;
    }
joined_r0x001005d5:
    if (iVar3 != 0) {
      return 0;
    }
    tsk_error_reset();
    tsk_error_set_errno(0x10000004);
    __s2 = "encase_getentry: Hash not found in file at offset: %lu";
  }
  else {
    tsk_error_reset();
    tsk_error_set_errno(0x10000004);
    __s2 = "encase_getentry: Invalid hash value: %s";
  }
  local_d0 = tsk_error_set_errstr(__s2,param_2);
LAB_00100597:
  return CONCAT71((int7)((ulong)local_d0 >> 8),1);
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int feof(FILE *__stream)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int fprintf(FILE *__stream,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

size_t fread(void *__ptr,size_t __size,size_t __n,FILE *__stream)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int fseek(FILE *__stream,long __off,int __whence)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int fseeko(FILE *__stream,__off_t __off,int __whence)

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

void hdb_base_db_name_from_path(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void hdb_binsrch_idx_add_entry_bin(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void hdb_binsrch_idx_finalize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void hdb_binsrch_idx_initialize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void hdb_binsrch_open(void)

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

int snprintf(char *__s,size_t __maxlen,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int strcasecmp(char *__s1,char *__s2)

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

void tsk_UTF16toUTF8(void)

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

void tsk_error_set_errstr2(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

size_t wcslen(wchar_t *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


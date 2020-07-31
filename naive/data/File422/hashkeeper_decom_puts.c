
undefined8 hk_test(FILE *param_1)

{
  int iVar1;
  uint uVar2;
  char *__s1;
  size_t __n;
  uint uVar3;
  char *__s2;
  undefined8 uVar4;
  char acStack536 [512];
  
  uVar4 = 0;
  fseek(param_1,0,0);
  __s1 = fgets(acStack536,0x200,param_1);
  if (__s1 != (char *)0x0) {
    __n = strlen(acStack536);
    if ((__n < 0x96) || (iVar1 = strncmp(acStack536,"\"file_id\"",9), iVar1 != 0)) {
LAB_00100055:
      uVar4 = 0;
    }
    else {
      __s1 = strchr(acStack536,0x2c);
      uVar4 = 1;
      if (__s1 != (char *)0x0) {
        uVar3 = 0;
        do {
          if (uVar3 == 0) {
            __s2 = ",\"hashset_id\"";
            __n = 0xd;
          }
          else {
            uVar2 = uVar3 & 0x7fffffff;
            if (uVar2 == 3) {
              __s2 = ",\"hash\"";
              __n = 7;
            }
            else {
              if (uVar2 == 2) {
                __s2 = ",\"directory\"";
              }
              else {
                if (uVar2 != 1) {
                  return 1;
                }
                __s2 = ",\"file_name\"";
              }
              __n = 0xc;
            }
          }
          iVar1 = strncmp(__s1,__s2,__n);
          if (iVar1 != 0) goto LAB_00100055;
          uVar3 = uVar3 + 1;
          __s1 = strchr(__s1 + 1,0x2c);
        } while (__s1 != (char *)0x0);
      }
    }
  }
  return uVar4;
}


long hk_open(void)

{
  long lVar1;
  
  lVar1 = hdb_binsrch_open();
  if (lVar1 != 0) {
    *(undefined4 *)(lVar1 + 0x208) = 3;
    *(undefined8 *)(lVar1 + 0x268) = 0x100160;
    *(undefined8 *)(lVar1 + 0x2c8) = 0x1003b0;
    return lVar1;
  }
  return 0;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 hk_makeindex(undefined8 *param_1)

{
  undefined auVar1 [16];
  char cVar2;
  int iVar3;
  undefined8 uVar4;
  char *pcVar5;
  size_t sVar6;
  uint uVar7;
  long lVar8;
  int iVar9;
  undefined auVar10 [16];
  uint local_278;
  uint local_274;
  char *local_270;
  undefined local_268 [16];
  undefined local_258 [16];
  undefined local_248;
  char local_238 [520];
  
  local_270 = (char *)0x0;
  cVar2 = hdb_binsrch_idx_initialize();
  if (cVar2 == '\0') {
    if (_tsk_verbose != 0) {
      fprintf(stderr,"Extracting Data from Database (%s)\n",*param_1);
    }
    marker264._12984_8_ = "function_inlined: memset";
    local_258 = "0000000000000000\"file_id\""._0_16_;
    local_268 = "0000000000000000\"file_id\""._0_16_;
    local_248 = 0x30;
    iVar9 = 0;
    fseek((FILE *)param_1[0x58],0,0);
    pcVar5 = fgets(local_238,0x200,(FILE *)param_1[0x58]);
    if (pcVar5 != (char *)0x0) {
      uVar7 = 0;
      local_274 = 0;
      local_278 = 0;
      lVar8 = 0;
      sVar6 = 0;
      do {
        if (iVar9 == 0) {
LAB_001002bf:
          uVar7 = uVar7 + 1;
        }
        else {
          sVar6 = strlen(local_238);
          iVar3 = hk_parse_md5(local_238,&local_270,0,0,0,0);
          if (iVar3 != 0) goto LAB_001002bf;
          marker264._13328_8_ = "function_inlined: memcmp";
                    /* WARNING: Load size is inaccurate */
          auVar10 = *(undefined *)local_270;
                    /* WARNING: Load size is inaccurate */
          auVar1 = *(undefined *)(local_270 + 0x10);
          uVar4 = CONCAT17(-(SUB161(auVar1 >> 0x38,0) == local_258[7]),
                           CONCAT16(-(SUB161(auVar1 >> 0x30,0) == local_258[6]),
                                    CONCAT15(-(SUB161(auVar1 >> 0x28,0) == local_258[5]),
                                             CONCAT14(-(SUB161(auVar1 >> 0x20,0) == local_258[4]),
                                                      CONCAT13(-(SUB161(auVar1 >> 0x18,0) ==
                                                                local_258[3]),
                                                               CONCAT12(-(SUB161(auVar1 >> 0x10,0)
                                                                         == local_258[2]),
                                                                        CONCAT11(-(SUB161(auVar1 >> 
                                                  8,0) == local_258[1]),
                                                  -(SUB161(auVar1,0) == local_258[0]))))))));
          local_278 = local_278 + 1;
          auVar10 = CONCAT115(-(SUB161(auVar10 >> 0x78,0) == local_268[15]),
                              CONCAT114(-(SUB161(auVar10 >> 0x70,0) == local_268[14]),
                                        CONCAT113(-(SUB161(auVar10 >> 0x68,0) == local_268[13]),
                                                  CONCAT112(-(SUB161(auVar10 >> 0x60,0) ==
                                                             local_268[12]),
                                                            CONCAT111(-(SUB161(auVar10 >> 0x58,0) ==
                                                                       local_268[11]),
                                                                      CONCAT110(-(SUB161(auVar10 >>
                                                                                         0x50,0) ==
                                                                                 local_268[10]),
                                                                                CONCAT19(-(SUB161(
                                                  auVar10 >> 0x48,0) == local_268[9]),
                                                  CONCAT18(-(SUB161(auVar10 >> 0x40,0) ==
                                                            local_268[8]),
                                                           CONCAT17(-(SUB161(auVar10 >> 0x38,0) ==
                                                                     local_268[7]),
                                                                    CONCAT16(-(SUB161(auVar10 >>
                                                                                      0x30,0) ==
                                                                              local_268[6]),
                                                                             CONCAT15(-(SUB161(
                                                  auVar10 >> 0x28,0) == local_268[5]),
                                                  CONCAT14(-(SUB161(auVar10 >> 0x20,0) ==
                                                            local_268[4]),
                                                           CONCAT13(-(SUB161(auVar10 >> 0x18,0) ==
                                                                     local_268[3]),
                                                                    CONCAT12(-(SUB161(auVar10 >>
                                                                                      0x10,0) ==
                                                                              local_268[2]),
                                                                             CONCAT11(-(SUB161(
                                                  auVar10 >> 8,0) == local_268[1]),
                                                  -(SUB161(auVar10,0) == local_268[0])))))))))))))))
                             ) &
                    CONCAT115(-(SUB161(auVar1 >> 0x78,0) == local_258[15]),
                              CONCAT114(-(SUB161(auVar1 >> 0x70,0) == local_258[14]),
                                        CONCAT113(-(SUB161(auVar1 >> 0x68,0) == local_258[13]),
                                                  CONCAT112(-(SUB161(auVar1 >> 0x60,0) ==
                                                             local_258[12]),
                                                            CONCAT111(-(SUB161(auVar1 >> 0x58,0) ==
                                                                       local_258[11]),
                                                                      CONCAT110(-(SUB161(auVar1 >> 
                                                  0x50,0) == local_258[10]),
                                                  CONCAT19(-(SUB161(auVar1 >> 0x48,0) ==
                                                            local_258[9]),
                                                           CONCAT18(-(SUB161(auVar1 >> 0x40,0) ==
                                                                     local_258[8]),uVar4))))))));
          iVar3 = pmovmskb(0,auVar10);
          if (iVar3 != 0xffff) {
            cVar2 = hdb_binsrch_idx_add_entry_str(SUB168(auVar10,0),uVar4,param_1,local_270,lVar8);
            if (cVar2 != '\0') goto LAB_00100186;
            local_274 = local_274 + 1;
            strncpy(local_268,local_270,0x21);
          }
        }
        lVar8 = lVar8 + sVar6;
        pcVar5 = fgets(local_238,0x200,(FILE *)param_1[0x58]);
        iVar9 = iVar9 + -1;
      } while (pcVar5 != (char *)0x0);
      if (0 < (int)local_274) {
        if (_tsk_verbose != 0) {
          fprintf(stderr,"  Valid Database Entries: %d\n",(ulong)local_278);
          fprintf(stderr,"  Invalid Database Entries (headers or errors): %d\n",(ulong)uVar7);
          pcVar5 = "(optimized)";
          if (local_274 == local_278) {
            pcVar5 = "";
          }
          fprintf(stderr,"  Index File Entries %s: %d\n",pcVar5,(ulong)local_274);
        }
        cVar2 = hdb_binsrch_idx_finalize(param_1);
        if (cVar2 == '\0') {
          return 0;
        }
        goto LAB_00100186;
      }
    }
    tsk_error_reset();
    tsk_error_set_errno(0x1000000b);
    uVar4 = tsk_error_set_errstr("hk_makeindex: No valid entries found in database");
  }
  else {
LAB_00100186:
    uVar4 = tsk_error_set_errstr2("hk_makeindex");
  }
  return CONCAT71((int7)((ulong)uVar4 >> 8),1);
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
hk_getentry(long param_1,char *param_2,char *param_3,ulong param_4,code *param_5,undefined8 param_6)

{
  bool bVar1;
  int iVar2;
  size_t sVar3;
  undefined8 uVar4;
  char *pcVar5;
  char *local_858;
  code *local_850;
  undefined8 local_848;
  undefined *local_840;
  char local_838 [512];
  char local_638 [512];
  undefined local_438 [512];
  char local_238 [520];
  
  local_858 = (char *)0x0;
  if (_tsk_verbose != 0) {
    fprintf(stderr,"hk_getentry: Lookup up hash %s at offset %ld\n",param_2,param_3);
  }
  sVar3 = strlen(param_2);
  if (sVar3 == 0x20) {
    memset(local_838,0x30,0x200);
    iVar2 = fseeko(*(FILE **)(param_1 + 0x2c0),(__off_t)param_3,0);
    if (iVar2 == 0) {
      local_840 = local_438;
      bVar1 = false;
      if ((param_4 & 2) == 0) {
        local_840 = (undefined *)0x0;
      }
      local_850 = param_5;
      local_848 = param_6;
      do {
        pcVar5 = fgets(local_638,0x200,*(FILE **)(param_1 + 0x2c0));
        if (pcVar5 == (char *)0x0) {
          iVar2 = feof(*(FILE **)(param_1 + 0x2c0));
          if (iVar2 == 0) {
            tsk_error_reset();
            tsk_error_set_errno(0x10000002);
            uVar4 = tsk_error_set_errstr("hk_getentry: Error reading database");
            goto LAB_0010045f;
          }
LAB_001005cc:
          if (bVar1) {
            return 0;
          }
          tsk_error_reset();
          tsk_error_set_errno(0x10000004);
          pcVar5 = "hk_getentry: Hash not found in file at offset: %lu";
          param_2 = param_3;
          goto LAB_0010045a;
        }
        sVar3 = strlen(local_638);
        if (sVar3 < 0x20) {
          tsk_error_reset();
          tsk_error_set_errno(0x1000000b);
          pcVar5 = "hk_getentry: Invalid entry in database (too short): %s";
LAB_00100617:
          param_2 = local_638;
          goto LAB_0010045a;
        }
        iVar2 = hk_parse_md5(local_638,&local_858,local_238,0x200,local_840,
                             (ulong)(((uint)param_4 & 2) << 8));
        if (iVar2 != 0) {
          tsk_error_reset();
          tsk_error_set_errno(0x1000000b);
          pcVar5 = "hk_getentry: Invalid entry in database: %s";
          goto LAB_00100617;
        }
        iVar2 = strcasecmp(local_858,param_2);
        if (iVar2 != 0) goto LAB_001005cc;
        iVar2 = strcmp(local_238,local_838);
        if (iVar2 != 0) {
          uVar4 = (*local_850)(param_1,param_2,local_238,local_848);
          if ((int)uVar4 == 1) {
            return 0;
          }
          if ((int)uVar4 == 2) goto LAB_0010045f;
          strncpy(local_838,local_238,0x200);
          bVar1 = true;
        }
        param_3 = param_3 + sVar3;
        iVar2 = fseeko(*(FILE **)(param_1 + 0x2c0),(__off_t)param_3,0);
      } while (iVar2 == 0);
    }
    tsk_error_reset();
    tsk_error_set_errno(0x10000002);
    pcVar5 = "hk_getentry: Error seeking to get file name: %lu";
    param_2 = param_3;
  }
  else {
    tsk_error_reset();
    tsk_error_set_errno(0x10000004);
    pcVar5 = "hk_getentry: Invalid hash value: %s";
  }
LAB_0010045a:
  uVar4 = tsk_error_set_errstr(pcVar5,param_2);
LAB_0010045f:
  return CONCAT71((int7)((ulong)uVar4 >> 8),1);
}


/* WARNING: Type propagation algorithm not settling */

ulong hk_parse_md5(char *param_1,char **param_2,char *param_3,int param_4,char *param_5,int param_6)

{
  char *pcVar1;
  char cVar2;
  size_t sVar3;
  char *__s;
  char *pcVar4;
  char *__src;
  char *pcVar5;
  int iVar6;
  bool bVar7;
  char *local_58;
  
  if ((param_1 != (char *)0x0) && (sVar3 = strlen(param_1), 0x1f < sVar3)) {
    bVar7 = ((ulong)param_2 | (ulong)param_3) == 0;
    if ((bVar7) && (param_5 == (char *)0x0)) {
      return 0;
    }
    pcVar4 = param_1;
    if (param_5 == (char *)0x0) {
      pcVar4 = param_5;
    }
    __s = strchr(param_1,0x2c);
    if (__s != (char *)0x0) {
      iVar6 = 3;
      pcVar5 = (char *)0x0;
      local_58 = (char *)0x0;
      __src = (char *)0x0;
      do {
        if ((param_5 == (char *)0x0) || (iVar6 != 3)) {
          if (iVar6 == 2) {
            if (param_5 != (char *)0x0) {
              *__s = '\0';
              snprintf(param_5,(long)param_6,"Hash ID: %s  File ID: %s",pcVar5,pcVar4);
            }
            if (bVar7) {
              return 0;
            }
            if (param_3 == (char *)0x0) {
LAB_001007d0:
              cVar2 = __s[1];
            }
            else {
              if (__s[1] != '\"') {
                return 1;
              }
              __src = __s + 2;
              cVar2 = __s[1];
            }
          }
          else {
            if ((param_3 == (char *)0x0) || (iVar6 != 1)) {
              if (iVar6 == 0) {
                if (param_3 != (char *)0x0) {
                  *param_3 = '\0';
                  if (local_58 != (char *)0x0) {
                    if (__s[-1] != '\"') {
                      return 1;
                    }
                    __s[-1] = '\0';
                    strncpy(param_3,local_58,(long)param_4);
                    strncat(param_3,"\\",(long)param_4);
                  }
                  if (__src == (char *)0x0) {
                    return 1;
                  }
                  strncat(param_3,__src,(long)param_4);
                }
                if (param_2 == (char **)0x0) {
                  return 0;
                }
                sVar3 = strlen(__s);
                if (sVar3 < 0x22) {
                  return 1;
                }
                if (__s[1] != '\"') {
                  return 1;
                }
                if (__s[0x22] == '\"') {
                  __s[0x22] = '\0';
                  *param_2 = __s + 2;
                  pcVar4 = strchr(__s + 2,0x2c);
                  return (ulong)(pcVar4 != (char *)0x0);
                }
                return 1;
              }
              goto LAB_001007d0;
            }
            if (__s[-1] != '\"') {
              return 1;
            }
            __s[-1] = '\0';
            local_58 = __s + 2;
            if (__s[1] != '\"') {
              local_58 = (char *)0x0;
            }
            cVar2 = __s[1];
          }
          if (cVar2 == '\"') goto LAB_001007da;
LAB_00100720:
          __s = __s + 1;
        }
        else {
          *__s = '\0';
          pcVar5 = __s + 1;
          pcVar1 = __s + 2;
          __s = pcVar5;
          if (*pcVar1 != '\"') goto LAB_00100720;
LAB_001007da:
          __s = strchr(__s + 2,0x22);
          if (__s == (char *)0x0) {
            return 1;
          }
        }
        __s = strchr(__s,0x2c);
        iVar6 = iVar6 + -1;
      } while (__s != (char *)0x0);
    }
  }
  return 1;
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

char * fgets(char *__s,int __n,FILE *__stream)

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

void hdb_binsrch_idx_add_entry_str(void)

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

char * strchr(char *__s,int __c)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int strcmp(char *__s1,char *__s2)

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
/* WARNING: Unknown calling convention yet parameter storage is locked */

char * strncat(char *__dest,char *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int strncmp(char *__s1,char *__s2,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

char * strncpy(char *__dest,char *__src,size_t __n)

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


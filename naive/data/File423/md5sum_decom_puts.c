
undefined8 md5sum_test(FILE *param_1)

{
  ushort *puVar1;
  char *pcVar2;
  size_t sVar3;
  ushort **ppuVar4;
  char local_218;
  char local_217;
  char local_216;
  char local_215;
  char local_214;
  char local_1f9;
  char local_1f8;
  
  fseeko(param_1,0,0);
  pcVar2 = fgets(&local_218,0x200,param_1);
  if (pcVar2 == (char *)0x0) {
    return 0;
  }
  sVar3 = strlen(&local_218);
  if (0x1f < sVar3) {
    if (((((long)local_218 == 0x4d) && (local_217 == 'D')) && (local_216 == '5')) &&
       ((local_215 == ' ' && (local_214 == '(')))) {
      return 1;
    }
    marker266._13216_8_ = 0x100830;
    marker266._14200_8_ = 0x100830;
    marker266._2528_8_ = "function_inlined: isspace";
    ppuVar4 = __ctype_b_loc();
    puVar1 = *ppuVar4;
    if ((((*(byte *)((long)puVar1 + (long)local_218 * 2 + 1) & 0x10) != 0) &&
        ((*(byte *)((long)puVar1 + (long)local_1f9 * 2 + 1) & 0x10) != 0)) &&
       ((*(byte *)((long)puVar1 + (long)local_1f8 * 2 + 1) & 0x20) != 0)) {
      return 1;
    }
  }
  return 0;
}


long md5sum_open(void)

{
  long lVar1;
  
  lVar1 = hdb_binsrch_open();
  if (lVar1 != 0) {
    *(undefined4 *)(lVar1 + 0x208) = 2;
    *(undefined8 *)(lVar1 + 0x2c8) = 0x100110;
    *(undefined8 *)(lVar1 + 0x268) = 0x1003a0;
    return lVar1;
  }
  return 0;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
md5sum_getentry(long param_1,char *param_2,char *param_3,undefined8 param_4,code *param_5,
               undefined8 param_6)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  size_t sVar4;
  undefined8 uVar5;
  char *pcVar6;
  char *local_458;
  char *local_450;
  code *local_448;
  undefined8 local_440;
  char local_438 [512];
  char local_238 [520];
  
  local_458 = (char *)0x0;
  if (_tsk_verbose != 0) {
    fprintf(stderr,"md5sum_getentry: Lookup up hash %s at offset %ld\n",param_2,param_3);
  }
  sVar4 = strlen(param_2);
  if (sVar4 == 0x20) {
    memset(local_438,0x30,0x200);
    iVar3 = fseeko(*(FILE **)(param_1 + 0x2c0),(__off_t)param_3,0);
    if (iVar3 == 0) {
      bVar1 = false;
      local_448 = param_5;
      local_440 = param_6;
      do {
        pcVar6 = fgets(local_238,0x200,*(FILE **)(param_1 + 0x2c0));
        if (pcVar6 == (char *)0x0) {
          iVar3 = feof(*(FILE **)(param_1 + 0x2c0));
          if (iVar3 == 0) {
            tsk_error_reset();
            tsk_error_set_errno(0x10000002);
            uVar5 = tsk_error_set_errstr("md5sum_getentry: Error reading database");
            goto LAB_001001bd;
          }
LAB_00100301:
          if (bVar1) {
            return 0;
          }
          tsk_error_reset();
          tsk_error_set_errno(0x10000004);
          pcVar6 = "md5sum_getentry: Hash not found in file at offset: %lu";
          param_2 = param_3;
          goto LAB_001001b8;
        }
        sVar4 = strlen(local_238);
        if (sVar4 < 0x20) {
          tsk_error_reset();
          tsk_error_set_errno(0x1000000b);
          pcVar6 = "md5sum_getentry: Invalid entry in database (too short): %s";
LAB_0010034a:
          param_2 = local_238;
          goto LAB_001001b8;
        }
        cVar2 = md5sum_parse_md5(local_238,&local_458,&local_450);
        if (cVar2 != '\0') {
          tsk_error_reset();
          tsk_error_set_errno(0x1000000b);
          pcVar6 = "md5sum_getentry: Invalid entry in database: %s";
          goto LAB_0010034a;
        }
        iVar3 = strcasecmp(local_458,param_2);
        pcVar6 = local_450;
        if (iVar3 != 0) goto LAB_00100301;
        iVar3 = strcmp(local_450,local_438);
        if (iVar3 != 0) {
          uVar5 = (*local_448)(param_1,param_2,pcVar6,local_440);
          if ((int)uVar5 == 1) {
            return 0;
          }
          if ((int)uVar5 == 2) goto LAB_001001bd;
          strncpy(local_438,local_450,0x200);
          bVar1 = true;
        }
        param_3 = param_3 + sVar4;
        iVar3 = fseeko(*(FILE **)(param_1 + 0x2c0),(__off_t)param_3,0);
      } while (iVar3 == 0);
    }
    tsk_error_reset();
    tsk_error_set_errno(0x10000002);
    pcVar6 = "md5sum_getentry: Error seeking to get file name: %lu";
    param_2 = param_3;
  }
  else {
    tsk_error_reset();
    tsk_error_set_errno(0x10000004);
    pcVar6 = "md5sum_getentry: Invalid hash value: %s";
  }
LAB_001001b8:
  uVar5 = tsk_error_set_errstr(pcVar6,param_2);
LAB_001001bd:
  return CONCAT71((int7)((ulong)uVar5 >> 8),1);
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 md5sum_makeindex(undefined8 *param_1)

{
  undefined auVar1 [16];
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined8 uVar5;
  char *pcVar6;
  size_t sVar7;
  uint uVar8;
  uint uVar9;
  long lVar10;
  undefined auVar11 [16];
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
    marker266._14408_8_ = "function_inlined: memset";
    local_258 = "0000000000000000function_inlined: isxdigit"._0_16_;
    local_268 = "0000000000000000function_inlined: isxdigit"._0_16_;
    local_248 = 0x30;
    uVar8 = 0;
    fseek((FILE *)param_1[0x58],0,0);
    pcVar6 = fgets(local_238,0x200,(FILE *)param_1[0x58]);
    if (pcVar6 != (char *)0x0) {
      local_274 = 0;
      uVar9 = 0;
      lVar10 = 0;
      do {
        sVar7 = strlen(local_238);
        uVar3 = md5sum_parse_md5(local_238,&local_270,0);
        if ((char)uVar3 == '\0') {
          marker266._8328_8_ = "function_inlined: memcmp";
                    /* WARNING: Load size is inaccurate */
          auVar11 = *(undefined *)local_270;
                    /* WARNING: Load size is inaccurate */
          auVar1 = *(undefined *)(local_270 + 0x10);
          uVar5 = CONCAT17(-(SUB161(auVar1 >> 0x38,0) == local_258[7]),
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
          uVar9 = uVar9 + 1;
          auVar11 = CONCAT115(-(SUB161(auVar11 >> 0x78,0) == local_268[15]),
                              CONCAT114(-(SUB161(auVar11 >> 0x70,0) == local_268[14]),
                                        CONCAT113(-(SUB161(auVar11 >> 0x68,0) == local_268[13]),
                                                  CONCAT112(-(SUB161(auVar11 >> 0x60,0) ==
                                                             local_268[12]),
                                                            CONCAT111(-(SUB161(auVar11 >> 0x58,0) ==
                                                                       local_268[11]),
                                                                      CONCAT110(-(SUB161(auVar11 >>
                                                                                         0x50,0) ==
                                                                                 local_268[10]),
                                                                                CONCAT19(-(SUB161(
                                                  auVar11 >> 0x48,0) == local_268[9]),
                                                  CONCAT18(-(SUB161(auVar11 >> 0x40,0) ==
                                                            local_268[8]),
                                                           CONCAT17(-(SUB161(auVar11 >> 0x38,0) ==
                                                                     local_268[7]),
                                                                    CONCAT16(-(SUB161(auVar11 >>
                                                                                      0x30,0) ==
                                                                              local_268[6]),
                                                                             CONCAT15(-(SUB161(
                                                  auVar11 >> 0x28,0) == local_268[5]),
                                                  CONCAT14(-(SUB161(auVar11 >> 0x20,0) ==
                                                            local_268[4]),
                                                           CONCAT13(-(SUB161(auVar11 >> 0x18,0) ==
                                                                     local_268[3]),
                                                                    CONCAT12(-(SUB161(auVar11 >>
                                                                                      0x10,0) ==
                                                                              local_268[2]),
                                                                             CONCAT11(-(SUB161(
                                                  auVar11 >> 8,0) == local_268[1]),
                                                  -(SUB161(auVar11,0) == local_268[0])))))))))))))))
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
                                                                     local_258[8]),uVar5))))))));
          iVar4 = pmovmskb(uVar3,auVar11);
          if (iVar4 != 0xffff) {
            cVar2 = hdb_binsrch_idx_add_entry_str(SUB168(auVar11,0),uVar5,param_1,local_270,lVar10);
            if (cVar2 != '\0') goto LAB_001003c6;
            local_274 = local_274 + 1;
            strncpy(local_268,local_270,0x21);
          }
        }
        else {
          uVar8 = uVar8 + 1;
        }
        lVar10 = lVar10 + sVar7;
        pcVar6 = fgets(local_238,0x200,(FILE *)param_1[0x58]);
      } while (pcVar6 != (char *)0x0);
      if (0 < (int)local_274) {
        if (_tsk_verbose != 0) {
          fprintf(stderr,"  Valid Database Entries: %d\n",(ulong)uVar9);
          fprintf(stderr,"  Invalid Database Entries (headers or errors): %d\n",(ulong)uVar8);
          pcVar6 = "(optimized)";
          if (local_274 == uVar9) {
            pcVar6 = "";
          }
          fprintf(stderr,"  Index File Entries %s: %d\n",pcVar6,(ulong)local_274);
        }
        cVar2 = hdb_binsrch_idx_finalize(param_1);
        if (cVar2 == '\0') {
          return 0;
        }
        goto LAB_001003c6;
      }
    }
    tsk_error_reset();
    tsk_error_set_errno(0x1000000b);
    uVar5 = tsk_error_set_errstr("md5sum_makeindex: No valid entries found in database");
  }
  else {
LAB_001003c6:
    uVar5 = tsk_error_set_errstr2("md5sum_makeindex");
  }
  return CONCAT71((int7)((ulong)uVar5 >> 8),1);
}


undefined8 md5sum_parse_md5(char *param_1,char **param_2,char **param_3)

{
  ushort *puVar1;
  size_t sVar2;
  ushort **ppuVar3;
  undefined8 uVar4;
  uint uVar5;
  size_t sVar6;
  char *pcVar7;
  
  sVar2 = strlen(param_1);
  if (sVar2 < 0x21) {
    tsk_error_reset();
    tsk_error_set_errno(0x1000000b);
    pcVar7 = "md5sum_parse_md5: String is too short: %s";
  }
  else {
    marker266._1016_8_ = 0x100830;
    marker266._7664_8_ = 0x100830;
    marker266._5536_8_ = "function_inlined: isspace";
    ppuVar3 = __ctype_b_loc();
    puVar1 = *ppuVar3;
    if ((((*(byte *)((long)puVar1 + (long)*param_1 * 2 + 1) & 0x10) != 0) &&
        ((*(byte *)((long)puVar1 + (long)param_1[0x1f] * 2 + 1) & 0x10) != 0)) &&
       ((*(byte *)((long)puVar1 + (long)param_1[0x20] * 2 + 1) & 0x20) != 0)) {
      sVar2 = strlen(param_1);
      if (param_2 != (char **)0x0) {
        *param_2 = param_1;
      }
      param_1[0x20] = '\0';
      if (sVar2 < 0x22) {
        if (param_3 != (char **)0x0) {
          *param_3 = "";
          return 0;
        }
      }
      else {
        sVar6 = 0x21;
        do {
          if ((param_1[sVar6] != ' ') && (param_1[sVar6] != '\t')) goto joined_r0x00100755;
          uVar5 = (int)sVar6 + 1;
          sVar6 = (size_t)uVar5;
        } while (sVar6 < sVar2);
        sVar6 = (size_t)uVar5;
joined_r0x00100755:
        if ((sVar2 != sVar6) && (param_1[sVar6] != '\n')) {
          if (param_1[sVar6] == '*') {
            sVar6 = (size_t)((int)sVar6 + 1);
          }
          param_1 = param_1 + sVar6;
          if (param_3 != (char **)0x0) {
            *param_3 = param_1;
          }
          sVar2 = strlen(param_1);
          if (param_1[sVar2 - 1] == '\n') {
            param_1[sVar2 - 1] = '\0';
          }
        }
      }
      return 0;
    }
    if ((((*param_1 == 'M') && (param_1[1] == 'D')) && (param_1[2] == '5')) &&
       ((param_1[3] == ' ' && (param_1[4] == '(')))) {
      if (param_3 != (char **)0x0) {
        *param_3 = param_1 + 5;
      }
      pcVar7 = strchr(param_1 + 5,0x29);
      if (pcVar7 == (char *)0x0) {
        tsk_error_reset();
        tsk_error_set_errno(0x1000000b);
        pcVar7 = "md5sum_parse_md5: Missing ) in name: %s";
      }
      else {
        *pcVar7 = '\0';
        param_1 = pcVar7 + 1;
        sVar2 = strlen(param_1);
        if (sVar2 < 0x24) {
          tsk_error_reset();
          tsk_error_set_errno(0x1000000b);
          pcVar7 = "md5sum_parse_md5: Invalid MD5 value: %s";
        }
        else {
          marker266._12296_8_ = 0x100830;
          if (*param_1 == ' ') {
            if (pcVar7[2] == '=') {
              if (pcVar7[3] == ' ') {
                param_1 = pcVar7 + 4;
                if (((*(byte *)((long)*ppuVar3 + (long)pcVar7[4] * 2 + 1) & 0x10) != 0) &&
                   (pcVar7[0x24] == '\n')) {
                  *param_2 = param_1;
                  pcVar7[0x24] = '\0';
                  return 0;
                }
              }
              else {
                param_1 = pcVar7 + 3;
              }
            }
            else {
              param_1 = pcVar7 + 2;
            }
          }
          tsk_error_reset();
          tsk_error_set_errno(0x1000000b);
          pcVar7 = "md5sum_parse_md5: Invalid hash value %s";
        }
      }
    }
    else {
      tsk_error_reset();
      tsk_error_set_errno(0x1000000b);
      pcVar7 = "md5sum_parse_md5: Invalid md5sum format in file: %s\n";
    }
  }
  uVar4 = tsk_error_set_errstr(pcVar7,param_1);
  return CONCAT71((int7)((ulong)uVar4 >> 8),1);
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

ushort ** __ctype_b_loc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
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


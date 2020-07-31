
undefined8 nsrl_test(FILE *param_1)

{
  char *pcVar1;
  size_t sVar2;
  char local_218;
  char local_217;
  char local_216;
  char local_215;
  char local_214;
  char local_213;
  char local_212;
  char local_20f;
  char local_209;
  char local_204;
  char local_201;
  char local_200;
  char local_1f9;
  char local_1f6;
  char local_1eb;
  
  fseeko(param_1,0,0);
  pcVar1 = fgets(&local_218,0x200,param_1);
  if ((((((pcVar1 != (char *)0x0) && (sVar2 = strlen(&local_218), 0x2c < sVar2)) &&
        (local_218 == '\"')) && ((local_217 == 'S' && (local_216 == 'H')))) &&
      ((local_215 == 'A' && ((local_214 == '-' && (local_213 == '1')))))) && (local_212 == '\"')) {
    if (local_20f == 'M') {
      if ((((local_209 == 'C') && (local_201 == 'F')) && (local_1f6 == 'F')) && (local_1eb == 'P'))
      {
        return 1;
      }
    }
    else {
      if (((local_20f == 'F') && (local_204 == 'F')) &&
         ((local_200 == 'S' && ((local_1f9 == 'P' && (local_1eb == 'O')))))) {
        return 1;
      }
    }
    tsk_error_reset();
    tsk_error_set_errno(0x1000000b);
    tsk_error_set_errstr("nsrl: Unknown header format: %s\n",&local_218);
  }
  return 0;
}


long nsrl_open(void)

{
  long lVar1;
  
  lVar1 = hdb_binsrch_open();
  if (lVar1 != 0) {
    *(undefined4 *)(lVar1 + 0x208) = 1;
    *(undefined8 *)(lVar1 + 0x268) = 0x100140;
    *(undefined8 *)(lVar1 + 0x2c8) = 0x100480;
    return lVar1;
  }
  return 0;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 nsrl_makeindex(undefined8 *param_1)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  char *pcVar4;
  size_t sVar5;
  long lVar6;
  long lVar7;
  uint uVar8;
  uint local_27c;
  uint local_278;
  uint local_274;
  char *local_270;
  undefined4 local_268;
  undefined4 uStack612;
  undefined4 uStack608;
  undefined4 uStack604;
  undefined4 local_258;
  undefined4 uStack596;
  undefined4 uStack592;
  undefined4 uStack588;
  undefined uStack584;
  undefined4 uStack583;
  undefined4 uStack579;
  char local_238 [9];
  char local_22f;
  char local_229;
  char local_224;
  char local_221;
  char local_220;
  char local_219;
  char local_216;
  char local_20b;
  
  local_270 = (char *)0x0;
  cVar1 = hdb_binsrch_idx_initialize();
  if (cVar1 == '\0') {
    if (_tsk_verbose != 0) {
      fprintf(stderr,"Extracting Data from Database (%s)\n",*param_1);
    }
    marker270._13920_8_ = "function_inlined: memset";
    uStack584 = (undefined)((uint)"0000000000000000nsrl_makeindex"._4_4_ >> 0x18);
    uStack583 = "0000000000000000nsrl_makeindex"._8_4_;
    uStack579 = "0000000000000000nsrl_makeindex"._12_4_;
    local_258 = "0000000000000000nsrl_makeindex"._0_4_;
    uStack596 = "0000000000000000nsrl_makeindex"._4_4_;
    uStack592 = "0000000000000000nsrl_makeindex"._8_4_;
    uStack588 = "0000000000000000nsrl_makeindex"._12_4_;
    local_268 = "0000000000000000nsrl_makeindex"._0_4_;
    uStack612 = "0000000000000000nsrl_makeindex"._4_4_;
    uStack608 = "0000000000000000nsrl_makeindex"._8_4_;
    uStack604 = "0000000000000000nsrl_makeindex"._12_4_;
    uVar8 = 0;
    fseek((FILE *)param_1[0x58],0,0);
    pcVar4 = fgets(local_238,0x200,(FILE *)param_1[0x58]);
    if (pcVar4 != (char *)0x0) {
      lVar6 = 0;
      local_278 = 0;
      local_274 = 0;
      local_27c = 0;
      lVar7 = 0;
      do {
        sVar5 = strlen(local_238);
        if (lVar6 == 0) {
          if (local_22f == 'M') {
            if ((((local_229 != 'C') || (local_221 != 'F')) || (local_216 != 'F')) ||
               (local_27c = 2, local_20b != 'P')) goto LAB_001003c4;
          }
          else {
            if (((local_22f != 'F') || (local_224 != 'F')) ||
               ((local_220 != 'S' || ((local_219 != 'P' || (local_27c = 1, local_20b != 'O')))))) {
LAB_001003c4:
              tsk_error_reset();
              tsk_error_set_errno(0x1000000b);
              uVar3 = tsk_error_set_errstr("nsrl: Unknown header format: %s\n",local_238);
              goto LAB_001003e6;
            }
          }
LAB_00100353:
          uVar8 = uVar8 + 1;
        }
        else {
          if ((*(uint *)(param_1 + 0x5a) & 2) == 0) {
            if ((*(uint *)(param_1 + 0x5a) & 1) != 0) {
              cVar1 = nsrl_parse_md5(local_238,&local_270,0);
              goto joined_r0x001002b5;
            }
          }
          else {
            cVar1 = nsrl_parse_sha1(local_238,&local_270,0,(ulong)local_27c);
joined_r0x001002b5:
            if (cVar1 != '\0') goto LAB_00100353;
          }
          pcVar4 = local_270;
          local_274 = local_274 + 1;
          iVar2 = memcmp(local_270,&local_268,(ulong)*(ushort *)((long)param_1 + 0x2d4));
          if (iVar2 != 0) {
            cVar1 = hdb_binsrch_idx_add_entry_str(param_1,pcVar4,lVar7);
            if (cVar1 != '\0') goto LAB_00100166;
            local_278 = local_278 + 1;
            strncpy((char *)&local_268,local_270,(ulong)*(ushort *)((long)param_1 + 0x2d4) + 1);
          }
        }
        lVar7 = lVar7 + sVar5;
        pcVar4 = fgets(local_238,0x200,(FILE *)param_1[0x58]);
        lVar6 = lVar6 + -1;
      } while (pcVar4 != (char *)0x0);
      if (0 < (int)local_278) {
        if (_tsk_verbose != 0) {
          fprintf(stderr,"  Valid Database Entries: %d\n",(ulong)local_274);
          fprintf(stderr,"  Invalid Database Entries (headers or errors): %d\n",(ulong)uVar8);
          pcVar4 = "(optimized)";
          if (local_278 == local_274) {
            pcVar4 = "";
          }
          fprintf(stderr,"  Index File Entries %s: %d\n",pcVar4,(ulong)local_278);
        }
        cVar1 = hdb_binsrch_idx_finalize(param_1);
        if (cVar1 == '\0') {
          return 0;
        }
        goto LAB_00100166;
      }
    }
    tsk_error_reset();
    tsk_error_set_errno(0x1000000b);
    uVar3 = tsk_error_set_errstr("nsrl_makeindex: No valid entries found in database");
  }
  else {
LAB_00100166:
    uVar3 = tsk_error_set_errstr2(0x100bf0);
  }
LAB_001003e6:
  return CONCAT71((int7)((ulong)uVar3 >> 8),1);
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 nsrl_getentry(long param_1,char *param_2,char *param_3,undefined8 param_4,code *param_5)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  size_t sVar4;
  undefined8 uVar5;
  uint uVar6;
  char *pcVar7;
  char *local_450;
  char *local_448;
  char *local_440;
  char local_438 [9];
  char local_42f;
  char local_429;
  char local_424;
  char local_421;
  char local_420;
  char local_419;
  char local_416;
  char local_40b;
  char local_238 [520];
  
  if (_tsk_verbose != 0) {
    fprintf(stderr,"nsrl_getentry: Lookup up hash %s at offset %ld\n",param_2,param_3);
  }
  if (*(int *)(param_1 + 0x2d0) == 2) {
    sVar4 = strlen(param_2);
    if (sVar4 == 0x28) goto LAB_001004f8;
    tsk_error_reset();
    tsk_error_set_errno(0x10000004);
    pcVar7 = "nsrl_getentry: Invalid hash value (expected to be SHA1): %s\n";
  }
  else {
    if ((*(int *)(param_1 + 0x2d0) != 1) || (sVar4 = strlen(param_2), sVar4 == 0x20)) {
LAB_001004f8:
      fseeko(*(FILE **)(param_1 + 0x2c0),0,0);
      pcVar7 = fgets(local_438,0x200,*(FILE **)(param_1 + 0x2c0));
      if (pcVar7 == (char *)0x0) {
        tsk_error_reset();
        tsk_error_set_errno(0x10000002);
        pcVar7 = "nsrl_getentry: Error reading NSRLFile.txt header\n";
LAB_0010057f:
        uVar5 = tsk_error_set_errstr(pcVar7);
        goto LAB_0010064f;
      }
      if (local_42f == 'M') {
        if ((((local_429 == 'C') && (local_421 == 'F')) && (local_416 == 'F')) &&
           (uVar6 = 2, local_40b == 'P')) goto LAB_001005d1;
      }
      else {
        if (((local_42f == 'F') && (local_424 == 'F')) &&
           ((local_420 == 'S' && ((local_419 == 'P' && (uVar6 = 1, local_40b == 'O')))))) {
LAB_001005d1:
          memset(local_238,0x30,0x200);
          iVar3 = fseeko(*(FILE **)(param_1 + 0x2c0),(__off_t)param_3,0);
          if (iVar3 == 0) {
            bVar1 = false;
            do {
              pcVar7 = fgets(local_438,0x200,*(FILE **)(param_1 + 0x2c0));
              if (pcVar7 == (char *)0x0) {
                iVar3 = feof(*(FILE **)(param_1 + 0x2c0));
                if (iVar3 == 0) {
                  tsk_error_reset();
                  tsk_error_set_errno(0x10000002);
                  pcVar7 = "nsrl_getentry: Error reading database";
                  goto LAB_0010057f;
                }
LAB_001007b5:
                if (bVar1) {
                  return 0;
                }
                tsk_error_reset();
                tsk_error_set_errno(0x10000004);
                pcVar7 = "nsrl_getentry: Hash not found in file at offset: %lu";
                param_2 = param_3;
                goto LAB_001005a6;
              }
              sVar4 = strlen(local_438);
              if (sVar4 < 0x2d) {
                tsk_error_reset();
                tsk_error_set_errno(0x1000000b);
                pcVar7 = "nsrl_getentry: Invalid entry in database (too short): %s";
LAB_0010081a:
                param_2 = local_438;
                goto LAB_001005a6;
              }
              if (*(int *)(param_1 + 0x2d0) == 1) {
                cVar2 = nsrl_parse_md5(local_438,&local_448,&local_450,(ulong)uVar6);
joined_r0x0010070e:
                if (cVar2 != '\0') {
                  tsk_error_reset();
                  tsk_error_set_errno(0x1000000b);
                  pcVar7 = "nsrl_getentry: Invalid entry in database: %s";
                  goto LAB_0010081a;
                }
              }
              else {
                if (*(int *)(param_1 + 0x2d0) == 2) {
                  cVar2 = nsrl_parse_sha1(local_438,&local_448,&local_450);
                  goto joined_r0x0010070e;
                }
              }
              iVar3 = strcasecmp(local_448,param_2);
              if (iVar3 != 0) goto LAB_001007b5;
              local_440 = local_450;
              iVar3 = strcmp(local_450,local_238);
              if (iVar3 != 0) {
                uVar5 = (*param_5)(param_1,param_2,local_440);
                if ((int)uVar5 == 1) {
                  return 0;
                }
                if ((int)uVar5 == 2) goto LAB_0010064f;
                strncpy(local_238,local_450,0x200);
                bVar1 = true;
              }
              param_3 = param_3 + sVar4;
              iVar3 = fseeko(*(FILE **)(param_1 + 0x2c0),(__off_t)param_3,0);
            } while (iVar3 == 0);
          }
          tsk_error_reset();
          tsk_error_set_errno(0x10000002);
          pcVar7 = "nsrl_getentry: Error seeking to get file name: %lu";
          param_2 = param_3;
          goto LAB_001005a6;
        }
      }
      tsk_error_reset();
      tsk_error_set_errno(0x1000000b);
      tsk_error_set_errstr("nsrl: Unknown header format: %s\n",local_438);
      uVar5 = tsk_error_set_errstr2("nsrl_getentry");
      goto LAB_0010064f;
    }
    tsk_error_reset();
    tsk_error_set_errno(0x10000004);
    pcVar7 = "nsrl_getentry: Invalid hash value (expected to be MD5): %s\n";
  }
LAB_001005a6:
  uVar5 = tsk_error_set_errstr(pcVar7,param_2);
LAB_0010064f:
  return CONCAT71((int7)((ulong)uVar5 >> 8),1);
}


undefined8 nsrl_parse_sha1(char *param_1,char **param_2,char **param_3,int param_4)

{
  char *__s;
  size_t sVar1;
  char *pcVar2;
  undefined8 uVar3;
  
  sVar1 = strlen(param_1);
  if ((((sVar1 < 0x2d) || (*param_1 != '\"')) || (param_1[0x29] != '\"')) ||
     ((param_1[0x2a] != ',' || (param_1[0x2b] != '\"')))) {
    tsk_error_reset();
    tsk_error_set_errno(0x1000000b);
    pcVar2 = "nsrl_parse_sha1: Invalid string to parse: %s";
LAB_001008cd:
    uVar3 = tsk_error_set_errstr(pcVar2,param_1);
    uVar3 = CONCAT71((int7)((ulong)uVar3 >> 8),1);
  }
  else {
    if (param_2 != (char **)0x0) {
      __s = param_1 + 1;
      param_1[0x29] = '\0';
      pcVar2 = strchr(__s,0x2c);
      if (pcVar2 != (char *)0x0) {
        tsk_error_reset();
        tsk_error_set_errno(0x1000000b);
        pcVar2 = "nsrl_parse_sha1: Invalid string to parse (commas after SHA1): %s";
        param_1 = __s;
        goto LAB_001008cd;
      }
      *param_2 = __s;
    }
    if (param_3 != (char **)0x0) {
      if (param_4 == 2) {
        param_1 = param_1 + 0x5a;
      }
      else {
        if (param_4 != 1) goto LAB_00100915;
        param_1 = param_1 + 0x2c;
      }
      *param_3 = param_1;
      pcVar2 = strchr(param_1,0x2c);
      if (pcVar2 == (char *)0x0) {
        tsk_error_reset();
        tsk_error_set_errno(0x1000000b);
        pcVar2 = "nsrl_parse_sha1: Invalid string to parse (commas after name): %s";
        param_1 = (char *)0x0;
        goto LAB_001008cd;
      }
      pcVar2[-1] = '\0';
    }
LAB_00100915:
    uVar3 = 0;
  }
  return uVar3;
}


undefined8 nsrl_parse_md5(long **param_1,long **param_2,long **param_3,uint param_4)

{
  size_t sVar1;
  char *__s;
  undefined8 uVar2;
  int iVar3;
  long **__s_00;
  
  sVar1 = strlen((char *)param_1);
  if ((((sVar1 < 0x2d) || (*(char *)param_1 != '\"')) || (*(char *)((long)param_1 + 0x29) != '\"'))
     || ((*(char *)((long)param_1 + 0x2a) != ',' || (*(char *)((long)param_1 + 0x2b) != '\"')))) {
    tsk_error_reset();
    tsk_error_set_errno(0x1000000b);
    __s = "nsrl_parse_md5: Invalid string to parse: %s";
    param_3 = param_1;
LAB_0010099c:
    uVar2 = tsk_error_set_errstr(__s,param_3);
LAB_001009a1:
    uVar2 = CONCAT71((int7)((ulong)uVar2 >> 8),1);
  }
  else {
    if (((ulong)param_2 | (ulong)param_3) != 0) {
      if (param_4 != 2) {
        if ((param_4 == 1) &&
           (__s_00 = (long **)strchr((char *)param_1,0x2c), __s_00 != (long **)0x0)) {
          iVar3 = 0;
          do {
            if ((param_3 == (long **)0x0) || (iVar3 != 0)) {
              if ((param_3 == (long **)0x0) || (iVar3 != 1)) {
                if ((param_2 != (long **)0x0) && (iVar3 == 5)) {
                  sVar1 = strlen((char *)__s_00);
                  if ((sVar1 < 0x22) ||
                     ((*(char *)((long)__s_00 + 1) != '\"' ||
                      (*(char *)((long)__s_00 + 0x22) != '\"')))) {
                    tsk_error_reset();
                    tsk_error_set_errno(0x1000000b);
                    __s = "nsrl_parse_md5: Invalid MD5 value: %s";
                    param_3 = __s_00;
                  }
                  else {
                    *(undefined *)((long)__s_00 + 0x22) = 0;
                    *param_2 = (long *)((long)__s_00 + 2);
                    __s = strchr((char *)(long *)((long)__s_00 + 2),0x2c);
                    if (__s == (char *)0x0) goto LAB_0010097d;
                    tsk_error_reset();
                    tsk_error_set_errno(0x1000000b);
                    __s = "nsrl_parse_md5: Missing comma after MD5: %s";
                    param_3 = param_2;
                  }
                  goto LAB_0010099c;
                }
              }
              else {
                if (*(char *)((long)__s_00 + -1) != '\"') {
                  tsk_error_reset();
                  tsk_error_set_errno(0x1000000b);
                  __s = "nsrl_parse_md5: Missing Quote after name: %s";
                  goto LAB_0010099c;
                }
                *(undefined *)((long)__s_00 + -1) = 0;
                if (param_2 == (long **)0x0) goto LAB_0010097d;
              }
              if (*(char *)((long)__s_00 + 1) != '\"') goto LAB_001009f1;
LAB_00100a30:
              __s = strchr((char *)((long)__s_00 + 2),0x22);
              if (__s == (char *)0x0) {
                tsk_error_reset();
                tsk_error_set_errno(0x1000000b);
                uVar2 = tsk_error_set_errstr("nsrl_parse_md5: Error advancing past quote");
                goto LAB_001009a1;
              }
            }
            else {
              *param_3 = (long *)((long)__s_00 + 2);
              if (*(char *)((long)__s_00 + 1) == '\"') goto LAB_00100a30;
LAB_001009f1:
              __s = (char *)((long)__s_00 + 1);
            }
            iVar3 = iVar3 + 1;
            __s_00 = (long **)strchr(__s,0x2c);
          } while (__s_00 != (long **)0x0);
        }
        tsk_error_reset();
        tsk_error_set_errno(0x10000004);
        uVar2 = tsk_error_set_errstr("nsrl_parse_md5: Invalid version: %d\n",(ulong)param_4);
        goto LAB_001009a1;
      }
      if (param_2 != (long **)0x0) {
        __s_00 = (long **)((long)param_1 + 0x2c);
        *(undefined *)((long)param_1 + 0x4c) = 0;
        __s = strchr((char *)__s_00,0x2c);
        if (__s != (char *)0x0) {
          tsk_error_reset();
          tsk_error_set_errno(0x1000000b);
          __s = "nsrl_parse_md5: Comma in MD5 value: %s";
          param_3 = __s_00;
          goto LAB_0010099c;
        }
        *(long ***)param_2 = __s_00;
      }
      if (param_3 != (long **)0x0) {
        *param_3 = (long *)((long)param_1 + 0x5a);
        __s = strchr((char *)(long *)((long)param_1 + 0x5a),0x2c);
        if (__s == (char *)0x0) {
          tsk_error_reset();
          tsk_error_set_errno(0x1000000b);
          __s = "nsrl_parse_md5: Missing comma after name: %s";
          goto LAB_0010099c;
        }
        __s[-1] = '\0';
      }
    }
LAB_0010097d:
    uVar2 = 0;
  }
  return uVar2;
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

int memcmp(void *__s1,void *__s2,size_t __n)

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


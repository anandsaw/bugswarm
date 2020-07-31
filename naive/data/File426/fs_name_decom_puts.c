
undefined4 * tsk_fs_name_alloc(long param_1,long param_2)

{
  undefined4 *__ptr;
  long lVar1;
  
  __ptr = (undefined4 *)tsk_malloc(0x58);
  if (__ptr != (undefined4 *)0x0) {
    lVar1 = tsk_malloc(param_1 + 1);
    *(long *)(__ptr + 2) = lVar1;
    if (lVar1 != 0) {
      *(long *)(__ptr + 4) = param_1;
      __ptr[0x15] = 0;
      *(long *)(__ptr + 8) = param_2;
      if (param_2 == 0) {
        *(undefined8 *)(__ptr + 6) = 0;
LAB_00100075:
        __ptr[0x14] = 0;
        *__ptr = 0x23147869;
        return __ptr;
      }
      lVar1 = tsk_malloc(param_2 + 1);
      *(long *)(__ptr + 6) = lVar1;
      if (lVar1 != 0) goto LAB_00100075;
      free(*(void **)(__ptr + 2));
    }
    free(__ptr);
  }
  return (undefined4 *)0;
}


ulong tsk_fs_name_realloc(int *param_1,ulong param_2)

{
  long lVar1;
  undefined8 unaff_RBP;
  ulong uVar2;
  
  uVar2 = CONCAT71((int7)((ulong)unaff_RBP >> 8),1);
  if ((param_1 != (int *)0x0) && (*param_1 == 0x23147869)) {
    if (*(ulong *)(param_1 + 4) < param_2) {
      lVar1 = tsk_realloc(*(undefined8 *)(param_1 + 2),param_2 + 1);
      *(long *)(param_1 + 2) = lVar1;
      if (lVar1 == 0) {
        *(undefined8 *)(param_1 + 4) = 0;
        goto LAB_001000d3;
      }
      param_1[0x14] = 0;
      *(ulong *)(param_1 + 4) = param_2;
    }
    uVar2 = 0;
  }
LAB_001000d3:
  return uVar2 & 0xffffffff;
}


void tsk_fs_name_reset(long param_1)

{
  if (*(undefined **)(param_1 + 8) != (undefined *)0x0) {
    **(undefined **)(param_1 + 8) = 0;
  }
  if (*(undefined **)(param_1 + 0x18) != (undefined *)0x0) {
    **(undefined **)(param_1 + 0x18) = 0;
  }
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x50) = 0;
  return;
}


void tsk_fs_name_free(int *param_1)

{
  if ((param_1 != (int *)0x0) && (*param_1 == 0x23147869)) {
    free(*(void **)(param_1 + 2));
    *(undefined8 *)(param_1 + 2) = 0;
    free(*(void **)(param_1 + 6));
    free(param_1);
    return;
  }
  return;
}


ulong tsk_fs_name_copy(long param_1,long param_2)

{
  size_t sVar1;
  ulong __n;
  char *__s;
  char *__dest;
  undefined8 unaff_R15;
  ulong uVar2;
  
  uVar2 = CONCAT71((int7)((ulong)unaff_R15 >> 8),1);
  if ((param_1 != 0) && (param_2 != 0)) {
    __s = *(char **)(param_2 + 8);
    if (__s == (char *)0x0) {
      if (*(long *)(param_1 + 0x10) == 0) {
        *(undefined8 *)(param_1 + 8) = 0;
      }
      else {
        **(undefined **)(param_1 + 8) = 0;
      }
    }
    else {
      sVar1 = strlen(__s);
      __n = *(ulong *)(param_1 + 0x10);
      if (sVar1 < __n) {
        __dest = *(char **)(param_1 + 8);
      }
      else {
        *(long *)(param_1 + 0x10) = sVar1 + 0x10;
        __dest = (char *)tsk_realloc(*(undefined8 *)(param_1 + 8),sVar1 + 0x10);
        *(char **)(param_1 + 8) = __dest;
        if (__dest == (char *)0x0) goto LAB_001002a1;
        __s = *(char **)(param_2 + 8);
        __n = *(size_t *)(param_1 + 0x10);
      }
      strncpy(__dest,__s,__n);
    }
    __s = *(char **)(param_2 + 0x18);
    if (__s == (char *)0x0) {
      if (*(long *)(param_1 + 0x20) == 0) {
        *(undefined8 *)(param_1 + 0x18) = 0;
      }
      else {
        **(undefined **)(param_1 + 0x18) = 0;
      }
    }
    else {
      sVar1 = strlen(__s);
      __n = *(ulong *)(param_1 + 0x20);
      if (sVar1 < __n) {
        __dest = *(char **)(param_1 + 0x18);
      }
      else {
        *(long *)(param_1 + 0x20) = sVar1 + 0x10;
        __dest = (char *)tsk_realloc(*(undefined8 *)(param_1 + 0x18),sVar1 + 0x10);
        *(char **)(param_1 + 0x18) = __dest;
        if (__dest == (char *)0x0) goto LAB_001002a1;
        __s = *(char **)(param_2 + 0x18);
        __n = *(size_t *)(param_1 + 0x20);
      }
      strncpy(__dest,__s,__n);
    }
    *(undefined8 *)(param_1 + 0x28) = *(undefined8 *)(param_2 + 0x28);
    *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_2 + 0x30);
    *(undefined8 *)(param_1 + 0x38) = *(undefined8 *)(param_2 + 0x38);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x40);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_2 + 0x50);
    *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_2 + 0x54);
    *(undefined8 *)(param_1 + 0x48) = *(undefined8 *)(param_2 + 0x48);
    uVar2 = 0;
  }
LAB_001002a1:
  return uVar2 & 0xffffffff;
}


/* WARNING: Type propagation algorithm not settling */

undefined8 tsk_fs_meta_make_ls(long param_1,undefined8 *param_2,ulong param_3)

{
  uint uVar1;
  char cVar2;
  undefined8 in_RAX;
  
  if (param_3 < 0xc) {
    return CONCAT71((int7)((ulong)in_RAX >> 8),1);
  }
  marker281._3640_8_ = "function_inlined: strcpy";
  *param_2 = 0x2d2d2d2d2d2d2d2d;
  *(undefined *)((long)param_2 + 10) = 0;
  *(undefined2 *)(param_2 + 1) = 0x2d2d;
  if (*(uint *)(param_1 + 0x10) < 0xc) {
    *(undefined *)param_2 = (&tsk_fs_meta_type_str)[(ulong)*(uint *)(param_1 + 0x10) * 2];
  }
  uVar1 = *(uint *)(param_1 + 0x14);
  if ((uVar1 & 0x100) == 0) {
    cVar2 = (char)uVar1;
  }
  else {
    *(undefined *)((long)param_2 + 1) = 0x72;
    uVar1 = *(uint *)(param_1 + 0x14);
    cVar2 = (char)uVar1;
  }
  if (cVar2 < '\0') {
    *(undefined *)((long)param_2 + 2) = 0x77;
    uVar1 = *(uint *)(param_1 + 0x14);
  }
  if ((uVar1 & 0x800) == 0) {
    if ((uVar1 & 0x40) != 0) {
      *(undefined *)((long)param_2 + 3) = 0x78;
    }
  }
  else {
    if ((uVar1 & 0x40) == 0) {
      *(undefined *)((long)param_2 + 3) = 0x53;
    }
    else {
      *(undefined *)((long)param_2 + 3) = 0x73;
    }
  }
  uVar1 = *(uint *)(param_1 + 0x14);
  if ((uVar1 & 0x20) != 0) {
    *(undefined *)((long)param_2 + 4) = 0x72;
    uVar1 = *(uint *)(param_1 + 0x14);
  }
  if ((uVar1 & 0x10) != 0) {
    *(undefined *)((long)param_2 + 5) = 0x77;
    uVar1 = *(uint *)(param_1 + 0x14);
  }
  if ((uVar1 & 0x400) == 0) {
    if ((uVar1 & 8) != 0) {
      *(undefined *)((long)param_2 + 6) = 0x78;
    }
  }
  else {
    if ((uVar1 & 8) == 0) {
      *(undefined *)((long)param_2 + 6) = 0x53;
    }
    else {
      *(undefined *)((long)param_2 + 6) = 0x73;
    }
  }
  uVar1 = *(uint *)(param_1 + 0x14);
  if ((uVar1 & 4) != 0) {
    *(undefined *)((long)param_2 + 7) = 0x72;
    uVar1 = *(uint *)(param_1 + 0x14);
  }
  if ((uVar1 & 2) != 0) {
    *(undefined *)(param_2 + 1) = 0x77;
    uVar1 = *(uint *)(param_1 + 0x14);
  }
  if ((uVar1 & 0x200) == 0) {
    if ((uVar1 & 1) != 0) {
      *(undefined *)((long)param_2 + 9) = 0x78;
    }
  }
  else {
    if ((uVar1 & 1) == 0) {
      *(undefined *)((long)param_2 + 9) = 0x54;
    }
    else {
      *(undefined *)((long)param_2 + 9) = 0x74;
    }
  }
  return 0;
}


char * tsk_fs_time_to_str(long param_1,char *param_2)

{
  tm *ptVar1;
  time_t local_20;
  
  *param_2 = '\0';
  local_20 = param_1;
  if ((0 < param_1) && (ptVar1 = localtime(&local_20), ptVar1 != (tm *)0x0)) {
    snprintf(param_2,0x80,"%.4d-%.2d-%.2d %.2d:%.2d:%.2d (%s)",(ulong)(ptVar1->tm_year + 0x76c),
             (ulong)(ptVar1->tm_mon + 1),(ulong)(uint)ptVar1->tm_mday,(ulong)(uint)ptVar1->tm_hour,
             (ulong)(uint)ptVar1->tm_min,(ulong)(uint)ptVar1->tm_sec,
             *(undefined8 *)(&tzname + (ulong)(ptVar1->tm_isdst != 0) * 8));
    return param_2;
  }
  strncpy(param_2,"0000-00-00 00:00:00 (UTC)",0x80);
  return param_2;
}


char * tsk_fs_time_to_str_subsecs(long param_1,uint param_2,char *param_3)

{
  tm *ptVar1;
  undefined8 uVar2;
  time_t local_28;
  
  *param_3 = '\0';
  local_28 = param_1;
  if (0 < param_1) {
    uVar2 = 0x100482;
    ptVar1 = localtime(&local_28);
    if (ptVar1 != (tm *)0x0) {
      snprintf(param_3,0x40,"%.4d-%.2d-%.2d %.2d:%.2d:%.2d.%.9d (%s)",
               (ulong)(ptVar1->tm_year + 0x76c),(ulong)(ptVar1->tm_mon + 1),
               (ulong)(uint)ptVar1->tm_mday,(ulong)(uint)ptVar1->tm_hour,(ulong)(uint)ptVar1->tm_min
               ,(ulong)(uint)ptVar1->tm_sec,(ulong)param_2,
               *(undefined8 *)(&tzname + (ulong)(ptVar1->tm_isdst != 0) * 8),uVar2);
      return param_3;
    }
  }
  strncpy(param_3,"0000-00-00 00:00:00 (UTC)",0x20);
  return param_3;
}


void tsk_fs_name_print(undefined8 param_1,long param_2,long param_3,undefined8 param_4,long param_5,
                      char param_6)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  char *pcVar4;
  undefined *puVar5;
  
  uVar1 = *(uint *)(*(long *)(param_2 + 8) + 0x50);
  if (uVar1 < 0xc) {
    tsk_fprintf(param_1,&DAT_00101161,tsk_fs_name_type_str + (ulong)uVar1 * 2);
  }
  else {
    tsk_fprintf(param_1,&DAT_00101165);
  }
  lVar3 = *(long *)(param_2 + 0x10);
  if (lVar3 == 0) {
LAB_001005b0:
    puVar5 = &DAT_0010116f;
  }
  else {
    if (((param_5 == 0) || (*(int *)(param_5 + 0x28) != 0x80)) ||
       ((*(int *)(lVar3 + 0x10) != 0xb && (*(int *)(lVar3 + 0x10) != 2)))) {
      if (*(uint *)(lVar3 + 0x10) < 0xc) {
        tsk_fprintf(param_1,&DAT_0010116b,&tsk_fs_meta_type_str + (ulong)*(uint *)(lVar3 + 0x10) * 2
                   );
        goto LAB_001005bf;
      }
      goto LAB_001005b0;
    }
    puVar5 = &DAT_00101168;
  }
  tsk_fprintf(param_1,puVar5);
LAB_001005bf:
  lVar3 = *(long *)(param_2 + 8);
  if ((*(byte *)(lVar3 + 0x54) & 2) != 0) {
    tsk_fprintf(param_1,&DAT_00101172);
    lVar3 = *(long *)(param_2 + 8);
  }
  tsk_fprintf(param_1,&DAT_00101175,*(undefined8 *)(lVar3 + 0x28));
  if (param_5 != 0) {
    tsk_fprintf(param_1,"-%u-%u",(ulong)*(uint *)(param_5 + 0x28),(ulong)*(ushort *)(param_5 + 0x2c)
               );
  }
  if ((*(long *)(param_2 + 0x10) == 0) || ((*(byte *)(*(long *)(param_2 + 0x10) + 4) & 1) == 0)) {
    pcVar4 = "";
  }
  else {
    pcVar4 = "(realloc)";
    if ((*(byte *)(*(long *)(param_2 + 8) + 0x54) & 2) == 0) {
      pcVar4 = "";
    }
  }
  tsk_fprintf(param_1,&DAT_00101180,pcVar4);
  if ((param_3 != 0) && (param_6 != '\0')) {
    tsk_print_sanitized(param_1,param_3);
  }
  tsk_print_sanitized(param_1,*(undefined8 *)(*(long *)(param_2 + 8) + 8));
  if ((param_5 != 0) && (*(char **)(param_5 + 0x18) != (char *)0x0)) {
    if ((*(int *)(param_5 + 0x28) == 0x90) &&
       (iVar2 = strcmp(*(char **)(param_5 + 0x18),"$I30"), iVar2 == 0)) {
      return;
    }
    tsk_fprintf(param_1,&DAT_00101195);
    tsk_print_sanitized(param_1,*(undefined8 *)(param_5 + 0x18));
    return;
  }
  return;
}


void tsk_fs_name_print_long
               (undefined8 param_1,long param_2,undefined8 param_3,long param_4,long param_5,
               undefined8 param_6,int param_7)

{
  ulong uVar1;
  tm *ptVar2;
  undefined8 uVar3;
  long lVar4;
  ulong local_a8 [16];
  
  tsk_fs_name_print();
  if ((param_4 == 0) || (*(long *)(param_2 + 0x10) == 0)) {
    tsk_fprintf(param_1,&DAT_00101197);
    local_a8[0] = local_a8[0] & 0xffffffffffffff00;
    strncpy((char *)local_a8,"0000-00-00 00:00:00 (UTC)",0x80);
    tsk_fprintf(param_1,&DAT_001011b6,local_a8);
    tsk_fprintf(param_1,&DAT_00101197);
    local_a8[0] = local_a8[0] & 0xffffffffffffff00;
    strncpy((char *)local_a8,"0000-00-00 00:00:00 (UTC)",0x80);
    tsk_fprintf(param_1,&DAT_001011b6,local_a8);
    tsk_fprintf(param_1,&DAT_00101197);
    local_a8[0] = local_a8[0] & 0xffffffffffffff00;
    strncpy((char *)local_a8,"0000-00-00 00:00:00 (UTC)",0x80);
    tsk_fprintf(param_1,&DAT_001011b6,local_a8);
    tsk_fprintf(param_1,&DAT_00101197);
    local_a8[0] = local_a8[0] & 0xffffffffffffff00;
    strncpy((char *)local_a8,"0000-00-00 00:00:00 (UTC)",0x80);
    tsk_fprintf(param_1,&DAT_001011b6,local_a8);
    tsk_fprintf(param_1,"\t0\t0\t0");
    return;
  }
  tsk_fprintf(param_1,&DAT_00101197);
  lVar4 = *(long *)(*(long *)(param_2 + 0x10) + 0x30);
  if (lVar4 == 0) {
    lVar4 = 0;
  }
  else {
    lVar4 = lVar4 - param_7;
  }
  tsk_fs_print_time(param_1,lVar4);
  tsk_fprintf(param_1,&DAT_00101197);
  uVar1 = *(ulong *)(*(long *)(param_2 + 0x10) + 0x40);
  if ((*(byte *)(param_4 + 0x70) & 0xe) == 0) {
    if (uVar1 != 0) {
      tsk_fs_print_time(param_1,uVar1 - (long)param_7);
      goto LAB_001008b1;
    }
    local_a8[0] = 0;
  }
  else {
    local_a8[0] = uVar1;
    if ((0 < (long)uVar1) && (ptVar2 = localtime((time_t *)local_a8), ptVar2 != (tm *)0x0)) {
      tsk_fprintf(param_1,"%.4d-%.2d-%.2d 00:00:00 (%s)",(ulong)(ptVar2->tm_year + 0x76c),
                  (ulong)(ptVar2->tm_mon + 1),(ulong)(uint)ptVar2->tm_mday,
                  *(undefined8 *)(&tzname + (ulong)(ptVar2->tm_isdst != 0) * 8));
      goto LAB_001008b1;
    }
  }
  tsk_fprintf(param_1,"0000-00-00 00:00:00 (UTC)");
LAB_001008b1:
  tsk_fprintf(param_1,&DAT_00101197);
  lVar4 = *(long *)(*(long *)(param_2 + 0x10) + 0x50);
  if (lVar4 == 0) {
    lVar4 = 0;
  }
  else {
    lVar4 = lVar4 - param_7;
  }
  tsk_fs_print_time(param_1,lVar4);
  tsk_fprintf(param_1,&DAT_00101197);
  lVar4 = *(long *)(*(long *)(param_2 + 0x10) + 0x60);
  if (lVar4 == 0) {
    lVar4 = 0;
  }
  else {
    lVar4 = lVar4 - param_7;
  }
  tsk_fs_print_time(param_1,lVar4);
  if (param_5 == 0) {
    uVar3 = *(undefined8 *)(*(long *)(param_2 + 0x10) + 0x20);
  }
  else {
    uVar3 = *(undefined8 *)(param_5 + 0x30);
  }
  tsk_fprintf(param_1,&DAT_001011a0,uVar3);
  tsk_fprintf(param_1,"\t%u\t%u",(ulong)*(uint *)(*(long *)(param_2 + 0x10) + 0x2c),
              (ulong)*(uint *)(*(long *)(param_2 + 0x10) + 0x28));
  return;
}


void tsk_fs_print_time(undefined8 param_1,long param_2)

{
  tm *ptVar1;
  time_t local_a0;
  char local_98 [128];
  
  local_98[0] = '\0';
  local_a0 = param_2;
  if (0 < param_2) {
    ptVar1 = localtime(&local_a0);
    if (ptVar1 != (tm *)0x0) {
      snprintf(local_98,0x80,"%.4d-%.2d-%.2d %.2d:%.2d:%.2d (%s)",(ulong)(ptVar1->tm_year + 0x76c),
               (ulong)(ptVar1->tm_mon + 1),(ulong)(uint)ptVar1->tm_mday,(ulong)(uint)ptVar1->tm_hour
               ,(ulong)(uint)ptVar1->tm_min,(ulong)(uint)ptVar1->tm_sec,
               *(undefined8 *)(&tzname + (ulong)(ptVar1->tm_isdst != 0) * 8));
      goto LAB_001009f5;
    }
  }
  strncpy(local_98,"0000-00-00 00:00:00 (UTC)",0x80);
LAB_001009f5:
  tsk_fprintf(param_1,&DAT_001011b6,local_98);
  return;
}


undefined8 tsk_fs_name_print_mac(void)

{
  tsk_fs_name_print_mac_md5();
  return 0;
}


/* WARNING: Could not reconcile some variable overlaps */

void tsk_fs_name_print_mac_md5
               (long param_1,long param_2,long param_3,long param_4,undefined8 param_5,int param_6,
               byte *param_7)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  undefined8 uVar4;
  long lVar5;
  undefined *puVar6;
  ulong local_48;
  undefined2 local_40;
  undefined local_3e;
  undefined4 local_38;
  int local_34;
  
  if (param_1 == 0) {
    return;
  }
  if (param_2 == 0) {
    return;
  }
  local_34 = param_6;
  if ((((param_4 == 0) || (*(char **)(param_4 + 0x18) == (char *)0x0)) ||
      (iVar2 = *(int *)(param_4 + 0x28), iVar2 == 0x30)) ||
     ((iVar2 == 0x90 && (iVar2 = strcmp(*(char **)(param_4 + 0x18),"$I30"), iVar2 == 0)))) {
    local_38 = 0;
    if (param_7 == (byte *)0x0) goto LAB_00100a9f;
LAB_00100ab6:
    tsk_fprintf(param_1,&DAT_001011af,(ulong)*param_7);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[1]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[2]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[3]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[4]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[5]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[6]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[7]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[8]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[9]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[10]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[0xb]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[0xc]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[0xd]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[0xe]);
    tsk_fprintf(param_1,&DAT_001011af,(ulong)param_7[0xf]);
    puVar6 = &DAT_001011b4;
  }
  else {
    local_38 = (undefined4)CONCAT71((uint7)(uint3)((uint)iVar2 >> 8),1);
    if (param_7 != (byte *)0x0) goto LAB_00100ab6;
LAB_00100a9f:
    puVar6 = &DAT_001011ac;
  }
  tsk_fprintf(param_1,puVar6);
  iVar2 = local_34;
  tsk_fprintf(param_1,&DAT_001011b6,param_5);
  if (param_3 != 0) {
    tsk_print_sanitized(param_1,param_3);
  }
  tsk_print_sanitized(param_1,*(undefined8 *)(*(long *)(param_2 + 8) + 8));
  if ((char)local_38 != '\0') {
    tsk_fprintf(param_1,&DAT_00101195);
    tsk_print_sanitized(param_1,*(undefined8 *)(param_4 + 0x18));
  }
  if ((param_4 != 0) && (*(int *)(param_4 + 0x28) == 0x30)) {
    tsk_fprintf(param_1," ($FILE_NAME)");
  }
  lVar5 = *(long *)(param_2 + 0x10);
  if (((lVar5 != 0) && (*(int *)(lVar5 + 0x10) == 6)) && (*(long *)(lVar5 + 0xf8) != 0)) {
    tsk_fprintf(param_1," -> %s");
  }
  lVar5 = *(long *)(param_2 + 8);
  if ((*(byte *)(lVar5 + 0x54) & 2) != 0) {
    if (*(long *)(param_2 + 0x10) == 0) {
      pcVar3 = "";
    }
    else {
      pcVar3 = "-realloc";
      if ((*(byte *)(*(long *)(param_2 + 0x10) + 4) & 1) == 0) {
        pcVar3 = "";
      }
    }
    tsk_fprintf(param_1," (deleted%s)",pcVar3);
    lVar5 = *(long *)(param_2 + 8);
  }
  tsk_fprintf(param_1,&DAT_001011e4,*(undefined8 *)(lVar5 + 0x28));
  if (param_4 != 0) {
    tsk_fprintf(param_1,"-%u-%u",(ulong)*(uint *)(param_4 + 0x28),(ulong)*(ushort *)(param_4 + 0x2c)
               );
  }
  tsk_fprintf(param_1,&DAT_001011b4);
  uVar1 = *(uint *)(*(long *)(param_2 + 8) + 0x50);
  if (uVar1 < 0xc) {
    tsk_fprintf(param_1,&DAT_00101161,tsk_fs_name_type_str + (ulong)uVar1 * 2);
  }
  else {
    tsk_fprintf(param_1,&DAT_00101165);
  }
  lVar5 = *(long *)(param_2 + 0x10);
  if (lVar5 == 0) {
    tsk_fprintf(param_1,"----------|0|0|0|");
    goto LAB_00100f2f;
  }
  marker281._3640_8_ = "function_inlined: strcpy";
  local_48 = 0x2d2d2d2d2d2d2d2d;
  local_3e = 0;
  local_40 = 0x2d2d;
  local_40._0_1_ = 0x2d;
  if (*(uint *)(lVar5 + 0x10) < 0xc) {
    local_48 = CONCAT71(0x2d2d2d2d2d2d2d,(&tsk_fs_meta_type_str)[(ulong)*(uint *)(lVar5 + 0x10) * 2]
                       );
  }
  uVar1 = *(uint *)(lVar5 + 0x14);
  if ((uVar1 & 0x100) == 0) {
    if ((char)uVar1 < '\0') goto LAB_00100e48;
LAB_00100db0:
    if ((uVar1 & 0x800) != 0) goto LAB_00100e58;
LAB_00100dbb:
    if ((uVar1 & 0x40) != 0) {
      local_48._0_4_ = CONCAT13(0x78,(uint3)local_48);
      local_48 = local_48 & 0xffffffff00000000 | (ulong)(uint)local_48;
      goto joined_r0x00100e63;
    }
joined_r0x00100e72:
    if ((uVar1 & 0x20) != 0) goto LAB_00100e78;
LAB_00100dd5:
    if ((uVar1 & 0x10) != 0) goto LAB_00100e85;
LAB_00100ddd:
    if ((uVar1 & 0x400) != 0) goto LAB_00100e95;
LAB_00100de8:
    if ((uVar1 & 8) != 0) {
      local_48._0_7_ = CONCAT16(0x78,(uint6)local_48);
      local_48 = local_48 & 0xff00000000000000 | (ulong)(uint7)local_48;
      goto joined_r0x00100ea0;
    }
joined_r0x00100eaf:
    if ((uVar1 & 4) == 0) goto LAB_00100e02;
LAB_00100eb5:
    local_48 = CONCAT17(0x72,(uint7)local_48);
    if ((uVar1 & 2) == 0) goto LAB_00100e0a;
LAB_00100ec2:
    local_40 = 0x2d77;
    local_40._0_1_ = 0x77;
    if ((uVar1 & 0x200) == 0) goto LAB_00100e15;
LAB_00100ed2:
    if ((uVar1 & 1) == 0) {
      local_40 = CONCAT11(0x54,(undefined)local_40);
    }
    else {
      local_40 = CONCAT11(0x74,(undefined)local_40);
    }
  }
  else {
    local_48._0_2_ = CONCAT11(0x72,(undefined)local_48);
    local_48 = local_48 & 0xffffffffffff0000 | (ulong)(ushort)local_48;
    if (-1 < (char)uVar1) goto LAB_00100db0;
LAB_00100e48:
    local_48._0_3_ = CONCAT12(0x77,(ushort)local_48);
    local_48 = local_48 & 0xffffffffff000000 | (ulong)(uint3)local_48;
    if ((uVar1 & 0x800) == 0) goto LAB_00100dbb;
LAB_00100e58:
    if ((uVar1 & 0x40) == 0) {
      local_48._0_4_ = CONCAT13(0x53,(uint3)local_48);
      local_48 = local_48 & 0xffffffff00000000 | (ulong)(uint)local_48;
      goto joined_r0x00100e72;
    }
    local_48._0_4_ = CONCAT13(0x73,(uint3)local_48);
    local_48 = local_48 & 0xffffffff00000000 | (ulong)(uint)local_48;
joined_r0x00100e63:
    if ((uVar1 & 0x20) == 0) goto LAB_00100dd5;
LAB_00100e78:
    local_48._0_5_ = CONCAT14(0x72,(uint)local_48);
    local_48 = local_48 & 0xffffff0000000000 | (ulong)(uint5)local_48;
    if ((uVar1 & 0x10) == 0) goto LAB_00100ddd;
LAB_00100e85:
    local_48._0_6_ = CONCAT15(0x77,(uint5)local_48);
    local_48 = local_48 & 0xffff000000000000 | (ulong)(uint6)local_48;
    if ((uVar1 & 0x400) == 0) goto LAB_00100de8;
LAB_00100e95:
    if ((uVar1 & 8) == 0) {
      local_48._0_7_ = CONCAT16(0x53,(uint6)local_48);
      local_48 = local_48 & 0xff00000000000000 | (ulong)(uint7)local_48;
      goto joined_r0x00100eaf;
    }
    local_48._0_7_ = CONCAT16(0x73,(uint6)local_48);
    local_48 = local_48 & 0xff00000000000000 | (ulong)(uint7)local_48;
joined_r0x00100ea0:
    if ((uVar1 & 4) != 0) goto LAB_00100eb5;
LAB_00100e02:
    if ((uVar1 & 2) != 0) goto LAB_00100ec2;
LAB_00100e0a:
    if ((uVar1 & 0x200) != 0) goto LAB_00100ed2;
LAB_00100e15:
    if ((uVar1 & 1) != 0) {
      local_40 = CONCAT11(0x78,(undefined)local_40);
    }
  }
  tsk_fprintf(param_1,&DAT_001011fb,&local_48);
  tsk_fprintf(param_1,"%u|%u|",(ulong)*(uint *)(*(long *)(param_2 + 0x10) + 0x28),
              (ulong)*(uint *)(*(long *)(param_2 + 0x10) + 0x2c));
  if (param_4 == 0) {
    uVar4 = *(undefined8 *)(*(long *)(param_2 + 0x10) + 0x20);
  }
  else {
    uVar4 = *(undefined8 *)(param_4 + 0x30);
  }
  tsk_fprintf(param_1,&DAT_00101206,uVar4);
LAB_00100f2f:
  lVar5 = *(long *)(param_2 + 0x10);
  if (lVar5 != 0) {
    if ((param_4 == 0) || (*(int *)(param_4 + 0x28) != 0x30)) {
      if (*(long *)(lVar5 + 0x40) == 0) {
        lVar5 = 0;
      }
      else {
        lVar5 = *(long *)(lVar5 + 0x40) - (long)iVar2;
      }
      tsk_fprintf(param_1,&DAT_00101213,lVar5);
      lVar5 = *(long *)(*(long *)(param_2 + 0x10) + 0x30);
      if (lVar5 == 0) {
        lVar5 = 0;
      }
      else {
        lVar5 = lVar5 - iVar2;
      }
      tsk_fprintf(param_1,&DAT_00101213,lVar5);
      lVar5 = *(long *)(*(long *)(param_2 + 0x10) + 0x50);
      if (lVar5 == 0) {
        lVar5 = 0;
      }
      else {
        lVar5 = lVar5 - iVar2;
      }
      tsk_fprintf(param_1,&DAT_00101213,lVar5);
      lVar5 = *(long *)(*(long *)(param_2 + 0x10) + 0x60);
    }
    else {
      if (*(long *)(lVar5 + 0x90) == 0) {
        lVar5 = 0;
      }
      else {
        lVar5 = *(long *)(lVar5 + 0x90) - (long)iVar2;
      }
      tsk_fprintf(param_1,&DAT_00101213,lVar5);
      lVar5 = *(long *)(*(long *)(param_2 + 0x10) + 0x80);
      if (lVar5 == 0) {
        lVar5 = 0;
      }
      else {
        lVar5 = lVar5 - iVar2;
      }
      tsk_fprintf(param_1,&DAT_00101213,lVar5);
      lVar5 = *(long *)(*(long *)(param_2 + 0x10) + 0xa0);
      if (lVar5 == 0) {
        lVar5 = 0;
      }
      else {
        lVar5 = lVar5 - iVar2;
      }
      tsk_fprintf(param_1,&DAT_00101213,lVar5);
      lVar5 = *(long *)(*(long *)(param_2 + 0x10) + 0x70);
    }
    if (lVar5 == 0) {
      lVar5 = 0;
    }
    else {
      lVar5 = lVar5 - iVar2;
    }
    tsk_fprintf(param_1,&DAT_00101217,lVar5);
    return;
  }
  tsk_fprintf(param_1,"0|0|0|0");
  return;
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

tm * localtime(time_t *__timer)

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

void tsk_fprintf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_malloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_print_sanitized(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_realloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


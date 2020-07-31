
undefined4 * tsk_fs_meta_alloc(long param_1)

{
  long lVar1;
  undefined4 *__ptr;
  
  __ptr = (undefined4 *)tsk_malloc(0x100);
  if (__ptr == (undefined4 *)0x0) {
LAB_0010005e:
    __ptr = (undefined4 *)0x0;
  }
  else {
    __ptr[0x3a] = 0;
    if (param_1 != 0) {
      lVar1 = tsk_malloc(param_1);
      *(long *)(__ptr + 0x2e) = lVar1;
      if (lVar1 == 0) {
        free(__ptr);
        goto LAB_0010005e;
      }
      *(long *)(__ptr + 0x30) = param_1;
      *(undefined8 *)(__ptr + 0x34) = 0;
    }
    *__ptr = 0x13524635;
  }
  return __ptr;
}


long tsk_fs_meta_realloc(long param_1,long param_2)

{
  long lVar1;
  
  if (*(code **)(param_1 + 0xd0) != (code *)0x0) {
    (**(code **)(param_1 + 0xd0))(*(undefined8 *)(param_1 + 0xb8));
  }
  if (*(long *)(param_1 + 0xc0) != param_2) {
    *(long *)(param_1 + 0xc0) = param_2;
    lVar1 = tsk_realloc(*(undefined8 *)(param_1 + 0xb8),param_2);
    *(long *)(param_1 + 0xb8) = lVar1;
    if (lVar1 == 0) {
      param_1 = 0;
    }
  }
  return param_1;
}


void tsk_fs_meta_close(int *param_1)

{
  undefined8 *puVar1;
  undefined8 *__ptr;
  void *__ptr_00;
  
  if ((param_1 != (int *)0x0) && (*param_1 == 0x13524635)) {
    *param_1 = 0;
    __ptr_00 = *(void **)(param_1 + 0x2e);
    if (__ptr_00 != (void *)0x0) {
      if (*(code **)(param_1 + 0x34) != (code *)0x0) {
        (**(code **)(param_1 + 0x34))();
        __ptr_00 = *(void **)(param_1 + 0x2e);
      }
      free(__ptr_00);
    }
    param_1[0x2e] = 0;
    param_1[0x2f] = 0;
    param_1[0x30] = 0;
    param_1[0x31] = 0;
    if (*(long *)(param_1 + 0x38) != 0) {
      tsk_fs_attrlist_free();
    }
    *(undefined8 *)(param_1 + 0x38) = 0;
    free(*(void **)(param_1 + 0x3e));
    *(undefined8 *)(param_1 + 0x3e) = 0;
    __ptr = *(undefined8 **)(param_1 + 0x3c);
    while (__ptr != (undefined8 *)0x0) {
      puVar1 = (undefined8 *)*__ptr;
      free(__ptr);
      __ptr = puVar1;
    }
    free(param_1);
    return;
  }
  return;
}


void tsk_fs_meta_reset(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  undefined *puVar7;
  
  if (*(code **)(param_1 + 0x34) != (code *)0x0) {
    (**(code **)(param_1 + 0x34))(*(undefined8 *)(param_1 + 0x2e));
  }
  uVar1 = param_1[0x2e];
  uVar2 = param_1[0x2f];
  uVar3 = param_1[0x30];
  uVar4 = param_1[0x31];
  uVar5 = *(undefined8 *)(param_1 + 0x38);
  puVar6 = *(undefined8 **)(param_1 + 0x3c);
  puVar7 = *(undefined **)(param_1 + 0x3e);
  marker298._7360_8_ = "function_inlined: memset";
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[0x30] = 0;
  param_1[0x31] = 0;
  param_1[0x32] = 0;
  param_1[0x33] = 0;
  param_1[0x2c] = 0;
  param_1[0x2d] = 0;
  param_1[0x2e] = 0;
  param_1[0x2f] = 0;
  param_1[0x38] = 0;
  param_1[0x39] = 0;
  param_1[0x3a] = 0;
  param_1[0x3b] = 0;
  param_1[0x34] = 0;
  param_1[0x35] = 0;
  param_1[0x36] = 0;
  param_1[0x37] = 0;
  param_1[0x28] = 0;
  param_1[0x29] = 0;
  param_1[0x2a] = 0;
  param_1[0x2b] = 0;
  param_1[0x24] = 0;
  param_1[0x25] = 0;
  param_1[0x26] = 0;
  param_1[0x27] = 0;
  param_1[0x20] = 0;
  param_1[0x21] = 0;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  param_1[0x1c] = 0;
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  *param_1 = 0x13524635;
  param_1[0x2e] = uVar1;
  param_1[0x2f] = uVar2;
  param_1[0x30] = uVar3;
  param_1[0x31] = uVar4;
  *(undefined8 *)(param_1 + 0x38) = uVar5;
  param_1[0x3a] = 0;
  *(undefined8 **)(param_1 + 0x3c) = puVar6;
  *(undefined **)(param_1 + 0x3e) = puVar7;
  if (puVar7 != (undefined *)0x0) {
    *puVar7 = 0;
    puVar6 = *(undefined8 **)(param_1 + 0x3c);
  }
  while (puVar6 != (undefined8 *)0x0) {
    *(undefined *)(puVar6 + 1) = 0;
    puVar6[0x41] = 0;
    *(undefined4 *)(puVar6 + 0x42) = 0;
    puVar6 = (undefined8 *)*puVar6;
  }
  return;
}


undefined8 tsk_fs_meta_walk(int *param_1)

{
  undefined8 in_RAX;
  undefined8 uVar1;
  
  if ((param_1 != (int *)0x0) && (*param_1 == 0x10101010)) {
                    /* WARNING: Could not recover jumptable at 0x001002c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0x4a))();
    return uVar1;
  }
  return CONCAT71((int7)((ulong)in_RAX >> 8),1);
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void free(void *__ptr)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_attrlist_free(void)

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

void tsk_realloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


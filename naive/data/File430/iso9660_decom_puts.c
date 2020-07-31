
undefined8 iso9660_dinode_load(long param_1,long param_2,void *param_3)

{
  void *__src;
  undefined8 in_RAX;
  
  __src = *(void **)(param_1 + 0x1c0);
  while( true ) {
    if (__src == (void *)0x0) {
      return CONCAT71((int7)((ulong)in_RAX >> 8),1);
    }
    if (*(long *)((long)__src + 0x168) == param_2) break;
    __src = *(void **)((long)__src + 0x178);
  }
  memcpy(param_3,__src,0x158);
  return 0;
}


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * iso9660_open(long param_1,long param_2,ulong param_3,ulong param_4)

{
  undefined3 uVar1;
  undefined uVar2;
  undefined uVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  long lVar8;
  ulong extraout_RAX;
  ulong uVar9;
  void *__ptr;
  undefined *__ptr_00;
  void *pvVar10;
  ulong uVar11;
  ulong uVar12;
  undefined uVar13;
  undefined8 uVar14;
  char *pcVar15;
  void *__ptr_01;
  undefined uVar16;
  void **ppvVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  ulong uVar20;
  uint *puVar21;
  bool bVar22;
  uint local_224;
  byte local_218 [2];
  undefined local_216;
  undefined local_215;
  undefined local_214;
  undefined local_213;
  ulong local_210;
  void **local_208;
  uint *local_200;
  undefined8 local_1f8;
  undefined4 local_1ec;
  undefined *local_1e8;
  long local_1e0;
  long local_1d8;
  undefined4 *local_1d0;
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 uStack448;
  undefined4 uStack444;
  undefined4 local_1b8;
  undefined4 uStack436;
  undefined4 uStack432;
  undefined4 uStack428;
  undefined4 local_1a8;
  undefined4 uStack420;
  undefined4 uStack416;
  undefined4 uStack412;
  undefined4 local_198;
  undefined4 uStack404;
  undefined4 uStack400;
  undefined4 uStack396;
  undefined4 local_188;
  undefined4 uStack388;
  undefined4 uStack384;
  undefined4 uStack380;
  undefined4 local_178;
  undefined4 uStack372;
  undefined4 uStack368;
  undefined4 uStack364;
  undefined4 local_168;
  undefined4 uStack356;
  undefined4 uStack352;
  undefined4 uStack348;
  undefined4 local_158;
  undefined4 uStack340;
  undefined4 uStack336;
  undefined4 uStack332;
  undefined local_138 [264];
  
  if ((param_3 & 0x800) == 0) {
    tsk_error_reset();
    uVar14 = 0x8000006;
  }
  else {
    if (*(int *)(param_1 + 0x14) == 0) {
      tsk_error_reset();
      tsk_error_set_errno(0x8000006);
      pcVar15 = "iso9660_open: sector size is 0";
      goto LAB_00100392;
    }
    if (_tsk_verbose != 0) {
      tsk_fprintf(stderr,"iso9660_open img_info: %lu ftype: %u test: %u\n",param_1,
                  param_3 & 0xffffffff,param_4 & 0xff);
    }
    puVar7 = (undefined4 *)tsk_fs_malloc(0x1d0);
    if (puVar7 == (undefined4 *)0x0) {
      return (undefined4 *)0;
    }
    local_1f8 = param_4 & 0xffffffff | (ulong)local_1f8._4_4_ << 0x20;
    *(undefined *)(puVar7 + 0x72) = 0;
    *(undefined8 *)(puVar7 + 0x70) = 0;
    puVar7[0x1c] = 0x800;
    *(undefined8 *)(puVar7 + 0x1e) = 0x104c2e;
    puVar7[0x20] = 0;
    *puVar7 = 0x10101010;
    *(long *)(puVar7 + 2) = param_1;
    *(long *)(puVar7 + 4) = param_2;
    local_1ec = 0x1000000;
    local_1e0 = param_1;
    local_1d8 = param_2;
    tsk_guess_end_u32(puVar7 + 0x2c,&local_1ec,1);
    puVar7[0x16] = 0x800;
    puVar7[0x6c] = 0;
    puVar7[0x6d] = 0;
    puVar7[0x6e] = 0;
    puVar7[0x6f] = 0;
    puVar7[0x17] = *(undefined4 *)(*(long *)(puVar7 + 2) + 0x14);
    __ptr_00 = (undefined *)tsk_malloc(0x808);
    if (__ptr_00 != (undefined *)0x0) {
      local_208 = (void **)(puVar7 + 0x6c);
      uVar11 = 0x8000;
      bVar22 = false;
      local_200 = puVar7 + 0x2c;
      do {
        lVar8 = tsk_fs_read(puVar7,uVar11,__ptr_00,0x800);
        if (lVar8 != 0x800) {
LAB_0010039b:
          if (-1 < lVar8) {
            tsk_error_reset();
            tsk_error_set_errno(0x8000004);
          }
          tsk_error_set_errstr2("iso_load_vol_desc: Error reading");
LAB_001003c7:
          free(__ptr_00);
          break;
        }
        local_210 = uVar11;
        while (iVar5 = strncmp(__ptr_00 + 1,"CD001",5), puVar21 = local_200, iVar5 != 0) {
          if (_tsk_verbose != 0) {
            tsk_fprintf(stderr,"%s: Bad volume descriptor: Magic number is not CD001\n",
                        "iso_load_vol_desc");
          }
          if (bVar22) goto LAB_001003c7;
          if (puVar7[0x18] == 0x10) {
            uVar18 = 0x118;
            uVar19 = 0x18;
            if (_tsk_verbose != 0) {
              pcVar15 = "Trying RAW ISO9660 with 24-byte pre-block size\n";
              uVar19 = 0x18;
              uVar18 = 0x118;
LAB_00100271:
              tsk_fprintf(stderr,pcVar15);
            }
          }
          else {
            if (puVar7[0x18] != 0) {
              *(undefined8 *)(puVar7 + 0x18) = 0;
              goto LAB_001003c7;
            }
            uVar18 = 0x120;
            uVar19 = 0x10;
            if (_tsk_verbose != 0) {
              pcVar15 = "Trying RAW ISO9660 with 16-byte pre-block size\n";
              uVar19 = 0x10;
              uVar18 = 0x120;
              goto LAB_00100271;
            }
          }
          uVar11 = local_210;
          puVar7[0x18] = uVar19;
          puVar7[0x19] = uVar18;
          lVar8 = tsk_fs_read(puVar7,local_210,__ptr_00,0x800);
          if (lVar8 != 0x800) goto LAB_0010039b;
        }
        switch(*__ptr_00) {
        default:
switchD_001002c5_caseD_0:
          free(__ptr_00);
          goto LAB_00100355;
        case 1:
          if (*local_208 == (void *)0x0) {
            *(undefined **)local_208 = __ptr_00;
          }
          else {
            __ptr = *local_208;
            do {
              pvVar10 = __ptr;
              if (__ptr_00 + 0x8c == (undefined *)((long)pvVar10 + 0x8c))
              goto switchD_001002c5_caseD_0;
              __ptr = *(void **)((long)pvVar10 + 0x800);
            } while (*(void **)((long)pvVar10 + 0x800) != (void *)0x0);
LAB_0010032b:
            *(undefined **)((long)pvVar10 + 0x800) = __ptr_00;
          }
          break;
        case 2:
          if (*(void **)(puVar7 + 0x6e) != (void *)0x0) {
            __ptr = *(void **)(puVar7 + 0x6e);
            do {
              pvVar10 = __ptr;
              if (__ptr_00 + 0x8c == (undefined *)((long)pvVar10 + 0x8c))
              goto switchD_001002c5_caseD_0;
              __ptr = *(void **)((long)pvVar10 + 0x800);
            } while (*(void **)((long)pvVar10 + 0x800) != (void *)0x0);
            goto LAB_0010032b;
          }
          *(undefined **)(puVar7 + 0x6e) = __ptr_00;
          break;
        case 0xff:
          free(__ptr_00);
          ppvVar17 = local_208;
          __ptr = *(void **)(puVar7 + 0x6c);
          lVar8 = *(long *)(puVar7 + 0x6e);
          pvVar10 = __ptr;
          while (lVar8 != 0) {
            if (__ptr != (void *)0x0) {
              __ptr_01 = __ptr;
LAB_00100480:
              if (*puVar21 == 1) {
                uVar6 = *(uint *)((long)__ptr_01 + 0x94);
                uVar1 = *(undefined3 *)(lVar8 + 0x94);
                __ptr_00 = (undefined *)(lVar8 + 0x97);
              }
              else {
                uVar6 = *(uint *)((long)__ptr_01 + 0x94);
                uVar6 = uVar6 >> 0x18 | (uVar6 & 0xff0000) >> 8 | (uVar6 & 0xff00) << 8 |
                        uVar6 << 0x18;
                uVar1 = CONCAT12(*(undefined *)(lVar8 + 0x95),
                                 CONCAT11(*(undefined *)(lVar8 + 0x96),*(undefined *)(lVar8 + 0x97))
                                );
                __ptr_00 = (undefined *)(lVar8 + 0x94);
              }
              if (uVar6 != CONCAT13(*__ptr_00,uVar1)) goto code_r0x001004e6;
              if (__ptr_01 == __ptr) {
                *ppvVar17 = *(void **)((long)__ptr + 0x800);
              }
              else {
                do {
                  pvVar10 = __ptr;
                  __ptr = *(void **)((long)pvVar10 + 0x800);
                } while (__ptr != __ptr_01);
                *(undefined8 *)((long)pvVar10 + 0x800) = *(undefined8 *)((long)__ptr_01 + 0x800);
                __ptr = __ptr_01;
              }
              *(undefined8 *)((long)__ptr + 0x800) = 0;
              free(__ptr_01);
              __ptr = *ppvVar17;
              pvVar10 = __ptr;
              goto LAB_00100548;
            }
            __ptr = (void *)0x0;
LAB_00100548:
            lVar8 = *(long *)(lVar8 + 0x800);
          }
          if ((__ptr != (void *)0x0) || (*(long *)(puVar7 + 0x6e) != 0)) {
            if (pvVar10 == (void *)0x0) {
              lVar8 = *(long *)(puVar7 + 0x6e);
              if (*puVar21 == 1) {
                puVar7[0x16] = (uint)*(ushort *)(lVar8 + 0x82);
                uVar1 = *(undefined3 *)(lVar8 + 0x54);
                __ptr_00 = (undefined *)(lVar8 + 0x57);
              }
              else {
                puVar7[0x16] = (uint)CONCAT11(*(undefined *)(lVar8 + 0x82),
                                              *(undefined *)(lVar8 + 0x83));
                __ptr_00 = (undefined *)(lVar8 + 0x54);
                uVar1 = CONCAT12(*(undefined *)(lVar8 + 0x55),
                                 CONCAT11(*(undefined *)(lVar8 + 0x56),*(undefined *)(lVar8 + 0x57))
                                );
              }
              *(ulong *)(puVar7 + 0xe) = (ulong)CONCAT13(*__ptr_00,uVar1);
              *(undefined8 *)(puVar7 + 0x2a) = 0;
              *(undefined *)(puVar7 + 0x21) = *(undefined *)(lVar8 + 0x28);
              *(undefined8 *)(puVar7 + 0x2a) = 1;
              uVar11 = 1;
              do {
                *(undefined *)((long)puVar7 + uVar11 + 0x84) =
                     *(undefined *)(*(long *)(puVar7 + 0x6e) + 0x28 + uVar11);
                uVar11 = *(long *)(puVar7 + 0x2a) + 1;
                *(ulong *)(puVar7 + 0x2a) = uVar11;
              } while (uVar11 < 0x20);
            }
            else {
              if (*puVar21 == 1) {
                puVar7[0x16] = (uint)*(ushort *)((long)pvVar10 + 0x82);
                uVar1 = *(undefined3 *)((long)pvVar10 + 0x54);
                __ptr_00 = (undefined *)((long)pvVar10 + 0x57);
              }
              else {
                puVar7[0x16] = (uint)CONCAT11(*(undefined *)((long)pvVar10 + 0x82),
                                              *(undefined *)((long)pvVar10 + 0x83));
                __ptr_00 = (undefined *)((long)pvVar10 + 0x54);
                uVar1 = CONCAT12(*(undefined *)((long)pvVar10 + 0x55),
                                 CONCAT11(*(undefined *)((long)pvVar10 + 0x56),
                                          *(undefined *)((long)pvVar10 + 0x57)));
              }
              *(ulong *)(puVar7 + 0xe) = (ulong)CONCAT13(*__ptr_00,uVar1);
              *(undefined8 *)(puVar7 + 0x2a) = 0;
              *(undefined *)(puVar7 + 0x21) = *(undefined *)((long)pvVar10 + 0x28);
              *(undefined8 *)(puVar7 + 0x2a) = 1;
              uVar11 = 1;
              do {
                *(undefined *)((long)puVar7 + uVar11 + 0x84) =
                     *(undefined *)(*(long *)(puVar7 + 0x6c) + 0x28 + uVar11);
                uVar11 = *(long *)(puVar7 + 0x2a) + 1;
                *(ulong *)(puVar7 + 0x2a) = uVar11;
              } while (uVar11 < 0x20);
            }
            if (puVar7[0x16] != 0) {
              *(undefined8 *)(puVar7 + 0x10) = 0;
              lVar8 = *(ulong *)(puVar7 + 0xe) - 1;
              *(long *)(puVar7 + 0x14) = lVar8;
              *(long *)(puVar7 + 0x12) = lVar8;
              uVar11 = (*(long *)(local_1e0 + 8) - local_1d8) / (long)(ulong)(uint)puVar7[0x16];
              if (uVar11 < *(ulong *)(puVar7 + 0xe)) {
                uVar11 = uVar11 - 1;
                *(ulong *)(puVar7 + 0x14) = uVar11;
              }
              if (_tsk_verbose != 0) {
                uVar11 = tsk_fprintf(stderr);
              }
              while (__ptr = *(void **)(puVar7 + 0x70), __ptr != (void *)0x0) {
                *(undefined8 *)(puVar7 + 0x70) = *(undefined8 *)((long)__ptr + 0x178);
                free(__ptr);
                uVar11 = extraout_RAX;
              }
              *(undefined8 *)(puVar7 + 0x70) = 0;
              uVar9 = *(ulong *)(puVar7 + 0x6e);
              uVar11 = CONCAT71((int7)(uVar11 >> 8),1);
              if (uVar9 == 0) {
                local_210 = local_210 & 0xffffffff00000000 | uVar11 & 0xffffffff;
                local_224 = 0;
              }
              else {
                local_210 = local_210 & 0xffffffff00000000 | uVar11 & 0xffffffff;
                local_224 = 0;
                do {
                  if ((((*(char *)(uVar9 + 0x58) == '%') && (*(char *)(uVar9 + 0x59) == '/')) &&
                      (bVar4 = *(char *)(uVar9 + 0x5a) - 0x40, bVar4 < 6)) &&
                     ((0x29U >> ((uint)bVar4 & 0x1f) & 1) != 0)) {
                    if (*puVar21 == 1) {
                      uVar6 = *(int *)(uVar9 + 0x94) * puVar7[0x16];
                      uVar1 = *(undefined3 *)(uVar9 + 0x88);
                      __ptr_00 = (undefined *)(uVar9 + 0x8b);
                    }
                    else {
                      uVar6 = *(uint *)(uVar9 + 0x94);
                      uVar6 = (uVar6 >> 0x18 | (uVar6 & 0xff0000) >> 8 | (uVar6 & 0xff00) << 8 |
                              uVar6 << 0x18) * puVar7[0x16];
                      __ptr_00 = (undefined *)(uVar9 + 0x88);
                      uVar1 = CONCAT12(*(undefined *)(uVar9 + 0x89),
                                       CONCAT11(*(undefined *)(uVar9 + 0x8a),
                                                *(undefined *)(uVar9 + 0x8b)));
                    }
                    uVar11 = (ulong)CONCAT13(*__ptr_00,uVar1);
                    uVar20 = (ulong)uVar6;
                    local_1f8 = uVar9;
                    while (uVar11 != 0) {
                      lVar8 = tsk_fs_read(puVar7,uVar20,local_218);
                      if (lVar8 == 8) {
                        uVar11 = uVar11 - 8;
                        uVar20 = uVar20 + 8;
                        local_158 = 0;
                        uStack340 = 0;
                        uStack336 = 0;
                        uStack332 = 0;
                        local_168 = 0;
                        uStack356 = 0;
                        uStack352 = 0;
                        uStack348 = 0;
                        local_178 = 0;
                        uStack372 = 0;
                        uStack368 = 0;
                        uStack364 = 0;
                        local_188 = 0;
                        uStack388 = 0;
                        uStack384 = 0;
                        uStack380 = 0;
                        local_198 = 0;
                        uStack404 = 0;
                        uStack400 = 0;
                        uStack396 = 0;
                        local_1a8 = 0;
                        uStack420 = 0;
                        uStack416 = 0;
                        uStack412 = 0;
                        local_1b8 = 0;
                        uStack436 = 0;
                        uStack432 = 0;
                        uStack428 = 0;
                        local_1c8 = 0;
                        local_1c4 = 0;
                        uStack448 = 0;
                        uStack444 = 0;
                        uVar9 = tsk_fs_read(puVar7,uVar20,&local_1c8);
                        if (uVar9 == (ulong)local_218[0]) {
                          local_1e8 = local_138;
                          local_1d0 = &local_1c8;
                          uVar6 = tsk_UTF16toUTF8((ulong)*local_200,&local_1d0,
                                                  (long)&local_1c8 + uVar9 + 1);
                          if (uVar6 != 0) {
                            if (_tsk_verbose != 0) {
                              tsk_fprintf(stderr,"fsstat: Error converting Joliet name to UTF8: %d",
                                          (ulong)uVar6);
                            }
                            local_138[0] = 0;
                          }
                          *local_1e8 = 0;
                          uVar20 = uVar20 + uVar9 + (ulong)((uint)local_218[0] & 1);
                          uVar11 = (uVar11 - uVar9) + (long)(char)-(local_218[0] & 1);
                          uVar13 = local_213;
                          uVar16 = local_215;
                          uVar2 = local_214;
                          uVar3 = local_216;
                          if (puVar7[0x2c] != 1) {
                            uVar13 = local_216;
                            uVar16 = local_214;
                            uVar2 = local_215;
                            uVar3 = local_213;
                          }
                          local_224 = iso9660_load_inodes_dir
                                                (puVar7,(ulong)(uint)(CONCAT13(uVar13,CONCAT12(uVar2
                                                  ,CONCAT11(uVar16,uVar3))) * puVar7[0x16]),
                                                 (ulong)local_224,1,local_138,local_210 & 0xff);
                          bVar22 = local_224 != 0xffffffff;
                        }
                        else {
                          if (-1 < (long)uVar9) {
                            tsk_error_reset();
                            tsk_error_set_errno(0x8000004);
                          }
                          bVar22 = false;
                          tsk_error_set_errstr2("iso_find_inodes");
                        }
                      }
                      else {
                        if (-1 < lVar8) {
                          tsk_error_reset();
                          tsk_error_set_errno(0x8000004);
                        }
                        bVar22 = false;
                        tsk_error_set_errstr2("iso9660_load_inodes_pt");
                      }
                      ppvVar17 = local_208;
                      if (!bVar22) goto LAB_00100d6d;
                    }
                    if (local_224 == 0xffffffff) {
LAB_00100d6d:
                      local_224 = 0xffffffff;
                      goto LAB_00100d73;
                    }
                    local_210 = local_210 & 0xffffffff00000000;
                    uVar9 = local_1f8;
                    puVar21 = local_200;
                  }
                  uVar9 = *(ulong *)(uVar9 + 0x800);
                } while (uVar9 != 0);
              }
              __ptr = *ppvVar17;
              while (__ptr != (void *)0x0) {
                if (*puVar21 == 1) {
                  uVar6 = *(int *)((long)__ptr + 0x94) * puVar7[0x16];
                  uVar1 = *(undefined3 *)((long)__ptr + 0x88);
                  __ptr_00 = (undefined *)((long)__ptr + 0x8b);
                }
                else {
                  uVar6 = *(uint *)((long)__ptr + 0x94);
                  uVar6 = (uVar6 >> 0x18 | (uVar6 & 0xff0000) >> 8 | (uVar6 & 0xff00) << 8 |
                          uVar6 << 0x18) * puVar7[0x16];
                  __ptr_00 = (undefined *)((long)__ptr + 0x88);
                  uVar1 = CONCAT12(*(undefined *)((long)__ptr + 0x89),
                                   CONCAT11(*(undefined *)((long)__ptr + 0x8a),
                                            *(undefined *)((long)__ptr + 0x8b)));
                }
                uVar9 = (ulong)CONCAT13(*__ptr_00,uVar1);
                uVar11 = (ulong)uVar6;
                while (uVar9 != 0) {
                  uVar20 = tsk_fs_read(puVar7,uVar11,&local_1c8,8);
                  if (uVar20 != 8) {
LAB_00100d4b:
                    if (-1 < (long)uVar20) {
                      tsk_error_reset();
                      tsk_error_set_errno(0x8000004);
                    }
                    tsk_error_set_errstr2("iso_find_inodes");
                    goto LAB_00100d6d;
                  }
                  uVar12 = (ulong)(byte)local_1c8;
                  if ((char)(byte)local_1c8 < '\0') {
                    uVar12 = 0x80;
                  }
                  uVar20 = tsk_fs_read(puVar7,uVar11 + 8,local_138,uVar12);
                  if (uVar20 != uVar12) goto LAB_00100d4b;
                  local_138[uVar12] = 0;
                  uVar11 = (ulong)(local_1c8 & 1) + uVar11 + 8 + uVar12;
                  uVar9 = (long)(char)-((byte)local_1c8 & 1) + ((uVar9 - 8) - uVar12);
                  uVar16 = local_1c8._2_1_;
                  if (puVar7[0x2c] != 1) {
                    uVar16 = local_1c4._1_1_;
                  }
                  uVar2 = local_1c8._3_1_;
                  if (puVar7[0x2c] != 1) {
                    local_1c4._1_1_ = local_1c8._2_1_;
                    uVar2 = (undefined)local_1c4;
                    local_1c4._0_1_ = local_1c8._3_1_;
                  }
                  local_224 = iso9660_load_inodes_dir
                                        (puVar7,(ulong)(uint)(CONCAT13(local_1c4._1_1_,
                                                                       CONCAT12((undefined)local_1c4
                                                                                ,CONCAT11(uVar2,
                                                  uVar16))) * puVar7[0x16]),(ulong)local_224,0,
                                         local_138,local_210 & 0xff);
                  if (local_224 == 0xffffffff) goto LAB_00100d6d;
                }
                __ptr = *(void **)((long)__ptr + 0x800);
                puVar21 = local_200;
              }
LAB_00100d73:
              lVar8 = (long)(int)local_224;
              *(long *)(puVar7 + 6) = lVar8;
              if (local_224 != 0xffffffff) {
                *(long *)(puVar7 + 6) = lVar8 + 1;
                *(long *)(puVar7 + 0xc) = lVar8;
                puVar7[8] = 0;
                puVar7[9] = 0;
                puVar7[10] = 0;
                puVar7[0xb] = 0;
                *(undefined8 *)(puVar7 + 0x4a) = 0x100fa0;
                *(undefined8 *)(puVar7 + 0x46) = 0x101290;
                *(undefined8 *)(puVar7 + 0x48) = 0x101470;
                *(undefined8 *)(puVar7 + 0x4e) = 0x101560;
                *(undefined8 *)(puVar7 + 0x50) = 0x101570;
                *(undefined8 *)(puVar7 + 0x4c) = 0x1017b0;
                *(undefined8 *)(puVar7 + 0x56) = 0x107028;
                *(undefined8 *)(puVar7 + 0x5e) = 0x1018d0;
                *(undefined8 *)(puVar7 + 0x62) = 0x102630;
                *(undefined8 *)(puVar7 + 0x54) = 0x102660;
                *(undefined8 *)(puVar7 + 100) = 0x100ed0;
                *(undefined8 *)(puVar7 + 0x60) = 0x107030;
                *(undefined8 *)(puVar7 + 0x5a) = 0x102ec0;
                *(undefined8 *)(puVar7 + 0x5c) = 0x102ef0;
                *(undefined8 *)(puVar7 + 0x58) = 0x102f20;
                return puVar7;
              }
              *puVar7 = 0;
              iso9660_close(puVar7);
              marker317._120_8_ = "function_inlined: fprintf";
              if (_tsk_verbose == 0) {
                return (undefined4 *)0;
              }
              fwrite("iso9660_open: Error loading primary table\n",0x2a,1,stderr);
              return (undefined4 *)0;
            }
            *puVar7 = 0;
            iso9660_close(puVar7);
            marker317._11440_8_ = "function_inlined: fprintf";
            if (_tsk_verbose == 0) {
            }
            else {
              fwrite("iso9660_open: Block size is 0\n",0x1e,1,stderr);
            }
            if ((char)local_1f8 != '\0') {
              return (undefined4 *)0;
            }
            tsk_error_reset();
            tsk_error_set_errno(0x800000a);
            pcVar15 = "Block size is 0";
            goto LAB_00100392;
          }
          tsk_error_reset();
          tsk_error_set_errno(0x800000a);
          tsk_error_set_errstr("load_vol_desc: primary and secondary volume descriptors null");
          goto LAB_001003cf;
        }
        *(undefined8 *)(__ptr_00 + 0x800) = 0;
LAB_00100355:
        uVar11 = uVar11 + 0x800;
        __ptr_00 = (undefined *)tsk_malloc(0x808);
        bVar22 = true;
      } while (__ptr_00 != (undefined *)0x0);
    }
LAB_001003cf:
    *puVar7 = 0;
    iso9660_close(puVar7);
    if (_tsk_verbose == 0) {
    }
    else {
      fwrite("iso9660_open: Error loading volume descriptor\n",0x2e,1,stderr);
    }
    if ((char)local_1f8 != '\0') {
      return (undefined4 *)0;
    }
    tsk_error_reset();
    uVar14 = 0x800000a;
  }
  tsk_error_set_errno(uVar14);
  pcVar15 = "Invalid FS type in iso9660_open";
LAB_00100392:
  tsk_error_set_errstr(pcVar15);
  return (undefined4 *)0;
code_r0x001004e6:
  __ptr_01 = *(void **)((long)__ptr_01 + 0x800);
  if (__ptr_01 == (void *)0x0) goto LAB_00100548;
  goto LAB_00100480;
}


void iso9660_close(undefined4 *param_1)

{
  void *__ptr;
  
  *param_1 = 0;
  __ptr = *(void **)(param_1 + 0x6c);
  while (__ptr != (void *)0x0) {
    *(undefined8 *)(param_1 + 0x6c) = *(undefined8 *)((long)__ptr + 0x800);
    free(__ptr);
    __ptr = *(void **)(param_1 + 0x6c);
  }
  while (__ptr = *(void **)(param_1 + 0x6e), __ptr != (void *)0x0) {
    *(undefined8 *)(param_1 + 0x6e) = *(undefined8 *)((long)__ptr + 0x800);
    free(__ptr);
  }
  while (__ptr = *(void **)(param_1 + 0x70), __ptr != (void *)0x0) {
    *(undefined8 *)(param_1 + 0x70) = *(undefined8 *)((long)__ptr + 0x178);
    if (*(void **)((long)__ptr + 0x138) != (void *)0x0) {
      free(*(void **)((long)__ptr + 0x138));
    }
    free(__ptr);
  }
  tsk_fs_free(param_1);
  return;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong iso9660_inode_walk(undefined4 *param_1,ulong param_2,ulong param_3,ulong param_4,code *param_5
                        ,undefined8 param_6)

{
  uint uVar1;
  void *__src;
  char cVar2;
  uint uVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  void *__dest;
  ulong uVar7;
  ulong uVar8;
  char *pcVar9;
  undefined7 uVar10;
  
  uVar8 = param_4 & 0xffffffff;
  tsk_error_reset();
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"iso9660_inode_walk:  start: %lu last: %lu flags: %d action: %lu ptr: %lu\n",
                param_2,param_3,uVar8,param_5,param_6);
  }
  uVar10 = (undefined7)((ulong)param_5 >> 8);
  if ((param_2 < *(ulong *)(param_1 + 10)) || (*(ulong *)(param_1 + 0xc) < param_2)) {
    tsk_error_reset();
    tsk_error_set_errno(0x8000003);
    pcVar9 = "%s: Start inode:  %lu";
    param_3 = param_2;
LAB_00101024:
    tsk_error_set_errstr(pcVar9,"iso9660_inode_walk",param_3);
  }
  else {
    if (((param_3 < param_2) || (param_3 < *(ulong *)(param_1 + 10))) ||
       (*(ulong *)(param_1 + 0xc) < param_3)) {
      tsk_error_reset();
      tsk_error_set_errno(0x8000003);
      pcVar9 = "%s: End inode: %lu";
      goto LAB_00101024;
    }
    if ((param_4 & 0x20) == 0) {
      if ((param_4 & 3) == 0) {
        uVar8 = (ulong)((uint)uVar8 | 3);
      }
    }
    else {
      uVar8 = (ulong)((uint)uVar8 & 0xfffffff0 | 6);
    }
    uVar3 = (uint)uVar8 | 0xc;
    if ((uVar8 & 0xc) != 0) {
      uVar3 = (uint)uVar8;
    }
    if (((uVar3 & 0x20) == 0) || (iVar4 = tsk_fs_dir_load_inum_named(param_1), iVar4 == 0)) {
      lVar5 = tsk_fs_file_alloc(param_1);
      uVar8 = CONCAT71(uVar10,1);
      if (lVar5 != 0) {
        lVar6 = tsk_fs_meta_alloc(8);
        *(long *)(lVar5 + 0x10) = lVar6;
        if (lVar6 != 0) {
          uVar7 = *(ulong *)(param_1 + 0xc);
          __dest = (void *)tsk_malloc(0x158);
          if (__dest == (void *)0x0) {
            *param_1 = 0;
            iso9660_close(param_1);
          }
          else {
            uVar7 = param_3 - (uVar7 == param_3);
            if (param_2 <= uVar7) {
              do {
                __src = *(void **)(param_1 + 0x70);
                while( true ) {
                  if (__src == (void *)0x0) goto LAB_00101262;
                  if (*(ulong *)((long)__src + 0x168) == param_2) break;
                  __src = *(void **)((long)__src + 0x178);
                }
                memcpy(__dest,__src,0x158);
                cVar2 = iso9660_dinode_copy(param_1,*(undefined8 *)(lVar5 + 0x10),param_2);
                if (cVar2 != '\0') {
                  free(__dest);
                  goto LAB_0010102c;
                }
                uVar1 = *(uint *)(*(long *)(lVar5 + 0x10) + 4);
                if (((uVar1 & uVar3) == uVar1) &&
                   (((uVar1 & 2) == 0 || (uVar3 & 0x20) == 0 ||
                    (cVar2 = tsk_fs_dir_find_inum_named(param_1,param_2), cVar2 == '\0')))) {
                  iVar4 = (*param_5)(lVar5,param_6);
                  if (iVar4 == 1) break;
                  if (iVar4 == 2) goto LAB_00101262;
                }
                param_2 = param_2 + 1;
              } while (param_2 <= uVar7);
            }
            if ((((uVar3 & 5) == 5) && (*(ulong *)(param_1 + 0xc) == param_3)) &&
               ((cVar2 = tsk_fs_dir_make_orphan_dir_meta(param_1,*(undefined8 *)(lVar5 + 0x10)),
                cVar2 != '\0' || (iVar4 = (*param_5)(lVar5,param_6), iVar4 == 2)))) {
LAB_00101262:
              tsk_fs_file_close(lVar5);
              free(__dest);
            }
            else {
              tsk_fs_file_close(lVar5);
              free(__dest);
              uVar8 = 0;
            }
          }
        }
      }
      goto LAB_0010102c;
    }
    tsk_error_errstr2_concat("- iso9660_inode_walk: identifying inodes allocated by file names");
  }
  uVar8 = CONCAT71(uVar10,1);
LAB_0010102c:
  return uVar8 & 0xffffffff;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong iso9660_block_walk(long param_1,ulong param_2,ulong param_3,ulong param_4,code *param_5,
                        undefined8 param_6)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  ulong uVar6;
  char *pcVar7;
  
  uVar6 = param_4;
  tsk_error_reset();
  if (_tsk_verbose != 0) {
    uVar6 = param_3;
    tsk_fprintf(stderr,"iso9660_block_walk:  start: %lu last: %lu flags: %d action: %lu ptr: %lu\n",
                param_2,param_3,param_4 & 0xffffffff,param_5,param_6);
  }
  if ((param_2 < *(ulong *)(param_1 + 0x40)) ||
     (uVar6 = *(ulong *)(param_1 + 0x48), uVar6 < param_2)) {
    tsk_error_reset();
    tsk_error_set_errno(0x8000003);
    pcVar7 = "%s: Start block: %lu";
    param_3 = param_2;
  }
  else {
    if ((*(ulong *)(param_1 + 0x40) <= param_3) && (param_3 <= uVar6)) {
      uVar1 = (uint)(param_4 & 0xffffffff);
      uVar2 = uVar1 | 3;
      if ((param_4 & 3) != 0) {
        uVar2 = uVar1;
      }
      uVar1 = uVar2 | 0xc;
      if ((uVar2 & 0xc) != 0) {
        uVar1 = uVar2;
      }
      lVar4 = tsk_fs_block_alloc(param_1);
      uVar6 = CONCAT71((int7)(uVar6 >> 8),1);
      if (lVar4 != 0) {
        if (_tsk_verbose != 0) {
          tsk_fprintf(stderr,"isofs_block_walk: Block Walking %lu to %lu\n",param_2);
        }
        if (param_2 <= param_3) {
          do {
            uVar2 = iso9660_block_getflags(param_1,param_2);
            if ((((uVar1 & 1) != 0) || ((uVar2 & 1) == 0)) &&
               (((uVar1 & 2) != 0 || ((uVar2 & 2) == 0)))) {
              uVar6 = (ulong)(uVar2 | (uVar1 & 0x10) << 5);
              lVar5 = tsk_fs_block_get_flag(param_1,lVar4,param_2);
              if (lVar5 == 0) {
                tsk_error_set_errstr2("iso_block_walk");
              }
              else {
                iVar3 = (*param_5)(lVar4,param_6);
                if (iVar3 == 1) break;
                if (iVar3 != 2) goto LAB_0010140d;
              }
              tsk_fs_block_free(lVar4);
              goto LAB_00101319;
            }
LAB_0010140d:
            param_2 = param_2 + 1;
          } while (param_2 <= param_3);
        }
        tsk_fs_block_free(lVar4);
        uVar6 = 0;
      }
      goto LAB_0010131b;
    }
    tsk_error_reset();
    tsk_error_set_errno(0x8000003);
    pcVar7 = "%s: End block: %lu";
  }
  tsk_error_set_errstr(pcVar7,"iso9660_block_walk",param_3);
LAB_00101319:
  uVar6 = CONCAT71((int7)(uVar6 >> 8),1);
LAB_0010131b:
  return uVar6 & 0xffffffff;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 iso9660_block_getflags(long param_1,ulong param_2)

{
  uint uVar1;
  undefined3 uVar2;
  ulong uVar3;
  undefined *puVar4;
  long lVar5;
  
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"iso9660_is_block_alloc:  blk_num: %lu\n",param_2);
  }
  lVar5 = *(long *)(param_1 + 0x1c0);
  if (lVar5 != 0) {
    uVar1 = *(uint *)(param_1 + 0x58);
    do {
      uVar3 = *(long *)(lVar5 + 0x158) / (long)(ulong)uVar1;
      if (*(int *)(param_1 + 0xb0) == 1) {
        uVar2 = *(undefined3 *)(lVar5 + 0xe);
        puVar4 = (undefined *)(lVar5 + 0x11);
      }
      else {
        puVar4 = (undefined *)(lVar5 + 0xe);
        uVar2 = CONCAT12(*(undefined *)(lVar5 + 0xf),
                         CONCAT11(*(undefined *)(lVar5 + 0x10),*(undefined *)(lVar5 + 0x11)));
      }
      if ((uVar3 <= param_2) &&
         (param_2 <=
          ((ulong)CONCAT13(*puVar4,uVar2) / (ulong)uVar1 + uVar3 + 1) -
          (ulong)(CONCAT13(*puVar4,uVar2) % uVar1 == 0))) {
        return 1;
      }
      lVar5 = *(long *)(lVar5 + 0x178);
    } while (lVar5 != 0);
  }
  return 2;
}


undefined8 iso9660_get_default_attr_type(void)

{
  return 1;
}


ulong iso9660_make_data_run(long param_1)

{
  byte bVar1;
  uint uVar2;
  undefined4 *puVar3;
  long lVar4;
  char cVar5;
  void *__dest;
  long lVar6;
  long lVar7;
  ulong uVar8;
  ulong unaff_RBP;
  undefined7 uVar10;
  ulong uVar9;
  void *__src;
  ulong uVar11;
  undefined8 uVar12;
  
  tsk_error_reset();
  uVar10 = (undefined7)(unaff_RBP >> 8);
  if (((param_1 == 0) || (lVar6 = *(long *)(param_1 + 0x10), lVar6 == 0)) ||
     (puVar3 = *(undefined4 **)(param_1 + 0x18), puVar3 == (undefined4 *)0x0)) {
    tsk_error_set_errno(0x8000006);
    tsk_error_set_errstr("iso9660_make_data_run: fs_file or meta is NULL");
    uVar9 = CONCAT71(uVar10,1);
  }
  else {
    if ((*(int *)(lVar6 + 0xe8) == 1) && (*(long *)(lVar6 + 0xe0) != 0)) {
LAB_001015b3:
      uVar9 = 0;
    }
    else {
      uVar9 = CONCAT71(uVar10,1);
      if (*(int *)(lVar6 + 0xe8) != 2) {
        if (*(long *)(lVar6 + 0xe0) == 0) {
          uVar12 = tsk_fs_attrlist_alloc();
          *(undefined8 *)(*(long *)(param_1 + 0x10) + 0xe0) = uVar12;
        }
        else {
          tsk_fs_attrlist_markunused();
        }
        __dest = (void *)tsk_malloc(0x158);
        if (__dest == (void *)0x0) {
          *puVar3 = 0;
          iso9660_close(puVar3);
        }
        else {
          __src = *(void **)(puVar3 + 0x70);
          if (__src != (void *)0x0) {
            do {
              if (*(long *)((long)__src + 0x168) == *(long *)(*(long *)(param_1 + 0x10) + 8)) {
                memcpy(__dest,__src,0x158);
                bVar1 = *(byte *)((long)__dest + 1);
                cVar5 = *(char *)((long)__dest + 0x1b);
                free(__dest);
                if (cVar5 != '\0') {
                  *(undefined4 *)(*(long *)(param_1 + 0x10) + 0xe8) = 2;
                  tsk_error_set_errno(0x8000002);
                  tsk_error_set_errstr
                            ("file %lu has an interleave gap -- not supported",
                             *(undefined8 *)(*(long *)(param_1 + 0x10) + 8));
                  goto LAB_001015d0;
                }
                lVar6 = tsk_fs_attrlist_getnew(*(undefined8 *)(*(long *)(param_1 + 0x10) + 0xe0),2);
                if (lVar6 == 0) goto LAB_001015d0;
                uVar12 = 0x1016f8;
                lVar7 = tsk_fs_attr_run_alloc();
                if (lVar7 == 0) {
                  uVar9 = unaff_RBP & 0xffffffffffffff00 | 0xff;
                  goto LAB_001015d0;
                }
                lVar4 = *(long *)(param_1 + 0x10);
                *(undefined8 *)(lVar7 + 0x10) = **(undefined8 **)(lVar4 + 0xb8);
                lVar4 = *(long *)(lVar4 + 0x20);
                uVar2 = puVar3[0x16];
                uVar8 = (ulong)uVar2;
                *(long *)(lVar7 + 0x18) = (long)(lVar4 + uVar8 + -1) / (long)uVar8;
                *(undefined8 *)(lVar7 + 8) = 0;
                uVar11 = (ulong)(uVar2 - 1);
                cVar5 = tsk_fs_attr_set_run(param_1,lVar6,lVar7,0,1,0,lVar4,lVar4,
                                            (uVar11 + lVar4) -
                                            (long)(lVar4 + (ulong)bVar1 + uVar11) % uVar8,0,0,uVar12
                                           );
                if (cVar5 != '\0') goto LAB_001015d0;
                *(uint *)(lVar6 + 0x48) = (uint)bVar1;
                *(undefined4 *)(*(long *)(param_1 + 0x10) + 0xe8) = 1;
                goto LAB_001015b3;
              }
              __src = *(void **)((long)__src + 0x178);
            } while (__src != (void *)0x0);
          }
          tsk_error_set_errstr2("iso9660_make_data_run");
          *(undefined4 *)(*(long *)(param_1 + 0x10) + 0xe8) = 2;
          free(__dest);
        }
      }
    }
  }
LAB_001015d0:
  return uVar9 & 0xffffffff;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong iso9660_inode_lookup(undefined4 *param_1,long param_2,ulong param_3)

{
  void *__src;
  char cVar1;
  void *__dest;
  long lVar2;
  ulong uVar3;
  
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"iso9660_inode_lookup: iso: inum: %lu\n",param_3);
  }
  if (param_2 == 0) {
    tsk_error_set_errno(0x8000006);
    tsk_error_set_errstr("iso9660_inode_lookup: fs_file is NULL");
  }
  else {
    if (*(long *)(param_2 + 0x10) == 0) {
      lVar2 = tsk_fs_meta_alloc(8);
      *(long *)(param_2 + 0x10) = lVar2;
      if (lVar2 == 0) goto LAB_00101892;
      uVar3 = *(ulong *)(param_1 + 0xc);
    }
    else {
      tsk_fs_meta_reset();
      uVar3 = *(ulong *)(param_1 + 0xc);
    }
    if (uVar3 == param_3) {
      cVar1 = tsk_fs_dir_make_orphan_dir_meta(param_1,*(undefined8 *)(param_2 + 0x10));
      uVar3 = param_3 & 0xffffffffffffff00 | (ulong)(cVar1 != '\0');
      goto LAB_00101894;
    }
    __dest = (void *)tsk_malloc(0x158);
    if (__dest == (void *)0x0) {
      *param_1 = 0;
      iso9660_close(param_1);
    }
    else {
      __src = *(void **)(param_1 + 0x70);
      while (__src != (void *)0x0) {
        if (*(ulong *)((long)__src + 0x168) == param_3) {
          memcpy(__dest,__src,0x158);
          cVar1 = iso9660_dinode_copy(param_1,*(undefined8 *)(param_2 + 0x10),param_3,__dest);
          uVar3 = param_3 & 0xffffffffffffff00 | (ulong)(cVar1 != '\0');
          free(__dest);
          goto LAB_00101894;
        }
        __src = *(void **)((long)__src + 0x178);
      }
      free(__dest);
    }
  }
LAB_00101892:
  uVar3 = CONCAT71((int7)(param_3 >> 8),1);
LAB_00101894:
  return uVar3 & 0xffffffff;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 iso9660_fsstat(long param_1,undefined8 param_2)

{
  char *__s1;
  byte bVar1;
  char cVar2;
  ulong uVar3;
  undefined3 uVar4;
  long lVar5;
  int iVar6;
  ushort **ppuVar7;
  undefined *puVar8;
  long lVar9;
  long lVar10;
  uint uVar11;
  uint uVar12;
  ulong uVar13;
  undefined4 local_b8;
  uint uStack180;
  undefined4 uStack176;
  undefined4 uStack172;
  undefined4 local_a8;
  uint uStack164;
  undefined4 uStack160;
  undefined4 uStack156;
  undefined4 uStack152;
  uint uStack148;
  undefined4 uStack144;
  undefined4 uStack140;
  undefined4 local_88;
  uint uStack132;
  undefined4 uStack128;
  undefined4 uStack124;
  undefined4 local_78;
  uint uStack116;
  undefined4 uStack112;
  undefined4 uStack108;
  undefined4 local_68;
  uint uStack100;
  undefined4 uStack96;
  undefined4 uStack92;
  undefined4 local_58;
  uint uStack84;
  undefined4 uStack80;
  undefined4 uStack76;
  undefined4 local_48;
  uint uStack68;
  undefined4 uStack64;
  undefined4 uStack60;
  
  tsk_error_reset();
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"iso9660_fsstat:\n");
  }
  lVar10 = *(long *)(param_1 + 0x1b0);
  if (lVar10 != 0) {
    uVar13 = 0;
    do {
      uVar13 = (ulong)((int)uVar13 + 1);
      tsk_fprintf(param_2,"\n=== PRIMARY VOLUME DESCRIPTOR %d ===\n",uVar13);
      tsk_fprintf(param_2,"FILE SYSTEM INFORMATION\n");
      tsk_fprintf(param_2,"--------------------------------------------\n");
      tsk_fprintf(param_2,"File System Type: ISO9660\n");
      tsk_fprintf(param_2,"Volume Name: %s\n",lVar10 + 0x28);
      uVar3 = (ulong)(*(int *)(param_1 + 0xb0) == 1);
      bVar1 = *(byte *)((lVar10 - uVar3) + 0x7b);
      tsk_fprintf(param_2,"Volume Set Size: %d\n",
                  (ulong)CONCAT11(*(undefined *)(lVar10 + 0x7a + uVar3),bVar1),(ulong)bVar1);
      uVar3 = (ulong)(*(int *)(param_1 + 0xb0) == 1);
      bVar1 = *(byte *)((lVar10 - uVar3) + 0x7f);
      tsk_fprintf(param_2,"Volume Set Sequence: %d\n",
                  (ulong)CONCAT11(*(undefined *)(lVar10 + 0x7e + uVar3),bVar1),(ulong)bVar1);
      if (*(char *)(lVar10 + 0x13e) == '_') {
        snprintf((char *)&local_b8,8,"In file\n");
      }
      else {
        snprintf((char *)&local_b8,0x80,"%s",lVar10 + 0x13e);
      }
      marker317._2968_8_ = "function_inlined: isprint";
      marker317._4824_8_ = "function_inlined: isspace";
      ppuVar7 = __ctype_b_loc();
      lVar5 = 0x7f;
      do {
        lVar9 = lVar5;
        if (lVar9 == 0) break;
        lVar5 = lVar9 + -1;
      } while (((*ppuVar7)[*(char *)((long)&local_b8 + lVar9)] & 0x6000) != 0x4000);
      *(undefined *)((long)&local_b8 + lVar9 + 1) = 0;
      tsk_fprintf(param_2,"Publisher: %s\n",&local_b8);
      marker317._14536_8_ = "function_inlined: memset";
      local_48 = LCPI9_0;
      uStack68 = DAT_00104ba4;
      uStack64 = DAT_00104ba8;
      uStack60 = DAT_00104bac;
      local_58 = LCPI9_0;
      uStack84 = DAT_00104ba4;
      uStack80 = DAT_00104ba8;
      uStack76 = DAT_00104bac;
      local_68 = LCPI9_0;
      uStack100 = DAT_00104ba4;
      uStack96 = DAT_00104ba8;
      uStack92 = DAT_00104bac;
      local_78 = LCPI9_0;
      uStack116 = DAT_00104ba4;
      uStack112 = DAT_00104ba8;
      uStack108 = DAT_00104bac;
      local_88 = LCPI9_0;
      uStack132 = DAT_00104ba4;
      uStack128 = DAT_00104ba8;
      uStack124 = DAT_00104bac;
      uStack152 = LCPI9_0;
      uStack148 = DAT_00104ba4;
      uStack144 = DAT_00104ba8;
      uStack140 = DAT_00104bac;
      local_a8 = LCPI9_0;
      uStack164 = DAT_00104ba4;
      uStack160 = DAT_00104ba8;
      uStack156 = DAT_00104bac;
      local_b8 = LCPI9_0;
      uStack180 = DAT_00104ba4;
      uStack176 = DAT_00104ba8;
      uStack172 = DAT_00104bac;
      if (*(char *)(lVar10 + 0x1be) == '_') {
        snprintf((char *)&local_b8,8,"In file\n");
      }
      else {
        snprintf((char *)&local_b8,0x80,"%s",lVar10 + 0x1be);
      }
      marker317._6320_8_ = "function_inlined: isprint";
      marker317._7528_8_ = "function_inlined: isspace";
      lVar5 = 0x7f;
      do {
        lVar9 = lVar5;
        if (lVar9 == 0) break;
        lVar5 = lVar9 + -1;
      } while (((*ppuVar7)[*(char *)((long)&local_b8 + lVar9)] & 0x6000) != 0x4000);
      *(undefined *)((long)&local_b8 + lVar9 + 1) = 0;
      tsk_fprintf(param_2,"Data Preparer: %s\n",&local_b8);
      marker317._7536_8_ = "function_inlined: memset";
      local_48 = LCPI9_0;
      uStack68 = DAT_00104ba4;
      uStack64 = DAT_00104ba8;
      uStack60 = DAT_00104bac;
      local_58 = LCPI9_0;
      uStack84 = DAT_00104ba4;
      uStack80 = DAT_00104ba8;
      uStack76 = DAT_00104bac;
      local_68 = LCPI9_0;
      uStack100 = DAT_00104ba4;
      uStack96 = DAT_00104ba8;
      uStack92 = DAT_00104bac;
      local_78 = LCPI9_0;
      uStack116 = DAT_00104ba4;
      uStack112 = DAT_00104ba8;
      uStack108 = DAT_00104bac;
      local_88 = LCPI9_0;
      uStack132 = DAT_00104ba4;
      uStack128 = DAT_00104ba8;
      uStack124 = DAT_00104bac;
      uStack152 = LCPI9_0;
      uStack148 = DAT_00104ba4;
      uStack144 = DAT_00104ba8;
      uStack140 = DAT_00104bac;
      local_a8 = LCPI9_0;
      uStack164 = DAT_00104ba4;
      uStack160 = DAT_00104ba8;
      uStack156 = DAT_00104bac;
      local_b8 = LCPI9_0;
      uStack180 = DAT_00104ba4;
      uStack176 = DAT_00104ba8;
      uStack172 = DAT_00104bac;
      if (*(char *)(lVar10 + 0x23e) == '_') {
        snprintf((char *)&local_b8,8,"In file\n");
      }
      else {
        snprintf((char *)&local_b8,0x80,"%s",lVar10 + 0x23e);
      }
      marker317._10112_8_ = "function_inlined: isprint";
      marker317._7224_8_ = "function_inlined: isspace";
      lVar5 = 0x7f;
      do {
        lVar9 = lVar5;
        if (lVar9 == 0) break;
        lVar5 = lVar9 + -1;
      } while (((*ppuVar7)[*(char *)((long)&local_b8 + lVar9)] & 0x6000) != 0x4000);
      *(undefined *)((long)&local_b8 + lVar9 + 1) = 0;
      tsk_fprintf(param_2,"Recording Application: %s\n",&local_b8);
      marker317._824_8_ = "function_inlined: memset";
      local_48 = LCPI9_0;
      uStack68 = DAT_00104ba4;
      uStack64 = DAT_00104ba8;
      uStack60 = DAT_00104bac;
      local_58 = LCPI9_0;
      uStack84 = DAT_00104ba4;
      uStack80 = DAT_00104ba8;
      uStack76 = DAT_00104bac;
      local_68 = LCPI9_0;
      uStack100 = DAT_00104ba4;
      uStack96 = DAT_00104ba8;
      uStack92 = DAT_00104bac;
      local_78 = LCPI9_0;
      uStack116 = DAT_00104ba4;
      uStack112 = DAT_00104ba8;
      uStack108 = DAT_00104bac;
      local_88 = LCPI9_0;
      uStack132 = DAT_00104ba4;
      uStack128 = DAT_00104ba8;
      uStack124 = DAT_00104bac;
      uStack152 = LCPI9_0;
      uStack148 = DAT_00104ba4;
      uStack144 = DAT_00104ba8;
      uStack140 = DAT_00104bac;
      local_a8 = LCPI9_0;
      uStack164 = DAT_00104ba4;
      uStack160 = DAT_00104ba8;
      uStack156 = DAT_00104bac;
      local_b8 = LCPI9_0;
      uStack180 = DAT_00104ba4;
      uStack176 = DAT_00104ba8;
      uStack172 = DAT_00104bac;
      if (*(char *)(lVar10 + 0x2be) == '_') {
        snprintf((char *)&local_b8,8,"In file\n");
      }
      else {
        snprintf((char *)&local_b8,0x25,"%s",lVar10 + 0x2be);
      }
      marker317._14384_8_ = "function_inlined: isprint";
      marker317._784_8_ = "function_inlined: isspace";
      lVar5 = 0x24;
      do {
        lVar9 = lVar5;
        if (lVar9 == 0) break;
        lVar5 = lVar9 + -1;
      } while (((*ppuVar7)[*(char *)((long)&local_b8 + lVar9)] & 0x6000) != 0x4000);
      *(undefined *)((long)&local_b8 + lVar9 + 1) = 0;
      tsk_fprintf(param_2,"Copyright: %s\n",&local_b8);
      marker317._1464_8_ = "function_inlined: memset";
      uStack152 = 0x20202020;
      uStack148 = uStack148 & 0xffffff00 | 0x20;
      local_a8 = LCPI9_0;
      uStack164 = DAT_00104ba4;
      uStack160 = DAT_00104ba8;
      uStack156 = DAT_00104bac;
      local_b8 = LCPI9_0;
      uStack180 = DAT_00104ba4;
      uStack176 = DAT_00104ba8;
      uStack172 = DAT_00104bac;
      tsk_fprintf(param_2,"\nMETADATA INFORMATION\n");
      tsk_fprintf(param_2,"--------------------------------------------\n");
      if (*(int *)(param_1 + 0xb0) == 1) {
        uVar12 = *(uint *)(lVar10 + 0x94);
        uVar4 = *(undefined3 *)(lVar10 + 0x88);
        puVar8 = (undefined *)(lVar10 + 0x8b);
      }
      else {
        uVar12 = *(uint *)(lVar10 + 0x94);
        uVar12 = uVar12 >> 0x18 | (uVar12 & 0xff0000) >> 8 | (uVar12 & 0xff00) << 8 | uVar12 << 0x18
        ;
        puVar8 = (undefined *)(lVar10 + 0x88);
        uVar4 = CONCAT12(*(undefined *)(lVar10 + 0x89),
                         CONCAT11(*(undefined *)(lVar10 + 0x8a),*(undefined *)(lVar10 + 0x8b)));
      }
      tsk_fprintf(param_2,"Path Table Location: %u-%u\n",(ulong)uVar12,
                  (ulong)(CONCAT13(*puVar8,uVar4) / *(uint *)(param_1 + 0x58) + uVar12));
      tsk_fprintf(param_2,"Inode Range: %lu - %lu\n",*(undefined8 *)(param_1 + 0x28),
                  *(undefined8 *)(param_1 + 0x30));
      if (*(int *)(param_1 + 0xb0) == 1) {
        uVar4 = *(undefined3 *)(lVar10 + 0xa2);
        puVar8 = (undefined *)(lVar10 + 0xa5);
      }
      else {
        puVar8 = (undefined *)(lVar10 + 0xa2);
        uVar4 = CONCAT12(*(undefined *)(lVar10 + 0xa3),
                         CONCAT11(*(undefined *)(lVar10 + 0xa4),*(undefined *)(lVar10 + 0xa5)));
      }
      tsk_fprintf(param_2,"Root Directory Block: %lu\n",(ulong)CONCAT13(*puVar8,uVar4));
      tsk_fprintf(param_2,"\nCONTENT INFORMATION\n");
      tsk_fprintf(param_2,"--------------------------------------------\n");
      tsk_fprintf(param_2,"Sector Size: %d\n",0x800);
      uVar3 = (ulong)(*(int *)(param_1 + 0xb0) == 1);
      bVar1 = *(byte *)((lVar10 - uVar3) + 0x83);
      tsk_fprintf(param_2,"Block Size: %d\n",
                  (ulong)CONCAT11(*(undefined *)(lVar10 + 0x82 + uVar3),bVar1),(ulong)bVar1);
      if (*(int *)(param_1 + 0x60) != 0) {
        tsk_fprintf(param_2,"Raw CD pre-block size: %d\n");
        tsk_fprintf(param_2,"Raw CD post-block size: %d\n",(ulong)*(uint *)(param_1 + 100));
      }
      tsk_fprintf(param_2,"Total Sector Range: 0 - %d\n",
                  (ulong)((*(int *)(param_1 + 0x38) + -1) * (*(uint *)(param_1 + 0x58) >> 0xb)));
      tsk_fprintf(param_2,"Total Block Range: 0 - %d\n",(ulong)(*(int *)(param_1 + 0x38) - 1));
      lVar10 = *(long *)(lVar10 + 0x800);
    } while (lVar10 != 0);
  }
  lVar10 = *(long *)(param_1 + 0x1b8);
  if (lVar10 != 0) {
    uVar12 = 0;
    do {
      uVar12 = uVar12 + 1;
      tsk_fprintf(param_2,"\n=== SUPPLEMENTARY VOLUME DESCRIPTOR %d ===\n",(ulong)uVar12);
      tsk_fprintf(param_2,"FILE SYSTEM INFORMATION\n");
      tsk_fprintf(param_2,"--------------------------------------------\n");
      tsk_fprintf(param_2,"File System Type: ISO9660\n");
      tsk_fprintf(param_2,"Volume Name: %s\n",lVar10 + 0x28);
      uVar13 = (ulong)(*(int *)(param_1 + 0xb0) == 1);
      bVar1 = *(byte *)((lVar10 - uVar13) + 0x7b);
      tsk_fprintf(param_2,"Volume Set Size: %d\n",
                  (ulong)CONCAT11(*(undefined *)(lVar10 + 0x7a + uVar13),bVar1),(ulong)bVar1);
      uVar13 = (ulong)(*(int *)(param_1 + 0xb0) == 1);
      bVar1 = *(byte *)((lVar10 - uVar13) + 0x7f);
      tsk_fprintf(param_2,"Volume Set Sequence: %d\n",
                  (ulong)CONCAT11(*(undefined *)(lVar10 + 0x7e + uVar13),bVar1),(ulong)bVar1);
      if (*(char *)(lVar10 + 0x13e) == '_') {
        snprintf((char *)&local_b8,8,"In file\n");
      }
      else {
        snprintf((char *)&local_b8,0x80,"%s",lVar10 + 0x13e);
      }
      marker317._10168_8_ = "function_inlined: isprint";
      marker317._8536_8_ = "function_inlined: isspace";
      ppuVar7 = __ctype_b_loc();
      lVar5 = 0x7f;
      do {
        lVar9 = lVar5;
        if (lVar9 == 0) break;
        lVar5 = lVar9 + -1;
      } while (((*ppuVar7)[*(char *)((long)&local_b8 + lVar9)] & 0x6000) != 0x4000);
      *(undefined *)((long)&local_b8 + lVar9 + 1) = 0;
      tsk_fprintf(param_2,"Publisher: %s\n",&local_b8);
      marker317._8784_8_ = "function_inlined: memset";
      local_48 = LCPI9_0;
      uStack68 = DAT_00104ba4;
      uStack64 = DAT_00104ba8;
      uStack60 = DAT_00104bac;
      local_58 = LCPI9_0;
      uStack84 = DAT_00104ba4;
      uStack80 = DAT_00104ba8;
      uStack76 = DAT_00104bac;
      local_68 = LCPI9_0;
      uStack100 = DAT_00104ba4;
      uStack96 = DAT_00104ba8;
      uStack92 = DAT_00104bac;
      local_78 = LCPI9_0;
      uStack116 = DAT_00104ba4;
      uStack112 = DAT_00104ba8;
      uStack108 = DAT_00104bac;
      local_88 = LCPI9_0;
      uStack132 = DAT_00104ba4;
      uStack128 = DAT_00104ba8;
      uStack124 = DAT_00104bac;
      uStack152 = LCPI9_0;
      uStack148 = DAT_00104ba4;
      uStack144 = DAT_00104ba8;
      uStack140 = DAT_00104bac;
      local_a8 = LCPI9_0;
      uStack164 = DAT_00104ba4;
      uStack160 = DAT_00104ba8;
      uStack156 = DAT_00104bac;
      local_b8 = LCPI9_0;
      uStack180 = DAT_00104ba4;
      uStack176 = DAT_00104ba8;
      uStack172 = DAT_00104bac;
      if (*(char *)(lVar10 + 0x1be) == '_') {
        snprintf((char *)&local_b8,8,"In file\n");
      }
      else {
        snprintf((char *)&local_b8,0x80,"%s",lVar10 + 0x1be);
      }
      marker317._7712_8_ = "function_inlined: isprint";
      marker317._14712_8_ = "function_inlined: isspace";
      lVar5 = 0x7f;
      do {
        lVar9 = lVar5;
        if (lVar9 == 0) break;
        lVar5 = lVar9 + -1;
      } while (((*ppuVar7)[*(char *)((long)&local_b8 + lVar9)] & 0x6000) != 0x4000);
      *(undefined *)((long)&local_b8 + lVar9 + 1) = 0;
      tsk_fprintf(param_2,"Data Preparer: %s\n",&local_b8);
      marker317._10296_8_ = "function_inlined: memset";
      local_48 = LCPI9_0;
      uStack68 = DAT_00104ba4;
      uStack64 = DAT_00104ba8;
      uStack60 = DAT_00104bac;
      local_58 = LCPI9_0;
      uStack84 = DAT_00104ba4;
      uStack80 = DAT_00104ba8;
      uStack76 = DAT_00104bac;
      local_68 = LCPI9_0;
      uStack100 = DAT_00104ba4;
      uStack96 = DAT_00104ba8;
      uStack92 = DAT_00104bac;
      local_78 = LCPI9_0;
      uStack116 = DAT_00104ba4;
      uStack112 = DAT_00104ba8;
      uStack108 = DAT_00104bac;
      local_88 = LCPI9_0;
      uStack132 = DAT_00104ba4;
      uStack128 = DAT_00104ba8;
      uStack124 = DAT_00104bac;
      uStack152 = LCPI9_0;
      uStack148 = DAT_00104ba4;
      uStack144 = DAT_00104ba8;
      uStack140 = DAT_00104bac;
      local_a8 = LCPI9_0;
      uStack164 = DAT_00104ba4;
      uStack160 = DAT_00104ba8;
      uStack156 = DAT_00104bac;
      local_b8 = LCPI9_0;
      uStack180 = DAT_00104ba4;
      uStack176 = DAT_00104ba8;
      uStack172 = DAT_00104bac;
      if (*(char *)(lVar10 + 0x23e) == '_') {
        snprintf((char *)&local_b8,8,"In file\n");
      }
      else {
        snprintf((char *)&local_b8,0x80,"%s",lVar10 + 0x23e);
      }
      marker317._11448_8_ = "function_inlined: isprint";
      marker317._8264_8_ = "function_inlined: isspace";
      lVar5 = 0x7f;
      do {
        lVar9 = lVar5;
        if (lVar9 == 0) break;
        lVar5 = lVar9 + -1;
      } while (((*ppuVar7)[*(char *)((long)&local_b8 + lVar9)] & 0x6000) != 0x4000);
      *(undefined *)((long)&local_b8 + lVar9 + 1) = 0;
      tsk_fprintf(param_2,"Recording Application: %s\n",&local_b8);
      marker317._4896_8_ = "function_inlined: memset";
      local_48 = LCPI9_0;
      uStack68 = DAT_00104ba4;
      uStack64 = DAT_00104ba8;
      uStack60 = DAT_00104bac;
      local_58 = LCPI9_0;
      uStack84 = DAT_00104ba4;
      uStack80 = DAT_00104ba8;
      uStack76 = DAT_00104bac;
      local_68 = LCPI9_0;
      uStack100 = DAT_00104ba4;
      uStack96 = DAT_00104ba8;
      uStack92 = DAT_00104bac;
      local_78 = LCPI9_0;
      uStack116 = DAT_00104ba4;
      uStack112 = DAT_00104ba8;
      uStack108 = DAT_00104bac;
      local_88 = LCPI9_0;
      uStack132 = DAT_00104ba4;
      uStack128 = DAT_00104ba8;
      uStack124 = DAT_00104bac;
      uStack152 = LCPI9_0;
      uStack148 = DAT_00104ba4;
      uStack144 = DAT_00104ba8;
      uStack140 = DAT_00104bac;
      local_a8 = LCPI9_0;
      uStack164 = DAT_00104ba4;
      uStack160 = DAT_00104ba8;
      uStack156 = DAT_00104bac;
      local_b8 = LCPI9_0;
      uStack180 = DAT_00104ba4;
      uStack176 = DAT_00104ba8;
      uStack172 = DAT_00104bac;
      if (*(char *)(lVar10 + 0x2be) == '_') {
        snprintf((char *)&local_b8,8,"In file\n");
      }
      else {
        snprintf((char *)&local_b8,0x25,"%s\n",lVar10 + 0x2be);
      }
      marker317._11480_8_ = "function_inlined: isprint";
      marker317._5872_8_ = "function_inlined: isspace";
      lVar5 = 0x24;
      do {
        lVar9 = lVar5;
        if (lVar9 == 0) break;
        lVar5 = lVar9 + -1;
      } while (((*ppuVar7)[*(char *)((long)&local_b8 + lVar9)] & 0x6000) != 0x4000);
      *(undefined *)((long)&local_b8 + lVar9 + 1) = 0;
      tsk_fprintf(param_2,"Copyright: %s\n",&local_b8);
      marker317._14760_8_ = "function_inlined: memset";
      uStack152 = 0x20202020;
      uStack148 = uStack148 & 0xffffff00 | 0x20;
      local_a8 = LCPI9_0;
      uStack164 = DAT_00104ba4;
      uStack160 = DAT_00104ba8;
      uStack156 = DAT_00104bac;
      local_b8 = LCPI9_0;
      uStack180 = DAT_00104ba4;
      uStack176 = DAT_00104ba8;
      uStack172 = DAT_00104bac;
      tsk_fprintf(param_2,"\nMETADATA INFORMATION\n");
      tsk_fprintf(param_2,"--------------------------------------------\n");
      if (*(int *)(param_1 + 0xb0) == 1) {
        uVar11 = *(uint *)(lVar10 + 0x94);
        uVar4 = *(undefined3 *)(lVar10 + 0x88);
        puVar8 = (undefined *)(lVar10 + 0x8b);
      }
      else {
        uVar11 = *(uint *)(lVar10 + 0x94);
        uVar11 = uVar11 >> 0x18 | (uVar11 & 0xff0000) >> 8 | (uVar11 & 0xff00) << 8 | uVar11 << 0x18
        ;
        puVar8 = (undefined *)(lVar10 + 0x88);
        uVar4 = CONCAT12(*(undefined *)(lVar10 + 0x89),
                         CONCAT11(*(undefined *)(lVar10 + 0x8a),*(undefined *)(lVar10 + 0x8b)));
      }
      tsk_fprintf(param_2,"Path Table Location: %u-%u\n",(ulong)uVar11,
                  (ulong)(CONCAT13(*puVar8,uVar4) / *(uint *)(param_1 + 0x58) + uVar11));
      if (*(int *)(param_1 + 0xb0) == 1) {
        uVar4 = *(undefined3 *)(lVar10 + 0xa2);
        puVar8 = (undefined *)(lVar10 + 0xa5);
      }
      else {
        puVar8 = (undefined *)(lVar10 + 0xa2);
        uVar4 = CONCAT12(*(undefined *)(lVar10 + 0xa3),
                         CONCAT11(*(undefined *)(lVar10 + 0xa4),*(undefined *)(lVar10 + 0xa5)));
      }
      tsk_fprintf(param_2,"Root Directory Block: %lu\n",(ulong)CONCAT13(*puVar8,uVar4));
      __s1 = (char *)(lVar10 + 0x58);
      iVar6 = strncmp(__s1,"%/E",3);
      if (iVar6 == 0) {
        tsk_fprintf(param_2,"Joliet Name Encoding: UCS-2 Level 3\n");
      }
      iVar6 = strncmp(__s1,"%/C",3);
      if (iVar6 == 0) {
        tsk_fprintf(param_2,"Joliet Name Encoding: UCS-2 Level 2\n");
      }
      iVar6 = strncmp(__s1,"%/@",3);
      if (iVar6 == 0) {
        tsk_fprintf(param_2,"Joliet Name Encoding: UCS-2 Level 1\n");
        cVar2 = *(char *)(param_1 + 0x1c8);
      }
      else {
        cVar2 = *(char *)(param_1 + 0x1c8);
      }
      if (cVar2 != '\0') {
        tsk_fprintf(param_2,"RockRidge Extensions present\n");
      }
      tsk_fprintf(param_2,"\nCONTENT INFORMATION\n");
      tsk_fprintf(param_2,"--------------------------------------------\n");
      tsk_fprintf(param_2,"Sector Size: %d\n",0x800);
      tsk_fprintf(param_2,"Block Size: %d\n",(ulong)*(uint *)(param_1 + 0x58));
      tsk_fprintf(param_2,"Total Sector Range: 0 - %d\n",
                  (ulong)((*(int *)(param_1 + 0x38) + -1) * (*(uint *)(param_1 + 0x58) >> 0xb)));
      tsk_fprintf(param_2,"Total Block Range: 0 - %d\n",(ulong)(*(int *)(param_1 + 0x38) - 1));
      lVar10 = *(long *)(lVar10 + 0x800);
    } while (lVar10 != 0);
  }
  return 0;
}


undefined8 iso9660_fscheck(void)

{
  undefined8 uVar1;
  
  tsk_error_reset();
  tsk_error_set_errno(0x8000002);
  uVar1 = tsk_error_set_errstr("fscheck not implemented for iso9660 yet");
  return CONCAT71((int7)((ulong)uVar1 >> 8),1);
}


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong iso9660_istat(undefined4 *param_1,uint param_2,FILE *param_3,long param_4,undefined8 param_5,
                   int param_6)

{
  undefined4 *__src;
  undefined3 uVar1;
  uint3 uVar2;
  ushort uVar3;
  char cVar4;
  long lVar5;
  void *__dest;
  void *__ptr;
  ulong uVar6;
  uint3 *puVar7;
  undefined8 uVar8;
  undefined *puVar9;
  long lVar10;
  ulong extraout_RDX;
  ulong extraout_RDX_00;
  ulong extraout_RDX_01;
  int iVar11;
  uint uVar12;
  char *pcVar13;
  undefined8 unaff_R13;
  long lVar14;
  undefined4 local_e8;
  undefined4 uStack228;
  undefined4 uStack224;
  undefined4 uStack220;
  undefined4 local_d8;
  undefined4 uStack212;
  undefined4 uStack208;
  undefined4 uStack204;
  undefined local_c8;
  undefined local_b8 [136];
  
  tsk_error_reset();
  lVar5 = tsk_fs_file_open_meta(param_1,0,param_4);
  uVar6 = CONCAT71((int7)((ulong)unaff_R13 >> 8),1);
  if (lVar5 != 0) {
    tsk_fprintf(param_3,"Entry: %lu\n",param_4);
    __dest = (void *)tsk_malloc(0x158);
    if (__dest == (void *)0x0) {
      *param_1 = 0;
      iso9660_close(param_1);
    }
    else {
      __src = *(undefined4 **)(param_1 + 0x70);
      while (__src != (undefined4 *)0x0) {
        if (*(long *)(__src + 0x5a) == param_4) {
          memcpy(__dest,__src,0x158);
          local_e8 = *__src;
          uStack228 = __src[1];
          uStack224 = __src[2];
          uStack220 = __src[3];
          local_d8 = __src[4];
          uStack212 = __src[5];
          uStack208 = __src[6];
          uStack204 = __src[7];
          local_c8 = *(undefined *)(__src + 8);
          tsk_fprintf(param_3,"Type: ");
          uVar12 = uStack208;
          if ((uStack208 & 0x200) == 0) {
            pcVar13 = "File\n";
          }
          else {
            pcVar13 = "Directory\n";
          }
          tsk_fprintf(param_3,pcVar13);
          tsk_fprintf(param_3,"Links: %d\n",(ulong)*(uint *)(*(long *)(lVar5 + 0x10) + 0x18));
          if (uStack208._3_1_ != '\0') {
            tsk_fprintf(param_3,"Interleave Gap Size: %d\n");
            tsk_fprintf(param_3,"Interleave File Unit Size: %d\n",(ulong)uStack208._2_1_);
          }
          tsk_fprintf(param_3,"Flags: ");
          if ((uVar12 & 0x100) != 0) {
            tsk_fprintf(param_3,"Hidden, ");
          }
          if ((uVar12 & 0x400) != 0) {
            tsk_fprintf(param_3,"Associated, ");
          }
          if ((uVar12 & 0x800) != 0) {
            tsk_fprintf(param_3,"Record Format, ");
          }
          if ((uVar12 & 0x1000) != 0) {
            tsk_fprintf(param_3,"Protected,  ");
          }
          if ((uVar12 & 0x2000) != 0) {
            tsk_fprintf(param_3,"Reserved1, ");
          }
          if ((uVar12 & 0x4000) != 0) {
            tsk_fprintf(param_3,"Reserved2, ");
          }
          if (uStack208._1_1_ < '\0') {
            tsk_fprintf(param_3,"Non-final multi-extent entry");
          }
          marker317._6152_8_ = "function_inlined: putchar";
          _IO_putc(10,stdout);
          tsk_fprintf(param_3,"Name: %s\n",(long)__dest + 0x30);
          if (param_1[0x2c] == 1) {
            uVar1 = *(undefined3 *)((long)__dest + 0xe);
            puVar9 = (undefined *)((long)__dest + 0x11);
          }
          else {
            puVar9 = (undefined *)((long)__dest + 0xe);
            uVar1 = CONCAT12(*(undefined *)((long)__dest + 0xf),
                             CONCAT11(*(undefined *)((long)__dest + 0x10),
                                      *(undefined *)((long)__dest + 0x11)));
          }
          tsk_fprintf(param_3,"Size: %u\n",(ulong)CONCAT13(*puVar9,uVar1));
          if (*(long *)((long)__dest + 0x28) == 0) {
            if (*(long *)((long)__dest + 0x148) == 0) {
              tsk_fprintf(param_3,"Owner-ID: 0\n");
              tsk_fprintf(param_3,"Group-ID: 0\n");
              goto LAB_00102aca;
            }
            __ptr = (void *)tsk_malloc(*(undefined8 *)((long)__dest + 0x150));
            if (__ptr != (void *)0x0) {
              marker317._1904_8_ = "function_inlined: fprintf";
              fwrite("\nRock Ridge Extension Data\n",0x1b,1,param_3);
              uVar6 = tsk_fs_read(param_1,*(undefined8 *)((long)__dest + 0x148),__ptr,
                                  *(undefined8 *)((long)__dest + 0x150));
              if (uVar6 == *(ulong *)((long)__dest + 0x150)) {
                parse_susp(param_1,__ptr,uVar6 & 0xffffffff,param_3);
              }
              else {
                marker317._11672_8_ = "function_inlined: fprintf";
                fwrite("Error reading Rock Ridge Location\n",0x22,1,param_3);
                if (_tsk_verbose != 0) {
                  fwrite("istat: error reading rock ridge entry\n",0x26,1,stderr);
                  tsk_error_print(stderr);
                }
                tsk_error_reset();
              }
              free(__ptr);
              goto joined_r0x00102c8b;
            }
            if (_tsk_verbose != 0) {
              fwrite("istat: error allocating memory to process rock ridge entry\n",0x3b,1,stderr);
            }
            tsk_error_reset();
            if (param_6 != 0) goto LAB_00102afd;
LAB_00102c91:
            pcVar13 = "\nFile Times:\n";
          }
          else {
            tsk_fprintf(param_3,"\nEXTENDED ATTRIBUTE INFO\n");
            puVar7 = *(uint3 **)((long)__dest + 0x28);
            if (param_1[0x2c] == 1) {
              uVar2 = *puVar7;
              puVar7 = puVar7 + 1;
            }
            else {
              uVar2 = CONCAT12(*(undefined *)((long)puVar7 + 1),
                               CONCAT11(*(undefined *)((long)puVar7 + 2),*(undefined *)(puVar7 + 1))
                              );
            }
            tsk_fprintf(param_3,"Owner-ID: %u\n",(ulong)CONCAT13(*(undefined *)puVar7,uVar2),
                        (ulong)uVar2);
            lVar14 = *(long *)((long)__dest + 0x28);
            if (param_1[0x2c] == 1) {
              uVar2 = *(uint3 *)(lVar14 + 4);
              puVar9 = (undefined *)(lVar14 + 7);
            }
            else {
              puVar9 = (undefined *)(lVar14 + 4);
              uVar2 = CONCAT12(*(undefined *)(lVar14 + 5),
                               CONCAT11(*(undefined *)(lVar14 + 6),*(undefined *)(lVar14 + 7)));
            }
            tsk_fprintf(param_3,"Group-ID: %u\n",(ulong)CONCAT13(*puVar9,uVar2),(ulong)uVar2);
LAB_00102aca:
            uVar8 = make_unix_perm(param_1,&local_e8,__dest,local_b8);
            tsk_fprintf(param_3,"Mode: %s\n",uVar8,uVar8);
joined_r0x00102c8b:
            if (param_6 == 0) goto LAB_00102c91;
LAB_00102afd:
            lVar10 = 0;
            tsk_fprintf(param_3,"\nAdjusted File Times:\n");
            lVar14 = *(long *)(lVar5 + 0x10);
            if (*(long *)(lVar14 + 0x30) != 0) {
              lVar10 = *(long *)(lVar14 + 0x30) - (long)param_6;
              *(long *)(lVar14 + 0x30) = lVar10;
            }
            if (*(long *)(lVar14 + 0x40) != 0) {
              *(long *)(lVar14 + 0x40) = *(long *)(lVar14 + 0x40) - (long)param_6;
            }
            if (*(long *)(lVar14 + 0x60) != 0) {
              *(long *)(lVar14 + 0x60) = *(long *)(lVar14 + 0x60) - (long)param_6;
            }
            uVar8 = tsk_fs_time_to_str(lVar10,local_b8);
            tsk_fprintf(param_3,"Written:\t%s\n",uVar8,uVar8);
            uVar8 = tsk_fs_time_to_str(*(undefined8 *)(*(long *)(lVar5 + 0x10) + 0x40),local_b8);
            tsk_fprintf(param_3,"Accessed:\t%s\n",uVar8,uVar8);
            uVar8 = tsk_fs_time_to_str(*(undefined8 *)(*(long *)(lVar5 + 0x10) + 0x60),local_b8);
            tsk_fprintf(param_3,"Created:\t%s\n",uVar8,uVar8);
            lVar14 = *(long *)(lVar5 + 0x10);
            if (*(long *)(lVar14 + 0x30) != 0) {
              *(long *)(lVar14 + 0x30) = *(long *)(lVar14 + 0x30) + (long)param_6;
            }
            if (*(long *)(lVar14 + 0x40) != 0) {
              *(long *)(lVar14 + 0x40) = *(long *)(lVar14 + 0x40) + (long)param_6;
            }
            if (*(long *)(lVar14 + 0x60) != 0) {
              *(long *)(lVar14 + 0x60) = *(long *)(lVar14 + 0x60) + (long)param_6;
            }
            pcVar13 = "\nOriginal File Times:\n";
          }
          tsk_fprintf(param_3,pcVar13);
          uVar8 = tsk_fs_time_to_str(*(undefined8 *)(*(long *)(lVar5 + 0x10) + 0x60),local_b8);
          tsk_fprintf(param_3,"Created:\t%s\n",uVar8,uVar8);
          uVar8 = tsk_fs_time_to_str(*(undefined8 *)(*(long *)(lVar5 + 0x10) + 0x30),local_b8);
          tsk_fprintf(param_3,"File Modified:\t%s\n",uVar8,uVar8);
          uVar8 = tsk_fs_time_to_str(*(undefined8 *)(*(long *)(lVar5 + 0x10) + 0x40),local_b8);
          tsk_fprintf(param_3,"Accessed:\t%s\n",uVar8,uVar8);
          tsk_fprintf(param_3,"\nSectors:\n");
          if ((param_2 & 1) == 0) {
            if (param_1[0x2c] == 1) {
              uVar1 = *(undefined3 *)((long)__dest + 6);
              puVar9 = (undefined *)((long)__dest + 9);
              uVar6 = extraout_RDX;
            }
            else {
              puVar9 = (undefined *)((long)__dest + 6);
              uVar3 = CONCAT11(*(undefined *)((long)__dest + 8),*(undefined *)((long)__dest + 9));
              uVar6 = (ulong)uVar3;
              uVar1 = CONCAT12(*(undefined *)((long)__dest + 7),uVar3);
            }
            lVar14 = *(long *)(*(long *)(lVar5 + 0x10) + 0x20);
            if (0 < lVar14) {
              uVar12 = CONCAT13(*puVar9,uVar1);
              iVar11 = 0;
              do {
                tsk_fprintf(param_3,&DAT_00105e07,(ulong)uVar12);
                lVar14 = lVar14 - (ulong)(uint)param_1[0x16];
                iVar11 = iVar11 + 1;
                uVar6 = extraout_RDX_00;
                if (iVar11 == 8) {
                  iVar11 = 0;
                  tsk_fprintf(param_3,&DAT_00105e0b);
                  uVar6 = extraout_RDX_01;
                }
                uVar12 = uVar12 + 1;
              } while (0 < lVar14);
            }
            tsk_fprintf(param_3,&DAT_00105e0b,uVar6);
          }
          else {
            lVar14 = tsk_fs_file_attr_get_type(lVar5,1,0,0);
            if (((lVar14 != 0) && ((*(byte *)(lVar14 + 0x10) & 2) != 0)) &&
               (cVar4 = tsk_fs_attr_print(lVar14,param_3), cVar4 != '\0')) {
              tsk_fprintf(param_3,"\nError creating run lists\n");
              tsk_error_print(param_3);
              tsk_error_reset();
            }
          }
          tsk_fs_file_close(lVar5);
          free(__dest);
          uVar6 = 0;
          goto LAB_00102e56;
        }
        __src = *(undefined4 **)(__src + 0x5e);
      }
      tsk_error_set_errstr2("iso9660_istat");
      tsk_fs_file_close(lVar5);
      free(__dest);
    }
  }
LAB_00102e56:
  return uVar6 & 0xffffffff;
}


undefined8 iso9660_jblk_walk(void)

{
  undefined8 uVar1;
  
  tsk_error_reset();
  tsk_error_set_errno(0x8000002);
  uVar1 = tsk_error_set_errstr("ISO9660 does not have a journal");
  return CONCAT71((int7)((ulong)uVar1 >> 8),1);
}


undefined8 iso9660_jentry_walk(void)

{
  undefined8 uVar1;
  
  tsk_error_reset();
  tsk_error_set_errno(0x8000002);
  uVar1 = tsk_error_set_errstr("ISO9660 does not have a journal");
  return CONCAT71((int7)((ulong)uVar1 >> 8),1);
}


undefined8 iso9660_jopen(void)

{
  undefined8 uVar1;
  
  tsk_error_reset();
  tsk_error_set_errno(0x8000002);
  uVar1 = tsk_error_set_errstr("ISO9660 does not have a journal");
  return CONCAT71((int7)((ulong)uVar1 >> 8),1);
}


/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong iso9660_load_inodes_dir
                (long param_1,long param_2,uint param_3,int param_4,char *param_5,char param_6)

{
  ushort *puVar1;
  undefined auVar2 [16];
  byte bVar3;
  byte bVar4;
  byte bVar5;
  undefined uVar6;
  undefined uVar7;
  undefined3 uVar8;
  byte bVar9;
  byte *pbVar10;
  long lVar11;
  undefined uVar12;
  undefined uVar13;
  undefined uVar14;
  uint uVar15;
  uint uVar16;
  long lVar17;
  undefined *__ptr;
  char *pcVar18;
  long lVar19;
  size_t __n;
  void *__ptr_00;
  undefined8 uVar20;
  byte bVar21;
  uint uVar22;
  ulong uVar23;
  ulong uVar24;
  byte *pbVar25;
  int iVar26;
  ulong uVar27;
  long lVar28;
  long lVar29;
  int iVar30;
  uint uVar31;
  char *__s;
  undefined8 uVar32;
  undefined auVar33 [16];
  undefined auVar34 [16];
  undefined auVar35 [16];
  undefined auVar36 [16];
  ulong local_888;
  uint local_874;
  uint local_870;
  byte *local_840;
  byte local_838 [6];
  undefined auStack2098 [8];
  byte bStack2090;
  byte abStack2089 [10];
  byte abStack2079 [7];
  byte local_818 [17];
  undefined auStack2055 [16];
  undefined auStack2039 [16];
  undefined local_7e7 [1975];
  
  local_888 = (ulong)param_3;
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"iso9660_load_inodes_dir: offs: %ld count: %d ctype: %d fn: %s\n",param_2,
                local_888);
  }
  local_870 = 1;
  local_874 = 0;
  do {
    lVar17 = tsk_fs_read(param_1,param_2,local_838);
    if (lVar17 != 0x800) {
      if (-1 < lVar17) {
        tsk_error_reset();
        tsk_error_set_errno(0x8000004);
      }
      tsk_error_set_errstr2("iso_get_dentries");
      return 0xffffffff;
    }
    uVar31 = 0;
    do {
      lVar17 = (long)(int)uVar31;
      bVar21 = local_838[lVar17];
      if (bVar21 == 0) {
        uVar15 = uVar31 + 2;
        goto LAB_00103860;
      }
      if (bVar21 < 0x21) {
        if (_tsk_verbose != 0) {
          pcVar18 = "iso9660_load_inodes_dir: entry length is shorter than dentry, bailing\n";
LAB_001038a7:
          tsk_fprintf(stderr,pcVar18);
        }
        break;
      }
      uVar15 = bVar21 + uVar31;
      if (0x800 < (int)uVar15) {
        if (_tsk_verbose != 0) {
          pcVar18 = "iso9660_load_inodes_dir: entry is longer than sector, bailing\n";
          goto LAB_001038a7;
        }
        break;
      }
      pbVar25 = local_838 + lVar17;
      if ((param_6 != '\0') || ((abStack2079[lVar17] & 2) == 0)) {
        __ptr = (undefined *)tsk_malloc();
        if (__ptr == (undefined *)0x0) {
          return 0xffffffff;
        }
        if ((uVar31 | local_874) != 0) {
          if (param_4 == 0) {
            __n = (size_t)local_818[lVar17];
            if ((ulong)*pbVar25 < __n + 0x21) {
              if (_tsk_verbose != 0) {
                pcVar18 = "iso9660_load_inodes_dir: ASCII name length is too large, bailing\n";
                goto LAB_001038a7;
              }
              break;
            }
            if (0x7f < local_818[lVar17]) {
              __n = 0x80;
            }
            memcpy(__ptr + 0x30,local_818 + lVar17 + 1,__n);
            __ptr[__n + 0x30] = 0;
          }
          else {
            if (param_4 != 1) {
              tsk_error_reset();
              tsk_error_set_errno(0x8000006);
              tsk_error_set_errstr("Invalid ctype in iso9660_load_inodes_dir");
              return 0xffffffff;
            }
            bVar21 = local_818[lVar17];
            if ((ulong)*pbVar25 < (ulong)bVar21 + 0x21) {
              if (_tsk_verbose != 0) {
                pcVar18 = "iso9660_load_inodes_dir: UTF-16 name length is too large, bailing\n";
                goto LAB_001038a7;
              }
              break;
            }
            local_840 = local_818 + lVar17 + 1;
            uVar15 = *(uint *)(param_1 + 0xb0);
            if ((uVar15 & 1) != 0) {
              bVar5 = bVar21 >> 1;
              if (bVar5 != 0) {
                if (bVar21 < 0x20) {
                  uVar24 = 0;
                }
                else {
                  uVar24 = (ulong)((uint)bVar5 & 0xfffffff0);
                  uVar27 = (uVar24 - 0x10 >> 4) + 1;
                  if (uVar24 - 0x10 == 0) {
                    lVar19 = 0;
                  }
                  else {
                    lVar29 = ((uint)uVar27 & 1) - uVar27;
                    lVar19 = 0;
                    do {
                    /* WARNING: Load size is inaccurate */
                      auVar33 = *(undefined *)(local_818 + lVar19 * 2 + lVar17 + 1);
                    /* WARNING: Load size is inaccurate */
                      auVar34 = *(undefined *)(auStack2055 + lVar19 * 2 + lVar17);
                    /* WARNING: Load size is inaccurate */
                      auVar35 = *(undefined *)(auStack2039 + lVar19 * 2 + lVar17);
                    /* WARNING: Load size is inaccurate */
                      auVar2 = *(undefined *)(local_7e7 + lVar17 + lVar19 * 2);
                      auVar36 = ZEXT1516(CONCAT114(SUB161(auVar33 >> 0x78,0),
                                                   ZEXT1314(CONCAT112(SUB161(auVar33 >> 0x70,0),
                                                                      ZEXT1112(CONCAT110(SUB161(
                                                  auVar33 >> 0x68,0),
                                                  (unkuint10)
                                                  CONCAT18(SUB161(auVar33 >> 0x60,0),
                                                           (ulong)CONCAT16(SUB161(auVar33 >> 0x58,0)
                                                                           ,(uint6)CONCAT14(SUB161(
                                                  auVar33 >> 0x50,0),
                                                  (uint)CONCAT12(SUB161(auVar33 >> 0x48,0),
                                                                 (ushort)SUB161(auVar33 >> 0x40,0)))
                                                  ))))))));
                      auVar36 = pshuflw(auVar36,auVar36,0xb1);
                      auVar36 = pshufhw(auVar36,auVar36,0xb1);
                      auVar33 = (auVar33 & (undefined  [16])0xffff |
                                CONCAT133((SUB1613(auVar33 >> 0x18,0) &
                                           SUB1613((undefined  [16])0xffffffff >> 0x18,0) |
                                          SUB1613(CONCAT115((SUB1611(auVar33 >> 0x28,0) &
                                                             SUB1611((undefined  [16])0xffffffffffff
                                                                     >> 0x28,0) |
                                                            SUB1611(CONCAT97((SUB169(auVar33 >> 0x38
                                                                                     ,0) &
                                                                              SUB169((undefined  [16
                                                  ])0xffffffffffffffff >> 0x38,0) |
                                                  SUB169(((undefined  [16])0x0 << 0x40) >> 0x38,0))
                                                  & SUB169((undefined  [16])0xffffffffffffffff >>
                                                           0x38,0),
                                                  SUB167(auVar33,0) & 0xffffffffffff |
                                                  (SUB167(auVar33,0) >> 0x18) << 0x30) >> 0x28,0) &
                                                  SUB1611((undefined  [16])0xffff000000000000 >>
                                                          0x28,0)) &
                                                  SUB1611((undefined  [16])0xffff00ffffffffff >>
                                                          0x28,0),
                                                  SUB165(auVar33,0) & 0xffffffff |
                                                  (SUB165(auVar33,0) >> 0x10) << 0x20) >> 0x18,0) &
                                          SUB1613((undefined  [16])0xffffffff00000000 >> 0x18,0)) &
                                          SUB1613((undefined  [16])0xffffffff00ffffff >> 0x18,0),
                                          (SUB163(auVar33,0) >> 8) << 0x10) &
                                (undefined  [16])0xffffffffffff0000) &
                                (undefined  [16])0xffffffffffff00ff;
                      auVar33 = pshuflw(auVar33,auVar33,0xb1);
                      auVar33 = pshufhw(auVar33,auVar33,0xb1);
                      auVar33 = packuswb(auVar33,auVar36);
                      auVar36 = ZEXT1516(CONCAT114(SUB161(auVar34 >> 0x78,0),
                                                   ZEXT1314(CONCAT112(SUB161(auVar34 >> 0x70,0),
                                                                      ZEXT1112(CONCAT110(SUB161(
                                                  auVar34 >> 0x68,0),
                                                  (unkuint10)
                                                  CONCAT18(SUB161(auVar34 >> 0x60,0),
                                                           (ulong)CONCAT16(SUB161(auVar34 >> 0x58,0)
                                                                           ,(uint6)CONCAT14(SUB161(
                                                  auVar34 >> 0x50,0),
                                                  (uint)CONCAT12(SUB161(auVar34 >> 0x48,0),
                                                                 (ushort)SUB161(auVar34 >> 0x40,0)))
                                                  ))))))));
                      auVar36 = pshuflw(auVar36,auVar36,0xb1);
                      auVar36 = pshufhw(auVar36,auVar36,0xb1);
                      auVar34 = (auVar34 & (undefined  [16])0xffff |
                                CONCAT133((SUB1613(auVar34 >> 0x18,0) &
                                           SUB1613((undefined  [16])0xffffffff >> 0x18,0) |
                                          SUB1613(CONCAT115((SUB1611(auVar34 >> 0x28,0) &
                                                             SUB1611((undefined  [16])0xffffffffffff
                                                                     >> 0x28,0) |
                                                            SUB1611(CONCAT97((unkuint9)
                                                                             (SUB168(auVar34,0) >>
                                                                             0x38) & 0xffff &
                                                                             SUB169((undefined  [16]
                                                                                    )
                                                  0xffffffffffffffff >> 0x38,0),
                                                  SUB167(auVar34,0) & 0xffffffffffff |
                                                  (SUB167(auVar34,0) >> 0x18) << 0x30) >> 0x28,0) &
                                                  SUB1611((undefined  [16])0xffff000000000000 >>
                                                          0x28,0)) &
                                                  SUB1611((undefined  [16])0xffff00ffffffffff >>
                                                          0x28,0),
                                                  SUB165(auVar34,0) & 0xffffffff |
                                                  (SUB165(auVar34,0) >> 0x10) << 0x20) >> 0x18,0) &
                                          SUB1613((undefined  [16])0xffffffff00000000 >> 0x18,0)) &
                                          SUB1613((undefined  [16])0xffffffff00ffffff >> 0x18,0),
                                          (SUB163(auVar34,0) >> 8) << 0x10) &
                                (undefined  [16])0xffffffffffff0000) &
                                (undefined  [16])0xffffffffffff00ff;
                      auVar34 = pshuflw(auVar34,auVar34,0xb1);
                      auVar34 = pshufhw(auVar34,auVar34,0xb1);
                      auVar34 = packuswb(auVar34,auVar36);
                    /* WARNING: Store size is inaccurate */
                      *(undefined *)(local_818 + lVar19 * 2 + lVar17 + 1) = auVar33;
                    /* WARNING: Store size is inaccurate */
                      *(undefined *)(auStack2055 + lVar19 * 2 + lVar17) = auVar34;
                      auVar33 = ZEXT1516(CONCAT114(SUB161(auVar35 >> 0x78,0),
                                                   ZEXT1314(CONCAT112(SUB161(auVar35 >> 0x70,0),
                                                                      ZEXT1112(CONCAT110(SUB161(
                                                  auVar35 >> 0x68,0),
                                                  (unkuint10)
                                                  CONCAT18(SUB161(auVar35 >> 0x60,0),
                                                           (ulong)CONCAT16(SUB161(auVar35 >> 0x58,0)
                                                                           ,(uint6)CONCAT14(SUB161(
                                                  auVar35 >> 0x50,0),
                                                  (uint)CONCAT12(SUB161(auVar35 >> 0x48,0),
                                                                 (ushort)SUB161(auVar35 >> 0x40,0)))
                                                  ))))))));
                      auVar33 = pshuflw(auVar33,auVar33,0xb1);
                      auVar33 = pshufhw(auVar33,auVar33,0xb1);
                      auVar34 = pshuflw(auVar34,(auVar35 & (undefined  [16])0xffff |
                                                CONCAT133((SUB1613(auVar35 >> 0x18,0) &
                                                           SUB1613((undefined  [16])0xffffffff >>
                                                                   0x18,0) |
                                                          SUB1613(CONCAT115((SUB1611(auVar35 >> 0x28
                                                                                     ,0) &
                                                                             SUB1611((undefined  [16
                                                  ])0xffffffffffff >> 0x28,0) |
                                                  SUB1611(CONCAT97((unkuint9)
                                                                   (SUB168(auVar35,0) >> 0x38) &
                                                                   0xffff & SUB169((undefined  [16])
                                                                                                                                                                      
                                                  0xffffffffffffffff >> 0x38,0),
                                                  SUB167(auVar35,0) & 0xffffffffffff |
                                                  (SUB167(auVar35,0) >> 0x18) << 0x30) >> 0x28,0) &
                                                  SUB1611((undefined  [16])0xffff000000000000 >>
                                                          0x28,0)) &
                                                  SUB1611((undefined  [16])0xffff00ffffffffff >>
                                                          0x28,0),
                                                  SUB165(auVar35,0) & 0xffffffff |
                                                  (SUB165(auVar35,0) >> 0x10) << 0x20) >> 0x18,0) &
                                                  SUB1613((undefined  [16])0xffffffff00000000 >>
                                                          0x18,0)) &
                                                  SUB1613((undefined  [16])0xffffffff00ffffff >>
                                                          0x18,0),(SUB163(auVar35,0) >> 8) << 0x10)
                                                & (undefined  [16])0xffffffffffff0000) &
                                                (undefined  [16])0xffffffffffff00ff,0xb1);
                      auVar34 = pshufhw(auVar34,auVar34,0xb1);
                      auVar35 = packuswb(auVar34,auVar33);
                      auVar33 = ZEXT1516(CONCAT114(SUB161(auVar2 >> 0x78,0),
                                                   ZEXT1314(CONCAT112(SUB161(auVar2 >> 0x70,0),
                                                                      ZEXT1112(CONCAT110(SUB161(
                                                  auVar2 >> 0x68,0),
                                                  (unkuint10)
                                                  CONCAT18(SUB161(auVar2 >> 0x60,0),
                                                           (ulong)CONCAT16(SUB161(auVar2 >> 0x58,0),
                                                                           (uint6)CONCAT14(SUB161(
                                                  auVar2 >> 0x50,0),
                                                  (uint)CONCAT12(SUB161(auVar2 >> 0x48,0),
                                                                 (ushort)SUB161(auVar2 >> 0x40,0))))
                                                  )))))));
                      auVar33 = pshuflw(auVar33,auVar33,0xb1);
                      auVar34 = pshufhw(auVar33,auVar33,0xb1);
                      auVar33 = (auVar2 & (undefined  [16])0xffff |
                                CONCAT133((SUB1613(auVar2 >> 0x18,0) &
                                           SUB1613((undefined  [16])0xffffffff >> 0x18,0) |
                                          SUB1613(CONCAT115((SUB1611(auVar2 >> 0x28,0) &
                                                             SUB1611((undefined  [16])0xffffffffffff
                                                                     >> 0x28,0) |
                                                            SUB1611(CONCAT97((unkuint9)
                                                                             (SUB168(auVar2,0) >>
                                                                             0x38) & 0xffff &
                                                                             SUB169((undefined  [16]
                                                                                    )
                                                  0xffffffffffffffff >> 0x38,0),
                                                  SUB167(auVar2,0) & 0xffffffffffff |
                                                  (SUB167(auVar2,0) >> 0x18) << 0x30) >> 0x28,0) &
                                                  SUB1611((undefined  [16])0xffff000000000000 >>
                                                          0x28,0)) &
                                                  SUB1611((undefined  [16])0xffff00ffffffffff >>
                                                          0x28,0),
                                                  SUB165(auVar2,0) & 0xffffffff |
                                                  (SUB165(auVar2,0) >> 0x10) << 0x20) >> 0x18,0) &
                                          SUB1613((undefined  [16])0xffffffff00000000 >> 0x18,0)) &
                                          SUB1613((undefined  [16])0xffffffff00ffffff >> 0x18,0),
                                          (SUB163(auVar2,0) >> 8) << 0x10) &
                                (undefined  [16])0xffffffffffff0000) &
                                (undefined  [16])0xffffffffffff00ff;
                      auVar33 = pshuflw(auVar33,auVar33,0xb1);
                      auVar33 = pshufhw(auVar33,auVar33,0xb1);
                      auVar33 = packuswb(auVar33,auVar34);
                    /* WARNING: Store size is inaccurate */
                      *(undefined *)(auStack2039 + lVar19 * 2 + lVar17) = auVar35;
                    /* WARNING: Store size is inaccurate */
                      *(undefined *)(local_7e7 + lVar17 + lVar19 * 2) = auVar33;
                      lVar19 = lVar19 + 0x20;
                      lVar29 = lVar29 + 2;
                    } while (lVar29 != 0);
                  }
                  if ((uVar27 & 1) != 0) {
                    /* WARNING: Load size is inaccurate */
                    auVar33 = *(undefined *)(local_840 + lVar19 * 2);
                    /* WARNING: Load size is inaccurate */
                    auVar34 = *(undefined *)(auStack2055 + lVar19 * 2 + lVar17);
                    auVar35 = ZEXT1516(CONCAT114(SUB161(auVar33 >> 0x78,0),
                                                 ZEXT1314(CONCAT112(SUB161(auVar33 >> 0x70,0),
                                                                    ZEXT1112(CONCAT110(SUB161(
                                                  auVar33 >> 0x68,0),
                                                  (unkuint10)
                                                  CONCAT18(SUB161(auVar33 >> 0x60,0),
                                                           (ulong)CONCAT16(SUB161(auVar33 >> 0x58,0)
                                                                           ,(uint6)CONCAT14(SUB161(
                                                  auVar33 >> 0x50,0),
                                                  (uint)CONCAT12(SUB161(auVar33 >> 0x48,0),
                                                                 (ushort)SUB161(auVar33 >> 0x40,0)))
                                                  ))))))));
                    auVar35 = pshuflw(auVar35,auVar35,0xb1);
                    auVar35 = pshufhw(auVar35,auVar35,0xb1);
                    auVar33 = (auVar33 & (undefined  [16])0xffff |
                              CONCAT133((SUB1613(auVar33 >> 0x18,0) &
                                         SUB1613((undefined  [16])0xffffffff >> 0x18,0) |
                                        SUB1613(CONCAT115((SUB1611(auVar33 >> 0x28,0) &
                                                           SUB1611((undefined  [16])0xffffffffffff
                                                                   >> 0x28,0) |
                                                          SUB1611(CONCAT97((SUB169(auVar33 >> 0x38,0
                                                                                  ) & SUB169((
                                                  undefined  [16])0xffffffffffffffff >> 0x38,0) |
                                                  SUB169(((undefined  [16])0x0 << 0x40) >> 0x38,0))
                                                  & SUB169((undefined  [16])0xffffffffffffffff >>
                                                           0x38,0),
                                                  SUB167(auVar33,0) & 0xffffffffffff |
                                                  (SUB167(auVar33,0) >> 0x18) << 0x30) >> 0x28,0) &
                                                  SUB1611((undefined  [16])0xffff000000000000 >>
                                                          0x28,0)) &
                                                  SUB1611((undefined  [16])0xffff00ffffffffff >>
                                                          0x28,0),
                                                  SUB165(auVar33,0) & 0xffffffff |
                                                  (SUB165(auVar33,0) >> 0x10) << 0x20) >> 0x18,0) &
                                        SUB1613((undefined  [16])0xffffffff00000000 >> 0x18,0)) &
                                        SUB1613((undefined  [16])0xffffffff00ffffff >> 0x18,0),
                                        (SUB163(auVar33,0) >> 8) << 0x10) &
                              (undefined  [16])0xffffffffffff0000) &
                              (undefined  [16])0xffffffffffff00ff;
                    auVar33 = pshuflw(auVar33,auVar33,0xb1);
                    auVar33 = pshufhw(auVar33,auVar33,0xb1);
                    auVar33 = packuswb(auVar33,auVar35);
                    auVar35 = ZEXT1516(CONCAT114(SUB161(auVar34 >> 0x78,0),
                                                 ZEXT1314(CONCAT112(SUB161(auVar34 >> 0x70,0),
                                                                    ZEXT1112(CONCAT110(SUB161(
                                                  auVar34 >> 0x68,0),
                                                  (unkuint10)
                                                  CONCAT18(SUB161(auVar34 >> 0x60,0),
                                                           (ulong)CONCAT16(SUB161(auVar34 >> 0x58,0)
                                                                           ,(uint6)CONCAT14(SUB161(
                                                  auVar34 >> 0x50,0),
                                                  (uint)CONCAT12(SUB161(auVar34 >> 0x48,0),
                                                                 (ushort)SUB161(auVar34 >> 0x40,0)))
                                                  ))))))));
                    auVar35 = pshuflw(auVar35,auVar35,0xb1);
                    auVar35 = pshufhw(auVar35,auVar35,0xb1);
                    auVar34 = (auVar34 & (undefined  [16])0xffff |
                              CONCAT133((SUB1613(auVar34 >> 0x18,0) &
                                         SUB1613((undefined  [16])0xffffffff >> 0x18,0) |
                                        SUB1613(CONCAT115((SUB1611(auVar34 >> 0x28,0) &
                                                           SUB1611((undefined  [16])0xffffffffffff
                                                                   >> 0x28,0) |
                                                          SUB1611(CONCAT97((unkuint9)
                                                                           (SUB168(auVar34,0) >>
                                                                           0x38) & 0xffff &
                                                                           SUB169((undefined  [16])
                                                                                  0xffffffffffffffff
                                                                                  >> 0x38,0),
                                                                           SUB167(auVar34,0) &
                                                                           0xffffffffffff |
                                                                           (SUB167(auVar34,0) >>
                                                                           0x18) << 0x30) >> 0x28,0)
                                                          & SUB1611((undefined  [16])
                                                                    0xffff000000000000 >> 0x28,0)) &
                                                          SUB1611((undefined  [16])
                                                                  0xffff00ffffffffff >> 0x28,0),
                                                          SUB165(auVar34,0) & 0xffffffff |
                                                          (SUB165(auVar34,0) >> 0x10) << 0x20) >>
                                                0x18,0) &
                                        SUB1613((undefined  [16])0xffffffff00000000 >> 0x18,0)) &
                                        SUB1613((undefined  [16])0xffffffff00ffffff >> 0x18,0),
                                        (SUB163(auVar34,0) >> 8) << 0x10) &
                              (undefined  [16])0xffffffffffff0000) &
                              (undefined  [16])0xffffffffffff00ff;
                    auVar34 = pshuflw(auVar34,auVar34,0xb1);
                    auVar34 = pshufhw(auVar34,auVar34,0xb1);
                    auVar34 = packuswb(auVar34,auVar35);
                    /* WARNING: Store size is inaccurate */
                    *(undefined *)(local_840 + lVar19 * 2) = auVar33;
                    /* WARNING: Store size is inaccurate */
                    *(undefined *)(auStack2055 + lVar19 * 2 + lVar17) = auVar34;
                  }
                  if (uVar24 == (ulong)bVar5) goto LAB_001033ee;
                }
                do {
                  puVar1 = (ushort *)(local_818 + uVar24 * 2 + lVar17 + 1);
                  *puVar1 = *puVar1 << 8 | *puVar1 >> 8;
                  uVar24 = uVar24 + 1;
                } while ((ulong)bVar5 != uVar24);
              }
            }
LAB_001033ee:
            uVar15 = tsk_UTF16toUTF8((ulong)uVar15,&local_840,local_818 + lVar17 + (ulong)bVar21 + 1
                                    );
            if (uVar15 != 0) {
              if (_tsk_verbose != 0) {
                tsk_fprintf(stderr,
                            "iso9660_load_inodes_dir: Error converting Joliet name to UTF8: %d",
                            (ulong)uVar15);
              }
              __ptr[0x30] = 0;
            }
            __ptr[0x30] = 0;
          }
          __s = __ptr + 0x30;
          pcVar18 = strchr(__s,0x3b);
          if (pcVar18 != (char *)0x0) {
            lVar19 = strtol(pcVar18 + 1,(char **)0x0,10);
            *(int *)(__ptr + 0x140) = (int)lVar19;
            *pcVar18 = '\0';
          }
          __n = strlen(__s);
          if (__ptr[__n + 0x2f] == '.') {
            __ptr[__n + 0x2f] = 0;
          }
          if (*__s == '\0') {
            if (_tsk_verbose != 0) {
              tsk_fprintf(stderr,
                          "iso9660_load_inodes_dir: length of name after processing is 0. bailing\n"
                         );
            }
          }
          else {
LAB_001034aa:
            __ptr[0x20] = local_818[lVar17];
                    /* WARNING: Load size is inaccurate */
            auVar33 = *(undefined *)pbVar25;
                    /* WARNING: Load size is inaccurate */
            auVar34 = *(undefined *)(abStack2089 + lVar17 + 1);
                    /* WARNING: Store size is inaccurate */
            *(undefined *)(__ptr + 0x10) = auVar34;
                    /* WARNING: Store size is inaccurate */
            *(undefined *)__ptr = auVar33;
            *(undefined8 *)(__ptr + 0x28) = 0;
            iVar26 = *(int *)(param_1 + 0xb0);
            if (iVar26 == 1) {
              bVar3 = auStack2098[lVar17 + 1];
              bVar4 = auStack2098[lVar17 + 2];
              uVar8 = *(undefined3 *)(auStack2098 + lVar17);
              bVar21 = auStack2098[lVar17 + 3];
              bVar9 = auStack2098[lVar17];
              bVar5 = bVar21;
            }
            else {
              bVar5 = auStack2098[lVar17 + 3];
              bVar4 = auStack2098[lVar17 + 2];
              bVar3 = auStack2098[lVar17 + 1];
              uVar8 = CONCAT12(bVar3,CONCAT11(bVar4,bVar5));
              bVar21 = auStack2098[lVar17];
              bVar9 = bVar21;
            }
            uVar15 = (uint)bVar4;
            uVar32 = SUB168(auVar33,0);
            uVar20 = SUB168(auVar34,0);
            uVar16 = (uint)bVar5;
            if ((ulong)CONCAT13(bVar21,uVar8) < *(ulong *)(param_1 + 0x48) ||
                (ulong)CONCAT13(bVar21,uVar8) == *(ulong *)(param_1 + 0x48)) {
              if (iVar26 == 1) {
                uVar15 = *(uint *)(param_1 + 0x58);
                uVar23 = (ulong)(CONCAT13(bVar5,CONCAT12(bVar4,CONCAT11(bVar3,bVar9))) * uVar15);
                *(ulong *)(__ptr + 0x158) = uVar23;
                uVar27 = (ulong)(byte)__ptr[0xe];
                uVar6 = __ptr[0xf];
                uVar7 = __ptr[0x10];
                uVar8 = *(undefined3 *)(__ptr + 0xe);
                uVar12 = __ptr[0x11];
                uVar24 = (ulong)CONCAT11(uVar6,uVar12);
              }
              else {
                uVar15 = *(uint *)(param_1 + 0x58);
                uVar23 = (ulong)(CONCAT13(bVar9,CONCAT12(bVar3,CONCAT11(bVar4,bVar5))) * uVar15);
                *(ulong *)(__ptr + 0x158) = uVar23;
                uVar24 = (ulong)(byte)__ptr[0x11];
                uVar7 = __ptr[0x10];
                uVar6 = __ptr[0xf];
                uVar8 = CONCAT12(uVar6,CONCAT11(uVar7,__ptr[0x11]));
                uVar12 = __ptr[0xe];
                uVar27 = (ulong)CONCAT11(uVar7,uVar12);
              }
              iVar30 = (int)uVar24;
              uVar13 = (undefined)uVar24;
              uVar14 = (undefined)uVar27;
              if ((long)(CONCAT13(uVar12,uVar8) + uVar23) <=
                  (long)((ulong)uVar15 * *(long *)(param_1 + 0x38))) {
                uVar12 = uVar6;
                if (iVar26 != 1) {
                  uVar14 = uVar13;
                  uVar12 = uVar7;
                  uVar7 = uVar6;
                  iVar30 = (int)uVar27;
                }
                *(uint *)(__ptr + 0x170) =
                     iVar30 << 0x18 | (uint)CONCAT12(uVar7,CONCAT11(uVar12,uVar14));
                *(uint *)(__ptr + 0x174) = (uint)local_838[lVar17 + 1];
                *(long *)(__ptr + 0x160) = param_2 + lVar17;
                *(bool *)(__ptr + 0x144) = param_6 == '\0';
                *(long *)(__ptr + 0x168) = (long)(int)local_888;
                uVar24 = ((ulong)local_838[lVar17] + 0xffffffdf) - (ulong)local_818[lVar17];
                iVar26 = (int)uVar24;
                if (iVar26 < 2) {
                  *(undefined8 *)(__ptr + 0x138) = 0;
                    /* WARNING: Store size is inaccurate */
                  *(undefined *)(__ptr + 0x148) = (undefined  [16])0x0;
                  lVar29 = 0;
                  lVar19 = 0;
                  __ptr_00 = (void *)0x0;
                }
                else {
                  __ptr_00 = (void *)parse_susp(uVar32,uVar20,0,param_1,
                                                local_818 + (ulong)local_818[lVar17] + lVar17 + 1,
                                                uVar24 & 0xffffffff,0);
                  *(void **)(__ptr + 0x138) = __ptr_00;
                  uVar32 = stderr;
                  if (__ptr_00 == (void *)0x0) {
                    if (_tsk_verbose != 0) {
                      uVar20 = tsk_error_get();
                      tsk_fprintf(uVar32,
                                  "iso9660_load_inodes_dir: parse_susp returned error (%s). bailing\n"
                                  ,uVar20,uVar20);
                    }
                    free(__ptr);
                    local_888 = (ulong)((int)local_888 + 1U);
                    break;
                  }
                  lVar19 = lVar17 + 0x21 + param_2 + (ulong)local_818[lVar17];
                  *(long *)(__ptr + 0x148) = lVar19;
                  lVar29 = (long)iVar26;
                  *(long *)(__ptr + 0x150) = lVar29;
                }
                if (*(long *)(param_1 + 0x1c0) == 0) {
                  *(undefined **)(param_1 + 0x1c0) = __ptr;
                }
                else {
                  lVar11 = *(long *)(param_1 + 0x1c0);
                  do {
                    lVar28 = lVar11;
                    if ((((*(long *)(__ptr + 0x158) == *(long *)(lVar28 + 0x158)) &&
                         (param_6 == '\0')) && (*(int *)(__ptr + 0x170) != 0)) &&
                       (*(int *)(__ptr + 0x170) == *(int *)(lVar28 + 0x170))) {
                      if (__ptr_00 != (void *)0x0) {
                        if (*(long *)(lVar28 + 0x138) == 0) {
                          *(void **)(lVar28 + 0x138) = __ptr_00;
                          *(long *)(lVar28 + 0x148) = lVar19;
                          *(long *)(lVar28 + 0x150) = lVar29;
                        }
                        else {
                          free(__ptr_00);
                        }
                        *(undefined8 *)(__ptr + 0x138) = 0;
                      }
                      if (_tsk_verbose != 0) {
                        tsk_fprintf(stderr,
                                    "iso9660_load_inodes_dir: Removing duplicate entry for: %s (orig name: %s start: %d size: %d)\n"
                                    ,__ptr + 0x30);
                      }
                      free(__ptr);
                      goto LAB_0010382a;
                    }
                    lVar11 = *(long *)(lVar28 + 0x178);
                  } while (*(long *)(lVar28 + 0x178) != 0);
                  *(undefined **)(lVar28 + 0x178) = __ptr;
                }
                *(undefined8 *)(__ptr + 0x178) = 0;
                local_888 = (ulong)((int)local_888 + 1U);
LAB_0010382a:
                if (((uVar31 | local_874) == 0) && ((int)local_888 == 1)) {
                  bVar21 = *pbVar25;
                  pbVar25 = local_838 + lVar17 + (ulong)bVar21;
                  uVar31 = (uint)(lVar17 + (ulong)bVar21);
                }
                uVar15 = *pbVar25 + uVar31;
                goto LAB_00103860;
              }
              if (_tsk_verbose != 0) {
                uVar12 = uVar6;
                if (iVar26 != 1) {
                  uVar24 = uVar27;
                  uVar14 = uVar13;
                  uVar12 = uVar7;
                  uVar7 = uVar6;
                }
                tsk_fprintf(uVar32,uVar20,0,stderr,
                                                        
                            "iso9660_load_inodes_dir: file ends past end of image (%u bytes). bailing\n"
                            ,((uVar24 & 0xff) << 0x18 |
                             (ulong)CONCAT12(uVar7,CONCAT11(uVar12,uVar14))) + uVar23);
              }
            }
            else {
              if (_tsk_verbose != 0) {
                uVar31 = (uint)bVar3;
                uVar22 = (uint)bVar9;
                if (iVar26 != 1) {
                  uVar31 = uVar15;
                  uVar22 = uVar16;
                  uVar15 = (uint)bVar3;
                  uVar16 = (uint)bVar9;
                }
                uVar22 = uVar31 << 8 | uVar22;
                tsk_fprintf(uVar32,uVar20,0,stderr,
                            "iso9660_load_inodes_dir: file starts past end of image (%u). bailing\n"
                            ,(ulong)(uVar16 << 0x18 | uVar15 << 0x10 | uVar22),(ulong)uVar22);
              }
            }
          }
          free(__ptr);
          break;
        }
        if (local_818[lVar17] < 2) {
          if (*(int *)(param_1 + 0xb0) == 1) {
            uVar15 = (uint)abStack2089[lVar17 + 1] << 0x10 | (uint)abStack2089[lVar17] << 8;
            pbVar10 = abStack2089 + 2;
          }
          else {
            pbVar10 = &bStack2090;
            uVar15 = (uint)abStack2089[lVar17] << 0x10 | (uint)abStack2089[lVar17 + 1] << 8;
          }
          local_870 = ((uint)pbVar10[lVar17] << 0x18 | uVar15) >> 0xb;
          if (_tsk_verbose != 0) {
            tsk_fprintf(stderr,"iso9660_load_inodes_dir: %d number of additional sectors\n",
                        (ulong)local_870);
          }
          __n = strlen(param_5);
          if (0x80 < __n) {
            tsk_error_reset();
            tsk_error_set_errno(0x8000006);
            tsk_error_set_errstr("iso9660_load_inodes_dir: Name argument specified is too long");
            free(__ptr);
            return 0xffffffff;
          }
          strncpy(__ptr + 0x30,param_5,0x81);
          if ((int)local_888 == 0) goto LAB_001034aa;
          free(__ptr);
          uVar15 = (uint)local_838[lVar17 + (ulong)*pbVar25] + (int)(lVar17 + (ulong)*pbVar25);
        }
        else {
          if (_tsk_verbose != 0) {
            tsk_fprintf(stderr,"iso9660_load_inodes_dir: first entry has name length > 1\n");
          }
          free(__ptr);
          uVar15 = uVar31 + *pbVar25;
        }
      }
LAB_00103860:
      uVar31 = uVar15;
    } while ((int)uVar15 < 0x800);
    param_2 = param_2 + 0x800;
    local_874 = local_874 + 1;
    if ((int)local_870 <= (int)local_874) {
      return local_888;
    }
  } while( true );
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * parse_susp(long param_1,byte *param_2,ulong param_3,FILE *param_4)

{
  undefined3 uVar1;
  int iVar2;
  uint *__dest;
  void *__ptr;
  ulong uVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte bVar6;
  uint uVar7;
  uint *__dest_00;
  char *__format;
  byte *pbVar8;
  uint *puVar9;
  byte *local_150;
  uint local_138 [66];
  
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"parse_susp: count is: %d\n",param_3 & 0xffffffff);
  }
  puVar9 = (uint *)tsk_malloc();
  if (puVar9 == (uint *)0x0) {
    puVar9 = (uint *)0x0;
  }
  else {
    pbVar8 = param_2 + (long)(int)(param_3 & 0xffffffff) + -1;
    if (param_2 + 4 <= pbVar8) {
      __dest = puVar9 + 4;
      do {
        uVar3 = (ulong)param_2[2];
        if (pbVar8 < param_2 + (uVar3 - 1)) {
          return puVar9;
        }
        pbVar4 = param_2 + 2;
        switch(*param_2) {
        case 0x43:
          if (param_2[1] != 0x4c) {
            if (param_2[1] == 0x45) {
              if (pbVar8 < param_2 + 0x1b) {
                if (_tsk_verbose == 0) {
                  return puVar9;
                }
                __format = "parse_susp: not enough room for CE structure\n";
                goto LAB_00104588;
              }
              if (param_4 != (FILE *)0x0) {
                fwrite("CE Entry\n",9,1,param_4);
                if (*(int *)(param_1 + 0xb0) == 1) {
                  uVar1 = *(undefined3 *)(param_2 + 8);
                  pbVar4 = param_2 + 0xb;
                }
                else {
                  pbVar4 = param_2 + 8;
                  uVar1 = CONCAT12(param_2[9],CONCAT11(param_2[10],param_2[0xb]));
                }
                fprintf(param_4,"* Block: %u\n",(ulong)CONCAT13(*pbVar4,uVar1));
                if (*(int *)(param_1 + 0xb0) == 1) {
                  uVar1 = *(undefined3 *)(param_2 + 0x10);
                  pbVar4 = param_2 + 0x13;
                }
                else {
                  pbVar4 = param_2 + 0x10;
                  uVar1 = CONCAT12(param_2[0x11],CONCAT11(param_2[0x12],param_2[0x13]));
                }
                fprintf(param_4,"* Offset: %u\n",(ulong)CONCAT13(*pbVar4,uVar1));
                if (*(int *)(param_1 + 0xb0) == 1) {
                  uVar1 = *(undefined3 *)(param_2 + 0x18);
                  pbVar4 = param_2 + 0x1b;
                }
                else {
                  pbVar4 = param_2 + 0x18;
                  uVar1 = CONCAT12(param_2[0x19],CONCAT11(param_2[0x1a],param_2[0x1b]));
                }
                fprintf(param_4,"* Len: %u\n",(ulong)CONCAT13(*pbVar4,uVar1));
              }
              if (*(int *)(param_1 + 0xb0) == 1) {
                uVar1 = *(undefined3 *)(param_2 + 8);
                bVar6 = param_2[0xb];
              }
              else {
                uVar1 = CONCAT12(param_2[9],CONCAT11(param_2[10],param_2[0xb]));
                bVar6 = param_2[8];
              }
              if ((ulong)CONCAT13(bVar6,uVar1) < *(ulong *)(param_1 + 0x48)) {
                if (*(int *)(param_1 + 0xb0) == 1) {
                  uVar1 = *(undefined3 *)(param_2 + 0x10);
                  bVar6 = param_2[0x13];
                }
                else {
                  uVar1 = CONCAT12(param_2[0x11],CONCAT11(param_2[0x12],param_2[0x13]));
                  bVar6 = param_2[0x10];
                }
                if (CONCAT13(bVar6,uVar1) < *(uint *)(param_1 + 0x58)) {
                  local_150 = param_2 + 0x18;
                  __ptr = (void *)tsk_malloc();
                  if (__ptr == (void *)0x0) {
                    if (_tsk_verbose != 0) {
                      fwrite("parse_susp: error allocating memory to process CE entry\n",0x38,1,
                             stderr);
                    }
                    tsk_error_reset();
                    uVar3 = (ulong)param_2[2];
                  }
                  else {
                    uVar3 = tsk_fs_read(param_1);
                    if (*(int *)(param_1 + 0xb0) == 1) {
                      uVar1 = *(undefined3 *)(param_2 + 0x18);
                      local_150 = param_2 + 0x1b;
                    }
                    else {
                      uVar1 = CONCAT12(param_2[0x19],CONCAT11(param_2[0x1a],param_2[0x1b]));
                    }
                    if (uVar3 == (ulong)CONCAT13(*local_150,uVar1)) {
                      parse_susp(param_1,__ptr,uVar3 & 0xffffffff,param_4);
                    }
                    else {
                      if (_tsk_verbose != 0) {
                        fwrite("parse_susp: error reading CE entry\n",0x23,1,stderr);
                        tsk_error_print(stderr);
                        tsk_error_reset();
                      }
                    }
                    free(__ptr);
                    uVar3 = (ulong)param_2[2];
                  }
                  break;
                }
              }
              if (_tsk_verbose != 0) {
                fwrite("parse_susp: CE offset or block too large to process\n",0x34,1,stderr);
              }
              goto LAB_0010428a;
            }
            goto switchD_00103d78_caseD_45;
          }
          if (param_4 != (FILE *)0x0) {
            __format = "CL Entry\n";
            goto LAB_00103f60;
          }
          break;
        default:
switchD_00103d78_caseD_45:
          param_2 = param_2 + 1;
          if (((ulong)pbVar4 & 1) == 0) {
            param_2 = pbVar4;
          }
          goto LAB_00103f79;
        case 0x45:
          if (param_2[1] == 0x53) {
            if (param_4 != (FILE *)0x0) {
              __format = "ES Entry\n";
              goto LAB_00103f60;
            }
          }
          else {
            if (param_2[1] != 0x52) goto switchD_00103d78_caseD_45;
            if (param_4 != (FILE *)0x0) {
              fwrite("ER Entry\n",9,1,param_4);
              __dest_00 = local_138;
              memcpy(__dest_00,param_2 + 8,(ulong)param_2[4]);
              *(undefined *)((long)local_138 + (ulong)param_2[4]) = 0;
              fprintf(param_4,"* Extension ID: %s\n",__dest_00);
              memcpy(__dest_00,param_2 + (ulong)param_2[4] + 8,(ulong)param_2[5]);
              *(undefined *)((long)local_138 + (ulong)param_2[5]) = 0;
              fprintf(param_4,"* Extension Descriptor: %s\n",__dest_00);
              memcpy(__dest_00,param_2 + (ulong)param_2[5] + (ulong)param_2[4] + 8,(ulong)param_2[6]
                    );
              *(undefined *)((long)local_138 + (ulong)param_2[6]) = 0;
              __format = "* Extension Spec Source: %s\n";
LAB_00103d53:
              fprintf(param_4,__format,__dest_00);
              uVar3 = (ulong)param_2[2];
            }
          }
          break;
        case 0x4e:
          if (param_2[1] != 0x4d) goto switchD_00103d78_caseD_45;
          if (pbVar8 < param_2 + 5) {
            if (_tsk_verbose == 0) {
              return puVar9;
            }
            __format = "parse_susp: not enough room for RR alternative name structure\n";
LAB_00104588:
            tsk_fprintf(stderr,__format);
            return puVar9;
          }
          if (pbVar8 < param_2 + (uVar3 - 1)) {
            if (_tsk_verbose == 0) {
              return puVar9;
            }
            __format = "parse_susp: not enough room for RR alternative name\n";
            goto LAB_00104588;
          }
          iVar2 = (uint)param_2[2] - 5;
          if (0xff < iVar2) {
            iVar2 = 0xff;
          }
          strncpy((char *)__dest,(char *)(param_2 + 5),(long)iVar2);
          *(undefined *)((long)__dest + (long)iVar2) = 0;
          if (param_4 != (FILE *)0x0) {
            fwrite("NM Entry\n",9,1,param_4);
            __format = "* %s\n";
            __dest_00 = __dest;
            goto LAB_00103d53;
          }
LAB_0010428a:
          uVar3 = (ulong)param_2[2];
          break;
        case 0x50:
          switch(param_2[1]) {
          case 0x44:
            if (param_4 != (FILE *)0x0) {
              __format = "PD Entry\n";
LAB_00103f60:
              fwrite(__format,9,1,param_4);
LAB_00103f72:
              uVar3 = (ulong)*pbVar4;
            }
            break;
          case 0x4c:
            if (param_4 != (FILE *)0x0) {
              __format = "PL Entry\n";
              goto LAB_00103f60;
            }
            break;
          case 0x4e:
            if (param_4 != (FILE *)0x0) {
              fwrite("PN Entry\n",9,1,param_4);
              if (*(int *)(param_1 + 0xb0) == 1) {
                uVar1 = *(undefined3 *)(param_2 + 8);
                pbVar5 = param_2 + 0xb;
              }
              else {
                pbVar5 = param_2 + 8;
                uVar1 = CONCAT12(param_2[9],CONCAT11(param_2[10],param_2[0xb]));
              }
              fprintf(param_4,"* Device ID High: %u\n",(ulong)CONCAT13(*pbVar5,uVar1));
              if (*(int *)(param_1 + 0xb0) == 1) {
                uVar1 = *(undefined3 *)(param_2 + 0x10);
                pbVar5 = param_2 + 0x13;
              }
              else {
                pbVar5 = param_2 + 0x10;
                uVar1 = CONCAT12(param_2[0x11],CONCAT11(param_2[0x12],param_2[0x13]));
              }
              uVar7 = CONCAT13(*pbVar5,uVar1);
              __format = "* Device ID Low: %u\n";
LAB_00104311:
              fprintf(param_4,__format,(ulong)uVar7);
              goto LAB_00103f72;
            }
            break;
          case 0x58:
            if (pbVar8 < param_2 + 0x2d) {
              if (_tsk_verbose == 0) {
                return puVar9;
              }
              __format = "parse_susp: not enough room for POSIX structure\n";
              goto LAB_00104588;
            }
            if (*(int *)(param_1 + 0xb0) == 1) {
              *puVar9 = *(uint *)(param_2 + 0x18);
              puVar9[1] = *(uint *)(param_2 + 0x20);
              *(undefined2 *)(puVar9 + 2) = *(undefined2 *)(param_2 + 8);
              uVar1 = *(undefined3 *)(param_2 + 0x10);
              pbVar5 = param_2 + 0x13;
            }
            else {
              uVar7 = *(uint *)(param_2 + 0x18);
              *puVar9 = uVar7 >> 0x18 | (uVar7 & 0xff0000) >> 8 | (uVar7 & 0xff00) << 8 |
                        uVar7 << 0x18;
              uVar7 = *(uint *)(param_2 + 0x20);
              puVar9[1] = uVar7 >> 0x18 | (uVar7 & 0xff0000) >> 8 | (uVar7 & 0xff00) << 8 |
                          uVar7 << 0x18;
              *(ushort *)(puVar9 + 2) =
                   *(ushort *)(param_2 + 8) << 8 | *(ushort *)(param_2 + 8) >> 8;
              pbVar5 = param_2 + 0x10;
              uVar1 = CONCAT12(param_2[0x11],CONCAT11(param_2[0x12],param_2[0x13]));
            }
            puVar9[3] = CONCAT13(*pbVar5,uVar1);
            if (param_4 != (FILE *)0x0) {
              fwrite("PX Entry\n",9,1,param_4);
              fprintf(param_4,"* UID: %u\n",(ulong)*puVar9);
              fprintf(param_4,"* GID: %u\n",(ulong)puVar9[1]);
              fprintf(param_4,"* Mode: %d\n",(ulong)*(ushort *)(puVar9 + 2));
              uVar7 = puVar9[3];
              __format = "* Links: %u\n";
              goto LAB_00104311;
            }
            break;
          default:
            goto switchD_00103d78_caseD_45;
          }
          break;
        case 0x52:
          if (param_2[1] == 0x52) {
            *(undefined *)(param_1 + 0x1c8) = 1;
            if (param_4 != (FILE *)0x0) {
              __format = "RR Entry\n";
              goto LAB_00103f60;
            }
          }
          else {
            if (param_2[1] != 0x45) goto switchD_00103d78_caseD_45;
            if (param_4 != (FILE *)0x0) {
              __format = "RE Entry\n";
              goto LAB_00103f60;
            }
          }
          break;
        case 0x53:
          switch(param_2[1] + 0xba >> 1 | param_2[1] << 7) {
          case 0:
            if (param_4 != (FILE *)0x0) {
              __format = "SF Entry\n";
              goto LAB_00103f60;
            }
            break;
          case 3:
            if (param_4 != (FILE *)0x0) {
              __format = "SL Entry\n";
              goto LAB_00103f60;
            }
            break;
          case 5:
            if (param_4 != (FILE *)0x0) {
              fwrite("SP Entry\n",9,1,param_4);
              fprintf(param_4,"* SKip Len: %d\n",(ulong)param_2[6]);
              uVar3 = (ulong)param_2[2];
            }
            break;
          case 7:
            if (param_4 != (FILE *)0x0) {
              __format = "ST Entry\n";
              goto LAB_00103f60;
            }
            break;
          default:
            goto switchD_00103d78_caseD_45;
          }
          break;
        case 0x54:
          if (param_2[1] != 0x46) goto switchD_00103d78_caseD_45;
          if (param_4 != (FILE *)0x0) {
            __format = "TF Entry\n";
            goto LAB_00103f60;
          }
        }
        param_2 = param_2 + uVar3;
LAB_00103f79:
      } while (param_2 + 4 <= pbVar8);
    }
  }
  return puVar9;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 iso9660_dinode_copy(long param_1,long param_2,undefined8 param_3,long param_4)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  undefined4 uVar6;
  undefined3 uVar7;
  time_t tVar8;
  uint *puVar9;
  undefined *puVar10;
  uint *puVar11;
  undefined auVar13 [12];
  undefined auVar12 [16];
  undefined local_58 [16];
  int local_48;
  uint local_44;
  int local_40;
  int iStack60;
  int iStack56;
  undefined4 uStack52;
  int local_30;
  int iStack44;
  int iStack40;
  undefined4 uStack36;
  
  if (param_2 == 0) {
    tsk_error_set_errno(0x8000006);
    param_2 = tsk_error_set_errstr("iso9660_dinode_copy: fs_file or meta is NULL");
  }
  else {
    *(undefined4 *)(param_2 + 0xe8) = 0;
    if (*(long *)(param_2 + 0xe0) != 0) {
      tsk_fs_attrlist_markunused();
    }
    if ((7 < *(ulong *)(param_2 + 0xc0)) || (param_2 = tsk_fs_meta_realloc(param_2), param_2 != 0))
    {
      *(undefined8 *)(param_2 + 8) = param_3;
      if (*(int *)(param_1 + 0xb0) == 1) {
        uVar7 = *(undefined3 *)(param_4 + 0xe);
        puVar10 = (undefined *)(param_4 + 0x11);
      }
      else {
        puVar10 = (undefined *)(param_4 + 0xe);
        uVar7 = CONCAT12(*(undefined *)(param_4 + 0xf),
                         CONCAT11(*(undefined *)(param_4 + 0x10),*(undefined *)(param_4 + 0x11)));
      }
      *(ulong *)(param_2 + 0x20) = (ulong)CONCAT13(*puVar10,uVar7);
      marker317._7456_8_ = "function_inlined: memset";
      local_40 = 0;
      iStack60 = 0;
      iStack56 = 0;
      uStack36 = 0;
      uStack52 = 0;
      uVar3 = *(uint *)(param_4 + 0x14);
      auVar12 = CONCAT115(SUB1611(CONCAT106((unkuint10)
                                            SUB115(CONCAT47(uVar3 >> 0x18,
                                                            (uint7)(uVar3 >> 0x18) << 0x30) >> 0x30,
                                                   0) &
                                            SUB1610((undefined  [16])0xffffffffffffffff >> 0x30,0),
                                            (uint6)(uVar3 >> 0x10) << 0x28) >> 0x28,0),
                          (uint5)(uVar3 >> 0x10) << 0x20);
      auVar13 = SUB1612(auVar12 >> 0x20,0);
      uVar6 = SUB164(CONCAT142(SUB1614(CONCAT133(SUB1613(CONCAT124(auVar13,(uVar3 >> 8) << 0x18) >>
                                                         0x18,0),((uint3)uVar3 >> 8) << 0x10) >>
                                       0x10,0),(ushort)uVar3 & 0xff | (ushort)uVar3 << 8),0);
      auVar12 = CONCAT412(SUB164((ZEXT1216(auVar13) << 0x20) >> 0x60,0),
                          CONCAT48(uVar6,CONCAT44(SUB164(auVar12 >> 0x20,0),uVar6)));
      auVar12 = pshuflw(auVar12,auVar12,0xe7);
      local_58 = pshufhw(auVar12,auVar12,0xc5);
      local_58 = local_58 & _LCPI17_0;
      local_48 = (uint)*(byte *)(param_4 + 0x13) - 1;
      local_44 = (uint)*(byte *)(param_4 + 0x12);
      local_30 = local_40;
      iStack44 = iStack60;
      iStack40 = iStack56;
      tVar8 = mktime((tm *)local_58);
      *(time_t *)(param_2 + 0x60) = tVar8;
      *(undefined8 *)(param_2 + 0x50) = 0;
      *(undefined8 *)(param_2 + 0x40) = 0;
      *(undefined8 *)(param_2 + 0x30) = 0;
      *(undefined4 *)(param_2 + 0x58) = 0;
      *(undefined4 *)(param_2 + 0x48) = 0;
      *(undefined4 *)(param_2 + 0x38) = 0;
      *(undefined4 *)(param_2 + 0x68) = 0;
      *(int *)(param_2 + 0x10) = 2 - (uint)((*(byte *)(param_4 + 0x19) & 2) == 0);
      puVar5 = *(uint **)(param_4 + 0x28);
      if (puVar5 == (uint *)0x0) {
        *(undefined8 *)(param_2 + 0x28) = 0;
        *(undefined8 *)(param_2 + 0x14) = 0x100000000;
        iVar4 = *(int *)(param_1 + 0xb0);
      }
      else {
        iVar4 = *(int *)(param_1 + 0xb0);
        if (iVar4 == 1) {
          *(uint *)(param_2 + 0x28) = *puVar5;
          *(uint *)(param_2 + 0x2c) = puVar5[1];
          puVar11 = puVar5 + 2;
          puVar9 = (uint *)((long)puVar5 + 9);
        }
        else {
          uVar3 = *puVar5;
          *(uint *)(param_2 + 0x28) =
               uVar3 >> 0x18 | (uVar3 & 0xff0000) >> 8 | (uVar3 & 0xff00) << 8 | uVar3 << 0x18;
          uVar3 = puVar5[1];
          *(uint *)(param_2 + 0x2c) =
               uVar3 >> 0x18 | (uVar3 & 0xff0000) >> 8 | (uVar3 & 0xff00) << 8 | uVar3 << 0x18;
          puVar9 = puVar5 + 2;
          puVar11 = (uint *)((long)puVar5 + 9);
        }
        bVar1 = *(byte *)puVar11;
        bVar2 = *(byte *)puVar9;
        *(uint *)(param_2 + 0x14) =
             (((uint)bVar1 & 0x40 | ((uint)bVar1 & 0x10) << 4) + ((uint)bVar1 & 0x20) * 4 |
             ((uint)bVar2 & 1) << 5) + ((uint)bVar2 & 2) * 8 + ((uint)bVar2 & 4) * 2 |
             (uint)(bVar2 >> 2) & 4 | (uint)(bVar2 >> 6) & 1 | (uint)(bVar2 >> 4) & 2;
        *(undefined4 *)(param_2 + 0x18) = 1;
      }
      if (iVar4 == 1) {
        uVar7 = *(undefined3 *)(param_4 + 6);
        puVar10 = (undefined *)(param_4 + 9);
      }
      else {
        puVar10 = (undefined *)(param_4 + 6);
        uVar7 = CONCAT12(*(undefined *)(param_4 + 7),
                         CONCAT11(*(undefined *)(param_4 + 8),*(undefined *)(param_4 + 9)));
      }
      **(ulong **)(param_2 + 0xb8) = (ulong)CONCAT13(*puVar10,uVar7);
      *(int *)(param_2 + 4) = 6 - (uint)(*(char *)(param_4 + 0x144) == '\0');
      return 0;
    }
  }
  return CONCAT71((int7)((ulong)param_2 >> 8),1);
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 * make_unix_perm(long param_1,long param_2,long param_3,undefined8 *param_4)

{
  long lVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  
  if (_tsk_verbose != 0) {
    tsk_fprintf(stderr,"make_unix_perm: fs: %lu dd: %lu\n",param_1);
  }
  marker317._5480_8_ = "function_inlined: memset";
  *param_4 = 0x2d2d2d2d2d2d2d2d;
  *(undefined2 *)(param_4 + 1) = 0x2d2d;
  *(undefined *)((long)param_4 + 10) = 0;
  if ((*(byte *)(param_2 + 0x19) & 2) != 0) {
    *(undefined *)param_4 = 100;
  }
  lVar1 = *(long *)(param_3 + 0x28);
  if (lVar1 == 0) {
    marker317._10312_8_ = "function_inlined: strcpy";
    *(undefined8 *)((long)param_4 + 1) = 0x2d72782d72782d72;
    *(undefined2 *)((long)param_4 + 9) = 0x78;
  }
  else {
    iVar3 = *(int *)(param_1 + 0xb0);
    if ((*(byte *)((lVar1 + 9) - (ulong)(iVar3 == 1)) & 0x10) != 0) {
      *(undefined *)((long)param_4 + 1) = 0x72;
      iVar3 = *(int *)(param_1 + 0xb0);
      lVar1 = *(long *)(param_3 + 0x28);
    }
    pbVar4 = (byte *)(lVar1 + 8);
    pbVar2 = (byte *)(lVar1 + 9);
    if (iVar3 == 1) {
      pbVar2 = pbVar4;
    }
    if ((*pbVar2 & 0x40) != 0) {
      *(undefined *)((long)param_4 + 3) = 0x78;
      iVar3 = *(int *)(param_1 + 0xb0);
      lVar1 = *(long *)(param_3 + 0x28);
      pbVar4 = (byte *)(lVar1 + 8);
    }
    pbVar2 = (byte *)(lVar1 + 9);
    if (iVar3 != 1) {
      pbVar2 = pbVar4;
    }
    if ((*pbVar2 & 1) != 0) {
      *(undefined *)((long)param_4 + 4) = 0x72;
      iVar3 = *(int *)(param_1 + 0xb0);
      lVar1 = *(long *)(param_3 + 0x28);
      pbVar4 = (byte *)(lVar1 + 8);
    }
    pbVar2 = (byte *)(lVar1 + 9);
    if (iVar3 != 1) {
      pbVar2 = pbVar4;
    }
    if ((*pbVar2 & 4) != 0) {
      *(undefined *)((long)param_4 + 6) = 0x78;
      iVar3 = *(int *)(param_1 + 0xb0);
      lVar1 = *(long *)(param_3 + 0x28);
      pbVar4 = (byte *)(lVar1 + 8);
    }
    pbVar2 = (byte *)(lVar1 + 9);
    if (iVar3 != 1) {
      pbVar2 = pbVar4;
    }
    if ((*pbVar2 & 0x10) != 0) {
      *(undefined *)((long)param_4 + 7) = 0x72;
      iVar3 = *(int *)(param_1 + 0xb0);
      lVar1 = *(long *)(param_3 + 0x28);
      pbVar4 = (byte *)(lVar1 + 8);
    }
    pbVar2 = (byte *)(lVar1 + 9);
    if (iVar3 != 1) {
      pbVar2 = pbVar4;
    }
    if ((*pbVar2 & 0x40) != 0) {
      *(undefined *)((long)param_4 + 9) = 0x78;
    }
  }
  return param_4;
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

int _IO_putc(int __c,_IO_FILE *__fp)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
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

int fprintf(FILE *__stream,char *__format,...)

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

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

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

time_t mktime(tm *__tp)

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

char * strchr(char *__s,int __c)

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
/* WARNING: Unknown calling convention yet parameter storage is locked */

long strtol(char *__nptr,char **__endptr,int __base)

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

void tsk_error_errstr2_concat(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_error_get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_error_print(void)

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

void tsk_fprintf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_attr_print(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_attr_run_alloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_attr_set_run(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_attrlist_alloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_attrlist_getnew(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_attrlist_markunused(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_block_alloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_block_free(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_block_get_flag(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_dir_find_inum_named(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_dir_load_inum_named(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_dir_make_orphan_dir_meta(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_file_alloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_file_attr_get_type(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_file_close(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_file_open_meta(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_free(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_malloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_meta_alloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_meta_realloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_meta_reset(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_read(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_time_to_str(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_guess_end_u32(void)

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


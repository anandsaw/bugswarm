
/* WARNING: Could not reconcile some variable overlaps */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
exfatfs_dent_parse_buf(long param_1,long param_2,ushort *param_3,long param_4,long param_5)

{
  long lVar1;
  undefined4 *puVar2;
  char *__s;
  ulong uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char cVar6;
  char cVar7;
  int iVar8;
  undefined8 *puVar9;
  size_t sVar10;
  undefined4 uVar11;
  long lVar12;
  long lVar13;
  ulong uVar14;
  ulong uVar15;
  undefined8 uVar16;
  byte bVar17;
  bool bVar18;
  long local_258;
  char local_250;
  undefined8 local_24f;
  size_t local_48;
  long local_40;
  long local_38;
  
  tsk_error_reset();
  cVar6 = fatfs_ptr_arg_is_null(param_1,"a_fatfs","exfatfs_parse_directory_buf");
  uVar16 = 1;
  if ((((cVar6 == '\0') &&
       (cVar6 = fatfs_ptr_arg_is_null(param_2,"a_fs_dir","exfatfs_parse_directory_buf"),
       cVar6 == '\0')) &&
      (cVar6 = fatfs_ptr_arg_is_null(param_3,"a_buf","exfatfs_parse_directory_buf"), cVar6 == '\0'))
     && (cVar6 = fatfs_ptr_arg_is_null(param_5,"a_sector_addrs","exfatfs_parse_directory_buf"),
        cVar6 == '\0')) {
    marker323._8616_8_ = "function_inlined: assert";
    if (param_4 < 1) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("a_buf_len > 0","exfatfs_dent.c",0x23c,
                                        
                    "TSK_RETVAL_ENUM exfatfs_dent_parse_buf(FATFS_INFO *, TSK_FS_DIR *, char *, TSK_OFF_T, TSK_DADDR_T *)"
                   );
    }
    memset(&local_250,0,0x220);
    local_258 = param_1;
    local_40 = tsk_fs_name_alloc(0x400);
    if (local_40 != 0) {
      **(undefined **)(local_40 + 8) = 0;
      param_4 = param_4 / (long)(ulong)*(ushort *)(param_1 + 0x4230);
      local_38 = param_2;
      if (0 < param_4) {
        lVar12 = 0;
        do {
          lVar1 = *(long *)(param_5 + lVar12 * 8);
          uVar15 = (ulong)*(uint *)(param_1 + 0x4228) * (lVar1 - *(long *)(param_1 + 0x4200)) + 3;
          if (*(ulong *)(param_1 + 0x30) <= uVar15 && uVar15 != *(ulong *)(param_1 + 0x30)) {
            tsk_error_reset();
            tsk_error_set_errno(0x8000006);
            tsk_error_set_errstr
                      (
                       "%s: inode address for sector address %lu at addresses array index %lu is too large"
                       ,"exfatfs_parse_directory_buf",uVar15,lVar12);
            tsk_fs_name_free(local_40);
            return 2;
          }
          if (_tsk_verbose != 0) {
            tsk_fprintf(stderr,"%s: Parsing sector %lu for dir %lu\n","exfatfs_parse_directory_buf",
                        lVar1,*(undefined8 *)(param_2 + 0x28));
          }
          local_250 = fatfs_is_sectalloc(param_1);
          if (local_250 == -1) {
            if (_tsk_verbose != 0) {
              tsk_fprintf(stderr,"%s: Error looking up allocation status of sector : %lu\n",
                          "exfatfs_parse_directory_buf",*(undefined8 *)(param_5 + lVar12 * 8));
              tsk_error_print(stderr);
            }
            tsk_error_reset();
          }
          else {
            if (*(int *)(param_1 + 0x4228) != 0) {
              uVar14 = 0;
LAB_001001c1:
              lVar1 = uVar15 + uVar14;
              cVar6 = fatfs_inum_is_in_range(param_1,lVar1);
              if (cVar6 == '\0') {
                tsk_fs_name_free(local_40);
                return 1;
              }
              cVar6 = exfatfs_is_dentry(param_1);
              if (cVar6 == '\0') {
                bVar17 = 0;
              }
              else {
                bVar17 = *(byte *)param_3;
              }
              iVar8 = exfatfs_get_enum_from_type((ulong)bVar17);
              switch(iVar8) {
              case 1:
              case 2:
              case 0x20:
              case 0x21:
                goto switchD_0010021f_caseD_1;
              case 3:
                marker323._568_8_ = "function_inlined: assert";
                marker323._104_8_ = "function_inlined: assert";
                if (local_258 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fatfs != NULL","exfatfs_dent.c",0x178,
                                                                
                                "void exfats_parse_vol_label_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._6864_8_ = "function_inlined: assert";
                if (local_40 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name != NULL","exfatfs_dent.c",0x17a,
                                                                
                                "void exfats_parse_vol_label_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._3528_8_ = "function_inlined: assert";
                if (*(long *)(local_40 + 8) == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name->name != NULL","exfatfs_dent.c",0x17c,
                                                                
                                "void exfats_parse_vol_label_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._7496_8_ = "function_inlined: assert";
                if (*(long *)(local_40 + 0x10) != 0x400) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name->name_size == FATFS_MAXNAMLEN_UTF8",
                                "exfatfs_dent.c",0x17e,
                                                                
                                "void exfats_parse_vol_label_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._12896_8_ = "function_inlined: assert";
                if (local_38 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_dir != NULL","exfatfs_dent.c",0x180,
                                                                
                                "void exfats_parse_vol_label_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._3048_8_ = "function_inlined: assert";
                if (param_3 == (ushort *)0x0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("dentry != NULL","exfatfs_dent.c",0x182,
                                                                
                                "void exfats_parse_vol_label_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._15272_8_ = "function_inlined: assert";
                iVar8 = exfatfs_get_enum_from_type((ulong)*(byte *)param_3);
                if (iVar8 != 3) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail(
                                "exfatfs_get_enum_from_type(dentry->entry_type) == EXFATFS_DIR_ENTRY_TYPE_VOLUME_LABEL"
                                ,"exfatfs_dent.c",0x184,
                                                                
                                "void exfats_parse_vol_label_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._12872_8_ = "function_inlined: assert";
                cVar6 = fatfs_inum_is_in_range(local_258);
                if (cVar6 == '\0') {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("fatfs_inum_is_in_range(a_name_info->fatfs, a_inum)",
                                "exfatfs_dent.c",0x186,
                                                                
                                "void exfats_parse_vol_label_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                exfatfs_add_name_to_dir_and_reset_info(&local_258);
                local_24f = local_24f & 0xffffffffffffff00 | (ulong)*(byte *)param_3;
                if (0xf < *(byte *)((long)param_3 + 1)) {
                  *(byte *)((long)param_3 + 1) = 0xf;
                }
                cVar6 = exfatfs_get_alloc_status_from_type((ulong)*(byte *)param_3);
                uVar5 = "$EMPTY_VOLUME_LABEL"._12_4_;
                uVar4 = "$EMPTY_VOLUME_LABEL"._8_4_;
                uVar11 = "$EMPTY_VOLUME_LABEL"._4_4_;
                if (cVar6 == '\x01') {
                  iVar8 = fatfs_utf16_inode_str_2_utf8
                                    (local_258,param_3 + 1,(ulong)*(byte *)((long)param_3 + 1),
                                     *(undefined8 *)(local_40 + 8),*(undefined8 *)(local_40 + 0x10),
                                     lVar1,"volume label");
                  if (iVar8 != 0) {
                    marker323._10232_8_ = "function_inlined: assert";
                    marker323._13848_8_ = "function_inlined: assert";
                    if (local_40 == 0) {
                    /* WARNING: Subroutine does not return */
                      __assert_fail("a_name_info->fs_name != NULL","exfatfs_dent.c",0x45,
                                    "void exfatfs_reset_name_info(EXFATFS_FS_NAME_INFO *)");
                    }
                    marker323._3248_8_ = "function_inlined: assert";
                    if (*(long *)(local_40 + 8) == 0) {
                    /* WARNING: Subroutine does not return */
                      __assert_fail("a_name_info->fs_name->name != NULL","exfatfs_dent.c",0x47,
                                    "void exfatfs_reset_name_info(EXFATFS_FS_NAME_INFO *)");
                    }
                    marker323._7632_8_ = "function_inlined: assert";
                    if (*(long *)(local_40 + 0x10) != 0x400) {
                    /* WARNING: Subroutine does not return */
                      __assert_fail("a_name_info->fs_name->name_size == FATFS_MAXNAMLEN_UTF8",
                                    "exfatfs_dent.c",0x49,
                                    "void exfatfs_reset_name_info(EXFATFS_FS_NAME_INFO *)");
                    }
                    local_48 = 0;
                    local_24f = 0;
                    **(undefined **)(local_40 + 8) = 0;
                    *(undefined8 *)(local_40 + 0x28) = 0;
                    *(undefined8 *)(local_40 + 0x50) = 0x100000000;
                    break;
                  }
                }
                else {
                  marker323._11080_8_ = "function_inlined: strcpy";
                  puVar2 = *(undefined4 **)(local_40 + 8);
                  *puVar2 = "$EMPTY_VOLUME_LABEL"._0_4_;
                  puVar2[1] = uVar11;
                  puVar2[2] = uVar4;
                  puVar2[3] = uVar5;
                  puVar2[4] = 0x4c4542;
                }
                lVar13 = local_40;
                local_48 = strlen(*(char **)(local_40 + 8));
                if (local_48 + 0x15 < 0x400) {
                  marker323._12472_8_ = "function_inlined: strcat";
                  __s = *(char **)(lVar13 + 8);
                  sVar10 = strlen(__s);
                  *(undefined8 *)(__s + sVar10 + 0xe) = 0x297972746e4520;
                  uVar5 = " (Volume Label Entry)"._12_4_;
                  uVar4 = " (Volume Label Entry)"._8_4_;
                  uVar11 = " (Volume Label Entry)"._4_4_;
                  *(undefined4 *)(__s + sVar10) = " (Volume Label Entry)"._0_4_;
                  *(undefined4 *)(__s + sVar10 + 4) = uVar11;
                  *(undefined4 *)(__s + sVar10 + 8) = uVar4;
                  *(undefined4 *)(__s + sVar10 + 0xc) = uVar5;
                  lVar13 = local_40;
                }
                *(long *)(lVar13 + 0x28) = lVar1;
                *(undefined4 *)(lVar13 + 0x50) = 5;
                if (local_250 != '\0') {
                  *(undefined4 *)(lVar13 + 0x54) = 1;
                }
                goto LAB_00100b3f;
              case 4:
              case 6:
              case 7:
              case 8:
              case 9:
              case 10:
              case 0xb:
              case 0xc:
              case 0xd:
              case 0xe:
              case 0xf:
              case 0x10:
              case 0x11:
              case 0x12:
              case 0x13:
              case 0x14:
              case 0x15:
              case 0x16:
              case 0x17:
              case 0x18:
              case 0x19:
              case 0x1a:
              case 0x1b:
              case 0x1c:
              case 0x1d:
              case 0x1e:
              case 0x1f:
              case 0x22:
              case 0x23:
              case 0x24:
              case 0x25:
              case 0x26:
              case 0x27:
              case 0x28:
              case 0x29:
              case 0x2a:
              case 0x2b:
              case 0x2c:
              case 0x2d:
              case 0x2e:
              case 0x2f:
              case 0x30:
              case 0x31:
              case 0x32:
              case 0x33:
              case 0x34:
              case 0x35:
              case 0x36:
              case 0x37:
              case 0x38:
              case 0x39:
              case 0x3a:
              case 0x3b:
              case 0x3c:
              case 0x3d:
              case 0x3e:
              case 0x3f:
LAB_0010037e:
                exfatfs_add_name_to_dir_and_reset_info(&local_258);
                break;
              case 5:
                marker323._14880_8_ = "function_inlined: assert";
                marker323._14672_8_ = "function_inlined: assert";
                if (local_258 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fatfs != NULL","exfatfs_dent.c",0x9c,
                                                                
                                "void exfats_parse_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._9632_8_ = "function_inlined: assert";
                if (local_40 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name != NULL","exfatfs_dent.c",0x9e,
                                                                
                                "void exfats_parse_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._14728_8_ = "function_inlined: assert";
                if (*(long *)(local_40 + 8) == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name->name != NULL","exfatfs_dent.c",0xa0,
                                                                
                                "void exfats_parse_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._9512_8_ = "function_inlined: assert";
                if (*(long *)(local_40 + 0x10) != 0x400) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name->name_size == FATFS_MAXNAMLEN_UTF8",
                                "exfatfs_dent.c",0xa2,
                                                                
                                "void exfats_parse_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._8248_8_ = "function_inlined: assert";
                if (local_38 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_dir != NULL","exfatfs_dent.c",0xa4,
                                                                
                                "void exfats_parse_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._15056_8_ = "function_inlined: assert";
                if (param_3 == (ushort *)0x0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("dentry != NULL","exfatfs_dent.c",0xa6,
                                                                
                                "void exfats_parse_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._15872_8_ = "function_inlined: assert";
                iVar8 = exfatfs_get_enum_from_type((ulong)*(byte *)param_3);
                if (iVar8 != 5) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail(
                                "exfatfs_get_enum_from_type(dentry->entry_type) == EXFATFS_DIR_ENTRY_TYPE_FILE"
                                ,"exfatfs_dent.c",0xa8,
                                                                
                                "void exfats_parse_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._7744_8_ = "function_inlined: assert";
                cVar6 = fatfs_inum_is_in_range(local_258);
                if (cVar6 == '\0') {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("fatfs_inum_is_in_range(a_name_info->fatfs, a_inum)",
                                "exfatfs_dent.c",0xaa,
                                                                
                                "void exfats_parse_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                exfatfs_add_name_to_dir_and_reset_info(&local_258);
                bVar17 = *(byte *)param_3;
                local_24f._0_3_ = (uint3)local_24f & 0xff0000 | (uint3)*param_3;
                uVar3 = (ulong)(*(int *)(local_258 + 0xb0) == 1);
                local_24f._0_5_ =
                     CONCAT23(CONCAT11(*(undefined *)((long)param_3 + uVar3 + 2),
                                       *(undefined *)((long)param_3 + (3 - uVar3))),(uint3)local_24f
                             );
                local_24f = local_24f & 0xffffff0000000000 | (ulong)(uint5)local_24f;
                bVar18 = (*(byte *)(param_3 + 2) & 0x10) == 0;
                *(int *)(local_40 + 0x50) = (uint)bVar18 + (uint)bVar18 + 3;
                if (local_250 == '\0') {
LAB_0010052f:
                  uVar11 = 2;
                }
                else {
                  cVar6 = exfatfs_get_alloc_status_from_type((ulong)bVar17);
                  uVar11 = 1;
                  if (cVar6 == '\0') goto LAB_0010052f;
                }
                *(undefined4 *)(local_40 + 0x54) = uVar11;
                *(long *)(local_40 + 0x28) = lVar1;
                break;
              case 0x40:
                marker323._3152_8_ = "function_inlined: assert";
                marker323._14016_8_ = "function_inlined: assert";
                if (local_258 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fatfs != NULL","exfatfs_dent.c",0xe1,
                                                                
                                "void exfats_parse_file_stream_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._11240_8_ = "function_inlined: assert";
                if (local_40 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name != NULL","exfatfs_dent.c",0xe3,
                                                                
                                "void exfats_parse_file_stream_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._6320_8_ = "function_inlined: assert";
                if (*(long *)(local_40 + 8) == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name->name != NULL","exfatfs_dent.c",0xe5,
                                                                
                                "void exfats_parse_file_stream_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._8896_8_ = "function_inlined: assert";
                if (*(long *)(local_40 + 0x10) != 0x400) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name->name_size == FATFS_MAXNAMLEN_UTF8",
                                "exfatfs_dent.c",0xe7,
                                                                
                                "void exfats_parse_file_stream_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._10632_8_ = "function_inlined: assert";
                if (local_38 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_dir != NULL","exfatfs_dent.c",0xe9,
                                                                
                                "void exfats_parse_file_stream_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._6440_8_ = "function_inlined: assert";
                if (param_3 == (ushort *)0x0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("dentry != NULL","exfatfs_dent.c",0xeb,
                                                                
                                "void exfats_parse_file_stream_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._13480_8_ = "function_inlined: assert";
                iVar8 = exfatfs_get_enum_from_type((ulong)*(byte *)param_3);
                if (iVar8 != 0x40) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail(
                                "exfatfs_get_enum_from_type(dentry->entry_type) == EXFATFS_DIR_ENTRY_TYPE_FILE_STREAM"
                                ,"exfatfs_dent.c",0xed,
                                                                
                                "void exfats_parse_file_stream_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._4952_8_ = "function_inlined: assert";
                cVar6 = fatfs_inum_is_in_range(local_258);
                if (cVar6 == '\0') {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("fatfs_inum_is_in_range(a_name_info->fatfs, a_inum)",
                                "exfatfs_dent.c",0xef,
                                                                
                                "void exfats_parse_file_stream_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                iVar8 = exfatfs_get_enum_from_type(local_24f & 0xff);
                if (iVar8 != 5) goto LAB_00100b3f;
                cVar6 = exfatfs_get_alloc_status_from_type(local_24f & 0xff);
                cVar7 = exfatfs_get_alloc_status_from_type((ulong)*(byte *)param_3);
                if (cVar6 != cVar7) goto LAB_00100b3f;
                local_24f._0_5_ = (uint5)local_24f & 0xffffffff00 | (uint5)*(byte *)param_3;
                local_24f._0_6_ = CONCAT15(*(byte *)((long)param_3 + 3),(uint5)local_24f);
                local_24f._2_1_ = (char)((ulong)(uint6)local_24f >> 0x10);
                local_24f._0_3_ = CONCAT12(local_24f._2_1_ + '\x01',(undefined2)local_24f);
                local_24f = local_24f & 0xffff000000000000 |
                            (ulong)(uint6)local_24f & 0xffffffffff000000 | (ulong)(uint3)local_24f;
                local_24f._1_1_ = (char)((ulong)(uint3)local_24f >> 8);
                if ((char)(local_24f._2_1_ + '\x01') != local_24f._1_1_) break;
                goto LAB_00100a91;
              case 0x41:
                marker323._48_8_ = "function_inlined: assert";
                marker323._9736_8_ = "function_inlined: assert";
                if (local_258 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fatfs != NULL","exfatfs_dent.c",0x127,
                                                                
                                "void exfats_parse_file_name_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._10520_8_ = "function_inlined: assert";
                if (local_40 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name != NULL","exfatfs_dent.c",0x129,
                                                                
                                "void exfats_parse_file_name_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._1248_8_ = "function_inlined: assert";
                if (*(long *)(local_40 + 8) == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name->name != NULL","exfatfs_dent.c",299,
                                                                
                                "void exfats_parse_file_name_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._8320_8_ = "function_inlined: assert";
                if (*(long *)(local_40 + 0x10) != 0x400) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_name->name_size == FATFS_MAXNAMLEN_UTF8",
                                "exfatfs_dent.c",0x12d,
                                                                
                                "void exfats_parse_file_name_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._5360_8_ = "function_inlined: assert";
                if (local_38 == 0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("a_name_info->fs_dir != NULL","exfatfs_dent.c",0x12f,
                                                                
                                "void exfats_parse_file_name_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._9944_8_ = "function_inlined: assert";
                if (param_3 == (ushort *)0x0) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("dentry != NULL","exfatfs_dent.c",0x131,
                                                                
                                "void exfats_parse_file_name_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._12528_8_ = "function_inlined: assert";
                iVar8 = exfatfs_get_enum_from_type((ulong)*(byte *)param_3);
                if (iVar8 != 0x41) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail(
                                "exfatfs_get_enum_from_type(dentry->entry_type) == EXFATFS_DIR_ENTRY_TYPE_FILE_NAME"
                                ,"exfatfs_dent.c",0x133,
                                                                
                                "void exfats_parse_file_name_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                marker323._3664_8_ = "function_inlined: assert";
                cVar6 = fatfs_inum_is_in_range(local_258);
                if (cVar6 == '\0') {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("fatfs_inum_is_in_range(a_name_info->fatfs, a_inum)",
                                "exfatfs_dent.c",0x135,
                                                                
                                "void exfats_parse_file_name_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                               );
                }
                iVar8 = exfatfs_get_enum_from_type(local_24f & 0xff);
                if ((iVar8 == 0x40) ||
                   (iVar8 = exfatfs_get_enum_from_type(local_24f & 0xff), iVar8 == 0x41)) {
                  cVar6 = exfatfs_get_alloc_status_from_type(local_24f & 0xff);
                  cVar7 = exfatfs_get_alloc_status_from_type((ulong)*(byte *)param_3);
                  if (cVar6 == cVar7) {
                    uVar3 = local_24f & 0xffffffffffffff00;
                    local_24f = uVar3 | *(byte *)param_3;
                    local_24f._5_1_ = (char)(uVar3 >> 0x28);
                    local_24f._6_1_ = (byte)(uVar3 >> 0x30);
                    bVar17 = local_24f._5_1_ - local_24f._6_1_;
                    if (0xe < bVar17) {
                      bVar17 = 0xf;
                    }
                    if (bVar17 <= (local_24f._6_1_ ^ 0xff)) {
                      memcpy((void *)((long)&local_24f + (ulong)local_24f._6_1_ * 2 + 7),param_3 + 1
                             ,(ulong)(byte)(bVar17 * '\x02'));
                      local_24f._0_7_ = CONCAT16(local_24f._6_1_ + bVar17,(uint6)local_24f);
                      local_24f = local_24f & 0xff00000000000000 | (ulong)(uint7)local_24f;
                    }
                    local_24f._0_3_ = CONCAT12(local_24f._2_1_ + '\x01',(undefined2)local_24f);
                    local_24f = local_24f & 0xffffffffff000000 | (ulong)(uint3)local_24f;
                    local_24f._1_1_ = (char)((ulong)(uint3)local_24f >> 8);
                    if ((char)(local_24f._2_1_ + '\x01') != local_24f._1_1_) break;
                  }
                }
LAB_00100b3f:
                exfatfs_add_name_to_dir_and_reset_info(&local_258);
                break;
              default:
                if (iVar8 != 0x62) goto LAB_0010037e;
                goto switchD_0010021f_caseD_1;
              }
              goto LAB_00100b4e;
            }
          }
LAB_00100bb4:
          lVar12 = lVar12 + 1;
        } while (lVar12 < param_4);
      }
      exfatfs_add_name_to_dir_and_reset_info(&local_258);
      tsk_fs_name_free(local_40);
      uVar16 = 0;
    }
  }
  return uVar16;
switchD_0010021f_caseD_1:
  marker323._544_8_ = "function_inlined: assert";
  marker323._3768_8_ = "function_inlined: assert";
  if (local_258 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fatfs != NULL","exfatfs_dent.c",0x1cc,
                                    
                  "void exfats_parse_special_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                 );
  }
  marker323._7376_8_ = "function_inlined: assert";
  if (local_40 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fs_name != NULL","exfatfs_dent.c",0x1ce,
                                    
                  "void exfats_parse_special_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                 );
  }
  marker323._3328_8_ = "function_inlined: assert";
  if (*(long *)(local_40 + 8) == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fs_name->name != NULL","exfatfs_dent.c",0x1d0,
                                    
                  "void exfats_parse_special_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                 );
  }
  marker323._12072_8_ = "function_inlined: assert";
  if (*(long *)(local_40 + 0x10) != 0x400) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fs_name->name_size == FATFS_MAXNAMLEN_UTF8","exfatfs_dent.c",0x1d2,
                                    
                  "void exfats_parse_special_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                 );
  }
  marker323._15920_8_ = "function_inlined: assert";
  if (local_38 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fs_dir != NULL","exfatfs_dent.c",0x1d4,
                                    
                  "void exfats_parse_special_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                 );
  }
  marker323._13808_8_ = "function_inlined: assert";
  if (param_3 == (ushort *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_dentry != NULL","exfatfs_dent.c",0x1d6,
                                    
                  "void exfats_parse_special_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                 );
  }
  marker323._14536_8_ = "function_inlined: assert";
  cVar6 = fatfs_inum_is_in_range();
  if (cVar6 == '\0') {
                    /* WARNING: Subroutine does not return */
    __assert_fail("fatfs_inum_is_in_range(a_name_info->fatfs, a_inum)","exfatfs_dent.c",0x1d8,
                                    
                  "void exfats_parse_special_file_dentry(EXFATFS_FS_NAME_INFO *, FATFS_DENTRY *, TSK_INUM_T)"
                 );
  }
  exfatfs_add_name_to_dir_and_reset_info();
  *(long *)(local_40 + 0x28) = lVar1;
  local_24f = local_24f & 0xffffffffffffff00 | (ulong)*(byte *)param_3;
  iVar8 = exfatfs_get_enum_from_type();
  uVar5 = "$ACCESS_CONTROL_TABLE"._12_4_;
  uVar4 = "$ACCESS_CONTROL_TABLE"._8_4_;
  uVar11 = "$ACCESS_CONTROL_TABLE"._4_4_;
  switch(iVar8) {
  case 1:
    marker323._14664_8_ = "function_inlined: strcpy";
    puVar9 = *(undefined8 **)(local_40 + 8);
    *(undefined8 *)((long)puVar9 + 6) = 0x50414d5449425f;
    uVar16 = 0x425f434f4c4c4124;
    goto LAB_00100a71;
  case 2:
    marker323._11816_8_ = "function_inlined: strcpy";
    puVar9 = *(undefined8 **)(local_40 + 8);
    *(undefined8 *)((long)puVar9 + 6) = 0x454c4241545f45;
    uVar16 = 0x5f45534143505524;
    goto LAB_00100a71;
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
switchD_00100313_caseD_3:
    **(undefined **)(local_40 + 8) = 0;
    break;
  case 0x20:
    marker323._1216_8_ = "function_inlined: strcpy";
    puVar9 = *(undefined8 **)(local_40 + 8);
    *(undefined8 *)((long)puVar9 + 5) = 0x444955475f454d;
    uVar16 = 0x5f454d554c4f5624;
LAB_00100a71:
    *puVar9 = uVar16;
    break;
  case 0x21:
    marker323._6056_8_ = "function_inlined: strcpy";
    puVar9 = *(undefined8 **)(local_40 + 8);
    *puVar9 = 0x5441465f58455424;
    *(undefined *)(puVar9 + 1) = 0;
    break;
  default:
    if (iVar8 != 0x62) goto switchD_00100313_caseD_3;
    marker323._3744_8_ = "function_inlined: strcpy";
    puVar2 = *(undefined4 **)(local_40 + 8);
    *puVar2 = "$ACCESS_CONTROL_TABLE"._0_4_;
    puVar2[1] = uVar11;
    puVar2[2] = uVar4;
    puVar2[3] = uVar5;
    *(undefined8 *)((long)puVar2 + 0xe) = 0x454c4241545f4c;
  }
  *(undefined4 *)(local_40 + 0x50) = 5;
  if (local_250 != '\0') {
    *(undefined4 *)(local_40 + 0x54) = 1;
  }
LAB_00100a91:
  exfatfs_add_name_to_dir_and_reset_info(&local_258);
LAB_00100b4e:
  uVar14 = uVar14 + 1;
  param_3 = param_3 + 0x10;
  if (*(uint *)(param_1 + 0x4228) <= uVar14) goto LAB_00100bb4;
  goto LAB_001001c1;
}


void exfatfs_add_name_to_dir_and_reset_info(undefined8 *param_1)

{
  long lVar1;
  
  marker323._11216_8_ = "function_inlined: assert";
  if (param_1 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info != NULL","exfatfs_dent.c",0x66,
                  "void exfatfs_add_name_to_dir_and_reset_info(EXFATFS_FS_NAME_INFO *)");
  }
  marker323._9960_8_ = "function_inlined: assert";
  if (param_1[0x43] == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fs_name != NULL","exfatfs_dent.c",0x68,
                  "void exfatfs_add_name_to_dir_and_reset_info(EXFATFS_FS_NAME_INFO *)");
  }
  marker323._13096_8_ = "function_inlined: assert";
  if (*(long *)(param_1[0x43] + 8) == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fs_name->name != NULL","exfatfs_dent.c",0x6a,
                  "void exfatfs_add_name_to_dir_and_reset_info(EXFATFS_FS_NAME_INFO *)");
  }
  marker323._10816_8_ = "function_inlined: assert";
  if (*(long *)(param_1[0x43] + 0x10) == 0x400) {
    marker323._13080_8_ = "function_inlined: assert";
    if (param_1[0x44] != 0) {
      marker323._6008_8_ = "function_inlined: strlen";
      lVar1 = param_1[0x43];
      if ((**(char **)(lVar1 + 8) == '\0') && (*(byte *)((long)param_1 + 0xf) != 0)) {
        fatfs_utf16_inode_str_2_utf8
                  (*param_1,param_1 + 2,(ulong)*(byte *)((long)param_1 + 0xf),*(char **)(lVar1 + 8),
                   *(undefined8 *)(lVar1 + 0x10),*(undefined8 *)(lVar1 + 0x28),"file name segment");
      }
      marker323._2344_8_ = "function_inlined: strlen";
      if (**(char **)(param_1[0x43] + 8) != '\0') {
        tsk_fs_dir_add(param_1[0x44]);
      }
      exfatfs_reset_name_info(param_1);
      return;
    }
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fs_dir != NULL","exfatfs_dent.c",0x6e,
                  "void exfatfs_add_name_to_dir_and_reset_info(EXFATFS_FS_NAME_INFO *)");
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("a_name_info->fs_name->name_size == FATFS_MAXNAMLEN_UTF8","exfatfs_dent.c",0x6c,
                "void exfatfs_add_name_to_dir_and_reset_info(EXFATFS_FS_NAME_INFO *)");
}


undefined8 exfatfs_reset_name_info(long param_1)

{
  long lVar1;
  undefined8 in_RAX;
  
  marker323._10232_8_ = "function_inlined: assert";
  if (param_1 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info != NULL","exfatfs_dent.c",0x43,
                  "void exfatfs_reset_name_info(EXFATFS_FS_NAME_INFO *)");
  }
  marker323._13848_8_ = "function_inlined: assert";
  if (*(long *)(param_1 + 0x218) == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fs_name != NULL","exfatfs_dent.c",0x45,
                  "void exfatfs_reset_name_info(EXFATFS_FS_NAME_INFO *)");
  }
  marker323._3248_8_ = "function_inlined: assert";
  if (*(long *)(*(long *)(param_1 + 0x218) + 8) == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("a_name_info->fs_name->name != NULL","exfatfs_dent.c",0x47,
                  "void exfatfs_reset_name_info(EXFATFS_FS_NAME_INFO *)");
  }
  marker323._7632_8_ = "function_inlined: assert";
  if (*(long *)(*(long *)(param_1 + 0x218) + 0x10) == 0x400) {
    *(undefined8 *)(param_1 + 0x210) = 0;
    *(undefined8 *)(param_1 + 9) = 0;
    **(undefined **)(*(long *)(param_1 + 0x218) + 8) = 0;
    lVar1 = *(long *)(param_1 + 0x218);
    *(undefined8 *)(lVar1 + 0x28) = 0;
    *(undefined8 *)(lVar1 + 0x50) = 0x100000000;
    return in_RAX;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("a_name_info->fs_name->name_size == FATFS_MAXNAMLEN_UTF8","exfatfs_dent.c",0x49,
                "void exfatfs_reset_name_info(EXFATFS_FS_NAME_INFO *)");
}


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention yet parameter storage is locked */

void __assert_fail(char *__assertion,char *__file,uint __line,char *__function)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void exfatfs_get_alloc_status_from_type(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void exfatfs_get_enum_from_type(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void exfatfs_is_dentry(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void fatfs_inum_is_in_range(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void fatfs_is_sectalloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void fatfs_ptr_arg_is_null(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void fatfs_utf16_inode_str_2_utf8(void)

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

void * memset(void *__s,int __c,size_t __n)

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

void tsk_fprintf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_dir_add(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_name_alloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* WARNING: Control flow encountered bad instruction data */

void tsk_fs_name_free(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


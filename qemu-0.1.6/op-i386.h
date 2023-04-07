/* i386字节码生成
 * @param opc_buf 操作码信息
 * @param opparam_buf 参数信息
 */
int dyngen_code(uint8_t *gen_code_buf,
                const uint16_t *opc_buf, const uint32_t *opparam_buf)
{
    uint8_t *gen_code_ptr;
    const uint16_t *opc_ptr;
    const uint32_t *opparam_ptr;
    gen_code_ptr = gen_code_buf;
    opc_ptr = opc_buf;
    opparam_ptr = opparam_buf;
    for(;;)
    {
        switch(*opc_ptr++)
        {
            case INDEX_op_movl_A0_EAX:
            {
                extern void op_movl_A0_EAX();
                /* 我很好奇,这里为什么是3,在32位系统下面,一个指针,应当有4个字节
                 * op_movl_A0_EAX的汇编实现如下,确实用了3个字节
                 * 0002b558 <op_movl_A0_EAX>:
                 * 2b558:	8b 7d 00             	mov    0x0(%ebp),%edi
                 * 2b55b:	c3                   	ret 
                 */
                memcpy(gen_code_ptr, &op_movl_A0_EAX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EAX:
            {
                extern void op_addl_A0_EAX();
                /* 拷贝生成的i386字节码 */
                memcpy(gen_code_ptr, &op_addl_A0_EAX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EAX_s1:
            {
                extern void op_addl_A0_EAX_s1();
                memcpy(gen_code_ptr, &op_addl_A0_EAX_s1, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EAX_s2:
            {
                extern void op_addl_A0_EAX_s2();
                memcpy(gen_code_ptr, &op_addl_A0_EAX_s2, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EAX_s3:
            {
                extern void op_addl_A0_EAX_s3();
                memcpy(gen_code_ptr, &op_addl_A0_EAX_s3, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_movl_T0_EAX:
            {
                extern void op_movl_T0_EAX();
                memcpy(gen_code_ptr, &op_movl_T0_EAX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_T1_EAX:
            {
                extern void op_movl_T1_EAX();
                memcpy(gen_code_ptr, &op_movl_T1_EAX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_T0_EAX:
            {
                extern void op_movh_T0_EAX();
                memcpy(gen_code_ptr, &op_movh_T0_EAX, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movh_T1_EAX:
            {
                extern void op_movh_T1_EAX();
                memcpy(gen_code_ptr, &op_movh_T1_EAX, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movl_EAX_T0:
            {
                extern void op_movl_EAX_T0();
                memcpy(gen_code_ptr, &op_movl_EAX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EAX_T1:
            {
                extern void op_movl_EAX_T1();
                memcpy(gen_code_ptr, &op_movl_EAX_T1, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EAX_A0:
            {
                extern void op_movl_EAX_A0();
                memcpy(gen_code_ptr, &op_movl_EAX_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_cmovw_EAX_T1_T0:
            {
                extern void op_cmovw_EAX_T1_T0();
                memcpy(gen_code_ptr, &op_cmovw_EAX_T1_T0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cmovl_EAX_T1_T0:
            {
                extern void op_cmovl_EAX_T1_T0();
                memcpy(gen_code_ptr, &op_cmovl_EAX_T1_T0, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movw_EAX_T0:
            {
                extern void op_movw_EAX_T0();
                memcpy(gen_code_ptr, &op_movw_EAX_T0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EAX_T1:
            {
                extern void op_movw_EAX_T1();
                memcpy(gen_code_ptr, &op_movw_EAX_T1, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EAX_A0:
            {
                extern void op_movw_EAX_A0();
                memcpy(gen_code_ptr, &op_movw_EAX_A0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movb_EAX_T0:
            {
                extern void op_movb_EAX_T0();
                memcpy(gen_code_ptr, &op_movb_EAX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_EAX_T0:
            {
                extern void op_movh_EAX_T0();
                memcpy(gen_code_ptr, &op_movh_EAX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movb_EAX_T1:
            {
                extern void op_movb_EAX_T1();
                memcpy(gen_code_ptr, &op_movb_EAX_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movh_EAX_T1:
            {
                extern void op_movh_EAX_T1();
				/* 其实我有一个疑问,那就是,为什么这里要拷贝5个字节 */
                memcpy(gen_code_ptr, &op_movh_EAX_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movl_A0_ECX:
            {
                extern void op_movl_A0_ECX();
                memcpy(gen_code_ptr, &op_movl_A0_ECX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_ECX:
            {
                extern void op_addl_A0_ECX();
                memcpy(gen_code_ptr, &op_addl_A0_ECX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_ECX_s1:
            {
                extern void op_addl_A0_ECX_s1();
                memcpy(gen_code_ptr, &op_addl_A0_ECX_s1, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_ECX_s2:
            {
                extern void op_addl_A0_ECX_s2();
                memcpy(gen_code_ptr, &op_addl_A0_ECX_s2, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_ECX_s3:
            {
                extern void op_addl_A0_ECX_s3();
                memcpy(gen_code_ptr, &op_addl_A0_ECX_s3, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_movl_T0_ECX:
            {
                extern void op_movl_T0_ECX();
                memcpy(gen_code_ptr, &op_movl_T0_ECX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_T1_ECX:
            {
                extern void op_movl_T1_ECX();
                memcpy(gen_code_ptr, &op_movl_T1_ECX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_T0_ECX:
            {
                extern void op_movh_T0_ECX();
                memcpy(gen_code_ptr, &op_movh_T0_ECX, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movh_T1_ECX:
            {
                extern void op_movh_T1_ECX();
                memcpy(gen_code_ptr, &op_movh_T1_ECX, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movl_ECX_T0:
            {
                extern void op_movl_ECX_T0();
                memcpy(gen_code_ptr, &op_movl_ECX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_ECX_T1:
            {
                extern void op_movl_ECX_T1();
                memcpy(gen_code_ptr, &op_movl_ECX_T1, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_ECX_A0:
            {
                extern void op_movl_ECX_A0();
                memcpy(gen_code_ptr, &op_movl_ECX_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_cmovw_ECX_T1_T0:
            {
                extern void op_cmovw_ECX_T1_T0();
                memcpy(gen_code_ptr, &op_cmovw_ECX_T1_T0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cmovl_ECX_T1_T0:
            {
                extern void op_cmovl_ECX_T1_T0();
                memcpy(gen_code_ptr, &op_cmovl_ECX_T1_T0, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movw_ECX_T0:
            {
                extern void op_movw_ECX_T0();
                memcpy(gen_code_ptr, &op_movw_ECX_T0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_ECX_T1:
            {
                extern void op_movw_ECX_T1();
                memcpy(gen_code_ptr, &op_movw_ECX_T1, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_ECX_A0:
            {
                extern void op_movw_ECX_A0();
                memcpy(gen_code_ptr, &op_movw_ECX_A0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movb_ECX_T0:
            {
                extern void op_movb_ECX_T0();
                memcpy(gen_code_ptr, &op_movb_ECX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_ECX_T0:
            {
                extern void op_movh_ECX_T0();
                memcpy(gen_code_ptr, &op_movh_ECX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movb_ECX_T1:
            {
                extern void op_movb_ECX_T1();
                memcpy(gen_code_ptr, &op_movb_ECX_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movh_ECX_T1:
            {
                extern void op_movh_ECX_T1();
                memcpy(gen_code_ptr, &op_movh_ECX_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movl_A0_EDX:
            {
                extern void op_movl_A0_EDX();
                memcpy(gen_code_ptr, &op_movl_A0_EDX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EDX:
            {
                extern void op_addl_A0_EDX();
                memcpy(gen_code_ptr, &op_addl_A0_EDX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EDX_s1:
            {
                extern void op_addl_A0_EDX_s1();
                memcpy(gen_code_ptr, &op_addl_A0_EDX_s1, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EDX_s2:
            {
                extern void op_addl_A0_EDX_s2();
                memcpy(gen_code_ptr, &op_addl_A0_EDX_s2, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EDX_s3:
            {
                extern void op_addl_A0_EDX_s3();
                memcpy(gen_code_ptr, &op_addl_A0_EDX_s3, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_movl_T0_EDX:
            {
                extern void op_movl_T0_EDX();
                memcpy(gen_code_ptr, &op_movl_T0_EDX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_T1_EDX:
            {
                extern void op_movl_T1_EDX();
                memcpy(gen_code_ptr, &op_movl_T1_EDX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_T0_EDX:
            {
                extern void op_movh_T0_EDX();
                memcpy(gen_code_ptr, &op_movh_T0_EDX, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movh_T1_EDX:
            {
                extern void op_movh_T1_EDX();
                memcpy(gen_code_ptr, &op_movh_T1_EDX, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movl_EDX_T0:
            {
                extern void op_movl_EDX_T0();
                memcpy(gen_code_ptr, &op_movl_EDX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EDX_T1:
            {
                extern void op_movl_EDX_T1();
                memcpy(gen_code_ptr, &op_movl_EDX_T1, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EDX_A0:
            {
                extern void op_movl_EDX_A0();
                memcpy(gen_code_ptr, &op_movl_EDX_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_cmovw_EDX_T1_T0:
            {
                extern void op_cmovw_EDX_T1_T0();
                memcpy(gen_code_ptr, &op_cmovw_EDX_T1_T0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cmovl_EDX_T1_T0:
            {
                extern void op_cmovl_EDX_T1_T0();
                memcpy(gen_code_ptr, &op_cmovl_EDX_T1_T0, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movw_EDX_T0:
            {
                extern void op_movw_EDX_T0();
                memcpy(gen_code_ptr, &op_movw_EDX_T0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EDX_T1:
            {
                extern void op_movw_EDX_T1();
                memcpy(gen_code_ptr, &op_movw_EDX_T1, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EDX_A0:
            {
                extern void op_movw_EDX_A0();
                memcpy(gen_code_ptr, &op_movw_EDX_A0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movb_EDX_T0:
            {
                extern void op_movb_EDX_T0();
                memcpy(gen_code_ptr, &op_movb_EDX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_EDX_T0:
            {
                extern void op_movh_EDX_T0();
                memcpy(gen_code_ptr, &op_movh_EDX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movb_EDX_T1:
            {
                extern void op_movb_EDX_T1();
                memcpy(gen_code_ptr, &op_movb_EDX_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movh_EDX_T1:
            {
                extern void op_movh_EDX_T1();
                memcpy(gen_code_ptr, &op_movh_EDX_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movl_A0_EBX:
            {
                extern void op_movl_A0_EBX();
                memcpy(gen_code_ptr, &op_movl_A0_EBX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EBX:
            {
                extern void op_addl_A0_EBX();
                memcpy(gen_code_ptr, &op_addl_A0_EBX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EBX_s1:
            {
                extern void op_addl_A0_EBX_s1();
                memcpy(gen_code_ptr, &op_addl_A0_EBX_s1, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EBX_s2:
            {
                extern void op_addl_A0_EBX_s2();
                memcpy(gen_code_ptr, &op_addl_A0_EBX_s2, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EBX_s3:
            {
                extern void op_addl_A0_EBX_s3();
                memcpy(gen_code_ptr, &op_addl_A0_EBX_s3, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_movl_T0_EBX:
            {
                extern void op_movl_T0_EBX();
                memcpy(gen_code_ptr, &op_movl_T0_EBX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_T1_EBX:
            {
                extern void op_movl_T1_EBX();
                memcpy(gen_code_ptr, &op_movl_T1_EBX, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_T0_EBX:
            {
                extern void op_movh_T0_EBX();
                memcpy(gen_code_ptr, &op_movh_T0_EBX, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movh_T1_EBX:
            {
                extern void op_movh_T1_EBX();
                memcpy(gen_code_ptr, &op_movh_T1_EBX, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movl_EBX_T0:
            {
                extern void op_movl_EBX_T0();
                memcpy(gen_code_ptr, &op_movl_EBX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EBX_T1:
            {
                extern void op_movl_EBX_T1();
                memcpy(gen_code_ptr, &op_movl_EBX_T1, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EBX_A0:
            {
                extern void op_movl_EBX_A0();
                memcpy(gen_code_ptr, &op_movl_EBX_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_cmovw_EBX_T1_T0:
            {
                extern void op_cmovw_EBX_T1_T0();
                memcpy(gen_code_ptr, &op_cmovw_EBX_T1_T0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cmovl_EBX_T1_T0:
            {
                extern void op_cmovl_EBX_T1_T0();
                memcpy(gen_code_ptr, &op_cmovl_EBX_T1_T0, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movw_EBX_T0:
            {
                extern void op_movw_EBX_T0();
                memcpy(gen_code_ptr, &op_movw_EBX_T0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EBX_T1:
            {
                extern void op_movw_EBX_T1();
                memcpy(gen_code_ptr, &op_movw_EBX_T1, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EBX_A0:
            {
                extern void op_movw_EBX_A0();
                memcpy(gen_code_ptr, &op_movw_EBX_A0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movb_EBX_T0:
            {
                extern void op_movb_EBX_T0();
                memcpy(gen_code_ptr, &op_movb_EBX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_EBX_T0:
            {
                extern void op_movh_EBX_T0();
                memcpy(gen_code_ptr, &op_movh_EBX_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movb_EBX_T1:
            {
                extern void op_movb_EBX_T1();
                memcpy(gen_code_ptr, &op_movb_EBX_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movh_EBX_T1:
            {
                extern void op_movh_EBX_T1();
                memcpy(gen_code_ptr, &op_movh_EBX_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movl_A0_ESP:
            {
                extern void op_movl_A0_ESP();
                memcpy(gen_code_ptr, &op_movl_A0_ESP, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_ESP:
            {
                extern void op_addl_A0_ESP();
                memcpy(gen_code_ptr, &op_addl_A0_ESP, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_ESP_s1:
            {
                extern void op_addl_A0_ESP_s1();
                memcpy(gen_code_ptr, &op_addl_A0_ESP_s1, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_ESP_s2:
            {
                extern void op_addl_A0_ESP_s2();
                memcpy(gen_code_ptr, &op_addl_A0_ESP_s2, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_ESP_s3:
            {
                extern void op_addl_A0_ESP_s3();
                memcpy(gen_code_ptr, &op_addl_A0_ESP_s3, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_movl_T0_ESP:
            {
                extern void op_movl_T0_ESP();
                memcpy(gen_code_ptr, &op_movl_T0_ESP, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_T1_ESP:
            {
                extern void op_movl_T1_ESP();
                memcpy(gen_code_ptr, &op_movl_T1_ESP, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_T0_ESP:
            {
                extern void op_movh_T0_ESP();
                memcpy(gen_code_ptr, &op_movh_T0_ESP, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movh_T1_ESP:
            {
                extern void op_movh_T1_ESP();
                memcpy(gen_code_ptr, &op_movh_T1_ESP, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movl_ESP_T0:
            {
                extern void op_movl_ESP_T0();
                memcpy(gen_code_ptr, &op_movl_ESP_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_ESP_T1:
            {
                extern void op_movl_ESP_T1();
                memcpy(gen_code_ptr, &op_movl_ESP_T1, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_ESP_A0:
            {
                extern void op_movl_ESP_A0();
                memcpy(gen_code_ptr, &op_movl_ESP_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_cmovw_ESP_T1_T0:
            {
                extern void op_cmovw_ESP_T1_T0();
                memcpy(gen_code_ptr, &op_cmovw_ESP_T1_T0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cmovl_ESP_T1_T0:
            {
                extern void op_cmovl_ESP_T1_T0();
                memcpy(gen_code_ptr, &op_cmovl_ESP_T1_T0, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movw_ESP_T0:
            {
                extern void op_movw_ESP_T0();
                memcpy(gen_code_ptr, &op_movw_ESP_T0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_ESP_T1:
            {
                extern void op_movw_ESP_T1();
                memcpy(gen_code_ptr, &op_movw_ESP_T1, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_ESP_A0:
            {
                extern void op_movw_ESP_A0();
                memcpy(gen_code_ptr, &op_movw_ESP_A0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movb_ESP_T0:
            {
                extern void op_movb_ESP_T0();
                memcpy(gen_code_ptr, &op_movb_ESP_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_ESP_T0:
            {
                extern void op_movh_ESP_T0();
                memcpy(gen_code_ptr, &op_movh_ESP_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movb_ESP_T1:
            {
                extern void op_movb_ESP_T1();
                memcpy(gen_code_ptr, &op_movb_ESP_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movh_ESP_T1:
            {
                extern void op_movh_ESP_T1();
                memcpy(gen_code_ptr, &op_movh_ESP_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movl_A0_EBP:
            {
                extern void op_movl_A0_EBP();
                memcpy(gen_code_ptr, &op_movl_A0_EBP, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EBP:
            {
                extern void op_addl_A0_EBP();
                memcpy(gen_code_ptr, &op_addl_A0_EBP, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EBP_s1:
            {
                extern void op_addl_A0_EBP_s1();
                memcpy(gen_code_ptr, &op_addl_A0_EBP_s1, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EBP_s2:
            {
                extern void op_addl_A0_EBP_s2();
                memcpy(gen_code_ptr, &op_addl_A0_EBP_s2, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EBP_s3:
            {
                extern void op_addl_A0_EBP_s3();
                memcpy(gen_code_ptr, &op_addl_A0_EBP_s3, 6);
                gen_code_ptr += 6;
            }
            break;
            /* 这里摘录一下op_movl_T0_EBP的实现,用了3个字节来编码 
             * 0002b848 <op_movl_T0_EBP>:
             * 2b848:	8b 5d 14             	mov    0x14(%ebp),%ebx
             * 2b84b:	c3                   	ret  
             */
            case INDEX_op_movl_T0_EBP:
            {
                extern void op_movl_T0_EBP();
                memcpy(gen_code_ptr, &op_movl_T0_EBP, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_T1_EBP:
            {
                extern void op_movl_T1_EBP();
                memcpy(gen_code_ptr, &op_movl_T1_EBP, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_T0_EBP:
            {
                extern void op_movh_T0_EBP();
                memcpy(gen_code_ptr, &op_movh_T0_EBP, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movh_T1_EBP:
            {
                extern void op_movh_T1_EBP();
                memcpy(gen_code_ptr, &op_movh_T1_EBP, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movl_EBP_T0:
            {
                extern void op_movl_EBP_T0();
                memcpy(gen_code_ptr, &op_movl_EBP_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EBP_T1:
            {
                extern void op_movl_EBP_T1();
                memcpy(gen_code_ptr, &op_movl_EBP_T1, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EBP_A0:
            {
                extern void op_movl_EBP_A0();
                memcpy(gen_code_ptr, &op_movl_EBP_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_cmovw_EBP_T1_T0:
            {
                extern void op_cmovw_EBP_T1_T0();
                memcpy(gen_code_ptr, &op_cmovw_EBP_T1_T0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cmovl_EBP_T1_T0:
            {
                extern void op_cmovl_EBP_T1_T0();
                memcpy(gen_code_ptr, &op_cmovl_EBP_T1_T0, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movw_EBP_T0:
            {
                extern void op_movw_EBP_T0();
                memcpy(gen_code_ptr, &op_movw_EBP_T0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EBP_T1:
            {
                extern void op_movw_EBP_T1();
                memcpy(gen_code_ptr, &op_movw_EBP_T1, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EBP_A0:
            {
                extern void op_movw_EBP_A0();
                memcpy(gen_code_ptr, &op_movw_EBP_A0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movb_EBP_T0:
            {
                extern void op_movb_EBP_T0();
                memcpy(gen_code_ptr, &op_movb_EBP_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_EBP_T0:
            {
                extern void op_movh_EBP_T0();
                memcpy(gen_code_ptr, &op_movh_EBP_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movb_EBP_T1:
            {
                extern void op_movb_EBP_T1();
                memcpy(gen_code_ptr, &op_movb_EBP_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movh_EBP_T1:
            {
                extern void op_movh_EBP_T1();
                memcpy(gen_code_ptr, &op_movh_EBP_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movl_A0_ESI:
            {
                extern void op_movl_A0_ESI();
                memcpy(gen_code_ptr, &op_movl_A0_ESI, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_ESI:
            {
                extern void op_addl_A0_ESI();
                memcpy(gen_code_ptr, &op_addl_A0_ESI, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_ESI_s1:
            {
                extern void op_addl_A0_ESI_s1();
                memcpy(gen_code_ptr, &op_addl_A0_ESI_s1, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_ESI_s2:
            {
                extern void op_addl_A0_ESI_s2();
                memcpy(gen_code_ptr, &op_addl_A0_ESI_s2, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_ESI_s3:
            {
                extern void op_addl_A0_ESI_s3();
                memcpy(gen_code_ptr, &op_addl_A0_ESI_s3, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_movl_T0_ESI:
            {
                extern void op_movl_T0_ESI();
                memcpy(gen_code_ptr, &op_movl_T0_ESI, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_T1_ESI:
            {
                extern void op_movl_T1_ESI();
                memcpy(gen_code_ptr, &op_movl_T1_ESI, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_T0_ESI:
            {
                extern void op_movh_T0_ESI();
                memcpy(gen_code_ptr, &op_movh_T0_ESI, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movh_T1_ESI:
            {
                extern void op_movh_T1_ESI();
                memcpy(gen_code_ptr, &op_movh_T1_ESI, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movl_ESI_T0:
            {
                extern void op_movl_ESI_T0();
                memcpy(gen_code_ptr, &op_movl_ESI_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_ESI_T1:
            {
                extern void op_movl_ESI_T1();
                memcpy(gen_code_ptr, &op_movl_ESI_T1, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_ESI_A0:
            {
                extern void op_movl_ESI_A0();
                memcpy(gen_code_ptr, &op_movl_ESI_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_cmovw_ESI_T1_T0:
            {
                extern void op_cmovw_ESI_T1_T0();
                memcpy(gen_code_ptr, &op_cmovw_ESI_T1_T0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cmovl_ESI_T1_T0:
            {
                extern void op_cmovl_ESI_T1_T0();
                memcpy(gen_code_ptr, &op_cmovl_ESI_T1_T0, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movw_ESI_T0:
            {
                extern void op_movw_ESI_T0();
                memcpy(gen_code_ptr, &op_movw_ESI_T0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_ESI_T1:
            {
                extern void op_movw_ESI_T1();
                memcpy(gen_code_ptr, &op_movw_ESI_T1, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_ESI_A0:
            {
                extern void op_movw_ESI_A0();
                memcpy(gen_code_ptr, &op_movw_ESI_A0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movb_ESI_T0:
            {
                extern void op_movb_ESI_T0();
                memcpy(gen_code_ptr, &op_movb_ESI_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_ESI_T0:
            {
                extern void op_movh_ESI_T0();
                memcpy(gen_code_ptr, &op_movh_ESI_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movb_ESI_T1:
            {
                extern void op_movb_ESI_T1();
                memcpy(gen_code_ptr, &op_movb_ESI_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movh_ESI_T1:
            {
                extern void op_movh_ESI_T1();
                memcpy(gen_code_ptr, &op_movh_ESI_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movl_A0_EDI:
            {
                extern void op_movl_A0_EDI();
                memcpy(gen_code_ptr, &op_movl_A0_EDI, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EDI:
            {
                extern void op_addl_A0_EDI();
                memcpy(gen_code_ptr, &op_addl_A0_EDI, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_addl_A0_EDI_s1:
            {
                extern void op_addl_A0_EDI_s1();
                memcpy(gen_code_ptr, &op_addl_A0_EDI_s1, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EDI_s2:
            {
                extern void op_addl_A0_EDI_s2();
                memcpy(gen_code_ptr, &op_addl_A0_EDI_s2, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_EDI_s3:
            {
                extern void op_addl_A0_EDI_s3();
                memcpy(gen_code_ptr, &op_addl_A0_EDI_s3, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_movl_T0_EDI:
            {
                extern void op_movl_T0_EDI();
                memcpy(gen_code_ptr, &op_movl_T0_EDI, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_T1_EDI:
            {
                extern void op_movl_T1_EDI();
                memcpy(gen_code_ptr, &op_movl_T1_EDI, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_T0_EDI:
            {
                extern void op_movh_T0_EDI();
                memcpy(gen_code_ptr, &op_movh_T0_EDI, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movh_T1_EDI:
            {
                extern void op_movh_T1_EDI();
                memcpy(gen_code_ptr, &op_movh_T1_EDI, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movl_EDI_T0:
            {
                extern void op_movl_EDI_T0();
                memcpy(gen_code_ptr, &op_movl_EDI_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EDI_T1:
            {
                extern void op_movl_EDI_T1();
                memcpy(gen_code_ptr, &op_movl_EDI_T1, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movl_EDI_A0:
            {
                extern void op_movl_EDI_A0();
                memcpy(gen_code_ptr, &op_movl_EDI_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_cmovw_EDI_T1_T0:
            {
                extern void op_cmovw_EDI_T1_T0();
                memcpy(gen_code_ptr, &op_cmovw_EDI_T1_T0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cmovl_EDI_T1_T0:
            {
                extern void op_cmovl_EDI_T1_T0();
                memcpy(gen_code_ptr, &op_cmovl_EDI_T1_T0, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movw_EDI_T0:
            {
                extern void op_movw_EDI_T0();
                memcpy(gen_code_ptr, &op_movw_EDI_T0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EDI_T1:
            {
                extern void op_movw_EDI_T1();
                memcpy(gen_code_ptr, &op_movw_EDI_T1, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movw_EDI_A0:
            {
                extern void op_movw_EDI_A0();
                memcpy(gen_code_ptr, &op_movw_EDI_A0, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_movb_EDI_T0:
            {
                extern void op_movb_EDI_T0();
                memcpy(gen_code_ptr, &op_movb_EDI_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movh_EDI_T0:
            {
                extern void op_movh_EDI_T0();
                memcpy(gen_code_ptr, &op_movh_EDI_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movb_EDI_T1:
            {
                extern void op_movb_EDI_T1();
                memcpy(gen_code_ptr, &op_movb_EDI_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_movh_EDI_T1:
            {
                extern void op_movh_EDI_T1();
                memcpy(gen_code_ptr, &op_movh_EDI_T1, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_addl_T0_T1_cc:
            {
                extern void op_addl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_addl_T0_T1_cc, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_orl_T0_T1_cc:
            {
                extern void op_orl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_orl_T0_T1_cc, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_andl_T0_T1_cc:
            {
                extern void op_andl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_andl_T0_T1_cc, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_subl_T0_T1_cc:
            {
                extern void op_subl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_subl_T0_T1_cc, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_xorl_T0_T1_cc:
            {
                extern void op_xorl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_xorl_T0_T1_cc, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_cmpl_T0_T1_cc:
            {
                extern void op_cmpl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_cmpl_T0_T1_cc, 10);
                gen_code_ptr += 10;
            }
            break;

            case INDEX_op_negl_T0_cc: /* T0取反,并且赋值给cc */
            {
                extern void op_negl_T0_cc();
                memcpy(gen_code_ptr, &op_negl_T0_cc, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_incl_T0_cc:
            {
                extern void op_incl_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_incl_T0_cc, 17);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 17;
            }
            break;

            case INDEX_op_decl_T0_cc:
            {
                extern void op_decl_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_decl_T0_cc, 17);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 17;
            }
            break;

            case INDEX_op_testl_T0_T1_cc:
            {
                extern void op_testl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_testl_T0_T1_cc, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_addl_T0_T1:
            {
                extern void op_addl_T0_T1();
                memcpy(gen_code_ptr, &op_addl_T0_T1, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_orl_T0_T1:
            {
                extern void op_orl_T0_T1();
                memcpy(gen_code_ptr, &op_orl_T0_T1, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_andl_T0_T1:
            {
                extern void op_andl_T0_T1();
                memcpy(gen_code_ptr, &op_andl_T0_T1, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_subl_T0_T1:
            {
                extern void op_subl_T0_T1();
                memcpy(gen_code_ptr, &op_subl_T0_T1, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_xorl_T0_T1:
            {
                extern void op_xorl_T0_T1();
                memcpy(gen_code_ptr, &op_xorl_T0_T1, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_negl_T0: /* 寄存器中的值取反 */
            {
                extern void op_negl_T0();
                memcpy(gen_code_ptr, &op_negl_T0, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_incl_T0:
            {
                extern void op_incl_T0();
                memcpy(gen_code_ptr, &op_incl_T0, 1);
                gen_code_ptr += 1;
            }
            break;

            case INDEX_op_decl_T0:
            {
                extern void op_decl_T0();
                memcpy(gen_code_ptr, &op_decl_T0, 1);
                gen_code_ptr += 1;
            }
            break;

            case INDEX_op_notl_T0:
            {
                extern void op_notl_T0();
                memcpy(gen_code_ptr, &op_notl_T0, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_bswapl_T0:
            {
                extern void op_bswapl_T0();
                memcpy(gen_code_ptr, &op_bswapl_T0, 38);
                gen_code_ptr += 38;
            }
            break;

            case INDEX_op_mulb_AL_T0:
            {
                extern void op_mulb_AL_T0();
                memcpy(gen_code_ptr, &op_mulb_AL_T0, 22);
                gen_code_ptr += 22;
            }
            break;

            case INDEX_op_imulb_AL_T0:
            {
                extern void op_imulb_AL_T0();
                memcpy(gen_code_ptr, &op_imulb_AL_T0, 28);
                gen_code_ptr += 28;
            }
            break;

            case INDEX_op_mulw_AX_T0:
            {
                extern void op_mulw_AX_T0();
                memcpy(gen_code_ptr, &op_mulw_AX_T0, 24);
                gen_code_ptr += 24;
            }
            break;

            case INDEX_op_imulw_AX_T0:
            {
                extern void op_imulw_AX_T0();
                memcpy(gen_code_ptr, &op_imulw_AX_T0, 37);
                gen_code_ptr += 37;
            }
            break;

            case INDEX_op_mull_EAX_T0:
            {
                extern void op_mull_EAX_T0();
                memcpy(gen_code_ptr, &op_mull_EAX_T0, 27);
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_imull_EAX_T0:
            {
                extern void op_imull_EAX_T0();
                memcpy(gen_code_ptr, &op_imull_EAX_T0, 67);
                gen_code_ptr += 67;
            }
            break;

            case INDEX_op_imulw_T0_T1:
            {
                extern void op_imulw_T0_T1();
                memcpy(gen_code_ptr, &op_imulw_T0_T1, 25);
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_imull_T0_T1:
            {
                extern void op_imull_T0_T1();
                memcpy(gen_code_ptr, &op_imull_T0_T1, 62);
                gen_code_ptr += 62;
            }
            break;

            case INDEX_op_divb_AL_T0:
            {
                extern void op_divb_AL_T0();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_divb_AL_T0, 69);
                *(uint32_t *)(gen_code_ptr + 28) = (long)(&raise_exception) - (long)(gen_code_ptr + 28) + -4;
                gen_code_ptr += 69;
            }
            break;

            case INDEX_op_idivb_AL_T0:
            {
                extern void op_idivb_AL_T0();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_idivb_AL_T0, 72);
                *(uint32_t *)(gen_code_ptr + 24) = (long)(&raise_exception) - (long)(gen_code_ptr + 24) + -4;
                gen_code_ptr += 72;
            }
            break;

            case INDEX_op_divw_AX_T0:
            {
                extern void op_divw_AX_T0();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_divw_AX_T0, 103);
                *(uint32_t *)(gen_code_ptr + 44) = (long)(&raise_exception) - (long)(gen_code_ptr + 44) + -4;
                gen_code_ptr += 103;
            }
            break;

            case INDEX_op_idivw_AX_T0:
            {
                extern void op_idivw_AX_T0();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_idivw_AX_T0, 111);
                *(uint32_t *)(gen_code_ptr + 41) = (long)(&raise_exception) - (long)(gen_code_ptr + 41) + -4;
                gen_code_ptr += 111;
            }
            break;

            case INDEX_op_divl_EAX_T0:
            {
                extern void op_divl_EAX_T0();
                extern char raise_exception;
                extern char __udivdi3;
                extern char __umoddi3;
                memcpy(gen_code_ptr, &op_divl_EAX_T0, 140);
                *(uint32_t *)(gen_code_ptr + 54) = (long)(&raise_exception) - (long)(gen_code_ptr + 54) + -4;
                *(uint32_t *)(gen_code_ptr + 92) = (long)(&__udivdi3) - (long)(gen_code_ptr + 92) + -4;
                *(uint32_t *)(gen_code_ptr + 123) = (long)(&__umoddi3) - (long)(gen_code_ptr + 123) + -4;
                gen_code_ptr += 140;
            }
            break;

            case INDEX_op_idivl_EAX_T0:
            {
                extern void op_idivl_EAX_T0();
                extern char raise_exception;
                extern char __divdi3;
                extern char __moddi3;
                memcpy(gen_code_ptr, &op_idivl_EAX_T0, 131);
                *(uint32_t *)(gen_code_ptr + 54) = (long)(&raise_exception) - (long)(gen_code_ptr + 54) + -4;
                *(uint32_t *)(gen_code_ptr + 83) = (long)(&__divdi3) - (long)(gen_code_ptr + 83) + -4;
                *(uint32_t *)(gen_code_ptr + 114) = (long)(&__moddi3) - (long)(gen_code_ptr + 114) + -4;
                gen_code_ptr += 131;
            }
            break;

            case INDEX_op_movl_T0_im:
            {
                long param1;
                extern void op_movl_T0_im();
                memcpy(gen_code_ptr, &op_movl_T0_im, 5);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_addl_T0_im:
            {
                long param1;
                extern void op_addl_T0_im();
                memcpy(gen_code_ptr, &op_addl_T0_im, 6);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_andl_T0_ffff:
            {
                extern void op_andl_T0_ffff();
                memcpy(gen_code_ptr, &op_andl_T0_ffff, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_movl_T0_T1:
            {
                extern void op_movl_T0_T1();
                memcpy(gen_code_ptr, &op_movl_T0_T1, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_movl_T1_im:
            {
                long param1;
                extern void op_movl_T1_im();
                memcpy(gen_code_ptr, &op_movl_T1_im, 5);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_addl_T1_im:
            {
                long param1;
                extern void op_addl_T1_im();
                memcpy(gen_code_ptr, &op_addl_T1_im, 6);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_movl_T1_A0:
            {
                extern void op_movl_T1_A0();
                memcpy(gen_code_ptr, &op_movl_T1_A0, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_movl_A0_im:
            {
                long param1;
                extern void op_movl_A0_im();
                memcpy(gen_code_ptr, &op_movl_A0_im, 5);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_addl_A0_im:
            {
                long param1;
                extern void op_addl_A0_im();
                memcpy(gen_code_ptr, &op_addl_A0_im, 6);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_AL:
            {
                extern void op_addl_A0_AL();
                memcpy(gen_code_ptr, &op_addl_A0_AL, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_andl_A0_ffff:
            {
                extern void op_andl_A0_ffff();
                memcpy(gen_code_ptr, &op_andl_A0_ffff, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_ldub_T0_A0:
            {
                extern void op_ldub_T0_A0();
                memcpy(gen_code_ptr, &op_ldub_T0_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_ldsb_T0_A0: /* [A0] -> T0 有符号,1字节 */
            {
                extern void op_ldsb_T0_A0();
                memcpy(gen_code_ptr, &op_ldsb_T0_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_lduw_T0_A0: /* [A0] -> T0 无符号,2字节 */
            {
                extern void op_lduw_T0_A0();
                memcpy(gen_code_ptr, &op_lduw_T0_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_ldsw_T0_A0:
            {
                extern void op_ldsw_T0_A0();
                memcpy(gen_code_ptr, &op_ldsw_T0_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_ldl_T0_A0:
            {
                extern void op_ldl_T0_A0();
                memcpy(gen_code_ptr, &op_ldl_T0_A0, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_ldub_T1_A0:
            {
                extern void op_ldub_T1_A0();
                memcpy(gen_code_ptr, &op_ldub_T1_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_ldsb_T1_A0:
            {
                extern void op_ldsb_T1_A0();
                memcpy(gen_code_ptr, &op_ldsb_T1_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_lduw_T1_A0:
            {
                extern void op_lduw_T1_A0();
                memcpy(gen_code_ptr, &op_lduw_T1_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_ldsw_T1_A0:
            {
                extern void op_ldsw_T1_A0();
                memcpy(gen_code_ptr, &op_ldsw_T1_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_ldl_T1_A0:
            {
                extern void op_ldl_T1_A0();
                memcpy(gen_code_ptr, &op_ldl_T1_A0, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_stb_T0_A0: /* T0 -> [A0],1字节 */
            {
                extern void op_stb_T0_A0();
                memcpy(gen_code_ptr, &op_stb_T0_A0, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_stw_T0_A0: /* T0 -> [A0], 2字节 */
            {
                extern void op_stw_T0_A0();
                memcpy(gen_code_ptr, &op_stw_T0_A0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_stl_T0_A0:
            {
                extern void op_stl_T0_A0();
                memcpy(gen_code_ptr, &op_stl_T0_A0, 2);
                gen_code_ptr += 2;
            }
            break;

            case INDEX_op_add_bitw_A0_T1:
            {
                extern void op_add_bitw_A0_T1();
                memcpy(gen_code_ptr, &op_add_bitw_A0_T1, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_add_bitl_A0_T1:
            {
                extern void op_add_bitl_A0_T1();
                memcpy(gen_code_ptr, &op_add_bitl_A0_T1, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_jmp_T0:
            {
                extern void op_jmp_T0();
                memcpy(gen_code_ptr, &op_jmp_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_jmp_im:
            {
                long param1;
                extern void op_jmp_im();
                memcpy(gen_code_ptr, &op_jmp_im, 7);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 3) = param1 + 0;
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_int_im:
            {
                long param1;
                extern void op_int_im();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_int_im, 15);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 10) = (long)(&raise_exception) - (long)(gen_code_ptr + 10) + -4;
                gen_code_ptr += 15;
            }
            break;

            case INDEX_op_int3:
            {
                long param1;
                extern void op_int3();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_int3, 15);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 10) = (long)(&raise_exception) - (long)(gen_code_ptr + 10) + -4;
                gen_code_ptr += 15;
            }
            break;

            case INDEX_op_into:
            {
                extern void op_into();
                extern char cc_table;
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_into, 25);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 20) = (long)(&raise_exception) - (long)(gen_code_ptr + 20) + -4;
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_cli:
            {
                extern void op_cli();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_cli, 8);
                *(uint32_t *)(gen_code_ptr + 3) = (long)(&raise_exception) - (long)(gen_code_ptr + 3) + -4;
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_sti:
            {
                extern void op_sti();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_sti, 8);
                *(uint32_t *)(gen_code_ptr + 3) = (long)(&raise_exception) - (long)(gen_code_ptr + 3) + -4;
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cli_vm:
            {
                extern void op_cli_vm();
                memcpy(gen_code_ptr, &op_cli_vm, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_sti_vm:
            {
                long param1;
                extern void op_sti_vm();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_sti_vm, 28);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 18) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = (long)(&raise_exception) - (long)(gen_code_ptr + 23) + -4;
                gen_code_ptr += 28;
            }
            break;

            case INDEX_op_boundw:
            {
                extern void op_boundw();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_boundw, 26);
                *(uint32_t *)(gen_code_ptr + 21) = (long)(&raise_exception) - (long)(gen_code_ptr + 21) + -4;
                gen_code_ptr += 26;
            }
            break;

            case INDEX_op_boundl:
            {
                extern void op_boundl();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_boundl, 19);
                *(uint32_t *)(gen_code_ptr + 14) = (long)(&raise_exception) - (long)(gen_code_ptr + 14) + -4;
                gen_code_ptr += 19;
            }
            break;

            case INDEX_op_cmpxchg8b:
            {
                extern void op_cmpxchg8b();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_cmpxchg8b, 169);
                *(uint32_t *)(gen_code_ptr + 9) = (long)(&cc_table) + 0;
                gen_code_ptr += 169;
            }
            break;

            case INDEX_op_jb_subb:
            {
                long param1, param2;
                extern void op_jb_subb();
                memcpy(gen_code_ptr, &op_jb_subb, 27);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
				/* 这里是在记录所谓的参数吗? */
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_jz_subb:
            {
                long param1, param2;
                extern void op_jz_subb();
                memcpy(gen_code_ptr, &op_jz_subb, 23);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 9) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_jbe_subb:
            {
                long param1, param2;
                extern void op_jbe_subb();
                memcpy(gen_code_ptr, &op_jbe_subb, 27);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_js_subb:
            {
                long param1, param2;
                extern void op_js_subb();
                memcpy(gen_code_ptr, &op_js_subb, 23);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 9) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_jl_subb:
            {
                long param1, param2;
                extern void op_jl_subb();
                memcpy(gen_code_ptr, &op_jl_subb, 27);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_jle_subb:
            {
                long param1, param2;
                extern void op_jle_subb();
                memcpy(gen_code_ptr, &op_jle_subb, 27);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_setb_T0_subb:
            {
                extern void op_setb_T0_subb();
                memcpy(gen_code_ptr, &op_setb_T0_subb, 14);
                gen_code_ptr += 14;
            }
            break;

            case INDEX_op_setz_T0_subb:
            {
                extern void op_setz_T0_subb();
                memcpy(gen_code_ptr, &op_setz_T0_subb, 9);
                gen_code_ptr += 9;
            }
            break;

            case INDEX_op_setbe_T0_subb:
            {
                extern void op_setbe_T0_subb();
                memcpy(gen_code_ptr, &op_setbe_T0_subb, 14);
                gen_code_ptr += 14;
            }
            break;

            case INDEX_op_sets_T0_subb:
            {
                extern void op_sets_T0_subb();
                memcpy(gen_code_ptr, &op_sets_T0_subb, 11);
                gen_code_ptr += 11;
            }
            break;

            case INDEX_op_setl_T0_subb:
            {
                extern void op_setl_T0_subb();
                memcpy(gen_code_ptr, &op_setl_T0_subb, 14);
                gen_code_ptr += 14;
            }
            break;

            case INDEX_op_setle_T0_subb:
            {
                extern void op_setle_T0_subb();
                memcpy(gen_code_ptr, &op_setle_T0_subb, 14);
                gen_code_ptr += 14;
            }
            break;

            case INDEX_op_rolb_T0_T1_cc:
            {
                extern void op_rolb_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rolb_T0_T1_cc, 111);
                *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
                gen_code_ptr += 111;
            }
            break;

            case INDEX_op_rolb_T0_T1:
            {
                extern void op_rolb_T0_T1();
                memcpy(gen_code_ptr, &op_rolb_T0_T1, 40);
                gen_code_ptr += 40;
            }
            break;

            case INDEX_op_rorb_T0_T1_cc:
            {
                extern void op_rorb_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rorb_T0_T1_cc, 114);
                *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
                gen_code_ptr += 114;
            }
            break;

            case INDEX_op_rorb_T0_T1:
            {
                extern void op_rorb_T0_T1();
                memcpy(gen_code_ptr, &op_rorb_T0_T1, 40);
                gen_code_ptr += 40;
            }
            break;

            case INDEX_op_rclb_T0_T1_cc:
            {
                extern void op_rclb_T0_T1_cc();
                extern char rclb_table;
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rclb_T0_T1_cc, 153);
                *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclb_table) + 0;
                *(uint32_t *)(gen_code_ptr + 29) = (long)(&cc_table) + 0;
                gen_code_ptr += 153;
            }
            break;

            case INDEX_op_rcrb_T0_T1_cc:
            {
                extern void op_rcrb_T0_T1_cc();
                extern char rclb_table;
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rcrb_T0_T1_cc, 153);
                *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclb_table) + 0;
                *(uint32_t *)(gen_code_ptr + 29) = (long)(&cc_table) + 0;
                gen_code_ptr += 153;
            }
            break;

            case INDEX_op_shlb_T0_T1_cc:
            {
                extern void op_shlb_T0_T1_cc();
                memcpy(gen_code_ptr, &op_shlb_T0_T1_cc, 32);
                gen_code_ptr += 32;
            }
            break;

            case INDEX_op_shlb_T0_T1:
            {
                extern void op_shlb_T0_T1();
                memcpy(gen_code_ptr, &op_shlb_T0_T1, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_shrb_T0_T1_cc:
            {
                extern void op_shrb_T0_T1_cc();
                memcpy(gen_code_ptr, &op_shrb_T0_T1_cc, 37);
                gen_code_ptr += 37;
            }
            break;

            case INDEX_op_shrb_T0_T1:
            {
                extern void op_shrb_T0_T1();
                memcpy(gen_code_ptr, &op_shrb_T0_T1, 13);
                gen_code_ptr += 13;
            }
            break;

            case INDEX_op_sarb_T0_T1_cc:
            {
                extern void op_sarb_T0_T1_cc();
                memcpy(gen_code_ptr, &op_sarb_T0_T1_cc, 40);
                gen_code_ptr += 40;
            }
            break;

            case INDEX_op_sarb_T0_T1:
            {
                extern void op_sarb_T0_T1();
                memcpy(gen_code_ptr, &op_sarb_T0_T1, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_adcb_T0_T1_cc:
            {
                extern void op_adcb_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_adcb_T0_T1_cc, 29);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 29;
            }
            break;

            case INDEX_op_sbbb_T0_T1_cc:
            {
                extern void op_sbbb_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_sbbb_T0_T1_cc, 31);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_cmpxchgb_T0_T1_EAX_cc:
            {
                extern void op_cmpxchgb_T0_T1_EAX_cc();
                memcpy(gen_code_ptr, &op_cmpxchgb_T0_T1_EAX_cc, 34);
                gen_code_ptr += 34;
            }
            break;

            case INDEX_op_movsb_fast:
            {
                extern void op_movsb_fast();
                memcpy(gen_code_ptr, &op_movsb_fast, 20);
                gen_code_ptr += 20;
            }
            break;

            case INDEX_op_rep_movsb_fast:
            {
                extern void op_rep_movsb_fast();
                memcpy(gen_code_ptr, &op_rep_movsb_fast, 39);
                gen_code_ptr += 39;
            }
            break;

            case INDEX_op_stosb_fast:
            {
                extern void op_stosb_fast();
                memcpy(gen_code_ptr, &op_stosb_fast, 17);
                gen_code_ptr += 17;
            }
            break;

            case INDEX_op_rep_stosb_fast:
            {
                extern void op_rep_stosb_fast();
                memcpy(gen_code_ptr, &op_rep_stosb_fast, 33);
                gen_code_ptr += 33;
            }
            break;

            case INDEX_op_lodsb_fast:
            {
                extern void op_lodsb_fast();
                memcpy(gen_code_ptr, &op_lodsb_fast, 18);
                gen_code_ptr += 18;
            }
            break;

            case INDEX_op_rep_lodsb_fast:
            {
                extern void op_rep_lodsb_fast();
                memcpy(gen_code_ptr, &op_rep_lodsb_fast, 36);
                gen_code_ptr += 36;
            }
            break;

            case INDEX_op_scasb_fast:
            {
                extern void op_scasb_fast();
                memcpy(gen_code_ptr, &op_scasb_fast, 23);
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_repz_scasb_fast:
            {
                extern void op_repz_scasb_fast();
                memcpy(gen_code_ptr, &op_repz_scasb_fast, 76);
                gen_code_ptr += 76;
            }
            break;

            case INDEX_op_repnz_scasb_fast:
            {
                extern void op_repnz_scasb_fast();
                memcpy(gen_code_ptr, &op_repnz_scasb_fast, 76);
                gen_code_ptr += 76;
            }
            break;

            case INDEX_op_cmpsb_fast:
            {
                extern void op_cmpsb_fast();
                memcpy(gen_code_ptr, &op_cmpsb_fast, 29);
                gen_code_ptr += 29;
            }
            break;

            case INDEX_op_repz_cmpsb_fast:
            {
                extern void op_repz_cmpsb_fast();
                memcpy(gen_code_ptr, &op_repz_cmpsb_fast, 81);
                gen_code_ptr += 81;
            }
            break;

            case INDEX_op_repnz_cmpsb_fast:
            {
                extern void op_repnz_cmpsb_fast();
                memcpy(gen_code_ptr, &op_repnz_cmpsb_fast, 81);
                gen_code_ptr += 81;
            }
            break;

            case INDEX_op_outsb_fast:
            {
                extern void op_outsb_fast();
                extern char cpu_x86_outb;
                memcpy(gen_code_ptr, &op_outsb_fast, 28);
                *(uint32_t *)(gen_code_ptr + 13) = (long)(&cpu_x86_outb) - (long)(gen_code_ptr + 13) + -4;
                gen_code_ptr += 28;
            }
            break;

            case INDEX_op_rep_outsb_fast:
            {
                extern void op_rep_outsb_fast();
                extern char cpu_x86_outb;
                memcpy(gen_code_ptr, &op_rep_outsb_fast, 62);
                *(uint32_t *)(gen_code_ptr + 36) = (long)(&cpu_x86_outb) - (long)(gen_code_ptr + 36) + -4;
                gen_code_ptr += 62;
            }
            break;

            case INDEX_op_insb_fast:
            {
                extern void op_insb_fast();
                extern char cpu_x86_inb;
                memcpy(gen_code_ptr, &op_insb_fast, 25);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inb) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_rep_insb_fast:
            {
                extern void op_rep_insb_fast();
                extern char cpu_x86_inb;
                memcpy(gen_code_ptr, &op_rep_insb_fast, 58);
                *(uint32_t *)(gen_code_ptr + 29) = (long)(&cpu_x86_inb) - (long)(gen_code_ptr + 29) + -4;
                gen_code_ptr += 58;
            }
            break;

            case INDEX_op_movsb_a32:
            {
                extern void op_movsb_a32();
                memcpy(gen_code_ptr, &op_movsb_a32, 28);
                gen_code_ptr += 28;
            }
            break;

            case INDEX_op_rep_movsb_a32:
            {
                extern void op_rep_movsb_a32();
                memcpy(gen_code_ptr, &op_rep_movsb_a32, 47);
                gen_code_ptr += 47;
            }
            break;

            case INDEX_op_stosb_a32:
            {
                extern void op_stosb_a32();
                memcpy(gen_code_ptr, &op_stosb_a32, 23);
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_rep_stosb_a32:
            {
                extern void op_rep_stosb_a32();
                memcpy(gen_code_ptr, &op_rep_stosb_a32, 39);
                gen_code_ptr += 39;
            }
            break;

            case INDEX_op_lodsb_a32:
            {
                extern void op_lodsb_a32();
                memcpy(gen_code_ptr, &op_lodsb_a32, 20);
                gen_code_ptr += 20;
            }
            break;

            case INDEX_op_rep_lodsb_a32:
            {
                extern void op_rep_lodsb_a32();
                memcpy(gen_code_ptr, &op_rep_lodsb_a32, 38);
                gen_code_ptr += 38;
            }
            break;

            case INDEX_op_scasb_a32:
            {
                extern void op_scasb_a32();
                memcpy(gen_code_ptr, &op_scasb_a32, 32);
                gen_code_ptr += 32;
            }
            break;

            case INDEX_op_repz_scasb_a32:
            {
                extern void op_repz_scasb_a32();
                memcpy(gen_code_ptr, &op_repz_scasb_a32, 90);
                gen_code_ptr += 90;
            }
            break;

            case INDEX_op_repnz_scasb_a32:
            {
                extern void op_repnz_scasb_a32();
                memcpy(gen_code_ptr, &op_repnz_scasb_a32, 90);
                gen_code_ptr += 90;
            }
            break;

            case INDEX_op_cmpsb_a32:
            {
                extern void op_cmpsb_a32();
                memcpy(gen_code_ptr, &op_cmpsb_a32, 37);
                gen_code_ptr += 37;
            }
            break;

            case INDEX_op_repz_cmpsb_a32:
            {
                extern void op_repz_cmpsb_a32();
                memcpy(gen_code_ptr, &op_repz_cmpsb_a32, 97);
                gen_code_ptr += 97;
            }
            break;

            case INDEX_op_repnz_cmpsb_a32:
            {
                extern void op_repnz_cmpsb_a32();
                memcpy(gen_code_ptr, &op_repnz_cmpsb_a32, 97);
                gen_code_ptr += 97;
            }
            break;

            case INDEX_op_outsb_a32:
            {
                extern void op_outsb_a32();
                extern char cpu_x86_outb;
                memcpy(gen_code_ptr, &op_outsb_a32, 30);
                *(uint32_t *)(gen_code_ptr + 15) = (long)(&cpu_x86_outb) - (long)(gen_code_ptr + 15) + -4;
                gen_code_ptr += 30;
            }
            break;

            case INDEX_op_rep_outsb_a32:
            {
                extern void op_rep_outsb_a32();
                extern char cpu_x86_outb;
                memcpy(gen_code_ptr, &op_rep_outsb_a32, 64);
                *(uint32_t *)(gen_code_ptr + 38) = (long)(&cpu_x86_outb) - (long)(gen_code_ptr + 38) + -4;
                gen_code_ptr += 64;
            }
            break;

            case INDEX_op_insb_a32:
            {
                extern void op_insb_a32();
                extern char cpu_x86_inb;
                memcpy(gen_code_ptr, &op_insb_a32, 31);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inb) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_rep_insb_a32:
            {
                extern void op_rep_insb_a32();
                extern char cpu_x86_inb;
                memcpy(gen_code_ptr, &op_rep_insb_a32, 64);
                *(uint32_t *)(gen_code_ptr + 29) = (long)(&cpu_x86_inb) - (long)(gen_code_ptr + 29) + -4;
                gen_code_ptr += 64;
            }
            break;

            case INDEX_op_movsb_a16:
            {
                extern void op_movsb_a16();
                memcpy(gen_code_ptr, &op_movsb_a16, 31);
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_rep_movsb_a16:
            {
                extern void op_rep_movsb_a16();
                memcpy(gen_code_ptr, &op_rep_movsb_a16, 51);
                gen_code_ptr += 51;
            }
            break;

            case INDEX_op_stosb_a16:
            {
                extern void op_stosb_a16();
                memcpy(gen_code_ptr, &op_stosb_a16, 22);
                gen_code_ptr += 22;
            }
            break;

            case INDEX_op_rep_stosb_a16:
            {
                extern void op_rep_stosb_a16();
                memcpy(gen_code_ptr, &op_rep_stosb_a16, 42);
                gen_code_ptr += 42;
            }
            break;

            case INDEX_op_lodsb_a16:
            {
                extern void op_lodsb_a16();
                memcpy(gen_code_ptr, &op_lodsb_a16, 18);
                gen_code_ptr += 18;
            }
            break;

            case INDEX_op_rep_lodsb_a16:
            {
                extern void op_rep_lodsb_a16();
                memcpy(gen_code_ptr, &op_rep_lodsb_a16, 38);
                gen_code_ptr += 38;
            }
            break;

            case INDEX_op_scasb_a16:
            {
                extern void op_scasb_a16();
                memcpy(gen_code_ptr, &op_scasb_a16, 31);
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_repz_scasb_a16:
            {
                extern void op_repz_scasb_a16();
                memcpy(gen_code_ptr, &op_repz_scasb_a16, 84);
                gen_code_ptr += 84;
            }
            break;

            case INDEX_op_repnz_scasb_a16:
            {
                extern void op_repnz_scasb_a16();
                memcpy(gen_code_ptr, &op_repnz_scasb_a16, 84);
                gen_code_ptr += 84;
            }
            break;

            case INDEX_op_cmpsb_a16:
            {
                extern void op_cmpsb_a16();
                memcpy(gen_code_ptr, &op_cmpsb_a16, 40);
                gen_code_ptr += 40;
            }
            break;

            case INDEX_op_repz_cmpsb_a16:
            {
                extern void op_repz_cmpsb_a16();
                memcpy(gen_code_ptr, &op_repz_cmpsb_a16, 92);
                gen_code_ptr += 92;
            }
            break;

            case INDEX_op_repnz_cmpsb_a16:
            {
                extern void op_repnz_cmpsb_a16();
                memcpy(gen_code_ptr, &op_repnz_cmpsb_a16, 92);
                gen_code_ptr += 92;
            }
            break;

            case INDEX_op_outsb_a16:
            {
                extern void op_outsb_a16();
                extern char cpu_x86_outb;
                memcpy(gen_code_ptr, &op_outsb_a16, 28);
                *(uint32_t *)(gen_code_ptr + 15) = (long)(&cpu_x86_outb) - (long)(gen_code_ptr + 15) + -4;
                gen_code_ptr += 28;
            }
            break;

            case INDEX_op_rep_outsb_a16:
            {
                extern void op_rep_outsb_a16();
                extern char cpu_x86_outb;
                memcpy(gen_code_ptr, &op_rep_outsb_a16, 66);
                *(uint32_t *)(gen_code_ptr + 38) = (long)(&cpu_x86_outb) - (long)(gen_code_ptr + 38) + -4;
                gen_code_ptr += 66;
            }
            break;

            case INDEX_op_insb_a16:
            {
                extern void op_insb_a16();
                extern char cpu_x86_inb;
                memcpy(gen_code_ptr, &op_insb_a16, 30);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inb) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 30;
            }
            break;

            case INDEX_op_rep_insb_a16:
            {
                extern void op_rep_insb_a16();
                extern char cpu_x86_inb;
                memcpy(gen_code_ptr, &op_rep_insb_a16, 67);
                *(uint32_t *)(gen_code_ptr + 29) = (long)(&cpu_x86_inb) - (long)(gen_code_ptr + 29) + -4;
                gen_code_ptr += 67;
            }
            break;

            case INDEX_op_outb_T0_T1:
            {
                extern void op_outb_T0_T1();
                extern char cpu_x86_outb;
                memcpy(gen_code_ptr, &op_outb_T0_T1, 19);
                *(uint32_t *)(gen_code_ptr + 13) = (long)(&cpu_x86_outb) - (long)(gen_code_ptr + 13) + -4;
                gen_code_ptr += 19;
            }
            break;

            case INDEX_op_inb_T0_T1:
            {
                extern void op_inb_T0_T1();
                extern char cpu_x86_inb;
                memcpy(gen_code_ptr, &op_inb_T0_T1, 12);
                *(uint32_t *)(gen_code_ptr + 5) = (long)(&cpu_x86_inb) - (long)(gen_code_ptr + 5) + -4;
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_jb_subw:
            {
                long param1, param2;
                extern void op_jb_subw();
                memcpy(gen_code_ptr, &op_jb_subw, 31);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 15) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 27) = param2 + 0;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_jz_subw:
            {
                long param1, param2;
                extern void op_jz_subw();
                memcpy(gen_code_ptr, &op_jz_subw, 23);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_jbe_subw:
            {
                long param1, param2;
                extern void op_jbe_subw();
                memcpy(gen_code_ptr, &op_jbe_subw, 31);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 15) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 27) = param2 + 0;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_js_subw:
            {
                long param1, param2;
                extern void op_js_subw();
                memcpy(gen_code_ptr, &op_js_subw, 23);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_jl_subw:
            {
                long param1, param2;
                extern void op_jl_subw();
                memcpy(gen_code_ptr, &op_jl_subw, 31);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 15) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 27) = param2 + 0;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_jle_subw:
            {
                long param1, param2;
                extern void op_jle_subw();
                memcpy(gen_code_ptr, &op_jle_subw, 31);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 15) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 27) = param2 + 0;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_loopnzw:
            {
                long param1, param2;
                extern void op_loopnzw();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_loopnzw, 51);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 37) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 47) = param2 + 0;
                gen_code_ptr += 51;
            }
            break;

            case INDEX_op_loopzw:
            {
                long param1, param2;
                extern void op_loopzw();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_loopzw, 51);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 37) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 47) = param2 + 0;
                gen_code_ptr += 51;
            }
            break;

            case INDEX_op_loopw:
            {
                long param1, param2;
                extern void op_loopw();
                memcpy(gen_code_ptr, &op_loopw, 35);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 20) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 31) = param2 + 0;
                gen_code_ptr += 35;
            }
            break;

            case INDEX_op_jecxzw:
            {
                long param1, param2;
                extern void op_jecxzw();
                memcpy(gen_code_ptr, &op_jecxzw, 23);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_setb_T0_subw:
            {
                extern void op_setb_T0_subw();
                memcpy(gen_code_ptr, &op_setb_T0_subw, 15);
                gen_code_ptr += 15;
            }
            break;

            case INDEX_op_setz_T0_subw:
            {
                extern void op_setz_T0_subw();
                memcpy(gen_code_ptr, &op_setz_T0_subw, 10);
                gen_code_ptr += 10;
            }
            break;

            case INDEX_op_setbe_T0_subw:
            {
                extern void op_setbe_T0_subw();
                memcpy(gen_code_ptr, &op_setbe_T0_subw, 15);
                gen_code_ptr += 15;
            }
            break;

            case INDEX_op_sets_T0_subw:
            {
                extern void op_sets_T0_subw();
                memcpy(gen_code_ptr, &op_sets_T0_subw, 11);
                gen_code_ptr += 11;
            }
            break;

            case INDEX_op_setl_T0_subw:
            {
                extern void op_setl_T0_subw();
                memcpy(gen_code_ptr, &op_setl_T0_subw, 15);
                gen_code_ptr += 15;
            }
            break;

            case INDEX_op_setle_T0_subw:
            {
                extern void op_setle_T0_subw();
                memcpy(gen_code_ptr, &op_setle_T0_subw, 15);
                gen_code_ptr += 15;
            }
            break;

            case INDEX_op_rolw_T0_T1_cc:
            {
                extern void op_rolw_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rolw_T0_T1_cc, 111);
                *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
                gen_code_ptr += 111;
            }
            break;

            case INDEX_op_rolw_T0_T1:
            {
                extern void op_rolw_T0_T1();
                memcpy(gen_code_ptr, &op_rolw_T0_T1, 40);
                gen_code_ptr += 40;
            }
            break;

            case INDEX_op_rorw_T0_T1_cc:
            {
                extern void op_rorw_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rorw_T0_T1_cc, 114);
                *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
                gen_code_ptr += 114;
            }
            break;

            case INDEX_op_rorw_T0_T1:
            {
                extern void op_rorw_T0_T1();
                memcpy(gen_code_ptr, &op_rorw_T0_T1, 40);
                gen_code_ptr += 40;
            }
            break;

            case INDEX_op_rclw_T0_T1_cc:
            {
                extern void op_rclw_T0_T1_cc();
                extern char rclw_table;
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rclw_T0_T1_cc, 153);
                *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclw_table) + 0;
                *(uint32_t *)(gen_code_ptr + 29) = (long)(&cc_table) + 0;
                gen_code_ptr += 153;
            }
            break;

            case INDEX_op_rcrw_T0_T1_cc:
            {
                extern void op_rcrw_T0_T1_cc();
                extern char rclw_table;
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rcrw_T0_T1_cc, 153);
                *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclw_table) + 0;
                *(uint32_t *)(gen_code_ptr + 29) = (long)(&cc_table) + 0;
                gen_code_ptr += 153;
            }
            break;

            case INDEX_op_shlw_T0_T1_cc:
            {
                extern void op_shlw_T0_T1_cc();
                memcpy(gen_code_ptr, &op_shlw_T0_T1_cc, 32);
                gen_code_ptr += 32;
            }
            break;

            case INDEX_op_shlw_T0_T1:
            {
                extern void op_shlw_T0_T1();
                memcpy(gen_code_ptr, &op_shlw_T0_T1, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_shrw_T0_T1_cc:
            {
                extern void op_shrw_T0_T1_cc();
                memcpy(gen_code_ptr, &op_shrw_T0_T1_cc, 37);
                gen_code_ptr += 37;
            }
            break;

            case INDEX_op_shrw_T0_T1:
            {
                extern void op_shrw_T0_T1();
                memcpy(gen_code_ptr, &op_shrw_T0_T1, 13);
                gen_code_ptr += 13;
            }
            break;

            case INDEX_op_sarw_T0_T1_cc:
            {
                extern void op_sarw_T0_T1_cc();
                memcpy(gen_code_ptr, &op_sarw_T0_T1_cc, 40);
                gen_code_ptr += 40;
            }
            break;

            case INDEX_op_sarw_T0_T1:
            {
                extern void op_sarw_T0_T1();
                memcpy(gen_code_ptr, &op_sarw_T0_T1, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_shldw_T0_T1_im_cc:
            {
                long param1;
                extern void op_shldw_T0_T1_im_cc();
                memcpy(gen_code_ptr, &op_shldw_T0_T1_im_cc, 70);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 24) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 36) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 51) = param1 + -16;
                gen_code_ptr += 70;
            }
            break;

            case INDEX_op_shldw_T0_T1_ECX_cc:
            {
                extern void op_shldw_T0_T1_ECX_cc();
                memcpy(gen_code_ptr, &op_shldw_T0_T1_ECX_cc, 98);
                gen_code_ptr += 98;
            }
            break;

            case INDEX_op_shrdw_T0_T1_im_cc:
            {
                long param1;
                extern void op_shrdw_T0_T1_im_cc();
                memcpy(gen_code_ptr, &op_shrdw_T0_T1_im_cc, 66);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 16) = param1 + -1;
                *(uint32_t *)(gen_code_ptr + 28) = param1 + 0;
                gen_code_ptr += 66;
            }
            break;

            case INDEX_op_shrdw_T0_T1_ECX_cc:
            {
                extern void op_shrdw_T0_T1_ECX_cc();
                memcpy(gen_code_ptr, &op_shrdw_T0_T1_ECX_cc, 88);
                gen_code_ptr += 88;
            }
            break;

            case INDEX_op_adcw_T0_T1_cc:
            {
                extern void op_adcw_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_adcw_T0_T1_cc, 29);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 29;
            }
            break;

            case INDEX_op_sbbw_T0_T1_cc:
            {
                extern void op_sbbw_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_sbbw_T0_T1_cc, 31);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_cmpxchgw_T0_T1_EAX_cc:
            {
                extern void op_cmpxchgw_T0_T1_EAX_cc();
                memcpy(gen_code_ptr, &op_cmpxchgw_T0_T1_EAX_cc, 38);
                gen_code_ptr += 38;
            }
            break;

            case INDEX_op_btw_T0_T1_cc:
            {
                extern void op_btw_T0_T1_cc();
                memcpy(gen_code_ptr, &op_btw_T0_T1_cc, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_btsw_T0_T1_cc:
            {
                extern void op_btsw_T0_T1_cc();
                memcpy(gen_code_ptr, &op_btsw_T0_T1_cc, 21);
                gen_code_ptr += 21;
            }
            break;

            case INDEX_op_btrw_T0_T1_cc:
            {
                extern void op_btrw_T0_T1_cc();
                memcpy(gen_code_ptr, &op_btrw_T0_T1_cc, 21);
                gen_code_ptr += 21;
            }
            break;

            case INDEX_op_btcw_T0_T1_cc:
            {
                extern void op_btcw_T0_T1_cc();
                memcpy(gen_code_ptr, &op_btcw_T0_T1_cc, 21);
                gen_code_ptr += 21;
            }
            break;

            case INDEX_op_bsfw_T0_cc:
            {
                extern void op_bsfw_T0_cc();
                memcpy(gen_code_ptr, &op_bsfw_T0_cc, 51);
                gen_code_ptr += 51;
            }
            break;

            case INDEX_op_bsrw_T0_cc:
            {
                extern void op_bsrw_T0_cc();
                memcpy(gen_code_ptr, &op_bsrw_T0_cc, 47);
                gen_code_ptr += 47;
            }
            break;

            case INDEX_op_movsw_fast:
            {
                extern void op_movsw_fast();
                memcpy(gen_code_ptr, &op_movsw_fast, 23);
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_rep_movsw_fast:
            {
                extern void op_rep_movsw_fast();
                memcpy(gen_code_ptr, &op_rep_movsw_fast, 77);
                gen_code_ptr += 77;
            }
            break;

            case INDEX_op_stosw_fast:
            {
                extern void op_stosw_fast();
                memcpy(gen_code_ptr, &op_stosw_fast, 17);
                gen_code_ptr += 17;
            }
            break;

            case INDEX_op_rep_stosw_fast:
            {
                extern void op_rep_stosw_fast();
                memcpy(gen_code_ptr, &op_rep_stosw_fast, 46);
                gen_code_ptr += 46;
            }
            break;

            case INDEX_op_lodsw_fast:
            {
                extern void op_lodsw_fast();
                memcpy(gen_code_ptr, &op_lodsw_fast, 18);
                gen_code_ptr += 18;
            }
            break;

            case INDEX_op_rep_lodsw_fast:
            {
                extern void op_rep_lodsw_fast();
                memcpy(gen_code_ptr, &op_rep_lodsw_fast, 45);
                gen_code_ptr += 45;
            }
            break;

            case INDEX_op_scasw_fast:
            {
                extern void op_scasw_fast();
                memcpy(gen_code_ptr, &op_scasw_fast, 25);
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_repz_scasw_fast:
            {
                extern void op_repz_scasw_fast();
                memcpy(gen_code_ptr, &op_repz_scasw_fast, 78);
                gen_code_ptr += 78;
            }
            break;

            case INDEX_op_repnz_scasw_fast:
            {
                extern void op_repnz_scasw_fast();
                memcpy(gen_code_ptr, &op_repnz_scasw_fast, 78);
                gen_code_ptr += 78;
            }
            break;

            case INDEX_op_cmpsw_fast:
            {
                extern void op_cmpsw_fast();
                memcpy(gen_code_ptr, &op_cmpsw_fast, 31);
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_repz_cmpsw_fast:
            {
                extern void op_repz_cmpsw_fast();
                memcpy(gen_code_ptr, &op_repz_cmpsw_fast, 83);
                gen_code_ptr += 83;
            }
            break;

            case INDEX_op_repnz_cmpsw_fast:
            {
                extern void op_repnz_cmpsw_fast();
                memcpy(gen_code_ptr, &op_repnz_cmpsw_fast, 83);
                gen_code_ptr += 83;
            }
            break;

            case INDEX_op_outsw_fast:
            {
                extern void op_outsw_fast();
                extern char cpu_x86_outw;
                memcpy(gen_code_ptr, &op_outsw_fast, 27);
                *(uint32_t *)(gen_code_ptr + 13) = (long)(&cpu_x86_outw) - (long)(gen_code_ptr + 13) + -4;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_rep_outsw_fast:
            {
                extern void op_rep_outsw_fast();
                extern char cpu_x86_outw;
                memcpy(gen_code_ptr, &op_rep_outsw_fast, 66);
                *(uint32_t *)(gen_code_ptr + 40) = (long)(&cpu_x86_outw) - (long)(gen_code_ptr + 40) + -4;
                gen_code_ptr += 66;
            }
            break;

            case INDEX_op_insw_fast:
            {
                extern void op_insw_fast();
                extern char cpu_x86_inw;
                memcpy(gen_code_ptr, &op_insw_fast, 25);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inw) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_rep_insw_fast:
            {
                extern void op_rep_insw_fast();
                extern char cpu_x86_inw;
                memcpy(gen_code_ptr, &op_rep_insw_fast, 63);
                *(uint32_t *)(gen_code_ptr + 33) = (long)(&cpu_x86_inw) - (long)(gen_code_ptr + 33) + -4;
                gen_code_ptr += 63;
            }
            break;

            case INDEX_op_movsw_a32:
            {
                extern void op_movsw_a32();
                memcpy(gen_code_ptr, &op_movsw_a32, 31);
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_rep_movsw_a32:
            {
                extern void op_rep_movsw_a32();
                memcpy(gen_code_ptr, &op_rep_movsw_a32, 112);
                gen_code_ptr += 112;
            }
            break;

            case INDEX_op_stosw_a32:
            {
                extern void op_stosw_a32();
                memcpy(gen_code_ptr, &op_stosw_a32, 23);
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_rep_stosw_a32:
            {
                extern void op_rep_stosw_a32();
                memcpy(gen_code_ptr, &op_rep_stosw_a32, 84);
                gen_code_ptr += 84;
            }
            break;

            case INDEX_op_lodsw_a32:
            {
                extern void op_lodsw_a32();
                memcpy(gen_code_ptr, &op_lodsw_a32, 20);
                gen_code_ptr += 20;
            }
            break;

            case INDEX_op_rep_lodsw_a32:
            {
                extern void op_rep_lodsw_a32();
                memcpy(gen_code_ptr, &op_rep_lodsw_a32, 46);
                gen_code_ptr += 46;
            }
            break;

            case INDEX_op_scasw_a32:
            {
                extern void op_scasw_a32();
                memcpy(gen_code_ptr, &op_scasw_a32, 31);
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_repz_scasw_a32:
            {
                extern void op_repz_scasw_a32();
                memcpy(gen_code_ptr, &op_repz_scasw_a32, 92);
                gen_code_ptr += 92;
            }
            break;

            case INDEX_op_repnz_scasw_a32:
            {
                extern void op_repnz_scasw_a32();
                memcpy(gen_code_ptr, &op_repnz_scasw_a32, 92);
                gen_code_ptr += 92;
            }
            break;

            case INDEX_op_cmpsw_a32:
            {
                extern void op_cmpsw_a32();
                memcpy(gen_code_ptr, &op_cmpsw_a32, 39);
                gen_code_ptr += 39;
            }
            break;

            case INDEX_op_repz_cmpsw_a32:
            {
                extern void op_repz_cmpsw_a32();
                memcpy(gen_code_ptr, &op_repz_cmpsw_a32, 97);
                gen_code_ptr += 97;
            }
            break;

            case INDEX_op_repnz_cmpsw_a32:
            {
                extern void op_repnz_cmpsw_a32();
                memcpy(gen_code_ptr, &op_repnz_cmpsw_a32, 97);
                gen_code_ptr += 97;
            }
            break;

            case INDEX_op_outsw_a32:
            {
                extern void op_outsw_a32();
                extern char cpu_x86_outw;
                memcpy(gen_code_ptr, &op_outsw_a32, 29);
                *(uint32_t *)(gen_code_ptr + 15) = (long)(&cpu_x86_outw) - (long)(gen_code_ptr + 15) + -4;
                gen_code_ptr += 29;
            }
            break;

            case INDEX_op_rep_outsw_a32:
            {
                extern void op_rep_outsw_a32();
                extern char cpu_x86_outw;
                memcpy(gen_code_ptr, &op_rep_outsw_a32, 68);
                *(uint32_t *)(gen_code_ptr + 42) = (long)(&cpu_x86_outw) - (long)(gen_code_ptr + 42) + -4;
                gen_code_ptr += 68;
            }
            break;

            case INDEX_op_insw_a32:
            {
                extern void op_insw_a32();
                extern char cpu_x86_inw;
                memcpy(gen_code_ptr, &op_insw_a32, 31);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inw) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_rep_insw_a32:
            {
                extern void op_rep_insw_a32();
                extern char cpu_x86_inw;
                memcpy(gen_code_ptr, &op_rep_insw_a32, 69);
                *(uint32_t *)(gen_code_ptr + 33) = (long)(&cpu_x86_inw) - (long)(gen_code_ptr + 33) + -4;
                gen_code_ptr += 69;
            }
            break;

            case INDEX_op_movsw_a16:
            {
                extern void op_movsw_a16();
                memcpy(gen_code_ptr, &op_movsw_a16, 34);
                gen_code_ptr += 34;
            }
            break;

            case INDEX_op_rep_movsw_a16:
            {
                extern void op_rep_movsw_a16();
                memcpy(gen_code_ptr, &op_rep_movsw_a16, 124);
                gen_code_ptr += 124;
            }
            break;

            case INDEX_op_stosw_a16:
            {
                extern void op_stosw_a16();
                memcpy(gen_code_ptr, &op_stosw_a16, 25);
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_rep_stosw_a16:
            {
                extern void op_rep_stosw_a16();
                memcpy(gen_code_ptr, &op_rep_stosw_a16, 91);
                gen_code_ptr += 91;
            }
            break;

            case INDEX_op_lodsw_a16:
            {
                extern void op_lodsw_a16();
                memcpy(gen_code_ptr, &op_lodsw_a16, 21);
                gen_code_ptr += 21;
            }
            break;

            case INDEX_op_rep_lodsw_a16:
            {
                extern void op_rep_lodsw_a16();
                memcpy(gen_code_ptr, &op_rep_lodsw_a16, 68);
                gen_code_ptr += 68;
            }
            break;

            case INDEX_op_scasw_a16:
            {
                extern void op_scasw_a16();
                memcpy(gen_code_ptr, &op_scasw_a16, 33);
                gen_code_ptr += 33;
            }
            break;

            case INDEX_op_repz_scasw_a16:
            {
                extern void op_repz_scasw_a16();
                memcpy(gen_code_ptr, &op_repz_scasw_a16, 84);
                gen_code_ptr += 84;
            }
            break;

            case INDEX_op_repnz_scasw_a16:
            {
                extern void op_repnz_scasw_a16();
                memcpy(gen_code_ptr, &op_repnz_scasw_a16, 84);
                gen_code_ptr += 84;
            }
            break;

            case INDEX_op_cmpsw_a16:
            {
                extern void op_cmpsw_a16();
                memcpy(gen_code_ptr, &op_cmpsw_a16, 42);
                gen_code_ptr += 42;
            }
            break;

            case INDEX_op_repz_cmpsw_a16:
            {
                extern void op_repz_cmpsw_a16();
                memcpy(gen_code_ptr, &op_repz_cmpsw_a16, 92);
                gen_code_ptr += 92;
            }
            break;

            case INDEX_op_repnz_cmpsw_a16:
            {
                extern void op_repnz_cmpsw_a16();
                memcpy(gen_code_ptr, &op_repnz_cmpsw_a16, 92);
                gen_code_ptr += 92;
            }
            break;

            case INDEX_op_outsw_a16:
            {
                extern void op_outsw_a16();
                extern char cpu_x86_outw;
                memcpy(gen_code_ptr, &op_outsw_a16, 30);
                *(uint32_t *)(gen_code_ptr + 15) = (long)(&cpu_x86_outw) - (long)(gen_code_ptr + 15) + -4;
                gen_code_ptr += 30;
            }
            break;

            case INDEX_op_rep_outsw_a16:
            {
                extern void op_rep_outsw_a16();
                extern char cpu_x86_outw;
                memcpy(gen_code_ptr, &op_rep_outsw_a16, 70);
                *(uint32_t *)(gen_code_ptr + 42) = (long)(&cpu_x86_outw) - (long)(gen_code_ptr + 42) + -4;
                gen_code_ptr += 70;
            }
            break;

            case INDEX_op_insw_a16:
            {
                extern void op_insw_a16();
                extern char cpu_x86_inw;
                memcpy(gen_code_ptr, &op_insw_a16, 33);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inw) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 33;
            }
            break;

            case INDEX_op_rep_insw_a16:
            {
                extern void op_rep_insw_a16();
                extern char cpu_x86_inw;
                memcpy(gen_code_ptr, &op_rep_insw_a16, 72);
                *(uint32_t *)(gen_code_ptr + 33) = (long)(&cpu_x86_inw) - (long)(gen_code_ptr + 33) + -4;
                gen_code_ptr += 72;
            }
            break;

            case INDEX_op_outw_T0_T1:
            {
                extern void op_outw_T0_T1();
                extern char cpu_x86_outw;
                memcpy(gen_code_ptr, &op_outw_T0_T1, 19);
                *(uint32_t *)(gen_code_ptr + 13) = (long)(&cpu_x86_outw) - (long)(gen_code_ptr + 13) + -4;
                gen_code_ptr += 19;
            }
            break;

            case INDEX_op_inw_T0_T1:
            {
                extern void op_inw_T0_T1();
                extern char cpu_x86_inw;
                memcpy(gen_code_ptr, &op_inw_T0_T1, 12);
                *(uint32_t *)(gen_code_ptr + 5) = (long)(&cpu_x86_inw) - (long)(gen_code_ptr + 5) + -4;
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_jb_subl:
            {
                long param1, param2;
                extern void op_jb_subl();
                memcpy(gen_code_ptr, &op_jb_subl, 27);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_jz_subl:
            {
                long param1, param2;
                extern void op_jz_subl();
                memcpy(gen_code_ptr, &op_jz_subl, 23);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_jbe_subl:
            {
                long param1, param2;
                extern void op_jbe_subl();
                memcpy(gen_code_ptr, &op_jbe_subl, 27);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_js_subl:
            {
                long param1, param2;
                extern void op_js_subl();
                memcpy(gen_code_ptr, &op_js_subl, 23);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_jl_subl:
            {
                long param1, param2;
                extern void op_jl_subl();
                memcpy(gen_code_ptr, &op_jl_subl, 27);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_jle_subl:
            {
                long param1, param2;
                extern void op_jle_subl();
                memcpy(gen_code_ptr, &op_jle_subl, 27);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_loopnzl:
            {
                long param1, param2;
                extern void op_loopnzl();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_loopnzl, 47);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 31) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 43) = param2 + 0;
                gen_code_ptr += 47;
            }
            break;

            case INDEX_op_loopzl:
            {
                long param1, param2;
                extern void op_loopzl();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_loopzl, 47);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 31) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 43) = param2 + 0;
                gen_code_ptr += 47;
            }
            break;

            case INDEX_op_loopl:
            {
                long param1, param2;
                extern void op_loopl();
                memcpy(gen_code_ptr, &op_loopl, 27);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_jecxzl:
            {
                long param1, param2;
                extern void op_jecxzl();
                memcpy(gen_code_ptr, &op_jecxzl, 23);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_setb_T0_subl:
            {
                extern void op_setb_T0_subl();
                memcpy(gen_code_ptr, &op_setb_T0_subl, 14);
                gen_code_ptr += 14;
            }
            break;

            case INDEX_op_setz_T0_subl:
            {
                extern void op_setz_T0_subl();
                memcpy(gen_code_ptr, &op_setz_T0_subl, 9);
                gen_code_ptr += 9;
            }
            break;

            case INDEX_op_setbe_T0_subl:
            {
                extern void op_setbe_T0_subl();
                memcpy(gen_code_ptr, &op_setbe_T0_subl, 14);
                gen_code_ptr += 14;
            }
            break;

            case INDEX_op_sets_T0_subl:
            {
                extern void op_sets_T0_subl();
                memcpy(gen_code_ptr, &op_sets_T0_subl, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_setl_T0_subl:
            {
                extern void op_setl_T0_subl();
                memcpy(gen_code_ptr, &op_setl_T0_subl, 14);
                gen_code_ptr += 14;
            }
            break;

            case INDEX_op_setle_T0_subl:
            {
                extern void op_setle_T0_subl();
                memcpy(gen_code_ptr, &op_setle_T0_subl, 14);
                gen_code_ptr += 14;
            }
            break;

            case INDEX_op_roll_T0_T1_cc:
            {
                extern void op_roll_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_roll_T0_T1_cc, 65);
                *(uint32_t *)(gen_code_ptr + 17) = (long)(&cc_table) + 0;
                gen_code_ptr += 65;
            }
            break;

            case INDEX_op_roll_T0_T1:
            {
                extern void op_roll_T0_T1();
                memcpy(gen_code_ptr, &op_roll_T0_T1, 9);
                gen_code_ptr += 9;
            }
            break;

            case INDEX_op_rorl_T0_T1_cc:
            {
                extern void op_rorl_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rorl_T0_T1_cc, 64);
                *(uint32_t *)(gen_code_ptr + 17) = (long)(&cc_table) + 0;
                gen_code_ptr += 64;
            }
            break;

            case INDEX_op_rorl_T0_T1:
            {
                extern void op_rorl_T0_T1();
                memcpy(gen_code_ptr, &op_rorl_T0_T1, 9);
                gen_code_ptr += 9;
            }
            break;

            case INDEX_op_rcll_T0_T1_cc:
            {
                extern void op_rcll_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rcll_T0_T1_cc, 138);
                *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
                gen_code_ptr += 138;
            }
            break;

            case INDEX_op_rcrl_T0_T1_cc:
            {
                extern void op_rcrl_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_rcrl_T0_T1_cc, 138);
                *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
                gen_code_ptr += 138;
            }
            break;

            case INDEX_op_shll_T0_T1_cc:
            {
                extern void op_shll_T0_T1_cc();
                memcpy(gen_code_ptr, &op_shll_T0_T1_cc, 31);
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_shll_T0_T1:
            {
                extern void op_shll_T0_T1();
                memcpy(gen_code_ptr, &op_shll_T0_T1, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_shrl_T0_T1_cc:
            {
                extern void op_shrl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_shrl_T0_T1_cc, 31);
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_shrl_T0_T1:
            {
                extern void op_shrl_T0_T1();
                memcpy(gen_code_ptr, &op_shrl_T0_T1, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_sarl_T0_T1_cc:
            {
                extern void op_sarl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_sarl_T0_T1_cc, 36);
                gen_code_ptr += 36;
            }
            break;

            case INDEX_op_sarl_T0_T1:
            {
                extern void op_sarl_T0_T1();
                memcpy(gen_code_ptr, &op_sarl_T0_T1, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_shldl_T0_T1_im_cc:
            {
                long param1;
                extern void op_shldl_T0_T1_im_cc();
                memcpy(gen_code_ptr, &op_shldl_T0_T1_im_cc, 43);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 1) = param1 + -1;
                *(uint32_t *)(gen_code_ptr + 12) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 28) = param1 + 0;
                gen_code_ptr += 43;
            }
            break;

            case INDEX_op_shldl_T0_T1_ECX_cc:
            {
                extern void op_shldl_T0_T1_ECX_cc();
                memcpy(gen_code_ptr, &op_shldl_T0_T1_ECX_cc, 69);
                gen_code_ptr += 69;
            }
            break;

            case INDEX_op_shrdl_T0_T1_im_cc:
            {
                long param1;
                extern void op_shrdl_T0_T1_im_cc();
                memcpy(gen_code_ptr, &op_shrdl_T0_T1_im_cc, 43);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 1) = param1 + -1;
                *(uint32_t *)(gen_code_ptr + 12) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 28) = param1 + 0;
                gen_code_ptr += 43;
            }
            break;

            case INDEX_op_shrdl_T0_T1_ECX_cc:
            {
                extern void op_shrdl_T0_T1_ECX_cc();
                memcpy(gen_code_ptr, &op_shrdl_T0_T1_ECX_cc, 69);
                gen_code_ptr += 69;
            }
            break;

            case INDEX_op_adcl_T0_T1_cc:
            {
                extern void op_adcl_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_adcl_T0_T1_cc, 29);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 29;
            }
            break;

            case INDEX_op_sbbl_T0_T1_cc:
            {
                extern void op_sbbl_T0_T1_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_sbbl_T0_T1_cc, 31);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_cmpxchgl_T0_T1_EAX_cc:
            {
                extern void op_cmpxchgl_T0_T1_EAX_cc();
                memcpy(gen_code_ptr, &op_cmpxchgl_T0_T1_EAX_cc, 23);
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_btl_T0_T1_cc:
            {
                extern void op_btl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_btl_T0_T1_cc, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_btsl_T0_T1_cc:
            {
                extern void op_btsl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_btsl_T0_T1_cc, 21);
                gen_code_ptr += 21;
            }
            break;

            case INDEX_op_btrl_T0_T1_cc:
            {
                extern void op_btrl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_btrl_T0_T1_cc, 21);
                gen_code_ptr += 21;
            }
            break;

            case INDEX_op_btcl_T0_T1_cc:
            {
                extern void op_btcl_T0_T1_cc();
                memcpy(gen_code_ptr, &op_btcl_T0_T1_cc, 21);
                gen_code_ptr += 21;
            }
            break;

            case INDEX_op_bsfl_T0_cc:
            {
                extern void op_bsfl_T0_cc();
                memcpy(gen_code_ptr, &op_bsfl_T0_cc, 47);
                gen_code_ptr += 47;
            }
            break;

            case INDEX_op_bsrl_T0_cc:
            {
                extern void op_bsrl_T0_cc();
                memcpy(gen_code_ptr, &op_bsrl_T0_cc, 39);
                gen_code_ptr += 39;
            }
            break;

            case INDEX_op_movsl_fast:
            {
                extern void op_movsl_fast();
                memcpy(gen_code_ptr, &op_movsl_fast, 22);
                gen_code_ptr += 22;
            }
            break;

            case INDEX_op_rep_movsl_fast:
            {
                extern void op_rep_movsl_fast();
                memcpy(gen_code_ptr, &op_rep_movsl_fast, 46);
                gen_code_ptr += 46;
            }
            break;

            case INDEX_op_stosl_fast:
            {
                extern void op_stosl_fast();
                memcpy(gen_code_ptr, &op_stosl_fast, 17);
                gen_code_ptr += 17;
            }
            break;

            case INDEX_op_rep_stosl_fast:
            {
                extern void op_rep_stosl_fast();
                memcpy(gen_code_ptr, &op_rep_stosl_fast, 41);
                gen_code_ptr += 41;
            }
            break;

            case INDEX_op_lodsl_fast:
            {
                extern void op_lodsl_fast();
                memcpy(gen_code_ptr, &op_lodsl_fast, 17);
                gen_code_ptr += 17;
            }
            break;

            case INDEX_op_rep_lodsl_fast:
            {
                extern void op_rep_lodsl_fast();
                memcpy(gen_code_ptr, &op_rep_lodsl_fast, 43);
                gen_code_ptr += 43;
            }
            break;

            case INDEX_op_scasl_fast:
            {
                extern void op_scasl_fast();
                memcpy(gen_code_ptr, &op_scasl_fast, 25);
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_repz_scasl_fast:
            {
                extern void op_repz_scasl_fast();
                memcpy(gen_code_ptr, &op_repz_scasl_fast, 77);
                gen_code_ptr += 77;
            }
            break;

            case INDEX_op_repnz_scasl_fast:
            {
                extern void op_repnz_scasl_fast();
                memcpy(gen_code_ptr, &op_repnz_scasl_fast, 77);
                gen_code_ptr += 77;
            }
            break;

            case INDEX_op_cmpsl_fast:
            {
                extern void op_cmpsl_fast();
                memcpy(gen_code_ptr, &op_cmpsl_fast, 30);
                gen_code_ptr += 30;
            }
            break;

            case INDEX_op_repz_cmpsl_fast:
            {
                extern void op_repz_cmpsl_fast();
                memcpy(gen_code_ptr, &op_repz_cmpsl_fast, 81);
                gen_code_ptr += 81;
            }
            break;

            case INDEX_op_repnz_cmpsl_fast:
            {
                extern void op_repnz_cmpsl_fast();
                memcpy(gen_code_ptr, &op_repnz_cmpsl_fast, 81);
                gen_code_ptr += 81;
            }
            break;

            case INDEX_op_outsl_fast:
            {
                extern void op_outsl_fast();
                extern char cpu_x86_outl;
                memcpy(gen_code_ptr, &op_outsl_fast, 26);
                *(uint32_t *)(gen_code_ptr + 11) = (long)(&cpu_x86_outl) - (long)(gen_code_ptr + 11) + -4;
                gen_code_ptr += 26;
            }
            break;

            case INDEX_op_rep_outsl_fast:
            {
                extern void op_rep_outsl_fast();
                extern char cpu_x86_outl;
                memcpy(gen_code_ptr, &op_rep_outsl_fast, 64);
                *(uint32_t *)(gen_code_ptr + 38) = (long)(&cpu_x86_outl) - (long)(gen_code_ptr + 38) + -4;
                gen_code_ptr += 64;
            }
            break;

            case INDEX_op_insl_fast:
            {
                extern void op_insl_fast();
                extern char cpu_x86_inl;
                memcpy(gen_code_ptr, &op_insl_fast, 25);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inl) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_rep_insl_fast:
            {
                extern void op_rep_insl_fast();
                extern char cpu_x86_inl;
                memcpy(gen_code_ptr, &op_rep_insl_fast, 62);
                *(uint32_t *)(gen_code_ptr + 33) = (long)(&cpu_x86_inl) - (long)(gen_code_ptr + 33) + -4;
                gen_code_ptr += 62;
            }
            break;

            case INDEX_op_movsl_a32:
            {
                extern void op_movsl_a32();
                memcpy(gen_code_ptr, &op_movsl_a32, 30);
                gen_code_ptr += 30;
            }
            break;

            case INDEX_op_rep_movsl_a32:
            {
                extern void op_rep_movsl_a32();
                memcpy(gen_code_ptr, &op_rep_movsl_a32, 60);
                gen_code_ptr += 60;
            }
            break;

            case INDEX_op_stosl_a32:
            {
                extern void op_stosl_a32();
                memcpy(gen_code_ptr, &op_stosl_a32, 23);
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_rep_stosl_a32:
            {
                extern void op_rep_stosl_a32();
                memcpy(gen_code_ptr, &op_rep_stosl_a32, 51);
                gen_code_ptr += 51;
            }
            break;

            case INDEX_op_lodsl_a32:
            {
                extern void op_lodsl_a32();
                memcpy(gen_code_ptr, &op_lodsl_a32, 19);
                gen_code_ptr += 19;
            }
            break;

            case INDEX_op_rep_lodsl_a32:
            {
                extern void op_rep_lodsl_a32();
                memcpy(gen_code_ptr, &op_rep_lodsl_a32, 45);
                gen_code_ptr += 45;
            }
            break;

            case INDEX_op_scasl_a32:
            {
                extern void op_scasl_a32();
                memcpy(gen_code_ptr, &op_scasl_a32, 31);
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_repz_scasl_a32:
            {
                extern void op_repz_scasl_a32();
                memcpy(gen_code_ptr, &op_repz_scasl_a32, 91);
                gen_code_ptr += 91;
            }
            break;

            case INDEX_op_repnz_scasl_a32:
            {
                extern void op_repnz_scasl_a32();
                memcpy(gen_code_ptr, &op_repnz_scasl_a32, 91);
                gen_code_ptr += 91;
            }
            break;

            case INDEX_op_cmpsl_a32:
            {
                extern void op_cmpsl_a32();
                memcpy(gen_code_ptr, &op_cmpsl_a32, 38);
                gen_code_ptr += 38;
            }
            break;

            case INDEX_op_repz_cmpsl_a32:
            {
                extern void op_repz_cmpsl_a32();
                memcpy(gen_code_ptr, &op_repz_cmpsl_a32, 99);
                gen_code_ptr += 99;
            }
            break;

            case INDEX_op_repnz_cmpsl_a32:
            {
                extern void op_repnz_cmpsl_a32();
                memcpy(gen_code_ptr, &op_repnz_cmpsl_a32, 99);
                gen_code_ptr += 99;
            }
            break;

            case INDEX_op_outsl_a32:
            {
                extern void op_outsl_a32();
                extern char cpu_x86_outl;
                memcpy(gen_code_ptr, &op_outsl_a32, 28);
                *(uint32_t *)(gen_code_ptr + 13) = (long)(&cpu_x86_outl) - (long)(gen_code_ptr + 13) + -4;
                gen_code_ptr += 28;
            }
            break;

            case INDEX_op_rep_outsl_a32:
            {
                extern void op_rep_outsl_a32();
                extern char cpu_x86_outl;
                memcpy(gen_code_ptr, &op_rep_outsl_a32, 66);
                *(uint32_t *)(gen_code_ptr + 40) = (long)(&cpu_x86_outl) - (long)(gen_code_ptr + 40) + -4;
                gen_code_ptr += 66;
            }
            break;

            case INDEX_op_insl_a32:
            {
                extern void op_insl_a32();
                extern char cpu_x86_inl;
                memcpy(gen_code_ptr, &op_insl_a32, 31);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inl) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_rep_insl_a32:
            {
                extern void op_rep_insl_a32();
                extern char cpu_x86_inl;
                memcpy(gen_code_ptr, &op_rep_insl_a32, 68);
                *(uint32_t *)(gen_code_ptr + 33) = (long)(&cpu_x86_inl) - (long)(gen_code_ptr + 33) + -4;
                gen_code_ptr += 68;
            }
            break;

            case INDEX_op_movsl_a16:
            {
                extern void op_movsl_a16();
                memcpy(gen_code_ptr, &op_movsl_a16, 33);
                gen_code_ptr += 33;
            }
            break;

            case INDEX_op_rep_movsl_a16:
            {
                extern void op_rep_movsl_a16();
                memcpy(gen_code_ptr, &op_rep_movsl_a16, 75);
                gen_code_ptr += 75;
            }
            break;

            case INDEX_op_stosl_a16:
            {
                extern void op_stosl_a16();
                memcpy(gen_code_ptr, &op_stosl_a16, 25);
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_rep_stosl_a16:
            {
                extern void op_rep_stosl_a16();
                memcpy(gen_code_ptr, &op_rep_stosl_a16, 53);
                gen_code_ptr += 53;
            }
            break;

            case INDEX_op_lodsl_a16:
            {
                extern void op_lodsl_a16();
                memcpy(gen_code_ptr, &op_lodsl_a16, 20);
                gen_code_ptr += 20;
            }
            break;

            case INDEX_op_rep_lodsl_a16:
            {
                extern void op_rep_lodsl_a16();
                memcpy(gen_code_ptr, &op_rep_lodsl_a16, 45);
                gen_code_ptr += 45;
            }
            break;

            case INDEX_op_scasl_a16:
            {
                extern void op_scasl_a16();
                memcpy(gen_code_ptr, &op_scasl_a16, 33);
                gen_code_ptr += 33;
            }
            break;

            case INDEX_op_repz_scasl_a16:
            {
                extern void op_repz_scasl_a16();
                memcpy(gen_code_ptr, &op_repz_scasl_a16, 83);
                gen_code_ptr += 83;
            }
            break;

            case INDEX_op_repnz_scasl_a16:
            {
                extern void op_repnz_scasl_a16();
                memcpy(gen_code_ptr, &op_repnz_scasl_a16, 83);
                gen_code_ptr += 83;
            }
            break;

            case INDEX_op_cmpsl_a16:
            {
                extern void op_cmpsl_a16();
                memcpy(gen_code_ptr, &op_cmpsl_a16, 41);
                gen_code_ptr += 41;
            }
            break;

            case INDEX_op_repz_cmpsl_a16:
            {
                extern void op_repz_cmpsl_a16();
                memcpy(gen_code_ptr, &op_repz_cmpsl_a16, 94);
                gen_code_ptr += 94;
            }
            break;

            case INDEX_op_repnz_cmpsl_a16:
            {
                extern void op_repnz_cmpsl_a16();
                memcpy(gen_code_ptr, &op_repnz_cmpsl_a16, 94);
                gen_code_ptr += 94;
            }
            break;

            case INDEX_op_outsl_a16:
            {
                extern void op_outsl_a16();
                extern char cpu_x86_outl;
                memcpy(gen_code_ptr, &op_outsl_a16, 29);
                *(uint32_t *)(gen_code_ptr + 13) = (long)(&cpu_x86_outl) - (long)(gen_code_ptr + 13) + -4;
                gen_code_ptr += 29;
            }
            break;

            case INDEX_op_rep_outsl_a16:
            {
                extern void op_rep_outsl_a16();
                extern char cpu_x86_outl;
                memcpy(gen_code_ptr, &op_rep_outsl_a16, 68);
                *(uint32_t *)(gen_code_ptr + 40) = (long)(&cpu_x86_outl) - (long)(gen_code_ptr + 40) + -4;
                gen_code_ptr += 68;
            }
            break;

            case INDEX_op_insl_a16:
            {
                extern void op_insl_a16();
                extern char cpu_x86_inl;
                memcpy(gen_code_ptr, &op_insl_a16, 33);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inl) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 33;
            }
            break;

            case INDEX_op_rep_insl_a16:
            {
                extern void op_rep_insl_a16();
                extern char cpu_x86_inl;
                memcpy(gen_code_ptr, &op_rep_insl_a16, 71);
                *(uint32_t *)(gen_code_ptr + 33) = (long)(&cpu_x86_inl) - (long)(gen_code_ptr + 33) + -4;
                gen_code_ptr += 71;
            }
            break;

            case INDEX_op_outl_T0_T1:
            {
                extern void op_outl_T0_T1();
                extern char cpu_x86_outl;
                memcpy(gen_code_ptr, &op_outl_T0_T1, 12);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_outl) - (long)(gen_code_ptr + 6) + -4;
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_inl_T0_T1:
            {
                extern void op_inl_T0_T1();
                extern char cpu_x86_inl;
                memcpy(gen_code_ptr, &op_inl_T0_T1, 12);
                *(uint32_t *)(gen_code_ptr + 5) = (long)(&cpu_x86_inl) - (long)(gen_code_ptr + 5) + -4;
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_movsbl_T0_T0:
            {
                extern void op_movsbl_T0_T0();
                memcpy(gen_code_ptr, &op_movsbl_T0_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movzbl_T0_T0:
            {
                extern void op_movzbl_T0_T0();
                memcpy(gen_code_ptr, &op_movzbl_T0_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movswl_T0_T0:
            {
                extern void op_movswl_T0_T0();
                memcpy(gen_code_ptr, &op_movswl_T0_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movzwl_T0_T0:
            {
                extern void op_movzwl_T0_T0();
                memcpy(gen_code_ptr, &op_movzwl_T0_T0, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_movswl_EAX_AX:
            {
                extern void op_movswl_EAX_AX();
                memcpy(gen_code_ptr, &op_movswl_EAX_AX, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movsbw_AX_AL:
            {
                extern void op_movsbw_AX_AL();
                memcpy(gen_code_ptr, &op_movsbw_AX_AL, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_movslq_EDX_EAX:
            {
                extern void op_movslq_EDX_EAX();
                memcpy(gen_code_ptr, &op_movslq_EDX_EAX, 9);
                gen_code_ptr += 9;
            }
            break;

            case INDEX_op_movswl_DX_AX:
            {
                extern void op_movswl_DX_AX();
                memcpy(gen_code_ptr, &op_movswl_DX_AX, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_pushl_T0:
            {
                extern void op_pushl_T0();
                memcpy(gen_code_ptr, &op_pushl_T0, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_pushw_T0:
            {
                extern void op_pushw_T0();
                memcpy(gen_code_ptr, &op_pushw_T0, 13);
                gen_code_ptr += 13;
            }
            break;

            case INDEX_op_pushl_ss32_T0:
            {
                extern void op_pushl_ss32_T0();
                memcpy(gen_code_ptr, &op_pushl_ss32_T0, 19);
                gen_code_ptr += 19;
            }
            break;

            case INDEX_op_pushw_ss32_T0:
            {
                extern void op_pushw_ss32_T0();
                memcpy(gen_code_ptr, &op_pushw_ss32_T0, 20);
                gen_code_ptr += 20;
            }
            break;

            case INDEX_op_pushl_ss16_T0:
            {
                extern void op_pushl_ss16_T0();
                memcpy(gen_code_ptr, &op_pushl_ss16_T0, 25);
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_pushw_ss16_T0:
            {
                extern void op_pushw_ss16_T0();
                memcpy(gen_code_ptr, &op_pushw_ss16_T0, 26);
                gen_code_ptr += 26;
            }
            break;

            case INDEX_op_popl_T0:
            {
                extern void op_popl_T0();
                memcpy(gen_code_ptr, &op_popl_T0, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_popw_T0:
            {
                extern void op_popw_T0();
                memcpy(gen_code_ptr, &op_popw_T0, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_popl_ss32_T0:
            {
                extern void op_popl_ss32_T0();
                memcpy(gen_code_ptr, &op_popl_ss32_T0, 11);
                gen_code_ptr += 11;
            }
            break;

            case INDEX_op_popw_ss32_T0:
            {
                extern void op_popw_ss32_T0();
                memcpy(gen_code_ptr, &op_popw_ss32_T0, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_popl_ss16_T0:
            {
                extern void op_popl_ss16_T0();
                memcpy(gen_code_ptr, &op_popl_ss16_T0, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_popw_ss16_T0:
            {
                extern void op_popw_ss16_T0();
                memcpy(gen_code_ptr, &op_popw_ss16_T0, 13);
                gen_code_ptr += 13;
            }
            break;

            case INDEX_op_addl_ESP_4:
            {
                extern void op_addl_ESP_4();
                memcpy(gen_code_ptr, &op_addl_ESP_4, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_addl_ESP_2:
            {
                extern void op_addl_ESP_2();
                memcpy(gen_code_ptr, &op_addl_ESP_2, 4);
                gen_code_ptr += 4;
            }
            break;

            case INDEX_op_addw_ESP_4:
            {
                extern void op_addw_ESP_4();
                memcpy(gen_code_ptr, &op_addw_ESP_4, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_addw_ESP_2:
            {
                extern void op_addw_ESP_2();
                memcpy(gen_code_ptr, &op_addw_ESP_2, 5);
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_addl_ESP_im:
            {
                long param1;
                extern void op_addl_ESP_im();
                memcpy(gen_code_ptr, &op_addl_ESP_im, 7);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 3) = param1 + 0;
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_addw_ESP_im:
            {
                long param1;
                extern void op_addw_ESP_im();
                memcpy(gen_code_ptr, &op_addw_ESP_im, 12);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 4) = param1 + 0;
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_rdtsc:
            {
                extern void op_rdtsc();
                memcpy(gen_code_ptr, &op_rdtsc, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_cpuid:
            {
                extern void op_cpuid();
                extern char helper_cpuid;
                memcpy(gen_code_ptr, &op_cpuid, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_cpuid) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_aam:
            {
                long param1;
                extern void op_aam();
                memcpy(gen_code_ptr, &op_aam, 36);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                gen_code_ptr += 36;
            }
            break;

            case INDEX_op_aad:
            {
                long param1;
                extern void op_aad();
                memcpy(gen_code_ptr, &op_aad, 23);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = param1 + 0;
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_aaa:
            {
                extern void op_aaa();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_aaa, 153);
                *(uint32_t *)(gen_code_ptr + 9) = (long)(&cc_table) + 0;
                gen_code_ptr += 153;
            }
            break;

            case INDEX_op_aas:
            {
                extern void op_aas();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_aas, 135);
                *(uint32_t *)(gen_code_ptr + 9) = (long)(&cc_table) + 0;
                gen_code_ptr += 135;
            }
            break;

            case INDEX_op_daa:
            {
                extern void op_daa();
                extern char cc_table;
                extern char parity_table;
                memcpy(gen_code_ptr, &op_daa, 138);
                *(uint32_t *)(gen_code_ptr + 9) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 118) = (long)(&parity_table) + 0;
                gen_code_ptr += 138;
            }
            break;

            case INDEX_op_das:
            {
                extern void op_das();
                extern char cc_table;
                extern char parity_table;
                memcpy(gen_code_ptr, &op_das, 162);
                *(uint32_t *)(gen_code_ptr + 9) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 142) = (long)(&parity_table) + 0;
                gen_code_ptr += 162;
            }
            break;

            case INDEX_op_movl_seg_T0:
            {
                long param1;
                extern void op_movl_seg_T0();
                extern char load_seg;
                memcpy(gen_code_ptr, &op_movl_seg_T0, 16);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 10) = (long)(&load_seg) - (long)(gen_code_ptr + 10) + -4;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_movl_T0_seg:
            {
                long param1;
                extern void op_movl_T0_seg();
                memcpy(gen_code_ptr, &op_movl_T0_seg, 12);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_movl_A0_seg:
            {
                long param1;
                extern void op_movl_A0_seg();
                memcpy(gen_code_ptr, &op_movl_A0_seg, 6);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_addl_A0_seg:
            {
                long param1;
                extern void op_addl_A0_seg();
                memcpy(gen_code_ptr, &op_addl_A0_seg, 6);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_jo_cc:
            {
                long param1, param2;
                extern void op_jo_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_jo_cc, 35);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 20) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 31) = param2 + 0;
                gen_code_ptr += 35;
            }
            break;

            case INDEX_op_jb_cc:
            {
                long param1, param2;
                extern void op_jb_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_jb_cc, 31);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                *(uint32_t *)(gen_code_ptr + 17) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 27) = param2 + 0;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_jz_cc:
            {
                long param1, param2;
                extern void op_jz_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_jz_cc, 31);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 18) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 27) = param2 + 0;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_jbe_cc:
            {
                long param1, param2;
                extern void op_jbe_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_jbe_cc, 31);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 18) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 27) = param2 + 0;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_js_cc:
            {
                long param1, param2;
                extern void op_js_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_js_cc, 31);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 17) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 27) = param2 + 0;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_jp_cc:
            {
                long param1, param2;
                extern void op_jp_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_jp_cc, 31);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 18) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 27) = param2 + 0;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_jl_cc:
            {
                long param1, param2;
                extern void op_jl_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_jl_cc, 35);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 22) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 31) = param2 + 0;
                gen_code_ptr += 35;
            }
            break;

            case INDEX_op_jle_cc:
            {
                long param1, param2;
                extern void op_jle_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_jle_cc, 43);
                param1 = *opparam_ptr++;
                param2 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                *(uint32_t *)(gen_code_ptr + 29) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 39) = param2 + 0;
                gen_code_ptr += 43;
            }
            break;

            case INDEX_op_seto_T0_cc:
            {
                extern void op_seto_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_seto_T0_cc, 18);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 18;
            }
            break;

            case INDEX_op_setb_T0_cc:
            {
                extern void op_setb_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_setb_T0_cc, 12);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_setz_T0_cc:
            {
                extern void op_setz_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_setz_T0_cc, 18);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 18;
            }
            break;

            case INDEX_op_setbe_T0_cc:
            {
                extern void op_setbe_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_setbe_T0_cc, 20);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 20;
            }
            break;

            case INDEX_op_sets_T0_cc:
            {
                extern void op_sets_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_sets_T0_cc, 18);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 18;
            }
            break;

            case INDEX_op_setp_T0_cc:
            {
                extern void op_setp_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_setp_T0_cc, 18);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 18;
            }
            break;

            case INDEX_op_setl_T0_cc:
            {
                extern void op_setl_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_setl_T0_cc, 25);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 25;
            }
            break;

            case INDEX_op_setle_T0_cc:
            {
                extern void op_setle_T0_cc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_setle_T0_cc, 40);
                *(uint32_t *)(gen_code_ptr + 7) = (long)(&cc_table) + 0;
                gen_code_ptr += 40;
            }
            break;

            case INDEX_op_xor_T0_1:
            {
                extern void op_xor_T0_1();
                memcpy(gen_code_ptr, &op_xor_T0_1, 3);
                gen_code_ptr += 3;
            }
            break;

            case INDEX_op_set_cc_op:
            {
                long param1;
                extern void op_set_cc_op();
                memcpy(gen_code_ptr, &op_set_cc_op, 7);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 3) = param1 + 0;
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_movl_eflags_T0:
            {
                extern void op_movl_eflags_T0();
                memcpy(gen_code_ptr, &op_movl_eflags_T0, 49);
                gen_code_ptr += 49;
            }
            break;

            case INDEX_op_movw_eflags_T0:
            {
                extern void op_movw_eflags_T0();
                memcpy(gen_code_ptr, &op_movw_eflags_T0, 49);
                gen_code_ptr += 49;
            }
            break;

            case INDEX_op_movw_eflags_T0_vm:
            {
                long param1;
                extern void op_movw_eflags_T0_vm();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_movw_eflags_T0_vm, 88);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 77) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 82) = (long)(&raise_exception) - (long)(gen_code_ptr + 82) + -4;
                gen_code_ptr += 88;
            }
            break;

            case INDEX_op_movl_eflags_T0_vm:
            {
                long param1;
                extern void op_movl_eflags_T0_vm();
                extern char raise_exception;
                memcpy(gen_code_ptr, &op_movl_eflags_T0_vm, 88);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 77) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 82) = (long)(&raise_exception) - (long)(gen_code_ptr + 82) + -4;
                gen_code_ptr += 88;
            }
            break;

            case INDEX_op_movb_eflags_T0:
            {
                extern void op_movb_eflags_T0();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_movb_eflags_T0, 28);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 28;
            }
            break;

            case INDEX_op_movl_T0_eflags:
            {
                extern void op_movl_T0_eflags();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_movl_T0_eflags, 33);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 33;
            }
            break;

            case INDEX_op_movl_T0_eflags_vm:
            {
                extern void op_movl_T0_eflags_vm();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_movl_T0_eflags_vm, 46);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 46;
            }
            break;

            case INDEX_op_cld:
            {
                extern void op_cld();
                memcpy(gen_code_ptr, &op_cld, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_std:
            {
                extern void op_std();
                memcpy(gen_code_ptr, &op_std, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_clc:
            {
                extern void op_clc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_clc, 16);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_stc:
            {
                extern void op_stc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_stc, 16);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_cmc:
            {
                extern void op_cmc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_cmc, 16);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_salc:
            {
                extern void op_salc();
                extern char cc_table;
                memcpy(gen_code_ptr, &op_salc, 15);
                *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
                gen_code_ptr += 15;
            }
            break;

            case INDEX_op_flds_FT0_A0:
            {
                extern void op_flds_FT0_A0();
                memcpy(gen_code_ptr, &op_flds_FT0_A0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_fldl_FT0_A0:
            {
                extern void op_fldl_FT0_A0();
                memcpy(gen_code_ptr, &op_fldl_FT0_A0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_fild_FT0_A0:
            {
                extern void op_fild_FT0_A0();
                memcpy(gen_code_ptr, &op_fild_FT0_A0, 16);
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_fildl_FT0_A0:
            {
                extern void op_fildl_FT0_A0();
                memcpy(gen_code_ptr, &op_fildl_FT0_A0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_fildll_FT0_A0:
            {
                extern void op_fildll_FT0_A0();
                memcpy(gen_code_ptr, &op_fildll_FT0_A0, 8);
                gen_code_ptr += 8;
            }
            break;

            case INDEX_op_flds_ST0_A0:
            {
                extern void op_flds_ST0_A0();
                memcpy(gen_code_ptr, &op_flds_ST0_A0, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_fldl_ST0_A0:
            {
                extern void op_fldl_ST0_A0();
                memcpy(gen_code_ptr, &op_fldl_ST0_A0, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_fldt_ST0_A0:
            {
                extern void op_fldt_ST0_A0();
                memcpy(gen_code_ptr, &op_fldt_ST0_A0, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_fild_ST0_A0:
            {
                extern void op_fild_ST0_A0();
                memcpy(gen_code_ptr, &op_fild_ST0_A0, 20);
                gen_code_ptr += 20;
            }
            break;

            case INDEX_op_fildl_ST0_A0:
            {
                extern void op_fildl_ST0_A0();
                memcpy(gen_code_ptr, &op_fildl_ST0_A0, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_fildll_ST0_A0:
            {
                extern void op_fildll_ST0_A0();
                memcpy(gen_code_ptr, &op_fildll_ST0_A0, 12);
                gen_code_ptr += 12;
            }
            break;

            case INDEX_op_fsts_ST0_A0:
            {
                extern void op_fsts_ST0_A0();
                memcpy(gen_code_ptr, &op_fsts_ST0_A0, 14);
                gen_code_ptr += 14;
            }
            break;

            case INDEX_op_fstl_ST0_A0:
            {
                extern void op_fstl_ST0_A0();
                memcpy(gen_code_ptr, &op_fstl_ST0_A0, 18);
                gen_code_ptr += 18;
            }
            break;

            case INDEX_op_fstt_ST0_A0:
            {
                extern void op_fstt_ST0_A0();
                memcpy(gen_code_ptr, &op_fstt_ST0_A0, 26);
                gen_code_ptr += 26;
            }
            break;

            case INDEX_op_fist_ST0_A0:
            {
                extern void op_fist_ST0_A0();
                extern char lrintl;
                memcpy(gen_code_ptr, &op_fist_ST0_A0, 29);
                *(uint32_t *)(gen_code_ptr + 19) = (long)(&lrintl) - (long)(gen_code_ptr + 19) + -4;
                gen_code_ptr += 29;
            }
            break;

            case INDEX_op_fistl_ST0_A0:
            {
                extern void op_fistl_ST0_A0();
                extern char lrintl;
                memcpy(gen_code_ptr, &op_fistl_ST0_A0, 28);
                *(uint32_t *)(gen_code_ptr + 19) = (long)(&lrintl) - (long)(gen_code_ptr + 19) + -4;
                gen_code_ptr += 28;
            }
            break;

            case INDEX_op_fistll_ST0_A0:
            {
                extern void op_fistll_ST0_A0();
                extern char llrintl;
                memcpy(gen_code_ptr, &op_fistll_ST0_A0, 31);
                *(uint32_t *)(gen_code_ptr + 19) = (long)(&llrintl) - (long)(gen_code_ptr + 19) + -4;
                gen_code_ptr += 31;
            }
            break;

            case INDEX_op_fbld_ST0_A0:
            {
                extern void op_fbld_ST0_A0();
                extern char helper_fbld_ST0_A0;
                memcpy(gen_code_ptr, &op_fbld_ST0_A0, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fbld_ST0_A0) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fbst_ST0_A0:
            {
                extern void op_fbst_ST0_A0();
                extern char helper_fbst_ST0_A0;
                memcpy(gen_code_ptr, &op_fbst_ST0_A0, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fbst_ST0_A0) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fpush:
            {
                extern void op_fpush();
                memcpy(gen_code_ptr, &op_fpush, 15);
                gen_code_ptr += 15;
            }
            break;

            case INDEX_op_fpop:
            {
                extern void op_fpop();
                memcpy(gen_code_ptr, &op_fpop, 15);
                gen_code_ptr += 15;
            }
            break;

            case INDEX_op_fdecstp:
            {
                extern void op_fdecstp();
                memcpy(gen_code_ptr, &op_fdecstp, 17);
                gen_code_ptr += 17;
            }
            break;

            case INDEX_op_fincstp:
            {
                extern void op_fincstp();
                memcpy(gen_code_ptr, &op_fincstp, 17);
                gen_code_ptr += 17;
            }
            break;

            case INDEX_op_fmov_ST0_FT0:
            {
                extern void op_fmov_ST0_FT0();
                memcpy(gen_code_ptr, &op_fmov_ST0_FT0, 16);
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_fmov_FT0_STN:
            {
                long param1;
                extern void op_fmov_FT0_STN();
                memcpy(gen_code_ptr, &op_fmov_FT0_STN, 44);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 4) = param1 + 0;
                gen_code_ptr += 44;
            }
            break;

            case INDEX_op_fmov_ST0_STN:
            {
                long param1;
                extern void op_fmov_ST0_STN();
                memcpy(gen_code_ptr, &op_fmov_ST0_STN, 36);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
                gen_code_ptr += 36;
            }
            break;

            case INDEX_op_fmov_STN_ST0:
            {
                long param1;
                extern void op_fmov_STN_ST0();
                memcpy(gen_code_ptr, &op_fmov_STN_ST0, 36);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                gen_code_ptr += 36;
            }
            break;

            case INDEX_op_fxchg_ST0_STN:
            {
                long param1;
                extern void op_fxchg_ST0_STN();
                memcpy(gen_code_ptr, &op_fxchg_ST0_STN, 64);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                *(uint32_t *)(gen_code_ptr + 23) = param1 + 0;
                gen_code_ptr += 64;
            }
            break;

            case INDEX_op_fcom_ST0_FT0:
            {
                extern void op_fcom_ST0_FT0();
                memcpy(gen_code_ptr, &op_fcom_ST0_FT0, 74);
                gen_code_ptr += 74;
            }
            break;

            case INDEX_op_fucom_ST0_FT0:
            {
                extern void op_fucom_ST0_FT0();
                memcpy(gen_code_ptr, &op_fucom_ST0_FT0, 74);
                gen_code_ptr += 74;
            }
            break;

            case INDEX_op_fadd_ST0_FT0:
            {
                extern void op_fadd_ST0_FT0();
                memcpy(gen_code_ptr, &op_fadd_ST0_FT0, 22);
                gen_code_ptr += 22;
            }
            break;

            case INDEX_op_fmul_ST0_FT0:
            {
                extern void op_fmul_ST0_FT0();
                memcpy(gen_code_ptr, &op_fmul_ST0_FT0, 22);
                gen_code_ptr += 22;
            }
            break;

            case INDEX_op_fsub_ST0_FT0:
            {
                extern void op_fsub_ST0_FT0();
                memcpy(gen_code_ptr, &op_fsub_ST0_FT0, 22);
                gen_code_ptr += 22;
            }
            break;

            case INDEX_op_fsubr_ST0_FT0:
            {
                extern void op_fsubr_ST0_FT0();
                memcpy(gen_code_ptr, &op_fsubr_ST0_FT0, 22);
                gen_code_ptr += 22;
            }
            break;

            case INDEX_op_fdiv_ST0_FT0:
            {
                extern void op_fdiv_ST0_FT0();
                memcpy(gen_code_ptr, &op_fdiv_ST0_FT0, 22);
                gen_code_ptr += 22;
            }
            break;

            case INDEX_op_fdivr_ST0_FT0:
            {
                extern void op_fdivr_ST0_FT0();
                memcpy(gen_code_ptr, &op_fdivr_ST0_FT0, 22);
                gen_code_ptr += 22;
            }
            break;

            case INDEX_op_fadd_STN_ST0:
            {
                long param1;
                extern void op_fadd_STN_ST0();
                memcpy(gen_code_ptr, &op_fadd_STN_ST0, 35);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                gen_code_ptr += 35;
            }
            break;

            case INDEX_op_fmul_STN_ST0:
            {
                long param1;
                extern void op_fmul_STN_ST0();
                memcpy(gen_code_ptr, &op_fmul_STN_ST0, 35);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                gen_code_ptr += 35;
            }
            break;

            case INDEX_op_fsub_STN_ST0:
            {
                long param1;
                extern void op_fsub_STN_ST0();
                memcpy(gen_code_ptr, &op_fsub_STN_ST0, 35);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                gen_code_ptr += 35;
            }
            break;

            case INDEX_op_fsubr_STN_ST0:
            {
                long param1;
                extern void op_fsubr_STN_ST0();
                memcpy(gen_code_ptr, &op_fsubr_STN_ST0, 37);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                gen_code_ptr += 37;
            }
            break;

            case INDEX_op_fdiv_STN_ST0:
            {
                long param1;
                extern void op_fdiv_STN_ST0();
                memcpy(gen_code_ptr, &op_fdiv_STN_ST0, 35);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                gen_code_ptr += 35;
            }
            break;

            case INDEX_op_fdivr_STN_ST0:
            {
                long param1;
                extern void op_fdivr_STN_ST0();
                memcpy(gen_code_ptr, &op_fdivr_STN_ST0, 37);
                param1 = *opparam_ptr++;
                *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
                gen_code_ptr += 37;
            }
            break;

            case INDEX_op_fchs_ST0:
            {
                extern void op_fchs_ST0();
                memcpy(gen_code_ptr, &op_fchs_ST0, 27);
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_fabs_ST0:
            {
                extern void op_fabs_ST0();
                memcpy(gen_code_ptr, &op_fabs_ST0, 27);
                gen_code_ptr += 27;
            }
            break;

            case INDEX_op_fxam_ST0:
            {
                extern void op_fxam_ST0();
                extern char helper_fxam_ST0;
                memcpy(gen_code_ptr, &op_fxam_ST0, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fxam_ST0) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fld1_ST0:
            {
                extern void op_fld1_ST0();
                extern char f15rk;
                memcpy(gen_code_ptr, &op_fld1_ST0, 16);
                *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 10;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_fldl2t_ST0:
            {
                extern void op_fldl2t_ST0();
                extern char f15rk;
                memcpy(gen_code_ptr, &op_fldl2t_ST0, 16);
                *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 60;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_fldl2e_ST0:
            {
                extern void op_fldl2e_ST0();
                extern char f15rk;
                memcpy(gen_code_ptr, &op_fldl2e_ST0, 16);
                *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 50;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_fldpi_ST0:
            {
                extern void op_fldpi_ST0();
                extern char f15rk;
                memcpy(gen_code_ptr, &op_fldpi_ST0, 16);
                *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 20;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_fldlg2_ST0:
            {
                extern void op_fldlg2_ST0();
                extern char f15rk;
                memcpy(gen_code_ptr, &op_fldlg2_ST0, 16);
                *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 30;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_fldln2_ST0:
            {
                extern void op_fldln2_ST0();
                extern char f15rk;
                memcpy(gen_code_ptr, &op_fldln2_ST0, 16);
                *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 40;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_fldz_ST0:
            {
                extern void op_fldz_ST0();
                extern char f15rk;
                memcpy(gen_code_ptr, &op_fldz_ST0, 16);
                *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 0;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_fldz_FT0:
            {
                extern void op_fldz_FT0();
                extern char f15rk;
                memcpy(gen_code_ptr, &op_fldz_FT0, 16);
                *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 0;
                gen_code_ptr += 16;
            }
            break;

            case INDEX_op_f2xm1:
            {
                extern void op_f2xm1();
                extern char helper_f2xm1;
                memcpy(gen_code_ptr, &op_f2xm1, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_f2xm1) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fyl2x:
            {
                extern void op_fyl2x();
                extern char helper_fyl2x;
                memcpy(gen_code_ptr, &op_fyl2x, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fyl2x) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fptan:
            {
                extern void op_fptan();
                extern char helper_fptan;
                memcpy(gen_code_ptr, &op_fptan, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fptan) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fpatan:
            {
                extern void op_fpatan();
                extern char helper_fpatan;
                memcpy(gen_code_ptr, &op_fpatan, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fpatan) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fxtract:
            {
                extern void op_fxtract();
                extern char helper_fxtract;
                memcpy(gen_code_ptr, &op_fxtract, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fxtract) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fprem1:
            {
                extern void op_fprem1();
                extern char helper_fprem1;
                memcpy(gen_code_ptr, &op_fprem1, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fprem1) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fprem:
            {
                extern void op_fprem();
                extern char helper_fprem;
                memcpy(gen_code_ptr, &op_fprem, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fprem) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fyl2xp1:
            {
                extern void op_fyl2xp1();
                extern char helper_fyl2xp1;
                memcpy(gen_code_ptr, &op_fyl2xp1, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fyl2xp1) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fsqrt:
            {
                extern void op_fsqrt();
                extern char helper_fsqrt;
                memcpy(gen_code_ptr, &op_fsqrt, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fsqrt) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fsincos:
            {
                extern void op_fsincos();
                extern char helper_fsincos;
                memcpy(gen_code_ptr, &op_fsincos, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fsincos) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_frndint:
            {
                extern void op_frndint();
                extern char helper_frndint;
                memcpy(gen_code_ptr, &op_frndint, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_frndint) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fscale:
            {
                extern void op_fscale();
                extern char helper_fscale;
                memcpy(gen_code_ptr, &op_fscale, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fscale) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fsin:
            {
                extern void op_fsin();
                extern char helper_fsin;
                memcpy(gen_code_ptr, &op_fsin, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fsin) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fcos:
            {
                extern void op_fcos();
                extern char helper_fcos;
                memcpy(gen_code_ptr, &op_fcos, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fcos) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_fnstsw_A0:
            {
                extern void op_fnstsw_A0();
                memcpy(gen_code_ptr, &op_fnstsw_A0, 23);
                gen_code_ptr += 23;
            }
            break;

            case INDEX_op_fnstsw_EAX:
            {
                extern void op_fnstsw_EAX();
                memcpy(gen_code_ptr, &op_fnstsw_EAX, 33);
                gen_code_ptr += 33;
            }
            break;

            case INDEX_op_fnstcw_A0:
            {
                extern void op_fnstcw_A0();
                memcpy(gen_code_ptr, &op_fnstcw_A0, 6);
                gen_code_ptr += 6;
            }
            break;

            case INDEX_op_fldcw_A0:
            {
                extern void op_fldcw_A0();
                extern char fesetround;
                memcpy(gen_code_ptr, &op_fldcw_A0, 63);
                *(uint32_t *)(gen_code_ptr + 58) = (long)(&fesetround) - (long)(gen_code_ptr + 58) + -4;
                gen_code_ptr += 63;
            }
            break;

            case INDEX_op_fclex:
            {
                extern void op_fclex();
                memcpy(gen_code_ptr, &op_fclex, 7);
                gen_code_ptr += 7;
            }
            break;

            case INDEX_op_fninit:
            {
                extern void op_fninit();
                memcpy(gen_code_ptr, &op_fninit, 53);
                gen_code_ptr += 53;
            }
            break;

            case INDEX_op_lock:
            {
                extern void op_lock();
                extern char cpu_lock;
                memcpy(gen_code_ptr, &op_lock, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&cpu_lock) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            case INDEX_op_unlock:
            {
                extern void op_unlock();
                extern char cpu_unlock;
                memcpy(gen_code_ptr, &op_unlock, 5);
                *(uint32_t *)(gen_code_ptr + 1) = (long)(&cpu_unlock) - (long)(gen_code_ptr + 1) + -4;
                gen_code_ptr += 5;
            }
            break;

            default:
                goto the_end;
        }
    }
the_end:
    *gen_code_ptr++ = 0xc3; /* ret */
    return gen_code_ptr -  gen_code_buf;
}

static inline void gen_op_movl_A0_EAX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_A0_EAX;
}

static inline void gen_op_addl_A0_EAX(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EAX;
}

static inline void gen_op_addl_A0_EAX_s1(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EAX_s1;
}

static inline void gen_op_addl_A0_EAX_s2(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EAX_s2;
}

static inline void gen_op_addl_A0_EAX_s3(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EAX_s3;
}

static inline void gen_op_movl_T0_EAX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_EAX;
}

static inline void gen_op_movl_T1_EAX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T1_EAX;
}

static inline void gen_op_movh_T0_EAX(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T0_EAX;
}

static inline void gen_op_movh_T1_EAX(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T1_EAX;
}

static inline void gen_op_movl_EAX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EAX_T0;
}

static inline void gen_op_movl_EAX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EAX_T1;
}

static inline void gen_op_movl_EAX_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EAX_A0;
}

static inline void gen_op_cmovw_EAX_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovw_EAX_T1_T0;
}

static inline void gen_op_cmovl_EAX_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovl_EAX_T1_T0;
}

static inline void gen_op_movw_EAX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EAX_T0;
}

static inline void gen_op_movw_EAX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EAX_T1;
}

static inline void gen_op_movw_EAX_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EAX_A0;
}

static inline void gen_op_movb_EAX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EAX_T0;
}

static inline void gen_op_movh_EAX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EAX_T0;
}

static inline void gen_op_movb_EAX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EAX_T1;
}

static inline void gen_op_movh_EAX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EAX_T1;
}

static inline void gen_op_movl_A0_ECX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_A0_ECX;
}

static inline void gen_op_addl_A0_ECX(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ECX;
}

static inline void gen_op_addl_A0_ECX_s1(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ECX_s1;
}

static inline void gen_op_addl_A0_ECX_s2(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ECX_s2;
}

static inline void gen_op_addl_A0_ECX_s3(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ECX_s3;
}

static inline void gen_op_movl_T0_ECX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_ECX;
}

static inline void gen_op_movl_T1_ECX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T1_ECX;
}

static inline void gen_op_movh_T0_ECX(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T0_ECX;
}

static inline void gen_op_movh_T1_ECX(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T1_ECX;
}

static inline void gen_op_movl_ECX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_ECX_T0;
}

static inline void gen_op_movl_ECX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_ECX_T1;
}

static inline void gen_op_movl_ECX_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_ECX_A0;
}

static inline void gen_op_cmovw_ECX_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovw_ECX_T1_T0;
}

static inline void gen_op_cmovl_ECX_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovl_ECX_T1_T0;
}

static inline void gen_op_movw_ECX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_ECX_T0;
}

static inline void gen_op_movw_ECX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_ECX_T1;
}

static inline void gen_op_movw_ECX_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_ECX_A0;
}

static inline void gen_op_movb_ECX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_ECX_T0;
}

static inline void gen_op_movh_ECX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_ECX_T0;
}

static inline void gen_op_movb_ECX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_ECX_T1;
}

static inline void gen_op_movh_ECX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_ECX_T1;
}

static inline void gen_op_movl_A0_EDX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_A0_EDX;
}

static inline void gen_op_addl_A0_EDX(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EDX;
}

static inline void gen_op_addl_A0_EDX_s1(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EDX_s1;
}

static inline void gen_op_addl_A0_EDX_s2(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EDX_s2;
}

static inline void gen_op_addl_A0_EDX_s3(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EDX_s3;
}

static inline void gen_op_movl_T0_EDX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_EDX;
}

static inline void gen_op_movl_T1_EDX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T1_EDX;
}

static inline void gen_op_movh_T0_EDX(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T0_EDX;
}

static inline void gen_op_movh_T1_EDX(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T1_EDX;
}

static inline void gen_op_movl_EDX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EDX_T0;
}

static inline void gen_op_movl_EDX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EDX_T1;
}

static inline void gen_op_movl_EDX_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EDX_A0;
}

static inline void gen_op_cmovw_EDX_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovw_EDX_T1_T0;
}

static inline void gen_op_cmovl_EDX_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovl_EDX_T1_T0;
}

static inline void gen_op_movw_EDX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EDX_T0;
}

static inline void gen_op_movw_EDX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EDX_T1;
}

static inline void gen_op_movw_EDX_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EDX_A0;
}

static inline void gen_op_movb_EDX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EDX_T0;
}

static inline void gen_op_movh_EDX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EDX_T0;
}

static inline void gen_op_movb_EDX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EDX_T1;
}

static inline void gen_op_movh_EDX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EDX_T1;
}

static inline void gen_op_movl_A0_EBX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_A0_EBX;
}

static inline void gen_op_addl_A0_EBX(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EBX;
}

static inline void gen_op_addl_A0_EBX_s1(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EBX_s1;
}

static inline void gen_op_addl_A0_EBX_s2(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EBX_s2;
}

static inline void gen_op_addl_A0_EBX_s3(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EBX_s3;
}

static inline void gen_op_movl_T0_EBX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_EBX;
}

static inline void gen_op_movl_T1_EBX(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T1_EBX;
}

static inline void gen_op_movh_T0_EBX(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T0_EBX;
}

static inline void gen_op_movh_T1_EBX(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T1_EBX;
}

static inline void gen_op_movl_EBX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EBX_T0;
}

static inline void gen_op_movl_EBX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EBX_T1;
}

static inline void gen_op_movl_EBX_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EBX_A0;
}

static inline void gen_op_cmovw_EBX_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovw_EBX_T1_T0;
}

static inline void gen_op_cmovl_EBX_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovl_EBX_T1_T0;
}

static inline void gen_op_movw_EBX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EBX_T0;
}

static inline void gen_op_movw_EBX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EBX_T1;
}

static inline void gen_op_movw_EBX_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EBX_A0;
}

static inline void gen_op_movb_EBX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EBX_T0;
}

static inline void gen_op_movh_EBX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EBX_T0;
}

static inline void gen_op_movb_EBX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EBX_T1;
}

static inline void gen_op_movh_EBX_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EBX_T1;
}

static inline void gen_op_movl_A0_ESP(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_A0_ESP;
}

static inline void gen_op_addl_A0_ESP(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ESP;
}

static inline void gen_op_addl_A0_ESP_s1(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ESP_s1;
}

static inline void gen_op_addl_A0_ESP_s2(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ESP_s2;
}

static inline void gen_op_addl_A0_ESP_s3(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ESP_s3;
}

static inline void gen_op_movl_T0_ESP(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_ESP;
}

static inline void gen_op_movl_T1_ESP(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T1_ESP;
}

static inline void gen_op_movh_T0_ESP(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T0_ESP;
}

static inline void gen_op_movh_T1_ESP(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T1_ESP;
}

static inline void gen_op_movl_ESP_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_ESP_T0;
}

static inline void gen_op_movl_ESP_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_ESP_T1;
}

static inline void gen_op_movl_ESP_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_ESP_A0;
}

static inline void gen_op_cmovw_ESP_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovw_ESP_T1_T0;
}

static inline void gen_op_cmovl_ESP_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovl_ESP_T1_T0;
}

static inline void gen_op_movw_ESP_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_ESP_T0;
}

static inline void gen_op_movw_ESP_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_ESP_T1;
}

static inline void gen_op_movw_ESP_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_ESP_A0;
}

static inline void gen_op_movb_ESP_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_ESP_T0;
}

static inline void gen_op_movh_ESP_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_ESP_T0;
}

static inline void gen_op_movb_ESP_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_ESP_T1;
}

static inline void gen_op_movh_ESP_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_ESP_T1;
}

static inline void gen_op_movl_A0_EBP(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_A0_EBP;
}

static inline void gen_op_addl_A0_EBP(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EBP;
}

static inline void gen_op_addl_A0_EBP_s1(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EBP_s1;
}

static inline void gen_op_addl_A0_EBP_s2(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EBP_s2;
}

static inline void gen_op_addl_A0_EBP_s3(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EBP_s3;
}

static inline void gen_op_movl_T0_EBP(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_EBP;
}

static inline void gen_op_movl_T1_EBP(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T1_EBP;
}

static inline void gen_op_movh_T0_EBP(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T0_EBP;
}

static inline void gen_op_movh_T1_EBP(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T1_EBP;
}

static inline void gen_op_movl_EBP_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EBP_T0;
}

static inline void gen_op_movl_EBP_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EBP_T1;
}

static inline void gen_op_movl_EBP_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EBP_A0;
}

static inline void gen_op_cmovw_EBP_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovw_EBP_T1_T0;
}

static inline void gen_op_cmovl_EBP_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovl_EBP_T1_T0;
}

static inline void gen_op_movw_EBP_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EBP_T0;
}

static inline void gen_op_movw_EBP_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EBP_T1;
}

static inline void gen_op_movw_EBP_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EBP_A0;
}

static inline void gen_op_movb_EBP_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EBP_T0;
}

static inline void gen_op_movh_EBP_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EBP_T0;
}

static inline void gen_op_movb_EBP_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EBP_T1;
}

static inline void gen_op_movh_EBP_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EBP_T1;
}

static inline void gen_op_movl_A0_ESI(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_A0_ESI;
}

static inline void gen_op_addl_A0_ESI(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ESI;
}

static inline void gen_op_addl_A0_ESI_s1(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ESI_s1;
}

static inline void gen_op_addl_A0_ESI_s2(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ESI_s2;
}

static inline void gen_op_addl_A0_ESI_s3(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_ESI_s3;
}

static inline void gen_op_movl_T0_ESI(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_ESI;
}

static inline void gen_op_movl_T1_ESI(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T1_ESI;
}

static inline void gen_op_movh_T0_ESI(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T0_ESI;
}

static inline void gen_op_movh_T1_ESI(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T1_ESI;
}

static inline void gen_op_movl_ESI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_ESI_T0;
}

static inline void gen_op_movl_ESI_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_ESI_T1;
}

static inline void gen_op_movl_ESI_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_ESI_A0;
}

static inline void gen_op_cmovw_ESI_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovw_ESI_T1_T0;
}

static inline void gen_op_cmovl_ESI_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovl_ESI_T1_T0;
}

static inline void gen_op_movw_ESI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_ESI_T0;
}

static inline void gen_op_movw_ESI_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_ESI_T1;
}

static inline void gen_op_movw_ESI_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_ESI_A0;
}

static inline void gen_op_movb_ESI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_ESI_T0;
}

static inline void gen_op_movh_ESI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_ESI_T0;
}

static inline void gen_op_movb_ESI_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_ESI_T1;
}

static inline void gen_op_movh_ESI_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_ESI_T1;
}

static inline void gen_op_movl_A0_EDI(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_A0_EDI;
}

static inline void gen_op_addl_A0_EDI(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EDI;
}

static inline void gen_op_addl_A0_EDI_s1(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EDI_s1;
}

static inline void gen_op_addl_A0_EDI_s2(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EDI_s2;
}

static inline void gen_op_addl_A0_EDI_s3(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_EDI_s3;
}

static inline void gen_op_movl_T0_EDI(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_EDI;
}

static inline void gen_op_movl_T1_EDI(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T1_EDI;
}

static inline void gen_op_movh_T0_EDI(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T0_EDI;
}

static inline void gen_op_movh_T1_EDI(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_T1_EDI;
}

static inline void gen_op_movl_EDI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EDI_T0;
}

static inline void gen_op_movl_EDI_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EDI_T1;
}

static inline void gen_op_movl_EDI_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_EDI_A0;
}

static inline void gen_op_cmovw_EDI_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovw_EDI_T1_T0;
}

static inline void gen_op_cmovl_EDI_T1_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_cmovl_EDI_T1_T0;
}

static inline void gen_op_movw_EDI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EDI_T0;
}

static inline void gen_op_movw_EDI_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EDI_T1;
}

static inline void gen_op_movw_EDI_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_EDI_A0;
}

static inline void gen_op_movb_EDI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EDI_T0;
}

static inline void gen_op_movh_EDI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EDI_T0;
}

static inline void gen_op_movb_EDI_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_EDI_T1;
}

static inline void gen_op_movh_EDI_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movh_EDI_T1;
}

static inline void gen_op_addl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_T0_T1_cc;
}

static inline void gen_op_orl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_orl_T0_T1_cc;
}

static inline void gen_op_andl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_andl_T0_T1_cc;
}

static inline void gen_op_subl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_subl_T0_T1_cc;
}

static inline void gen_op_xorl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_xorl_T0_T1_cc;
}

static inline void gen_op_cmpl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpl_T0_T1_cc;
}

static inline void gen_op_negl_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_negl_T0_cc;
}

static inline void gen_op_incl_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_incl_T0_cc;
}

static inline void gen_op_decl_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_decl_T0_cc;
}

static inline void gen_op_testl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_testl_T0_T1_cc;
}

static inline void gen_op_addl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_T0_T1;
}

static inline void gen_op_orl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_orl_T0_T1;
}

static inline void gen_op_andl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_andl_T0_T1;
}

static inline void gen_op_subl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_subl_T0_T1;
}

static inline void gen_op_xorl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_xorl_T0_T1;
}

static inline void gen_op_negl_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_negl_T0;
}

static inline void gen_op_incl_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_incl_T0;
}

static inline void gen_op_decl_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_decl_T0;
}

static inline void gen_op_notl_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_notl_T0;
}

static inline void gen_op_bswapl_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_bswapl_T0;
}

static inline void gen_op_mulb_AL_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_mulb_AL_T0;
}

static inline void gen_op_imulb_AL_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_imulb_AL_T0;
}

static inline void gen_op_mulw_AX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_mulw_AX_T0;
}

static inline void gen_op_imulw_AX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_imulw_AX_T0;
}

static inline void gen_op_mull_EAX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_mull_EAX_T0;
}

static inline void gen_op_imull_EAX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_imull_EAX_T0;
}

static inline void gen_op_imulw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_imulw_T0_T1;
}

static inline void gen_op_imull_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_imull_T0_T1;
}

static inline void gen_op_divb_AL_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_divb_AL_T0;
}

static inline void gen_op_idivb_AL_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_idivb_AL_T0;
}

static inline void gen_op_divw_AX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_divw_AX_T0;
}

static inline void gen_op_idivw_AX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_idivw_AX_T0;
}

static inline void gen_op_divl_EAX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_divl_EAX_T0;
}

static inline void gen_op_idivl_EAX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_idivl_EAX_T0;
}

static inline void gen_op_movl_T0_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_T0_im;
}

static inline void gen_op_addl_T0_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_addl_T0_im;
}

static inline void gen_op_andl_T0_ffff(void)
{
    *gen_opc_ptr++ = INDEX_op_andl_T0_ffff;
}

static inline void gen_op_movl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_T1;
}

static inline void gen_op_movl_T1_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_T1_im;
}

static inline void gen_op_addl_T1_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_addl_T1_im;
}

static inline void gen_op_movl_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T1_A0;
}

static inline void gen_op_movl_A0_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_A0_im;
}

static inline void gen_op_addl_A0_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_addl_A0_im;
}

static inline void gen_op_addl_A0_AL(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_A0_AL;
}

static inline void gen_op_andl_A0_ffff(void)
{
    *gen_opc_ptr++ = INDEX_op_andl_A0_ffff;
}

static inline void gen_op_ldub_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldub_T0_A0;
}

static inline void gen_op_ldsb_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsb_T0_A0;
}

static inline void gen_op_lduw_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_lduw_T0_A0;
}

static inline void gen_op_ldsw_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsw_T0_A0;
}

static inline void gen_op_ldl_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldl_T0_A0;
}

static inline void gen_op_ldub_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldub_T1_A0;
}

static inline void gen_op_ldsb_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsb_T1_A0;
}

static inline void gen_op_lduw_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_lduw_T1_A0;
}

static inline void gen_op_ldsw_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsw_T1_A0;
}

static inline void gen_op_ldl_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldl_T1_A0;
}

static inline void gen_op_stb_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_stb_T0_A0;
}

static inline void gen_op_stw_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_stw_T0_A0;
}

static inline void gen_op_stl_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_stl_T0_A0;
}

static inline void gen_op_add_bitw_A0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_add_bitw_A0_T1;
}

static inline void gen_op_add_bitl_A0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_add_bitl_A0_T1;
}

static inline void gen_op_jmp_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_jmp_T0;
}

static inline void gen_op_jmp_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_jmp_im;
}

static inline void gen_op_int_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_int_im;
}

static inline void gen_op_int3(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_int3;
}

static inline void gen_op_into(void)
{
    *gen_opc_ptr++ = INDEX_op_into;
}

static inline void gen_op_cli(void)
{
    *gen_opc_ptr++ = INDEX_op_cli;
}

static inline void gen_op_sti(void)
{
    *gen_opc_ptr++ = INDEX_op_sti;
}

static inline void gen_op_cli_vm(void)
{
    *gen_opc_ptr++ = INDEX_op_cli_vm;
}

static inline void gen_op_sti_vm(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_sti_vm;
}

static inline void gen_op_boundw(void)
{
    *gen_opc_ptr++ = INDEX_op_boundw;
}

static inline void gen_op_boundl(void)
{
    *gen_opc_ptr++ = INDEX_op_boundl;
}

static inline void gen_op_cmpxchg8b(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpxchg8b;
}

static inline void gen_op_jb_subb(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jb_subb;
}

static inline void gen_op_jz_subb(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jz_subb;
}

static inline void gen_op_jbe_subb(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jbe_subb;
}

static inline void gen_op_js_subb(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_js_subb;
}

static inline void gen_op_jl_subb(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jl_subb;
}

static inline void gen_op_jle_subb(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jle_subb;
}

static inline void gen_op_setb_T0_subb(void)
{
    *gen_opc_ptr++ = INDEX_op_setb_T0_subb;
}

static inline void gen_op_setz_T0_subb(void)
{
    *gen_opc_ptr++ = INDEX_op_setz_T0_subb;
}

static inline void gen_op_setbe_T0_subb(void)
{
    *gen_opc_ptr++ = INDEX_op_setbe_T0_subb;
}

static inline void gen_op_sets_T0_subb(void)
{
    *gen_opc_ptr++ = INDEX_op_sets_T0_subb;
}

static inline void gen_op_setl_T0_subb(void)
{
    *gen_opc_ptr++ = INDEX_op_setl_T0_subb;
}

static inline void gen_op_setle_T0_subb(void)
{
    *gen_opc_ptr++ = INDEX_op_setle_T0_subb;
}

static inline void gen_op_rolb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rolb_T0_T1_cc;
}

static inline void gen_op_rolb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rolb_T0_T1;
}

static inline void gen_op_rorb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rorb_T0_T1_cc;
}

static inline void gen_op_rorb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rorb_T0_T1;
}

static inline void gen_op_rclb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rclb_T0_T1_cc;
}

static inline void gen_op_rcrb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rcrb_T0_T1_cc;
}

static inline void gen_op_shlb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shlb_T0_T1_cc;
}

static inline void gen_op_shlb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shlb_T0_T1;
}

static inline void gen_op_shrb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrb_T0_T1_cc;
}

static inline void gen_op_shrb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shrb_T0_T1;
}

static inline void gen_op_sarb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sarb_T0_T1_cc;
}

static inline void gen_op_sarb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_sarb_T0_T1;
}

static inline void gen_op_adcb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_adcb_T0_T1_cc;
}

static inline void gen_op_sbbb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sbbb_T0_T1_cc;
}

static inline void gen_op_cmpxchgb_T0_T1_EAX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpxchgb_T0_T1_EAX_cc;
}

static inline void gen_op_movsb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_movsb_fast;
}

static inline void gen_op_rep_movsb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_movsb_fast;
}

static inline void gen_op_stosb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_stosb_fast;
}

static inline void gen_op_rep_stosb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_stosb_fast;
}

static inline void gen_op_lodsb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_lodsb_fast;
}

static inline void gen_op_rep_lodsb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_lodsb_fast;
}

static inline void gen_op_scasb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_scasb_fast;
}

static inline void gen_op_repz_scasb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_scasb_fast;
}

static inline void gen_op_repnz_scasb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_scasb_fast;
}

static inline void gen_op_cmpsb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpsb_fast;
}

static inline void gen_op_repz_cmpsb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_cmpsb_fast;
}

static inline void gen_op_repnz_cmpsb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_cmpsb_fast;
}

static inline void gen_op_outsb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_outsb_fast;
}

static inline void gen_op_rep_outsb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_outsb_fast;
}

static inline void gen_op_insb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_insb_fast;
}

static inline void gen_op_rep_insb_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_insb_fast;
}

static inline void gen_op_movsb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_movsb_a32;
}

static inline void gen_op_rep_movsb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_movsb_a32;
}

static inline void gen_op_stosb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_stosb_a32;
}

static inline void gen_op_rep_stosb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_stosb_a32;
}

static inline void gen_op_lodsb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_lodsb_a32;
}

static inline void gen_op_rep_lodsb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_lodsb_a32;
}

static inline void gen_op_scasb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_scasb_a32;
}

static inline void gen_op_repz_scasb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_scasb_a32;
}

static inline void gen_op_repnz_scasb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_scasb_a32;
}

static inline void gen_op_cmpsb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpsb_a32;
}

static inline void gen_op_repz_cmpsb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_cmpsb_a32;
}

static inline void gen_op_repnz_cmpsb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_cmpsb_a32;
}

static inline void gen_op_outsb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_outsb_a32;
}

static inline void gen_op_rep_outsb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_outsb_a32;
}

static inline void gen_op_insb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_insb_a32;
}

static inline void gen_op_rep_insb_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_insb_a32;
}

static inline void gen_op_movsb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_movsb_a16;
}

static inline void gen_op_rep_movsb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_movsb_a16;
}

static inline void gen_op_stosb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_stosb_a16;
}

static inline void gen_op_rep_stosb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_stosb_a16;
}

static inline void gen_op_lodsb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_lodsb_a16;
}

static inline void gen_op_rep_lodsb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_lodsb_a16;
}

static inline void gen_op_scasb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_scasb_a16;
}

static inline void gen_op_repz_scasb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_scasb_a16;
}

static inline void gen_op_repnz_scasb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_scasb_a16;
}

static inline void gen_op_cmpsb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpsb_a16;
}

static inline void gen_op_repz_cmpsb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_cmpsb_a16;
}

static inline void gen_op_repnz_cmpsb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_cmpsb_a16;
}

static inline void gen_op_outsb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_outsb_a16;
}

static inline void gen_op_rep_outsb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_outsb_a16;
}

static inline void gen_op_insb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_insb_a16;
}

static inline void gen_op_rep_insb_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_insb_a16;
}

static inline void gen_op_outb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_outb_T0_T1;
}

static inline void gen_op_inb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_inb_T0_T1;
}

static inline void gen_op_jb_subw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jb_subw;
}

static inline void gen_op_jz_subw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jz_subw;
}

static inline void gen_op_jbe_subw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jbe_subw;
}

static inline void gen_op_js_subw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_js_subw;
}

static inline void gen_op_jl_subw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jl_subw;
}

static inline void gen_op_jle_subw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jle_subw;
}

static inline void gen_op_loopnzw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_loopnzw;
}

static inline void gen_op_loopzw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_loopzw;
}

static inline void gen_op_loopw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_loopw;
}

static inline void gen_op_jecxzw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jecxzw;
}

static inline void gen_op_setb_T0_subw(void)
{
    *gen_opc_ptr++ = INDEX_op_setb_T0_subw;
}

static inline void gen_op_setz_T0_subw(void)
{
    *gen_opc_ptr++ = INDEX_op_setz_T0_subw;
}

static inline void gen_op_setbe_T0_subw(void)
{
    *gen_opc_ptr++ = INDEX_op_setbe_T0_subw;
}

static inline void gen_op_sets_T0_subw(void)
{
    *gen_opc_ptr++ = INDEX_op_sets_T0_subw;
}

static inline void gen_op_setl_T0_subw(void)
{
    *gen_opc_ptr++ = INDEX_op_setl_T0_subw;
}

static inline void gen_op_setle_T0_subw(void)
{
    *gen_opc_ptr++ = INDEX_op_setle_T0_subw;
}

static inline void gen_op_rolw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rolw_T0_T1_cc;
}

static inline void gen_op_rolw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rolw_T0_T1;
}

static inline void gen_op_rorw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rorw_T0_T1_cc;
}

static inline void gen_op_rorw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rorw_T0_T1;
}

static inline void gen_op_rclw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rclw_T0_T1_cc;
}

static inline void gen_op_rcrw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rcrw_T0_T1_cc;
}

static inline void gen_op_shlw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shlw_T0_T1_cc;
}

static inline void gen_op_shlw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shlw_T0_T1;
}

static inline void gen_op_shrw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrw_T0_T1_cc;
}

static inline void gen_op_shrw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shrw_T0_T1;
}

static inline void gen_op_sarw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sarw_T0_T1_cc;
}

static inline void gen_op_sarw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_sarw_T0_T1;
}

static inline void gen_op_shldw_T0_T1_im_cc(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_shldw_T0_T1_im_cc;
}

static inline void gen_op_shldw_T0_T1_ECX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shldw_T0_T1_ECX_cc;
}

static inline void gen_op_shrdw_T0_T1_im_cc(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_shrdw_T0_T1_im_cc;
}

static inline void gen_op_shrdw_T0_T1_ECX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrdw_T0_T1_ECX_cc;
}

static inline void gen_op_adcw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_adcw_T0_T1_cc;
}

static inline void gen_op_sbbw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sbbw_T0_T1_cc;
}

static inline void gen_op_cmpxchgw_T0_T1_EAX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpxchgw_T0_T1_EAX_cc;
}

static inline void gen_op_btw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_btw_T0_T1_cc;
}

static inline void gen_op_btsw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_btsw_T0_T1_cc;
}

static inline void gen_op_btrw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_btrw_T0_T1_cc;
}

static inline void gen_op_btcw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_btcw_T0_T1_cc;
}

static inline void gen_op_bsfw_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_bsfw_T0_cc;
}

static inline void gen_op_bsrw_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_bsrw_T0_cc;
}

static inline void gen_op_movsw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_movsw_fast;
}

static inline void gen_op_rep_movsw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_movsw_fast;
}

static inline void gen_op_stosw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_stosw_fast;
}

static inline void gen_op_rep_stosw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_stosw_fast;
}

static inline void gen_op_lodsw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_lodsw_fast;
}

static inline void gen_op_rep_lodsw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_lodsw_fast;
}

static inline void gen_op_scasw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_scasw_fast;
}

static inline void gen_op_repz_scasw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_scasw_fast;
}

static inline void gen_op_repnz_scasw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_scasw_fast;
}

static inline void gen_op_cmpsw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpsw_fast;
}

static inline void gen_op_repz_cmpsw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_cmpsw_fast;
}

static inline void gen_op_repnz_cmpsw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_cmpsw_fast;
}

static inline void gen_op_outsw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_outsw_fast;
}

static inline void gen_op_rep_outsw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_outsw_fast;
}

static inline void gen_op_insw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_insw_fast;
}

static inline void gen_op_rep_insw_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_insw_fast;
}

static inline void gen_op_movsw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_movsw_a32; /* 2字节记录一个操作符 */
}

static inline void gen_op_rep_movsw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_movsw_a32;
}

static inline void gen_op_stosw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_stosw_a32;
}

static inline void gen_op_rep_stosw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_stosw_a32;
}

static inline void gen_op_lodsw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_lodsw_a32;
}

static inline void gen_op_rep_lodsw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_lodsw_a32;
}

static inline void gen_op_scasw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_scasw_a32;
}

static inline void gen_op_repz_scasw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_scasw_a32;
}

static inline void gen_op_repnz_scasw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_scasw_a32;
}

static inline void gen_op_cmpsw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpsw_a32;
}

static inline void gen_op_repz_cmpsw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_cmpsw_a32;
}

static inline void gen_op_repnz_cmpsw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_cmpsw_a32;
}

static inline void gen_op_outsw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_outsw_a32;
}

static inline void gen_op_rep_outsw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_outsw_a32;
}

static inline void gen_op_insw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_insw_a32;
}

static inline void gen_op_rep_insw_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_insw_a32;
}

static inline void gen_op_movsw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_movsw_a16;
}

static inline void gen_op_rep_movsw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_movsw_a16;
}

static inline void gen_op_stosw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_stosw_a16;
}

static inline void gen_op_rep_stosw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_stosw_a16;
}

static inline void gen_op_lodsw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_lodsw_a16;
}

static inline void gen_op_rep_lodsw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_lodsw_a16;
}

static inline void gen_op_scasw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_scasw_a16;
}

static inline void gen_op_repz_scasw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_scasw_a16;
}

static inline void gen_op_repnz_scasw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_scasw_a16;
}

static inline void gen_op_cmpsw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpsw_a16;
}

static inline void gen_op_repz_cmpsw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_cmpsw_a16;
}

static inline void gen_op_repnz_cmpsw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_cmpsw_a16;
}

static inline void gen_op_outsw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_outsw_a16;
}

static inline void gen_op_rep_outsw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_outsw_a16;
}

static inline void gen_op_insw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_insw_a16;
}

static inline void gen_op_rep_insw_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_insw_a16;
}

static inline void gen_op_outw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_outw_T0_T1;
}

static inline void gen_op_inw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_inw_T0_T1;
}

static inline void gen_op_jb_subl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jb_subl;
}

static inline void gen_op_jz_subl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jz_subl;
}

static inline void gen_op_jbe_subl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jbe_subl;
}

static inline void gen_op_js_subl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_js_subl;
}

static inline void gen_op_jl_subl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jl_subl;
}

static inline void gen_op_jle_subl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jle_subl;
}

static inline void gen_op_loopnzl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_loopnzl;
}

static inline void gen_op_loopzl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_loopzl;
}

static inline void gen_op_loopl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_loopl;
}

static inline void gen_op_jecxzl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jecxzl;
}

static inline void gen_op_setb_T0_subl(void)
{
    *gen_opc_ptr++ = INDEX_op_setb_T0_subl;
}

static inline void gen_op_setz_T0_subl(void)
{
    *gen_opc_ptr++ = INDEX_op_setz_T0_subl;
}

static inline void gen_op_setbe_T0_subl(void)
{
    *gen_opc_ptr++ = INDEX_op_setbe_T0_subl;
}

static inline void gen_op_sets_T0_subl(void)
{
    *gen_opc_ptr++ = INDEX_op_sets_T0_subl;
}

static inline void gen_op_setl_T0_subl(void)
{
    *gen_opc_ptr++ = INDEX_op_setl_T0_subl;
}

static inline void gen_op_setle_T0_subl(void)
{
    *gen_opc_ptr++ = INDEX_op_setle_T0_subl;
}

static inline void gen_op_roll_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_roll_T0_T1_cc;
}

static inline void gen_op_roll_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_roll_T0_T1;
}

static inline void gen_op_rorl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rorl_T0_T1_cc;
}

static inline void gen_op_rorl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rorl_T0_T1;
}

static inline void gen_op_rcll_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rcll_T0_T1_cc;
}

static inline void gen_op_rcrl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rcrl_T0_T1_cc;
}

static inline void gen_op_shll_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shll_T0_T1_cc;
}

static inline void gen_op_shll_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shll_T0_T1;
}

static inline void gen_op_shrl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrl_T0_T1_cc;
}

static inline void gen_op_shrl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shrl_T0_T1;
}

static inline void gen_op_sarl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sarl_T0_T1_cc;
}

static inline void gen_op_sarl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_sarl_T0_T1;
}

static inline void gen_op_shldl_T0_T1_im_cc(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_shldl_T0_T1_im_cc;
}

static inline void gen_op_shldl_T0_T1_ECX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shldl_T0_T1_ECX_cc;
}

static inline void gen_op_shrdl_T0_T1_im_cc(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_shrdl_T0_T1_im_cc;
}

static inline void gen_op_shrdl_T0_T1_ECX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrdl_T0_T1_ECX_cc;
}

static inline void gen_op_adcl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_adcl_T0_T1_cc;
}

static inline void gen_op_sbbl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sbbl_T0_T1_cc;
}

static inline void gen_op_cmpxchgl_T0_T1_EAX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpxchgl_T0_T1_EAX_cc;
}

static inline void gen_op_btl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_btl_T0_T1_cc;
}

static inline void gen_op_btsl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_btsl_T0_T1_cc;
}

static inline void gen_op_btrl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_btrl_T0_T1_cc;
}

static inline void gen_op_btcl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_btcl_T0_T1_cc;
}

static inline void gen_op_bsfl_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_bsfl_T0_cc;
}

static inline void gen_op_bsrl_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_bsrl_T0_cc;
}

static inline void gen_op_movsl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_movsl_fast;
}

static inline void gen_op_rep_movsl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_movsl_fast;
}

static inline void gen_op_stosl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_stosl_fast;
}

static inline void gen_op_rep_stosl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_stosl_fast;
}

static inline void gen_op_lodsl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_lodsl_fast;
}

static inline void gen_op_rep_lodsl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_lodsl_fast;
}

static inline void gen_op_scasl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_scasl_fast;
}

static inline void gen_op_repz_scasl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_scasl_fast;
}

static inline void gen_op_repnz_scasl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_scasl_fast;
}

static inline void gen_op_cmpsl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpsl_fast;
}

static inline void gen_op_repz_cmpsl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_cmpsl_fast;
}

static inline void gen_op_repnz_cmpsl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_cmpsl_fast;
}

static inline void gen_op_outsl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_outsl_fast;
}

static inline void gen_op_rep_outsl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_outsl_fast;
}

static inline void gen_op_insl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_insl_fast;
}

static inline void gen_op_rep_insl_fast(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_insl_fast;
}

static inline void gen_op_movsl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_movsl_a32;
}

static inline void gen_op_rep_movsl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_movsl_a32;
}

static inline void gen_op_stosl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_stosl_a32;
}

static inline void gen_op_rep_stosl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_stosl_a32;
}

static inline void gen_op_lodsl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_lodsl_a32;
}

static inline void gen_op_rep_lodsl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_lodsl_a32;
}

static inline void gen_op_scasl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_scasl_a32;
}

static inline void gen_op_repz_scasl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_scasl_a32;
}

static inline void gen_op_repnz_scasl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_scasl_a32;
}

static inline void gen_op_cmpsl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpsl_a32;
}

static inline void gen_op_repz_cmpsl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_cmpsl_a32;
}

static inline void gen_op_repnz_cmpsl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_cmpsl_a32;
}

static inline void gen_op_outsl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_outsl_a32;
}

static inline void gen_op_rep_outsl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_outsl_a32;
}

static inline void gen_op_insl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_insl_a32;
}

static inline void gen_op_rep_insl_a32(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_insl_a32;
}

static inline void gen_op_movsl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_movsl_a16;
}

static inline void gen_op_rep_movsl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_movsl_a16;
}

static inline void gen_op_stosl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_stosl_a16;
}

static inline void gen_op_rep_stosl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_stosl_a16;
}

static inline void gen_op_lodsl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_lodsl_a16;
}

static inline void gen_op_rep_lodsl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_lodsl_a16;
}

static inline void gen_op_scasl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_scasl_a16;
}

static inline void gen_op_repz_scasl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_scasl_a16;
}

static inline void gen_op_repnz_scasl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_scasl_a16;
}

static inline void gen_op_cmpsl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpsl_a16;
}

static inline void gen_op_repz_cmpsl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repz_cmpsl_a16;
}

static inline void gen_op_repnz_cmpsl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_repnz_cmpsl_a16;
}

static inline void gen_op_outsl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_outsl_a16;
}

static inline void gen_op_rep_outsl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_outsl_a16;
}

static inline void gen_op_insl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_insl_a16;
}

static inline void gen_op_rep_insl_a16(void)
{
    *gen_opc_ptr++ = INDEX_op_rep_insl_a16;
}

static inline void gen_op_outl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_outl_T0_T1;
}

static inline void gen_op_inl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_inl_T0_T1;
}

static inline void gen_op_movsbl_T0_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movsbl_T0_T0;
}

static inline void gen_op_movzbl_T0_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movzbl_T0_T0;
}

static inline void gen_op_movswl_T0_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movswl_T0_T0;
}

static inline void gen_op_movzwl_T0_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movzwl_T0_T0;
}

static inline void gen_op_movswl_EAX_AX(void)
{
    *gen_opc_ptr++ = INDEX_op_movswl_EAX_AX;
}

static inline void gen_op_movsbw_AX_AL(void)
{
    *gen_opc_ptr++ = INDEX_op_movsbw_AX_AL;
}

static inline void gen_op_movslq_EDX_EAX(void)
{
    *gen_opc_ptr++ = INDEX_op_movslq_EDX_EAX;
}

static inline void gen_op_movswl_DX_AX(void)
{
    *gen_opc_ptr++ = INDEX_op_movswl_DX_AX;
}

static inline void gen_op_pushl_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_pushl_T0;
}

static inline void gen_op_pushw_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_pushw_T0;
}

static inline void gen_op_pushl_ss32_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_pushl_ss32_T0;
}

static inline void gen_op_pushw_ss32_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_pushw_ss32_T0;
}

static inline void gen_op_pushl_ss16_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_pushl_ss16_T0;
}

static inline void gen_op_pushw_ss16_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_pushw_ss16_T0;
}

static inline void gen_op_popl_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_popl_T0;
}

static inline void gen_op_popw_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_popw_T0;
}

static inline void gen_op_popl_ss32_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_popl_ss32_T0;
}

static inline void gen_op_popw_ss32_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_popw_ss32_T0;
}

static inline void gen_op_popl_ss16_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_popl_ss16_T0;
}

static inline void gen_op_popw_ss16_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_popw_ss16_T0;
}

static inline void gen_op_addl_ESP_4(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_ESP_4;
}

static inline void gen_op_addl_ESP_2(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_ESP_2;
}

static inline void gen_op_addw_ESP_4(void)
{
    *gen_opc_ptr++ = INDEX_op_addw_ESP_4;
}

static inline void gen_op_addw_ESP_2(void)
{
    *gen_opc_ptr++ = INDEX_op_addw_ESP_2;
}

static inline void gen_op_addl_ESP_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_addl_ESP_im;
}

static inline void gen_op_addw_ESP_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_addw_ESP_im;
}

static inline void gen_op_rdtsc(void)
{
    *gen_opc_ptr++ = INDEX_op_rdtsc;
}

static inline void gen_op_cpuid(void)
{
    *gen_opc_ptr++ = INDEX_op_cpuid;
}

static inline void gen_op_aam(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_aam;
}

static inline void gen_op_aad(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_aad;
}

static inline void gen_op_aaa(void)
{
    *gen_opc_ptr++ = INDEX_op_aaa;
}

static inline void gen_op_aas(void)
{
    *gen_opc_ptr++ = INDEX_op_aas;
}

static inline void gen_op_daa(void)
{
    *gen_opc_ptr++ = INDEX_op_daa;
}

static inline void gen_op_das(void)
{
    *gen_opc_ptr++ = INDEX_op_das;
}

static inline void gen_op_movl_seg_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_seg_T0;
}

static inline void gen_op_movl_T0_seg(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_T0_seg;
}

static inline void gen_op_movl_A0_seg(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_A0_seg;
}

static inline void gen_op_addl_A0_seg(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_addl_A0_seg;
}

static inline void gen_op_jo_cc(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jo_cc;
}

static inline void gen_op_jb_cc(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jb_cc;
}

static inline void gen_op_jz_cc(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jz_cc;
}

static inline void gen_op_jbe_cc(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jbe_cc;
}

static inline void gen_op_js_cc(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_js_cc;
}

static inline void gen_op_jp_cc(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jp_cc;
}

static inline void gen_op_jl_cc(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jl_cc;
}

static inline void gen_op_jle_cc(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jle_cc;
}

static inline void gen_op_seto_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_seto_T0_cc;
}

static inline void gen_op_setb_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_setb_T0_cc;
}

static inline void gen_op_setz_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_setz_T0_cc;
}

static inline void gen_op_setbe_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_setbe_T0_cc;
}

static inline void gen_op_sets_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sets_T0_cc;
}

static inline void gen_op_setp_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_setp_T0_cc;
}

static inline void gen_op_setl_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_setl_T0_cc;
}

static inline void gen_op_setle_T0_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_setle_T0_cc;
}

static inline void gen_op_xor_T0_1(void)
{
    *gen_opc_ptr++ = INDEX_op_xor_T0_1;
}

static inline void gen_op_set_cc_op(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_set_cc_op;
}

static inline void gen_op_movl_eflags_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_eflags_T0;
}

static inline void gen_op_movw_eflags_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_eflags_T0;
}

static inline void gen_op_movw_eflags_T0_vm(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movw_eflags_T0_vm;
}

static inline void gen_op_movl_eflags_T0_vm(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_eflags_T0_vm;
}

static inline void gen_op_movb_eflags_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_eflags_T0;
}

static inline void gen_op_movl_T0_eflags(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_eflags;
}

static inline void gen_op_movl_T0_eflags_vm(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_eflags_vm;
}

static inline void gen_op_cld(void)
{
    *gen_opc_ptr++ = INDEX_op_cld;
}

static inline void gen_op_std(void)
{
    *gen_opc_ptr++ = INDEX_op_std;
}

static inline void gen_op_clc(void)
{
    *gen_opc_ptr++ = INDEX_op_clc;
}

static inline void gen_op_stc(void)
{
    *gen_opc_ptr++ = INDEX_op_stc;
}

static inline void gen_op_cmc(void)
{
    *gen_opc_ptr++ = INDEX_op_cmc;
}

static inline void gen_op_salc(void)
{
    *gen_opc_ptr++ = INDEX_op_salc;
}

static inline void gen_op_flds_FT0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_flds_FT0_A0;
}

static inline void gen_op_fldl_FT0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldl_FT0_A0;
}

static inline void gen_op_fild_FT0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fild_FT0_A0;
}

static inline void gen_op_fildl_FT0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fildl_FT0_A0;
}

static inline void gen_op_fildll_FT0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fildll_FT0_A0;
}

static inline void gen_op_flds_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_flds_ST0_A0;
}

static inline void gen_op_fldl_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldl_ST0_A0;
}

static inline void gen_op_fldt_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldt_ST0_A0;
}

static inline void gen_op_fild_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fild_ST0_A0;
}

static inline void gen_op_fildl_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fildl_ST0_A0;
}

static inline void gen_op_fildll_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fildll_ST0_A0;
}

static inline void gen_op_fsts_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fsts_ST0_A0;
}

static inline void gen_op_fstl_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fstl_ST0_A0;
}

static inline void gen_op_fstt_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fstt_ST0_A0;
}

static inline void gen_op_fist_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fist_ST0_A0;
}

static inline void gen_op_fistl_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fistl_ST0_A0;
}

static inline void gen_op_fistll_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fistll_ST0_A0;
}

static inline void gen_op_fbld_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fbld_ST0_A0;
}

static inline void gen_op_fbst_ST0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fbst_ST0_A0;
}

static inline void gen_op_fpush(void)
{
    *gen_opc_ptr++ = INDEX_op_fpush;
}

static inline void gen_op_fpop(void)
{
    *gen_opc_ptr++ = INDEX_op_fpop;
}

static inline void gen_op_fdecstp(void)
{
    *gen_opc_ptr++ = INDEX_op_fdecstp;
}

static inline void gen_op_fincstp(void)
{
    *gen_opc_ptr++ = INDEX_op_fincstp;
}

static inline void gen_op_fmov_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fmov_ST0_FT0;
}

static inline void gen_op_fmov_FT0_STN(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fmov_FT0_STN;
}

static inline void gen_op_fmov_ST0_STN(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fmov_ST0_STN;
}

static inline void gen_op_fmov_STN_ST0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fmov_STN_ST0;
}

static inline void gen_op_fxchg_ST0_STN(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fxchg_ST0_STN;
}

static inline void gen_op_fcom_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fcom_ST0_FT0;
}

static inline void gen_op_fucom_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fucom_ST0_FT0;
}

static inline void gen_op_fadd_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fadd_ST0_FT0;
}

static inline void gen_op_fmul_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fmul_ST0_FT0;
}

static inline void gen_op_fsub_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fsub_ST0_FT0;
}

static inline void gen_op_fsubr_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fsubr_ST0_FT0;
}

static inline void gen_op_fdiv_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fdiv_ST0_FT0;
}

static inline void gen_op_fdivr_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fdivr_ST0_FT0;
}

static inline void gen_op_fadd_STN_ST0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fadd_STN_ST0;
}

static inline void gen_op_fmul_STN_ST0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fmul_STN_ST0;
}

static inline void gen_op_fsub_STN_ST0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fsub_STN_ST0;
}

static inline void gen_op_fsubr_STN_ST0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fsubr_STN_ST0;
}

static inline void gen_op_fdiv_STN_ST0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fdiv_STN_ST0;
}

static inline void gen_op_fdivr_STN_ST0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fdivr_STN_ST0;
}

static inline void gen_op_fchs_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fchs_ST0;
}

static inline void gen_op_fabs_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fabs_ST0;
}

static inline void gen_op_fxam_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fxam_ST0;
}

static inline void gen_op_fld1_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fld1_ST0;
}

static inline void gen_op_fldl2t_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldl2t_ST0;
}

static inline void gen_op_fldl2e_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldl2e_ST0;
}

static inline void gen_op_fldpi_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldpi_ST0;
}

static inline void gen_op_fldlg2_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldlg2_ST0;
}

static inline void gen_op_fldln2_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldln2_ST0;
}

static inline void gen_op_fldz_ST0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldz_ST0;
}

static inline void gen_op_fldz_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldz_FT0;
}

static inline void gen_op_f2xm1(void)
{
    *gen_opc_ptr++ = INDEX_op_f2xm1;
}

static inline void gen_op_fyl2x(void)
{
    *gen_opc_ptr++ = INDEX_op_fyl2x;
}

static inline void gen_op_fptan(void)
{
    *gen_opc_ptr++ = INDEX_op_fptan;
}

static inline void gen_op_fpatan(void)
{
    *gen_opc_ptr++ = INDEX_op_fpatan;
}

static inline void gen_op_fxtract(void)
{
    *gen_opc_ptr++ = INDEX_op_fxtract;
}

static inline void gen_op_fprem1(void)
{
    *gen_opc_ptr++ = INDEX_op_fprem1;
}

static inline void gen_op_fprem(void)
{
    *gen_opc_ptr++ = INDEX_op_fprem;
}

static inline void gen_op_fyl2xp1(void)
{
    *gen_opc_ptr++ = INDEX_op_fyl2xp1;
}

static inline void gen_op_fsqrt(void)
{
    *gen_opc_ptr++ = INDEX_op_fsqrt;
}

static inline void gen_op_fsincos(void)
{
    *gen_opc_ptr++ = INDEX_op_fsincos;
}

static inline void gen_op_frndint(void)
{
    *gen_opc_ptr++ = INDEX_op_frndint;
}

static inline void gen_op_fscale(void)
{
    *gen_opc_ptr++ = INDEX_op_fscale;
}

static inline void gen_op_fsin(void)
{
    *gen_opc_ptr++ = INDEX_op_fsin;
}

static inline void gen_op_fcos(void)
{
    *gen_opc_ptr++ = INDEX_op_fcos;
}

static inline void gen_op_fnstsw_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fnstsw_A0;
}

static inline void gen_op_fnstsw_EAX(void)
{
    *gen_opc_ptr++ = INDEX_op_fnstsw_EAX;
}

static inline void gen_op_fnstcw_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fnstcw_A0;
}

static inline void gen_op_fldcw_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_fldcw_A0;
}

static inline void gen_op_fclex(void)
{
    *gen_opc_ptr++ = INDEX_op_fclex;
}

static inline void gen_op_fninit(void)
{
    *gen_opc_ptr++ = INDEX_op_fninit;
}

static inline void gen_op_lock(void)
{
    *gen_opc_ptr++ = INDEX_op_lock;
}

static inline void gen_op_unlock(void)
{
    *gen_opc_ptr++ = INDEX_op_unlock;
}


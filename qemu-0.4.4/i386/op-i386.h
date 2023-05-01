int dyngen_code(uint8_t *gen_code_buf,
                uint16_t *label_offsets, uint16_t *jmp_offsets,
                const uint16_t *opc_buf, const uint32_t *opparam_buf)
{
    uint8_t *gen_code_ptr;
    const uint16_t *opc_ptr;
    const uint32_t *opparam_ptr;

    gen_code_ptr = gen_code_buf;
    opc_ptr = opc_buf;
    opparam_ptr = opparam_buf;
    for(;;) {
        switch(*opc_ptr++) {
case INDEX_op_movl_A0_EAX: {
    extern void op_movl_A0_EAX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_EAX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EAX: {
    extern void op_addl_A0_EAX();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EAX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EAX_s1: {
    extern void op_addl_A0_EAX_s1();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EAX_s1+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EAX_s2: {
    extern void op_addl_A0_EAX_s2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EAX_s2+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EAX_s3: {
    extern void op_addl_A0_EAX_s3();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EAX_s3+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T0_EAX: {
    extern void op_movl_T0_EAX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_EAX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_T1_EAX: {
    extern void op_movl_T1_EAX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_EAX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_T0_EAX: {
    extern void op_movh_T0_EAX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T0_EAX+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movh_T1_EAX: {
    extern void op_movh_T1_EAX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T1_EAX+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movl_EAX_T0: {
    extern void op_movl_EAX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EAX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EAX_T1: {
    extern void op_movl_EAX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EAX_T1+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EAX_A0: {
    extern void op_movl_EAX_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EAX_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_cmovw_EAX_T1_T0: {
    extern void op_cmovw_EAX_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovw_EAX_T1_T0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_cmovl_EAX_T1_T0: {
    extern void op_cmovl_EAX_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovl_EAX_T1_T0+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_movw_EAX_T0: {
    extern void op_movw_EAX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EAX_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EAX_T1: {
    extern void op_movw_EAX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EAX_T1+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EAX_A0: {
    extern void op_movw_EAX_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EAX_A0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movb_EAX_T0: {
    extern void op_movb_EAX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EAX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_EAX_T0: {
    extern void op_movh_EAX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EAX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movb_EAX_T1: {
    extern void op_movb_EAX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EAX_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movh_EAX_T1: {
    extern void op_movh_EAX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EAX_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movl_A0_ECX: {
    extern void op_movl_A0_ECX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_ECX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_ECX: {
    extern void op_addl_A0_ECX();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ECX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_ECX_s1: {
    extern void op_addl_A0_ECX_s1();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ECX_s1+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_ECX_s2: {
    extern void op_addl_A0_ECX_s2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ECX_s2+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_ECX_s3: {
    extern void op_addl_A0_ECX_s3();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ECX_s3+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T0_ECX: {
    extern void op_movl_T0_ECX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_ECX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_T1_ECX: {
    extern void op_movl_T1_ECX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_ECX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_T0_ECX: {
    extern void op_movh_T0_ECX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T0_ECX+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movh_T1_ECX: {
    extern void op_movh_T1_ECX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T1_ECX+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movl_ECX_T0: {
    extern void op_movl_ECX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_ECX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_ECX_T1: {
    extern void op_movl_ECX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_ECX_T1+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_ECX_A0: {
    extern void op_movl_ECX_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_ECX_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_cmovw_ECX_T1_T0: {
    extern void op_cmovw_ECX_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovw_ECX_T1_T0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_cmovl_ECX_T1_T0: {
    extern void op_cmovl_ECX_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovl_ECX_T1_T0+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_movw_ECX_T0: {
    extern void op_movw_ECX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_ECX_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_ECX_T1: {
    extern void op_movw_ECX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_ECX_T1+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_ECX_A0: {
    extern void op_movw_ECX_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_ECX_A0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movb_ECX_T0: {
    extern void op_movb_ECX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_ECX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_ECX_T0: {
    extern void op_movh_ECX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_ECX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movb_ECX_T1: {
    extern void op_movb_ECX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_ECX_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movh_ECX_T1: {
    extern void op_movh_ECX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_ECX_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movl_A0_EDX: {
    extern void op_movl_A0_EDX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_EDX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EDX: {
    extern void op_addl_A0_EDX();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EDX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EDX_s1: {
    extern void op_addl_A0_EDX_s1();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EDX_s1+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EDX_s2: {
    extern void op_addl_A0_EDX_s2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EDX_s2+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EDX_s3: {
    extern void op_addl_A0_EDX_s3();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EDX_s3+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T0_EDX: {
    extern void op_movl_T0_EDX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_EDX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_T1_EDX: {
    extern void op_movl_T1_EDX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_EDX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_T0_EDX: {
    extern void op_movh_T0_EDX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T0_EDX+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movh_T1_EDX: {
    extern void op_movh_T1_EDX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T1_EDX+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movl_EDX_T0: {
    extern void op_movl_EDX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EDX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EDX_T1: {
    extern void op_movl_EDX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EDX_T1+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EDX_A0: {
    extern void op_movl_EDX_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EDX_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_cmovw_EDX_T1_T0: {
    extern void op_cmovw_EDX_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovw_EDX_T1_T0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_cmovl_EDX_T1_T0: {
    extern void op_cmovl_EDX_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovl_EDX_T1_T0+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_movw_EDX_T0: {
    extern void op_movw_EDX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EDX_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EDX_T1: {
    extern void op_movw_EDX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EDX_T1+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EDX_A0: {
    extern void op_movw_EDX_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EDX_A0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movb_EDX_T0: {
    extern void op_movb_EDX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EDX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_EDX_T0: {
    extern void op_movh_EDX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EDX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movb_EDX_T1: {
    extern void op_movb_EDX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EDX_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movh_EDX_T1: {
    extern void op_movh_EDX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EDX_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movl_A0_EBX: {
    extern void op_movl_A0_EBX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_EBX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EBX: {
    extern void op_addl_A0_EBX();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EBX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EBX_s1: {
    extern void op_addl_A0_EBX_s1();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EBX_s1+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EBX_s2: {
    extern void op_addl_A0_EBX_s2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EBX_s2+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EBX_s3: {
    extern void op_addl_A0_EBX_s3();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EBX_s3+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T0_EBX: {
    extern void op_movl_T0_EBX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_EBX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_T1_EBX: {
    extern void op_movl_T1_EBX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_EBX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_T0_EBX: {
    extern void op_movh_T0_EBX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T0_EBX+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movh_T1_EBX: {
    extern void op_movh_T1_EBX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T1_EBX+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movl_EBX_T0: {
    extern void op_movl_EBX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EBX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EBX_T1: {
    extern void op_movl_EBX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EBX_T1+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EBX_A0: {
    extern void op_movl_EBX_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EBX_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_cmovw_EBX_T1_T0: {
    extern void op_cmovw_EBX_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovw_EBX_T1_T0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_cmovl_EBX_T1_T0: {
    extern void op_cmovl_EBX_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovl_EBX_T1_T0+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_movw_EBX_T0: {
    extern void op_movw_EBX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EBX_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EBX_T1: {
    extern void op_movw_EBX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EBX_T1+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EBX_A0: {
    extern void op_movw_EBX_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EBX_A0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movb_EBX_T0: {
    extern void op_movb_EBX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EBX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_EBX_T0: {
    extern void op_movh_EBX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EBX_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movb_EBX_T1: {
    extern void op_movb_EBX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EBX_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movh_EBX_T1: {
    extern void op_movh_EBX_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EBX_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movl_A0_ESP: {
    extern void op_movl_A0_ESP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_ESP+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_ESP: {
    extern void op_addl_A0_ESP();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ESP+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_ESP_s1: {
    extern void op_addl_A0_ESP_s1();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ESP_s1+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_ESP_s2: {
    extern void op_addl_A0_ESP_s2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ESP_s2+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_ESP_s3: {
    extern void op_addl_A0_ESP_s3();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ESP_s3+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T0_ESP: {
    extern void op_movl_T0_ESP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_ESP+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_T1_ESP: {
    extern void op_movl_T1_ESP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_ESP+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_T0_ESP: {
    extern void op_movh_T0_ESP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T0_ESP+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movh_T1_ESP: {
    extern void op_movh_T1_ESP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T1_ESP+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movl_ESP_T0: {
    extern void op_movl_ESP_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_ESP_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_ESP_T1: {
    extern void op_movl_ESP_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_ESP_T1+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_ESP_A0: {
    extern void op_movl_ESP_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_ESP_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_cmovw_ESP_T1_T0: {
    extern void op_cmovw_ESP_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovw_ESP_T1_T0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_cmovl_ESP_T1_T0: {
    extern void op_cmovl_ESP_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovl_ESP_T1_T0+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_movw_ESP_T0: {
    extern void op_movw_ESP_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_ESP_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_ESP_T1: {
    extern void op_movw_ESP_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_ESP_T1+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_ESP_A0: {
    extern void op_movw_ESP_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_ESP_A0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movb_ESP_T0: {
    extern void op_movb_ESP_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_ESP_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_ESP_T0: {
    extern void op_movh_ESP_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_ESP_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movb_ESP_T1: {
    extern void op_movb_ESP_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_ESP_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movh_ESP_T1: {
    extern void op_movh_ESP_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_ESP_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movl_A0_EBP: {
    extern void op_movl_A0_EBP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_EBP+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EBP: {
    extern void op_addl_A0_EBP();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EBP+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EBP_s1: {
    extern void op_addl_A0_EBP_s1();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EBP_s1+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EBP_s2: {
    extern void op_addl_A0_EBP_s2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EBP_s2+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EBP_s3: {
    extern void op_addl_A0_EBP_s3();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EBP_s3+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T0_EBP: {
    extern void op_movl_T0_EBP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_EBP+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_T1_EBP: {
    extern void op_movl_T1_EBP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_EBP+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_T0_EBP: {
    extern void op_movh_T0_EBP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T0_EBP+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movh_T1_EBP: {
    extern void op_movh_T1_EBP();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T1_EBP+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movl_EBP_T0: {
    extern void op_movl_EBP_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EBP_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EBP_T1: {
    extern void op_movl_EBP_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EBP_T1+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EBP_A0: {
    extern void op_movl_EBP_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EBP_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_cmovw_EBP_T1_T0: {
    extern void op_cmovw_EBP_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovw_EBP_T1_T0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_cmovl_EBP_T1_T0: {
    extern void op_cmovl_EBP_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovl_EBP_T1_T0+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_movw_EBP_T0: {
    extern void op_movw_EBP_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EBP_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EBP_T1: {
    extern void op_movw_EBP_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EBP_T1+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EBP_A0: {
    extern void op_movw_EBP_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EBP_A0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movb_EBP_T0: {
    extern void op_movb_EBP_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EBP_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_EBP_T0: {
    extern void op_movh_EBP_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EBP_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movb_EBP_T1: {
    extern void op_movb_EBP_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EBP_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movh_EBP_T1: {
    extern void op_movh_EBP_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EBP_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movl_A0_ESI: {
    extern void op_movl_A0_ESI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_ESI+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_ESI: {
    extern void op_addl_A0_ESI();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ESI+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_ESI_s1: {
    extern void op_addl_A0_ESI_s1();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ESI_s1+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_ESI_s2: {
    extern void op_addl_A0_ESI_s2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ESI_s2+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_ESI_s3: {
    extern void op_addl_A0_ESI_s3();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_ESI_s3+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T0_ESI: {
    extern void op_movl_T0_ESI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_ESI+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_T1_ESI: {
    extern void op_movl_T1_ESI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_ESI+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_T0_ESI: {
    extern void op_movh_T0_ESI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T0_ESI+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movh_T1_ESI: {
    extern void op_movh_T1_ESI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T1_ESI+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movl_ESI_T0: {
    extern void op_movl_ESI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_ESI_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_ESI_T1: {
    extern void op_movl_ESI_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_ESI_T1+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_ESI_A0: {
    extern void op_movl_ESI_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_ESI_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_cmovw_ESI_T1_T0: {
    extern void op_cmovw_ESI_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovw_ESI_T1_T0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_cmovl_ESI_T1_T0: {
    extern void op_cmovl_ESI_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovl_ESI_T1_T0+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_movw_ESI_T0: {
    extern void op_movw_ESI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_ESI_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_ESI_T1: {
    extern void op_movw_ESI_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_ESI_T1+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_ESI_A0: {
    extern void op_movw_ESI_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_ESI_A0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movb_ESI_T0: {
    extern void op_movb_ESI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_ESI_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_ESI_T0: {
    extern void op_movh_ESI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_ESI_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movb_ESI_T1: {
    extern void op_movb_ESI_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_ESI_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movh_ESI_T1: {
    extern void op_movh_ESI_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_ESI_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movl_A0_EDI: {
    extern void op_movl_A0_EDI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_EDI+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EDI: {
    extern void op_addl_A0_EDI();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EDI+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addl_A0_EDI_s1: {
    extern void op_addl_A0_EDI_s1();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EDI_s1+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EDI_s2: {
    extern void op_addl_A0_EDI_s2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EDI_s2+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_EDI_s3: {
    extern void op_addl_A0_EDI_s3();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_EDI_s3+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T0_EDI: {
    extern void op_movl_T0_EDI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_EDI+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_T1_EDI: {
    extern void op_movl_T1_EDI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_EDI+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_T0_EDI: {
    extern void op_movh_T0_EDI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T0_EDI+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movh_T1_EDI: {
    extern void op_movh_T1_EDI();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_T1_EDI+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movl_EDI_T0: {
    extern void op_movl_EDI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EDI_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EDI_T1: {
    extern void op_movl_EDI_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EDI_T1+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_EDI_A0: {
    extern void op_movl_EDI_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_EDI_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_cmovw_EDI_T1_T0: {
    extern void op_cmovw_EDI_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovw_EDI_T1_T0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_cmovl_EDI_T1_T0: {
    extern void op_cmovl_EDI_T1_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmovl_EDI_T1_T0+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_movw_EDI_T0: {
    extern void op_movw_EDI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EDI_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EDI_T1: {
    extern void op_movw_EDI_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EDI_T1+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movw_EDI_A0: {
    extern void op_movw_EDI_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_EDI_A0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_movb_EDI_T0: {
    extern void op_movb_EDI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EDI_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movh_EDI_T0: {
    extern void op_movh_EDI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EDI_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movb_EDI_T1: {
    extern void op_movb_EDI_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_EDI_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_movh_EDI_T1: {
    extern void op_movh_EDI_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movh_EDI_T1+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_update2_cc: {
    extern void op_update2_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_update2_cc+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_update1_cc: {
    extern void op_update1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_update1_cc+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_update_neg_cc: {
    extern void op_update_neg_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_update_neg_cc+0), 10);
    gen_code_ptr += 10;
}
break;

case INDEX_op_cmpl_T0_T1_cc: {
    extern void op_cmpl_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmpl_T0_T1_cc+0), 10);
    gen_code_ptr += 10;
}
break;

case INDEX_op_update_inc_cc: {
    extern void op_update_inc_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_update_inc_cc+0), 16);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 16;
}
break;

case INDEX_op_testl_T0_T1_cc: {
    extern void op_testl_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_testl_T0_T1_cc+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_addl_T0_T1: {
    extern void op_addl_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_T0_T1+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_orl_T0_T1: {
    extern void op_orl_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_orl_T0_T1+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_andl_T0_T1: {
    extern void op_andl_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_andl_T0_T1+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_subl_T0_T1: {
    extern void op_subl_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_subl_T0_T1+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_xorl_T0_T1: {
    extern void op_xorl_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_xorl_T0_T1+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_negl_T0: {
    extern void op_negl_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_negl_T0+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_incl_T0: {
    extern void op_incl_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_incl_T0+0), 1);
    gen_code_ptr += 1;
}
break;

case INDEX_op_decl_T0: {
    extern void op_decl_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_decl_T0+0), 1);
    gen_code_ptr += 1;
}
break;

case INDEX_op_notl_T0: {
    extern void op_notl_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_notl_T0+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_bswapl_T0: {
    extern void op_bswapl_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_bswapl_T0+0), 38);
    gen_code_ptr += 38;
}
break;

case INDEX_op_mulb_AL_T0: {
    extern void op_mulb_AL_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_mulb_AL_T0+0), 22);
    gen_code_ptr += 22;
}
break;

case INDEX_op_imulb_AL_T0: {
    extern void op_imulb_AL_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_imulb_AL_T0+0), 28);
    gen_code_ptr += 28;
}
break;

case INDEX_op_mulw_AX_T0: {
    extern void op_mulw_AX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_mulw_AX_T0+0), 24);
    gen_code_ptr += 24;
}
break;

case INDEX_op_imulw_AX_T0: {
    extern void op_imulw_AX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_imulw_AX_T0+0), 37);
    gen_code_ptr += 37;
}
break;

case INDEX_op_mull_EAX_T0: {
    extern void op_mull_EAX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_mull_EAX_T0+0), 27);
    gen_code_ptr += 27;
}
break;

case INDEX_op_imull_EAX_T0: {
    extern void op_imull_EAX_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_imull_EAX_T0+0), 67);
    gen_code_ptr += 67;
}
break;

case INDEX_op_imulw_T0_T1: {
    extern void op_imulw_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_imulw_T0_T1+0), 25);
    gen_code_ptr += 25;
}
break;

case INDEX_op_imull_T0_T1: {
    extern void op_imull_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_imull_T0_T1+0), 62);
    gen_code_ptr += 62;
}
break;

case INDEX_op_divb_AL_T0: {
    long param1;
    extern void op_divb_AL_T0();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_divb_AL_T0+0), 76);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 30) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 35) = (long)(&raise_exception) - (long)(gen_code_ptr + 35) + -4;
    gen_code_ptr += 76;
}
break;

case INDEX_op_idivb_AL_T0: {
    long param1;
    extern void op_idivb_AL_T0();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_idivb_AL_T0+0), 79);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 26) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 31) = (long)(&raise_exception) - (long)(gen_code_ptr + 31) + -4;
    gen_code_ptr += 79;
}
break;

case INDEX_op_divw_AX_T0: {
    long param1;
    extern void op_divw_AX_T0();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_divw_AX_T0+0), 110);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 46) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 51) = (long)(&raise_exception) - (long)(gen_code_ptr + 51) + -4;
    gen_code_ptr += 110;
}
break;

case INDEX_op_idivw_AX_T0: {
    long param1;
    extern void op_idivw_AX_T0();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_idivw_AX_T0+0), 118);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 43) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 48) = (long)(&raise_exception) - (long)(gen_code_ptr + 48) + -4;
    gen_code_ptr += 118;
}
break;

case INDEX_op_divl_EAX_T0: {
    long param1;
    extern void op_divl_EAX_T0();
extern char helper_divl_EAX_T0;
    memcpy(gen_code_ptr, (void *)((char *)&op_divl_EAX_T0+0), 11);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&helper_divl_EAX_T0) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 11;
}
break;

case INDEX_op_idivl_EAX_T0: {
    long param1;
    extern void op_idivl_EAX_T0();
extern char helper_idivl_EAX_T0;
    memcpy(gen_code_ptr, (void *)((char *)&op_idivl_EAX_T0+0), 11);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&helper_idivl_EAX_T0) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 11;
}
break;

case INDEX_op_movl_T0_im: {
    long param1;
    extern void op_movl_T0_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_im+0), 5);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    gen_code_ptr += 5;
}
break;

case INDEX_op_addl_T0_im: {
    long param1;
    extern void op_addl_T0_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_T0_im+0), 6);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
    gen_code_ptr += 6;
}
break;

case INDEX_op_andl_T0_ffff: {
    extern void op_andl_T0_ffff();
    memcpy(gen_code_ptr, (void *)((char *)&op_andl_T0_ffff+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_andl_T0_im: {
    long param1;
    extern void op_andl_T0_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_andl_T0_im+0), 6);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T0_T1: {
    extern void op_movl_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_T1+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_movl_T1_im: {
    long param1;
    extern void op_movl_T1_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_im+0), 5);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    gen_code_ptr += 5;
}
break;

case INDEX_op_addl_T1_im: {
    long param1;
    extern void op_addl_T1_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_T1_im+0), 6);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_T1_A0: {
    extern void op_movl_T1_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T1_A0+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_movl_A0_im: {
    long param1;
    extern void op_movl_A0_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_im+0), 5);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    gen_code_ptr += 5;
}
break;

case INDEX_op_addl_A0_im: {
    long param1;
    extern void op_addl_A0_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_im+0), 6);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_AL: {
    extern void op_addl_A0_AL();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_AL+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_andl_A0_ffff: {
    extern void op_andl_A0_ffff();
    memcpy(gen_code_ptr, (void *)((char *)&op_andl_A0_ffff+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_ldub_T0_A0: {
    extern void op_ldub_T0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_ldub_T0_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_ldsb_T0_A0: {
    extern void op_ldsb_T0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsb_T0_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_lduw_T0_A0: {
    extern void op_lduw_T0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_lduw_T0_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_ldsw_T0_A0: {
    extern void op_ldsw_T0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsw_T0_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_ldl_T0_A0: {
    extern void op_ldl_T0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_ldl_T0_A0+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_ldub_T1_A0: {
    extern void op_ldub_T1_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_ldub_T1_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_ldsb_T1_A0: {
    extern void op_ldsb_T1_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsb_T1_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_lduw_T1_A0: {
    extern void op_lduw_T1_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_lduw_T1_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_ldsw_T1_A0: {
    extern void op_ldsw_T1_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsw_T1_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_ldl_T1_A0: {
    extern void op_ldl_T1_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_ldl_T1_A0+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_stb_T0_A0: {
    extern void op_stb_T0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_stb_T0_A0+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_stw_T0_A0: {
    extern void op_stw_T0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_stw_T0_A0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_stl_T0_A0: {
    extern void op_stl_T0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_stl_T0_A0+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_ldub_user_T0_A0: {
    extern void op_ldub_user_T0_A0();
extern char __ldb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldub_user_T0_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldb_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_ldsb_user_T0_A0: {
    extern void op_ldsb_user_T0_A0();
extern char __ldb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsb_user_T0_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldb_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_lduw_user_T0_A0: {
    extern void op_lduw_user_T0_A0();
extern char __ldw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_lduw_user_T0_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldw_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_ldsw_user_T0_A0: {
    extern void op_ldsw_user_T0_A0();
extern char __ldw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsw_user_T0_A0+0), 48);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldw_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 48;
}
break;

case INDEX_op_ldl_user_T0_A0: {
    extern void op_ldl_user_T0_A0();
extern char __ldl_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldl_user_T0_A0+0), 47);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldl_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 47;
}
break;

case INDEX_op_ldub_user_T1_A0: {
    extern void op_ldub_user_T1_A0();
extern char __ldb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldub_user_T1_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldb_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_ldsb_user_T1_A0: {
    extern void op_ldsb_user_T1_A0();
extern char __ldb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsb_user_T1_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldb_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_lduw_user_T1_A0: {
    extern void op_lduw_user_T1_A0();
extern char __ldw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_lduw_user_T1_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldw_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_ldsw_user_T1_A0: {
    extern void op_ldsw_user_T1_A0();
extern char __ldw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsw_user_T1_A0+0), 48);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldw_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 48;
}
break;

case INDEX_op_ldl_user_T1_A0: {
    extern void op_ldl_user_T1_A0();
extern char __ldl_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldl_user_T1_A0+0), 47);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldl_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 47;
}
break;

case INDEX_op_stb_user_T0_A0: {
    extern void op_stb_user_T0_A0();
extern char __stb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_stb_user_T0_A0+0), 57);
    *(uint32_t *)(gen_code_ptr + 37) = (long)(&__stb_mmu) - (long)(gen_code_ptr + 37) + -4;
    gen_code_ptr += 57;
}
break;

case INDEX_op_stw_user_T0_A0: {
    extern void op_stw_user_T0_A0();
extern char __stw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_stw_user_T0_A0+0), 58);
    *(uint32_t *)(gen_code_ptr + 37) = (long)(&__stw_mmu) - (long)(gen_code_ptr + 37) + -4;
    gen_code_ptr += 58;
}
break;

case INDEX_op_stl_user_T0_A0: {
    extern void op_stl_user_T0_A0();
extern char __stl_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_stl_user_T0_A0+0), 57);
    *(uint32_t *)(gen_code_ptr + 35) = (long)(&__stl_mmu) - (long)(gen_code_ptr + 35) + -4;
    gen_code_ptr += 57;
}
break;

case INDEX_op_ldub_kernel_T0_A0: {
    extern void op_ldub_kernel_T0_A0();
extern char __ldb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldub_kernel_T0_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldb_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_ldsb_kernel_T0_A0: {
    extern void op_ldsb_kernel_T0_A0();
extern char __ldb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsb_kernel_T0_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldb_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_lduw_kernel_T0_A0: {
    extern void op_lduw_kernel_T0_A0();
extern char __ldw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_lduw_kernel_T0_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldw_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_ldsw_kernel_T0_A0: {
    extern void op_ldsw_kernel_T0_A0();
extern char __ldw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsw_kernel_T0_A0+0), 48);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldw_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 48;
}
break;

case INDEX_op_ldl_kernel_T0_A0: {
    extern void op_ldl_kernel_T0_A0();
extern char __ldl_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldl_kernel_T0_A0+0), 47);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldl_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 47;
}
break;

case INDEX_op_ldub_kernel_T1_A0: {
    extern void op_ldub_kernel_T1_A0();
extern char __ldb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldub_kernel_T1_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldb_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_ldsb_kernel_T1_A0: {
    extern void op_ldsb_kernel_T1_A0();
extern char __ldb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsb_kernel_T1_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldb_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_lduw_kernel_T1_A0: {
    extern void op_lduw_kernel_T1_A0();
extern char __ldw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_lduw_kernel_T1_A0+0), 52);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldw_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 52;
}
break;

case INDEX_op_ldsw_kernel_T1_A0: {
    extern void op_ldsw_kernel_T1_A0();
extern char __ldw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldsw_kernel_T1_A0+0), 48);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldw_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 48;
}
break;

case INDEX_op_ldl_kernel_T1_A0: {
    extern void op_ldl_kernel_T1_A0();
extern char __ldl_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_ldl_kernel_T1_A0+0), 47);
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&__ldl_mmu) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 47;
}
break;

case INDEX_op_stb_kernel_T0_A0: {
    extern void op_stb_kernel_T0_A0();
extern char __stb_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_stb_kernel_T0_A0+0), 57);
    *(uint32_t *)(gen_code_ptr + 37) = (long)(&__stb_mmu) - (long)(gen_code_ptr + 37) + -4;
    gen_code_ptr += 57;
}
break;

case INDEX_op_stw_kernel_T0_A0: {
    extern void op_stw_kernel_T0_A0();
extern char __stw_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_stw_kernel_T0_A0+0), 58);
    *(uint32_t *)(gen_code_ptr + 37) = (long)(&__stw_mmu) - (long)(gen_code_ptr + 37) + -4;
    gen_code_ptr += 58;
}
break;

case INDEX_op_stl_kernel_T0_A0: {
    extern void op_stl_kernel_T0_A0();
extern char __stl_mmu;
    memcpy(gen_code_ptr, (void *)((char *)&op_stl_kernel_T0_A0+0), 57);
    *(uint32_t *)(gen_code_ptr + 35) = (long)(&__stl_mmu) - (long)(gen_code_ptr + 35) + -4;
    gen_code_ptr += 57;
}
break;

case INDEX_op_add_bitw_A0_T1: {
    extern void op_add_bitw_A0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_add_bitw_A0_T1+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_add_bitl_A0_T1: {
    extern void op_add_bitl_A0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_add_bitl_A0_T1+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_jmp_T0: {
    extern void op_jmp_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_jmp_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_jmp_im: {
    long param1;
    extern void op_jmp_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_jmp_im+0), 7);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 3) = param1 + 0;
    gen_code_ptr += 7;
}
break;

case INDEX_op_hlt: {
    extern void op_hlt();
extern char cpu_loop_exit;
    memcpy(gen_code_ptr, (void *)((char *)&op_hlt+0), 15);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&cpu_loop_exit) - (long)(gen_code_ptr + 11) + -4;
    gen_code_ptr += 15;
}
break;

case INDEX_op_debug: {
    extern void op_debug();
extern char cpu_loop_exit;
    memcpy(gen_code_ptr, (void *)((char *)&op_debug+0), 15);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&cpu_loop_exit) - (long)(gen_code_ptr + 11) + -4;
    gen_code_ptr += 15;
}
break;

case INDEX_op_raise_interrupt: {
    long param1, param2;
    extern void op_raise_interrupt();
extern char raise_interrupt;
    memcpy(gen_code_ptr, (void *)((char *)&op_raise_interrupt+0), 22);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 15) = (long)(&raise_interrupt) - (long)(gen_code_ptr + 15) + -4;
    gen_code_ptr += 22;
}
break;

case INDEX_op_raise_exception: {
    long param1;
    extern void op_raise_exception();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_raise_exception+0), 11);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&raise_exception) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 11;
}
break;

case INDEX_op_into: {
    long param1;
    extern void op_into();
extern char cc_table;
extern char raise_interrupt;
    memcpy(gen_code_ptr, (void *)((char *)&op_into+0), 36);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    *(uint32_t *)(gen_code_ptr + 18) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&raise_interrupt) - (long)(gen_code_ptr + 29) + -4;
    gen_code_ptr += 36;
}
break;

case INDEX_op_cli: {
    extern void op_cli();
    memcpy(gen_code_ptr, (void *)((char *)&op_cli+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_sti: {
    extern void op_sti();
    memcpy(gen_code_ptr, (void *)((char *)&op_sti+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_set_inhibit_irq: {
    extern void op_set_inhibit_irq();
    memcpy(gen_code_ptr, (void *)((char *)&op_set_inhibit_irq+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_reset_inhibit_irq: {
    extern void op_reset_inhibit_irq();
    memcpy(gen_code_ptr, (void *)((char *)&op_reset_inhibit_irq+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_boundw: {
    long param1;
    extern void op_boundw();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_boundw+0), 33);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 23) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = (long)(&raise_exception) - (long)(gen_code_ptr + 28) + -4;
    gen_code_ptr += 33;
}
break;

case INDEX_op_boundl: {
    long param1;
    extern void op_boundl();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_boundl+0), 26);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 16) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 21) = (long)(&raise_exception) - (long)(gen_code_ptr + 21) + -4;
    gen_code_ptr += 26;
}
break;

case INDEX_op_cmpxchg8b: {
    extern void op_cmpxchg8b();
extern char helper_cmpxchg8b;
    memcpy(gen_code_ptr, (void *)((char *)&op_cmpxchg8b+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_cmpxchg8b) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_jmp: {
    long param1, param2;
    extern void op_jmp();
    memcpy(gen_code_ptr, (void *)((char *)&op_jmp+0), 21);
    label_offsets[0] = 8 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 16) = param2 + 0;
    gen_code_ptr += 21;
}
break;

case INDEX_op_movl_T0_0: {
    extern void op_movl_T0_0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_0+0), 2);
    gen_code_ptr += 2;
}
break;

case INDEX_op_exit_tb: {
    extern void op_exit_tb();
    memcpy(gen_code_ptr, (void *)((char *)&op_exit_tb+0), 1);
    gen_code_ptr += 1;
}
break;

case INDEX_op_jb_subb: {
    long param1, param2, param3;
    extern void op_jb_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_jb_subb+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_jz_subb: {
    long param1, param2, param3;
    extern void op_jz_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_jz_subb+0), 49);
    label_offsets[0] = 12 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 36 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 8) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 20) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 30) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 37) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 44) = param3 + 0;
    gen_code_ptr += 49;
}
break;

case INDEX_op_jbe_subb: {
    long param1, param2, param3;
    extern void op_jbe_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_jbe_subb+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_js_subb: {
    long param1, param2, param3;
    extern void op_js_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_js_subb+0), 49);
    label_offsets[0] = 12 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 36 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 8) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 20) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 30) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 37) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 44) = param3 + 0;
    gen_code_ptr += 49;
}
break;

case INDEX_op_jl_subb: {
    long param1, param2, param3;
    extern void op_jl_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_jl_subb+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_jle_subb: {
    long param1, param2, param3;
    extern void op_jle_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_jle_subb+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_setb_T0_subb: {
    extern void op_setb_T0_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_setb_T0_subb+0), 14);
    gen_code_ptr += 14;
}
break;

case INDEX_op_setz_T0_subb: {
    extern void op_setz_T0_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_setz_T0_subb+0), 9);
    gen_code_ptr += 9;
}
break;

case INDEX_op_setbe_T0_subb: {
    extern void op_setbe_T0_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_setbe_T0_subb+0), 14);
    gen_code_ptr += 14;
}
break;

case INDEX_op_sets_T0_subb: {
    extern void op_sets_T0_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_sets_T0_subb+0), 11);
    gen_code_ptr += 11;
}
break;

case INDEX_op_setl_T0_subb: {
    extern void op_setl_T0_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_setl_T0_subb+0), 14);
    gen_code_ptr += 14;
}
break;

case INDEX_op_setle_T0_subb: {
    extern void op_setle_T0_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_setle_T0_subb+0), 14);
    gen_code_ptr += 14;
}
break;

case INDEX_op_shlb_T0_T1: {
    extern void op_shlb_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_shlb_T0_T1+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_shrb_T0_T1: {
    extern void op_shrb_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrb_T0_T1+0), 13);
    gen_code_ptr += 13;
}
break;

case INDEX_op_sarb_T0_T1: {
    extern void op_sarb_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_sarb_T0_T1+0), 12);
    gen_code_ptr += 12;
}
break;

case INDEX_op_rolb_T0_T1_cc: {
    extern void op_rolb_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rolb_T0_T1_cc+0), 103);
    *(uint32_t *)(gen_code_ptr + 51) = (long)(&cc_table) + 0;
    gen_code_ptr += 103;
}
break;

case INDEX_op_rorb_T0_T1_cc: {
    extern void op_rorb_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rorb_T0_T1_cc+0), 104);
    *(uint32_t *)(gen_code_ptr + 51) = (long)(&cc_table) + 0;
    gen_code_ptr += 104;
}
break;

case INDEX_op_rolb_T0_T1: {
    extern void op_rolb_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rolb_T0_T1+0), 40);
    gen_code_ptr += 40;
}
break;

case INDEX_op_rorb_T0_T1: {
    extern void op_rorb_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rorb_T0_T1+0), 40);
    gen_code_ptr += 40;
}
break;

case INDEX_op_rclb_T0_T1_cc: {
    extern void op_rclb_T0_T1_cc();
extern char rclb_table;
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rclb_T0_T1_cc+0), 153);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclb_table) + 0;
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&cc_table) + 0;
    gen_code_ptr += 153;
}
break;

case INDEX_op_rcrb_T0_T1_cc: {
    extern void op_rcrb_T0_T1_cc();
extern char rclb_table;
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rcrb_T0_T1_cc+0), 153);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclb_table) + 0;
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&cc_table) + 0;
    gen_code_ptr += 153;
}
break;

case INDEX_op_shlb_T0_T1_cc: {
    extern void op_shlb_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shlb_T0_T1_cc+0), 32);
    gen_code_ptr += 32;
}
break;

case INDEX_op_shrb_T0_T1_cc: {
    extern void op_shrb_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrb_T0_T1_cc+0), 37);
    gen_code_ptr += 37;
}
break;

case INDEX_op_sarb_T0_T1_cc: {
    extern void op_sarb_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_sarb_T0_T1_cc+0), 30);
    gen_code_ptr += 30;
}
break;

case INDEX_op_adcb_T0_T1_cc: {
    extern void op_adcb_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_adcb_T0_T1_cc+0), 29);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 29;
}
break;

case INDEX_op_sbbb_T0_T1_cc: {
    extern void op_sbbb_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_sbbb_T0_T1_cc+0), 31);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_cmpxchgb_T0_T1_EAX_cc: {
    extern void op_cmpxchgb_T0_T1_EAX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmpxchgb_T0_T1_EAX_cc+0), 40);
    gen_code_ptr += 40;
}
break;

case INDEX_op_rolb_mem_T0_T1_cc: {
    extern void op_rolb_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rolb_mem_T0_T1_cc+0), 105);
    *(uint32_t *)(gen_code_ptr + 53) = (long)(&cc_table) + 0;
    gen_code_ptr += 105;
}
break;

case INDEX_op_rorb_mem_T0_T1_cc: {
    extern void op_rorb_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rorb_mem_T0_T1_cc+0), 106);
    *(uint32_t *)(gen_code_ptr + 53) = (long)(&cc_table) + 0;
    gen_code_ptr += 106;
}
break;

case INDEX_op_rolb_mem_T0_T1: {
    extern void op_rolb_mem_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rolb_mem_T0_T1+0), 42);
    gen_code_ptr += 42;
}
break;

case INDEX_op_rorb_mem_T0_T1: {
    extern void op_rorb_mem_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rorb_mem_T0_T1+0), 42);
    gen_code_ptr += 42;
}
break;

case INDEX_op_rclb_mem_T0_T1_cc: {
    extern void op_rclb_mem_T0_T1_cc();
extern char rclb_table;
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rclb_mem_T0_T1_cc+0), 159);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclb_table) + 0;
    *(uint32_t *)(gen_code_ptr + 33) = (long)(&cc_table) + 0;
    gen_code_ptr += 159;
}
break;

case INDEX_op_rcrb_mem_T0_T1_cc: {
    extern void op_rcrb_mem_T0_T1_cc();
extern char rclb_table;
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rcrb_mem_T0_T1_cc+0), 159);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclb_table) + 0;
    *(uint32_t *)(gen_code_ptr + 33) = (long)(&cc_table) + 0;
    gen_code_ptr += 159;
}
break;

case INDEX_op_shlb_mem_T0_T1_cc: {
    extern void op_shlb_mem_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shlb_mem_T0_T1_cc+0), 34);
    gen_code_ptr += 34;
}
break;

case INDEX_op_shrb_mem_T0_T1_cc: {
    extern void op_shrb_mem_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrb_mem_T0_T1_cc+0), 39);
    gen_code_ptr += 39;
}
break;

case INDEX_op_sarb_mem_T0_T1_cc: {
    extern void op_sarb_mem_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_sarb_mem_T0_T1_cc+0), 32);
    gen_code_ptr += 32;
}
break;

case INDEX_op_adcb_mem_T0_T1_cc: {
    extern void op_adcb_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_adcb_mem_T0_T1_cc+0), 31);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_sbbb_mem_T0_T1_cc: {
    extern void op_sbbb_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_sbbb_mem_T0_T1_cc+0), 33);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 33;
}
break;

case INDEX_op_cmpxchgb_mem_T0_T1_EAX_cc: {
    extern void op_cmpxchgb_mem_T0_T1_EAX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmpxchgb_mem_T0_T1_EAX_cc+0), 42);
    gen_code_ptr += 42;
}
break;

case INDEX_op_movl_T0_Dshiftb: {
    extern void op_movl_T0_Dshiftb();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_Dshiftb+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_string_jz_subb: {
    long param1;
    extern void op_string_jz_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jz_subb+0), 12);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 8) = param1 + 40;
    gen_code_ptr += 12;
}
break;

case INDEX_op_string_jnz_subb: {
    long param1;
    extern void op_string_jnz_subb();
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jnz_subb+0), 12);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 8) = param1 + 40;
    gen_code_ptr += 12;
}
break;

case INDEX_op_string_jz_subb_im: {
    long param1;
    extern void op_string_jz_subb_im();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jz_subb_im+0), 30);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 22) = (long)(&raise_exception) - (long)(gen_code_ptr + 22) + -4;
    gen_code_ptr += 30;
}
break;

case INDEX_op_string_jnz_subb_im: {
    long param1;
    extern void op_string_jnz_subb_im();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jnz_subb_im+0), 30);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 22) = (long)(&raise_exception) - (long)(gen_code_ptr + 22) + -4;
    gen_code_ptr += 30;
}
break;

case INDEX_op_outb_T0_T1: {
    extern void op_outb_T0_T1();
extern char cpu_x86_outb;
    memcpy(gen_code_ptr, (void *)((char *)&op_outb_T0_T1+0), 21);
    *(uint32_t *)(gen_code_ptr + 14) = (long)(&cpu_x86_outb) - (long)(gen_code_ptr + 14) + -4;
    gen_code_ptr += 21;
}
break;

case INDEX_op_inb_T0_T1: {
    extern void op_inb_T0_T1();
extern char cpu_x86_inb;
    memcpy(gen_code_ptr, (void *)((char *)&op_inb_T0_T1+0), 14);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inb) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 14;
}
break;

case INDEX_op_inb_DX_T0: {
    extern void op_inb_DX_T0();
extern char cpu_x86_inb;
    memcpy(gen_code_ptr, (void *)((char *)&op_inb_DX_T0+0), 15);
    *(uint32_t *)(gen_code_ptr + 7) = (long)(&cpu_x86_inb) - (long)(gen_code_ptr + 7) + -4;
    gen_code_ptr += 15;
}
break;

case INDEX_op_outb_DX_T0: {
    extern void op_outb_DX_T0();
extern char cpu_x86_outb;
    memcpy(gen_code_ptr, (void *)((char *)&op_outb_DX_T0+0), 15);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&cpu_x86_outb) - (long)(gen_code_ptr + 8) + -4;
    gen_code_ptr += 15;
}
break;

case INDEX_op_jb_subw: {
    long param1, param2, param3;
    extern void op_jb_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_jb_subw+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_jz_subw: {
    long param1, param2, param3;
    extern void op_jz_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_jz_subw+0), 53);
    label_offsets[0] = 16 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 40 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 17) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 24) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 34) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 41) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 48) = param3 + 0;
    gen_code_ptr += 53;
}
break;

case INDEX_op_jbe_subw: {
    long param1, param2, param3;
    extern void op_jbe_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_jbe_subw+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_js_subw: {
    long param1, param2, param3;
    extern void op_js_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_js_subw+0), 53);
    label_offsets[0] = 16 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 40 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 17) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 24) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 34) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 41) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 48) = param3 + 0;
    gen_code_ptr += 53;
}
break;

case INDEX_op_jl_subw: {
    long param1, param2, param3;
    extern void op_jl_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_jl_subw+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_jle_subw: {
    long param1, param2, param3;
    extern void op_jle_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_jle_subw+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_loopnzw: {
    long param1, param2;
    extern void op_loopnzw();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_loopnzw+0), 51);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    *(uint32_t *)(gen_code_ptr + 37) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 47) = param2 + 0;
    gen_code_ptr += 51;
}
break;

case INDEX_op_loopzw: {
    long param1, param2;
    extern void op_loopzw();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_loopzw+0), 51);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    *(uint32_t *)(gen_code_ptr + 37) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 47) = param2 + 0;
    gen_code_ptr += 51;
}
break;

case INDEX_op_loopw: {
    long param1, param2;
    extern void op_loopw();
    memcpy(gen_code_ptr, (void *)((char *)&op_loopw+0), 35);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 20) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 31) = param2 + 0;
    gen_code_ptr += 35;
}
break;

case INDEX_op_jecxzw: {
    long param1, param2;
    extern void op_jecxzw();
    memcpy(gen_code_ptr, (void *)((char *)&op_jecxzw+0), 23);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
    gen_code_ptr += 23;
}
break;

case INDEX_op_setb_T0_subw: {
    extern void op_setb_T0_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_setb_T0_subw+0), 15);
    gen_code_ptr += 15;
}
break;

case INDEX_op_setz_T0_subw: {
    extern void op_setz_T0_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_setz_T0_subw+0), 10);
    gen_code_ptr += 10;
}
break;

case INDEX_op_setbe_T0_subw: {
    extern void op_setbe_T0_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_setbe_T0_subw+0), 15);
    gen_code_ptr += 15;
}
break;

case INDEX_op_sets_T0_subw: {
    extern void op_sets_T0_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_sets_T0_subw+0), 11);
    gen_code_ptr += 11;
}
break;

case INDEX_op_setl_T0_subw: {
    extern void op_setl_T0_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_setl_T0_subw+0), 15);
    gen_code_ptr += 15;
}
break;

case INDEX_op_setle_T0_subw: {
    extern void op_setle_T0_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_setle_T0_subw+0), 15);
    gen_code_ptr += 15;
}
break;

case INDEX_op_shlw_T0_T1: {
    extern void op_shlw_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_shlw_T0_T1+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_shrw_T0_T1: {
    extern void op_shrw_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrw_T0_T1+0), 13);
    gen_code_ptr += 13;
}
break;

case INDEX_op_sarw_T0_T1: {
    extern void op_sarw_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_sarw_T0_T1+0), 12);
    gen_code_ptr += 12;
}
break;

case INDEX_op_rolw_T0_T1_cc: {
    extern void op_rolw_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rolw_T0_T1_cc+0), 103);
    *(uint32_t *)(gen_code_ptr + 51) = (long)(&cc_table) + 0;
    gen_code_ptr += 103;
}
break;

case INDEX_op_rorw_T0_T1_cc: {
    extern void op_rorw_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rorw_T0_T1_cc+0), 104);
    *(uint32_t *)(gen_code_ptr + 51) = (long)(&cc_table) + 0;
    gen_code_ptr += 104;
}
break;

case INDEX_op_rolw_T0_T1: {
    extern void op_rolw_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rolw_T0_T1+0), 40);
    gen_code_ptr += 40;
}
break;

case INDEX_op_rorw_T0_T1: {
    extern void op_rorw_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rorw_T0_T1+0), 40);
    gen_code_ptr += 40;
}
break;

case INDEX_op_rclw_T0_T1_cc: {
    extern void op_rclw_T0_T1_cc();
extern char rclw_table;
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rclw_T0_T1_cc+0), 153);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclw_table) + 0;
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&cc_table) + 0;
    gen_code_ptr += 153;
}
break;

case INDEX_op_rcrw_T0_T1_cc: {
    extern void op_rcrw_T0_T1_cc();
extern char rclw_table;
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rcrw_T0_T1_cc+0), 153);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclw_table) + 0;
    *(uint32_t *)(gen_code_ptr + 29) = (long)(&cc_table) + 0;
    gen_code_ptr += 153;
}
break;

case INDEX_op_shlw_T0_T1_cc: {
    extern void op_shlw_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shlw_T0_T1_cc+0), 32);
    gen_code_ptr += 32;
}
break;

case INDEX_op_shrw_T0_T1_cc: {
    extern void op_shrw_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrw_T0_T1_cc+0), 37);
    gen_code_ptr += 37;
}
break;

case INDEX_op_sarw_T0_T1_cc: {
    extern void op_sarw_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_sarw_T0_T1_cc+0), 30);
    gen_code_ptr += 30;
}
break;

case INDEX_op_shldw_T0_T1_im_cc: {
    long param1;
    extern void op_shldw_T0_T1_im_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shldw_T0_T1_im_cc+0), 74);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 20) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 29) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 49) = param1 + -16;
    gen_code_ptr += 74;
}
break;

case INDEX_op_shldw_T0_T1_ECX_cc: {
    extern void op_shldw_T0_T1_ECX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shldw_T0_T1_ECX_cc+0), 106);
    gen_code_ptr += 106;
}
break;

case INDEX_op_shrdw_T0_T1_im_cc: {
    long param1;
    extern void op_shrdw_T0_T1_im_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrdw_T0_T1_im_cc+0), 73);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + -1;
    *(uint32_t *)(gen_code_ptr + 20) = param1 + 0;
    gen_code_ptr += 73;
}
break;

case INDEX_op_shrdw_T0_T1_ECX_cc: {
    extern void op_shrdw_T0_T1_ECX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrdw_T0_T1_ECX_cc+0), 96);
    gen_code_ptr += 96;
}
break;

case INDEX_op_adcw_T0_T1_cc: {
    extern void op_adcw_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_adcw_T0_T1_cc+0), 29);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 29;
}
break;

case INDEX_op_sbbw_T0_T1_cc: {
    extern void op_sbbw_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_sbbw_T0_T1_cc+0), 31);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_cmpxchgw_T0_T1_EAX_cc: {
    extern void op_cmpxchgw_T0_T1_EAX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmpxchgw_T0_T1_EAX_cc+0), 44);
    gen_code_ptr += 44;
}
break;

case INDEX_op_rolw_mem_T0_T1_cc: {
    extern void op_rolw_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rolw_mem_T0_T1_cc+0), 106);
    *(uint32_t *)(gen_code_ptr + 54) = (long)(&cc_table) + 0;
    gen_code_ptr += 106;
}
break;

case INDEX_op_rorw_mem_T0_T1_cc: {
    extern void op_rorw_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rorw_mem_T0_T1_cc+0), 107);
    *(uint32_t *)(gen_code_ptr + 54) = (long)(&cc_table) + 0;
    gen_code_ptr += 107;
}
break;

case INDEX_op_rolw_mem_T0_T1: {
    extern void op_rolw_mem_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rolw_mem_T0_T1+0), 43);
    gen_code_ptr += 43;
}
break;

case INDEX_op_rorw_mem_T0_T1: {
    extern void op_rorw_mem_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rorw_mem_T0_T1+0), 43);
    gen_code_ptr += 43;
}
break;

case INDEX_op_rclw_mem_T0_T1_cc: {
    extern void op_rclw_mem_T0_T1_cc();
extern char rclw_table;
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rclw_mem_T0_T1_cc+0), 160);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclw_table) + 0;
    *(uint32_t *)(gen_code_ptr + 33) = (long)(&cc_table) + 0;
    gen_code_ptr += 160;
}
break;

case INDEX_op_rcrw_mem_T0_T1_cc: {
    extern void op_rcrw_mem_T0_T1_cc();
extern char rclw_table;
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rcrw_mem_T0_T1_cc+0), 160);
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&rclw_table) + 0;
    *(uint32_t *)(gen_code_ptr + 33) = (long)(&cc_table) + 0;
    gen_code_ptr += 160;
}
break;

case INDEX_op_shlw_mem_T0_T1_cc: {
    extern void op_shlw_mem_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shlw_mem_T0_T1_cc+0), 35);
    gen_code_ptr += 35;
}
break;

case INDEX_op_shrw_mem_T0_T1_cc: {
    extern void op_shrw_mem_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrw_mem_T0_T1_cc+0), 40);
    gen_code_ptr += 40;
}
break;

case INDEX_op_sarw_mem_T0_T1_cc: {
    extern void op_sarw_mem_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_sarw_mem_T0_T1_cc+0), 33);
    gen_code_ptr += 33;
}
break;

case INDEX_op_shldw_mem_T0_T1_im_cc: {
    long param1;
    extern void op_shldw_mem_T0_T1_im_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shldw_mem_T0_T1_im_cc+0), 73);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 20) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 30) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + -16;
    gen_code_ptr += 73;
}
break;

case INDEX_op_shldw_mem_T0_T1_ECX_cc: {
    extern void op_shldw_mem_T0_T1_ECX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shldw_mem_T0_T1_ECX_cc+0), 109);
    gen_code_ptr += 109;
}
break;

case INDEX_op_shrdw_mem_T0_T1_im_cc: {
    long param1;
    extern void op_shrdw_mem_T0_T1_im_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrdw_mem_T0_T1_im_cc+0), 67);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + -1;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 42) = param1 + 0;
    gen_code_ptr += 67;
}
break;

case INDEX_op_shrdw_mem_T0_T1_ECX_cc: {
    extern void op_shrdw_mem_T0_T1_ECX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrdw_mem_T0_T1_ECX_cc+0), 99);
    gen_code_ptr += 99;
}
break;

case INDEX_op_adcw_mem_T0_T1_cc: {
    extern void op_adcw_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_adcw_mem_T0_T1_cc+0), 32);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 32;
}
break;

case INDEX_op_sbbw_mem_T0_T1_cc: {
    extern void op_sbbw_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_sbbw_mem_T0_T1_cc+0), 34);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 34;
}
break;

case INDEX_op_cmpxchgw_mem_T0_T1_EAX_cc: {
    extern void op_cmpxchgw_mem_T0_T1_EAX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmpxchgw_mem_T0_T1_EAX_cc+0), 47);
    gen_code_ptr += 47;
}
break;

case INDEX_op_btw_T0_T1_cc: {
    extern void op_btw_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_btw_T0_T1_cc+0), 12);
    gen_code_ptr += 12;
}
break;

case INDEX_op_btsw_T0_T1_cc: {
    extern void op_btsw_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_btsw_T0_T1_cc+0), 18);
    gen_code_ptr += 18;
}
break;

case INDEX_op_btrw_T0_T1_cc: {
    extern void op_btrw_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_btrw_T0_T1_cc+0), 18);
    gen_code_ptr += 18;
}
break;

case INDEX_op_btcw_T0_T1_cc: {
    extern void op_btcw_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_btcw_T0_T1_cc+0), 18);
    gen_code_ptr += 18;
}
break;

case INDEX_op_bsfw_T0_cc: {
    extern void op_bsfw_T0_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_bsfw_T0_cc+0), 51);
    gen_code_ptr += 51;
}
break;

case INDEX_op_bsrw_T0_cc: {
    extern void op_bsrw_T0_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_bsrw_T0_cc+0), 47);
    gen_code_ptr += 47;
}
break;

case INDEX_op_movl_T0_Dshiftw: {
    extern void op_movl_T0_Dshiftw();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_Dshiftw+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_string_jz_subw: {
    long param1;
    extern void op_string_jz_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jz_subw+0), 16);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 40;
    gen_code_ptr += 16;
}
break;

case INDEX_op_string_jnz_subw: {
    long param1;
    extern void op_string_jnz_subw();
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jnz_subw+0), 16);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 40;
    gen_code_ptr += 16;
}
break;

case INDEX_op_string_jz_subw_im: {
    long param1;
    extern void op_string_jz_subw_im();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jz_subw_im+0), 31);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 23) = (long)(&raise_exception) - (long)(gen_code_ptr + 23) + -4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_string_jnz_subw_im: {
    long param1;
    extern void op_string_jnz_subw_im();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jnz_subw_im+0), 31);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 23) = (long)(&raise_exception) - (long)(gen_code_ptr + 23) + -4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_jz_ecxw: {
    long param1, param2;
    extern void op_jz_ecxw();
    memcpy(gen_code_ptr, (void *)((char *)&op_jz_ecxw+0), 29);
    label_offsets[1] = 16 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 17) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 24) = param2 + 0;
    gen_code_ptr += 29;
}
break;

case INDEX_op_jz_ecxw_im: {
    long param1;
    extern void op_jz_ecxw_im();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_jz_ecxw_im+0), 31);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 23) = (long)(&raise_exception) - (long)(gen_code_ptr + 23) + -4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_outw_T0_T1: {
    extern void op_outw_T0_T1();
extern char cpu_x86_outw;
    memcpy(gen_code_ptr, (void *)((char *)&op_outw_T0_T1+0), 21);
    *(uint32_t *)(gen_code_ptr + 14) = (long)(&cpu_x86_outw) - (long)(gen_code_ptr + 14) + -4;
    gen_code_ptr += 21;
}
break;

case INDEX_op_inw_T0_T1: {
    extern void op_inw_T0_T1();
extern char cpu_x86_inw;
    memcpy(gen_code_ptr, (void *)((char *)&op_inw_T0_T1+0), 14);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inw) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 14;
}
break;

case INDEX_op_inw_DX_T0: {
    extern void op_inw_DX_T0();
extern char cpu_x86_inw;
    memcpy(gen_code_ptr, (void *)((char *)&op_inw_DX_T0+0), 15);
    *(uint32_t *)(gen_code_ptr + 7) = (long)(&cpu_x86_inw) - (long)(gen_code_ptr + 7) + -4;
    gen_code_ptr += 15;
}
break;

case INDEX_op_outw_DX_T0: {
    extern void op_outw_DX_T0();
extern char cpu_x86_outw;
    memcpy(gen_code_ptr, (void *)((char *)&op_outw_DX_T0+0), 15);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&cpu_x86_outw) - (long)(gen_code_ptr + 8) + -4;
    gen_code_ptr += 15;
}
break;

case INDEX_op_jb_subl: {
    long param1, param2, param3;
    extern void op_jb_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_jb_subl+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_jz_subl: {
    long param1, param2, param3;
    extern void op_jz_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_jz_subl+0), 53);
    label_offsets[0] = 16 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 40 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 17) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 24) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 34) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 41) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 48) = param3 + 0;
    gen_code_ptr += 53;
}
break;

case INDEX_op_jbe_subl: {
    long param1, param2, param3;
    extern void op_jbe_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_jbe_subl+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_js_subl: {
    long param1, param2, param3;
    extern void op_js_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_js_subl+0), 53);
    label_offsets[0] = 16 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 40 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 17) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 24) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 34) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 41) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 48) = param3 + 0;
    gen_code_ptr += 53;
}
break;

case INDEX_op_jl_subl: {
    long param1, param2, param3;
    extern void op_jl_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_jl_subl+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_jle_subl: {
    long param1, param2, param3;
    extern void op_jle_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_jle_subl+0), 57);
    label_offsets[0] = 20 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 44 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 21) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 38) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 45) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 52) = param3 + 0;
    gen_code_ptr += 57;
}
break;

case INDEX_op_loopnzl: {
    long param1, param2;
    extern void op_loopnzl();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_loopnzl+0), 47);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    *(uint32_t *)(gen_code_ptr + 31) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 43) = param2 + 0;
    gen_code_ptr += 47;
}
break;

case INDEX_op_loopzl: {
    long param1, param2;
    extern void op_loopzl();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_loopzl+0), 47);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    *(uint32_t *)(gen_code_ptr + 31) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 43) = param2 + 0;
    gen_code_ptr += 47;
}
break;

case INDEX_op_loopl: {
    long param1, param2;
    extern void op_loopl();
    memcpy(gen_code_ptr, (void *)((char *)&op_loopl+0), 27);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 23) = param2 + 0;
    gen_code_ptr += 27;
}
break;

case INDEX_op_jecxzl: {
    long param1, param2;
    extern void op_jecxzl();
    memcpy(gen_code_ptr, (void *)((char *)&op_jecxzl+0), 23);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
    gen_code_ptr += 23;
}
break;

case INDEX_op_setb_T0_subl: {
    extern void op_setb_T0_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_setb_T0_subl+0), 14);
    gen_code_ptr += 14;
}
break;

case INDEX_op_setz_T0_subl: {
    extern void op_setz_T0_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_setz_T0_subl+0), 9);
    gen_code_ptr += 9;
}
break;

case INDEX_op_setbe_T0_subl: {
    extern void op_setbe_T0_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_setbe_T0_subl+0), 14);
    gen_code_ptr += 14;
}
break;

case INDEX_op_sets_T0_subl: {
    extern void op_sets_T0_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_sets_T0_subl+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_setl_T0_subl: {
    extern void op_setl_T0_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_setl_T0_subl+0), 14);
    gen_code_ptr += 14;
}
break;

case INDEX_op_setle_T0_subl: {
    extern void op_setle_T0_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_setle_T0_subl+0), 14);
    gen_code_ptr += 14;
}
break;

case INDEX_op_shll_T0_T1: {
    extern void op_shll_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_shll_T0_T1+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_shrl_T0_T1: {
    extern void op_shrl_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrl_T0_T1+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_sarl_T0_T1: {
    extern void op_sarl_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_sarl_T0_T1+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_roll_T0_T1_cc: {
    extern void op_roll_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_roll_T0_T1_cc+0), 64);
    *(uint32_t *)(gen_code_ptr + 19) = (long)(&cc_table) + 0;
    gen_code_ptr += 64;
}
break;

case INDEX_op_rorl_T0_T1_cc: {
    extern void op_rorl_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rorl_T0_T1_cc+0), 63);
    *(uint32_t *)(gen_code_ptr + 19) = (long)(&cc_table) + 0;
    gen_code_ptr += 63;
}
break;

case INDEX_op_roll_T0_T1: {
    extern void op_roll_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_roll_T0_T1+0), 9);
    gen_code_ptr += 9;
}
break;

case INDEX_op_rorl_T0_T1: {
    extern void op_rorl_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rorl_T0_T1+0), 9);
    gen_code_ptr += 9;
}
break;

case INDEX_op_rcll_T0_T1_cc: {
    extern void op_rcll_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rcll_T0_T1_cc+0), 138);
    *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
    gen_code_ptr += 138;
}
break;

case INDEX_op_rcrl_T0_T1_cc: {
    extern void op_rcrl_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rcrl_T0_T1_cc+0), 138);
    *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
    gen_code_ptr += 138;
}
break;

case INDEX_op_shll_T0_T1_cc: {
    extern void op_shll_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shll_T0_T1_cc+0), 31);
    gen_code_ptr += 31;
}
break;

case INDEX_op_shrl_T0_T1_cc: {
    extern void op_shrl_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrl_T0_T1_cc+0), 31);
    gen_code_ptr += 31;
}
break;

case INDEX_op_sarl_T0_T1_cc: {
    extern void op_sarl_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_sarl_T0_T1_cc+0), 27);
    gen_code_ptr += 27;
}
break;

case INDEX_op_shldl_T0_T1_im_cc: {
    long param1;
    extern void op_shldl_T0_T1_im_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shldl_T0_T1_im_cc+0), 43);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + -1;
    *(uint32_t *)(gen_code_ptr + 12) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param1 + 0;
    gen_code_ptr += 43;
}
break;

case INDEX_op_shldl_T0_T1_ECX_cc: {
    extern void op_shldl_T0_T1_ECX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shldl_T0_T1_ECX_cc+0), 69);
    gen_code_ptr += 69;
}
break;

case INDEX_op_shrdl_T0_T1_im_cc: {
    long param1;
    extern void op_shrdl_T0_T1_im_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrdl_T0_T1_im_cc+0), 43);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + -1;
    *(uint32_t *)(gen_code_ptr + 12) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 28) = param1 + 0;
    gen_code_ptr += 43;
}
break;

case INDEX_op_shrdl_T0_T1_ECX_cc: {
    extern void op_shrdl_T0_T1_ECX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrdl_T0_T1_ECX_cc+0), 69);
    gen_code_ptr += 69;
}
break;

case INDEX_op_adcl_T0_T1_cc: {
    extern void op_adcl_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_adcl_T0_T1_cc+0), 29);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 29;
}
break;

case INDEX_op_sbbl_T0_T1_cc: {
    extern void op_sbbl_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_sbbl_T0_T1_cc+0), 31);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_cmpxchgl_T0_T1_EAX_cc: {
    extern void op_cmpxchgl_T0_T1_EAX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmpxchgl_T0_T1_EAX_cc+0), 25);
    gen_code_ptr += 25;
}
break;

case INDEX_op_roll_mem_T0_T1_cc: {
    extern void op_roll_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_roll_mem_T0_T1_cc+0), 66);
    *(uint32_t *)(gen_code_ptr + 21) = (long)(&cc_table) + 0;
    gen_code_ptr += 66;
}
break;

case INDEX_op_rorl_mem_T0_T1_cc: {
    extern void op_rorl_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rorl_mem_T0_T1_cc+0), 65);
    *(uint32_t *)(gen_code_ptr + 21) = (long)(&cc_table) + 0;
    gen_code_ptr += 65;
}
break;

case INDEX_op_roll_mem_T0_T1: {
    extern void op_roll_mem_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_roll_mem_T0_T1+0), 11);
    gen_code_ptr += 11;
}
break;

case INDEX_op_rorl_mem_T0_T1: {
    extern void op_rorl_mem_T0_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_rorl_mem_T0_T1+0), 11);
    gen_code_ptr += 11;
}
break;

case INDEX_op_rcll_mem_T0_T1_cc: {
    extern void op_rcll_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rcll_mem_T0_T1_cc+0), 140);
    *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
    gen_code_ptr += 140;
}
break;

case INDEX_op_rcrl_mem_T0_T1_cc: {
    extern void op_rcrl_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_rcrl_mem_T0_T1_cc+0), 140);
    *(uint32_t *)(gen_code_ptr + 20) = (long)(&cc_table) + 0;
    gen_code_ptr += 140;
}
break;

case INDEX_op_shll_mem_T0_T1_cc: {
    extern void op_shll_mem_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shll_mem_T0_T1_cc+0), 33);
    gen_code_ptr += 33;
}
break;

case INDEX_op_shrl_mem_T0_T1_cc: {
    extern void op_shrl_mem_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrl_mem_T0_T1_cc+0), 33);
    gen_code_ptr += 33;
}
break;

case INDEX_op_sarl_mem_T0_T1_cc: {
    extern void op_sarl_mem_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_sarl_mem_T0_T1_cc+0), 29);
    gen_code_ptr += 29;
}
break;

case INDEX_op_shldl_mem_T0_T1_im_cc: {
    long param1;
    extern void op_shldl_mem_T0_T1_im_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shldl_mem_T0_T1_im_cc+0), 53);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + -1;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 29) = param1 + 0;
    gen_code_ptr += 53;
}
break;

case INDEX_op_shldl_mem_T0_T1_ECX_cc: {
    extern void op_shldl_mem_T0_T1_ECX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shldl_mem_T0_T1_ECX_cc+0), 79);
    gen_code_ptr += 79;
}
break;

case INDEX_op_shrdl_mem_T0_T1_im_cc: {
    long param1;
    extern void op_shrdl_mem_T0_T1_im_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrdl_mem_T0_T1_im_cc+0), 53);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 4) = param1 + -1;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 29) = param1 + 0;
    gen_code_ptr += 53;
}
break;

case INDEX_op_shrdl_mem_T0_T1_ECX_cc: {
    extern void op_shrdl_mem_T0_T1_ECX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_shrdl_mem_T0_T1_ECX_cc+0), 79);
    gen_code_ptr += 79;
}
break;

case INDEX_op_adcl_mem_T0_T1_cc: {
    extern void op_adcl_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_adcl_mem_T0_T1_cc+0), 31);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_sbbl_mem_T0_T1_cc: {
    extern void op_sbbl_mem_T0_T1_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_sbbl_mem_T0_T1_cc+0), 33);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 33;
}
break;

case INDEX_op_cmpxchgl_mem_T0_T1_EAX_cc: {
    extern void op_cmpxchgl_mem_T0_T1_EAX_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_cmpxchgl_mem_T0_T1_EAX_cc+0), 27);
    gen_code_ptr += 27;
}
break;

case INDEX_op_btl_T0_T1_cc: {
    extern void op_btl_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_btl_T0_T1_cc+0), 12);
    gen_code_ptr += 12;
}
break;

case INDEX_op_btsl_T0_T1_cc: {
    extern void op_btsl_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_btsl_T0_T1_cc+0), 18);
    gen_code_ptr += 18;
}
break;

case INDEX_op_btrl_T0_T1_cc: {
    extern void op_btrl_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_btrl_T0_T1_cc+0), 18);
    gen_code_ptr += 18;
}
break;

case INDEX_op_btcl_T0_T1_cc: {
    extern void op_btcl_T0_T1_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_btcl_T0_T1_cc+0), 18);
    gen_code_ptr += 18;
}
break;

case INDEX_op_bsfl_T0_cc: {
    extern void op_bsfl_T0_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_bsfl_T0_cc+0), 47);
    gen_code_ptr += 47;
}
break;

case INDEX_op_bsrl_T0_cc: {
    extern void op_bsrl_T0_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_bsrl_T0_cc+0), 39);
    gen_code_ptr += 39;
}
break;

case INDEX_op_update_bt_cc: {
    extern void op_update_bt_cc();
    memcpy(gen_code_ptr, (void *)((char *)&op_update_bt_cc+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movl_T0_Dshiftl: {
    extern void op_movl_T0_Dshiftl();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_Dshiftl+0), 10);
    gen_code_ptr += 10;
}
break;

case INDEX_op_string_jz_subl: {
    long param1;
    extern void op_string_jz_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jz_subl+0), 16);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 40;
    gen_code_ptr += 16;
}
break;

case INDEX_op_string_jnz_subl: {
    long param1;
    extern void op_string_jnz_subl();
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jnz_subl+0), 16);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 40;
    gen_code_ptr += 16;
}
break;

case INDEX_op_string_jz_subl_im: {
    long param1;
    extern void op_string_jz_subl_im();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jz_subl_im+0), 31);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 23) = (long)(&raise_exception) - (long)(gen_code_ptr + 23) + -4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_string_jnz_subl_im: {
    long param1;
    extern void op_string_jnz_subl_im();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_string_jnz_subl_im+0), 31);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 23) = (long)(&raise_exception) - (long)(gen_code_ptr + 23) + -4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_jz_ecxl: {
    long param1, param2;
    extern void op_jz_ecxl();
    memcpy(gen_code_ptr, (void *)((char *)&op_jz_ecxl+0), 29);
    label_offsets[1] = 16 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 9) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 17) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 24) = param2 + 0;
    gen_code_ptr += 29;
}
break;

case INDEX_op_jz_ecxl_im: {
    long param1;
    extern void op_jz_ecxl_im();
extern char raise_exception;
    memcpy(gen_code_ptr, (void *)((char *)&op_jz_ecxl_im+0), 31);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 23) = (long)(&raise_exception) - (long)(gen_code_ptr + 23) + -4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_outl_T0_T1: {
    extern void op_outl_T0_T1();
extern char cpu_x86_outl;
    memcpy(gen_code_ptr, (void *)((char *)&op_outl_T0_T1+0), 14);
    *(uint32_t *)(gen_code_ptr + 7) = (long)(&cpu_x86_outl) - (long)(gen_code_ptr + 7) + -4;
    gen_code_ptr += 14;
}
break;

case INDEX_op_inl_T0_T1: {
    extern void op_inl_T0_T1();
extern char cpu_x86_inl;
    memcpy(gen_code_ptr, (void *)((char *)&op_inl_T0_T1+0), 14);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cpu_x86_inl) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 14;
}
break;

case INDEX_op_inl_DX_T0: {
    extern void op_inl_DX_T0();
extern char cpu_x86_inl;
    memcpy(gen_code_ptr, (void *)((char *)&op_inl_DX_T0+0), 15);
    *(uint32_t *)(gen_code_ptr + 7) = (long)(&cpu_x86_inl) - (long)(gen_code_ptr + 7) + -4;
    gen_code_ptr += 15;
}
break;

case INDEX_op_outl_DX_T0: {
    extern void op_outl_DX_T0();
extern char cpu_x86_outl;
    memcpy(gen_code_ptr, (void *)((char *)&op_outl_DX_T0+0), 15);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&cpu_x86_outl) - (long)(gen_code_ptr + 8) + -4;
    gen_code_ptr += 15;
}
break;

case INDEX_op_movsbl_T0_T0: {
    extern void op_movsbl_T0_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movsbl_T0_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movzbl_T0_T0: {
    extern void op_movzbl_T0_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movzbl_T0_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movswl_T0_T0: {
    extern void op_movswl_T0_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movswl_T0_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movzwl_T0_T0: {
    extern void op_movzwl_T0_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movzwl_T0_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_movswl_EAX_AX: {
    extern void op_movswl_EAX_AX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movswl_EAX_AX+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_movsbw_AX_AL: {
    extern void op_movsbw_AX_AL();
    memcpy(gen_code_ptr, (void *)((char *)&op_movsbw_AX_AL+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_movslq_EDX_EAX: {
    extern void op_movslq_EDX_EAX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movslq_EDX_EAX+0), 9);
    gen_code_ptr += 9;
}
break;

case INDEX_op_movswl_DX_AX: {
    extern void op_movswl_DX_AX();
    memcpy(gen_code_ptr, (void *)((char *)&op_movswl_DX_AX+0), 12);
    gen_code_ptr += 12;
}
break;

case INDEX_op_addl_ESI_T0: {
    extern void op_addl_ESI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_ESI_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addw_ESI_T0: {
    extern void op_addw_ESI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_addw_ESI_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_addl_EDI_T0: {
    extern void op_addl_EDI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_EDI_T0+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_addw_EDI_T0: {
    extern void op_addw_EDI_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_addw_EDI_T0+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_decl_ECX: {
    extern void op_decl_ECX();
    memcpy(gen_code_ptr, (void *)((char *)&op_decl_ECX+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_decw_ECX: {
    extern void op_decw_ECX();
    memcpy(gen_code_ptr, (void *)((char *)&op_decw_ECX+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_pushl_T0: {
    extern void op_pushl_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_pushl_T0+0), 12);
    gen_code_ptr += 12;
}
break;

case INDEX_op_pushw_T0: {
    extern void op_pushw_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_pushw_T0+0), 13);
    gen_code_ptr += 13;
}
break;

case INDEX_op_pushl_ss32_T0: {
    extern void op_pushl_ss32_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_pushl_ss32_T0+0), 19);
    gen_code_ptr += 19;
}
break;

case INDEX_op_pushw_ss32_T0: {
    extern void op_pushw_ss32_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_pushw_ss32_T0+0), 20);
    gen_code_ptr += 20;
}
break;

case INDEX_op_pushl_ss16_T0: {
    extern void op_pushl_ss16_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_pushl_ss16_T0+0), 25);
    gen_code_ptr += 25;
}
break;

case INDEX_op_pushw_ss16_T0: {
    extern void op_pushw_ss16_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_pushw_ss16_T0+0), 26);
    gen_code_ptr += 26;
}
break;

case INDEX_op_popl_T0: {
    extern void op_popl_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_popl_T0+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_popw_T0: {
    extern void op_popw_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_popw_T0+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_popl_ss32_T0: {
    extern void op_popl_ss32_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_popl_ss32_T0+0), 11);
    gen_code_ptr += 11;
}
break;

case INDEX_op_popw_ss32_T0: {
    extern void op_popw_ss32_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_popw_ss32_T0+0), 12);
    gen_code_ptr += 12;
}
break;

case INDEX_op_popl_ss16_T0: {
    extern void op_popl_ss16_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_popl_ss16_T0+0), 12);
    gen_code_ptr += 12;
}
break;

case INDEX_op_popw_ss16_T0: {
    extern void op_popw_ss16_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_popw_ss16_T0+0), 13);
    gen_code_ptr += 13;
}
break;

case INDEX_op_addl_ESP_4: {
    extern void op_addl_ESP_4();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_ESP_4+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_addl_ESP_2: {
    extern void op_addl_ESP_2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_ESP_2+0), 4);
    gen_code_ptr += 4;
}
break;

case INDEX_op_addw_ESP_4: {
    extern void op_addw_ESP_4();
    memcpy(gen_code_ptr, (void *)((char *)&op_addw_ESP_4+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_addw_ESP_2: {
    extern void op_addw_ESP_2();
    memcpy(gen_code_ptr, (void *)((char *)&op_addw_ESP_2+0), 5);
    gen_code_ptr += 5;
}
break;

case INDEX_op_addl_ESP_im: {
    long param1;
    extern void op_addl_ESP_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_ESP_im+0), 7);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 3) = param1 + 0;
    gen_code_ptr += 7;
}
break;

case INDEX_op_addw_ESP_im: {
    long param1;
    extern void op_addw_ESP_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_addw_ESP_im+0), 12);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 4) = param1 + 0;
    gen_code_ptr += 12;
}
break;

case INDEX_op_rdtsc: {
    extern void op_rdtsc();
extern char helper_rdtsc;
    memcpy(gen_code_ptr, (void *)((char *)&op_rdtsc+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_rdtsc) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_cpuid: {
    extern void op_cpuid();
extern char helper_cpuid;
    memcpy(gen_code_ptr, (void *)((char *)&op_cpuid+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_cpuid) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_rdmsr: {
    extern void op_rdmsr();
extern char helper_rdmsr;
    memcpy(gen_code_ptr, (void *)((char *)&op_rdmsr+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_rdmsr) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_wrmsr: {
    extern void op_wrmsr();
extern char helper_wrmsr;
    memcpy(gen_code_ptr, (void *)((char *)&op_wrmsr+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_wrmsr) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_aam: {
    long param1;
    extern void op_aam();
    memcpy(gen_code_ptr, (void *)((char *)&op_aam+0), 36);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    gen_code_ptr += 36;
}
break;

case INDEX_op_aad: {
    long param1;
    extern void op_aad();
    memcpy(gen_code_ptr, (void *)((char *)&op_aad+0), 23);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 6) = param1 + 0;
    gen_code_ptr += 23;
}
break;

case INDEX_op_aaa: {
    extern void op_aaa();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_aaa+0), 153);
    *(uint32_t *)(gen_code_ptr + 9) = (long)(&cc_table) + 0;
    gen_code_ptr += 153;
}
break;

case INDEX_op_aas: {
    extern void op_aas();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_aas+0), 135);
    *(uint32_t *)(gen_code_ptr + 9) = (long)(&cc_table) + 0;
    gen_code_ptr += 135;
}
break;

case INDEX_op_daa: {
    extern void op_daa();
extern char cc_table;
extern char parity_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_daa+0), 138);
    *(uint32_t *)(gen_code_ptr + 9) = (long)(&cc_table) + 0;
    *(uint32_t *)(gen_code_ptr + 118) = (long)(&parity_table) + 0;
    gen_code_ptr += 138;
}
break;

case INDEX_op_das: {
    extern void op_das();
extern char cc_table;
extern char parity_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_das+0), 162);
    *(uint32_t *)(gen_code_ptr + 9) = (long)(&cc_table) + 0;
    *(uint32_t *)(gen_code_ptr + 142) = (long)(&parity_table) + 0;
    gen_code_ptr += 162;
}
break;

case INDEX_op_movl_seg_T0: {
    long param1, param2;
    extern void op_movl_seg_T0();
extern char load_seg;
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_seg_T0+0), 22);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 10) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 15) = (long)(&load_seg) - (long)(gen_code_ptr + 15) + -4;
    gen_code_ptr += 22;
}
break;

case INDEX_op_movl_seg_T0_vm: {
    long param1;
    extern void op_movl_seg_T0_vm();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_seg_T0_vm+0), 17);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    gen_code_ptr += 17;
}
break;

case INDEX_op_movl_T0_seg: {
    long param1;
    extern void op_movl_T0_seg();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_seg+0), 15);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    gen_code_ptr += 15;
}
break;

case INDEX_op_movl_A0_seg: {
    long param1;
    extern void op_movl_A0_seg();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_A0_seg+0), 6);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
    gen_code_ptr += 6;
}
break;

case INDEX_op_addl_A0_seg: {
    long param1;
    extern void op_addl_A0_seg();
    memcpy(gen_code_ptr, (void *)((char *)&op_addl_A0_seg+0), 6);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
    gen_code_ptr += 6;
}
break;

case INDEX_op_lsl: {
    extern void op_lsl();
extern char helper_lsl;
    memcpy(gen_code_ptr, (void *)((char *)&op_lsl+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_lsl) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_lar: {
    extern void op_lar();
extern char helper_lar;
    memcpy(gen_code_ptr, (void *)((char *)&op_lar+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_lar) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_ljmp_protected_T0_T1: {
    extern void op_ljmp_protected_T0_T1();
extern char helper_ljmp_protected_T0_T1;
    memcpy(gen_code_ptr, (void *)((char *)&op_ljmp_protected_T0_T1+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_ljmp_protected_T0_T1) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_lcall_real_T0_T1: {
    long param1, param2;
    extern void op_lcall_real_T0_T1();
extern char helper_lcall_real_T0_T1;
    memcpy(gen_code_ptr, (void *)((char *)&op_lcall_real_T0_T1+0), 17);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&helper_lcall_real_T0_T1) - (long)(gen_code_ptr + 11) + -4;
    gen_code_ptr += 17;
}
break;

case INDEX_op_lcall_protected_T0_T1: {
    long param1, param2;
    extern void op_lcall_protected_T0_T1();
extern char helper_lcall_protected_T0_T1;
    memcpy(gen_code_ptr, (void *)((char *)&op_lcall_protected_T0_T1+0), 17);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&helper_lcall_protected_T0_T1) - (long)(gen_code_ptr + 11) + -4;
    gen_code_ptr += 17;
}
break;

case INDEX_op_iret_real: {
    long param1;
    extern void op_iret_real();
extern char helper_iret_real;
    memcpy(gen_code_ptr, (void *)((char *)&op_iret_real+0), 11);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&helper_iret_real) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 11;
}
break;

case INDEX_op_iret_protected: {
    long param1;
    extern void op_iret_protected();
extern char helper_iret_protected;
    memcpy(gen_code_ptr, (void *)((char *)&op_iret_protected+0), 11);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&helper_iret_protected) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 11;
}
break;

case INDEX_op_lret_protected: {
    long param1, param2;
    extern void op_lret_protected();
extern char helper_lret_protected;
    memcpy(gen_code_ptr, (void *)((char *)&op_lret_protected+0), 17);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 11) = (long)(&helper_lret_protected) - (long)(gen_code_ptr + 11) + -4;
    gen_code_ptr += 17;
}
break;

case INDEX_op_lldt_T0: {
    extern void op_lldt_T0();
extern char helper_lldt_T0;
    memcpy(gen_code_ptr, (void *)((char *)&op_lldt_T0+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_lldt_T0) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_ltr_T0: {
    extern void op_ltr_T0();
extern char helper_ltr_T0;
    memcpy(gen_code_ptr, (void *)((char *)&op_ltr_T0+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_ltr_T0) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_movl_crN_T0: {
    long param1;
    extern void op_movl_crN_T0();
extern char helper_movl_crN_T0;
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_crN_T0+0), 11);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&helper_movl_crN_T0) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 11;
}
break;

case INDEX_op_movl_drN_T0: {
    long param1;
    extern void op_movl_drN_T0();
extern char helper_movl_drN_T0;
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_drN_T0+0), 11);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&helper_movl_drN_T0) - (long)(gen_code_ptr + 6) + -4;
    gen_code_ptr += 11;
}
break;

case INDEX_op_lmsw_T0: {
    extern void op_lmsw_T0();
extern char helper_movl_crN_T0;
    memcpy(gen_code_ptr, (void *)((char *)&op_lmsw_T0+0), 26);
    *(uint32_t *)(gen_code_ptr + 21) = (long)(&helper_movl_crN_T0) - (long)(gen_code_ptr + 21) + -4;
    gen_code_ptr += 26;
}
break;

case INDEX_op_invlpg_A0: {
    extern void op_invlpg_A0();
extern char helper_invlpg;
    memcpy(gen_code_ptr, (void *)((char *)&op_invlpg_A0+0), 7);
    *(uint32_t *)(gen_code_ptr + 2) = (long)(&helper_invlpg) - (long)(gen_code_ptr + 2) + -4;
    gen_code_ptr += 7;
}
break;

case INDEX_op_movl_T0_env: {
    long param1;
    extern void op_movl_T0_env();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_env+0), 6);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_env_T0: {
    long param1;
    extern void op_movl_env_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_env_T0+0), 6);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
    gen_code_ptr += 6;
}
break;

case INDEX_op_movl_env_T1: {
    long param1;
    extern void op_movl_env_T1();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_env_T1+0), 6);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 2) = param1 + 0;
    gen_code_ptr += 6;
}
break;

case INDEX_op_clts: {
    extern void op_clts();
    memcpy(gen_code_ptr, (void *)((char *)&op_clts+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_jcc: {
    long param1, param2, param3;
    extern void op_jcc();
    memcpy(gen_code_ptr, (void *)((char *)&op_jcc+0), 49);
    label_offsets[0] = 12 + (gen_code_ptr - gen_code_buf);
    label_offsets[1] = 36 + (gen_code_ptr - gen_code_buf);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    param3 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 6) = param1 + 36;
    *(uint32_t *)(gen_code_ptr + 13) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 20) = param2 + 0;
    *(uint32_t *)(gen_code_ptr + 30) = param1 + 40;
    *(uint32_t *)(gen_code_ptr + 37) = param1 + 1;
    *(uint32_t *)(gen_code_ptr + 44) = param3 + 0;
    gen_code_ptr += 49;
}
break;

case INDEX_op_jcc_im: {
    long param1, param2;
    extern void op_jcc_im();
    memcpy(gen_code_ptr, (void *)((char *)&op_jcc_im+0), 23);
    param1 = *opparam_ptr++;
    param2 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 7) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 19) = param2 + 0;
    gen_code_ptr += 23;
}
break;

case INDEX_op_seto_T0_cc: {
    extern void op_seto_T0_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_seto_T0_cc+0), 18);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 18;
}
break;

case INDEX_op_setb_T0_cc: {
    extern void op_setb_T0_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_setb_T0_cc+0), 12);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 12;
}
break;

case INDEX_op_setz_T0_cc: {
    extern void op_setz_T0_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_setz_T0_cc+0), 18);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 18;
}
break;

case INDEX_op_setbe_T0_cc: {
    extern void op_setbe_T0_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_setbe_T0_cc+0), 20);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 20;
}
break;

case INDEX_op_sets_T0_cc: {
    extern void op_sets_T0_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_sets_T0_cc+0), 18);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 18;
}
break;

case INDEX_op_setp_T0_cc: {
    extern void op_setp_T0_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_setp_T0_cc+0), 18);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 18;
}
break;

case INDEX_op_setl_T0_cc: {
    extern void op_setl_T0_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_setl_T0_cc+0), 25);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 25;
}
break;

case INDEX_op_setle_T0_cc: {
    extern void op_setle_T0_cc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_setle_T0_cc+0), 40);
    *(uint32_t *)(gen_code_ptr + 7) = (long)(&cc_table) + 0;
    gen_code_ptr += 40;
}
break;

case INDEX_op_xor_T0_1: {
    extern void op_xor_T0_1();
    memcpy(gen_code_ptr, (void *)((char *)&op_xor_T0_1+0), 3);
    gen_code_ptr += 3;
}
break;

case INDEX_op_set_cc_op: {
    long param1;
    extern void op_set_cc_op();
    memcpy(gen_code_ptr, (void *)((char *)&op_set_cc_op+0), 7);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 3) = param1 + 0;
    gen_code_ptr += 7;
}
break;

case INDEX_op_movl_eflags_T0: {
    extern void op_movl_eflags_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_eflags_T0+0), 49);
    gen_code_ptr += 49;
}
break;

case INDEX_op_movw_eflags_T0: {
    extern void op_movw_eflags_T0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_eflags_T0+0), 49);
    gen_code_ptr += 49;
}
break;

case INDEX_op_movl_eflags_T0_cpl0: {
    extern void op_movl_eflags_T0_cpl0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_eflags_T0_cpl0+0), 49);
    gen_code_ptr += 49;
}
break;

case INDEX_op_movw_eflags_T0_cpl0: {
    extern void op_movw_eflags_T0_cpl0();
    memcpy(gen_code_ptr, (void *)((char *)&op_movw_eflags_T0_cpl0+0), 49);
    gen_code_ptr += 49;
}
break;

case INDEX_op_movb_eflags_T0: {
    extern void op_movb_eflags_T0();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_movb_eflags_T0+0), 28);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 28;
}
break;

case INDEX_op_movl_T0_eflags: {
    extern void op_movl_T0_eflags();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_movl_T0_eflags+0), 33);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 33;
}
break;

case INDEX_op_cld: {
    extern void op_cld();
    memcpy(gen_code_ptr, (void *)((char *)&op_cld+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_std: {
    extern void op_std();
    memcpy(gen_code_ptr, (void *)((char *)&op_std+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_clc: {
    extern void op_clc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_clc+0), 16);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 16;
}
break;

case INDEX_op_stc: {
    extern void op_stc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_stc+0), 16);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 16;
}
break;

case INDEX_op_cmc: {
    extern void op_cmc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_cmc+0), 16);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 16;
}
break;

case INDEX_op_salc: {
    extern void op_salc();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_salc+0), 15);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 4;
    gen_code_ptr += 15;
}
break;

case INDEX_op_flds_FT0_A0: {
    extern void op_flds_FT0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_flds_FT0_A0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_fldl_FT0_A0: {
    extern void op_fldl_FT0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fldl_FT0_A0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_fild_FT0_A0: {
    extern void op_fild_FT0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fild_FT0_A0+0), 16);
    gen_code_ptr += 16;
}
break;

case INDEX_op_fildl_FT0_A0: {
    extern void op_fildl_FT0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fildl_FT0_A0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_fildll_FT0_A0: {
    extern void op_fildll_FT0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fildll_FT0_A0+0), 8);
    gen_code_ptr += 8;
}
break;

case INDEX_op_flds_ST0_A0: {
    extern void op_flds_ST0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_flds_ST0_A0+0), 24);
    gen_code_ptr += 24;
}
break;

case INDEX_op_fldl_ST0_A0: {
    extern void op_fldl_ST0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fldl_ST0_A0+0), 24);
    gen_code_ptr += 24;
}
break;

case INDEX_op_fldt_ST0_A0: {
    extern void op_fldt_ST0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fldt_ST0_A0+0), 24);
    gen_code_ptr += 24;
}
break;

case INDEX_op_fild_ST0_A0: {
    extern void op_fild_ST0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fild_ST0_A0+0), 32);
    gen_code_ptr += 32;
}
break;

case INDEX_op_fildl_ST0_A0: {
    extern void op_fildl_ST0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fildl_ST0_A0+0), 24);
    gen_code_ptr += 24;
}
break;

case INDEX_op_fildll_ST0_A0: {
    extern void op_fildll_ST0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fildll_ST0_A0+0), 24);
    gen_code_ptr += 24;
}
break;

case INDEX_op_fsts_ST0_A0: {
    extern void op_fsts_ST0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fsts_ST0_A0+0), 14);
    gen_code_ptr += 14;
}
break;

case INDEX_op_fstl_ST0_A0: {
    extern void op_fstl_ST0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fstl_ST0_A0+0), 18);
    gen_code_ptr += 18;
}
break;

case INDEX_op_fstt_ST0_A0: {
    extern void op_fstt_ST0_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fstt_ST0_A0+0), 26);
    gen_code_ptr += 26;
}
break;

case INDEX_op_fist_ST0_A0: {
    extern void op_fist_ST0_A0();
extern char lrintl;
    memcpy(gen_code_ptr, (void *)((char *)&op_fist_ST0_A0+0), 41);
    *(uint32_t *)(gen_code_ptr + 19) = (long)(&lrintl) - (long)(gen_code_ptr + 19) + -4;
    gen_code_ptr += 41;
}
break;

case INDEX_op_fistl_ST0_A0: {
    extern void op_fistl_ST0_A0();
extern char lrintl;
    memcpy(gen_code_ptr, (void *)((char *)&op_fistl_ST0_A0+0), 28);
    *(uint32_t *)(gen_code_ptr + 19) = (long)(&lrintl) - (long)(gen_code_ptr + 19) + -4;
    gen_code_ptr += 28;
}
break;

case INDEX_op_fistll_ST0_A0: {
    extern void op_fistll_ST0_A0();
extern char llrintl;
    memcpy(gen_code_ptr, (void *)((char *)&op_fistll_ST0_A0+0), 31);
    *(uint32_t *)(gen_code_ptr + 19) = (long)(&llrintl) - (long)(gen_code_ptr + 19) + -4;
    gen_code_ptr += 31;
}
break;

case INDEX_op_fbld_ST0_A0: {
    extern void op_fbld_ST0_A0();
extern char helper_fbld_ST0_A0;
    memcpy(gen_code_ptr, (void *)((char *)&op_fbld_ST0_A0+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fbld_ST0_A0) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fbst_ST0_A0: {
    extern void op_fbst_ST0_A0();
extern char helper_fbst_ST0_A0;
    memcpy(gen_code_ptr, (void *)((char *)&op_fbst_ST0_A0+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fbst_ST0_A0) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fpush: {
    extern void op_fpush();
    memcpy(gen_code_ptr, (void *)((char *)&op_fpush+0), 15);
    gen_code_ptr += 15;
}
break;

case INDEX_op_fpop: {
    extern void op_fpop();
    memcpy(gen_code_ptr, (void *)((char *)&op_fpop+0), 15);
    gen_code_ptr += 15;
}
break;

case INDEX_op_fdecstp: {
    extern void op_fdecstp();
    memcpy(gen_code_ptr, (void *)((char *)&op_fdecstp+0), 17);
    gen_code_ptr += 17;
}
break;

case INDEX_op_fincstp: {
    extern void op_fincstp();
    memcpy(gen_code_ptr, (void *)((char *)&op_fincstp+0), 17);
    gen_code_ptr += 17;
}
break;

case INDEX_op_fmov_ST0_FT0: {
    extern void op_fmov_ST0_FT0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fmov_ST0_FT0+0), 16);
    gen_code_ptr += 16;
}
break;

case INDEX_op_fmov_FT0_STN: {
    long param1;
    extern void op_fmov_FT0_STN();
    memcpy(gen_code_ptr, (void *)((char *)&op_fmov_FT0_STN+0), 44);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 4) = param1 + 0;
    gen_code_ptr += 44;
}
break;

case INDEX_op_fmov_ST0_STN: {
    long param1;
    extern void op_fmov_ST0_STN();
    memcpy(gen_code_ptr, (void *)((char *)&op_fmov_ST0_STN+0), 36);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 14) = param1 + 0;
    gen_code_ptr += 36;
}
break;

case INDEX_op_fmov_STN_ST0: {
    long param1;
    extern void op_fmov_STN_ST0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fmov_STN_ST0+0), 36);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    gen_code_ptr += 36;
}
break;

case INDEX_op_fxchg_ST0_STN: {
    long param1;
    extern void op_fxchg_ST0_STN();
    memcpy(gen_code_ptr, (void *)((char *)&op_fxchg_ST0_STN+0), 64);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 23) = param1 + 0;
    gen_code_ptr += 64;
}
break;

case INDEX_op_fcom_ST0_FT0: {
    extern void op_fcom_ST0_FT0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fcom_ST0_FT0+0), 74);
    gen_code_ptr += 74;
}
break;

case INDEX_op_fucom_ST0_FT0: {
    extern void op_fucom_ST0_FT0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fucom_ST0_FT0+0), 74);
    gen_code_ptr += 74;
}
break;

case INDEX_op_fcomi_ST0_FT0: {
    extern void op_fcomi_ST0_FT0();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_fcomi_ST0_FT0+0), 77);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 77;
}
break;

case INDEX_op_fucomi_ST0_FT0: {
    extern void op_fucomi_ST0_FT0();
extern char cc_table;
    memcpy(gen_code_ptr, (void *)((char *)&op_fucomi_ST0_FT0+0), 77);
    *(uint32_t *)(gen_code_ptr + 6) = (long)(&cc_table) + 0;
    gen_code_ptr += 77;
}
break;

case INDEX_op_fadd_ST0_FT0: {
    extern void op_fadd_ST0_FT0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fadd_ST0_FT0+0), 22);
    gen_code_ptr += 22;
}
break;

case INDEX_op_fmul_ST0_FT0: {
    extern void op_fmul_ST0_FT0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fmul_ST0_FT0+0), 22);
    gen_code_ptr += 22;
}
break;

case INDEX_op_fsub_ST0_FT0: {
    extern void op_fsub_ST0_FT0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fsub_ST0_FT0+0), 22);
    gen_code_ptr += 22;
}
break;

case INDEX_op_fsubr_ST0_FT0: {
    extern void op_fsubr_ST0_FT0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fsubr_ST0_FT0+0), 22);
    gen_code_ptr += 22;
}
break;

case INDEX_op_fdiv_ST0_FT0: {
    extern void op_fdiv_ST0_FT0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fdiv_ST0_FT0+0), 22);
    gen_code_ptr += 22;
}
break;

case INDEX_op_fdivr_ST0_FT0: {
    extern void op_fdivr_ST0_FT0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fdivr_ST0_FT0+0), 22);
    gen_code_ptr += 22;
}
break;

case INDEX_op_fadd_STN_ST0: {
    long param1;
    extern void op_fadd_STN_ST0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fadd_STN_ST0+0), 35);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    gen_code_ptr += 35;
}
break;

case INDEX_op_fmul_STN_ST0: {
    long param1;
    extern void op_fmul_STN_ST0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fmul_STN_ST0+0), 35);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    gen_code_ptr += 35;
}
break;

case INDEX_op_fsub_STN_ST0: {
    long param1;
    extern void op_fsub_STN_ST0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fsub_STN_ST0+0), 35);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    gen_code_ptr += 35;
}
break;

case INDEX_op_fsubr_STN_ST0: {
    long param1;
    extern void op_fsubr_STN_ST0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fsubr_STN_ST0+0), 37);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    gen_code_ptr += 37;
}
break;

case INDEX_op_fdiv_STN_ST0: {
    long param1;
    extern void op_fdiv_STN_ST0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fdiv_STN_ST0+0), 35);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    gen_code_ptr += 35;
}
break;

case INDEX_op_fdivr_STN_ST0: {
    long param1;
    extern void op_fdivr_STN_ST0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fdivr_STN_ST0+0), 37);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 5) = param1 + 0;
    gen_code_ptr += 37;
}
break;

case INDEX_op_fchs_ST0: {
    extern void op_fchs_ST0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fchs_ST0+0), 27);
    gen_code_ptr += 27;
}
break;

case INDEX_op_fabs_ST0: {
    extern void op_fabs_ST0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fabs_ST0+0), 27);
    gen_code_ptr += 27;
}
break;

case INDEX_op_fxam_ST0: {
    extern void op_fxam_ST0();
extern char helper_fxam_ST0;
    memcpy(gen_code_ptr, (void *)((char *)&op_fxam_ST0+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fxam_ST0) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fld1_ST0: {
    extern void op_fld1_ST0();
extern char f15rk;
    memcpy(gen_code_ptr, (void *)((char *)&op_fld1_ST0+0), 16);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 12;
    gen_code_ptr += 16;
}
break;

case INDEX_op_fldl2t_ST0: {
    extern void op_fldl2t_ST0();
extern char f15rk;
    memcpy(gen_code_ptr, (void *)((char *)&op_fldl2t_ST0+0), 16);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 72;
    gen_code_ptr += 16;
}
break;

case INDEX_op_fldl2e_ST0: {
    extern void op_fldl2e_ST0();
extern char f15rk;
    memcpy(gen_code_ptr, (void *)((char *)&op_fldl2e_ST0+0), 16);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 60;
    gen_code_ptr += 16;
}
break;

case INDEX_op_fldpi_ST0: {
    extern void op_fldpi_ST0();
extern char f15rk;
    memcpy(gen_code_ptr, (void *)((char *)&op_fldpi_ST0+0), 16);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 24;
    gen_code_ptr += 16;
}
break;

case INDEX_op_fldlg2_ST0: {
    extern void op_fldlg2_ST0();
extern char f15rk;
    memcpy(gen_code_ptr, (void *)((char *)&op_fldlg2_ST0+0), 16);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 36;
    gen_code_ptr += 16;
}
break;

case INDEX_op_fldln2_ST0: {
    extern void op_fldln2_ST0();
extern char f15rk;
    memcpy(gen_code_ptr, (void *)((char *)&op_fldln2_ST0+0), 16);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 48;
    gen_code_ptr += 16;
}
break;

case INDEX_op_fldz_ST0: {
    extern void op_fldz_ST0();
extern char f15rk;
    memcpy(gen_code_ptr, (void *)((char *)&op_fldz_ST0+0), 16);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 0;
    gen_code_ptr += 16;
}
break;

case INDEX_op_fldz_FT0: {
    extern void op_fldz_FT0();
extern char f15rk;
    memcpy(gen_code_ptr, (void *)((char *)&op_fldz_FT0+0), 16);
    *(uint32_t *)(gen_code_ptr + 8) = (long)(&f15rk) + 0;
    gen_code_ptr += 16;
}
break;

case INDEX_op_f2xm1: {
    extern void op_f2xm1();
extern char helper_f2xm1;
    memcpy(gen_code_ptr, (void *)((char *)&op_f2xm1+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_f2xm1) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fyl2x: {
    extern void op_fyl2x();
extern char helper_fyl2x;
    memcpy(gen_code_ptr, (void *)((char *)&op_fyl2x+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fyl2x) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fptan: {
    extern void op_fptan();
extern char helper_fptan;
    memcpy(gen_code_ptr, (void *)((char *)&op_fptan+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fptan) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fpatan: {
    extern void op_fpatan();
extern char helper_fpatan;
    memcpy(gen_code_ptr, (void *)((char *)&op_fpatan+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fpatan) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fxtract: {
    extern void op_fxtract();
extern char helper_fxtract;
    memcpy(gen_code_ptr, (void *)((char *)&op_fxtract+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fxtract) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fprem1: {
    extern void op_fprem1();
extern char helper_fprem1;
    memcpy(gen_code_ptr, (void *)((char *)&op_fprem1+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fprem1) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fprem: {
    extern void op_fprem();
extern char helper_fprem;
    memcpy(gen_code_ptr, (void *)((char *)&op_fprem+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fprem) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fyl2xp1: {
    extern void op_fyl2xp1();
extern char helper_fyl2xp1;
    memcpy(gen_code_ptr, (void *)((char *)&op_fyl2xp1+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fyl2xp1) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fsqrt: {
    extern void op_fsqrt();
extern char helper_fsqrt;
    memcpy(gen_code_ptr, (void *)((char *)&op_fsqrt+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fsqrt) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fsincos: {
    extern void op_fsincos();
extern char helper_fsincos;
    memcpy(gen_code_ptr, (void *)((char *)&op_fsincos+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fsincos) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_frndint: {
    extern void op_frndint();
extern char helper_frndint;
    memcpy(gen_code_ptr, (void *)((char *)&op_frndint+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_frndint) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fscale: {
    extern void op_fscale();
extern char helper_fscale;
    memcpy(gen_code_ptr, (void *)((char *)&op_fscale+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fscale) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fsin: {
    extern void op_fsin();
extern char helper_fsin;
    memcpy(gen_code_ptr, (void *)((char *)&op_fsin+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fsin) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fcos: {
    extern void op_fcos();
extern char helper_fcos;
    memcpy(gen_code_ptr, (void *)((char *)&op_fcos+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&helper_fcos) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_fnstsw_A0: {
    extern void op_fnstsw_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fnstsw_A0+0), 23);
    gen_code_ptr += 23;
}
break;

case INDEX_op_fnstsw_EAX: {
    extern void op_fnstsw_EAX();
    memcpy(gen_code_ptr, (void *)((char *)&op_fnstsw_EAX+0), 33);
    gen_code_ptr += 33;
}
break;

case INDEX_op_fnstcw_A0: {
    extern void op_fnstcw_A0();
    memcpy(gen_code_ptr, (void *)((char *)&op_fnstcw_A0+0), 6);
    gen_code_ptr += 6;
}
break;

case INDEX_op_fldcw_A0: {
    extern void op_fldcw_A0();
extern char fesetround;
    memcpy(gen_code_ptr, (void *)((char *)&op_fldcw_A0+0), 63);
    *(uint32_t *)(gen_code_ptr + 58) = (long)(&fesetround) - (long)(gen_code_ptr + 58) + -4;
    gen_code_ptr += 63;
}
break;

case INDEX_op_fclex: {
    extern void op_fclex();
    memcpy(gen_code_ptr, (void *)((char *)&op_fclex+0), 7);
    gen_code_ptr += 7;
}
break;

case INDEX_op_fninit: {
    extern void op_fninit();
    memcpy(gen_code_ptr, (void *)((char *)&op_fninit+0), 53);
    gen_code_ptr += 53;
}
break;

case INDEX_op_fnstenv_A0: {
    long param1;
    extern void op_fnstenv_A0();
extern char helper_fstenv;
    memcpy(gen_code_ptr, (void *)((char *)&op_fnstenv_A0+0), 13);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 7) = (long)(&helper_fstenv) - (long)(gen_code_ptr + 7) + -4;
    gen_code_ptr += 13;
}
break;

case INDEX_op_fldenv_A0: {
    long param1;
    extern void op_fldenv_A0();
extern char helper_fldenv;
    memcpy(gen_code_ptr, (void *)((char *)&op_fldenv_A0+0), 13);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 7) = (long)(&helper_fldenv) - (long)(gen_code_ptr + 7) + -4;
    gen_code_ptr += 13;
}
break;

case INDEX_op_fnsave_A0: {
    long param1;
    extern void op_fnsave_A0();
extern char helper_fsave;
    memcpy(gen_code_ptr, (void *)((char *)&op_fnsave_A0+0), 13);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 7) = (long)(&helper_fsave) - (long)(gen_code_ptr + 7) + -4;
    gen_code_ptr += 13;
}
break;

case INDEX_op_frstor_A0: {
    long param1;
    extern void op_frstor_A0();
extern char helper_frstor;
    memcpy(gen_code_ptr, (void *)((char *)&op_frstor_A0+0), 13);
    param1 = *opparam_ptr++;
    *(uint32_t *)(gen_code_ptr + 1) = param1 + 0;
    *(uint32_t *)(gen_code_ptr + 7) = (long)(&helper_frstor) - (long)(gen_code_ptr + 7) + -4;
    gen_code_ptr += 13;
}
break;

case INDEX_op_lock: {
    extern void op_lock();
extern char cpu_lock;
    memcpy(gen_code_ptr, (void *)((char *)&op_lock+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&cpu_lock) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

case INDEX_op_unlock: {
    extern void op_unlock();
extern char cpu_unlock;
    memcpy(gen_code_ptr, (void *)((char *)&op_unlock+0), 5);
    *(uint32_t *)(gen_code_ptr + 1) = (long)(&cpu_unlock) - (long)(gen_code_ptr + 1) + -4;
    gen_code_ptr += 5;
}
break;

        case INDEX_op_nop:
            break;
        case INDEX_op_nop1:
            opparam_ptr++;
            break;
        case INDEX_op_nop2:
            opparam_ptr += 2;
            break;
        case INDEX_op_nop3:
            opparam_ptr += 3;
            break;
        default:
            goto the_end;
        }
    }
 the_end:
flush_icache_range((unsigned long)gen_code_buf, (unsigned long)gen_code_ptr);
return gen_code_ptr -  gen_code_buf;
}


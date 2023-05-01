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

static inline void gen_op_update2_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_update2_cc;
}

static inline void gen_op_update1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_update1_cc;
}

static inline void gen_op_update_neg_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_update_neg_cc;
}

static inline void gen_op_cmpl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpl_T0_T1_cc;
}

static inline void gen_op_update_inc_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_update_inc_cc;
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

static inline void gen_op_divb_AL_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_divb_AL_T0;
}

static inline void gen_op_idivb_AL_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_idivb_AL_T0;
}

static inline void gen_op_divw_AX_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_divw_AX_T0;
}

static inline void gen_op_idivw_AX_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_idivw_AX_T0;
}

static inline void gen_op_divl_EAX_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_divl_EAX_T0;
}

static inline void gen_op_idivl_EAX_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
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

static inline void gen_op_andl_T0_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_andl_T0_im;
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

static inline void gen_op_ldub_user_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldub_user_T0_A0;
}

static inline void gen_op_ldsb_user_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsb_user_T0_A0;
}

static inline void gen_op_lduw_user_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_lduw_user_T0_A0;
}

static inline void gen_op_ldsw_user_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsw_user_T0_A0;
}

static inline void gen_op_ldl_user_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldl_user_T0_A0;
}

static inline void gen_op_ldub_user_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldub_user_T1_A0;
}

static inline void gen_op_ldsb_user_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsb_user_T1_A0;
}

static inline void gen_op_lduw_user_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_lduw_user_T1_A0;
}

static inline void gen_op_ldsw_user_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsw_user_T1_A0;
}

static inline void gen_op_ldl_user_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldl_user_T1_A0;
}

static inline void gen_op_stb_user_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_stb_user_T0_A0;
}

static inline void gen_op_stw_user_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_stw_user_T0_A0;
}

static inline void gen_op_stl_user_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_stl_user_T0_A0;
}

static inline void gen_op_ldub_kernel_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldub_kernel_T0_A0;
}

static inline void gen_op_ldsb_kernel_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsb_kernel_T0_A0;
}

static inline void gen_op_lduw_kernel_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_lduw_kernel_T0_A0;
}

static inline void gen_op_ldsw_kernel_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsw_kernel_T0_A0;
}

static inline void gen_op_ldl_kernel_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldl_kernel_T0_A0;
}

static inline void gen_op_ldub_kernel_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldub_kernel_T1_A0;
}

static inline void gen_op_ldsb_kernel_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsb_kernel_T1_A0;
}

static inline void gen_op_lduw_kernel_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_lduw_kernel_T1_A0;
}

static inline void gen_op_ldsw_kernel_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldsw_kernel_T1_A0;
}

static inline void gen_op_ldl_kernel_T1_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_ldl_kernel_T1_A0;
}

static inline void gen_op_stb_kernel_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_stb_kernel_T0_A0;
}

static inline void gen_op_stw_kernel_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_stw_kernel_T0_A0;
}

static inline void gen_op_stl_kernel_T0_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_stl_kernel_T0_A0;
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

static inline void gen_op_hlt(void)
{
    *gen_opc_ptr++ = INDEX_op_hlt;
}

static inline void gen_op_debug(void)
{
    *gen_opc_ptr++ = INDEX_op_debug;
}

static inline void gen_op_raise_interrupt(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_raise_interrupt;
}

static inline void gen_op_raise_exception(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_raise_exception;
}

static inline void gen_op_into(long param1)
{
    *gen_opparam_ptr++ = param1;
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

static inline void gen_op_set_inhibit_irq(void)
{
    *gen_opc_ptr++ = INDEX_op_set_inhibit_irq;
}

static inline void gen_op_reset_inhibit_irq(void)
{
    *gen_opc_ptr++ = INDEX_op_reset_inhibit_irq;
}

static inline void gen_op_boundw(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_boundw;
}

static inline void gen_op_boundl(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_boundl;
}

static inline void gen_op_cmpxchg8b(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpxchg8b;
}

static inline void gen_op_jmp(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jmp;
}

static inline void gen_op_movl_T0_0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_0;
}

static inline void gen_op_exit_tb(void)
{
    *gen_opc_ptr++ = INDEX_op_exit_tb;
}

static inline void gen_op_jb_subb(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jb_subb;
}

static inline void gen_op_jz_subb(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jz_subb;
}

static inline void gen_op_jbe_subb(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jbe_subb;
}

static inline void gen_op_js_subb(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_js_subb;
}

static inline void gen_op_jl_subb(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jl_subb;
}

static inline void gen_op_jle_subb(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
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

static inline void gen_op_shlb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shlb_T0_T1;
}

static inline void gen_op_shrb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shrb_T0_T1;
}

static inline void gen_op_sarb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_sarb_T0_T1;
}

static inline void gen_op_rolb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rolb_T0_T1_cc;
}

static inline void gen_op_rorb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rorb_T0_T1_cc;
}

static inline void gen_op_rolb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rolb_T0_T1;
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

static inline void gen_op_shrb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrb_T0_T1_cc;
}

static inline void gen_op_sarb_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sarb_T0_T1_cc;
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

static inline void gen_op_rolb_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rolb_mem_T0_T1_cc;
}

static inline void gen_op_rorb_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rorb_mem_T0_T1_cc;
}

static inline void gen_op_rolb_mem_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rolb_mem_T0_T1;
}

static inline void gen_op_rorb_mem_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rorb_mem_T0_T1;
}

static inline void gen_op_rclb_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rclb_mem_T0_T1_cc;
}

static inline void gen_op_rcrb_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rcrb_mem_T0_T1_cc;
}

static inline void gen_op_shlb_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shlb_mem_T0_T1_cc;
}

static inline void gen_op_shrb_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrb_mem_T0_T1_cc;
}

static inline void gen_op_sarb_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sarb_mem_T0_T1_cc;
}

static inline void gen_op_adcb_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_adcb_mem_T0_T1_cc;
}

static inline void gen_op_sbbb_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sbbb_mem_T0_T1_cc;
}

static inline void gen_op_cmpxchgb_mem_T0_T1_EAX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpxchgb_mem_T0_T1_EAX_cc;
}

static inline void gen_op_movl_T0_Dshiftb(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_Dshiftb;
}

static inline void gen_op_string_jz_subb(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jz_subb;
}

static inline void gen_op_string_jnz_subb(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jnz_subb;
}

static inline void gen_op_string_jz_subb_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jz_subb_im;
}

static inline void gen_op_string_jnz_subb_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jnz_subb_im;
}

static inline void gen_op_outb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_outb_T0_T1;
}

static inline void gen_op_inb_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_inb_T0_T1;
}

static inline void gen_op_inb_DX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_inb_DX_T0;
}

static inline void gen_op_outb_DX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_outb_DX_T0;
}

static inline void gen_op_jb_subw(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jb_subw;
}

static inline void gen_op_jz_subw(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jz_subw;
}

static inline void gen_op_jbe_subw(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jbe_subw;
}

static inline void gen_op_js_subw(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_js_subw;
}

static inline void gen_op_jl_subw(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jl_subw;
}

static inline void gen_op_jle_subw(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
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

static inline void gen_op_shlw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shlw_T0_T1;
}

static inline void gen_op_shrw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shrw_T0_T1;
}

static inline void gen_op_sarw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_sarw_T0_T1;
}

static inline void gen_op_rolw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rolw_T0_T1_cc;
}

static inline void gen_op_rorw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rorw_T0_T1_cc;
}

static inline void gen_op_rolw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rolw_T0_T1;
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

static inline void gen_op_shrw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrw_T0_T1_cc;
}

static inline void gen_op_sarw_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sarw_T0_T1_cc;
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

static inline void gen_op_rolw_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rolw_mem_T0_T1_cc;
}

static inline void gen_op_rorw_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rorw_mem_T0_T1_cc;
}

static inline void gen_op_rolw_mem_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rolw_mem_T0_T1;
}

static inline void gen_op_rorw_mem_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rorw_mem_T0_T1;
}

static inline void gen_op_rclw_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rclw_mem_T0_T1_cc;
}

static inline void gen_op_rcrw_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rcrw_mem_T0_T1_cc;
}

static inline void gen_op_shlw_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shlw_mem_T0_T1_cc;
}

static inline void gen_op_shrw_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrw_mem_T0_T1_cc;
}

static inline void gen_op_sarw_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sarw_mem_T0_T1_cc;
}

static inline void gen_op_shldw_mem_T0_T1_im_cc(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_shldw_mem_T0_T1_im_cc;
}

static inline void gen_op_shldw_mem_T0_T1_ECX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shldw_mem_T0_T1_ECX_cc;
}

static inline void gen_op_shrdw_mem_T0_T1_im_cc(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_shrdw_mem_T0_T1_im_cc;
}

static inline void gen_op_shrdw_mem_T0_T1_ECX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrdw_mem_T0_T1_ECX_cc;
}

static inline void gen_op_adcw_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_adcw_mem_T0_T1_cc;
}

static inline void gen_op_sbbw_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sbbw_mem_T0_T1_cc;
}

static inline void gen_op_cmpxchgw_mem_T0_T1_EAX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpxchgw_mem_T0_T1_EAX_cc;
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

static inline void gen_op_movl_T0_Dshiftw(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_Dshiftw;
}

static inline void gen_op_string_jz_subw(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jz_subw;
}

static inline void gen_op_string_jnz_subw(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jnz_subw;
}

static inline void gen_op_string_jz_subw_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jz_subw_im;
}

static inline void gen_op_string_jnz_subw_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jnz_subw_im;
}

static inline void gen_op_jz_ecxw(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jz_ecxw;
}

static inline void gen_op_jz_ecxw_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_jz_ecxw_im;
}

static inline void gen_op_outw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_outw_T0_T1;
}

static inline void gen_op_inw_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_inw_T0_T1;
}

static inline void gen_op_inw_DX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_inw_DX_T0;
}

static inline void gen_op_outw_DX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_outw_DX_T0;
}

static inline void gen_op_jb_subl(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jb_subl;
}

static inline void gen_op_jz_subl(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jz_subl;
}

static inline void gen_op_jbe_subl(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jbe_subl;
}

static inline void gen_op_js_subl(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_js_subl;
}

static inline void gen_op_jl_subl(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jl_subl;
}

static inline void gen_op_jle_subl(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
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

static inline void gen_op_shll_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shll_T0_T1;
}

static inline void gen_op_shrl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_shrl_T0_T1;
}

static inline void gen_op_sarl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_sarl_T0_T1;
}

static inline void gen_op_roll_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_roll_T0_T1_cc;
}

static inline void gen_op_rorl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rorl_T0_T1_cc;
}

static inline void gen_op_roll_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_roll_T0_T1;
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

static inline void gen_op_shrl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrl_T0_T1_cc;
}

static inline void gen_op_sarl_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sarl_T0_T1_cc;
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

static inline void gen_op_roll_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_roll_mem_T0_T1_cc;
}

static inline void gen_op_rorl_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rorl_mem_T0_T1_cc;
}

static inline void gen_op_roll_mem_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_roll_mem_T0_T1;
}

static inline void gen_op_rorl_mem_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_rorl_mem_T0_T1;
}

static inline void gen_op_rcll_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rcll_mem_T0_T1_cc;
}

static inline void gen_op_rcrl_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_rcrl_mem_T0_T1_cc;
}

static inline void gen_op_shll_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shll_mem_T0_T1_cc;
}

static inline void gen_op_shrl_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrl_mem_T0_T1_cc;
}

static inline void gen_op_sarl_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sarl_mem_T0_T1_cc;
}

static inline void gen_op_shldl_mem_T0_T1_im_cc(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_shldl_mem_T0_T1_im_cc;
}

static inline void gen_op_shldl_mem_T0_T1_ECX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shldl_mem_T0_T1_ECX_cc;
}

static inline void gen_op_shrdl_mem_T0_T1_im_cc(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_shrdl_mem_T0_T1_im_cc;
}

static inline void gen_op_shrdl_mem_T0_T1_ECX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_shrdl_mem_T0_T1_ECX_cc;
}

static inline void gen_op_adcl_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_adcl_mem_T0_T1_cc;
}

static inline void gen_op_sbbl_mem_T0_T1_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_sbbl_mem_T0_T1_cc;
}

static inline void gen_op_cmpxchgl_mem_T0_T1_EAX_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_cmpxchgl_mem_T0_T1_EAX_cc;
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

static inline void gen_op_update_bt_cc(void)
{
    *gen_opc_ptr++ = INDEX_op_update_bt_cc;
}

static inline void gen_op_movl_T0_Dshiftl(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_Dshiftl;
}

static inline void gen_op_string_jz_subl(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jz_subl;
}

static inline void gen_op_string_jnz_subl(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jnz_subl;
}

static inline void gen_op_string_jz_subl_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jz_subl_im;
}

static inline void gen_op_string_jnz_subl_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_string_jnz_subl_im;
}

static inline void gen_op_jz_ecxl(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jz_ecxl;
}

static inline void gen_op_jz_ecxl_im(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_jz_ecxl_im;
}

static inline void gen_op_outl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_outl_T0_T1;
}

static inline void gen_op_inl_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_inl_T0_T1;
}

static inline void gen_op_inl_DX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_inl_DX_T0;
}

static inline void gen_op_outl_DX_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_outl_DX_T0;
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

static inline void gen_op_addl_ESI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_ESI_T0;
}

static inline void gen_op_addw_ESI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_addw_ESI_T0;
}

static inline void gen_op_addl_EDI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_addl_EDI_T0;
}

static inline void gen_op_addw_EDI_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_addw_EDI_T0;
}

static inline void gen_op_decl_ECX(void)
{
    *gen_opc_ptr++ = INDEX_op_decl_ECX;
}

static inline void gen_op_decw_ECX(void)
{
    *gen_opc_ptr++ = INDEX_op_decw_ECX;
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

static inline void gen_op_rdmsr(void)
{
    *gen_opc_ptr++ = INDEX_op_rdmsr;
}

static inline void gen_op_wrmsr(void)
{
    *gen_opc_ptr++ = INDEX_op_wrmsr;
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

static inline void gen_op_movl_seg_T0(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_movl_seg_T0;
}

static inline void gen_op_movl_seg_T0_vm(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_seg_T0_vm;
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

static inline void gen_op_lsl(void)
{
    *gen_opc_ptr++ = INDEX_op_lsl;
}

static inline void gen_op_lar(void)
{
    *gen_opc_ptr++ = INDEX_op_lar;
}

static inline void gen_op_ljmp_protected_T0_T1(void)
{
    *gen_opc_ptr++ = INDEX_op_ljmp_protected_T0_T1;
}

static inline void gen_op_lcall_real_T0_T1(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_lcall_real_T0_T1;
}

static inline void gen_op_lcall_protected_T0_T1(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_lcall_protected_T0_T1;
}

static inline void gen_op_iret_real(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_iret_real;
}

static inline void gen_op_iret_protected(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_iret_protected;
}

static inline void gen_op_lret_protected(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_lret_protected;
}

static inline void gen_op_lldt_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_lldt_T0;
}

static inline void gen_op_ltr_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_ltr_T0;
}

static inline void gen_op_movl_crN_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_crN_T0;
}

static inline void gen_op_movl_drN_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_drN_T0;
}

static inline void gen_op_lmsw_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_lmsw_T0;
}

static inline void gen_op_invlpg_A0(void)
{
    *gen_opc_ptr++ = INDEX_op_invlpg_A0;
}

static inline void gen_op_movl_T0_env(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_T0_env;
}

static inline void gen_op_movl_env_T0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_env_T0;
}

static inline void gen_op_movl_env_T1(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_movl_env_T1;
}

static inline void gen_op_clts(void)
{
    *gen_opc_ptr++ = INDEX_op_clts;
}

static inline void gen_op_jcc(long param1, long param2, long param3)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opparam_ptr++ = param3;
    *gen_opc_ptr++ = INDEX_op_jcc;
}

static inline void gen_op_jcc_im(long param1, long param2)
{
    *gen_opparam_ptr++ = param1;
    *gen_opparam_ptr++ = param2;
    *gen_opc_ptr++ = INDEX_op_jcc_im;
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

static inline void gen_op_movl_eflags_T0_cpl0(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_eflags_T0_cpl0;
}

static inline void gen_op_movw_eflags_T0_cpl0(void)
{
    *gen_opc_ptr++ = INDEX_op_movw_eflags_T0_cpl0;
}

static inline void gen_op_movb_eflags_T0(void)
{
    *gen_opc_ptr++ = INDEX_op_movb_eflags_T0;
}

static inline void gen_op_movl_T0_eflags(void)
{
    *gen_opc_ptr++ = INDEX_op_movl_T0_eflags;
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

static inline void gen_op_fcomi_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fcomi_ST0_FT0;
}

static inline void gen_op_fucomi_ST0_FT0(void)
{
    *gen_opc_ptr++ = INDEX_op_fucomi_ST0_FT0;
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

static inline void gen_op_fnstenv_A0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fnstenv_A0;
}

static inline void gen_op_fldenv_A0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fldenv_A0;
}

static inline void gen_op_fnsave_A0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_fnsave_A0;
}

static inline void gen_op_frstor_A0(long param1)
{
    *gen_opparam_ptr++ = param1;
    *gen_opc_ptr++ = INDEX_op_frstor_A0;
}

static inline void gen_op_lock(void)
{
    *gen_opc_ptr++ = INDEX_op_lock;
}

static inline void gen_op_unlock(void)
{
    *gen_opc_ptr++ = INDEX_op_unlock;
}


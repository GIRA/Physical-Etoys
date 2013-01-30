/* Generated automatically by the program `genflags'
   from the machine description file `md'.  */

#ifndef GCC_INSN_FLAGS_H
#define GCC_INSN_FLAGS_H

#define HAVE_movhi_sp_r_irq_off 1
#define HAVE_movhi_sp_r_irq_on 1
#define HAVE_addqi3 1
#define HAVE_addsi3 1
#define HAVE_subqi3 1
#define HAVE_subhi3 1
#define HAVE_subsi3 1
#define HAVE_mulqihi3 (AVR_HAVE_MUL)
#define HAVE_umulqihi3 (AVR_HAVE_MUL)
#define HAVE_divmodqi4 1
#define HAVE_udivmodqi4 1
#define HAVE_divmodhi4 1
#define HAVE_udivmodhi4 1
#define HAVE_divmodsi4 1
#define HAVE_udivmodsi4 1
#define HAVE_andqi3 1
#define HAVE_andhi3 1
#define HAVE_andsi3 1
#define HAVE_iorqi3 1
#define HAVE_iorhi3 1
#define HAVE_iorsi3 1
#define HAVE_xorqi3 1
#define HAVE_xorhi3 1
#define HAVE_xorsi3 1
#define HAVE_ashlhi3 1
#define HAVE_ashlsi3 1
#define HAVE_ashrqi3 1
#define HAVE_ashrhi3 1
#define HAVE_ashrsi3 1
#define HAVE_lshrhi3 1
#define HAVE_lshrsi3 1
#define HAVE_absqi2 1
#define HAVE_abssf2 1
#define HAVE_negqi2 1
#define HAVE_neghi2 1
#define HAVE_negsi2 1
#define HAVE_negsf2 1
#define HAVE_one_cmplqi2 1
#define HAVE_one_cmplhi2 1
#define HAVE_one_cmplsi2 1
#define HAVE_extendqihi2 1
#define HAVE_extendqisi2 1
#define HAVE_extendhisi2 1
#define HAVE_zero_extendqihi2 1
#define HAVE_zero_extendqisi2 1
#define HAVE_zero_extendhisi2 1
#define HAVE_zero_extendqidi2 1
#define HAVE_zero_extendhidi2 1
#define HAVE_zero_extendsidi2 1
#define HAVE_branch 1
#define HAVE_difficult_branch 1
#define HAVE_rvbranch 1
#define HAVE_difficult_rvbranch 1
#define HAVE_jump 1
#define HAVE_call_insn ((register_operand (operands[0], HImode) || CONSTANT_P (operands[0])))
#define HAVE_call_value_insn ((register_operand (operands[0], VOIDmode) || CONSTANT_P (operands[0])))
#define HAVE_nop 1
#define HAVE_sez 1
#define HAVE_popqi 1
#define HAVE_pophi 1
#define HAVE_enable_interrupt 1
#define HAVE_disable_interrupt 1
#define HAVE_call_prologue_saves 1
#define HAVE_epilogue_restores 1
#define HAVE_return (reload_completed && avr_simple_epilogue ())
#define HAVE_return_from_epilogue ((reload_completed  \
    && cfun->machine  \
    && !(cfun->machine->is_interrupt || cfun->machine->is_signal) \
    && !cfun->machine->is_naked))
#define HAVE_return_from_interrupt_epilogue ((reload_completed  \
    && cfun->machine  \
    && (cfun->machine->is_interrupt || cfun->machine->is_signal) \
    && !cfun->machine->is_naked))
#define HAVE_return_from_naked_epilogue ((reload_completed  \
    && cfun->machine  \
    && cfun->machine->is_naked))
#define HAVE_nonlocal_goto_receiver 1
#define HAVE_nonlocal_goto 1
#define HAVE_movqi 1
#define HAVE_movhi 1
#define HAVE_movsi 1
#define HAVE_movsf 1
#define HAVE_movmemhi 1
#define HAVE_setmemhi 1
#define HAVE_strlenhi 1
#define HAVE_addhi3 1
#define HAVE_mulqi3 1
#define HAVE_mulqi3_call 1
#define HAVE_mulhi3 1
#define HAVE_mulhi3_call 1
#define HAVE_mulsi3 (AVR_HAVE_MUL)
#define HAVE_rotlqi3 1
#define HAVE_rotlhi3 1
#define HAVE_rotlsi3 1
#define HAVE_rotldi3 1
#define HAVE_ashlqi3 1
#define HAVE_lshrqi3 1
#define HAVE_cbranchsi4 1
#define HAVE_cbranchhi4 1
#define HAVE_cbranchqi4 1
#define HAVE_call 1
#define HAVE_call_value 1
#define HAVE_indirect_jump 1
#define HAVE_casesi 1
#define HAVE_prologue 1
#define HAVE_epilogue 1
extern rtx        gen_movhi_sp_r_irq_off             (rtx, rtx);
extern rtx        gen_movhi_sp_r_irq_on              (rtx, rtx);
extern rtx        gen_addqi3                         (rtx, rtx, rtx);
extern rtx        gen_addsi3                         (rtx, rtx, rtx);
extern rtx        gen_subqi3                         (rtx, rtx, rtx);
extern rtx        gen_subhi3                         (rtx, rtx, rtx);
extern rtx        gen_subsi3                         (rtx, rtx, rtx);
extern rtx        gen_mulqihi3                       (rtx, rtx, rtx);
extern rtx        gen_umulqihi3                      (rtx, rtx, rtx);
extern rtx        gen_divmodqi4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_udivmodqi4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_divmodhi4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_udivmodhi4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_divmodsi4                      (rtx, rtx, rtx, rtx);
extern rtx        gen_udivmodsi4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_andqi3                         (rtx, rtx, rtx);
extern rtx        gen_andhi3                         (rtx, rtx, rtx);
extern rtx        gen_andsi3                         (rtx, rtx, rtx);
extern rtx        gen_iorqi3                         (rtx, rtx, rtx);
extern rtx        gen_iorhi3                         (rtx, rtx, rtx);
extern rtx        gen_iorsi3                         (rtx, rtx, rtx);
extern rtx        gen_xorqi3                         (rtx, rtx, rtx);
extern rtx        gen_xorhi3                         (rtx, rtx, rtx);
extern rtx        gen_xorsi3                         (rtx, rtx, rtx);
extern rtx        gen_ashlhi3                        (rtx, rtx, rtx);
extern rtx        gen_ashlsi3                        (rtx, rtx, rtx);
extern rtx        gen_ashrqi3                        (rtx, rtx, rtx);
extern rtx        gen_ashrhi3                        (rtx, rtx, rtx);
extern rtx        gen_ashrsi3                        (rtx, rtx, rtx);
extern rtx        gen_lshrhi3                        (rtx, rtx, rtx);
extern rtx        gen_lshrsi3                        (rtx, rtx, rtx);
extern rtx        gen_absqi2                         (rtx, rtx);
extern rtx        gen_abssf2                         (rtx, rtx);
extern rtx        gen_negqi2                         (rtx, rtx);
extern rtx        gen_neghi2                         (rtx, rtx);
extern rtx        gen_negsi2                         (rtx, rtx);
extern rtx        gen_negsf2                         (rtx, rtx);
extern rtx        gen_one_cmplqi2                    (rtx, rtx);
extern rtx        gen_one_cmplhi2                    (rtx, rtx);
extern rtx        gen_one_cmplsi2                    (rtx, rtx);
extern rtx        gen_extendqihi2                    (rtx, rtx);
extern rtx        gen_extendqisi2                    (rtx, rtx);
extern rtx        gen_extendhisi2                    (rtx, rtx);
extern rtx        gen_zero_extendqihi2               (rtx, rtx);
extern rtx        gen_zero_extendqisi2               (rtx, rtx);
extern rtx        gen_zero_extendhisi2               (rtx, rtx);
extern rtx        gen_zero_extendqidi2               (rtx, rtx);
extern rtx        gen_zero_extendhidi2               (rtx, rtx);
extern rtx        gen_zero_extendsidi2               (rtx, rtx);
extern rtx        gen_branch                         (rtx, rtx);
extern rtx        gen_difficult_branch               (rtx, rtx);
extern rtx        gen_rvbranch                       (rtx, rtx);
extern rtx        gen_difficult_rvbranch             (rtx, rtx);
extern rtx        gen_jump                           (rtx);
extern rtx        gen_call_insn                      (rtx, rtx);
extern rtx        gen_call_value_insn                (rtx, rtx, rtx);
extern rtx        gen_nop                            (void);
extern rtx        gen_sez                            (void);
extern rtx        gen_popqi                          (rtx);
extern rtx        gen_pophi                          (rtx);
extern rtx        gen_enable_interrupt               (void);
extern rtx        gen_disable_interrupt              (void);
extern rtx        gen_call_prologue_saves            (rtx, rtx);
extern rtx        gen_epilogue_restores              (rtx);
extern rtx        gen_return                         (void);
extern rtx        gen_return_from_epilogue           (void);
extern rtx        gen_return_from_interrupt_epilogue (void);
extern rtx        gen_return_from_naked_epilogue     (void);
extern rtx        gen_nonlocal_goto_receiver         (void);
extern rtx        gen_nonlocal_goto                  (rtx, rtx, rtx, rtx);
extern rtx        gen_movqi                          (rtx, rtx);
extern rtx        gen_movhi                          (rtx, rtx);
extern rtx        gen_movsi                          (rtx, rtx);
extern rtx        gen_movsf                          (rtx, rtx);
extern rtx        gen_movmemhi                       (rtx, rtx, rtx, rtx);
extern rtx        gen_setmemhi                       (rtx, rtx, rtx, rtx);
extern rtx        gen_strlenhi                       (rtx, rtx, rtx, rtx);
extern rtx        gen_addhi3                         (rtx, rtx, rtx);
extern rtx        gen_mulqi3                         (rtx, rtx, rtx);
extern rtx        gen_mulqi3_call                    (rtx, rtx, rtx);
extern rtx        gen_mulhi3                         (rtx, rtx, rtx);
extern rtx        gen_mulhi3_call                    (rtx, rtx, rtx);
extern rtx        gen_mulsi3                         (rtx, rtx, rtx);
extern rtx        gen_rotlqi3                        (rtx, rtx, rtx);
extern rtx        gen_rotlhi3                        (rtx, rtx, rtx, rtx);
extern rtx        gen_rotlsi3                        (rtx, rtx, rtx, rtx);
extern rtx        gen_rotldi3                        (rtx, rtx, rtx, rtx);
extern rtx        gen_ashlqi3                        (rtx, rtx, rtx);
extern rtx        gen_lshrqi3                        (rtx, rtx, rtx);
extern rtx        gen_cbranchsi4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchhi4                     (rtx, rtx, rtx, rtx);
extern rtx        gen_cbranchqi4                     (rtx, rtx, rtx, rtx);
#define GEN_CALL(A, B, C, D) gen_call ((A), (B))
extern rtx        gen_call                           (rtx, rtx);
#define GEN_CALL_VALUE(A, B, C, D, E) gen_call_value ((A), (B), (C))
extern rtx        gen_call_value                     (rtx, rtx, rtx);
extern rtx        gen_indirect_jump                  (rtx);
extern rtx        gen_casesi                         (rtx, rtx, rtx, rtx, rtx);
extern rtx        gen_prologue                       (void);
extern rtx        gen_epilogue                       (void);

#endif /* GCC_INSN_FLAGS_H */

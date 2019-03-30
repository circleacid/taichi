std::tuple<Matrix, Matrix, Matrix> sifakis_svd(const Matrix &a) {
  Local(Sfour_gamma_squared) = 0.0f;
  Local(Ssine_pi_over_eight) = 0.0f;
  Local(Scosine_pi_over_eight) = 0.0f;
  Local(Sone_half) = 0.0f;
  Local(Sone) = 0.0f;
  Local(Stiny_number) = 0.0f;
  Local(Ssmall_number) = 0.0f;
  Local(Sa11) = 0.0f;
  Local(Sa21) = 0.0f;
  Local(Sa31) = 0.0f;
  Local(Sa12) = 0.0f;
  Local(Sa22) = 0.0f;
  Local(Sa32) = 0.0f;
  Local(Sa13) = 0.0f;
  Local(Sa23) = 0.0f;
  Local(Sa33) = 0.0f;
  Local(Sv11) = 0.0f;
  Local(Sv21) = 0.0f;
  Local(Sv31) = 0.0f;
  Local(Sv12) = 0.0f;
  Local(Sv22) = 0.0f;
  Local(Sv32) = 0.0f;
  Local(Sv13) = 0.0f;
  Local(Sv23) = 0.0f;
  Local(Sv33) = 0.0f;
  Local(Su11) = 0.0f;
  Local(Su21) = 0.0f;
  Local(Su31) = 0.0f;
  Local(Su12) = 0.0f;
  Local(Su22) = 0.0f;
  Local(Su32) = 0.0f;
  Local(Su13) = 0.0f;
  Local(Su23) = 0.0f;
  Local(Su33) = 0.0f;
  Local(Sc) = 0.0f;
  Local(Ss) = 0.0f;
  Local(Sch) = 0.0f;
  Local(Ssh) = 0.0f;
  Local(Stmp1) = 0.0f;
  Local(Stmp2) = 0.0f;
  Local(Stmp3) = 0.0f;
  Local(Stmp4) = 0.0f;
  Local(Stmp5) = 0.0f;
  Local(Sqvs) = 0.0f;
  Local(Sqvvx) = 0.0f;
  Local(Sqvvy) = 0.0f;
  Local(Sqvvz) = 0.0f;
  Local(Ss11) = 0.0f;
  Local(Ss21) = 0.0f;
  Local(Ss31) = 0.0f;
  Local(Ss22) = 0.0f;
  Local(Ss32) = 0.0f;
  Local(Ss33) = 0.0f;

  constexpr float Four_Gamma_Squared = 5.82842712474619f;
  constexpr float Sine_Pi_Over_Eight = 0.3826834323650897f;
  constexpr float Cosine_Pi_Over_Eight = 0.9238795325112867f;

  Sfour_gamma_squared = Expr(Four_Gamma_Squared);
  Ssine_pi_over_eight = Expr(Sine_Pi_Over_Eight);
  Scosine_pi_over_eight = Expr(Cosine_Pi_Over_Eight);
  Sone_half = 0.5f;
  Sone = 1.0f;
  Stiny_number = 1.e-20f;
  Ssmall_number = 1.e-12f;
  Sa11 = a(0, 0);
  Print(Sa11);
  Sa21 = a(1, 0);
  Print(Sa21);
  Sa31 = a(2, 0);
  Sa12 = a(0, 1);
  Sa22 = a(1, 1);
  Sa32 = a(2, 1);
  Sa13 = a(0, 2);
  Sa23 = a(1, 2);
  Sa33 = a(2, 2);
  Sqvs = 1.0f;
  Sqvvx = 0.0f;
  Sqvvy = 0.0f;
  Sqvvz = 0.0f;
  Ss11 = Sa11 * Sa11;
  Stmp1 = Sa21 * Sa21;
  Ss11 = Stmp1 + Ss11;
  Stmp1 = Sa31 * Sa31;
  Ss11 = Stmp1 + Ss11;
  Ss21 = Sa12 * Sa11;
  Stmp1 = Sa22 * Sa21;
  Ss21 = Stmp1 + Ss21;
  Stmp1 = Sa32 * Sa31;
  Ss21 = Stmp1 + Ss21;
  Ss31 = Sa13 * Sa11;
  Stmp1 = Sa23 * Sa21;
  Ss31 = Stmp1 + Ss31;
  Stmp1 = Sa33 * Sa31;
  Ss31 = Stmp1 + Ss31;
  Ss22 = Sa12 * Sa12;
  Stmp1 = Sa22 * Sa22;
  Ss22 = Stmp1 + Ss22;
  Stmp1 = Sa32 * Sa32;
  Ss22 = Stmp1 + Ss22;
  Ss32 = Sa13 * Sa12;
  Stmp1 = Sa23 * Sa22;
  Ss32 = Stmp1 + Ss32;
  Stmp1 = Sa33 * Sa32;
  Ss32 = Stmp1 + Ss32;
  Ss33 = Sa13 * Sa13;
  Stmp1 = Sa23 * Sa23;
  Ss33 = Stmp1 + Ss33;
  Stmp1 = Sa33 * Sa33;
  Ss33 = Stmp1 + Ss33;
  Declare(sweep);
  For(sweep, 0, 5, [&] {
    Ssh = Ss21 * Sone_half;
    Stmp5 = Ss11 - Ss22;
    Stmp2 = Ssh * Ssh;
    Stmp1 = bit_cast<float32>(
        select(Stmp2 >= Stiny_number, Expr(int(0xffffffff)), Expr(0)));
    Ssh = float32_bitwise_and(Stmp1, Ssh);
    Sch = float32_bitwise_and(Stmp1, Stmp5);
    Stmp2 = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp1)), Sone);
    Sch = float32_bitwise_or(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Stmp3 = Stmp1 + Stmp2;
    Stmp4 = rsqrt(Stmp3);
    Ssh = Stmp4 * Ssh;
    Sch = Stmp4 * Sch;
    Stmp1 = Sfour_gamma_squared * Stmp1;
    Stmp1 = bit_cast<float32>(
        select(Stmp2 <= Stmp1, Expr(int(0xffffffff)), Expr(0)));
    Stmp2 = float32_bitwise_and(Ssine_pi_over_eight, Stmp1);
    Ssh = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp1)), Ssh);
    Ssh = float32_bitwise_or(Ssh, Stmp2);
    Stmp2 = float32_bitwise_and(Scosine_pi_over_eight, Stmp1);
    Sch = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp1)), Sch);
    Sch = float32_bitwise_or(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Sc = Stmp2 - Stmp1;
    Ss = Sch * Ssh;
    Ss = Ss + Ss;
    Stmp3 = Stmp1 + Stmp2;
    Ss33 = Ss33 * Stmp3;
    Ss31 = Ss31 * Stmp3;
    Ss32 = Ss32 * Stmp3;
    Ss33 = Ss33 * Stmp3;
    Stmp1 = Ss * Ss31;
    Stmp2 = Ss * Ss32;
    Ss31 = Sc * Ss31;
    Ss32 = Sc * Ss32;
    Ss31 = Stmp2 + Ss31;
    Ss32 = Ss32 - Stmp1;
    Stmp2 = Ss * Ss;
    Stmp1 = Ss22 * Stmp2;
    Stmp3 = Ss11 * Stmp2;
    Stmp4 = Sc * Sc;
    Ss11 = Ss11 * Stmp4;
    Ss22 = Ss22 * Stmp4;
    Ss11 = Ss11 + Stmp1;
    Ss22 = Ss22 + Stmp3;
    Stmp4 = Stmp4 - Stmp2;
    Stmp2 = Ss21 + Ss21;
    Ss21 = Ss21 * Stmp4;
    Stmp4 = Sc * Ss;
    Stmp2 = Stmp2 * Stmp4;
    Stmp5 = Stmp5 * Stmp4;
    Ss11 = Ss11 + Stmp2;
    Ss21 = Ss21 - Stmp5;
    Ss22 = Ss22 - Stmp2;
    Stmp1 = Ssh * Sqvvx;
    Stmp2 = Ssh * Sqvvy;
    Stmp3 = Ssh * Sqvvz;
    Ssh = Ssh * Sqvs;
    Sqvs = Sch * Sqvs;
    Sqvvx = Sch * Sqvvx;
    Sqvvy = Sch * Sqvvy;
    Sqvvz = Sch * Sqvvz;
    Sqvvz = Sqvvz + Ssh;
    Sqvs = Sqvs - Stmp3;
    Sqvvx = Sqvvx + Stmp2;
    Sqvvy = Sqvvy - Stmp1;
    Ssh = Ss32 * Sone_half;
    Stmp5 = Ss22 - Ss33;
    Stmp2 = Ssh * Ssh;
    Stmp1 = bit_cast<float32>(
        select(Stmp2 >= Stiny_number, Expr(int(0xffffffff)), Expr(0)));
    Ssh = float32_bitwise_and(Stmp1, Ssh);
    Sch = float32_bitwise_and(Stmp1, Stmp5);
    Stmp2 = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp1)), Sone);
    Sch = float32_bitwise_or(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Stmp3 = Stmp1 + Stmp2;
    Stmp4 = rsqrt(Stmp3);
    Ssh = Stmp4 * Ssh;
    Sch = Stmp4 * Sch;
    Stmp1 = Sfour_gamma_squared * Stmp1;
    Stmp1 = bit_cast<float32>(
        select(Stmp2 <= Stmp1, Expr(int(0xffffffff)), Expr(0)));
    Stmp2 = float32_bitwise_and(Ssine_pi_over_eight, Stmp1);
    Ssh = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp1)), Ssh);
    Ssh = float32_bitwise_or(Ssh, Stmp2);
    Stmp2 = float32_bitwise_and(Scosine_pi_over_eight, Stmp1);
    Sch = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp1)), Sch);
    Sch = float32_bitwise_or(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Sc = Stmp2 - Stmp1;
    Ss = Sch * Ssh;
    Ss = Ss + Ss;
    Stmp3 = Stmp1 + Stmp2;
    Ss11 = Ss11 * Stmp3;
    Ss21 = Ss21 * Stmp3;
    Ss31 = Ss31 * Stmp3;
    Ss11 = Ss11 * Stmp3;
    Stmp1 = Ss * Ss21;
    Stmp2 = Ss * Ss31;
    Ss21 = Sc * Ss21;
    Ss31 = Sc * Ss31;
    Ss21 = Stmp2 + Ss21;
    Ss31 = Ss31 - Stmp1;
    Stmp2 = Ss * Ss;
    Stmp1 = Ss33 * Stmp2;
    Stmp3 = Ss22 * Stmp2;
    Stmp4 = Sc * Sc;
    Ss22 = Ss22 * Stmp4;
    Ss33 = Ss33 * Stmp4;
    Ss22 = Ss22 + Stmp1;
    Ss33 = Ss33 + Stmp3;
    Stmp4 = Stmp4 - Stmp2;
    Stmp2 = Ss32 + Ss32;
    Ss32 = Ss32 * Stmp4;
    Stmp4 = Sc * Ss;
    Stmp2 = Stmp2 * Stmp4;
    Stmp5 = Stmp5 * Stmp4;
    Ss22 = Ss22 + Stmp2;
    Ss32 = Ss32 - Stmp5;
    Ss33 = Ss33 - Stmp2;
    Stmp1 = Ssh * Sqvvx;
    Stmp2 = Ssh * Sqvvy;
    Stmp3 = Ssh * Sqvvz;
    Ssh = Ssh * Sqvs;
    Sqvs = Sch * Sqvs;
    Sqvvx = Sch * Sqvvx;
    Sqvvy = Sch * Sqvvy;
    Sqvvz = Sch * Sqvvz;
    Sqvvx = Sqvvx + Ssh;
    Sqvs = Sqvs - Stmp1;
    Sqvvy = Sqvvy + Stmp3;
    Sqvvz = Sqvvz - Stmp2;
    Ssh = Ss31 * Sone_half;
    Stmp5 = Ss33 - Ss11;
    Stmp2 = Ssh * Ssh;
    Stmp1 = bit_cast<float32>(
        select(Stmp2 >= Stiny_number, Expr(int(0xffffffff)), Expr(0)));
    Ssh = float32_bitwise_and(Stmp1, Ssh);
    Sch = float32_bitwise_and(Stmp1, Stmp5);
    Stmp2 = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp1)), Sone);
    Sch = float32_bitwise_or(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Stmp3 = Stmp1 + Stmp2;
    Stmp4 = rsqrt(Stmp3);
    Ssh = Stmp4 * Ssh;
    Sch = Stmp4 * Sch;
    Stmp1 = Sfour_gamma_squared * Stmp1;
    Stmp1 = bit_cast<float32>(
        select(Stmp2 <= Stmp1, Expr(int(0xffffffff)), Expr(0)));
    Stmp2 = float32_bitwise_and(Ssine_pi_over_eight, Stmp1);
    Ssh = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp1)), Ssh);
    Ssh = float32_bitwise_or(Ssh, Stmp2);
    Stmp2 = float32_bitwise_and(Scosine_pi_over_eight, Stmp1);
    Sch = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp1)), Sch);
    Sch = float32_bitwise_or(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Sc = Stmp2 - Stmp1;
    Ss = Sch * Ssh;
    Ss = Ss + Ss;
    Stmp3 = Stmp1 + Stmp2;
    Ss22 = Ss22 * Stmp3;
    Ss32 = Ss32 * Stmp3;
    Ss21 = Ss21 * Stmp3;
    Ss22 = Ss22 * Stmp3;
    Stmp1 = Ss * Ss32;
    Stmp2 = Ss * Ss21;
    Ss32 = Sc * Ss32;
    Ss21 = Sc * Ss21;
    Ss32 = Stmp2 + Ss32;
    Ss21 = Ss21 - Stmp1;
    Stmp2 = Ss * Ss;
    Stmp1 = Ss11 * Stmp2;
    Stmp3 = Ss33 * Stmp2;
    Stmp4 = Sc * Sc;
    Ss33 = Ss33 * Stmp4;
    Ss11 = Ss11 * Stmp4;
    Ss33 = Ss33 + Stmp1;
    Ss11 = Ss11 + Stmp3;
    Stmp4 = Stmp4 - Stmp2;
    Stmp2 = Ss31 + Ss31;
    Ss31 = Ss31 * Stmp4;
    Stmp4 = Sc * Ss;
    Stmp2 = Stmp2 * Stmp4;
    Stmp5 = Stmp5 * Stmp4;
    Ss33 = Ss33 + Stmp2;
    Ss31 = Ss31 - Stmp5;
    Ss11 = Ss11 - Stmp2;
    Stmp1 = Ssh * Sqvvx;
    Stmp2 = Ssh * Sqvvy;
    Stmp3 = Ssh * Sqvvz;
    Ssh = Ssh * Sqvs;
    Sqvs = Sch * Sqvs;
    Sqvvx = Sch * Sqvvx;
    Sqvvy = Sch * Sqvvy;
    Sqvvz = Sch * Sqvvz;
    Sqvvy = Sqvvy + Ssh;
    Sqvs = Sqvs - Stmp2;
    Sqvvz = Sqvvz + Stmp1;
    Sqvvx = Sqvvx - Stmp3;
  });
  Stmp2 = Sqvs * Sqvs;
  Stmp1 = Sqvvx * Sqvvx;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = Sqvvy * Sqvvy;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = Sqvvz * Sqvvz;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Sqvs = Sqvs * Stmp1;
  Sqvvx = Sqvvx * Stmp1;
  Sqvvy = Sqvvy * Stmp1;
  Sqvvz = Sqvvz * Stmp1;
  Stmp1 = Sqvvx * Sqvvx;
  Stmp2 = Sqvvy * Sqvvy;
  Stmp3 = Sqvvz * Sqvvz;
  Sv11 = Sqvs * Sqvs;
  Sv22 = Sv11 - Stmp1;
  Sv33 = Sv22 - Stmp2;
  Sv33 = Sv33 + Stmp3;
  Sv22 = Sv22 + Stmp2;
  Sv22 = Sv22 - Stmp3;
  Sv11 = Sv11 + Stmp1;
  Sv11 = Sv11 - Stmp2;
  Sv11 = Sv11 - Stmp3;
  Stmp1 = Sqvvx + Sqvvx;
  Stmp2 = Sqvvy + Sqvvy;
  Stmp3 = Sqvvz + Sqvvz;
  Sv32 = Sqvs * Stmp1;
  Sv13 = Sqvs * Stmp2;
  Sv21 = Sqvs * Stmp3;
  Stmp1 = Sqvvy * Stmp1;
  Stmp2 = Sqvvz * Stmp2;
  Stmp3 = Sqvvx * Stmp3;
  Sv12 = Stmp1 - Sv21;
  Sv23 = Stmp2 - Sv32;
  Sv31 = Stmp3 - Sv13;
  Sv21 = Stmp1 + Sv21;
  Sv32 = Stmp2 + Sv32;
  Sv13 = Stmp3 + Sv13;
  Stmp2 = Sa12;
  Stmp3 = Sa13;
  Sa12 = Sv12 * Sa11;
  Sa13 = Sv13 * Sa11;
  Sa11 = Sv11 * Sa11;
  Stmp1 = Sv21 * Stmp2;
  Sa11 = Sa11 + Stmp1;
  Stmp1 = Sv31 * Stmp3;
  Sa11 = Sa11 + Stmp1;
  Stmp1 = Sv22 * Stmp2;
  Sa12 = Sa12 + Stmp1;
  Stmp1 = Sv32 * Stmp3;
  Sa12 = Sa12 + Stmp1;
  Stmp1 = Sv23 * Stmp2;
  Sa13 = Sa13 + Stmp1;
  Stmp1 = Sv33 * Stmp3;
  Sa13 = Sa13 + Stmp1;
  Stmp2 = Sa22;
  Stmp3 = Sa23;
  Sa22 = Sv12 * Sa21;
  Sa23 = Sv13 * Sa21;
  Sa21 = Sv11 * Sa21;
  Stmp1 = Sv21 * Stmp2;
  Sa21 = Sa21 + Stmp1;
  Stmp1 = Sv31 * Stmp3;
  Sa21 = Sa21 + Stmp1;
  Stmp1 = Sv22 * Stmp2;
  Sa22 = Sa22 + Stmp1;
  Stmp1 = Sv32 * Stmp3;
  Sa22 = Sa22 + Stmp1;
  Stmp1 = Sv23 * Stmp2;
  Sa23 = Sa23 + Stmp1;
  Stmp1 = Sv33 * Stmp3;
  Sa23 = Sa23 + Stmp1;
  Stmp2 = Sa32;
  Stmp3 = Sa33;
  Sa32 = Sv12 * Sa31;
  Sa33 = Sv13 * Sa31;
  Sa31 = Sv11 * Sa31;
  Stmp1 = Sv21 * Stmp2;
  Sa31 = Sa31 + Stmp1;
  Stmp1 = Sv31 * Stmp3;
  Sa31 = Sa31 + Stmp1;
  Stmp1 = Sv22 * Stmp2;
  Sa32 = Sa32 + Stmp1;
  Stmp1 = Sv32 * Stmp3;
  Sa32 = Sa32 + Stmp1;
  Stmp1 = Sv23 * Stmp2;
  Sa33 = Sa33 + Stmp1;
  Stmp1 = Sv33 * Stmp3;
  Sa33 = Sa33 + Stmp1;
  Stmp1 = Sa11 * Sa11;
  Stmp4 = Sa21 * Sa21;
  Stmp1 = Stmp1 + Stmp4;
  Stmp4 = Sa31 * Sa31;
  Stmp1 = Stmp1 + Stmp4;
  Stmp2 = Sa12 * Sa12;
  Stmp4 = Sa22 * Sa22;
  Stmp2 = Stmp2 + Stmp4;
  Stmp4 = Sa32 * Sa32;
  Stmp2 = Stmp2 + Stmp4;
  Stmp3 = Sa13 * Sa13;
  Stmp4 = Sa23 * Sa23;
  Stmp3 = Stmp3 + Stmp4;
  Stmp4 = Sa33 * Sa33;
  Stmp3 = Stmp3 + Stmp4;
  Stmp4 =
      bit_cast<float32>(select(Stmp1 < Stmp2, Expr(int(0xffffffff)), Expr(0)));
  Stmp5 = float32_bitwise_xor(Sa11, Sa12);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sa11 = float32_bitwise_xor(Sa11, Stmp5);
  Sa12 = float32_bitwise_xor(Sa12, Stmp5);
  Stmp5 = float32_bitwise_xor(Sa21, Sa22);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sa21 = float32_bitwise_xor(Sa21, Stmp5);
  Sa22 = float32_bitwise_xor(Sa22, Stmp5);
  Stmp5 = float32_bitwise_xor(Sa31, Sa32);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sa31 = float32_bitwise_xor(Sa31, Stmp5);
  Sa32 = float32_bitwise_xor(Sa32, Stmp5);
  Stmp5 = float32_bitwise_xor(Sv11, Sv12);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sv11 = float32_bitwise_xor(Sv11, Stmp5);
  Sv12 = float32_bitwise_xor(Sv12, Stmp5);
  Stmp5 = float32_bitwise_xor(Sv21, Sv22);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sv21 = float32_bitwise_xor(Sv21, Stmp5);
  Sv22 = float32_bitwise_xor(Sv22, Stmp5);
  Stmp5 = float32_bitwise_xor(Sv31, Sv32);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sv31 = float32_bitwise_xor(Sv31, Stmp5);
  Sv32 = float32_bitwise_xor(Sv32, Stmp5);
  Stmp5 = float32_bitwise_xor(Stmp1, Stmp2);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Stmp1 = float32_bitwise_xor(Stmp1, Stmp5);
  Stmp2 = float32_bitwise_xor(Stmp2, Stmp5);
  Stmp5 = -2.0f;
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Stmp4 = 1.0f;
  Stmp4 = Stmp4 + Stmp5;
  Sa12 = Sa12 * Stmp4;
  Sa22 = Sa22 * Stmp4;
  Sa32 = Sa32 * Stmp4;
  Sv12 = Sv12 * Stmp4;
  Sv22 = Sv22 * Stmp4;
  Sv32 = Sv32 * Stmp4;
  Stmp4 =
      bit_cast<float32>(select(Stmp1 < Stmp3, Expr(int(0xffffffff)), Expr(0)));
  Stmp5 = float32_bitwise_xor(Sa11, Sa13);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sa11 = float32_bitwise_xor(Sa11, Stmp5);
  Sa13 = float32_bitwise_xor(Sa13, Stmp5);
  Stmp5 = float32_bitwise_xor(Sa21, Sa23);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sa21 = float32_bitwise_xor(Sa21, Stmp5);
  Sa23 = float32_bitwise_xor(Sa23, Stmp5);
  Stmp5 = float32_bitwise_xor(Sa31, Sa33);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sa31 = float32_bitwise_xor(Sa31, Stmp5);
  Sa33 = float32_bitwise_xor(Sa33, Stmp5);
  Stmp5 = float32_bitwise_xor(Sv11, Sv13);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sv11 = float32_bitwise_xor(Sv11, Stmp5);
  Sv13 = float32_bitwise_xor(Sv13, Stmp5);
  Stmp5 = float32_bitwise_xor(Sv21, Sv23);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sv21 = float32_bitwise_xor(Sv21, Stmp5);
  Sv23 = float32_bitwise_xor(Sv23, Stmp5);
  Stmp5 = float32_bitwise_xor(Sv31, Sv33);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sv31 = float32_bitwise_xor(Sv31, Stmp5);
  Sv33 = float32_bitwise_xor(Sv33, Stmp5);
  Stmp5 = float32_bitwise_xor(Stmp1, Stmp3);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Stmp1 = float32_bitwise_xor(Stmp1, Stmp5);
  Stmp3 = float32_bitwise_xor(Stmp3, Stmp5);
  Stmp5 = -2.0f;
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Stmp4 = 1.0f;
  Stmp4 = Stmp4 + Stmp5;
  Sa11 = Sa11 * Stmp4;
  Sa21 = Sa21 * Stmp4;
  Sa31 = Sa31 * Stmp4;
  Sv11 = Sv11 * Stmp4;
  Sv21 = Sv21 * Stmp4;
  Sv31 = Sv31 * Stmp4;
  Stmp4 =
      bit_cast<float32>(select(Stmp2 < Stmp3, Expr(int(0xffffffff)), Expr(0)));
  Stmp5 = float32_bitwise_xor(Sa12, Sa13);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sa12 = float32_bitwise_xor(Sa12, Stmp5);
  Sa13 = float32_bitwise_xor(Sa13, Stmp5);
  Stmp5 = float32_bitwise_xor(Sa22, Sa23);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sa22 = float32_bitwise_xor(Sa22, Stmp5);
  Sa23 = float32_bitwise_xor(Sa23, Stmp5);
  Stmp5 = float32_bitwise_xor(Sa32, Sa33);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sa32 = float32_bitwise_xor(Sa32, Stmp5);
  Sa33 = float32_bitwise_xor(Sa33, Stmp5);
  Stmp5 = float32_bitwise_xor(Sv12, Sv13);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sv12 = float32_bitwise_xor(Sv12, Stmp5);
  Sv13 = float32_bitwise_xor(Sv13, Stmp5);
  Stmp5 = float32_bitwise_xor(Sv22, Sv23);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sv22 = float32_bitwise_xor(Sv22, Stmp5);
  Sv23 = float32_bitwise_xor(Sv23, Stmp5);
  Stmp5 = float32_bitwise_xor(Sv32, Sv33);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Sv32 = float32_bitwise_xor(Sv32, Stmp5);
  Sv33 = float32_bitwise_xor(Sv33, Stmp5);
  Stmp5 = float32_bitwise_xor(Stmp2, Stmp3);
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Stmp2 = float32_bitwise_xor(Stmp2, Stmp5);
  Stmp3 = float32_bitwise_xor(Stmp3, Stmp5);
  Stmp5 = -2.0f;
  Stmp5 = float32_bitwise_and(Stmp5, Stmp4);
  Stmp4 = 1.0f;
  Stmp4 = Stmp4 + Stmp5;
  Sa13 = Sa13 * Stmp4;
  Sa23 = Sa23 * Stmp4;
  Sa33 = Sa33 * Stmp4;
  Sv13 = Sv13 * Stmp4;
  Sv23 = Sv23 * Stmp4;
  Sv33 = Sv33 * Stmp4;
  Su11 = 1.0f;
  Su21 = 0.0f;
  Su31 = 0.0f;
  Su12 = 0.0f;
  Su22 = 1.0f;
  Su32 = 0.0f;
  Su13 = 0.0f;
  Su23 = 0.0f;
  Su33 = 1.0f;
  Ssh = Sa21 * Sa21;
  Ssh = bit_cast<float32>(
      select(Ssh >= Ssmall_number, Expr(int(0xffffffff)), Expr(0)));
  Ssh = float32_bitwise_and(Ssh, Sa21);
  Stmp5 = 0.0f;
  Sch = Stmp5 - Sa11;
  Sch = max(Sch, Sa11);
  Sch = max(Sch, Ssmall_number);
  Stmp5 =
      bit_cast<float32>(select(Sa11 >= Stmp5, Expr(int(0xffffffff)), Expr(0)));
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Stmp1 = Stmp1 * Stmp2;
  Sch = Sch + Stmp1;
  Stmp1 = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp5)), Ssh);
  Stmp2 = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp5)), Sch);
  Sch = float32_bitwise_and(Stmp5, Sch);
  Ssh = float32_bitwise_and(Stmp5, Ssh);
  Sch = float32_bitwise_or(Sch, Stmp1);
  Ssh = float32_bitwise_or(Ssh, Stmp2);
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Sch = Sch * Stmp1;
  Ssh = Ssh * Stmp1;
  Sc = Sch * Sch;
  Ss = Ssh * Ssh;
  Sc = Sc - Ss;
  Ss = Ssh * Sch;
  Ss = Ss + Ss;
  Stmp1 = Ss * Sa11;
  Stmp2 = Ss * Sa21;
  Sa11 = Sc * Sa11;
  Sa21 = Sc * Sa21;
  Sa11 = Sa11 + Stmp2;
  Sa21 = Sa21 - Stmp1;
  Stmp1 = Ss * Sa12;
  Stmp2 = Ss * Sa22;
  Sa12 = Sc * Sa12;
  Sa22 = Sc * Sa22;
  Sa12 = Sa12 + Stmp2;
  Sa22 = Sa22 - Stmp1;
  Stmp1 = Ss * Sa13;
  Stmp2 = Ss * Sa23;
  Sa13 = Sc * Sa13;
  Sa23 = Sc * Sa23;
  Sa13 = Sa13 + Stmp2;
  Sa23 = Sa23 - Stmp1;
  Stmp1 = Ss * Su11;
  Stmp2 = Ss * Su12;
  Su11 = Sc * Su11;
  Su12 = Sc * Su12;
  Su11 = Su11 + Stmp2;
  Su12 = Su12 - Stmp1;
  Stmp1 = Ss * Su21;
  Stmp2 = Ss * Su22;
  Su21 = Sc * Su21;
  Su22 = Sc * Su22;
  Su21 = Su21 + Stmp2;
  Su22 = Su22 - Stmp1;
  Stmp1 = Ss * Su31;
  Stmp2 = Ss * Su32;
  Su31 = Sc * Su31;
  Su32 = Sc * Su32;
  Su31 = Su31 + Stmp2;
  Su32 = Su32 - Stmp1;
  Ssh = Sa31 * Sa31;
  Ssh = bit_cast<float32>(
      select(Ssh >= Ssmall_number, Expr(int(0xffffffff)), Expr(0)));
  Ssh = float32_bitwise_and(Ssh, Sa31);
  Stmp5 = 0.0f;
  Sch = Stmp5 - Sa11;
  Sch = max(Sch, Sa11);
  Sch = max(Sch, Ssmall_number);
  Stmp5 =
      bit_cast<float32>(select(Sa11 >= Stmp5, Expr(int(0xffffffff)), Expr(0)));
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Stmp1 = Stmp1 * Stmp2;
  Sch = Sch + Stmp1;
  Stmp1 = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp5)), Ssh);
  Stmp2 = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp5)), Sch);
  Sch = float32_bitwise_and(Stmp5, Sch);
  Ssh = float32_bitwise_and(Stmp5, Ssh);
  Sch = float32_bitwise_or(Sch, Stmp1);
  Ssh = float32_bitwise_or(Ssh, Stmp2);
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Sch = Sch * Stmp1;
  Ssh = Ssh * Stmp1;
  Sc = Sch * Sch;
  Ss = Ssh * Ssh;
  Sc = Sc - Ss;
  Ss = Ssh * Sch;
  Ss = Ss + Ss;
  Stmp1 = Ss * Sa11;
  Stmp2 = Ss * Sa31;
  Sa11 = Sc * Sa11;
  Sa31 = Sc * Sa31;
  Sa11 = Sa11 + Stmp2;
  Sa31 = Sa31 - Stmp1;
  Stmp1 = Ss * Sa12;
  Stmp2 = Ss * Sa32;
  Sa12 = Sc * Sa12;
  Sa32 = Sc * Sa32;
  Sa12 = Sa12 + Stmp2;
  Sa32 = Sa32 - Stmp1;
  Stmp1 = Ss * Sa13;
  Stmp2 = Ss * Sa33;
  Sa13 = Sc * Sa13;
  Sa33 = Sc * Sa33;
  Sa13 = Sa13 + Stmp2;
  Sa33 = Sa33 - Stmp1;
  Stmp1 = Ss * Su11;
  Stmp2 = Ss * Su13;
  Su11 = Sc * Su11;
  Su13 = Sc * Su13;
  Su11 = Su11 + Stmp2;
  Su13 = Su13 - Stmp1;
  Stmp1 = Ss * Su21;
  Stmp2 = Ss * Su23;
  Su21 = Sc * Su21;
  Su23 = Sc * Su23;
  Su21 = Su21 + Stmp2;
  Su23 = Su23 - Stmp1;
  Stmp1 = Ss * Su31;
  Stmp2 = Ss * Su33;
  Su31 = Sc * Su31;
  Su33 = Sc * Su33;
  Su31 = Su31 + Stmp2;
  Su33 = Su33 - Stmp1;
  Ssh = Sa32 * Sa32;
  Ssh = bit_cast<float32>(
      select(Ssh >= Ssmall_number, Expr(int(0xffffffff)), Expr(0)));
  Ssh = float32_bitwise_and(Ssh, Sa32);
  Stmp5 = 0.0f;
  Sch = Stmp5 - Sa22;
  Sch = max(Sch, Sa22);
  Sch = max(Sch, Ssmall_number);
  Stmp5 =
      bit_cast<float32>(select(Sa22 >= Stmp5, Expr(int(0xffffffff)), Expr(0)));
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Stmp1 = Stmp1 * Stmp2;
  Sch = Sch + Stmp1;
  Stmp1 = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp5)), Ssh);
  Stmp2 = float32_bitwise_and(Expr(~bit_cast<int32>(Stmp5)), Sch);
  Sch = float32_bitwise_and(Stmp5, Sch);
  Ssh = float32_bitwise_and(Stmp5, Ssh);
  Sch = float32_bitwise_or(Sch, Stmp1);
  Ssh = float32_bitwise_or(Ssh, Stmp2);
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Sch = Sch * Stmp1;
  Ssh = Ssh * Stmp1;
  Sc = Sch * Sch;
  Ss = Ssh * Ssh;
  Sc = Sc - Ss;
  Ss = Ssh * Sch;
  Ss = Ss + Ss;
  Stmp1 = Ss * Sa21;
  Stmp2 = Ss * Sa31;
  Sa21 = Sc * Sa21;
  Sa31 = Sc * Sa31;
  Sa21 = Sa21 + Stmp2;
  Sa31 = Sa31 - Stmp1;
  Stmp1 = Ss * Sa22;
  Stmp2 = Ss * Sa32;
  Sa22 = Sc * Sa22;
  Sa32 = Sc * Sa32;
  Sa22 = Sa22 + Stmp2;
  Sa32 = Sa32 - Stmp1;
  Stmp1 = Ss * Sa23;
  Stmp2 = Ss * Sa33;
  Sa23 = Sc * Sa23;
  Sa33 = Sc * Sa33;
  Sa23 = Sa23 + Stmp2;
  Sa33 = Sa33 - Stmp1;
  Stmp1 = Ss * Su12;
  Stmp2 = Ss * Su13;
  Su12 = Sc * Su12;
  Su13 = Sc * Su13;
  Su12 = Su12 + Stmp2;
  Su13 = Su13 - Stmp1;
  Stmp1 = Ss * Su22;
  Stmp2 = Ss * Su23;
  Su22 = Sc * Su22;
  Su23 = Sc * Su23;
  Su22 = Su22 + Stmp2;
  Su23 = Su23 - Stmp1;
  Stmp1 = Ss * Su32;
  Stmp2 = Ss * Su33;
  Su32 = Sc * Su32;
  Su33 = Sc * Su33;
  Su32 = Su32 + Stmp2;
  Su33 = Su33 - Stmp1;
  Matrix u(3, 3), v(3, 3), sigma(3);
  u(0, 0) = Su11;
  u(1, 0) = Su21;
  u(2, 0) = Su31;
  u(0, 1) = Su12;
  u(1, 1) = Su22;
  u(2, 1) = Su32;
  u(0, 2) = Su13;
  u(1, 2) = Su23;
  u(2, 2) = Su33;
  v(0, 0) = Sv11;
  v(1, 0) = Sv21;
  v(2, 0) = Sv31;
  v(0, 1) = Sv12;
  v(1, 1) = Sv22;
  v(2, 1) = Sv32;
  v(0, 2) = Sv13;
  v(1, 2) = Sv23;
  v(2, 2) = Sv33;
  sigma(0) = Sa11;
  sigma(1) = Sa22;
  sigma(2) = Sa33;
  return std::make_tuple(u, sigma, v);
}

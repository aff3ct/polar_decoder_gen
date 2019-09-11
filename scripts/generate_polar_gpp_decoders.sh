#/bin/bash

ROOT=src_generated
if [ "$#" -gt "0" ];
then
	ROOT=$1
fi

mkdir ./$ROOT          > /dev/null 2>&1
mkdir ./$ROOT/SC/      > /dev/null 2>&1
mkdir ./$ROOT/SCL/     > /dev/null 2>&1
mkdir ./$ROOT/SCL/CRC/ > /dev/null 2>&1

# Frozen bits generation method (Gaussian Approximation = "GA", Tal & Vardy = "TV")
GEN="GA"

echo "Generates GPP SC decoders (rate 1/2)..."
./build/bin/polar_decoder_gen --dec-type SC -N       4 -K      2 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4_K2_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N       8 -K      4 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8_K4_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N      16 -K      8 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16_K8_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N      32 -K     16 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32_K16_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N      64 -K     32 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N64_K32_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N     128 -K     64 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N128_K64_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N     256 -K    128 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N256_K128_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N     512 -K    256 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N512_K256_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N    1024 -K    512 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N1024_K512_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N    2048 -K   1024 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1024_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N    4096 -K   2048 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4096_K2048_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N    4096 -K   2048 --fbg-noise 3.3 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4096_K2048_SNR33.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N    8192 -K   4096 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8192_K4096_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N   16384 -K   8192 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16384_K8192_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N   32768 -K  16384 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K16384_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N   32768 -K  16384 --fbg-noise 1.8 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K16384_SNR18.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N   65536 -K  32768 --fbg-noise 1.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N65536_K32768_SNR15.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N   65536 -K  32768 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N65536_K32768_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N  131072 -K  65536 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N131072_K65536_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N  262144 -K 131072 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N262144_K131072_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N  524288 -K 262144 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N524288_K262144_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 1048576 -K 524288 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N1048576_K524288_SNR25.report 2>&1

echo "Generates GPP SC decoders (rate 5/6)..."
./build/bin/polar_decoder_gen --dec-type SC -N       4 -K      3 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4_K3_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N       8 -K      7 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8_K7_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N      16 -K     13 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16_K13_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N      32 -K     27 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32_K27_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N      64 -K     53 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N64_K53_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N     128 -K    107 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N128_K107_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N     256 -K    213 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N256_K213_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N     512 -K    427 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N512_K427_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N    1024 -K    853 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N1024_K853_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N    2048 -K   1707 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1707_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N    4096 -K   3413 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4096_K3413_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N    8192 -K   6827 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8192_K6827_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N   16384 -K  13653 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16384_K13653_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N   32768 -K  27307 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K27307_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N   65536 -K  54613 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N65536_K54613_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N  131072 -K 109227 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N131072_K109227_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N  262144 -K 218453 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N262144_K218453_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N  524288 -K 436907 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N524288_K436907_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 1048576 -K 873813 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N1048576_K873813_SNR40.report 2>&1

echo "Generates GPP SC decoders N = 2048 (rate 1/10, 2/10, ..., 9/10)..."
./build/bin/polar_decoder_gen --dec-type SC -N 2048 -K  205 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K205_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 2048 -K  410 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K410_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 2048 -K  614 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K614_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 2048 -K  819 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K819_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 2048 -K 1024 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1024_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 2048 -K 1229 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1229_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 2048 -K 1434 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1434_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 2048 -K 1638 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1638_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 2048 -K 1843 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1843_SNR25.report 2>&1

echo "Generates GPP SC decoders N = 32768 (rate 1/10, 2/10, ..., 9/10)..."
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K  3277 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K3277_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K  6554 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K6554_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K  9830 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K9830_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K 13107 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K13107_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K 16384 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K16384_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K 19661 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K19661_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K 22938 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K22938_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K 26214 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K26214_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K 29491 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K29491_SNR25.report 2>&1

echo "Generates GPP SC decoders (other rates)..."
./build/bin/polar_decoder_gen --dec-type SC -N  2048 -K   410 --fbg-noise 2.5 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K410_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N  2048 -K  1843 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1843_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 16384 -K 14746 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16384_K14746_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K 27568 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K27568_SNR40.report 2>&1
./build/bin/polar_decoder_gen --dec-type SC -N 32768 -K 29492 --fbg-noise 4.0 --fbg-gen-method $GEN --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K29492_SNR40.report 2>&1

echo "Generates GPP SCL decoders (all rates)..."
./build/bin/polar_decoder_gen --dec-type SCL -N    4 -K    2 --fbg-noise 2.5 --dec-polar-nodes "{R0,R0L,R1,REP,REPL,SPC_4}"  --fbg-gen-method $GEN --dec-path ./$ROOT/SCL/CRC > ./$ROOT/SCL/CRC/Decoder_polar_SCL_fast_CA_sys_N4_K2_SNR25.report 2>&1
./build/bin/polar_decoder_gen --dec-type SCL -N 2048 -K 1755 --fbg-noise 3.5 --dec-polar-nodes "{R0,R0L,R1,REP,REPL,SPC_4}"  --fbg-gen-method $GEN --dec-path ./$ROOT/SCL/CRC > ./$ROOT/SCL/CRC/Decoder_polar_SCL_fast_CA_sys_N2048_K1755_SNR35.report 2>&1
./build/bin/polar_decoder_gen --dec-type SCL -N  256 -K   64 --fbg-noise 3.0 --dec-polar-nodes "{R0,R0L,R1,REP,REPL,SPC_4+}" --fbg-gen-method $GEN --dec-path ./$ROOT/SCL/CRC > ./$ROOT/SCL/CRC/Decoder_polar_SCL_fast_CA_sys_N256_K64_SNR30.report 2>&1
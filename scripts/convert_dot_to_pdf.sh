#/bin/bash

ROOT=src_generated
if [ "$#" -gt "0" ];
then
	ROOT=$1
fi

# Make sure to have Graphviz installed (http://www.graphviz.org/)

echo "Generates SC graphs (from *.dot to *.dot.pdf, rate 1/2)..."
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4_K2_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4_K2_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8_K4_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16_K8_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32_K16_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N64_K32_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N128_K64_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N256_K128_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N512_K256_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N1024_K512_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1024_SNR25.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4096_K2048_SNR25.dot -O

echo "Generates SC graphs (from *.dot to *.dot.pdf, rate 5/6)..."
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4_K3_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8_K7_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16_K13_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32_K27_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N64_K53_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N128_K107_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N256_K213_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N512_K427_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N1024_K853_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1707_SNR40.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4096_K3413_SNR40.dot -O

echo "Generates SC short graphs (from *.short.dot to *.short.dot.pdf, rate 1/2)..."
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4_K2_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4_K2_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8_K4_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16_K8_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32_K16_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N64_K32_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N128_K64_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N256_K128_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N512_K256_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N1024_K512_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1024_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4096_K2048_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8192_K4096_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16384_K8192_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K16384_SNR25.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K16384_SNR18.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N65536_K32768_SNR15.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N65536_K32768_SNR25.short.dot -O

echo "Generates SC short graphs (from *.short.dot to *.short.dot.pdf, rate 5/6)..."
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4_K3_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8_K7_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16_K13_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32_K27_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N64_K53_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N128_K107_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N256_K213_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N512_K427_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N1024_K853_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N2048_K1707_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N4096_K3413_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N8192_K6827_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N16384_K13653_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N32768_K27307_SNR40.short.dot -O
dot -Tpdf ./$ROOT/SC/Decoder_polar_SC_fast_sys_N65536_K54613_SNR40.short.dot -O

echo "Generates SCL graphs (from *.dot to *.dot.pdf, all rates)..."
dot -Tpdf ./$ROOT/SCL/CRC/Decoder_polar_SCL_fast_CA_sys_N4_K2_SNR25.dot -O
dot -Tpdf ./$ROOT/SCL/CRC/Decoder_polar_SCL_fast_CA_sys_N2048_K1755_SNR35.dot -O
dot -Tpdf ./$ROOT/SCL/CRC/Decoder_polar_SCL_fast_CA_sys_N256_K64_SNR30.dot -O

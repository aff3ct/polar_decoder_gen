#/bin/bash

ROOT=src_generated
if [ "$#" -gt "0" ];
then
	ROOT=$1
fi

mkdir ./$ROOT       > /dev/null 2>&1
mkdir ./$ROOT/SC/   > /dev/null 2>&1
mkdir ./$ROOT/SCAN/ > /dev/null 2>&1

echo "Generates TTA SC decoders (rate 1/2)..."
./build/bin/polar_decoder_gen -D SC -N 1024 -K 512 --fbg-gen-method FILE --fbg-awgn-path lib/aff3ct/conf/cde/awgn_polar_codes/TV/10/N1024_awgn_s0.750.pc --dec-polar-nodes "{R0_8+,R1_8+,R0L_8+}" --fbg-noise 1.0 -a TTA --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_simd_unrolled_N1024_K512.report 2>&1
./build/bin/polar_decoder_gen -D SC -N 512  -K 256 --fbg-gen-method FILE --fbg-awgn-path lib/aff3ct/conf/cde/awgn_polar_codes/TV/9/N512_awgn_s0.750.pc   --dec-polar-nodes "{R0_8+,R1_8+}"        --fbg-noise 1.0 -a TTA --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_simd_unrolled_N512_K256.report  2>&1
./build/bin/polar_decoder_gen -D SC -N 256  -K 128 --fbg-gen-method FILE --fbg-awgn-path lib/aff3ct/conf/cde/awgn_polar_codes/TV/8/N256_awgn_s0.750.pc   --dec-polar-nodes "{R0_8+,R1_8+}"        --fbg-noise 1.0 -a TTA --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_simd_unrolled_N256_K128.report  2>&1
./build/bin/polar_decoder_gen -D SC -N 128  -K 64  --fbg-gen-method FILE --fbg-awgn-path lib/aff3ct/conf/cde/awgn_polar_codes/TV/7/N128_awgn_s0.750.pc   --dec-polar-nodes "{R0_8+,R1_8+}"        --fbg-noise 1.0 -a TTA --dec-path ./$ROOT/SC > ./$ROOT/SC/Decoder_simd_unrolled_N128_K64.report   2>&1

echo "Generates TTA SCAN decoders (rate 1/2)..."
./build/bin/polar_decoder_gen -D SCAN -N 1024 -K 512 --fbg-gen-method FILE --fbg-awgn-path lib/aff3ct/conf/cde/awgn_polar_codes/TV/10/N1024_awgn_s0.750.pc --dec-polar-nodes "{}" --fbg-noise 1.0 -a TTA --dec-path ./$ROOT/SCAN > ./$ROOT/SCAN/Decoder_simd_scan_N1024_K512.report 2>&1

#/bin/bash

if [ ! -d "tests/refs" ]; then
	cd tests
	unzip refs.zip
	rc=$?; if [[ $rc != 0 ]]; then echo "Unzip the refs failed :-(!"; exit $rc; fi
	cd ..
fi

./scripts/generate_polar_gpp_decoders.sh tests_output_GPP
rm -rf tests/tests_output_GPP
mv tests_output_GPP tests
rm tests/tests_output_GPP/SC/*.report
rm tests/tests_output_GPP/SCL/CRC/*.report

diff tests/tests_output_GPP/SC tests/refs/GPP/SC
rc=$?; if [[ $rc != 0 ]]; then echo "Tests GPP SC failed :-(!"; exit $rc; fi
echo "Tests GPP SC passed successfully!"

diff tests/tests_output_GPP/SCL/CRC tests/refs/GPP/SCL/CRC
rc=$?; if [[ $rc != 0 ]]; then echo "Tests GPP SCL failed :-(!"; exit $rc; fi
echo "Tests GPP SCL passed successfully!"

rm -rf tests/tests_output_GPP

./scripts/generate_polar_tta_decoders.sh tests_output_TTA
rm -rf tests/tests_output_TTA
mv tests_output_TTA tests
rm tests/tests_output_TTA/SC/*.report
rm tests/tests_output_TTA/SCAN/*.report

diff tests/tests_output_TTA/SC tests/refs/TTA/SC
rc=$?; if [[ $rc != 0 ]]; then echo "Tests TTA SC failed :-(!"; exit $rc; fi
echo "Tests TTA SC passed successfully!"

diff tests/tests_output_TTA/SCAN tests/refs/TTA/SCAN
rc=$?; if [[ $rc != 0 ]]; then echo "Tests TTA SCL failed :-(!"; exit $rc; fi
echo "Tests TTA SCL passed successfully!"

rm -rf tests/tests_output_TTA
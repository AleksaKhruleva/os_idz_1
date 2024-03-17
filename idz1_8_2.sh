rm -r ./idz1_8_2/cmake-build-debug

if ! cmake -S ./idz1_8_2 -B ./idz1_8_2/cmake-build-debug; then
    echo cmake initialize error
fi
if ! cmake --build ./idz1_8_2/cmake-build-debug --target idz1_8_2; then
    echo cmake build error
fi

echo "-------------------------------------------------------------------------"
./idz1_8_2/cmake-build-debug/idz1_8_2
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_8_2/cmake-build-debug/idz1_8_2
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_8_2/cmake-build-debug/idz1_8_2
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_8_2/cmake-build-debug/idz1_8_2
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_8_2/cmake-build-debug/idz1_8_2
sleep 1
echo "-------------------------------------------------------------------------"

rm -r ./idz1_8_2/cmake-build-debug

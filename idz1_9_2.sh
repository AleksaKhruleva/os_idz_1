rm -r ./idz1_9_2/cmake-build-debug

if ! cmake -S ./idz1_9_2 -B ./idz1_9_2/cmake-build-debug; then
    echo cmake initialize error
fi
if ! cmake --build ./idz1_9_2/cmake-build-debug --target idz1_9_2; then
    echo cmake build error
fi

echo "-------------------------------------------------------------------------"
./idz1_9_2/cmake-build-debug/idz1_9_2
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_9_2/cmake-build-debug/idz1_9_2
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_9_2/cmake-build-debug/idz1_9_2
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_9_2/cmake-build-debug/idz1_9_2
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_9_2/cmake-build-debug/idz1_9_2
sleep 1
echo "-------------------------------------------------------------------------"

rm -r ./idz1_9_2/cmake-build-debug

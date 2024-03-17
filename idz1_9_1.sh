rm -r ./idz1_9_1/cmake-build-debug

if ! cmake -S ./idz1_9_1 -B ./idz1_9_1/cmake-build-debug; then
    echo cmake initialize error
fi
if ! cmake --build ./idz1_9_1/cmake-build-debug --target idz1_9_1; then
    echo cmake build error
fi

echo "-------------------------------------------------------------------------"
./idz1_9_1/cmake-build-debug/idz1_9_1 -i case1i.txt -o ./idz1_9_1/case1o.txt
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_9_1/cmake-build-debug/idz1_9_1 -i case2i.txt -o ./idz1_9_1/case2o.txt
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_9_1/cmake-build-debug/idz1_9_1 -i case3i.txt -o ./idz1_9_1/case3o.txt
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_9_1/cmake-build-debug/idz1_9_1 -i case4i.txt -o ./idz1_9_1/case4o.txt
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_9_1/cmake-build-debug/idz1_9_1 -i case5i.txt -o ./idz1_9_1/case5o.txt
sleep 1
echo "-------------------------------------------------------------------------"
./idz1_9_1/cmake-build-debug/idz1_9_1
echo "-------------------------------------------------------------------------"

rm -r ./idz1_9_1/cmake-build-debug

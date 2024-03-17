rm -r ./idz1_4/cmake-build-debug

if ! cmake -S ./idz1_4 -B ./idz1_4/cmake-build-debug; then
    echo cmake initialize error
fi
if ! cmake --build ./idz1_4/cmake-build-debug --target idz1_4; then
    echo cmake build error
fi

echo "-------------------------------------------------------------------------"
./idz1_4/cmake-build-debug/idz1_4 -i case1i.txt -o ./idz1_4/case1o.txt
echo "-------------------------------------------------------------------------"
./idz1_4/cmake-build-debug/idz1_4 -i case2i.txt -o ./idz1_4/case2o.txt
echo "-------------------------------------------------------------------------"
./idz1_4/cmake-build-debug/idz1_4 -i case3i.txt -o ./idz1_4/case3o.txt
echo "-------------------------------------------------------------------------"
./idz1_4/cmake-build-debug/idz1_4 -i case4i.txt -o ./idz1_4/case4o.txt
echo "-------------------------------------------------------------------------"
./idz1_4/cmake-build-debug/idz1_4 -i case5i.txt -o ./idz1_4/case5o.txt
echo "-------------------------------------------------------------------------"
./idz1_4/cmake-build-debug/idz1_4
echo "-------------------------------------------------------------------------"

rm -r ./idz1_4/cmake-build-debug
